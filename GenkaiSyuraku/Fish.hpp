#pragma once
#include <array>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <random>
#include <string>
#include "Item.hpp"

// 釣りの状態
enum :std::uint_fast8_t {
	fish_scene_empty,
	fish_scene_start,
	fish_scene_fish,
	fish_scene_end,
};

// 魚の状態
enum :std::uint_fast8_t {
	fish_status_empty,
	fish_status_swim,
	fish_status_get,
	fish_status_up_fly,
	fish_status_down_fly,
	fish_status_stay
};

// 漁師の状態
enum :std::uint_fast8_t {
	fisher_scene_empty,
	fisher_scene_hit,
	fisher_scene_get,
	fisher_scene_go,
	fisher_scene_num
};

// 魚リスト
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
constexpr std::array<std::uint_fast8_t, fish_num + 1> fish_size{ { fish_small,fish_medium,fish_large,fish_medium,fish_whale_shark,fish_regalecus_glesne,fish_small } };

// 魚の浮き待機フレーム
constexpr std::array<std::uint_fast8_t, fish_num + 1> fish_frame{ { 24,20,16,16,10,12,1 } };
constexpr std::array<std::uint_fast8_t, fish_num + 1> fish_start_frame{ { 5,5,5,5,5,5,1 } };
constexpr std::array<std::uint_fast8_t, fish_num + 1> fish_half_frame{ { 18,18,12,12,8,8,1 } };

constexpr std::array<float, 8> fish_sin{ { 0.0f,0.7f,1.0f,0.7f,0.0f,-0.7f,-1.0f,-0.7f } };
constexpr std::array<float, fish_num + 1> fish_shake{ { 3.0f,6.0f,9.0f,18.0f,60.0f,25.0f,0.0f } };

// 魚別のスコア
constexpr std::array<std::uint_fast32_t, fish_num + 1> fish_score{ { 1,3,8,12,50,35,1 } };

// 魚のデフォルトサイズ
constexpr std::array<float, fish_num + 1> fish_gram{ { 50,80,120,150,300,300,1 } };

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
		std::uint_fast8_t status{ fish_status_swim };
		std::int_fast32_t frame{};
		std::int_fast32_t start_frame{};

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

		font_timer = CreateFontToHandle(NULL, 100, 0, DX_FONTTYPE_NORMAL);

		// 画像格納
		for (std::size_t i{}; i < 4; ++i) {
			fish_start_image[i] = LoadGraph(std::string("image/fish_start" + std::to_string(i) + ".png").c_str());
		}
		bottle = LoadGraph("image/bottle.png");
		rare = LoadGraph("image/rare.png");
		super_rare = LoadGraph("image/super_rare.png");
		image_find_fish = LoadGraph("image/find_fish.png");
		image_result = LoadGraph("image/result2.png");
		back = LoadGraph("image/ocean.png");
		image_uki = LoadGraph("image/uki.png");
		wave = LoadGraph("image/wave.png");
		fisher_image[fisher_scene_empty] = LoadGraph("image/fisher1.png");
		fisher_image[fisher_scene_hit] = LoadGraph("image/fisher2.png");
		fisher_image[fisher_scene_go] = LoadGraph("image/fisher3.png");

		image_ocean_sky = LoadGraph("image/ocean_sky.png");
		image_ocean_cloud = LoadGraph("image/ocean_cloud.png");
		image_ocean_island = LoadGraph("image/ocean_island.png");
		for (std::size_t i{}; i < 6; ++i) {
			message_image[i] = LoadGraph(std::string("image/fish_message" + std::to_string(i) + ".png").c_str());
		}
		for (std::size_t i{}; i < fish_image.size(); ++i) {
			fish_image[i] = LoadGraph(std::string("image/fish" + std::to_string(i + 1) + ".png").c_str());
		}
		for (std::size_t i{}; i < fish_shadow_image.size(); ++i) {
			fish_shadow_image[i] = LoadGraph(std::string("image/fish_shadow" + std::to_string(i + 1) + ".png").c_str());
			result_shadow_image[i] = LoadGraph(std::string("image/result_shadow" + std::to_string(i + 1) + ".png").c_str());
			fish_30shadow_image[i] = LoadGraph(std::string("image/fish_30shadow" + std::to_string(i + 1) + ".png").c_str());
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

	void call(std::array<int, item_num>& item_count, bool up_key[], bool down_key[], std::uint_fast8_t& scene_id, std::uint_fast32_t& fished_count, std::uint_fast32_t& go_fish_count) {
		std::mt19937 engine(seed_gen());

		shake_value -= 0.5f;
		if (shake_value < 0.0f)shake_value = 0.0f;
		++shake_count;
		if (shake_count >= 8) shake_count = 0;

		int shake_y{ int(shake_value * fish_sin[shake_count])};

		++cloud_move_time;
		if (fish_scene != fish_scene_end)
		if (cloud_move_time >= cloud_move_time_max) {
			++cloud_x;
			cloud_move_time = 0;
		}

		// 背景を描画
		DxLib::DrawGraph(0, 0, image_ocean_sky, FALSE);
		DxLib::DrawGraph(-cloud_x, 0, image_ocean_cloud, TRUE);

		// 釣った魚を描画
		total_score = 0;
		for (std::size_t i{}; i < fish_get.size(); ++i) {
			total_score += fish_score[fish_get[i].fish_type];
			if (fish_get[i].status == fish_status_down_fly) {
				fish_get[i].y += 20;
				fish_get[i].r += fish_get[i].add_r;
				if (fish_get[i].y > 750 - fish_get.size() * 5) {
					fish_get[i].status = fish_status_stay;
					shake_value += fish_shake[fish_get[i].fish_type];
				}
			}
			DrawRotaGraph((int)fish_get[i].x, (int)fish_get[i].y + shake_y, 1.0f, fish_get[i].r, fish_image[fish_get[i].fish_type], TRUE);
		}
		uki_y = 872;
		bool is_hit{ false };
		bool is_fisher{ false };
		// 泳ぐ魚の制御
		if (fish_scene == fish_scene_fish)
		for (std::size_t i{}; i < fish_swim.size(); ++i) {

			++fish_swim[i].start_frame;
			fish_swim[i].x = std::int_fast32_t(double(fish_swim[i].x) * 0.95 + double(uki_x) * 0.05);
			fish_swim[i].y = std::int_fast32_t(fish_swim[i].y * 0.95 + (uki_y + 50) * 0.05);

			std::int_fast32_t fish_dis{ (fish_swim[i].x - uki_x) * (fish_swim[i].x - uki_x) + (fish_swim[i].y - (uki_y + 50)) * (fish_swim[i].y - (uki_y + 50)) };
			if (fish_dis < 1500) {
				uki_y = 890;
				++fish_swim[i].frame;
				is_hit = true;
				std::uniform_real_distribution<double> dist_r(0.01, 0.2);
				// 魚がかかっている時
				DxLib::DrawGraph(500, 600, image_find_fish, TRUE);
				if (fish_swim[i].fish_type == fish_sunfish || fish_swim[i].fish_type == fish_whale_shark || fish_swim[i].fish_type == fish_regalecus_glesne) {
					DxLib::DrawGraph(460, 600, image_find_fish, TRUE);
				}
				if (fish_swim[i].fish_type == fish_whale_shark || fish_swim[i].fish_type == fish_regalecus_glesne) {
					DxLib::DrawGraph(420, 600, image_find_fish, TRUE);
					DxLib::DrawGraph(0, 0, super_rare, TRUE);
				}
				if (fish_swim[i].fish_type == fish_sunfish) {
					DxLib::DrawGraph(0, 0, rare, TRUE);
				}

				if (fish_swim[i].frame >= fish_frame[fish_swim[i].fish_type]) {
					fish_swim.erase(fish_swim.begin() + i);
					--i;
					continue;
				}
				if (i >= fish_swim.size()) break;
				if (down_key[KEY_INPUT_SPACE] && timer > 0 && fisher_timer == 0) {
					is_fisher = true;
					fish_get.emplace_back(fish_swim[i]);
					fish_get.back().status = fish_status_up_fly;
					fish_get.back().add_r = dist_r(engine);
					fish_swim.erase(fish_swim.begin() + i);

					++fish_count[fish_get.back().fish_type];

					--i;
					continue;
				}

			}
		}
		if (is_fisher) fisher_timer = 30;

		std::uint_fast8_t fisher_status{ fisher_scene_empty };
		if (is_hit) fisher_status = fisher_scene_hit;
		//if (down_key[KEY_INPUT_SPACE] && timer > 0) fisher_status = fisher_scene_get;
		if (fisher_timer > 0) {
			--fisher_timer;
			fisher_status = fisher_scene_go;
		}

		// 海と島
		DxLib::DrawGraph(0, 0, image_ocean_island, TRUE);

		DxLib::DrawGraph(850, 400 + shake_y, fisher_image[fisher_status], TRUE);
		(fisher_timer > 0)? DxLib::DrawLine(uki_x, uki_y, 1250, 498 + shake_y, 0x00000000) :
		(is_hit) ?
			DxLib::DrawLine(uki_x, uki_y, 898, 637 + shake_y, 0x00000000) :
			DxLib::DrawLine(uki_x, uki_y, 957, 527 + shake_y, 0x00000000);
		//898,637
		DxLib::DrawGraph(850, 400 + shake_y, wave, TRUE);

		DxLib::DrawGraph(460, uki_y - 2, image_uki, TRUE);

		//DxLib::DrawBox(range_x, range_y, range_w, range_h, 0xffffffff, FALSE);


		// 泳ぐ魚の制御
		for (std::size_t i{}; i < fish_swim.size(); ++i) {
			if (fish_swim[i].start_frame < fish_start_frame[fish_swim[i].fish_type]) {
				DrawRotaGraph((int)fish_swim[i].x, (int)fish_swim[i].y, 1.0f, 0.0, fish_30shadow_image[fish_size[fish_swim[i].fish_type]], TRUE);
			}
			else if (fish_swim[i].frame >= fish_half_frame[fish_swim[i].fish_type]) {
				DrawRotaGraph((int)fish_swim[i].x, (int)fish_swim[i].y, 1.0f, 0.0, fish_30shadow_image[fish_size[fish_swim[i].fish_type]], TRUE);
			}
			else DrawRotaGraph((int)fish_swim[i].x, (int)fish_swim[i].y, 1.0f, 0.0, fish_shadow_image[fish_size[fish_swim[i].fish_type]], TRUE);
		}

		std::uniform_int_distribution<std::size_t> dist(1, 100);
		if (fish_scene == fish_scene_fish)
		if (dist(engine) > 92 && fish_swim.size() < 10) this->addFish();


		// 釣った魚を描画
		for (std::size_t i{}; i < fish_get.size(); ++i) {

			if (fish_get[i].status == fish_status_up_fly) {
				fish_get[i].y -= 30;
				fish_get[i].r += fish_get[i].add_r;
				if (fish_get[i].y < -500) {
					fish_get[i].x = 1200;
					fish_get[i].y = 0;
					fish_get[i].status = fish_status_down_fly;
				}
				DrawRotaGraph((int)fish_get[i].x, (int)fish_get[i].y + shake_y, 1.0f, fish_get[i].r, fish_image[fish_get[i].fish_type], TRUE);
			}
		}

		DrawCircle(200, 200, 80, 0xffffffff);
		if (fish_get.size() > 0) {
			DrawRotaGraph(200, 200, 0.5f, 0.0f, fish_image[fish_get.back().fish_type], TRUE);
		}
		
		switch (fish_scene)
		{
		case fish_scene_empty:
			break;
		case fish_scene_start:
			--fish_scene_start_timer;
			DxLib::DrawGraph(0, 0, fish_start_image[fish_scene_start_timer/100], TRUE);
			if (fish_scene_start_timer <= 0) fish_scene = fish_scene_fish;
			break;
		case fish_scene_fish:
			DrawFormatStringToHandle(0, 0, GetColor(30, 30, 30), font_timer, "制限時間：%d.%d", timer / 60, (int)((timer % 60) / 60.0 * 100));
			break;
		case fish_scene_end:
			DxLib::DrawGraph(0, 0, image_result, TRUE);
			DrawFormatStringToHandle(700, 380, GetColor(0, 0, 0), font_timer, "%d匹", fish_count[fish_small]);
			DrawFormatStringToHandle(700, 580, GetColor(0, 0, 0), font_timer, "%d匹", fish_count[fish_medium]);
			DrawFormatStringToHandle(700, 780, GetColor(0, 0, 0), font_timer, "%d匹", fish_count[fish_large]);
			DrawFormatStringToHandle(1400, 380, GetColor(0, 0, 0), font_timer, "%d匹", fish_count[fish_sunfish]);
			DrawFormatStringToHandle(1400, 580, GetColor(0, 0, 0), font_timer, "%d匹", fish_count[fish_whale_shark]);
			DrawFormatStringToHandle(1400, 780, GetColor(0, 0, 0), font_timer, "%d匹", fish_count[fish_regalecus_glesne]);
			for (std::size_t i{}; i < fish_num; ++i) {
				if (fish_count[i] == 0) DxLib::DrawGraph(0, 0, result_shadow_image[i], TRUE);
			}
			DxLib::DrawGraph(0, 0, message_image[scoreFish(total_score)], TRUE);
			break;
		}

		if (fish_scene == fish_scene_fish) {
			DrawBox(650, 600, 700, 700, 0xffffffff, TRUE);
			DrawBox(650, 600, 700, 700 - fisher_timer * 100 / 30, 0xff33aa33, TRUE);
			DxLib::DrawGraph(610, 552, bottle, TRUE);
		}
		// 強制リザルト画面
		if (up_key[KEY_INPUT_T]) timer = 0;

		if (fish_scene == fish_scene_fish && timer > 0) --timer;
		if (timer == 0) {
			if (up_key[KEY_INPUT_RETURN]) timer = -1;
			fish_scene = fish_scene_end;
		}
		else if (timer <= -1) {
			scene_id = 2; // マップ
			timer = 60 * 15;
			fished_count = (std::uint_fast32_t)fish_get.size();
			++go_fish_count;

			for (std::size_t i{}; i < fish_num; ++i) {
				fish_count[i] = 0;
			}

			item_count[item_fish_small] = fish_count[fish_small];
			item_count[item_fish_medium] = fish_count[fish_medium];
			item_count[item_fish_large] = fish_count[fish_large];
			item_count[item_fish_sunfish] = fish_count[fish_sunfish];
			item_count[item_fish_whale_shark] = fish_count[fish_whale_shark];
			item_count[item_fish_regalecus_glesne] = fish_count[fish_regalecus_glesne];

			cloud_move_time = 0;
			cloud_x = 0;
			fisher_timer = 0;
			fish_scene_start_timer = 100 * 4;
			fish_scene = fish_scene_start;
			total_score = 0;
			uki_frame = 0;
			fish_get.resize(0);
			fish_swim.resize(0);
		}

		if (up_key[KEY_INPUT_R]) {
			timer = 60 * 15;
			fished_count = (std::uint_fast32_t)fish_get.size();
			++go_fish_count;

			for (std::size_t i{}; i < fish_num; ++i) {
				fish_count[i] = 0;
			}

			item_count[item_fish_small] = fish_count[fish_small];
			item_count[item_fish_medium] = fish_count[fish_medium];
			item_count[item_fish_large] = fish_count[fish_large];
			item_count[item_fish_sunfish] = fish_count[fish_sunfish];
			item_count[item_fish_whale_shark] = fish_count[fish_whale_shark];
			item_count[item_fish_regalecus_glesne] = fish_count[fish_regalecus_glesne];

			cloud_move_time = 0;
			cloud_x = 0;
			fisher_timer = 0;
			fish_scene_start_timer = 100 * 4;
			fish_scene = fish_scene_start;
			total_score = 0;
			uki_frame = 0;
			fish_get.resize(0);
			fish_swim.resize(0);
		}
	}

private:

	std::uint_fast8_t uki_frame{};

	int shake_count{};
	int timer{ 60 * 15 };

	const int cloud_move_time_max{ 6 };
	int cloud_move_time{};
	int cloud_x{};

	const int fisher_timer_max{ 30 };
	int fisher_timer{ 0 };

	int uki_x{ 482 };
	int uki_y{ 872 };

	// 泳ぐ範囲
	const int range_x{ 0 };
	const int range_y{ 900 };
	const int range_w{ 900 };
	const int range_h{ 1080 };

	int back{ -1 };
	int wave{ -1 };

	int bottle{ -1 };
	int rare{ -1 };
	int super_rare{ -1 };

	int font_timer{ -1 };

	int image_find_fish{ -1 };
	int image_uki{ -1 };
	int image_ocean_sky{ -1 };
	int image_ocean_cloud{ -1 };
	int image_ocean_island{ -1 };
	int image_result{ -1 };

	float shake_value{};

	std::array<int, 6> message_image{ -1 };
	std::array<int, 4> fish_start_image{ -1 };
	std::array<int, fisher_scene_num> fisher_image{ -1 };
	std::array<int, fish_num> fish_image{};
	std::array<int, fish_num> fish_shadow_image{};
	std::array<int, fish_num> fish_30shadow_image{};
	std::array<int, fish_num> result_shadow_image{};

	std::int_fast32_t fish_scene_start_timer{ 100 * 4 };
	std::uint_fast8_t fish_scene{ fish_scene_start };
	std::uint_fast32_t total_score{};

	std::array<std::int_fast32_t, fish_num> fish_count{};

	// デフォルト乱数
	std::random_device seed_gen{};

	// 取った魚
	std::vector<FishStatus> fish_get{};

	// 泳ぐ魚
	std::vector<FishStatus> fish_swim{};

	// 魚の生成確率
	std::uint_fast8_t spawnFish(const std::int_fast32_t fish_count_) const {
		if (fish_count_ < 110) return fish_small;
		if (fish_count_ < 170) return fish_medium;
		if (fish_count_ < 220) return fish_large;
		if (fish_count_ < 248) return fish_sunfish;
		if (fish_count_ < 252) return fish_whale_shark;
		return fish_regalecus_glesne;
	}

	std::uint_fast8_t scoreFish(const std::int_fast32_t fish_count_) const {
		if (fish_count_ <= 0) return 0;
		if (fish_count_ < 80) return 1;
		if (fish_count_ < 180) return 2;
		if (fish_count_ < 220) return 3;
		if (fish_count_ < 300) return 4;
		return 5;
	}

};