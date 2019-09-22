#pragma once
#include <array>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <random>
#include <string>

enum :std::uint_fast8_t {
	fish_scene_empty,
	fish_scene_swim,
	fish_scene_get,
	fish_scene_up_fly,
	fish_scene_down_fly,
	fish_scene_stay
};

enum :std::uint_fast8_t {
	fisher_scene_empty,
	fisher_scene_hit,
	fisher_scene_get,
	fisher_scene_up_fly,
	fisher_scene_down_fly,
	fisher_scene_num
};

enum :std::uint_fast8_t {
	// 小魚
	fish_small,
	// 中魚
	fish_medium,
	// 大魚
	fish_large,
	// マンボウ
	fish_sunfish,
	// ジンベイザメ
	fish_whale_shark,
	// リュウグウノツカイ
	fish_regalecus_glesne,
	// 魚の種類
	fish_num
};

// 魚の大きさ
constexpr std::array<std::uint_fast8_t, fish_num + 1> fish_size{{ fish_small,fish_medium,fish_large,fish_medium,fish_large,fish_large,fish_small }};

// 魚の浮き待機フレーム
constexpr std::array<std::uint_fast8_t, fish_num + 1> fish_frame{ { 120,90,40,30,10,20,1 } };

class Fish {
public:

	// 魚のステータス
	struct FishStatus {
		std::uint_fast8_t fish_type{};
		std::int_fast32_t x{};
		std::int_fast32_t y{};
		double r{};
		double add_r{};
		bool can_fly{ true };
		std::uint_fast8_t status{ fish_scene_swim };
		std::int_fast32_t frame{};

		FishStatus() = default;
		FishStatus(const std::uint_fast8_t fish_type_, const std::uint_fast32_t x_, const std::uint_fast32_t y_)
			:fish_type(fish_type_), x(x_), y(y_) {}
	};

	// 魚の生成
	void addFish() {
		std::mt19937 engine(seed_gen());
		// 初期の魚の種類
		std::uniform_int_distribution<> dist_x(range_x, range_w);
		std::uniform_int_distribution<> dist_y(range_y, range_h);
		std::uniform_int_distribution<> dist_spawn(0, 255);
		fish_swim.emplace_back(
			// 魚の種類
			static_cast<std::uint_fast8_t>(this->spawnFish(dist_spawn(engine))),
			// X座標
			static_cast<std::uint_fast32_t>(dist_x(engine)),
			// Y座標
			static_cast<std::uint_fast32_t>(dist_y(engine)));
	}

	Fish() {

		font_timer = CreateFontToHandle(NULL, 100, 9, DX_FONTTYPE_EDGE);

		// 画像格納
		back = LoadGraph("image/ocean.png");
		image_uki = LoadGraph("image/uki.png");
		wave = LoadGraph("image/wave.png");
		fisher_image[fisher_scene_empty] = LoadGraph("image/fisher1.png");
		fisher_image[fisher_scene_hit] = LoadGraph("image/fisher2.png");

		image_ocean_sky = LoadGraph("image/ocean_sky.png");
		image_ocean_cloud = LoadGraph("image/ocean_cloud.png");
		image_ocean_island = LoadGraph("image/ocean_island.png");
		for (std::size_t i{}; i < fish_image.size(); ++i) {
			fish_image[i] = LoadGraph(std::string("image/fish" + std::to_string(i + 1) + ".png").c_str());
		}
		for (std::size_t i{}; i < fish_shadow_image.size(); ++i) {
			fish_shadow_image[i] = LoadGraph(std::string("image/fish_shadow" + std::to_string(i + 1) + ".png").c_str());
		}

		std::mt19937 engine(seed_gen());
		std::uniform_int_distribution<std::size_t> dist(1, 3);
		// 初期の魚の数
		fish_swim.resize(dist(engine));

		// 初期の魚の種類
		std::uniform_int_distribution<> dist_x(range_x, range_w);
		std::uniform_int_distribution<> dist_y(range_y, range_h);
		std::uniform_int_distribution<> dist_spawn(0, 255);
		for (auto&& i : fish_swim) {
			i.fish_type = (std::uint_fast8_t)this->spawnFish(dist_spawn(engine));
			i.x = (std::uint_fast32_t)dist_x(engine);
			i.y = (std::uint_fast32_t)dist_y(engine);
		}

	}

	void call(bool down_key[], std::uint_fast8_t& scene_id, std::uint_fast32_t& fished_count, std::uint_fast32_t& go_fish_count) {
		--timer;
		std::mt19937 engine(seed_gen());

		// 背景を描画
		DxLib::DrawGraph(0, 0, image_ocean_sky, FALSE);
		DxLib::DrawGraph(0, 0, image_ocean_cloud, TRUE);

		// 釣った魚を描画
		for (std::size_t i{}; i < fish_get.size(); ++i) {
			if (fish_get[i].status == fish_scene_down_fly) {
				fish_get[i].y += 20;
				fish_get[i].r += fish_get[i].add_r;
				if (fish_get[i].y > 750 - fish_get.size() * 5) fish_get[i].status = fish_scene_stay;
			}
			DrawRotaGraph((int)fish_get[i].x, (int)fish_get[i].y, 1.0f, fish_get[i].r, fish_image[fish_get[i].fish_type], TRUE);
		}
		bool is_hit{ false };
		// 泳ぐ魚の制御
		for (std::size_t i{}; i < fish_swim.size(); ++i) {

			fish_swim[i].x = std::int_fast32_t(fish_swim[i].x * 0.95 + uki_x * 0.05);
			fish_swim[i].y = std::int_fast32_t(fish_swim[i].y * 0.95 + uki_y * 0.05);

			std::int_fast32_t fish_dis{ (fish_swim[i].x - uki_x) * (fish_swim[i].x - uki_x) + (fish_swim[i].y - uki_y) * (fish_swim[i].y - uki_y) };
			if (fish_dis < 1500) {
				++fish_swim[i].frame;
				is_hit = true;
				printfDx("%d", fish_dis);
				std::uniform_real_distribution<double> dist_r(0.01, 0.2);

				if (fish_swim[i].frame >= fish_frame[fish_swim[i].fish_type]) {
					fish_swim.erase(fish_swim.begin() + i);
					//--i;
				}
				if (i >= fish_swim.size()) break;
				if (down_key[KEY_INPUT_SPACE]) {
					fish_get.emplace_back(fish_swim[i]);
					fish_get.back().status = fish_scene_up_fly;
					fish_get.back().add_r = dist_r(engine);
					fish_swim.erase(fish_swim.begin() + i);
					//--i;
				}

			}
		}

		std::uint_fast8_t fisher_status{};
		if (is_hit) fisher_status = fisher_scene_hit;
		if (down_key[KEY_INPUT_SPACE]) fisher_status = fisher_scene_get;

		// 海と島
		DxLib::DrawGraph(0, 0, image_ocean_island, TRUE);

		DxLib::DrawGraph(0, 0, fisher_image[(is_hit?fisher_scene_hit: fisher_scene_empty)], TRUE);
		(is_hit)?
			DxLib::DrawLine(uki_x, uki_y, 898, 637, 0x00000000) :
			DxLib::DrawLine(uki_x, uki_y, 957, 527, 0x00000000);
		//898,637
		DxLib::DrawGraph(0, 0, wave, TRUE);

		DxLib::DrawGraph(0, 0, image_uki, TRUE);

		//DxLib::DrawBox(range_x, range_y, range_w, range_h, 0xffffffff, FALSE);
		
		DrawFormatStringToHandle(900, 150, GetColor(255, 255, 255), font_timer, "%d.%d", timer / 60, (int)((timer % 60) / 60.0 * 100));

		// 泳ぐ魚の制御
		for (std::size_t i{}; i < fish_swim.size(); ++i) {
			DrawRotaGraph((int)fish_swim[i].x, (int)fish_swim[i].y, 1.0f, 0.0, fish_shadow_image[fish_size[fish_swim[i].fish_type]], TRUE); //todo
		}

		std::uniform_int_distribution<std::size_t> dist(1, 100);
		//if (dist(engine) > 98 && fish_swim.size() < 10) this->addFish();
		if (dist(engine) > 98) this->addFish();

		if (down_key[KEY_INPUT_SPACE]) {
			//printfDx("a");
		}

		// 釣った魚を描画
		for (std::size_t i{}; i < fish_get.size(); ++i) {

			if (fish_get[i].status == fish_scene_up_fly) {
				fish_get[i].y -= 30;
				fish_get[i].r += fish_get[i].add_r;
				if (fish_get[i].y < -500) {
					fish_get[i].x = 1200;
					fish_get[i].y = 0;
					fish_get[i].status = fish_scene_down_fly;
				}
				DrawRotaGraph((int)fish_get[i].x, (int)fish_get[i].y, 1.0f, fish_get[i].r, fish_image[fish_get[i].fish_type], TRUE);
			}
		}
		clsDx();
		//printfDx("%d.%d", timer / 60, (int)((timer % 60) / 60.0 * 100));

		if (timer <= 0) {
			scene_id = 2; // マップ
			timer = 60 * 3;
			fished_count = (std::uint_fast32_t)fish_get.size();
			++go_fish_count;
		}
	}

private:

	std::uint_fast8_t uki_frame{};

	int timer{ 60 * 3 };

	int uki_x{ 482 };
	int uki_y{ 872 };

	// 泳ぐ範囲
	const int range_x{ 0 };
	const int range_y{ 900 };
	const int range_w{ 900 };
	const int range_h{ 1080 };

	int back{ -1 };
	int wave{ -1 };

	int font_timer{ -1 };

	int image_uki{ -1 };
	int image_ocean_sky{ -1 };
	int image_ocean_cloud{ -1 };
	int image_ocean_island{ -1 };

	std::array<int, fisher_scene_num> fisher_image{ -1 };
	std::array<int, fish_num> fish_image{};
	std::array<int, fish_num> fish_shadow_image{};

	// デフォルト乱数
	std::random_device seed_gen{};

	// 取った魚
	std::vector<FishStatus> fish_get{};

	// 泳ぐ魚
	std::vector<FishStatus> fish_swim{};

	// 魚の生成確率
	std::uint_fast8_t spawnFish(const std::int_fast32_t fish_count) const {
		if (fish_count < 110) return fish_small;
		if (fish_count < 190) return fish_medium;
		if (fish_count < 230) return fish_large;
		if (fish_count < 250) return fish_sunfish;
		if (fish_count < 252) return fish_whale_shark;
		return fish_regalecus_glesne;
	}

};