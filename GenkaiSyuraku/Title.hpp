#pragma once
#include <DxLib.h>

class Title {
public:
	void init() {
		title_backimage[0] = LoadGraph("image/map1.png", TRUE);
		title_backimage[1] = LoadGraph("image/map4.png", TRUE);
		//title_backimage[2] = LoadGraph("image/map3.png", TRUE);
		title_image[0] = LoadGraph("image/title1.png", TRUE);
		title_image[1] = LoadGraph("image/title2.png", TRUE);
		start_image[0] = LoadGraph("image/start.png", TRUE);
		start_image[1] = LoadGraph("image/start2.png", TRUE);
		continue_image[0] = LoadGraph("image/continue.png", TRUE);
		continue_image[1] = LoadGraph("image/continue2.png", TRUE);
		end_image[0] = LoadGraph("image/end.png", TRUE);
		end_image[1] = LoadGraph("image/end2.png", TRUE);
		bgm = LoadSoundMem("music/genkaivillage.wav");
	}

	void start(bool down_key[], std::uint_fast8_t& scene_id) {
		if (ret == 0) background_x--;
		else background_x++;
		if (background_x == -1920) ret = 1;
		else if (background_x == 0) ret = 0;

		//メニュー選択
		if (down_key[KEY_INPUT_UP] > 0) select--;
		else if (down_key[KEY_INPUT_DOWN] > 0) select++;
		if (select > 2) select = 0;
		if (select < 0) select = 2;

		//メニュー決定
		if (down_key[KEY_INPUT_RETURN] > 0) {
			StopSoundMem(bgm);
			if (select == 0) scene_id = 2;
			if (select == 1) scene_id = 2;
			if (select == 2) scene_id = 4;
		}
		//背景
		DrawGraph(background_x, 0, title_backimage[map_level], TRUE);
		//タイトル
		DrawGraph(0, -200, title_image[map_level], TRUE);
			   		 
		//その他表示
		DrawGraph(0, 0, start_image[0], TRUE);
		DrawGraph(0, 0, continue_image[0], TRUE);
		DrawGraph(0, 0, end_image[0], TRUE);

		//選択
		if(select == 0)	DrawGraph(0, 0, start_image[1], TRUE);
		else if (select == 1) DrawGraph(0, 0, continue_image[1], TRUE);
		else DrawGraph(0, 0, end_image[1], TRUE);
			
		if (bgm_flag == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_BACK);//バックグラウンド再生
			bgm_flag = 1;
		}

	}

private:
	int background_x = 0, ret = 0;
	int select = 0;
	int map_level = 0;
	int bgm, bgm_flag = 0;
	int title_backimage[3];
	int title_image[2];
	int start_image[2];
	int continue_image[2];
	int end_image[2];

};