#include"Player.h"
#include"Colision.h"
#include"Utility.h"

//�R���X�g���N�^
Player::Player():isHitTop(false),isGround(false)
{
	//���W�̏�����
	pos = VGet(FIRST_X, FIRST_Y, 0);
	dir = VGet(0, 0, 0);
	fallSpeed = 0;
	playTime = 0.0f;
	//���f���n���h���ɑ��
	modelHandle = MV1LoadModel("mv1/Player/playerModel.mv1");
	//���f���̃T�C�Y��ݒ�
	MV1SetScale(modelHandle, VGet(0.02f, 0.02f, 0.02f));
	//���f���̉�]�l��ݒ�(y����90�x��]������);
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, -110.0f * DX_PI_F / 180.0f, 0.0f));
	//3D���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	attachIndex = MV1AttachAnim(modelHandle, IDLE, -1, FALSE);
	//�A�^�b�`�����A�j���V�����̑��Đ����Ԃ��擾
	totalAnimeTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
}
//�f�X�g���N�^
Player::~Player()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// �Q�[���J�n���̏�����
/// </summary>
void Player::Init()
{
	//���W�̏������ƈړ������̏�����
	pos = VGet(FIRST_X, FIRST_Y, 0);
	dir = VGet(0, 0, 0);
	fallSpeed = 0;
	isHitTop, isGround = false;
	//�A�j���[�V�����֘A�̏�����
	playTime = 0.0f;
	for (int i = 0; i < ANIME_STATE_SUM; i++)
	{
		if (i == IDLE)
		{
			animeState[i] = true;
		}
		animeState[i] = false;
	}

}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update(bool keyStop,const Map &map)
{
	// ���͏�Ԃ��X�V
// �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �v���C���[�̈ړ�����
	// ���E�̈ړ��������o��
	dir = VGet(0, 0, 0);
	if (input & PAD_INPUT_LEFT && keyStop == false)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}
	if (input & PAD_INPUT_RIGHT && keyStop == false)
	{
		dir = VAdd(dir, VGet(1, 0, 0));
	}

	// ���K��
	if (VSquareSize(dir) > 0)		//dir�̃T�C�Y��2��ɂ��ĕԂ�(���ɂ��邱�Ƃ�dir�ɒl�������Ă����if�ɓ���
	{
		dir = VNorm(dir);			//�e�����̃T�C�Y���P�ɂ���
	}

	// �ړ��ʂ��o��
	auto velocity = VScale(dir, SPEED);		//dir�̊e������speed���|����

	fallSpeed += Utility::GRAVITY;

	// HACK: ��ɐݒ蔻������邱�Ƃ�fallSpeed�C���{�ڒn�t���O�X�V
	PlayerColision::CheckIsGround(*this, map);
	PlayerColision::CheckIsTopHit(*this, map);

	// �������x���X�V

	// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
	if (((isGround && !isHitTop)) && (input & PAD_INPUT_A) && keyStop == false)
	{
		fallSpeed = -JUMP_POWER;	// �W�����v�{�^�����������瑦���ɏ�����̗͂ɑ���
		isGround = false;			//�ڒn�����؂�
	}

	// �������x���ړ��ʂɉ�����
	auto fallVelocity = VGet(0, fallSpeed, 0);	// �������x�N�g���ɁBy���W�����ω����Ȃ��̂ōŌ�Ƀx�N�g���ɂ���
	velocity = VAdd(velocity, fallVelocity);

	// �����蔻������āA�ǂɂ߂荞�܂Ȃ��悤��velocity�𑀍삷��
	velocity = PlayerColision::CheckPlayerHitWithMap(*this, map, velocity);
	
	//FIXME:�}�b�v���X�N���[�����邽�߂Ɏg�p���Ă��邪���̎g�p�͎��߂��̂�
	//�o���l��ۑ�����
	keepVelocity = velocity;

	// �ړ�
	pos = VAdd(pos, velocity);
	//3D���f����`�悳���邽�߂Ɉʒu�𒲐�����
	drawPos = VGet(pos.x+10,pos.y+60,0.7f);
	pos3D = ConvScreenPosToWorldPos(drawPos);
	MV1SetPosition(modelHandle, pos3D);



	//�A�j���[�V�����̐ݒ�
	if (velocity.x != 0)
	{
		AnimeSet(RUN);
	}
	else
	{
		//�ҋ@��Ԃ̃A�j���[�V�����ɂ���
		AnimeSet(IDLE);

	}

	//�A�j���[�V�����J�E���g�̍X�V(1��̍Đ����Ԃ𒴂����烊�Z�b�g)
	playTime += 0.7f;
	if (playTime >= totalAnimeTime)
	{
		playTime = 0.0f;
	}
	//�Đ����Ԃ̃Z�b�g
	MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);



	
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{

	//DrawBox(pos.x, pos.y, pos.x + PLAYER_W, pos.y + PLAYER_H, GetColor(255, 255, 255), FALSE);
	MV1DrawModel(modelHandle);

}

/// <summary>
/// �A�j���[�V�����t���O��S��false��
/// </summary>
void Player::ResetAnimeFlag()
{
	for (int i = 0; i < ANIME_STATE_SUM; i++)
	{
		animeState[i] = false;
	}
}

/// <summary>
/// �A�j���[�V�����̃Z�b�g
/// </summary>
/// <param name="setState">�Z�b�g����X�e�[�g</param>
void Player::AnimeSet(int setState)
{
	//���݂��̃A�j���[�V�������Đ�����Ă��Ȃ���΃Z�b�g
	if (animeState[setState]!= true)
	{
		MV1DetachAnim(modelHandle, attachIndex);
		//3D���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
		attachIndex = MV1AttachAnim(modelHandle, setState, -1, FALSE);
		//�A�^�b�`�����A�j���V�����̑��Đ����Ԃ��擾
		totalAnimeTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
		playTime = 0.0f;
		//��x�A�j���[�V�����t���O�����Z�b�g
		ResetAnimeFlag();
		animeState[setState] = true;
	}
}


