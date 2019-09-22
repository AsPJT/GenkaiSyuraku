#pragma once
#include <DxLib.h>
#include <cstddef>
#include <cstdint>
#include "Map.hpp"

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

	// 閉じる画面
	scene_close

};

// メインフレームの管理クラス
class MainFrame {
public:

	// 初期化処理
	bool init() {

		// ログ出力を行わない
		DxLib::SetOutApplicationLogValidFlag(FALSE);

		// ウインドウモードにする
		DxLib::ChangeWindowMode(TRUE);

		// 画面の解像度を指定する
		DxLib::SetGraphMode(1920, 1080, 32);

		// ウインドウのタイトルを変更する
		DxLib::SetMainWindowText("GenkaiSyuraku");

		// ライブラリの初期化
		if (DxLib::DxLib_Init() == -1) return false;
		
		// 描画先グラフィック領域の指定
		DxLib::SetDrawScreen(DX_SCREEN_BACK);

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

			break;

		// マップ画面
		case scene_map:
			map.control(key_frame, scene_id);
			break;

		// 釣り画面
		case scene_fish:

			break;

		// 閉じる画面
		case scene_close:
			return false;
		}
		for (std::size_t i{}; i < 256; ++i) {
			//if(down_key[i]) printfDx("down:true\n");
			//if (up_key[i]) printfDx("up:true\n");
			//if (key_frame[i]) printfDx("%d", key_frame[i]);
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
	Map map;

	// 画面遷移のタイプ
	std::uint_fast8_t scene_id{ scene_map };


};