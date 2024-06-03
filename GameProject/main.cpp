#include"DxLib.h"
#include"Utility.h"
#include"Camera.h"
#include"Effect.h"
#include"Game.h"
#include"EffekseerForDXLib.h"

//----------------------------//
// WinMain�֐�.
//----------------------------//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_W, SCREEN_H, 16);		// �𑜓x��SCREEN_W*SCREEN_H�Acolor��16bit�ɐݒ�.




	/////////////////////////////////
	// �E�C���h�E���[�h��(�R�����g�A�E�g������t���X�N���[��).
	ChangeWindowMode(TRUE);
	////////////////////////////

	SetCameraNearFar(0.0f, 500.0f);	//near��far�̐ݒ�

		// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//�G�t�F�N�g�̏����ݒ�
	if (Effect::Setting() == -1)
	{
		DxLib_End();
		return -1;
	}

	

	// �w�i�̃X�N���[�������邽�߂Ƀe�N�X�`�����[�h�����b�s���O�ɏC��.
	//SetTextureAddressMode(DX_TEXADDRESS_WRAP);

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g


	Utility::FpsInit();
	Game* game = new Game;

	game->Initialize();

	



	// �Q�[�����[�v.
	while (1)
	{
		Utility::FpsUpdate();
		// ��ʂ�������(�^�����ɂ���)
		SetCameraNearFar(10.0f, 500.0f);	//near��far�̐ݒ�
		ClearDrawScreen();
		game->Update();
		game->Draw();

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);


		/*int nowTime = GetNowCount();
		DrawFormatString(600, 400, GetColor(255, 255, 255), "%d", nowTime);*/

		// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// �}�C�i�X�̒l�i�G���[�l�j���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0)
		{
			break;
		}
		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		else if ( CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
		//������FPS�̒���
		Utility::FpsControll();
		
	};
	//gameFinalize(game);
	// Effekseer���I������B
	Effkseer_End();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}