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
			title.call(up_key, scene_id, yorozuya_level, fish_shop_level, farm_level, square_level, field_level);
			break;

		// マップ画面
		case scene_map:
			map.call(item_count, up_key, key_frame, scene_id, fished_count, go_fish_count, material_count, go_material_count, 
				yorozuya_level, fish_shop_level, farm_level, square_level, field_level);
			break;

		// 釣り画面
		case scene_fish:
			fish.call(item_count, up_key, down_key, scene_id, fished_count, go_fish_count);
			break;

		// 素材あつめ画面
		case scene_material:
			material.call(item_count, up_key, down_key, key_frame, scene_id, material_count, go_material_count);
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

private:
	Map map;
	Title title;

	//集落レベル
	std::uint_fast32_t yorozuya_level = 0;
	std::uint_fast32_t fish_shop_level = 1;
	std::uint_fast32_t farm_level = 1;
	std::uint_fast32_t square_level = 0; //tower=2,3,4 castle=5,6,7 statue=8,9,10 big_farm=11
	std::uint_fast32_t field_level = 0;

	std::uint_fast32_t fished_count{};
	std::uint_fast32_t go_fish_count{};
	std::uint_fast32_t material_count{};
	std::uint_fast32_t go_material_count{};

	// 画面遷移のタイプ
	std::uint_fast8_t scene_id{ scene_title };


};