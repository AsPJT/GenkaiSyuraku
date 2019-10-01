#pragma once
#include <DxLib.h>
#include <cstddef>
#include <cstdint>
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
	scene_close

};

// メインフレームの管理クラス
class MainFrame {
public:

	// 初期化処理
	bool init(const int load_font) {
		::DxLib::ProcessMessage();
		title.init(bgm, map_image);
		::DxLib::DrawStringToHandle(title_frame_x, title_frame_y, u8"\n■■■■□", 0xffffffff, load_font);
		::DxLib::ProcessMessage();
		map.init(bgm, map_image);
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
			title.call(up_key, scene_id, yorozuya_level, sakanaya_level, farm_level, hiroba_level, hatake_level);
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
			fish.call(item_count, up_key, down_key, scene_id, fished_count, go_fish_count);
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
				tmp_key[KEY_INPUT_T] = 1;
				tmp_key[KEY_INPUT_E] = 1;
			}
			else if (pos_x >= 1584 / frame_size && pos_y >= 904 / frame_size && pos_x < 1744 / frame_size && pos_y < 1024 / frame_size) {
				tmp_key[KEY_INPUT_R] = 1;
				tmp_key[KEY_INPUT_LEFT] = 1;
			}
			else if (pos_x >= 1424 / frame_size && pos_y >= 744 / frame_size && pos_x < 1584 / frame_size && pos_y < 904 / frame_size) {
				tmp_key[KEY_INPUT_R] = 1;
				tmp_key[KEY_INPUT_LEFT] = 1;
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