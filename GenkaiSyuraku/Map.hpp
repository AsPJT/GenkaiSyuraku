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
	int x = size * 30, y = size * 20; //3940以内で指定
	int px = size * 30, py = size * 20; //1920以内で指定
	int bx, by;
	int bpx, bpy;
	int img;
	int img_num = 1;
	int muki = 3;
	int walking_flag = 0;
	int walking_ani = 1;
	int walking_rev = 1;
	int enter;
	int speed = 4;
};


class Map {
public:
	void init() {
		map_image[0] = LoadGraph("image/1.png", TRUE);
		map_image[1] = LoadGraph("image/2.png", TRUE);
		map_image[2] = LoadGraph("image/3.png", TRUE);
		icon_image = LoadGraph("image/ex_icon.png", TRUE);
		fish_icon_image = LoadGraph("image/fish_icon.png", TRUE);
		area_icon_image = LoadGraph("image/area_icon.png", TRUE);
		hatake_image = LoadGraph("image/hatake3.png", TRUE);
		bgm = LoadSoundMem("music/genkaivillage.wav");

		LoadDivGraph("image/player.png", 24, 6, 4, player.sizeX, player.sizeY, player.image);//画像を分割してimage配列に保存
		LoadDivGraph("image/ji.png", 4, 1, 4, mob[0].sizeX, mob[0].sizeY, mob[0].image);//画像を分割してimage配列に保存

		mob[0].x = mob[0].size * 23;
		mob[0].y = mob[0].size * 12;  //3076 384 93 12
	}

	void control(bool up_key[], std::int_fast32_t key[256], std::uint_fast8_t& scene_id, std::uint_fast32_t fished_count, std::uint_fast32_t go_fish_count) {
		//プレイヤー移動
		if (player.x % player.size == 0 && player.y % player.size == 0) {       //座標が32で割り切れたら入力可能

			player.walking_flag = 1;                  //歩くフラグを立てる。
			player.enter = 0;
			if ((key[KEY_INPUT_UP] > 0 && key[KEY_INPUT_LEFT] > 0) || (key[KEY_INPUT_W] > 0 && key[KEY_INPUT_A] > 0))
				player.muki = 1;
			else if (key[KEY_INPUT_LEFT] > 0 && key[KEY_INPUT_DOWN] > 0 || (key[KEY_INPUT_A] > 0 && key[KEY_INPUT_S] > 0))
				player.muki = 3;
			else if (key[KEY_INPUT_DOWN] > 0 && key[KEY_INPUT_RIGHT] > 0 || (key[KEY_INPUT_S] > 0 && key[KEY_INPUT_D] > 0))
				player.muki = 5;
			else if (key[KEY_INPUT_RIGHT] > 0 && key[KEY_INPUT_UP] > 0 || (key[KEY_INPUT_D] > 0 && key[KEY_INPUT_A] > 0))
				player.muki = 7;
			else if (key[KEY_INPUT_UP] > 0 || key[KEY_INPUT_W] > 0)    //上ボタンが押されたら
				player.muki = 0;                       //上向きフラグを立てる
			else if (key[KEY_INPUT_LEFT] > 0 || key[KEY_INPUT_A] > 0)  //左ボタンが押されたら
				player.muki = 2;                       //左向きフラグを
			else if (key[KEY_INPUT_DOWN] > 0 || key[KEY_INPUT_S] > 0)  //下ボタンが押されたら
				player.muki = 4;                       //右向きフラグを立てる
			else if (key[KEY_INPUT_RIGHT] > 0 || key[KEY_INPUT_D] > 0) //右ボタンが押されたら
				player.muki = 6;                       //下向きフラグを
			else if (up_key[KEY_INPUT_RETURN] > 0) //エンターキーが離されたら
				player.enter = 1, player.walking_flag = 0;             //会話フラグを
			else                                //何のボタンも押されてなかったら
				player.walking_flag = 0;              //歩かないフラグを立てる
		}

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
		
			if (player.x <= 1980 / 2 - player.sizeX || player.x >= 1980 + 1980 / 2 - player.sizeX) {   //プレイヤーのみ動かす
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
			else {  //背景を追従させる
				if (player.muki == 0)
					player.py-= player.speed;
				else if (player.muki == 1)
					background_x+= player.speed, player.py-= player.speed;
				else if (player.muki == 2)
					background_x+= player.speed;
				else if (player.muki == 3)
					background_x+= player.speed, player.py+= player.speed;
				else if (player.muki == 4)
					player.py+= player.speed;
				else if (player.muki == 5)
					background_x-= player.speed, player.py+= player.speed;
				else if (player.muki == 6)
					background_x-= player.speed;
				else if (player.muki == 7)
					background_x-= player.speed, player.py-= player.speed;
			}
		}
		//カメラ追尾
		if (player.x <= 1920 / 2 - player.sizeX) background_x = 0;
		else if (player.x >= 1920 + 1920 / 2 - player.sizeX) background_x = 1920;
		else background_x = 1920 / 2 - player.sizeX - player.x;

		//移動範囲
		if (player.x < 0) player.x = player.bx, player.px = player.bpx;
		else if (player.x > player.size*85 && player.px > player.size * 23) player.x = player.bx, player.px = player.bpx; //2720
		if (player.y < 352) player.y = player.by, player.py = player.bpy;
		else if (player.y > player.size*26) player.y = player.by, player.py = player.bpy;
		
		//Mobとの当たり判定
		for (i = 0; i < 1; i++) {
			if (player.x + player.sizeX / 2 > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX / 2 &&
				player.y + player.sizeY / 4 > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY / 4) {
				player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
			}
		}
		
		//プレイヤーの歩行アニメーション
		if (player.x % 32 == 0 && player.y % 32 == 0) {
			player.img = player.image[player.img_num];
			if (player.walking_rev == 0) {
				if (player.walking_ani < 2) player.walking_ani++;
				else if (player.walking_ani == 2) player.walking_rev = 1;
			}
			else {
				if (player.walking_ani >= 0) player.walking_ani--;
				else if (player.walking_ani == 2) player.walking_rev = 0;
			}
		}
		printfDx("%d %d \n", player.x, background_x);

		if(player.walking_ani == 0) player.img = player.image[player.img_num - 1];
		else if(player.walking_ani == 1) player.img = player.image[player.img_num];
		else player.img = player.image[player.img_num + 1];

		//if(player.x % player.size*2 >= 32 || player.y % player.size*2 >= 32 ) player.img = player.image[player.img_num + 1];
		//else if (player.x % player.size >= 1 || player.y % player.size >= 1) player.img = player.image[player.img_num - 1];
		//else player.img = player.image[player.img_num];

		//背景と人物の描画
		DrawGraph(background_x, 0, map_image[map_level], TRUE);  //背景を描画

		//つりエリアのアイコン表示
		if (player.x > 2000) {
			DrawGraph(1900 + background_x, 0, area_icon_image, TRUE);
			DrawGraph(1600 + background_x, 100, fish_icon_image, TRUE);
		}

		//おじいのアイコンを描画
		DrawGraph(mob[0].x + background_x - 64, mob[0].y - 200, icon_image, TRUE);

		for(i=0;i<1;i++)
			if (mob[i].y <= player.y) 
				if(mob[i].x > player.x-1980 && mob[i].x < player.x+1980) DrawGraph(mob[0].x + background_x, mob[0].y, mob[0].image[0], TRUE);                     //jiを描画
		DrawGraph(player.px, player.py, player.img, TRUE);                                                      //プレイヤーを描画
		for (i = 0; i < 1; i++) 
			if (mob[i].y > player.y)
				if (mob[i].x > player.x-1980 && mob[i].x < player.x + 1980)  DrawGraph(mob[0].x + background_x, mob[0].y, mob[0].image[0], TRUE);  //jiを描画

		for (i = 0; i < 1; i++) {
			//Mobに近づくとアイコンを出す
			if (player.x + player.sizeX > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX &&
				player.y + player.sizeY > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY) {
				//近づいた状態で話しかける
				if (player.enter == 1) {
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
			else if (player.x > 2000) {
				if (player.enter == 1) {
					if (talk == 0) {
						StopSoundMem(bgm);
						scene_id = 3;
						talk = 1;
					}
				}
			}
		}
		//DrawGraph(200, 850, hatake_image, TRUE);  //はたけを描画
		//DrawGraph(328, 850, hatake_image, TRUE);  //はたけを描画
		//DrawGraph(456, 850, hatake_image, TRUE);  //はたけを描画
		
		//printfDx("%d %d \n", player.x, player.y);
		player.bpx = player.px;
		player.bpy = player.py;
		player.bx = player.x;
		player.by = player.y;

		if (go_fish_count != go_fish_before) talk = 0, map_level++, bgm_flag = 0;
		go_fish_before = go_fish_count;

		if (bgm_flag == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_BACK);//バックグラウンド再生
			bgm_flag = 1;
		}

	}

private:
	Mob mob[5];
	Player player;
	int i;
	int bgm, bgm_flag = 0;
	std::uint_fast32_t go_fish_before = 0;
	int talk = 0;
	int map_level = 0;
	int map_image[3];
	int area_icon_image;
	int fish_icon_image;
	int icon_image;
	int hatake_image;
	int background_x = 0;
	int chip_size = 32;
	int map_width = 120;//3840
	int map_hight = 20;//640

	
	//std::unique_ptr<int[][map_width]> map(new int[map_hight][map_width]);

	//map[map_hight][map_width] = {
	//	{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
	//	{}
	//};
};
