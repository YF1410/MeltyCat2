#include "DxLib.h"
#include "Player.h"
#include "Block.h"
#include "Item.h"
#include "Cursor.h"

#include "GameStart.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "MeltyCat";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 768;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x80, 0x80, 0xFF);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int buck = LoadGraph("graphic/buckground.png");//start�w�i
	int game_name[8];//�Q�[����
	LoadDivGraph("graphic/MeltyCat.png", 8, 8, 1, 64, 64, game_name);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int frame = 0;

	int scene = 0;
	
	//start�Ŏg�p����
	int buck_pos_x = 0,buck_pos_y = 0;//�w�i���W

	//�w�i�̃p�[�e�B�N��
	const int staet_particle_num = 200;
	GameStart gamestart[staet_particle_num];

	//�Q�[�����ړ�
	float name_x[8], name_y[8];
	int name_flag[8];
	int name_count = 0;
	float name_move[8];
	for (int i = 0; i < 8; i++)
	{
		if (i < 5)
		{
			name_x[i] = 200 + i * 100;
		} else
		{
			name_x[i] = 350 + i * 100;
		}
		name_y[i] = -70;
		name_move[i] = 0;
		name_flag[i] = 0;
	}
	
	/*Player*/
	enum Cat { SOLID/*�ő�*/, LIQUID/*�t��*/ };
	Player* player = new Player(800, 352, 32, 2, 0, SOLID);
	/*Item*/
	Item* item = new Item(1120, 160, 8, 1);
	/*PlayArea*/
	const int edgeL = 320;
	/*JampBlock*/
	enum Jamp { LU, LD, RD, RU };/*Left,Right,Up,Down*/
	Block* block = new Block(0, 0, 32, 0, LU);
	/*Cursor*/
	Cursor* cursor = new Cursor(0, 0, 32, 0, 0, LU);

	/*MapChip*/
	int map[12][15] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };
	int click = 0;

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };
	int oldclick = 0;

	// �Q�[�����[�v
	while (1) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		oldclick = click;
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);
		click = GetMouseInput();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		frame++;

		//�X�^�[�g���
		if (scene == 0)
		{
			if (frame == 1)
			{
				for (int i = 0; i < staet_particle_num; i++)
				{
					gamestart[i].start(i);
				}
			}

			//�薼
			if (frame % 30 == 1 && name_y[name_count] < -60 && name_flag[name_count] == 0)
			{
				name_flag[name_count] = 1;
				name_move[name_count] = 10;
				name_count++;
				if (name_count == 8)
				{
					name_count = 0;
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if (name_flag[i] == 1)
				{
					name_move[i] = name_move[i] * 1.09;
				}

				if (name_y[i] + name_move[i] > 330)
				{
					name_flag[i] = 2;
				}
			}
			
			for (int i = 0; i < staet_particle_num; i++)
			{
				gamestart[i].update();
			}
			if (keys[KEY_INPUT_SPACE] == true)
			{
				scene = 1;
			}
		}

		if (scene == 2)
		{
			player->Update(edgeL, WIN_WIDTH, WIN_HEIGHT, block, item);
			block->Update();
			item->Update();
			cursor->Update(edgeL, keys, oldkeys, click, oldclick, block, WIN_WIDTH, WIN_HEIGHT);
		}
		
		// �`�揈��
		if (scene == 0)
		{
			//�w�i
			DrawGraph(buck_pos_x, buck_pos_y, buck, true);
			//�p�[�e�B�N��
			for (int i = 0; i < staet_particle_num; i++)
			{
				gamestart[i].draw(i);
			}
			//�Q�[����
			for (int i = 0; i < 8; i++)
			{
				DrawRotaGraph(name_x[i], name_y[i] + name_move[i], 1.6, 0, game_name[i], true);
			}
		}

		/*PlaeArea*/
		if (scene == 2)
		{
			DrawBox(edgeL, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 192, 192), true);
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 12; j++) {
					DrawBox(i * 64 + edgeL, j * 64, (i + 1) * 64 + edgeL, (j + 1) * 64, GetColor(255, 255, 255), false);
				}
			}
			cursor->Draw(edgeL, WIN_WIDTH, WIN_HEIGHT);
			block->Draw();
			item->Draw();
			player->Draw();
		}
		/*�f�o�b�O�R�[�h*/
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", name_y[0] + name_move[0]);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}