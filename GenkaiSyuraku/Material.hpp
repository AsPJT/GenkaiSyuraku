#pragma once
#include <array>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <random>
#include <string>
#include "Item.hpp"

// 釣りの状態
enum : ::std::uint_fast8_t {
	material_scene_empty,
	material_scene_start,
	material_scene_material,
	material_scene_end,
};

// 素材の状態
enum : ::std::uint_fast8_t {
	material_status_empty,
	material_status_swim,
	material_status_get,
	material_status_up_fly,
	material_status_down_fly,
	material_status_stay
};

enum : ::std::uint_fast8_t {
	materialer_scene_empty,
	materialer_scene_hit,
	materialer_scene_go,
	materialer_scene_num
};

enum : ::std::uint_fast8_t {
	// お金
	material_money,
	// 中素材
	material_stone,
	// 大素材
	material_wood,
	// マンボウ
	material_gold,
	// ジンベイザメ
	material_timer,
	// リュウグウノツカイ
	material_straw,
	// 素材の種類
	material_num
};

// 素材の大きさ
constexpr ::std::array<::std::uint_fast8_t, material_num + 1> material_size{ { material_money,material_stone,material_wood,material_stone,material_wood,material_wood,material_money } };

// 素材の浮き待機フレーム
constexpr ::std::array<::std::uint_fast8_t, material_num + 1> material_frame{ { 120,120,200,60,60,200,1 } };
constexpr ::std::array<::std::uint_fast8_t, material_num + 1> material_start_frame{ { 8,8,8,8,8,8,1 } };
constexpr ::std::array<::std::uint_fast8_t, material_num + 1> material_half_frame{ { 80,80,180,80,80,180,1 } };

// 素材別のスコア
constexpr ::std::array<::std::uint_fast32_t, material_num + 1> material_score{ { 1,3,8,50,35,12,1 } };

// 素材のデフォルトサイズ
constexpr ::std::array<float, material_num + 1> material_gram{ { 50,80,120,150,300,300,1 } };

class Material {
private:

	bool first_frame{ true };

	::std::uint_fast8_t uki_frame{};

	int timer_count{};
	int timer{ 60 * 15 };

	int width{ 1 };
	int height{ 1 };
	int select_x{};
	int select_y{};

	int field_x{ 160 };
	int field_y{ 220 };

	const int materialer_timer_max{ 30 };
	int materialer_timer{};

	const int time_plus_timer_max{ 40 };
	int time_plus_timer{};

	const int font_timer{ CreateFontToHandle(nullptr, 100 / frame_size, 0, DX_FONTTYPE_NORMAL) };

	const int image_hand{ ::DxLib::LoadGraph("image/hand.png") };
	const int image_broom{ ::DxLib::LoadGraph("image/broom.png") };
	const int up_time{ ::DxLib::LoadGraph("image/up_time.png") };
	const int bottle{ ::DxLib::LoadGraph("image/bottle.png") };
	const int image_materialer_hand{ ::DxLib::LoadGraph("image/materialer_hand.png") };
	const int image_select_range{ ::DxLib::LoadGraph("image/select_range.png") };
	const int image_find_material{ ::DxLib::LoadGraph("image/find_fish.png") };
	const int image_ocean_sky{ ::DxLib::LoadGraph("image/material_map.jpg") };
	const int image_result{ ::DxLib::LoadGraph("image/result3.png") };

	::std::array<int, 6> message_image{ -1 };
	::std::array<int, 4> material_start_image{ -1 };
	::std::array<int, materialer_scene_num> materialer_image{ -1 };
	::std::array<int, materialer_scene_num> broomer_image{ -1 };
	::std::array<int, material_num> material_image{};
	::std::array<int, material_num> material_30shadow_image{};

	::std::array<::std::array<::std::uint_fast8_t, 6>, 6> field{};

	::std::int_fast32_t material_scene_start_timer{ 100 * 4 };
	::std::uint_fast8_t material_scene{ material_scene_start };
	::std::uint_fast32_t total_score{};

	::std::array<::std::int_fast32_t, material_num> material_count{};

	// デフォルト乱数
	::std::random_device seed_gen{};

	// 素材のステータス
	struct MaterialStatus {
		::std::uint_fast8_t material_type{};
		::std::int_fast32_t xx{};
		::std::int_fast32_t yy{};
		::std::int_fast32_t window_x{};
		::std::int_fast32_t window_y{};
		double r{};
		double add_r{};
		bool can_fly{ true };
		::std::uint_fast8_t status{ material_status_swim };
		::std::int_fast32_t frame{};
		::std::int_fast32_t start_frame{};

		MaterialStatus() = default;
		MaterialStatus(const ::std::uint_fast8_t material_type_, const ::std::uint_fast32_t x_, const ::std::uint_fast32_t y_, const ::std::uint_fast32_t window_x_, const ::std::uint_fast32_t window_y_)
			:material_type(material_type_), xx(x_), yy(y_), window_x(window_x_), window_y(window_y_) {}
	};

	// 取った素材
	::std::vector<MaterialStatus> material_get{};

	// 泳ぐ素材
	::std::vector<MaterialStatus> material_swim{};

	// 素材の生成確率
	constexpr ::std::uint_fast8_t spawnMaterial(const ::std::int_fast32_t material_count_) const noexcept {
		if (material_count_ < 83) return material_money;
		if (material_count_ < 166) return material_stone;
		if (material_count_ < 207) return material_wood;
		if (material_count_ < 248) return material_straw;
		if (material_count_ < 252) return material_timer;
		return material_gold;
	}

	constexpr ::std::uint_fast8_t scoreMaterial(const ::std::int_fast32_t fish_count_) const noexcept {
		if (fish_count_ <= 0) return 0;
		if (fish_count_ < 80) return 1;
		if (fish_count_ < 150) return 2;
		if (fish_count_ < 200) return 3;
		if (fish_count_ < 300) return 4;
		return 5;
	}

public:

	// 素材の生成
	::std::uint_fast8_t addMaterial(const ::std::size_t x_, const ::std::size_t y_) {
		::std::mt19937 engine(seed_gen());
		// 初期の素材の種類
		::std::uniform_int_distribution<> dist_spawn(0, 255);
		material_swim.emplace_back(
			// 素材の種類
			static_cast<::std::uint_fast8_t>(this->spawnMaterial(dist_spawn(engine))),
			(int)x_,
			(int)y_,
			// X座標
			static_cast<::std::uint_fast32_t>(field_x + (int)x_ * 128 + 64),
			// Y座標
			static_cast<::std::uint_fast32_t>(field_x + (int)y_ * 128 + 124));
		return material_swim.back().material_type;
	}

	Material() {
		first_frame = true;
		char a[2];
		a[1] = 0;

		// 画像格納
		for (::std::size_t i{}; i < 4; ++i) {
			a[0] = static_cast<char>(i + 48);
			material_start_image[i] = ::DxLib::LoadGraph(::std::string("image/material_start" + ::std::string(a) + ".png").c_str());
		}
		::DxLib::ProcessMessage();
		materialer_image[materialer_scene_empty] = ::DxLib::LoadGraph("image/materialer1.png");
		materialer_image[materialer_scene_hit] = ::DxLib::LoadGraph("image/materialer2.png");
		materialer_image[materialer_scene_go] = ::DxLib::LoadGraph("image/materialer3.png");
		broomer_image[materialer_scene_empty] = ::DxLib::LoadGraph("image/broomer1.png");
		broomer_image[materialer_scene_hit] = ::DxLib::LoadGraph("image/broomer2.png");
		broomer_image[materialer_scene_go] = ::DxLib::LoadGraph("image/broomer3.png");
		::DxLib::ProcessMessage();
		for (::std::size_t i{}; i < 6; ++i) {
			a[0] = static_cast<char>(i + 48);
			message_image[i] = ::DxLib::LoadGraph(::std::string("image/fish_message" + ::std::string(a) + ".png").c_str());
		}
		::DxLib::ProcessMessage();
		for (::std::size_t i{}; i < material_image.size(); ++i) {
			a[0] = static_cast<char>(i + 49);
			material_image[i] = ::DxLib::LoadGraph(::std::string("image/material" + ::std::string(a) + ".png").c_str());
			material_30shadow_image[i] = ::DxLib::LoadGraph(::std::string("image/material_30shadow" + ::std::string(a) + ".png").c_str());
		}
		::DxLib::ProcessMessage();
		for (::std::size_t i{}; i < field.size(); ++i)
			for (::std::size_t j{}; j < field[i].size(); ++j)
				field[i][j] = material_num;
	}

	void call(::std::array<int, item_num>& item_count, bool up_key[], bool down_key[], ::std::int_fast32_t key_frame[], ::std::uint_fast8_t& scene_id, ::std::uint_fast32_t& materialed_count, ::std::uint_fast32_t& go_material_count, bool is_select_, int select_x_, int select_y_) {
		if (first_frame) {
			if (item_count[item_broom] > 0) {
				--item_count[item_broom];
				width = height = 2;
			}
			else width = height = 1;
		}
		::std::mt19937 engine(seed_gen());

		if (down_key[KEY_INPUT_D]) ++select_x;
		if (down_key[KEY_INPUT_A]) --select_x;
		if (down_key[KEY_INPUT_S]) ++select_y;
		if (down_key[KEY_INPUT_W]) --select_y;
		if (down_key[KEY_INPUT_RIGHT]) ++select_x;
		if (down_key[KEY_INPUT_LEFT]) --select_x;
		if (down_key[KEY_INPUT_DOWN]) ++select_y;
		if (down_key[KEY_INPUT_UP]) --select_y;
		if (is_select_) {
			select_x = select_x_;
			select_y = select_y_;
		}
		if (select_x - width < -1) select_x = width - 1;
		else if (select_x >= 6) select_x = 5;
		if (select_y - height < -1) select_y = height - 1;
		else if (select_y >= 6) select_y = 5;

		// 背景を描画
		::DxLib::DrawGraph(0, 0, image_ocean_sky, FALSE);

		::std::uniform_int_distribution<::std::size_t> dist(1, 100);
		for (::std::size_t i{}; i < field.size(); ++i)
			for (::std::size_t j{}; j < field[i].size(); ++j)
				if (field[i][j] == material_num && material_scene == material_scene_material && dist(engine) > 92 && material_swim.size() < 10) field[i][j] = this->addMaterial(j, i);

		// 釣った素材を描画
		total_score = 0;
		for (::std::size_t i{}; i < material_get.size(); ++i) {
			total_score += material_score[material_get[i].material_type];
			if (material_get[i].status == material_status_down_fly) {
				material_get[i].window_y += 20;
				material_get[i].r += material_get[i].add_r;
				if (material_get[i].window_y > 850 - static_cast<::std::int_fast32_t>(material_get.size() * 10)) material_get[i].status = material_status_stay;
			}
			::DxLib::DrawRotaGraph((int)material_get[i].window_x / frame_size, (int)material_get[i].window_y / frame_size, 1.0f, material_get[i].r, material_image[material_get[i].material_type], TRUE);
		}
		bool is_hit{ false };
		bool is_materialer{ false };
		// 泳ぐ素材の制御

		if (material_scene == material_scene_material)
			for (::std::size_t i{}; i < material_swim.size(); ++i) {
				++material_swim[i].start_frame;
				++material_swim[i].frame;
			}

		if (material_scene == material_scene_material)
			for (int select_all_y{ select_y - height + 1 }; select_all_y <= select_y; ++select_all_y)
				for (int select_all_x{ select_x - width + 1 }; select_all_x <= select_x; ++select_all_x)
					for (::std::size_t i{}; i < material_swim.size(); ++i) {
						if (material_swim[i].frame >= material_frame[material_swim[i].material_type]) {
							field[material_swim[i].yy][material_swim[i].xx] = material_num;
							material_swim.erase(material_swim.begin() + i);
							--i;
							continue;
						}
						if (i >= material_swim.size()) break;
						if (material_swim[i].xx == select_all_x && material_swim[i].yy == select_all_y) {
							is_hit = true;
							::std::uniform_real_distribution<double> dist_r(0.01, 0.2);
							::DxLib::DrawGraph(1500 / frame_size, 200 / frame_size, image_find_material, TRUE);

							if ((down_key[KEY_INPUT_SPACE] || is_select_) && timer > 0 && materialer_timer == 0) {
								is_materialer = true;
								const bool is_timer{ material_swim[i].material_type == material_timer };
								if (!is_timer) {
									material_get.emplace_back(material_swim[i]);
									material_get.back().status = material_status_up_fly;
									material_get.back().add_r = dist_r(engine);
								}
								else {
									++timer_count;
									timer += 180;
									time_plus_timer = 100;
								}
								field[material_swim[i].yy][material_swim[i].xx] = material_num;
								material_swim.erase(material_swim.begin() + i);

								if (!is_timer) {
									++material_count[material_get.back().material_type];
								}

								--i;
								continue;
							}

						}
					}
		if (is_materialer) materialer_timer = 30;

		::std::uint_fast8_t materialer_status{ materialer_scene_empty };
		if (is_hit) materialer_status = materialer_scene_hit;
		if (materialer_timer > 0) {
			--materialer_timer;
			materialer_status = materialer_scene_go;
		}

		// 海と島
		::DxLib::DrawGraph(1200 / frame_size, 100 / frame_size, (width == 1 && height == 1) ? materialer_image[materialer_status] : broomer_image[materialer_status], TRUE);

		if (field[select_y][select_x] != material_num) ::DxLib::DrawGraph(1350 / frame_size, 800 / frame_size, material_image[field[select_y][select_x]], TRUE);

		// 泳ぐ素材の制御
		for (::std::size_t i{}; i < material_swim.size(); ++i) {
			if (material_swim[i].start_frame < material_start_frame[material_swim[i].material_type]) {
				::DxLib::DrawRotaGraph((int)material_swim[i].window_x / frame_size, (int)material_swim[i].window_y / frame_size, 1.0f, 0.0, material_30shadow_image[material_swim[i].material_type], TRUE);
			}
			else if (material_swim[i].frame >= material_half_frame[material_swim[i].material_type]) {
				::DxLib::DrawRotaGraph((int)material_swim[i].window_x / frame_size, (int)material_swim[i].window_y / frame_size, 1.0f, 0.0, material_30shadow_image[material_swim[i].material_type], TRUE);
			}
			else ::DxLib::DrawRotaGraph((int)material_swim[i].window_x / frame_size, (int)material_swim[i].window_y / frame_size, 1.0f, 0.0, material_image[material_swim[i].material_type], TRUE);
		}

		// 釣った素材を描画
		for (::std::size_t i{}; i < material_get.size(); ++i) {

			if (material_get[i].status == material_status_up_fly) {
				material_get[i].window_y -= 30;
				material_get[i].r += material_get[i].add_r;
				if (material_get[i].window_y < -500) {
					material_get[i].window_x = 1200;
					material_get[i].window_y = 0;
					material_get[i].status = material_status_down_fly;
				}
				::DxLib::DrawRotaGraph((int)material_get[i].window_x / frame_size, (int)material_get[i].window_y / frame_size, 1.0f, material_get[i].r, material_image[material_get[i].material_type], TRUE);
			}
		}

		if (width == 1 && height == 1) {
			::DxLib::DrawGraph((field_x + (int)select_x * 128) / frame_size, (field_y + (int)select_y * 128) / frame_size, image_select_range, TRUE);
			::DxLib::DrawGraph((field_x + (int)select_x * 128) / frame_size, (field_y + (int)select_y * 128) / frame_size, image_hand, TRUE);
		}
		else for (int i{ select_y - height + 1 }; i <= select_y; ++i) {
			for (int j{ select_x - width + 1 }; j <= select_x; ++j) {
				::DxLib::DrawGraph((field_x + (int)j * 128) / frame_size, (field_y + (int)i * 128) / frame_size, image_select_range, TRUE);
				::DxLib::DrawGraph((field_x + (int)j * 128) / frame_size, (field_y + (int)i * 128) / frame_size, image_broom, TRUE);
			}
		}
		if (width == 1 && height == 1) {
			if (materialer_status == materialer_scene_go && material_get.size() > 0) {
				::DxLib::DrawGraph(1300 / frame_size, 750 / frame_size, material_image[material_get.back().material_type], TRUE);
				::DxLib::DrawGraph(0, 0, image_materialer_hand, TRUE);
			}
		}

		if (material_scene == material_scene_material) {
			::DxLib::DrawBox((field_x + ((select_x + 1) * 128)) / frame_size, (field_y + (select_y * 128)) / frame_size, (field_x + ((select_x + 1) * 128) + 50) / frame_size, (field_y + (select_y * 128) + 100) / frame_size, 0xffffffff, TRUE);
			::DxLib::DrawBox((field_x + ((select_x + 1) * 128)) / frame_size, (field_y + (select_y * 128) + materialer_timer * 100 / 30) / frame_size, (field_x + ((select_x + 1) * 128) + 50) / frame_size, (field_y + (select_y * 128) + 100) / frame_size, 0xff33aa33, TRUE);
			::DxLib::DrawGraph((field_x + ((select_x + 1) * 128) - 40) / frame_size, (field_y + (select_y * 128) - 48) / frame_size, bottle, TRUE);
		}

		if (time_plus_timer > 0) {
			--time_plus_timer;
			if (time_plus_timer >= 80) ::DxLib::DrawGraph((550 + (time_plus_timer - 80) * 100) / frame_size, 500 / frame_size, up_time, TRUE);
			else if (time_plus_timer > 20) ::DxLib::DrawGraph(550 / frame_size, 500 / frame_size, up_time, TRUE);
			else ::DxLib::DrawGraph((550 + (time_plus_timer - 20) * 100) / frame_size, 500 / frame_size, up_time, TRUE);
		}

		switch (material_scene)
		{
		case material_scene_empty:
			break;
		case material_scene_start:
			--material_scene_start_timer;
			if (key_frame[KEY_INPUT_LSHIFT] > 0) --material_scene_start_timer;
			::DxLib::DrawGraph(0, 0, material_start_image[material_scene_start_timer / 100], TRUE);
			if (material_scene_start_timer <= 0) material_scene = material_scene_material;
			break;
		case material_scene_material:
			::DxLib::DrawFormatStringToHandle(0, 0, GetColor(30, 30, 30), font_timer, u8"制限時間：%d.%d", timer / 60, (int)((timer % 60) / 60.0 * 100));
			break;
		case material_scene_end:
			::DxLib::DrawGraph(0, 0, image_result, TRUE);
			::DxLib::DrawFormatStringToHandle(700 / frame_size, 380 / frame_size, GetColor(0, 0, 0), font_timer, u8"%d個", material_count[material_money]);
			::DxLib::DrawFormatStringToHandle(700 / frame_size, 580 / frame_size, GetColor(0, 0, 0), font_timer, u8"%d個", material_count[material_stone]);
			::DxLib::DrawFormatStringToHandle(700 / frame_size, 780 / frame_size, GetColor(0, 0, 0), font_timer, u8"%d個", material_count[material_wood]);
			::DxLib::DrawFormatStringToHandle(1400 / frame_size, 380 / frame_size, GetColor(0, 0, 0), font_timer, u8"%d個", material_count[material_gold]);
			::DxLib::DrawFormatStringToHandle(1400 / frame_size, 580 / frame_size, GetColor(0, 0, 0), font_timer, u8"%d回", timer_count);
			::DxLib::DrawFormatStringToHandle(1400 / frame_size, 780 / frame_size, GetColor(0, 0, 0), font_timer, u8"%d個", material_count[material_straw]);
			::DxLib::DrawGraph(0, 0, message_image[scoreMaterial(total_score)], TRUE);
			break;
		}

		// 強制リザルト画面
		if (up_key[KEY_INPUT_T]) timer = 0;

		// 初期フレームだったら初期フレームを終了
		if (first_frame) first_frame = false;

		if (material_scene == material_scene_material && timer > 0) --timer;
		if (material_scene == material_scene_material && timer > 0 && key_frame[KEY_INPUT_LSHIFT] > 0) --timer;

		if (timer == 0) {
			if (up_key[KEY_INPUT_RETURN]) timer = -100;
			material_scene = material_scene_end;
		}
		if (timer <= -1 || up_key[KEY_INPUT_R]) {
			if (timer <= -1) scene_id = 2; // マップ
			timer = 60 * 15;

			materialed_count = (::std::uint_fast32_t)material_get.size();
			++go_material_count;

			item_count[item_stone] += material_count[material_stone];
			item_count[item_wood] += material_count[material_wood];
			item_count[item_gold] += material_count[material_gold];
			item_count[item_straw] += material_count[material_straw];
			item_count[item_ore] += material_count[material_money];

			for (::std::size_t i{}; i < field.size(); ++i)
				for (::std::size_t j{}; j < field[i].size(); ++j)
					field[i][j] = material_num;
			for (::std::size_t i{}; i < material_num; ++i)
				material_count[i] = 0;

			timer_count = 0;
			width = 1;
			height = 1;
			first_frame = true;
			materialer_timer = 0;
			material_scene_start_timer = 100 * 4;
			material_scene = material_scene_start;
			total_score = 0;
			uki_frame = 0;
			material_get.resize(0);
			material_swim.resize(0);
		}
	}
};