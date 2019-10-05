#pragma once
#include <DxLib.h>

class Title {
public:
	void init(const int bgm_, const int map_) {
		map_image = map_;
		sakanaya_image[0] = LoadGraph("image/sakanaya1.png", TRUE);
		sakanaya_image[1] = LoadGraph("image/sakanaya2.png", TRUE);
		sakanaya_image[2] = LoadGraph("image/sakanaya3.png", TRUE);
		yorozuya_image[0] = LoadGraph("image/yorozuya1.png", TRUE);
		yorozuya_image[1] = LoadGraph("image/yorozuya2.png", TRUE);
		yorozuya_image[2] = LoadGraph("image/yorozuya3.png", TRUE);
		farm_image[0] = LoadGraph("image/farm1.png", TRUE);
		farm_image[1] = LoadGraph("image/farm2.png", TRUE);
		farm_image[2] = LoadGraph("image/farm3.png", TRUE);
		farm_image[3] = LoadGraph("image/farm4.png", FALSE);
		::DxLib::ProcessMessage();
		hiroba_image[0] = LoadGraph("image/hiroba.png", TRUE);
		hiroba_image[1] = LoadGraph("image/tower1.png", TRUE);
		hiroba_image[2] = LoadGraph("image/tower2.png", TRUE);
		hiroba_image[3] = LoadGraph("image/tower3.jpg", FALSE);
		hiroba_image[4] = LoadGraph("image/castle1.png", TRUE);
		hiroba_image[5] = LoadGraph("image/castle2.png", TRUE);
		hiroba_image[6] = LoadGraph("image/castle3.jpg", FALSE);
		hiroba_image[7] = LoadGraph("image/statue1.png", TRUE);
		hiroba_image[8] = LoadGraph("image/statue2.png", TRUE);
		hiroba_image[9] = LoadGraph("image/statue3.jpg", FALSE);
		::DxLib::ProcessMessage();
		title_image[0] = LoadGraph("image/title1.png", TRUE);
		title_image[1] = LoadGraph("image/title2.png", TRUE);
		start_image[0] = LoadGraph("image/start.png", TRUE);
		start_image[1] = LoadGraph("image/start2.png", TRUE);
		continue_image[0] = LoadGraph("image/continue.png", TRUE);
		continue_image[1] = LoadGraph("image/continue2.png", TRUE);
		end_image[0] = LoadGraph("image/end.png", TRUE);
		end_image[1] = LoadGraph("image/end2.png", TRUE);
		bgm = bgm_;
	}

	void call(bool up_key[], std::uint_fast8_t& scene_id, std::uint_fast8_t yorozuya_level, std::uint_fast8_t sakanaya_level,
		std::uint_fast8_t farm_level, std::uint_fast8_t hiroba_level) {
		if (sakanaya_level == 3 || (hiroba_level % 3 == 1 && hiroba_level >= 2) || farm_level == 4) title_level = 1;

		if (ret == 0) background_x--;
		else background_x++;
		if (background_x == -1920) ret = 1;
		else if (background_x == 0) ret = 0;

		//メニュー選択
		if (up_key[KEY_INPUT_UP]) select--;
		else if (up_key[KEY_INPUT_DOWN]) select++;
		if (select > 2) select = 0;
		if (select < 0) select = 2;

		//メニュー決定
		if (up_key[KEY_INPUT_RETURN]) {
			StopSoundMem(bgm);
			if (select == 0) scene_id = 6;
			if (select == 1) scene_id = 2;
			if (select == 2) scene_id = 5;
		}
		//背景の描画
		DrawGraph(background_x / frame_size, 0, map_image, TRUE);

		//施設の描画
		if (hiroba_level == 0 && farm_level != 4) DrawGraph(background_x / frame_size, 0, hiroba_image[hiroba_level], TRUE);
		else if (farm_level != 4) DrawGraph(background_x / frame_size, 0, hiroba_image[hiroba_level - 1], TRUE);
		if (farm_level == 0) DrawGraph(background_x / frame_size, 0, farm_image[farm_level], TRUE);
		else DrawGraph(background_x / frame_size, 0, farm_image[farm_level - 1], TRUE);
		if (yorozuya_level == 0) DrawGraph(background_x / frame_size, 0, yorozuya_image[yorozuya_level], TRUE);
		else DrawGraph(background_x / frame_size, 0, yorozuya_image[yorozuya_level - 1], TRUE);
		if (sakanaya_level == 0) DrawGraph(background_x / frame_size, 0, sakanaya_image[sakanaya_level], TRUE);
		else DrawGraph(background_x / frame_size, 0, sakanaya_image[sakanaya_level - 1], TRUE);


		//タイトル
		if (title_level == 0) DrawGraph(0, -200 / frame_size, title_image[title_level], TRUE);
		else DrawGraph(0, -50 / frame_size, title_image[title_level], TRUE);

		//その他表示
		DrawGraph(0, 0, start_image[0], TRUE);
		DrawGraph(0, 0, continue_image[0], TRUE);
		DrawGraph(0, 0, end_image[0], TRUE);

		//選択
		if (select == 0)	DrawGraph(0, 0, start_image[1], TRUE);
		else if (select == 1) DrawGraph(0, 0, continue_image[1], TRUE);
		else DrawGraph(0, 0, end_image[1], TRUE);

		if (bgm_flag == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);//バックグラウンド再生
			bgm_flag = 1;
		}
	}

private:
	int background_x = 0, ret = 0;
	int select = 0;
	int bgm = 0;
	int bgm_flag = 0;
	int title_level = 0;
	int map_image = 0;
	int sakanaya_image[3] = {};
	int yorozuya_image[3] = {};
	int hiroba_image[10] = {};
	int farm_image[4] = {};
	int title_image[2] = {};
	int start_image[2] = {};
	int continue_image[2] = {};
	int end_image[2] = {};

};