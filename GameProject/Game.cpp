#include<vector>
#include"DxLib.h"
#include"Player.h"
#include"Map.h"
#include"Utility.h"
#include"Camera.h"
#include"Effect.h"
#include"EnemyManager.h"
#include"Game.h"

//�R���X�g���N�^
Game::Game()
{
	//�N���X�̃C���X�^���X�̍쐬
	player = new Player();
	utility = new Utility();
	camera = new Camera();
	gameOverEffect = new Effect("Effect/BreakChara.efkefc");
	clearCharaEffect = new Effect("Effect/clearChara.efkefc");
	map = new Map();
	enemyManager = new EnemyManager();

\

	//�G�t�F�N�g�̓��I�m��
	for (int i = 0; i < CLEAR_EFFECT_NUM; i++)
	{
		clearEffect.emplace_back(new Effect("Effect/hitEffect.efkefc"));
	}

	
	
}
//�f�X�g���N�^
Game::~Game()
{
	//���
	delete player,utility,ui,bgModel,camera,bg,player3D,gameOverEffect,clearCharaEffect,map
		,enemyManager;
	player ,utility,ui,bgModel,camera,bg,player3D = nullptr;
	gimmick.clear();
	cloud.clear();
	clearEffect.clear();
}

//���ꂼ��̃X�e�[�^�X�Ɉڍs����ۂ�
void Game::GameStateChange()
{
	//�Q�[���X�e�[�^�X�̎擾
	int inGameState = utility->getGameState();
	//�v���C���[���W�̎擾
	switch (inGameState)
	{
	case STATE_TITLE:
		//�v���C���[�ƃM�~�b�N�̈ʒu�͖��񃊃Z�b�g
		//player->Init();
		utility->StartInit();
		break;
	case STATE_GAME:
		utility->StartInit();
		player->Init();
		map->Init();
		enemyManager->Init();
		break;
	case STATE_GAMECLEAR:

		break;
	case STATE_GAMEOVER:
		//�v���C���[�ƃM�~�b�N�̈ʒu�͖��񃊃Z�b�g
		player->Init();
		break;
	default:
		break;
	}




}

void Game::Initialize()
{
	player->Init();
	map->Init();
	camera->Init();
	enemyManager->Init();
}

void Game::Update()
{
	//�Q�[���X�e�[�^�X�̎擾
	int inGameState = utility->getGameState();
	//���[�J���ϐ��̐錾
	bool inGameOverFlag = false;//�Q�[���I�[�o�[�t���O
	bool inGameClearFlag = false;//�Q�[���N���A�t���O
	//�L�[����
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool inEffectPlayFlag = gameOverEffect->GetPlayFlag();
	int scrollSpeed = utility->getScrollSpeed();
	int elapsedTime = utility->getElapsedTime();


	keyRelease = false;
		// �L�[�������u�Ԃ����.
		if (keyOn)
		{
			//
			if (!(input & PAD_INPUT_10))
			{
				keyOn = false;
				keyRelease = true;
			}
		}
		else if (prevKeyOn == false && (input & PAD_INPUT_10))	//�L�[���ŏ��ɉ����ꂽ�^�C�~���O
		{
			keyRelease = false;
			keyOn = true;
		}
		if ((input & PAD_INPUT_10))	//�����������Ă��鎞�̏���
		{
			prevKeyOn = true;
		}
		else
		{
			prevKeyOn = false;
		}


	switch (inGameState)
	{
	case STATE_TITLE:


		break;
	case STATE_GAME:
		map->Update(player->GetKeepVelocity());
		player->Update(keyStop, *map);
		enemyManager->Update(*map, *player);
		camera->Update(*map,*player);
		break;
	case STATE_GAMEOVER:

		break;
	case STATE_GAMECLEAR:

		break;
	default:
		break;
	}

}

void Game::Draw()
{

	//�Q�[���X�e�[�^�X�̎擾
	int inGameState = utility->getGameState();
	int inElapsedTime = utility->getElapsedTime();
	switch (inGameState)
	{
	case STATE_TITLE:
		break;
	case STATE_GAME:
		map->Draw();
		player->Draw();
		enemyManager->Draw();

		break;
	case STATE_GAMECLEAR:

		break;
	case STATE_GAMEOVER:

		break;
	default:
		break;
	}
	

	
}





