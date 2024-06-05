#pragma once

/// <summary>
/// 3D���W��ԂɃX�v���C�g��\������d�g�݁i�s�{�b�g�͒��S�Œ�A�摜��graph�͊O�ŊǗ��j
/// </summary>
class WorldSprite
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="textureGraph">�e�N�X�`���̉摜�n���h��</param>
	/// <param name="chipPixelSize">�X�v���C�g�̂P�`�b�v�̃s�N�Z���T�C�Y</param>
	/// <param name="spriteNo">�X�v���C�g�ԍ�</param>
	void Initialize(int textureGraph, int chipPixelSize, int spriteNo);
	/// <summary>
	/// �T�C�Y�ƃ|�W�V�����ɉ����ĂS���_���̒��_�ʒu�𒲐�
	/// </summary>
	/// <param name="pos">�|�W�V����</param>
	/// <param name="chipSize">�z�u���郏�[���h�X�v���C�g�̃T�C�Y</param>
	void SetTransform(const VECTOR& pos, float spriteSize);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//�Q�b�^�[
	const VECTOR& GetPos()const { return pos; }

private:
	int			textureGraph;	// �X�v���C�g���쐬���錳�e�N�X�`���̃O���t�B�b�N�n���h��
	VECTOR		pos;			// �`��|�W�V����
	VERTEX3D	Vertex[4];		// ���_�o�b�t�@
	WORD		Index[6];		// �C���f�b�N�X�o�b�t�@
};
