#pragma once
#include <DxLib.h>
#include <cstddef>
#include <cstdint>
#include <fstream>
//#include <iostream>
//#include <string>
#include "Item.hpp"
#include "Title.hpp"
#include "Map.hpp"
#include "Fish.hpp"
#include "Material.hpp"

// 画面遷移
enum :std::uint_fast8_t {

	// 空
	scene_empty,

	// タイトル画面
	scene_title,

	// マップ画面
	scene_map,

	// 釣り画面
	scene_fish,

	// 素材あつめ画面
	scene_material,

	// 閉じる画面
	scene_close,

	scene_title_init

};

// メインフレームの管理クラス
class MainFrame {
public:

	// 初期化処理
	bool init(const int load_font) {
		this->ReadFile();
		::DxLib::ProcessMessage();
		title.init(bgm, map_image, s0, s1, s2, y0, y1, y2, t0, t1, t2, c0, c1, c2, st0, st1, st2, f0, f1, f2, f3, hiroba_image);
		::DxLib::DrawStringToHandle(title_frame_x, title_frame_y, u8"\n■■■■□", 0xffffffff, load_font);
		::DxLib::ProcessMessage();
		map.init(bgm, map_image, s0, s1, s2, y0, y1, y2, t0, t1, t2, c0, c1, c2, st0, st1, st2, f0, f1, f2, f3, hiroba_image);
		::DxLib::DrawStringToHandle(title_frame_x, title_frame_y, u8"\n■■■■■", 0xffffffff, load_font);
		::DxLib::ProcessMessage();
		//
		// 描画先グラフィック領域の指定
		::DxLib::SetDrawScreen(DX_SCREEN_BACK);
		return true;
	}

	// 画面ループ
	bool loop() {

		this->updateKey();

		switch (scene_id) {

			// タイトル画面
		case scene_title:
			title.call(up_key, scene_id, yorozuya_level, sakanaya_level, farm_level, hiroba_level);
#ifdef GENKAI_SYURAKU_TOUCH
			::DxLib::DrawGraph(0, button2_frame_y, button2, TRUE);
			::DxLib::DrawGraph(button1_frame_x, button1_frame_y, button1, TRUE);
#endif
			break;

			// マップ画面
		case scene_map:
			map.call(item_count, up_key, key_frame, scene_id, fished_count, go_fish_count, material_count, go_material_count,
				yorozuya_level, sakanaya_level, farm_level, hiroba_level, hatake_level, talk_id);
#ifdef GENKAI_SYURAKU_TOUCH
			if (talk_id == 0) ::DxLib::DrawGraph(0, button2_frame_y, button2, TRUE);
			::DxLib::DrawGraph(button1_frame_x, button1_frame_y, button1, TRUE);
#endif
			break;

			// 釣り画面
		case scene_fish:
			fish.call(item_count, up_key, down_key, key_frame, scene_id, fished_count, go_fish_count);
#ifdef GENKAI_SYURAKU_TOUCH
			::DxLib::DrawGraph(button1_frame_x, button1_frame_y, button1, TRUE);
#endif
			break;

			// 素材あつめ画面
		case scene_material:
			material.call(item_count, up_key, down_key, key_frame, scene_id, material_count, go_material_count, is_select, select_x, select_y);
#ifdef GENKAI_SYURAKU_TOUCH
			::DxLib::DrawGraph(button1_frame_x, button1_frame_y, button1, TRUE);
#endif
			break;

			// 閉じる画面
		case scene_close:
			return false;

		case scene_title_init:
			yorozuya_level = 0;
			sakanaya_level = 1;
			farm_level = 0;
			hiroba_level = 0;
			hatake_level = 0;

			fished_count = 0;
			go_fish_count = 0;
			material_count = 0;
			go_material_count = 0;

			for (std::size_t i{}; i < item_count.size(); ++i)
				item_count[i] = 200;

			scene_id = scene_map;
			return true;
		}
		return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1 && key_frame[KEY_INPUT_ESCAPE] == 0);
	}

	// キーが押されているフレーム数を格納する
	std::int_fast32_t key_frame[256]{};
	bool up_key[256]{};
	bool down_key[256]{};

	// キーの入力状態を更新する
	void updateKey() {
		// 現在のキーの入力状態を格納する
		char tmp_key[256]{};
		// 全てのキーの入力状態を得る
		DxLib::GetHitKeyStateAll(tmp_key);

#ifdef GENKAI_SYURAKU_TOUCH
		is_select = false;
		int pos_x{}, pos_y{};
		const std::size_t num{ static_cast<std::size_t>(GetTouchInputNum()) };
		for (std::size_t i{}; i < num; ++i) {
			// タッチされている箇所の座標を取得
			GetTouchInput(static_cast<int>(i), &pos_x, &pos_y, nullptr, nullptr);
			if (pos_x >= 161 / frame_size && pos_y >= 221 / frame_size && pos_x < (161 + 128 * 6) / frame_size && pos_y < (221 + 128 * 6) / frame_size) {
				is_select = true;
				select_x = (pos_x - 161 / frame_size) / (128 / frame_size);
				select_y = (pos_y - 221 / frame_size) / (128 / frame_size);
			}

			if (scene_id != scene_material)
				if (pos_x >= 176 / frame_size && pos_y >= 584 / frame_size && pos_x < 336 / frame_size && pos_y < 744 / frame_size) tmp_key[KEY_INPUT_UP] = 1;
				else if (pos_x >= 16 / frame_size && pos_y >= 584 / frame_size && pos_x < 176 / frame_size && pos_y < 744 / frame_size) {
					tmp_key[KEY_INPUT_UP] = 1;
					tmp_key[KEY_INPUT_LEFT] = 1;
				}
				else if (pos_x >= 336 / frame_size && pos_y >= 584 / frame_size && pos_x < 496 / frame_size && pos_y < 744 / frame_size) {
					tmp_key[KEY_INPUT_UP] = 1;
					tmp_key[KEY_INPUT_RIGHT] = 1;
				}
				else if (pos_x >= 176 / frame_size && pos_y >= 904 / frame_size && pos_x < 336 / frame_size && pos_y < 1024 / frame_size) tmp_key[KEY_INPUT_DOWN] = 1;
				else if (pos_x >= 16 / frame_size && pos_y >= 904 / frame_size && pos_x < 176 / frame_size && pos_y < 1024 / frame_size) {
					tmp_key[KEY_INPUT_DOWN] = 1;
					tmp_key[KEY_INPUT_LEFT] = 1;
				}
				else if (pos_x >= 336 / frame_size && pos_y >= 904 / frame_size && pos_x < 496 / frame_size && pos_y < 1024 / frame_size) {
					tmp_key[KEY_INPUT_DOWN] = 1;
					tmp_key[KEY_INPUT_RIGHT] = 1;
				}
				else if (pos_x >= 16 / frame_size && pos_y >= 744 / frame_size && pos_x < 176 / frame_size && pos_y < 904 / frame_size) tmp_key[KEY_INPUT_LEFT] = 1;
				else if (pos_x >= 336 / frame_size && pos_y >= 744 / frame_size && pos_x < 496 / frame_size && pos_y < 904 / frame_size) tmp_key[KEY_INPUT_RIGHT] = 1;

			if (pos_x >= 1584 / frame_size && pos_y >= 584 / frame_size && pos_x < 1744 / frame_size && pos_y < 744 / frame_size) {
				tmp_key[KEY_INPUT_R] = 1;
				tmp_key[KEY_INPUT_E] = 1;
			}
			else if (pos_x >= 1584 / frame_size && pos_y >= 904 / frame_size && pos_x < 1744 / frame_size && pos_y < 1024 / frame_size) {
				tmp_key[KEY_INPUT_T] = 1;
				//tmp_key[KEY_INPUT_LEFT] = 1;
			}
			else if (pos_x >= 1424 / frame_size && pos_y >= 744 / frame_size && pos_x < 1584 / frame_size && pos_y < 904 / frame_size) {
				tmp_key[KEY_INPUT_LSHIFT] = 1;
				//tmp_key[KEY_INPUT_LEFT] = 1;
			}
			else if (pos_x >= 1744 / frame_size && pos_y >= 744 / frame_size && pos_x < 1904 / frame_size && pos_y < 904 / frame_size) {
				tmp_key[KEY_INPUT_RETURN] = 1;
				tmp_key[KEY_INPUT_SPACE] = 1;
			}
		}
#endif

		for (std::size_t i{}; i < 256; ++i) {
			// 押されたらtrue
			down_key[i] = (tmp_key[i] != 0 && key_frame[i] == 0);
			// 離されたらtrue
			up_key[i] = (tmp_key[i] == 0 && key_frame[i] != 0);

			// i番のキーコードに対応するキーが押されていたら加算
			if (tmp_key[i] != 0) ++key_frame[i];
			// 押されていなければ0にする
			else key_frame[i] = 0;


		}
	}

	// 終了時処理
	void end() {
		this->WriteFile();
		DxLib::DxLib_End();
	}

private:
	Fish fish{};
	Material material{};
	std::array<int, item_num> item_count{ {} };
#ifdef GENKAI_SYURAKU_TOUCH
	const int button1{ ::DxLib::LoadGraph(u8"image/button1.png") };
	const int button2{ ::DxLib::LoadGraph(u8"image/button2.png") };
#endif
	int talk_id{};
	bool is_select{};
	int select_x{};
	int select_y{};

	const int bgm{ ::DxLib::LoadSoundMem("music/genkaivillage.ogg") };
	const int map_image{ ::DxLib::LoadGraph("image/map.jpg", FALSE) };

	const int s0{ ::DxLib::LoadGraph("image/sakanaya1.png", TRUE) };
	const int s1{ ::DxLib::LoadGraph("image/sakanaya2.png", TRUE) };
	const int s2{ ::DxLib::LoadGraph("image/sakanaya3.png", TRUE) };
	const int y0{ ::DxLib::LoadGraph("image/yorozuya1.png", TRUE) };
	const int y1{ ::DxLib::LoadGraph("image/yorozuya2.png", TRUE) };
	const int y2{ ::DxLib::LoadGraph("image/yorozuya3.png", TRUE) };
	const int t0{ ::DxLib::LoadGraph("image/tower1.png", TRUE) };
	const int t1{ ::DxLib::LoadGraph("image/tower2.png", TRUE) };
	const int t2{ ::DxLib::LoadGraph("image/tower3.jpg", FALSE) };
	const int c0{ ::DxLib::LoadGraph("image/castle1.png", TRUE) };
	const int c1{ ::DxLib::LoadGraph("image/castle2.png", TRUE) };
	const int c2{ ::DxLib::LoadGraph("image/castle3.jpg", FALSE) };
	const int st0{ ::DxLib::LoadGraph("image/statue1.png", TRUE) };
	const int st1{ ::DxLib::LoadGraph("image/statue2.png", TRUE) };
	const int st2{ ::DxLib::LoadGraph("image/statue3.jpg", FALSE) };
	const int f0{ ::DxLib::LoadGraph("image/farm1.png", TRUE) };
	const int f1{ ::DxLib::LoadGraph("image/farm2.png", TRUE) };
	const int f2{ ::DxLib::LoadGraph("image/farm3.png", TRUE) };
	const int f3{ ::DxLib::LoadGraph("image/farm4.jpg", FALSE) };
	const int hiroba_image{ ::DxLib::LoadGraph("image/hiroba.png", TRUE) };

	void parse32(char str[], std::size_t num, std::uint_fast32_t item_) const {
		str[num + 3] = static_cast<char>(static_cast<unsigned char>(item_ & 255));
		item_ >>= 8;
		str[num + 2] = static_cast<char>(static_cast<unsigned char>(item_ & 255));
		item_ >>= 8;
		str[num + 1] = static_cast<char>(static_cast<unsigned char>(item_ & 255));
		item_ >>= 8;
		str[num] = static_cast<char>(static_cast<unsigned char>(item_ & 255));
	}

	std::uint_fast32_t compose(const char* str, std::size_t num) const {
		std::uint_fast32_t item_{};
		item_ = static_cast<std::uint_fast32_t>(static_cast<unsigned char>(str[num]));
		item_ <<= 8;
		item_ += static_cast<std::uint_fast32_t>(static_cast<unsigned char>(str[num + 1]));
		item_ <<= 8;
		item_ += static_cast<std::uint_fast32_t>(static_cast<unsigned char>(str[num + 2]));
		item_ <<= 8;
		item_ += static_cast<std::uint_fast32_t>(static_cast<unsigned char>(str[num + 3]));
		return item_;
	}

	bool WriteFile() const {
#ifdef __ANDROID__
		char file_path[256]{};
		::DxLib::GetInternalDataPath(file_path, sizeof(file_path));
		//std::ofstream ofs(std::string(std::string(file_path) + u8"/save.txt").c_str(), std::ios::binary);

		FILE* ofs;
		ofs = fopen(std::string(std::string(file_path) + u8"/save.txt").c_str(), "wb");
		if (ofs == nullptr) return false;

#else
		//FILE* ofs;
		//ofs = fopen(u8"save/save.txt", "wb");
		//if (ofs == nullptr) return false;
		std::ofstream ofs(u8"save/save.txt", std::ios::binary);
		if (ofs.fail()) return false;
#endif
		char str[256]{};

		// 0-4
		str[0] = static_cast<char>(static_cast<unsigned char>(yorozuya_level));
		str[1] = static_cast<char>(static_cast<unsigned char>(sakanaya_level));
		str[2] = static_cast<char>(static_cast<unsigned char>(farm_level));
		str[3] = static_cast<char>(static_cast<unsigned char>(hiroba_level));
		str[4] = static_cast<char>(static_cast<unsigned char>(hatake_level));

		// 12-15
		parse32(str, 12, fished_count);
		// 16
		parse32(str, 16, go_fish_count);
		// 20
		parse32(str, 20, material_count);
		// 24
		parse32(str, 24, go_material_count);

		// 60
		for (std::size_t i{}; i < item_count.size(); ++i)
			parse32(str, 60 + i * 4, static_cast<std::uint_fast32_t>(item_count[i]));

#ifdef __ANDROID__
		for (std::size_t i{}; i < 256; ++i)
			fprintf(ofs, "%c", str[i]);
		fclose(ofs);
#else
		ofs.write(str, 256);
#endif
		return true;
	}

	bool ReadFile() {
#ifdef __ANDROID__
		char file_path[256]{};
		::DxLib::GetInternalDataPath(file_path, sizeof(file_path));
		//std::ifstream ifs(std::string(std::string(file_path) + u8"/save.txt").c_str());
		char str[256]{};

		FILE* fp;
		if ((fp = fopen(std::string(std::string(file_path) + u8"/save.txt").c_str(), "rb")) == nullptr) return false;
		fread(str, sizeof(char), 256, fp);
		fclose(fp);

#else
		//char str[256]{};
		//FILE* fp;
		//if ((fp = fopen(u8"save/save.txt", "rb")) == nullptr) return false;
		//fread(str, sizeof(char), 256, fp);
		//fclose(fp);
		std::ifstream ifs(u8"save/save.txt");
		if (ifs.fail()) return false;
		std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
		if (str.size() < 256) return false;
#endif
		if (str[1] == 0) str[1] = 1;

#ifdef __ANDROID__
		// 0-4
		yorozuya_level = static_cast<std::uint_fast8_t>(static_cast<unsigned char>(str[0]));
		sakanaya_level = static_cast<std::uint_fast8_t>(static_cast<unsigned char>(str[1]));
		farm_level = static_cast<std::uint_fast8_t>(static_cast<unsigned char>(str[2]));
		hiroba_level = static_cast<std::uint_fast8_t>(static_cast<unsigned char>(str[3]));
		hatake_level = static_cast<std::uint_fast8_t>(static_cast<unsigned char>(str[4]));

		// 12
		fished_count = compose(str, 12);
		go_fish_count = compose(str, 16);
		material_count = compose(str, 20);
		go_material_count = compose(str, 24);

		// 60
		for (std::size_t i{}; i < item_count.size(); ++i)
			item_count[i] = static_cast<int>(compose(str, 60 + i * 4));
#else
		// 12
		fished_count = compose(str.c_str(), 12);
		go_fish_count = compose(str.c_str(), 16);
		material_count = compose(str.c_str(), 20);
		go_material_count = compose(str.c_str(), 24);

		// 60
		for (std::size_t i{}; i < item_count.size(); ++i)
			item_count[i] = static_cast<int>(compose(str.c_str(), 60 + i * 4));
#endif
		return true;
	}

private:
	Map map;
	Title title;

	//集落レベル
	std::uint_fast8_t yorozuya_level = 0;
	std::uint_fast8_t sakanaya_level = 1;
	std::uint_fast8_t farm_level = 0;
	std::uint_fast8_t hiroba_level = 0; //tower=2,3,4 castle=5,6,7 statue=8,9,10
	std::uint_fast8_t hatake_level = 0;

	std::uint_fast32_t fished_count{};
	std::uint_fast32_t go_fish_count{};
	std::uint_fast32_t material_count{};
	std::uint_fast32_t go_material_count{};

	// 画面遷移のタイプ
	std::uint_fast8_t scene_id{ scene_title };


};