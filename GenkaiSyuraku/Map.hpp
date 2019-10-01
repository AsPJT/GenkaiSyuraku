#pragma once

class Mob {
public:
	int image[4] = {};
	int size = 32;
	int sizeX = 128;
	int sizeY = 256;
	int x = 0, y = 0;
	int img = 0;
	int img_num = 1;
	int muki = 3;

};

class Player {
public:
	int image[24] = {};
	int size = 32;
	int sizeX = 128;
	int sizeY = 256;
	int x = 2752, y = size * 15; //xを3940以内の32の倍数で指定 2752
	int px = 832, py = size * 15; //xが832~2752のときは832固定 832
	int bx = 0, by = 0;
	int bpx = 0, bpy = 0;
	int img = 0;
	int img_num = 1;
	int muki = 3;
	int walking_flag = 0;
	int walking_ani = 0;
	int walking_ani_flag = 0;
	int speed = 4;
	unsigned int money = 100;
};

class Hatake {
public:
	int size = 128;
	int x, y;
	int img;
	int seeds;
	int level;

};

class Map {
public:
	void init(const int bgm_, const int map_) {
		map_image = map_;
		sakanaya_image[0] = LoadGraph("image/sakanaya1.png", TRUE);
		sakanaya_image[1] = LoadGraph("image/sakanaya2.png", TRUE);
		sakanaya_image[2] = LoadGraph("image/sakanaya3.png", TRUE);
		yorozuya_image[0] = LoadGraph("image/yorozuya1.png", TRUE);
		yorozuya_image[1] = LoadGraph("image/yorozuya2.png", TRUE);
		yorozuya_image[2] = LoadGraph("image/yorozuya3.png", TRUE);
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
		farm_image[0] = LoadGraph("image/farm1.png", TRUE);
		farm_image[1] = LoadGraph("image/farm2.png", TRUE);
		farm_image[2] = LoadGraph("image/farm3.png", TRUE);
		farm_image[3] = LoadGraph("image/farm4.png", FALSE);
		::DxLib::ProcessMessage();

		tomato_image[0] = LoadGraph("image/tomato1.png", TRUE);
		tomato_image[1] = LoadGraph("image/tomato2.png", TRUE);
		tomato_image[2] = LoadGraph("image/tomato3.png", TRUE);
		kyabetsu_image[0] = LoadGraph("image/kyabetsu1.png", TRUE);
		kyabetsu_image[1] = LoadGraph("image/kyabetsu2.png", TRUE);
		kyabetsu_image[2] = LoadGraph("image/kyabetsu3.png", TRUE);
		morokoshi_image[0] = LoadGraph("image/morokoshi1.png", TRUE);
		morokoshi_image[1] = LoadGraph("image/morokoshi2.png", TRUE);
		morokoshi_image[2] = LoadGraph("image/morokoshi3.png", TRUE);
		::DxLib::ProcessMessage();

		hatake_image = LoadGraph("image/hatake.png", TRUE);
		icon_image = LoadGraph("image/ex_icon.png", TRUE);
		fish_icon_image = LoadGraph("image/fish_icon.png", TRUE);
		area_icon_image = LoadGraph("image/area_icon.png", TRUE);
		menu_image = LoadGraph("image/menu.png", TRUE);
		menu2_image = LoadGraph("image/menu_yorozu.png", TRUE);
		selector_image = LoadGraph("image/selector.png", TRUE);
		textwindow_image = LoadGraph("image/textwindow.png", TRUE);
		window_image = LoadGraph("image/window.png", TRUE);
		find_image = LoadGraph("image/find_fish.png", TRUE);
		::DxLib::ProcessMessage();

		LoadDivGraph("image/player.png", 24, 6, 4, player.sizeX / frame_size, player.sizeY / frame_size, player.image);//画像を分割してimage配列に保存
		LoadDivGraph("image/ji.png", 4, 1, 4, mob[0].sizeX / frame_size, mob[0].sizeY / frame_size, mob[0].image);
		LoadDivGraph("image/ba.png", 4, 1, 4, mob[1].sizeX / frame_size, mob[1].sizeY / frame_size, mob[1].image);
		LoadDivGraph("image/man1.png", 4, 1, 4, mob[2].sizeX / frame_size, mob[2].sizeY / frame_size, mob[2].image);
		LoadDivGraph("image/man2.png", 4, 1, 4, mob[3].sizeX / frame_size, mob[3].sizeY / frame_size, mob[3].image);
		LoadDivGraph("image/man3.png", 4, 1, 4, mob[4].sizeX / frame_size, mob[4].sizeY / frame_size, mob[4].image);
		LoadDivGraph("image/foreign1.png", 4, 1, 4, mob[5].sizeX / frame_size, mob[5].sizeY / frame_size, mob[5].image);
		LoadDivGraph("image/foreign2.png", 4, 1, 4, mob[6].sizeX / frame_size, mob[6].sizeY / frame_size, mob[6].image);
		LoadDivGraph("image/foreign3.png", 4, 1, 4, mob[7].sizeX / frame_size, mob[7].sizeY / frame_size, mob[7].image);
		LoadDivGraph("image/alien.png", 4, 1, 4, mob[8].sizeX / frame_size, mob[8].sizeY / frame_size, mob[8].image);
		LoadDivGraph("image/girl1.png", 4, 1, 4, mob[9].sizeX / frame_size, mob[9].sizeY / frame_size, mob[9].image);
		LoadDivGraph("image/girl2.png", 4, 1, 4, mob[10].sizeX / frame_size, mob[10].sizeY / frame_size, mob[10].image);
		::DxLib::ProcessMessage();

		bgm = bgm_;
		bgm2 = LoadSoundMem("music/goukavillage.ogg");
		::DxLib::ProcessMessage();

		//Font
		FontHandle_mini = CreateFontToHandle(nullptr, 20 / frame_size, 2, (frame_size == 1) ? DX_FONTTYPE_EDGE : DX_FONTTYPE_NORMAL);
		FontHandle = CreateFontToHandle(nullptr, 50 / frame_size, 2, (frame_size == 1) ? DX_FONTTYPE_EDGE : DX_FONTTYPE_NORMAL);
		FontHandle_big = CreateFontToHandle(nullptr, 70 / frame_size, 2, (frame_size == 1) ? DX_FONTTYPE_EDGE : DX_FONTTYPE_NORMAL);
		::DxLib::ProcessMessage();

		//村人の初期画像(正面)，y座標
		for (i = 0; i < mob_num; i++) {
			mob[i].img = mob[i].image[0];
			mob[i].x = mob[i].size * -50;
			mob[i].y = mob[i].size * 13;
		}

		//畑の位置
		for (j = 0; j < 2; j++) {
			for (i = 0; i < 5; i++) {
				hatake[i + j * 5].x = 640 + chip_size * i;
				hatake[i + j * 5].y = 800 + chip_size * j;
				hatake[i + j * 5].img = hatake_image;
			}
		}
	}

	void call(std::array<int, item_num>& item_count, bool up_key[], std::int_fast32_t key[256], std::uint_fast8_t& scene_id, std::uint_fast32_t fished_count, 
		std::uint_fast32_t go_fish_count, std::uint_fast32_t material_count, std::uint_fast32_t go_material_count, std::uint_fast8_t& yorozuya_level, 
		std::uint_fast8_t& sakanaya_level, std::uint_fast8_t& farm_level, std::uint_fast8_t& hiroba_level, std::uint_fast8_t& hatake_level, int& talk_id) {
		returnflag = 0;
	
		//メニュー画面(よろず屋なども含む)
		switch (menu)
		{
		case 0:
			if (talk == 0 && up_key[KEY_INPUT_E]) menu = 1;
			break;
		case 1:
			//メインメニュー
			//選択
			if (up_key[KEY_INPUT_E]) menu = 0;
			else if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select--, selector_y -= 172;
			else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select++, selector_y += 172;
			if (select > 2) select = 0, selector_y -= 516;
			if (select < 0) select = 2, selector_y += 516;
			//決定
			if ((key[KEY_INPUT_RIGHT] || key[KEY_INPUT_D]) && select == 0) menu = 2;
			if (up_key[KEY_INPUT_RETURN]) {
				returnflag = 1;
				if (select == 0) menu = 2;
				if (select == 1) menu = 0;
				if (select == 2) {
					StopSoundMem(bgm);
					bgm_flag = 0;
					scene_id = 1;
					menu = 0;
				}
			}
			break;
		case 2:
			//アイテム選択
			//選択
			if (up_key[KEY_INPUT_E]) menu = 0;
			else if (key[KEY_INPUT_LEFT] || key[KEY_INPUT_A]) menu = 1;
			else if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) {
				select2--;
				if(menu_size < 6) selector2_y -= 70, menu_size++;
			}
			else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) {
				select2++;
				if (menu_size > 1) selector2_y += 70, menu_size--;
			}
			if (select2 > item_num - 2) select2 = item_num - 2;
			if (select2 < 0) select2 = 0;
			//決定
			if (up_key[KEY_INPUT_RETURN]) {
				returnflag = 1;
				menu = 0;
			}
			break;
		case 3:
			//よろず屋
			if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select3--, selector3_y -= 170;
			else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select3++, selector3_y += 170;
			if (select3 > 2) select3 = 0, selector3_y -= 510;
			if (select3 < 0) select3 = 2, selector3_y += 510;
			//決定
			if (up_key[KEY_INPUT_RETURN] || key[KEY_INPUT_RIGHT] || key[KEY_INPUT_D]) {
				returnflag = 1;
				if (select3 == 0) menu = 4;
				if (select3 == 1) menu = 5;
				if (select3 == 2) menu = 0;
			}
			break;
		case 4:
			//買う
			if (key[KEY_INPUT_LEFT] || key[KEY_INPUT_A]) menu = 3;
			else if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select4--, selector4_y -= 70;
			else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select4++, selector4_y += 70;
			if (select4 > 4) select4 = 0, selector4_y -= 350;
			if (select4 < 0) select4 = 4, selector4_y += 350;
			//決定
			if (up_key[KEY_INPUT_RETURN]) {
				returnflag = 1;
				if (select4 == 0 && player.money >= item_buy[item_tomato_seed]) item_count[item_tomato_seed]++, player.money -= item_buy[item_tomato_seed], buy++;
				else if (select4 == 1 && player.money >= item_buy[item_cabbage_seed]) item_count[item_cabbage_seed]++, player.money -= item_buy[item_cabbage_seed], buy++;
				else if (select4 == 2 && player.money >= item_buy[item_corn_seed]) item_count[item_corn_seed]++, player.money -= item_buy[item_corn_seed], buy++;
				else if (select4 == 3 && player.money >= item_buy[item_broom]) item_count[item_broom]++, player.money -= item_buy[item_broom], buy++;
				else if (select4 == 4) menu = 3;
				
				if (buy > 10) buy == 10;
			}
			break;
		case 5:
			//売る
			if (key[KEY_INPUT_LEFT] || key[KEY_INPUT_A]) menu = 3;
			else if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) {
				select5--;
				if (menu_size < 6) selector5_y -= 70, menu_size++;
			}
			else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) {
				select5++;
				if (menu_size > 1) selector5_y += 70, menu_size--;
			}
			if (select5 > item_num - 2) select5 = item_num - 2;
			if (select5 < 0) select5 = 0;
			//決定
			if (up_key[KEY_INPUT_RETURN]) {
				returnflag = 1;
				if (item_count[select5 + 1] > 0) {
					item_count[select5 + 1]--;
					player.money += item_sell[select5 + 1];
				}
			}
			break;
		case 6:
			//畑
			if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select6--, selector6_y -= 50;
			else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select6++, selector6_y += 50;
			if (select6 > 3) select6 = 0, selector6_y -= 200;
			if (select6 < 0) select6 = 3, selector6_y += 200;
			//決定
			if (up_key[KEY_INPUT_RETURN]) {
				menu = 0;
				talk = 22;
				returnflag = 1;
				if (select6 == 0) {
					if (item_count[item_tomato_seed] > 0) {
						talk = 23;
						hatake[hatake_select].img = tomato_image[0];
						hatake[hatake_select].level = 0;
						item_count[item_tomato_seed]--;
					}
				}
				else if (select6 == 1) {
					if (item_count[item_cabbage_seed] > 0) {
						talk = 23;
						hatake[hatake_select].img = kyabetsu_image[0];
						hatake[hatake_select].level = 0;
						item_count[item_cabbage_seed]--;
					}
				}
				else if (select6 == 2) {
					if (item_count[item_corn_seed] > 0) {
						talk = 23;
						hatake[hatake_select].img = morokoshi_image[0];
						hatake[hatake_select].level = 0;
						item_count[item_corn_seed]--;
					}
				}
				else if (select6 == 3) {
					talk = 0;
				}
			}
			break;
		case 7:
			//資材選択
			if (kenchiku != 0) {
				talk = 27;
				menu = 0;
			}
			else if (farm_level == 4) {
				talk = 20;
				menu = 0;
			}
			else if (hiroba_level == 1) {
				if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select7--, selector7_y -= 54;
				else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select7++, selector7_y += 54;
				if (select7 > 3) select7 = 0, selector7_y -= 216;
				if (select7 < 0) select7 = 3, selector7_y += 216;
				//決定
				if (up_key[KEY_INPUT_RETURN]) {
					returnflag = 1;
					if (select7 == 0 && item_count[item_wood] >= 10) item_count[item_wood] -= 10, menu = 0, kenchiku = 2;
					else if (select7 == 1 && item_count[item_stone] >= 20) item_count[item_stone] -=20, menu = 0, kenchiku = 5;
					else if (select7 == 2 && item_count[item_stone] >= 10) item_count[item_stone] -= 10, menu = 0, kenchiku = 8;
					else if (select7 == 3) menu = 0;
				}
			}
			else if (hiroba_level == 2 || hiroba_level == 5 || hiroba_level == 8) {
				if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select7--, selector7_y -= 54;
				else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select7++, selector7_y += 54;
				if (select7 > 3) select7 = 0, selector7_y -= 216;
				if (select7 < 0) select7 = 3, selector7_y += 216;
				//決定
				if (up_key[KEY_INPUT_RETURN]) {
					returnflag = 1;
					if (select7 == 0 && item_count[item_stone] >= 20 && item_count[item_wood] >= 10 && hiroba_level == 2) item_count[item_wood] -= 10, item_count[item_stone] -= 20, menu = 0, kenchiku = 3;
					else if (select7 == 1 && item_count[item_stone] >= 20 && item_count[item_ore] >= 10 && hiroba_level == 5) item_count[item_stone] -= 20, item_count[item_ore] -= 10, menu = 0, kenchiku = 6;
					else if (select7 == 2 && item_count[item_stone] >= 10 && item_count[item_ore] >= 10 && hiroba_level == 8) item_count[item_stone] -= 10, item_count[item_ore] -= 10, menu = 0, kenchiku = 9;
					else if (select7 == 3) menu = 0;
				}
			}
			else if (hiroba_level == 3 || hiroba_level == 6 || hiroba_level == 9) {
				if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select7--, selector7_y -= 54;
				else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select7++, selector7_y += 54;
				if (select7 > 3) select7 = 0, selector7_y -= 216;
				if (select7 < 0) select7 = 3, selector7_y += 216;
				//決定
				if (up_key[KEY_INPUT_RETURN]) {
					returnflag = 1;
					if (select7 == 0 && item_count[item_stone] >= 30 && item_count[item_wood] >= 10 && hiroba_level == 3) item_count[item_wood] -= 10, item_count[item_stone] -= 30, menu = 0, kenchiku = 4;
					else if (select7 == 1 && item_count[item_stone] >= 30 && item_count[item_ore] >= 30 && hiroba_level == 6) item_count[item_stone] -= 30, item_count[item_ore] -= 30, menu = 0, kenchiku = 7;
					else if (select7 == 2 && item_count[item_stone] >= 20 && item_count[item_ore] >= 20 && hiroba_level == 9) item_count[item_stone] -= 20, item_count[item_ore] -= 20, menu = 0, kenchiku = 10;
					else if (select7 == 3) menu = 0;
				}
			}
			else {
				talk = 20;
				menu = 0;
			}
			break;
		default:
			break;
		}
		if (menu == 0) {
			switch (talk)
			{
			case 0:
				//モブとの会話
				for (i = 0; i < mob_num; i++) {
					if (player.x + player.sizeX > mob[i].x &&
						player.x < mob[i].x + mob[i].sizeX &&
						player.y + player.sizeY / 4> mob[i].y &&
						player.y < mob[i].y + mob[i].sizeY / 4) {
						//近づいた状態で話しかける
						if ((up_key[KEY_INPUT_RETURN] && returnflag == 0)) {
							returnflag = 1;
							//モブの振り向き
							if (player.x + player.sizeX / 2 < mob[i].x) mob[i].img = mob[i].image[1];
							else if (player.x + player.sizeX / 2 > mob[i].x + player.sizeX) mob[i].img = mob[i].image[2];
							else if (player.y + 32 < mob[i].y + mob[i].sizeY / 4) mob[i].img = mob[i].image[3];
							else mob[i].img = mob[i].image[0];
							if (talk == 0) {
								if (i == 0) {//jii
									person = person_grandpa;
									if (hiroba_level >= 1) talk = 10;
									else if (sakanaya_level == 1) talk = 1;
								}
								else if (i == 1) {//baa
									person = person_yorozu;
									if(yorozuya_level == 3) talk = 6;
									else if (yorozuya_level == 2) talk = 5;
									else talk = 4;
								}
								else if (i == 2) {//man1
									person = person_man;
									if(farm_level == 2) talk = 8;
									else if (farm_level == 1) talk = 7;
								}
								else if (i == 3) {//man2
									person = person_man;
									talk = 14;
								}
								else if (i == 4) {//man3
									person = person_man;
									if (hiroba_level >= 1) talk = 19;
								}
								else if (i == 5) {//foreign1
									person = person_foreign;
									if (farm_level == 4) talk = 17;
									else if (farm_level == 3) talk = 9;
								}
								else if (i == 6) {//foreign2
									person = person_foreign;
									talk = 13;
								}
								else if (i == 7) {//foreign3
									person = person_foreign;
									talk = 16;
								}
								else if (i == 8) {//alien
									person = person_alien;
									talk = 12;
								}
								else if (i == 9) {//girl1
									person = person_child;
									talk = 3;
								}
								else if (i == 10) {//girl2 tower or statue level == 1 or 2
									person = person_child;
									if(hiroba_level == 2 || hiroba_level == 3) talk = 11;
									else if (hiroba_level == 8 || hiroba_level == 9) talk = 15;
								}
							}
							break;
						}
					}
				}
				//釣り場移行
				if (player.x > tsuri_area) {
					if (up_key[KEY_INPUT_RETURN] && returnflag == 0) {
						bgm_flag = 0;
						StopSoundMem(bgm);
						scene_id = 3;
					}
				}
				//畑の種植or収穫
				else if (hatake_level > 0) {
					hatake_find = 10;
					for (j = 0; j < 10; j++) {
						if (player.x + player.sizeX - 32 > hatake[j].x &&
							player.x < hatake[j].x + hatake[j].size - 32 &&
							player.y + player.sizeY / 2 > hatake[j].y - 96 &&
							player.y < hatake[j].y + hatake[j].size / 2 - 128) {
							hatake_find = j;
							//近づいた状態で話しかける
							if ((up_key[KEY_INPUT_RETURN] && returnflag == 0) && hatake[j].img == hatake_image) {//種植
								talk = 21;
								hatake_select = j;
								break;
							}
							else if ((up_key[KEY_INPUT_RETURN] && returnflag == 0) && hatake[j].level == 2) {//収穫
								hatake_select = j;
								if (hatake[j].img == tomato_image[2]) {
									talk = 24;
									item_count[item_tomato]++;
								}
								else if (hatake[j].img == kyabetsu_image[2]) {
									talk = 25;
									item_count[item_cabbage]++;
								}
								else if (hatake[j].img == morokoshi_image[2]) {
									talk = 26;
									item_count[item_corn]++;
								}
								break;
							}
						}
					}
				}
				break;
			case 4:
			case 5:
			case 6:
				//よろず屋
				if (up_key[KEY_INPUT_RETURN] && returnflag == 0) talk = 0, menu = 3;
				break;
			case 10:
			case 18:
				//ミニゲームmaterial
				if (up_key[KEY_INPUT_RETURN] && returnflag == 0) {
					bgm_flag = 0;
					StopSoundMem(bgm);
					talk = 0;
					scene_id = 4;
				}
				break;
			case 19:
				if (up_key[KEY_INPUT_RETURN] && returnflag == 0) {
					talk = 0;
					menu = 7;
				}
				break;
			case 21:
				//畑
				if (up_key[KEY_INPUT_RETURN] && returnflag == 0) menu = 6;
				break;
			case 24:
			case 25:
			case 26:
				//畑
				if (up_key[KEY_INPUT_RETURN] && returnflag == 0) {
					hatake[hatake_select].img = hatake_image;
					hatake[hatake_select].level = 0;
					talk = 0;
				}
				break;
			default:
				if (up_key[KEY_INPUT_RETURN] && returnflag == 0) talk = 0;
				break;
			}
		}

		//歩行フラグ
		if (player.x % player.size == 0 && player.y % player.size == 0) {       //座標が32で割り切れたら入力可能
			player.walking_flag = 1;                  //歩くフラグを立てる。
			if(talk != 0 || menu != 0) player.walking_flag = 0;
			if ((key[KEY_INPUT_UP] && key[KEY_INPUT_LEFT]) || (key[KEY_INPUT_W] && key[KEY_INPUT_A]))
				player.muki = 1;
			else if (key[KEY_INPUT_LEFT] && key[KEY_INPUT_DOWN] || (key[KEY_INPUT_A] && key[KEY_INPUT_S]))
				player.muki = 3;
			else if (key[KEY_INPUT_DOWN] && key[KEY_INPUT_RIGHT] || (key[KEY_INPUT_S] && key[KEY_INPUT_D]))
				player.muki = 5;
			else if (key[KEY_INPUT_RIGHT] && key[KEY_INPUT_UP] || (key[KEY_INPUT_D] && key[KEY_INPUT_W]))
				player.muki = 7;
			else if (key[KEY_INPUT_UP] || key[KEY_INPUT_W])    //上ボタンが押されたら
				player.muki = 0;                       //上向きフラグを立てる
			else if (key[KEY_INPUT_LEFT] || key[KEY_INPUT_A])  //左ボタンが押されたら
				player.muki = 2;                       //左向きフラグを
			else if (key[KEY_INPUT_DOWN] || key[KEY_INPUT_S])  //下ボタンが押されたら
				player.muki = 4;                       //右向きフラグを立てる
			else if (key[KEY_INPUT_RIGHT] || key[KEY_INPUT_D]) //右ボタンが押されたら
				player.muki = 6;                       //下向きフラグを
			else                                      //何のボタンも押されてなかったら
				player.walking_flag = 0;              //歩かないフラグを立てる
		}

		//移動処理
		if (player.walking_flag == 1) {       //歩くフラグが立っていたら
			if (player.muki == 0)             //上向きならy座標を減らす
				player.y-= player.speed, player.img_num = 19;
			else if (player.muki == 1)
				player.x-= player.speed, player.y-= player.speed, player.img_num = 16;
			else if (player.muki == 2)        //左向きならx座標を減らす
				player.x-= player.speed, player.img_num = 7;
			else if (player.muki == 3)
				player.x-= player.speed, player.y+= player.speed, player.img_num = 4;
			else if (player.muki == 4)        //下向きならy座標を増やす
				player.y+= player.speed, player.img_num = 1;
			else if (player.muki == 5)
				player.x+= player.speed, player.y+= player.speed, player.img_num = 10;
			else if (player.muki == 6)        //右向きならx座標を増やす
				player.x+= player.speed, player.img_num = 13;
			else if (player.muki == 7)
				player.x+= player.speed, player.y-= player.speed, player.img_num = 22;
		
			if (player.x <= map_width / 2 - player.sizeX || player.x >= map_width + map_width / 2 - player.sizeX) {   //プレイヤーのみ動かす
				if (player.muki == 0)
					player.py-= player.speed;
				else if (player.muki == 1)
					player.px-= player.speed, player.py-= player.speed;
				else if (player.muki == 2)
					player.px-= player.speed;
				else if (player.muki == 3)
					player.px-= player.speed, player.py+= player.speed;
				else if (player.muki == 4)
					player.py+= player.speed;
				else if (player.muki == 5)
					player.px+= player.speed, player.py+= player.speed;
				else if (player.muki == 6)
					player.px+= player.speed;
				else if (player.muki == 7)
					player.px+= player.speed, player.py-= player.speed;
			}
			else {  //背景を追従させる(プレイヤーのx座標固定)
				if (player.muki == 0)
					player.py-= player.speed;
				else if (player.muki == 1)
					player.py-= player.speed;
				else if (player.muki == 3)
					player.py+= player.speed;
				else if (player.muki == 4)
					player.py+= player.speed;
				else if (player.muki == 5)
					player.py+= player.speed;
				else if (player.muki == 7)
					player.py-= player.speed;
			}
		}

		//カメラ追従
		if (player.x <= map_width / 2 - player.sizeX) background_x = 0;
		else if (player.x >= map_width + map_width / 2 - player.sizeX) background_x = -map_width;
		else background_x = map_width / 2 - player.sizeX - player.x;

		//進入禁止エリアの指定
		if (player.x < 0) player.x = player.bx, player.px = player.bpx;
		else if (player.x > player.size*110 && player.px > player.size * 48) player.x = player.bx, player.px = player.bpx;
		if (player.y < player.size * 13) player.y = player.by, player.py = player.bpy;
		else if (player.y > player.size*26) player.y = player.by, player.py = player.bpy;
		
		//Mobとの当たり判定
		for (i = 0; i < mob_num; i++) {
			if (player.x + player.sizeX - 32 > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX - 32 &&
				player.y + player.sizeY / 4 - 32 > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY / 4 - 32) {
				player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
			}
		}
		//畑の当たり判定
		if (hatake_level > 0) {
			for (i = 0; i < hatake_num; i++) {
				if (player.x + player.sizeX > hatake[i].x &&
					player.x < hatake[i].x + hatake[i].size &&
					player.y + player.sizeY / 4 > hatake[i].y - 128 &&
					player.y < hatake[i].y + hatake[i].size / 4 - 128) {
					player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
				}
			}
		}

		//プレイヤーの歩行アニメーション
		if ((player.x % 32 == 0 && player.y % 32 == 0) && player.walking_ani_flag == 0) {
			if (player.px % 32 != 0) {
				if (player.bpx > player.px) player.px += player.speed;
				else if (player.bpx < player.px) player.px -= player.speed;
			}
			player.walking_ani++;
			player.walking_ani_flag = 1;
		}
		else if (player.bx != player.x || player.by != player.y) {
			player.walking_ani_flag = 0;
		}
		if (player.walking_ani == 200) player.walking_ani = 0;

		if (player.x % 32 == 0 && player.y % 32 == 0) player.img = player.image[player.img_num];
		else if (player.walking_ani % 4 == 0) player.img = player.image[player.img_num - 1];
		else if (player.walking_ani % 4 == 1) player.img = player.image[player.img_num];
		else if (player.walking_ani % 4 == 2) player.img = player.image[player.img_num + 1];
		else if (player.walking_ani % 4 == 3) player.img = player.image[player.img_num];
		
		//モード推移後のフラグ処理
		if (go_fish_count != go_fish_before || go_material_count != go_material_before) {
			if (go_fish_count != go_fish_before) sakana_total += fished_count;
			if (go_material_count != go_material_before) material_total += material_count;

			//畑の成長
			for (j = 0; j < 10; j++) {
				if (hatake_level > 0) {
					if (hatake[j].img != hatake_image) hatake[j].level++;
					if (hatake[j].level > 2) hatake[j].level = 2;
				}
			}

			//村人の初期画像(正面)，y座標
			for (i = 0; i < mob_num; i++) {
				mob[i].img = mob[i].image[0];
				mob[i].x = mob[i].size * -50;
				mob[i].y = mob[i].size * 13;
			}

			//集落レベルの管理
			if(kenchiku != 0) hiroba_level = kenchiku;
			kenchiku = 0;

			if ((item_count[item_straw] >= 150 || farm_level == 4) && hiroba_level != 4 && hiroba_level != 7 && hiroba_level != 10)
				farm_level = 4;
			else if (item_count[item_straw] >= 100 || farm_level == 3)
				farm_level = 3;
			else if (item_count[item_straw] >= 50 || farm_level == 2)
				farm_level = 2;
			else if (item_count[item_straw] >= 20 || farm_level == 1)
				farm_level = 1;
			
			if (sakana_total >= 70)
				sakanaya_level = 3;
			else if (sakana_total >= 20) {
				sakanaya_level = 2;
				yorozuya_level = 1;
				hatake_level = 1;
				if(hiroba_level < 2) hiroba_level = 1;
			}

			if (buy >= 10 && go_material_count >= 3 && go_fish_count >= 3)
				yorozuya_level = 3;
			else if (buy >= 1)
				yorozuya_level = 2;
		}
		
		//集落レベルに応じた村人の配置
		if (sakanaya_level >= 2)
			mob[9].x = mob[9].size * 91;  //こども1
		else if (sakanaya_level >= 1)
			mob[0].x = mob[0].size * 91;  //おじい

		if (yorozuya_level >= 1)
			mob[1].x = mob[1].size * 16;  //おばあ

		if (hiroba_level >= 1) {
			mob[0].x = mob[0].size * 37;  //おじい
			mob[4].x = mob[4].size * 27;  //おじさん3(建築)

			if (farm_level != 4) {
				if (hiroba_level == 10)
					mob[7].x = mob[7].size * 47;  //外国人3
				else if (hiroba_level >= 8)
					mob[10].x = mob[10].size * 47;  //こども2
				else if (hiroba_level >= 7)
					mob[3].x = mob[3].size * 47;  //おじさん2
				else if (hiroba_level >= 5)
					mob[6].x = mob[6].size * 47;  //外国人2
				else if (hiroba_level >= 4)
					mob[8].x = mob[8].size * 47;  //宇宙人
				else if (hiroba_level >= 2)
					mob[10].x = mob[10].size * 47;  //こども2
			}
		}
		
		if (farm_level >= 3)
			mob[5].x = mob[5].size * 60;  //外国人1
		else if (farm_level >= 2)
			mob[2].x = mob[2].size * 60;  //おじさん1
		else if (farm_level >= 1)
			mob[2].x = mob[2].size * 60;  //おじさん1

		//畑の成長に応じた画像の差し替え
		if (hatake_level > 0) {
			for (i = 0; i < 10; i++) {
				for (j = 0; j < 2; j++) {
					if (hatake[i].img == tomato_image[j] && j + 1 == hatake[i].level) {
						hatake[i].img = tomato_image[j + 1];
					}
					else if (hatake[i].img == kyabetsu_image[j] && j + 1 == hatake[i].level) {
						hatake[i].img = kyabetsu_image[j + 1];
					}
					else if (hatake[i].img == morokoshi_image[j] && j + 1 == hatake[i].level) {
						hatake[i].img = morokoshi_image[j + 1];
					}
				}
			}
		}
		
        //BGM再生
		if (bgm_flag == 0) {
			if(hiroba_level >= 2) StopSoundMem(bgm), PlaySoundMem(bgm2, DX_PLAYTYPE_LOOP);
			else PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
			bgm_flag = 1;
		}
		
		Draw(yorozuya_level, sakanaya_level, farm_level, hiroba_level, hatake_level, item_count);

		//selectorの初期化
		if (talk == 0 && menu == 0) {
			selector_y = 325;
			selector2_y = 230;
			selector3_y = 340;
			selector4_y = 230;
			selector5_y = 230;
			selector6_y = 615;
			selector7_y = 820;
			select = 0;
			select2 = 0;
			select3 = 0;
			select4 = 0;
			select5 = 0;
			select6 = 0;
			select7 = 0;
			menu_size = 6;
		}
		//前フレームのデータを記録
		player.bpx = player.px;
		player.bpy = player.py;
		player.bx = player.x;
		player.by = player.y;
		go_fish_before = go_fish_count;
		go_material_before = go_material_count;

		//printfDx("%d %d %d\n", sakana_total, material_total, farm_level);
		talk_id = talk;
	}

	void Draw(std::uint_fast8_t yorozuya_level, std::uint_fast8_t sakanaya_level, std::uint_fast8_t farm_level, std::uint_fast8_t hiroba_level, 
		std::uint_fast8_t hatake_level, std::array<int, item_num>& item_count) {
		//背景の描画
		DrawGraph(background_x / frame_size, 0, map_image, TRUE);

		//施設の描画
		if (hiroba_level == 0 && farm_level != 4) DrawGraph(background_x / frame_size, 0, hiroba_image[hiroba_level], TRUE);
		else if(farm_level != 4) DrawGraph(background_x / frame_size, 0, hiroba_image[hiroba_level - 1], TRUE);
		if (farm_level == 0) DrawGraph(background_x / frame_size, 0, farm_image[farm_level], TRUE);
		else DrawGraph(background_x / frame_size, 0, farm_image[farm_level - 1], TRUE);
		if(yorozuya_level == 0) DrawGraph(background_x / frame_size, 0, yorozuya_image[yorozuya_level], TRUE);
		else DrawGraph(background_x / frame_size, 0, yorozuya_image[yorozuya_level - 1], TRUE);
		if (sakanaya_level == 0) DrawGraph(background_x / frame_size, 0, sakanaya_image[sakanaya_level], TRUE);
		else DrawGraph(background_x / frame_size, 0, sakanaya_image[sakanaya_level - 1], TRUE);

		//つりエリアのアイコン表示
		if (player.x > tsuri_area) {
			DrawGraph(0, 0, area_icon_image, TRUE);
			DrawGraph((tsuri_area + background_x - 400) / frame_size, -250 / frame_size, fish_icon_image, TRUE);
			DrawFormatStringToHandle(1050 / frame_size, 200 / frame_size, GetColor(0, 0, 0), FontHandle, u8"Enterキーで釣りエリアへ");
		}
		//おじいのアイコンを描画
		DrawGraph((mob[0].x + background_x - 64) / frame_size, (mob[0].y - 200) / frame_size, icon_image, TRUE);

		//後方のものから表示
		for (i = 0; i < mob_num; i++)
			if (mob[i].y <= player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width) DrawGraph((mob[i].x + background_x) / frame_size, mob[i].y / frame_size, mob[i].img, TRUE);//mobを描画
		if (hatake_level > 0) {
			for (i = 0; i < hatake_num; i++)
				if (hatake[i].y + hatake[i].size / 2 <= player.y + player.sizeY)
					if (hatake[i].x > player.x - map_width && hatake[i].x < player.x + map_width) DrawGraph((hatake[i].x + background_x) / frame_size, hatake[i].y / frame_size, hatake[i].img, TRUE);//畑を描画
		}
		DrawGraph(player.px / frame_size, player.py / frame_size, player.img, TRUE);   //プレイヤーを描画
		for (i = 0; i < mob_num; i++)
			if (mob[i].y > player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width)  DrawGraph((mob[i].x + background_x) / frame_size, mob[i].y / frame_size, mob[i].img, TRUE);  //mobを描画
		if (hatake_level > 0) {
			for (i = 0; i < hatake_num; i++)
				if (hatake[i].y + hatake[i].size / 2 > player.y + player.sizeY)
					if (hatake[i].x > player.x - map_width && hatake[i].x < player.x + map_width)  DrawGraph((hatake[i].x + background_x) / frame_size, hatake[i].y / frame_size, hatake[i].img, TRUE);  //畑を描画
		}

		//畑に近づいたときのアイコン
		if (hatake_find != 10) {
			DrawRotaGraph((hatake[hatake_find].x + background_x + 64) / frame_size, (hatake[hatake_find].y + 96) / frame_size, 0.3, 0, find_image, TRUE, FALSE);
		}

		//会話
		if (talk >= 1) {
			DrawGraph(0, 0, textwindow_image, TRUE);
			DrawFormatStringToHandle(130 / frame_size, 815 / frame_size, GetColor(255, 255, 255), FontHandle, talk_list[talk].c_str());
			DrawFormatStringToHandle(190 / frame_size, 730 / frame_size, GetColor(255, 255, 255), FontHandle, person_list[person].c_str());
		}

		//メニューの描画
		switch (menu)
		{
		case 1:
			//メインメニュー
			DrawGraph(0, 0, menu_image, TRUE);
			DrawGraph(170 / frame_size, selector_y / frame_size, selector_image, TRUE);
			DrawFormatStringToHandle(250 / frame_size, 160 / frame_size, GetColor(0, 0, 0), FontHandle, "%d", player.money);
			break;
		case 2:
			//アイテム選択
			DrawGraph(0, 0, menu_image, TRUE);
			DrawGraph(520 / frame_size, selector2_y / frame_size, selector_image, TRUE);
			DrawFormatStringToHandle(250 / frame_size, 160 / frame_size, GetColor(0, 0, 0), FontHandle, "%d", player.money);

			DrawFormatStringToHandle(600 / frame_size, 180 / frame_size, GetColor(0, 0, 0), FontHandle, u8"アイテム名　　　　　　所持数");

			DrawFormatStringToHandle(600 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select2 + menu_size - 5].c_str());
			DrawFormatStringToHandle(600 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select2 + menu_size - 4].c_str());
			DrawFormatStringToHandle(600 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select2 + menu_size - 3].c_str());
			DrawFormatStringToHandle(600 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select2 + menu_size - 2].c_str());
			DrawFormatStringToHandle(600 / frame_size, 530 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select2 + menu_size - 1].c_str());
			DrawFormatStringToHandle(600 / frame_size, 600 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select2 + menu_size].c_str());

			DrawFormatStringToHandle(1200 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select2 + menu_size - 5]);
			DrawFormatStringToHandle(1200 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select2 + menu_size - 4]);
			DrawFormatStringToHandle(1200 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select2 + menu_size - 3]);
			DrawFormatStringToHandle(1200 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select2 + menu_size - 2]);
			DrawFormatStringToHandle(1200 / frame_size, 530 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select2 + menu_size - 1]);
			DrawFormatStringToHandle(1200 / frame_size, 600 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select2 + menu_size]);

			DrawFormatStringToHandle(550 / frame_size, 850 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_string[select2 + 1.0].c_str());

			break;
		case 3:
			//よろず屋
			DrawGraph(0, 0, menu2_image, TRUE);
			DrawGraph(170 / frame_size, selector3_y / frame_size, selector_image, TRUE);
			DrawFormatStringToHandle(250 / frame_size, 160 / frame_size, GetColor(0, 0, 0), FontHandle, "%d", player.money);
			break;
		case 4:
			//買う
			DrawGraph(0, 0, menu2_image, TRUE);
			DrawGraph(520 / frame_size, selector4_y / frame_size, selector_image, TRUE);
			DrawFormatStringToHandle(250 / frame_size, 160 / frame_size, GetColor(0, 0, 0), FontHandle, "%d", player.money);

			DrawFormatStringToHandle(600 / frame_size, 180 / frame_size, GetColor(0, 0, 0), FontHandle, u8"アイテム名　　　売値　　　所持数");

			DrawFormatStringToHandle(600 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[item_tomato_seed].c_str());
			DrawFormatStringToHandle(600 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[item_cabbage_seed].c_str());
			DrawFormatStringToHandle(600 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[item_corn_seed].c_str());
			DrawFormatStringToHandle(600 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[item_broom].c_str());
			DrawFormatStringToHandle(600 / frame_size, 530 / frame_size, GetColor(0, 0, 0), FontHandle, u8"とじる");

			DrawFormatStringToHandle(1500 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[item_tomato_seed]);
			DrawFormatStringToHandle(1500 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[item_cabbage_seed]);
			DrawFormatStringToHandle(1500 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[item_corn_seed]);
			DrawFormatStringToHandle(1500 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[item_broom]);

			DrawFormatStringToHandle(1100 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_buy[item_tomato_seed]);
			DrawFormatStringToHandle(1100 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_buy[item_cabbage_seed]);
			DrawFormatStringToHandle(1100 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_buy[item_corn_seed]);
			DrawFormatStringToHandle(1100 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_buy[item_broom]);

			if (select4 == 0) DrawFormatStringToHandle(550 / frame_size, 850 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_string[item_tomato_seed].c_str());
			else if (select4 == 1) DrawFormatStringToHandle(550 / frame_size, 850 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_string[item_cabbage_seed].c_str());
			else if (select4 == 2) DrawFormatStringToHandle(550 / frame_size, 850 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_string[item_corn_seed].c_str());
			else if (select4 == 3) DrawFormatStringToHandle(550 / frame_size, 850 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_string[item_broom].c_str());

			break;
		case 5:
			//売る
			DrawGraph(0, 0, menu2_image, TRUE);
			DrawGraph(520 / frame_size, selector5_y / frame_size, selector_image, TRUE);
			DrawFormatStringToHandle(250 / frame_size, 160 / frame_size, GetColor(0, 0, 0), FontHandle, "%d", player.money);

			DrawFormatStringToHandle(600 / frame_size, 180 / frame_size, GetColor(0, 0, 0), FontHandle, u8"アイテム名　　　　　買値　　　所持数");

			DrawFormatStringToHandle(600 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select5 + menu_size - 5].c_str());
			DrawFormatStringToHandle(600 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select5 + menu_size - 4].c_str());
			DrawFormatStringToHandle(600 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select5 + menu_size - 3].c_str());
			DrawFormatStringToHandle(600 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select5 + menu_size - 2].c_str());
			DrawFormatStringToHandle(600 / frame_size, 530 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select5 + menu_size - 1].c_str());
			DrawFormatStringToHandle(600 / frame_size, 600 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_name[select5 + menu_size].c_str());

			DrawFormatStringToHandle(1500 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select5 + menu_size - 5]);
			DrawFormatStringToHandle(1500 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select5 + menu_size - 4]);
			DrawFormatStringToHandle(1500 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select5 + menu_size - 3]);
			DrawFormatStringToHandle(1500 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select5 + menu_size - 2]);
			DrawFormatStringToHandle(1500 / frame_size, 530 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select5 + menu_size - 1]);
			DrawFormatStringToHandle(1500 / frame_size, 600 / frame_size, GetColor(0, 0, 0), FontHandle, "%d個", item_count[select5 + menu_size]);

			DrawFormatStringToHandle(1100 / frame_size, 250 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_sell[select5 + menu_size - 5]);
			DrawFormatStringToHandle(1100 / frame_size, 320 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_sell[select5 + menu_size - 4]);
			DrawFormatStringToHandle(1100 / frame_size, 390 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_sell[select5 + menu_size - 3]);
			DrawFormatStringToHandle(1100 / frame_size, 460 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_sell[select5 + menu_size - 2]);
			DrawFormatStringToHandle(1100 / frame_size, 530 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_sell[select5 + menu_size - 1]);
			DrawFormatStringToHandle(1100 / frame_size, 600 / frame_size, GetColor(0, 0, 0), FontHandle, "%dG", item_sell[select5 + menu_size]);

			DrawFormatStringToHandle(550 / frame_size, 850 / frame_size, GetColor(0, 0, 0), FontHandle, "%s", item_string[select5 + 1].c_str());
			break;
		case 6:
			//畑
			DrawGraph(0, 0, window_image, TRUE);
			DrawRotaGraph(1450 / frame_size, selector6_y / frame_size, 0.5, 0, selector_image, TRUE, FALSE);
			DrawFormatStringToHandle(1470 / frame_size, 600 / frame_size, GetColor(0, 0, 0), FontHandle_mini, u8"トマトの種 ×%d", item_count[item_tomato_seed]);
			DrawFormatStringToHandle(1470 / frame_size, 650 / frame_size, GetColor(0, 0, 0), FontHandle_mini, u8"キャベツの種 ×%d", item_count[item_cabbage_seed]);
			DrawFormatStringToHandle(1470 / frame_size, 700 / frame_size, GetColor(0, 0, 0), FontHandle_mini, u8"とうもろこしの種 ×%d", item_count[item_corn_seed]);
			DrawFormatStringToHandle(1470 / frame_size, 750 / frame_size, GetColor(0, 0, 0), FontHandle_mini, u8"やめる");
			break;
		case 7:
			//資材選択
			if (hiroba_level != 4 && hiroba_level != 7 && hiroba_level != 10 && kenchiku == 0) {
				DrawGraph(0, 0, textwindow_image, TRUE);
				DrawFormatStringToHandle(190 / frame_size, 730 / frame_size, GetColor(255, 255, 255), FontHandle, person_list[person].c_str());
				DrawRotaGraph(600 / frame_size, selector7_y / frame_size, 0.5, 0, selector_image, TRUE, FALSE);
				DrawFormatStringToHandle(620 / frame_size, 950 / frame_size, GetColor(255, 255, 255), FontHandle, u8"とじる");
				DrawFormatStringToHandle(1400 / frame_size, 785 / frame_size, GetColor(255, 255, 255), FontHandle, u8"所持数");
				DrawFormatStringToHandle(1400 / frame_size, 840 / frame_size, GetColor(255, 255, 255), FontHandle, u8"木材:%d個", item_count[item_wood]);
				DrawFormatStringToHandle(1400 / frame_size, 895 / frame_size, GetColor(255, 255, 255), FontHandle, u8"石材:%d個", item_count[item_stone]);
				DrawFormatStringToHandle(1400 / frame_size, 950 / frame_size, GetColor(255, 255, 255), FontHandle, u8"鉱石:%d個", item_count[item_ore]);
				if (hiroba_level == 1) {
					DrawFormatStringToHandle(620 / frame_size, 785 / frame_size, GetColor(255, 255, 255), FontHandle, u8"タワー:木材10個");
					DrawFormatStringToHandle(620 / frame_size, 840 / frame_size, GetColor(255, 255, 255), FontHandle, u8"城:石材20個");
					DrawFormatStringToHandle(620 / frame_size, 895 / frame_size, GetColor(255, 255, 255), FontHandle, u8"像:石材10個");
				}
				else if (hiroba_level == 2 || hiroba_level == 5 || hiroba_level == 8) {
					if (hiroba_level == 2) DrawFormatStringToHandle(620 / frame_size, 785 / frame_size, GetColor(255, 255, 255), FontHandle, u8"タワー:石材20個 木材10個");
					else DrawFormatStringToHandle(620 / frame_size, 785 / frame_size, GetColor(64, 64, 64), FontHandle, u8"タワー:石材20個 木材10個");
					if (hiroba_level == 5) DrawFormatStringToHandle(620 / frame_size, 840 / frame_size, GetColor(255, 255, 255), FontHandle, u8"城:石材20個 鉱石10個");
					else DrawFormatStringToHandle(620 / frame_size, 840 / frame_size, GetColor(64, 64, 64), FontHandle, u8"城:石材20個 鉱石10個");
					if (hiroba_level == 8) DrawFormatStringToHandle(620 / frame_size, 895 / frame_size, GetColor(255, 255, 255), FontHandle, u8"像:石材10個 鉱石10個");
					else DrawFormatStringToHandle(620 / frame_size, 895 / frame_size, GetColor(64, 64, 64), FontHandle, u8"像:石材10個 鉱石10個");
				}
				else if (hiroba_level == 3 || hiroba_level == 6 || hiroba_level == 9) {
					if (hiroba_level == 3) DrawFormatStringToHandle(620 / frame_size, 785 / frame_size, GetColor(255, 255, 255), FontHandle, u8"タワー:石材30個 木材10個");
					else DrawFormatStringToHandle(620 / frame_size, 785 / frame_size, GetColor(64, 64, 64), FontHandle, u8"タワー:石材30個 木材10個");
					if (hiroba_level == 6) DrawFormatStringToHandle(620 / frame_size, 840 / frame_size, GetColor(255, 255, 255), FontHandle, u8"城:石材30個 鉱石30個");
					else DrawFormatStringToHandle(620 / frame_size, 840 / frame_size, GetColor(64, 64, 64), FontHandle, u8"城:石材30個 鉱石30個");
					if (hiroba_level == 9) DrawFormatStringToHandle(620 / frame_size, 895 / frame_size, GetColor(255, 255, 255), FontHandle, u8"像:石材20個 鉱石20個");
					else DrawFormatStringToHandle(620 / frame_size, 895 / frame_size, GetColor(64, 64, 64), FontHandle, u8"像:石材20個 鉱石20個");
				}
				break;
			}
		default:
			break;
		}

	}

private:
	Mob mob[11];
	Player player;
	Hatake hatake[10];

	enum :std::uint_fast8_t {
		//祖父
		person_grandpa,
		//こども
		person_child,
		//よろず屋
		person_yorozu,
		//外国人
		person_foreign,
		//おじさん
		person_man,
		//宇宙人
		person_alien,
		//畑
		person_field,
		//person_num
		person_num
	};

	std::array<std::string, person_num> person_list {
	   u8"　祖父　",
	   u8" こども ",
	   u8"よろず屋",
	   u8" 外国人 ",
	   u8"おじさん",
	   u8" 宇宙人 ",
	   u8"　 畑 　"
	};

	std::array<std::string, 28> talk_list {
	   u8"",
	   u8"釣りをしてこの集落を復興させてくれ！", //祖父
	   u8"今日も釣りをしてくれて感謝じゃ！", //祖父
	   u8"お兄ちゃんは今日はどれくらいお魚釣るの？", //こども
	   u8"なんか用？", //よろず屋
	   u8"いらっしゃい！何か買ってくかい？", //よろず屋5
	   u8"いつもごひいきにありがとうね！\nいろいろ見ていっておくれ！", //よろず屋
	   u8"この牧場も寂しいなぁ", //おじさん (祖父)
	   u8"この牧場もだいぶ賑やかになってきたな！", //おじさん (祖父)
	   u8"ここで羊たちに囲まれて寝てみたいデース！", //外国人 (この羊たちに囲まれて寝てみたいデース！)
	   u8"次は素材集めでこの広場を賑やかにするのじゃ！", //祖父10
	   u8"この塔に登ってみたいな！もっと高くなるのかな……", //こども
	   u8"ココハ　ワタシタチノ　スンデイタトコロニ　ニテイマスネ。", //宇宙人
	   u8"ワタシの国にはこれより大きい城がいくつもアリマース。", //外国人
	   u8"わたしがこのおしろのおうさまだ！", //     (祖父 ぼくがこのおしろのおうさまだ！えっへん。)
	   u8"もっとこの像が豪華になったらいいのになあ……", //こども15
	   u8"こんなに立派な像、ワタシの国でも見たことないデス！！", //外国人
	   u8"生まれ変わったら羊になりたいデス……", //外国人 (こども 生まれ変わったら羊になりたいなあ……)
	   u8"素材集めゲームを始めます", //おじさん
	   u8"素材を集めて建築をしよう", //おじさん
	   u8"ここまで大きくしてくれてありがとう。", //おじさん20
	   u8"植える種を選んでください。", //畑
	   u8"種を持っていません。", //畑
	   u8"育つまでミニゲームで遊ぼう。", //畑
	   u8"トマトを収穫しました。", //畑
	   u8"キャベツを収穫しました。", //畑25
	   u8"とうもろこしを収穫しました。", //畑
	   u8"いまから建築するからちょっと待ってな" //おじさん
	};


	std::uint_fast32_t go_fish_before = 0;
	std::uint_fast32_t go_material_before = 0;
	int i, j;
	int mob_num = 11;
	int hatake_num = 10;
	int FontHandle;
	int FontHandle_mini;
	int FontHandle_big;
	int sakana_total = 0;
	int material_total = 0;
	int menu_size = 4;
	int sizai = 0;

	//selector
	int select = 0;
	int select2 = 0;
	int select3 = 0;
	int select4 = 0;
	int select5 = 0;
	int select6 = 0;
	int select7 = 0;
	int item_select = 0;
	int hatake_select = 0;

	//flag
	int bgm, bgm2, bgm_flag = 0;
	int talk = 0;
	int person = 0;
	int menu = 0;
	int returnflag = 0;
	int hatake_find = 10;
	int buy = 0;
	int kenchiku = 0;

	//image
	int map_image;
	int sakanaya_image[3];
	int yorozuya_image[3];
	int hiroba_image[10];
	int farm_image[4];
	int tomato_image[3];
	int kyabetsu_image[3];
	int morokoshi_image[3];
	int hatake_image;
	int area_icon_image;
	int fish_icon_image;
	int icon_image;
	int menu_image;
    int selector_image;
	int textwindow_image;
	int window_image;
	int find_image;
	int menu2_image;

	//座標
	int background_x = 0;
	int selector_y = 0;
	int selector2_y = 0;
	int selector3_y = 0;
	int selector4_y = 0;
	int selector5_y = 0;
	int selector6_y = 0;
	int selector7_y = 0;
	int tsuri_area = 2800;


	int chip_size = 128;
	int map_width = 1920;//3840 120
	int map_hight = 1080;//640 20

};
