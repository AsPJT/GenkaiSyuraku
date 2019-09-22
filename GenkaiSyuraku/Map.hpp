#pragma once

class Mob {
public:
	int image[4];
	int size = 32;
	int sizeX = 128;
	int sizeY = 256;
	int x = size * 93, y = size * 12;  //3008-32 384
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
	int x = size * 10, y = size * 20;
	int px = size * 10, py = size * 20;
	int bx, by;
	int bpx, bpy;
	int img;
	int img_num = 1;
	int muki = 3;
	int walking_flag = 0;
	int walking_ani = 1;
	int enter;
	int speed = 4;
};

class Map {
public:
	void init() {
		map_image[0] = LoadGraph("image/1.png", TRUE);
		map_image[1] = LoadGraph("image/2.png", TRUE);
		map_image[2] = LoadGraph("image/3.png", TRUE);
		icon_image = LoadGraph("image/icon.png", TRUE);
		hatake_image = LoadGraph("image/hatake3.png", TRUE);

		LoadDivGraph("image/player.png", 24, 6, 4, player.sizeX, player.sizeY, player.image);//�摜�𕪊�����image�z��ɕۑ�
		LoadDivGraph("image/ji.png", 4, 1, 4, mob[0].sizeX, mob[0].sizeY, mob[0].image);//�摜�𕪊�����image�z��ɕۑ�
	}

	void control(std::int_fast32_t key[256], std::uint_fast8_t& scene_id) {
		//�v���C���[�ړ�
		if (player.x % player.size == 0 && player.y % player.size == 0) {       //���W��32�Ŋ���؂ꂽ����͉\

			player.walking_flag = 1;                  //�����t���O�𗧂Ă�B
			player.enter = 0;
			if (key[KEY_INPUT_UP] > 0 && key[KEY_INPUT_LEFT] > 0)
				player.muki = 1;
			else if (key[KEY_INPUT_LEFT] > 0 && key[KEY_INPUT_DOWN] > 0)
				player.muki = 3;
			else if (key[KEY_INPUT_DOWN] > 0 && key[KEY_INPUT_RIGHT] > 0)
				player.muki = 5;
			else if (key[KEY_INPUT_RIGHT] > 0 && key[KEY_INPUT_UP] > 0)
				player.muki = 7;
			else if (key[KEY_INPUT_UP] > 0)    //��{�^���������ꂽ��
				player.muki = 0;                       //������t���O�𗧂Ă�
			else if (key[KEY_INPUT_LEFT] > 0)  //���{�^���������ꂽ��
				player.muki = 2;                       //�������t���O��
			else if (key[KEY_INPUT_DOWN] > 0)  //���{�^���������ꂽ��
				player.muki = 4;                       //�E�����t���O�𗧂Ă�
			else if (key[KEY_INPUT_RIGHT] > 0) //�E�{�^���������ꂽ��
				player.muki = 6;                       //�������t���O��
			else if (key[KEY_INPUT_RETURN] > 0) //�G���^�[�L�[�������ꂽ��
				player.enter = 1, player.walking_flag = 0;             //��b�t���O��
			else                                //���̃{�^����������ĂȂ�������
				player.walking_flag = 0;              //�����Ȃ��t���O�𗧂Ă�
		}

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
		
			if (player.x <= 1980 / 2 - player.size || player.x >= 1980 + 1980 / 2 - player.size) {   //�v���C���[�̂ݓ�����
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
			else {  //�w�i��Ǐ]������
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
		
		if (player.x <= 1980 / 2 - player.size || player.x >= 1980 + 1980 / 2 - player.size)
			//background_x = -player.x+;

		//�ړ��͈�
		if (player.x < 0) player.x = player.bx, player.px = player.bpx;
		else if (player.x > player.size*98 && player.px > player.size * 36) player.x = player.bx, player.px = player.bpx;
		if (player.y < 0) player.y = player.by, player.py = player.bpy;
		else if (player.y > player.size*26) player.y = player.by, player.py = player.bpy;
		
		//Mob�Ƃ̓����蔻��
		for (i = 0; i < 1; i++) {
			if (player.x + player.sizeX / 2 > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX / 2 &&
				player.y + player.sizeY / 4 > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY / 4) {
				player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
			}
		}
		
		//�v���C���[�̕��s�A�j���[�V����
		if(player.x % 32 == 0 && player.x % 32 == 0) player.img = player.image[player.img_num];
		else if(player.walking_ani == 1) player.img = player.image[player.img_num + 1], player.walking_ani = 0;
		else player.img = player.image[player.img_num - 1], player.walking_ani = 1;

		//if(player.x % player.size*2 >= 32 || player.y % player.size*2 >= 32 ) player.img = player.image[player.img_num + 1];
		//else if (player.x % player.size >= 1 || player.y % player.size >= 1) player.img = player.image[player.img_num - 1];
		//else player.img = player.image[player.img_num];

		//�w�i�Ɛl���̕`��
		DrawGraph(background_x, 0, map_image[map_level], TRUE);  //�w�i��`��
		for(i=0;i<1;i++)
			if (mob[i].y <= player.y) 
				if(mob[i].x > player.x-1980 && mob[i].x < player.x+1980) DrawGraph(mob[0].x + background_x, mob[0].y, mob[0].image[0], TRUE);                     //ji��`��
		DrawGraph(player.px, player.py, player.img, TRUE);                                                      //�v���C���[��`��
		for (i = 0; i < 1; i++) 
			if (mob[i].y > player.y)
				if (mob[i].x > player.x-1980 && mob[i].x < player.x + 1980)  DrawGraph(mob[0].x + background_x, mob[0].y, mob[0].image[0], TRUE);  //ji��`��

		//Mob�ɋ߂Â��ƃA�C�R�����o��
		if (player.x + player.sizeX > mob[i].x &&
			player.x < mob[i].x + mob[i].sizeX &&
			player.y + player.sizeY > mob[i].y &&
			player.y < mob[i].y + mob[i].sizeY) {
			DrawGraph(mob[0].x + background_x-64, mob[0].y-200, icon_image, TRUE);  //�A�C�R����`��
			//�߂Â�����ԂŘb��������
			if (player.enter == 1) {
				//printfDx("TALK\n");
				if (talk == 0) {
					scene_id = 3;
					talk = 1;
				}
			}
		}
		//DrawGraph(200, 850, hatake_image, TRUE);  //�͂�����`��
		//DrawGraph(328, 850, hatake_image, TRUE);  //�͂�����`��
		//DrawGraph(456, 850, hatake_image, TRUE);  //�͂�����`��
		
		//printfDx("%d %d \n", player.x, player.y);
		player.bpx = player.px;
		player.bpy = player.py;
		player.bx = player.x;
		player.by = player.y;

	}

private:
	Mob mob[5];
	Player player;
	int i;
	int talk = 0;
	int map_level = 0;
	int map_image[3];
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
