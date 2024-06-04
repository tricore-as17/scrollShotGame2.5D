#include"DxLib.h"
#include"WorldSprite.h"

/// <summary>
/// ������
/// </summary>
/// <param name="textureGraph">�e�N�X�`���̉摜�n���h��</param>
/// <param name="chipPixelSize">�X�v���C�g�̂P�`�b�v�̃s�N�Z���T�C�Y</param>
/// <param name="spriteNo">�X�v���C�g�ԍ�</param>
void WorldSprite::Initialize(int textureGraph, int chipPixelSize, int spriteNo)
{
    //�}�b�v�̃`�b�v�O���t�����[���h�X�v���C�g�̃e�N�X�`���O���t�ɑ��
    this->textureGraph = textureGraph;

    // NOTE:���������ɌŒ肵�Ă��邪�A�ύX��������Ύ����Ŋ֐���ǉ�����K�v������
    // �S���_����uv�f�[�^��ݒ�
    int texW, texH;
    //�`�b�v�O���t�̏c�����Ɖ������̃T�C�Y���Q�b�g
    GetGraphTextureSize(textureGraph, &texW, &texH);
    //�������̃T�C�Y�������Đ����o��
    //���ƍ����͓����Ȃ̂ň��
    int chipXNum = texW / chipPixelSize;
    int chipYNum = texH / chipPixelSize;
    //������divgraph���蓮�ōs���Ă���݂����Ȋ���
    int chipNoX = spriteNo % chipXNum;       //��̎w��
    int chipNoY = spriteNo / chipXNum;       //�s�̎w��
    float oneChipUVXRate = 1.0f / (float)chipXNum;   // �e�N�X�`���S����1.0�Ƃ�������cihp��ɑ΂���uv�̃T�C�Y
    float oneChipUVYRate = 1.0f / (float)chipYNum;
    //�e�N�X�`���̍��W�̐ݒ�
    // 0.0�Ȃ�x1��������y1�@//1.0�Ȃ�x2��������y2
    //�e�N�X�`���𒣂�4�̍��W�����̍��W�̗�or�s��+
    Vertex[0].u = (chipNoX + 0.0f) * oneChipUVXRate;     //�`�b�v�̍����x���W
    Vertex[0].v = (chipNoY + 0.0f) * oneChipUVYRate;     //�`�b�v�̍����Y���W
    Vertex[1].u = (chipNoX + 1.0f) * oneChipUVXRate;     //�`�b�v�̉E���x���W
    Vertex[1].v = (chipNoY + 0.0f) * oneChipUVYRate;     //�`�b�v�̉E���y���W
    Vertex[2].u = (chipNoX + 0.0f) * oneChipUVXRate;     //�`�b�v�̍�����x���W
    Vertex[2].v = (chipNoY + 1.0f) * oneChipUVYRate;     //�`�b�v�̉E���y���W
    Vertex[3].u = (chipNoX + 1.0f) * oneChipUVXRate;     //�`�b�v�̉E����x���W
    Vertex[3].v = (chipNoY + 1.0f) * oneChipUVYRate;     //�`�b�v�̉E����y���W

    // �f�B�t���[�Y�A�X�y�L�����͏��������ɌŒ�(�����͋C�ɂ��Ȃ�)
    for (int i = 0; i < 4; i++)
    {
        Vertex[i].dif = GetColorU8(255, 255, 255, 255);
        Vertex[i].spc = GetColorU8(0, 0, 0, 0);
        Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);   // ��]���T�|�[�g���Ȃ��̂Ńm�[�}�����Œ�

        // �⏕�e�N�X�`�����T�|�[�g���Ȃ��̂�uv�Œ�
        Vertex[i].su = 0.0f;
        Vertex[i].sv = 0.0f;
    }

    // �Q�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 3;
    Index[4] = 2;
    Index[5] = 1;
}

/// <summary>
/// �T�C�Y�ƃ|�W�V�����ɉ����ĂS���_���̒��_�ʒu�𒲐�
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="chipSize">�z�u���郏�[���h�X�v���C�g�̃T�C�Y</param>
void WorldSprite::SetTransform(const VECTOR& pos, float spriteSize)
{
    this->pos = pos;
    // �s�{�b�g���S�Őݒ�
    //spriteSize��0.725
    //����A�E��A�����A�E���ɍ��W��ݒ�
    Vertex[0].pos = VScale(VGet(-1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
    Vertex[1].pos = VScale(VGet(1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
    Vertex[2].pos = VScale(VGet(-1.0, -1.0f, 0.0f), spriteSize * 0.5f);
    Vertex[3].pos = VScale(VGet(1.0f, -1.0f, 0.0f), spriteSize * 0.5f);
    for (int i = 0; i < 4; i++)
    {
        Vertex[i].pos = VAdd(Vertex[i].pos, pos);
    }
}

/// <summary>
/// �`��
/// </summary>
void WorldSprite::Draw()
{
    // �Q�|���S���̕`��
    //4�͒��_�̐�2���|���S���̐�
    DrawPolygonIndexed3D(Vertex, 4, Index, 2, textureGraph, TRUE);
}