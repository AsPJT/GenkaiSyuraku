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
	int x = size * 25, y = size * 20; //x��3940�ȓ���32�̔{���Ŏw��
	int px = size * 25, py = size * 20; //x��832~2752�̂Ƃ���832�Œ�
	int bx, by;
	int bpx, bpy;
	int img;
	int img_num = 1;
	int muki = 3;
	int walking_flag = 0;
	int walking_ani = 0;
	int walking_ani_flag = 0;
	int speed = 4;
	int money = 1000;
};

class Item {
public:
	char name[32];
	char effect[64];
	int num = 0;
};

class Map {
public:
	void init() {
		map_image = LoadGraph("image/map.png", TRUE);
		sakanaya_image[0] = LoadGraph("image/sakanaya1.png", TRUE);
		sakanaya_image[1] = LoadGraph("image/sakanaya2.png", TRUE);
		sakanaya_image[2] = LoadGraph("image/sakanaya3.png", TRUE);
		yorozuya_image[0] = LoadGraph("image/yorozuya1.png", TRUE);
		yorozuya_image[1] = LoadGraph("image/yorozuya2.png", TRUE);
		yorozuya_image[2] = LoadGraph("image/yorozuya3.png", TRUE);
		icon_image = LoadGraph("image/ex_icon.png", TRUE);
		fish_icon_image = LoadGraph("image/fish_icon.png", TRUE);
		area_icon_image = LoadGraph("image/area_icon.png", TRUE);
		menu_image = LoadGraph("image/menu.png", TRUE);
		selector_image = LoadGraph("image/selector.png", TRUE);
		textwindow_image = LoadGraph("image/textwindow.png", TRUE);
		hatake_image = LoadGraph("image/hatake3.png", TRUE);
		bgm = LoadSoundMem("music/genkaivillage.wav");

		LoadDivGraph("image/player.png", 24, 6, 4, player.sizeX, player.sizeY, player.image);//�摜�𕪊�����image�z��ɕۑ�
		LoadDivGraph("image/ji.png", 4, 1, 4, mob[0].sizeX, mob[0].sizeY, mob[0].image);//�摜�𕪊�����image�z��ɕۑ�
		LoadDivGraph("image/ba.png", 4, 1, 4, mob[1].sizeX, mob[1].sizeY, mob[1].image);//�摜�𕪊�����image�z��ɕۑ�

		//Font
		FontHandle = CreateFontToHandle(NULL, 50, 2, DX_FONTTYPE_EDGE);
		FontHandle_big = CreateFontToHandle(NULL, 70, 2, DX_FONTTYPE_EDGE);

		//�������̏����ʒu
		mob[0].x = mob[0].size * 43;
		mob[0].y = mob[0].size * 12;
		mob[0].img = mob[0].image[0];

		//���΂��̏����ʒu
		mob[1].x = mob[1].size * 20;
		mob[1].y = mob[1].size * 12;
		mob[1].img = mob[1].image[0];

		//item
		item[0].num = 0;
		//item[0].name = "�g�}�g�̎�";

	}

	void control(bool up_key[], std::int_fast32_t key[256], std::uint_fast8_t& scene_id, std::uint_fast32_t fished_count, std::uint_fast32_t go_fish_count, int& yorozuya_level, int& sakanaya_level) {
		//�L�[����
		eflag = 0;
		returnflag = 0;
		if (player.x % player.size == 0 && player.y % player.size == 0) {       //���W��32�Ŋ���؂ꂽ����͉\
			player.walking_flag = 1;                  //�����t���O�𗧂Ă�B
			if ((key[KEY_INPUT_UP] > 0 && key[KEY_INPUT_LEFT] > 0) || (key[KEY_INPUT_W] > 0 && key[KEY_INPUT_A] > 0))
				player.muki = 1;
			else if (key[KEY_INPUT_LEFT] > 0 && key[KEY_INPUT_DOWN] > 0 || (key[KEY_INPUT_A] > 0 && key[KEY_INPUT_S] > 0))
				player.muki = 3;
			else if (key[KEY_INPUT_DOWN] > 0 && key[KEY_INPUT_RIGHT] > 0 || (key[KEY_INPUT_S] > 0 && key[KEY_INPUT_D] > 0))
				player.muki = 5;
			else if (key[KEY_INPUT_RIGHT] > 0 && key[KEY_INPUT_UP] > 0 || (key[KEY_INPUT_D] > 0 && key[KEY_INPUT_W] > 0))
				player.muki = 7;
			else if (key[KEY_INPUT_UP] > 0 || key[KEY_INPUT_W] > 0)    //��{�^���������ꂽ��
				player.muki = 0;                       //������t���O�𗧂Ă�
			else if (key[KEY_INPUT_LEFT] > 0 || key[KEY_INPUT_A] > 0)  //���{�^���������ꂽ��
				player.muki = 2;                       //�������t���O��
			else if (key[KEY_INPUT_DOWN] > 0 || key[KEY_INPUT_S] > 0)  //���{�^���������ꂽ��
				player.muki = 4;                       //�E�����t���O�𗧂Ă�
			else if (key[KEY_INPUT_RIGHT] > 0 || key[KEY_INPUT_D] > 0) //�E�{�^���������ꂽ��
				player.muki = 6;                       //�������t���O��
			else                                      //���̃{�^����������ĂȂ�������
				player.walking_flag = 0;              //�����Ȃ��t���O�𗧂Ă�
		}		

		//��낸��
		if (talk == 2) {
			if (up_key[KEY_INPUT_RETURN] > 0 && returnflag == 0) {
				returnflag = 1;
				talk = 0;
			}
		}
		//���j���[���
		if (up_key[KEY_INPUT_E] > 0 && menu == 1 && eflag == 0 && talk == 0) {
			menu = 0;
			eflag = 1;
		}
		else if ((up_key[KEY_INPUT_E] > 0 || menu == 1) && eflag == 0 && talk == 0) {
			eflag = 1;
			player.walking_flag = 0;
			menu = 1;
			if (up_key[KEY_INPUT_UP] > 0 || up_key[KEY_INPUT_W] > 0) select--, selector_y -= 175;
			else if (up_key[KEY_INPUT_DOWN] > 0 || up_key[KEY_INPUT_S] > 0) select++, selector_y += 175;
			if (select > 3) select = 0, selector_y -= 700;
			if (select < 0) select = 3, selector_y += 700;
			//����
			if (up_key[KEY_INPUT_RETURN] > 0 && returnflag == 0) {
				returnflag = 1;
				if (select == 0) select = 0;
				if (select == 1) select = 1;
				if (select == 2) select = 2;
				if (select == 3) scene_id = 1, menu = 0;
			}
		}
		else {
			for (i = 0; i < mob_num; i++) {
				if (player.x + player.sizeX * 2 > mob[i].x &&
					player.x < mob[i].x + mob[i].sizeX * 2 &&
					player.y + player.sizeY > mob[i].y &&
					player.y < mob[i].y + mob[i].sizeY) {
					//�߂Â�����ԂŘb��������
					if (talk >= 1 && (up_key[KEY_INPUT_RETURN] > 0 && returnflag == 0)) {
						talk = 0;
					}
					else if ((up_key[KEY_INPUT_RETURN] > 0 && returnflag == 0) || talk >= 1) {
						returnflag = 1;
						player.walking_flag = 0;

						if (talk == 0) {
							talk = i+1;
							//���u�̐U�����
							if (player.x + player.sizeX/2 < mob[i].x) mob[i].img = mob[i].image[1];
							else if (player.x + player.sizeX/2 > mob[i].x + player.sizeX) mob[i].img = mob[i].image[2];
							//else if (player.y < mob[i].y + mob[i].sizeY / 4) mob[i].img = mob[i].image[3];
							else mob[i].img = mob[i].image[0];
						}
					}
				}
				//�ނ��ڍs
				else if (player.x > tsuri_area) {
					if (up_key[KEY_INPUT_RETURN] > 0 && returnflag == 0) {
						returnflag = 1;
						StopSoundMem(bgm);
						scene_id = 3;
					}
				}
			}
		}

		//�ړ�����
		if (player.walking_flag == 1) {       //�����t���O�������Ă�����
			if (player.muki == 0)             //������Ȃ�y���W�����炷
				player.y-= player.speed, player.img_num = 19;
			else if (player.muki == 1)
				player.x-= player.speed, player.y-= player.speed, player.img_num = 16;
			else if (player.muki == 2)        //�������Ȃ�x���W�����炷
				player.x-= player.speed, player.img_num = 7;
			else if (player.muki == 3)
				player.x-= player.speed, player.y+= player.speed, player.img_num = 4;
			else if (player.muki == 4)        //�������Ȃ�y���W�𑝂₷
				player.y+= player.speed, player.img_num = 1;
			else if (player.muki == 5)
				player.x+= player.speed, player.y+= player.speed, player.img_num = 10;
			else if (player.muki == 6)        //�E�����Ȃ�x���W�𑝂₷
				player.x+= player.speed, player.img_num = 13;
			else if (player.muki == 7)
				player.x+= player.speed, player.y-= player.speed, player.img_num = 22;
		
			if (player.x <= map_width / 2 - player.sizeX || player.x >= map_width + map_width / 2 - player.sizeX) {   //�v���C���[�̂ݓ�����
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
			else {  //�w�i��Ǐ]������(�v���C���[��x���W�Œ�)
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

		//�J�����Ǐ]
		if (player.x <= map_width / 2 - player.sizeX) background_x = 0;
		else if (player.x >= map_width + map_width / 2 - player.sizeX) background_x = -map_width;
		else background_x = map_width / 2 - player.sizeX - player.x;

		//�i���֎~�G���A�̎w��
		if (player.x < 0) player.x = player.bx, player.px = player.bpx;
		else if (player.x > player.size*110 && player.px > player.size * 48) player.x = player.bx, player.px = player.bpx;
		if (player.y < player.size * 11) player.y = player.by, player.py = player.bpy;
		else if (player.y > player.size*26) player.y = player.by, player.py = player.bpy;
		
		//Mob�Ƃ̓����蔻��
		for (i = 0; i < mob_num; i++) {
			if (player.x + player.sizeX > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX &&
				player.y + player.sizeY / 4 > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY / 4) {
				player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
			}
		}
		
		//�v���C���[�̕��s�A�j���[�V����
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
			
		//printfDx("%d \n", fished_count);
		//DrawGraph(200, 850, hatake_image, TRUE);  //�͂�����`��
		//DrawGraph(328, 850, hatake_image, TRUE);  //�͂�����`��
		//DrawGraph(456, 850, hatake_image, TRUE);  //�͂�����`��
		
		//���[�h���ڌ�̃t���O����
		if (go_fish_count != go_fish_before) {
			sakana_total += fished_count;
			bgm_flag = 0;
		}

		//�W�����x���̊Ǘ�
		if (sakana_total >= 100) sakanaya_level = 2;
		else if (sakana_total >= 30) sakanaya_level = 1;
		
        //BGM�Đ�
		if (bgm_flag == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
			bgm_flag = 1;
		}

		//�O�t���[���̃f�[�^���L�^
		player.bpx = player.px;
		player.bpy = player.py;
		player.bx = player.x;
		player.by = player.y;
		go_fish_before = go_fish_count;

		Draw(yorozuya_level, sakanaya_level);
	}

	void Draw(int yorozuya_level, int sakanaya_level) {
		//�w�i��`��
		DrawGraph(background_x, 0, map_image, TRUE);
		DrawGraph(background_x, 0, yorozuya_image[yorozuya_level], TRUE);
		DrawGraph(background_x, 0, sakanaya_image[sakanaya_level], TRUE);

		//��G���A�̃A�C�R���\��
		if (player.x > tsuri_area) {
			DrawGraph(0, 0, area_icon_image, TRUE);
			DrawGraph(tsuri_area + background_x - 400, -250, fish_icon_image, TRUE);
			DrawFormatStringToHandle(1050, 200, GetColor(0, 0, 0), FontHandle, "Enter�L�[�Œނ�G���A��");
		}
		//�������̃A�C�R����`��
		DrawGraph(mob[0].x + background_x - 64, mob[0].y - 200, icon_image, TRUE);

		//����̃L��������\��
		for (i = 0; i < mob_num; i++)
			if (mob[i].y <= player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width) DrawGraph(mob[i].x + background_x, mob[i].y, mob[i].img, TRUE);//ji��`��
		DrawGraph(player.px, player.py, player.img, TRUE);   //�v���C���[��`��
		for (i = 0; i < mob_num; i++)
			if (mob[i].y > player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width)  DrawGraph(mob[i].x + background_x, mob[i].y, mob[i].img, TRUE);  //ji��`��
		
		//���j���[�̕`��
		if (menu == 1) {
			DrawGraph(0, 0, menu_image, TRUE);
			DrawGraph(-25, selector_y, selector_image, TRUE);
		}

		//�e�L�X�g�{�b�N�X
		if(talk >= 1) {
			DrawGraph(0, 0, textwindow_image, TRUE);
			if (talk == 1) {
				DrawFormatStringToHandle(130, 815, GetColor(255, 255, 255), FontHandle, "�ނ��s���Ēނ��s���Ēނ��s���Ēނ��s���Ēނ��s����");
				DrawFormatStringToHandle(130, 875, GetColor(255, 255, 255), FontHandle, "�ނ��s���Ēނ��s���Ēނ��s���Ēނ��s���Ēނ��s����");
				DrawFormatStringToHandle(240, 730, GetColor(255, 255, 255), FontHandle, "�c��");
			}
			else if (talk == 2) {
				DrawFormatStringToHandle(130, 815, GetColor(255, 255, 255), FontHandle, "�Ȃ񂩔����H");
				DrawFormatStringToHandle(130, 875, GetColor(255, 255, 255), FontHandle, "");
				DrawFormatStringToHandle(190, 730, GetColor(255, 255, 255), FontHandle, "��낸��");
			}
		}
		
	}

private:
	Mob mob[2];
	Player player;
	Item item[10];

	std::uint_fast32_t go_fish_before = 0;
	int i;
	int mob_num = 2;
	int select = 0;
	int FontHandle;
	int FontHandle_big;
	int sakana_total = 0;

	//flag
	int bgm, bgm_flag = 0;
	int talk = 0;
	int menu = 0;
	int eflag = 0;
	int returnflag = 0;

	//image
	int map_image;
	int sakanaya_image[3];
	int yorozuya_image[3];
	int area_icon_image;
	int fish_icon_image;
	int icon_image;
	int menu_image;
    int selector_image;
	int textwindow_image;
	int hatake_image;

	//���W
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
