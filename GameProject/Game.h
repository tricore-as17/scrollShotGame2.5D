#pragma once
#include<vector>

//�N���X�̃v���g�^�C�v�錾
class Player;
class Map;
class Gimmick;
class Utility;
class UI;
class BgModel;
class BG;
class Cloud;
class Player3DDraw;
class Gimmick3D;
class GroundDraw3D;
class Effect;
class EnemyManager;


class Game
{
public:

	//�萔
	static constexpr int CLEAR_EFFECT_NUM = 4;		//�N���A���̃G�t�F�N�g�̐�
	//�R���X�g���N�^�E�f�X�g���N�^
	Game();
	~Game();
	void GameStateChange();		//�Q�[���X�e�[�^�X���ڍs����ۂ̏���
	void Initialize();			//������
	//���C���`��̌�ɃT�u�̏���������K�v������̂ŕʁX�ɂ���
	void Update();				//���C����ʂ̍X�V����
	void Draw();				//���C����ʂ̕`��
private:
	//�v���C���[��}�b�v�Ȃǂ̃N���X���܂Ƃ߂�
	Player* player;
	Utility* utility;
	UI* ui;
	BgModel* bgModel;
	Camera* camera;
	BG *bg;
	Player3DDraw* player3D;
	Gimmick3D* gimmick3D;
	GroundDraw3D* groundDraw3D;
	Effect* gameOverEffect;
	Effect* clearCharaEffect;
	Map* map;
	EnemyManager* enemyManager;
	
	std::vector<Cloud*> cloud;
	std::vector<Gimmick*> gimmick;
	std::vector<Effect*>clearEffect;
	//�Q�[���̃X�e�[�^�X�֘A�i�X�N���[���X�s�[�h�Ȃ�)
	
	bool keyRelease = false;
	bool keyOn = false;
	bool prevKeyOn = false;
	int effectPlayCount = 0;
	bool keyStop = false;

};
