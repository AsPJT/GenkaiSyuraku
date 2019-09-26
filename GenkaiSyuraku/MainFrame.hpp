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
	bool init() {
		title.init();
		map.init();
		return true;
	}

	// 画面ループ
	bool loop() {

		this->updateKey();

		switch (scene_id) {

		// 空
		case scene_empty:

			break;

		// タイトル画面
		case scene_title:
			title.call(up_key, scene_id, yorozuya_level, sakanaya_level, farm_level);
#ifdef GENKAI_SYURAKU_TOUCH
			::DxLib::DrawGraph(1408, 568, button1, TRUE);
#endif
			break;

		// マップ画面
		case scene_map:
			map.call(item_count, up_key, key_frame, scene_id, fished_count, go_fish_count, material_count, go_material_count, yorozuya_level, sakanaya_level, farm_level);
#ifdef GENKAI_SYURAKU_TOUCH
			::DxLib::DrawGraph(0, 568, button2, TRUE);
			::DxLib::DrawGraph(1408, 568, button1, TRUE);
#endif
			break;

		// 釣り画面
		case scene_fish:
			fish.call(item_count, up_key, down_key, scene_id, fished_count, go_fish_count);
#ifdef GENKAI_SYURAKU_TOUCH
			::DxLib::DrawGraph(1408, 568, button1, TRUE);
#endif
			break;

		// 素材あつめ画面
		case scene_material:
			material.call(item_count, up_key, down_key, key_frame, scene_id, material_count, go_material_count);
#ifdef GENKAI_SYURAKU_TOUCH
			::DxLib::DrawGraph(0, 568, button2, TRUE);
			::DxLib::DrawGraph(1408, 568, button1, TRUE);
#endif
			break;

		// 閉じる画面
		case scene_close:
			return false;
		}
		return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1);
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
		int pos_x{}, pos_y{};
		const std::size_t num{ static_cast<std::size_t>(GetTouchInputNum()) };
		for (std::size_t i{}; i < num; ++i) {
			// タッチされている箇所の座標を取得
			GetTouchInput(static_cast<int>(i), &pos_x, &pos_y, nullptr, nullptr);
			if (pos_x>=176 && pos_y>=584 && pos_x < 336 && pos_y < 744) {
				tmp_key[KEY_INPUT_UP] = 1;
			}
			else if (pos_x >= 176 && pos_y >= 904 && pos_x < 336 && pos_y < 1024) {
				tmp_key[KEY_INPUT_DOWN] = 1;
			}
			else if (pos_x >= 16 && pos_y >= 744 && pos_x < 176 && pos_y < 904) {
				tmp_key[KEY_INPUT_LEFT] = 1;
			}
			else if (pos_x >= 336 && pos_y >= 744 && pos_x < 496 && pos_y < 904) {
				tmp_key[KEY_INPUT_RIGHT] = 1;
			}
			else if (pos_x >= 1584 && pos_y >= 584 && pos_x < 1744 && pos_y < 744) {
				tmp_key[KEY_INPUT_T] = 1;
				tmp_key[KEY_INPUT_E] = 1;
			}
			else if (pos_x >= 1584 && pos_y >= 904 && pos_x < 1744 && pos_y < 1024) {
				tmp_key[KEY_INPUT_R] = 1;
				tmp_key[KEY_INPUT_LEFT] = 1;
			}
			else if (pos_x >= 1424 && pos_y >= 744 && pos_x < 1584 && pos_y < 904) {
				tmp_key[KEY_INPUT_R] = 1;
				tmp_key[KEY_INPUT_LEFT] = 1;
			}
			else if (pos_x >= 1744 && pos_y >= 744 && pos_x < 1904 && pos_y < 904) {
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
	int button1{ ::DxLib::LoadGraph(u8"image/button1.png") };
	int button2{ ::DxLib::LoadGraph(u8"image/button2.png") };
#endif

private:
	Map map;
	Title title;

	//集落レベル
	int yorozuya_level = 0;
	int sakanaya_level = 1;
	int farm_level = 1;

	std::uint_fast32_t fished_count{};
	std::uint_fast32_t go_fish_count{};
	std::uint_fast32_t material_count{};
	std::uint_fast32_t go_material_count{};

	// 画面遷移のタイプ
	std::uint_fast8_t scene_id{ scene_title };


};