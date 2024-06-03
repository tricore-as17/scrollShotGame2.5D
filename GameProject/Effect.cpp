#include"EffekseerForDXLib.h"
#include"Effect.h"

//�R���X�g���N�^
Effect::Effect(const char* fileName) :playTime(0), pos(VGet(0.0f, 0.0f, 0.0f)), playFlag(false), playHandle(-1)
{
	//�n���h���̓ǂݍ���
	handle = LoadEffekseerEffect(fileName, 1.5f);
}
//�f�X�g���N�^
Effect::~Effect()
{
	//�G�t�F�N�g���\�[�X�̍폜
	DeleteEffekseerEffect(handle);
}
//�G�t�F�N�g��\�����鎞�̏����ݒ�
int Effect::Setting()
{
	//Effekseer�����悤����ۂ�DirectX11���g����悤�ɂ���K�v������
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	//Effekseer�̏�����
	if (Effekseer_Init(8000) == -1)
	{
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �؂�ւ��͍s��Ȃ����ꉞ�Z�b�e�B���O
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	//Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);
	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);
	return 0;
}
