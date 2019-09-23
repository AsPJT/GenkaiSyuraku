#pragma once

class Mob {
public:
	int image[4];
	int size = 32;
	int sizeX = 128;
	int sizeY = 256;
	int x, y;
	int img;
	int img_num = 1;
	int muki = 3;

};

class Player {
public:
	int image[24];
	int size = 32;
	int sizeX = 128;
	int sizeY = 256;
	int x = size * 25, y = size * 20; //xを3940以内の32の倍数で指定
	int px = size * 25, py = size * 20; //xが832~2752のときは832固定
	int bx, by;
	int bpx, bpy;
	int img;
	int img_num = 1;
	int muki = 3;
	int walking_flag = 0;
	int walking_ani = 0;
	int walking_ani_flag = 0;
	int speed = 4;
};

class Map {
public:
	void init() {
		map_image[0] = LoadGraph("image/map1.png", TRUE);
		map_image[1] = LoadGraph("image/map2.png", TRUE);
		map_image[2] = LoadGraph("image/map3.png", TRUE);
		icon_image = LoadGraph("image/ex_icon.png", TRUE);
		fish_icon_image = LoadGraph("image/fish_icon.png", TRUE);
		area_icon_image = LoadGraph("image/area_icon.png", TRUE);
		menu_image = LoadGraph("image/menu.png", TRUE);
		selector_image = LoadGraph("image/selector.png", TRUE);
		textwindow_image = LoadGraph("image/textwindow.png", TRUE);
		hatake_image = LoadGraph("image/hatake3.png", TRUE);
		bgm = LoadSoundMem("music/genkaivillage.wav");

		LoadDivGraph("image/player.png", 24, 6, 4, player.sizeX, player.sizeY, player.image);//画像を分割してimage配列に保存
		LoadDivGraph("image/ji.png", 4, 1, 4, mob[0].sizeX, mob[0].sizeY, mob[0].image);//画像を分割してimage配列に保存

		//Font
		FontHandle = CreateFontToHandle(NULL, 100, 9, DX_FONTTYPE_EDGE);

		//おじいの初期位置
		mob[0].x = mob[0].size * 23;
		mob[0].y = mob[0].size * 12;  //3076 384 93 12
	}

	void control(bool up_key[], std::int_fast32_t key[256], std::uint_fast8_t& scene_id, std::uint_fast32_t fished_count, std::uint_fast32_t go_fish_count) {
		//キー入力
		if (player.x % player.size == 0 && player.y % player.size == 0) {       //座標が32で割り切れたら入力可能
			player.walking_flag = 1;                  //歩くフラグを立てる。
			if ((key[KEY_INPUT_UP] > 0 && key[KEY_INPUT_LEFT] > 0) || (key[KEY_INPUT_W] > 0 && key[KEY_INPUT_A] > 0))
				player.muki = 1;
			else if (key[KEY_INPUT_LEFT] > 0 && key[KEY_INPUT_DOWN] > 0 || (key[KEY_INPUT_A] > 0 && key[KEY_INPUT_S] > 0))
				player.muki = 3;
			else if (key[KEY_INPUT_DOWN] > 0 && key[KEY_INPUT_RIGHT] > 0 || (key[KEY_INPUT_S] > 0 && key[KEY_INPUT_D] > 0))
				player.muki = 5;
			else if (key[KEY_INPUT_RIGHT] > 0 && key[KEY_INPUT_UP] > 0 || (key[KEY_INPUT_D] > 0 && key[KEY_INPUT_W] > 0))
				player.muki = 7;
			else if (key[KEY_INPUT_UP] > 0 || key[KEY_INPUT_W] > 0)    //上ボタンが押されたら
				player.muki = 0;                       //上向きフラグを立てる
			else if (key[KEY_INPUT_LEFT] > 0 || key[KEY_INPUT_A] > 0)  //左ボタンが押されたら
				player.muki = 2;                       //左向きフラグを
			else if (key[KEY_INPUT_DOWN] > 0 || key[KEY_INPUT_S] > 0)  //下ボタンが押されたら
				player.muki = 4;                       //右向きフラグを立てる
			else if (key[KEY_INPUT_RIGHT] > 0 || key[KEY_INPUT_D] > 0) //右ボタンが押されたら
				player.muki = 6;                       //下向きフラグを
			else                                      //何のボタンも押されてなかったら
				player.walking_flag = 0;              //歩かないフラグを立てる
		}

		//メニュー画面
		if (up_key[KEY_INPUT_E] > 0 || menu == 1) {
			player.walking_flag = 0;
			menu = 1;
			if (up_key[KEY_INPUT_UP] > 0 || up_key[KEY_INPUT_W] > 0) select--, selector_y -= 175;
			else if (up_key[KEY_INPUT_DOWN] > 0 || up_key[KEY_INPUT_S] > 0) select++, selector_y += 175;
			if (select > 3) select = 0, selector_y -= 700;
			if (select < 0) select = 3, selector_y += 700;
			//決定
			if (up_key[KEY_INPUT_RETURN] > 0) {
				if (select == 0) select = 0;
				if (select == 1) select = 1;
				if (select == 2) select = 2;
				if (select == 3) scene_id = 1, menu = 0;
			}
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
		if (player.y < player.size * 11) player.y = player.by, player.py = player.bpy;
		else if (player.y > player.size*26) player.y = player.by, player.py = player.bpy;
		
		//Mobとの当たり判定
		for (i = 0; i < 1; i++) {
			if (player.x + player.sizeX > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX &&
				player.y + player.sizeY / 4 > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY / 4) {
				player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
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
			
		for (i = 0; i < 1; i++) {
			//Mobに近づくとアイコンを出す
			if (player.x + player.sizeX > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX &&
				player.y + player.sizeY > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY) {
				//近づいた状態で話しかける
				if (up_key[KEY_INPUT_RETURN] > 0) {
					//if (player.px + player.sizeX < mob[0].x) mob[0].img = mob[0].image[1];
					//else if (player.x < mob[i].x + mob[i].sizeX / 2) mob[0].img = mob[0].image[2];
					//else if (player.y < mob[i].y + mob[i].sizeY / 4) mob[0].img = mob[0].image[3];
					//else mob[0].img = mob[0].image[0];

					if (talk == 0) {
						StopSoundMem(bgm);
						scene_id = 3;
						talk = 1;
					}
				}
			}
			//釣り場移行
			else if (player.x > tsuri_area) {
				if (up_key[KEY_INPUT_RETURN] > 0) {
					StopSoundMem(bgm);
					scene_id = 3;
				}
			}
		}
		//printfDx("%d %d \n", player.px, player.x);
		//DrawGraph(200, 850, hatake_image, TRUE);  //はたけを描画
		//DrawGraph(328, 850, hatake_image, TRUE);  //はたけを描画
		//DrawGraph(456, 850, hatake_image, TRUE);  //はたけを描画
		
		//モード推移後のフラグ処理
		if (go_fish_count != go_fish_before) talk = 0, map_level++, bgm_flag = 0;

        //BGM再生
		if (bgm_flag == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
			bgm_flag = 1;
		}

		//前フレームのデータを記録
		player.bpx = player.px;
		player.bpy = player.py;
		player.bx = player.x;
		player.by = player.y;
		go_fish_before = go_fish_count;

		Draw();
	}

	void Draw() {
		//背景と人物の描画
		DrawGraph(background_x, 0, map_image[map_level], TRUE);  //背景を描画

		//つりエリアのアイコン表示
		if (player.x > tsuri_area) {
			DrawGraph(0, 0, area_icon_image, TRUE);
			DrawGraph(tsuri_area + background_x - 400, -250, fish_icon_image, TRUE);
			//DrawFormatStringToHandle(tsuri_area + background_x - 400, -150, GetColor(0, 0, 0), FontHandle, "Enterキーで釣りエリアへ");
			//DrawString(0, 0, "hello! DX Library!", GetColor(0, 0, 0));
		}
		//おじいのアイコンを描画
		DrawGraph(mob[0].x + background_x - 64, mob[0].y - 200, icon_image, TRUE);

		//後方のキャラから表示
		for (i = 0; i < 1; i++)
			if (mob[i].y <= player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width) DrawGraph(mob[0].x + background_x, mob[0].y, mob[0].image[0], TRUE);//jiを描画
		DrawGraph(player.px, player.py, player.img, TRUE);   //プレイヤーを描画
		for (i = 0; i < 1; i++)
			if (mob[i].y > player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width)  DrawGraph(mob[0].x + background_x, mob[0].y, mob[0].image[0], TRUE);  //jiを描画
		
		//メニューの描画
		if (menu == 1) {
			DrawGraph(0, 0, menu_image, TRUE);
			DrawGraph(0, selector_y, selector_image, TRUE);
		}
	}

private:
	Mob mob[5];
	Player player;
	std::uint_fast32_t go_fish_before = 0;
	int i;
	int select = 0;
	int map_level = 0;
	int FontHandle;

	//flag
	int bgm, bgm_flag = 0;
	int talk = 0;
	int menu = 0;

	//image
	int map_image[3];
	int area_icon_image;
	int fish_icon_image;
	int icon_image;
	int menu_image;
    int selector_image;
	int textwindow_image;
	int hatake_image;

	//座標
	int background_x = 0;
	int selector_y = 0;
	int tsuri_area = 2800;


	int chip_size = 32;
	int map_width = 1920;//3840 120
	int map_hight = 1080;//640 20

	
	//std::unique_ptr<int[][map_width]> map(new int[map_hight][map_width]);

	//map[map_hight][map_width] = {
	//	{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	//	{}
	//};
};
