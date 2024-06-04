#include"DxLib.h"
#include"Colision.h"
#include"GameObject.h"
#include"Player.h"
#include"EasyEnemy.h"
#include"Map.h"

VECTOR PlayerColision::CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity)
{
	// �T�C�Y���ŏ�����0�Ȃ瓮����������return
	if (VSize(velocity) == 0)		//VSize�Ńx�N�g���̃T�C�Y���Ƃ��Ă���0�Ȃ瓮���ĂȂ��Ȃ̂ł����ŕԂ�
	{
		return velocity;
	}
	//�Q�b�^�[�Ő��l��ϐ��ɑ��
	//���Əc�̃}�b�v�`�b�v�̐��������Ă���
	int mapXNum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//�v���C���[�̍��W�������Ă���
	VECTOR playerPos = player.GetPos();
	//�}�b�v�f�[�^�������Ă���
	int** mapData = map.getMapData();
	VECTOR mapLeftPos = map.GetChipLeftPos();



	VECTOR ret = velocity;

	// ������Ȃ��Ȃ�܂ŌJ��Ԃ�
	bool loop = true;
	bool isFirstHit = true;	// ����œ���������
	while (loop)
	{
		loop = false;

		// �����̃v���C���[�̃|�W�V�������܂��o��
		VECTOR futurePos = VAdd(playerPos, ret);

		// �S�}�b�v�`�b�v���J��Ԃ�
		for (int hIndex = 0; hIndex <mapYNum; hIndex++)
		{
			bool isHit = false;
			for (int wIndex = 0; wIndex < mapXNum; wIndex++)
			{
				//�}�b�v�`�b�v���ꂼ��̍��W���擾
				VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex+mapLeftPos.x, Map::CHIP_SIZE * (-hIndex -1)  + mapLeftPos.y, 0);
				//�}�b�v�`�b�v�ƃv���C���[�̓����蔻����݂�
				isHit = IsHitPlayerWithMapChip(player, futurePos, mapData[hIndex][wIndex],mapChipPos);

				// ����ɓ��������Ƃ�
				if (isHit && isFirstHit)
				{
					// ���㓖���蔻��Ń|�W�V������velocity�̕␳������Ƃ��A�����_�ȉ��̌덷���Y�܂��
					// �G��1�h�b�g�����炷�A���w�v�Z�����Ȃ��}�b�V�u�����蔻��ɂ͎ז��Ȃ̂ŏ���Ɋۂ߂Ă��܂��A
					// �ȍ~���߂ē����蔻��
					// pos��Velocity���ۂ߂�
					//playerPos.x = floorf(playerPos.x);		//floorf�͏����_���ۂ߂�
					//playerPos.y = floorf(playerPos.y);
					player.SetPos(playerPos);
					//ret.x = floorf(ret.x);
					//ret.y = floorf(ret.y);
					isFirstHit = false;
					loop = true;	// ���[�v�p��
				}

				// �����������_�Ń}�b�v�`�b�v�̃��[�v����ʂ��邪�A������Ȃ��Ȃ�܂ŌJ��Ԃ����[�v�͌p��
				if (isHit && !isFirstHit)
				{
					// HACK: �������Ă����ꍇ��velocity��1�h�b�g���k�߂Ă����A������Ȃ��Ȃ�܂ŌJ��Ԃ�
					// ���̂܂܏k�߂Ă��܂��ƁA�΂߂̃x�N�g���̂Ƃ��i�Ⴆ�ΕǂɌ������ăW�����v�����Ƃ��j�ɃW�����v�̐������k�߂Ă��܂�
					// �����h�����߂ɁA
					// ����������k�߂Ă������ƂŁA�����������
					float absX = fabsf(ret.x);	// velocity��x�����̐�Βl
					float absY = fabsf(ret.y);	// velocity��y�����̐�Βl

					// x�������k�ߐ؂��Ă��Ȃ����x�������k�߂�
					bool shrinkX = (absX != 0.0f);	// x�������k�߂邩�ǂ���

					if (shrinkX)
					{
						if (ret.x > 0.0f)
						{
							ret.x -= Map::ONE_PIXEL_SIZE;
						}
						else
						{
							ret.x += Map::ONE_PIXEL_SIZE;
						}

						// �k�ߐ؂��������
						if (fabs(ret.x) < Map::ONE_PIXEL_SIZE)
						{
							ret.x = 0.0f;
						}
						loop = true;
					}
					else
					{
						if (ret.y > 0.0f)
						{
							ret.y -= Map::ONE_PIXEL_SIZE;
						}
						else
						{
							ret.y += Map::ONE_PIXEL_SIZE;
						}

						// �k�ߐ؂��������
						if (fabs(ret.y) < Map::ONE_PIXEL_SIZE)
						{
							ret.y = 0.0f;
						}
						loop = true;
					}
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
	}

	// MEMO: �������ňړ����ă}�b�v�˂��������ꍇ�͍l�����Ă��Ȃ�
	// MEMO: �������ׂ������ł����炷���߂ɁA�}�b�v�`�b�v�ƃv���C���[�̋����ł�������v�Z���O����Ƃ��A�F�X����̂̓A��

	return ret;
}

/// <summary>
/// �v���C���[�ƃ}�b�v�������������̃`�F�b�N
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="futurePos">�ړ�����v�Z������̍��W</param>
/// <param name="mapData">�ǂ�ȃ}�b�v�`�b�v��</param>
/// <returns>�����������̃t���O</returns>
bool PlayerColision::IsHitPlayerWithMapChip(const Player& player, const  VECTOR& futurePos, int mapData,VECTOR mapChipPos)
{
	// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
	if (mapData == 48)
	{
		return false;
	}	
	//���ƍ����𔼕��ɂ��Ē��S���W�����߂�
	float futurePosLeft = futurePos.x - Player::PLAYER_W * 0.5f;
	float futurePosRight = futurePos.x + Player::PLAYER_W * 0.5f;
	float futurePosTop = futurePos.y - Player::PLAYER_H * 0.5f;
	float futurePosBottom = futurePos.y + Player::PLAYER_H * 0.5f;
	float targetLeft = mapChipPos.x - Map::CHIP_SIZE * 0.5f;
	float targetRight = mapChipPos.x + Map::CHIP_SIZE * 0.5f;
	float targetTop = mapChipPos.y - Map::CHIP_SIZE * 0.5f;
	float targetBottom = mapChipPos.y + Map::CHIP_SIZE * 0.5f;
	// ��`���m�̓����蔻��
	if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
		(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
		((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
			(targetTop > futurePosTop && targetTop < futurePosBottom)))
	{
		return true;
	}
	return false;
}

/// <summary>
/// �ڒn�����ꍇ�̏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="map">�}�b�v</param>
void PlayerColision::CheckIsGround(Player& player, const  Map& map)
{
	//�Q�b�^�[�ŕK�v�Ȓl�������Ă���
	VECTOR playerPos = player.GetPos();
	//���Əc�̃}�b�v�`�b�v�̐��������Ă���
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//�}�b�v�f�[�^�������Ă���
	int** mapData = map.getMapData();
	VECTOR mapLeftPos = map.GetChipLeftPos();


	// 1�h�b�g���ɂ��炵�ē�����Βn�ʂɑ����Ԃ����Ă��� �i�����_�����j
	auto checkPos = VGet(playerPos.x, playerPos.y - Map::ONE_PIXEL_SIZE, playerPos.z);
	bool isHit;
	// �S�}�b�v�`�b�v���J��Ԃ�
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//�}�b�v�`�b�v���ꂼ��̍��W���擾
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * (-hIndex - 1) + mapLeftPos.y, 0);
			//if (isHit == false)
			//{
			isHit = IsHitPlayerWithMapChip(player, checkPos, mapData[hIndex][wIndex],mapChipPos);
			//}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//�ڒn�����true�ɂ���
		player.SetIsGround(true);
		// fallSpeed���[���ɂ��A�}���ȗ�����h��
		player.SetFallSpeed(0.0f);

	
	}
	else
	{
		player.SetIsGround(false);
	}
}

/// <summary>
/// �V��ɓ������Ă����ꍇ�̏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="map">�}�b�v</param>
void PlayerColision::CheckIsTopHit(Player& player, const  Map& map)
{
	//�Q�b�^�[�ŕK�v�Ȓl�������Ă���
	VECTOR playerPos = player.GetPos();
	//���Əc�̃}�b�v�`�b�v�̐��������Ă���
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//�}�b�v�f�[�^�������Ă���
	int** mapData = map.getMapData();
	VECTOR mapLeftPos = map.GetChipLeftPos();


	// 1�h�b�g��ɂ��炵�ē�����Γ��オ�Ԃ����Ă��� �i�����_�����j
	auto checkPos = VGet(playerPos.x, playerPos.y + Map::ONE_PIXEL_SIZE, playerPos.z);
	bool isHit;
	//�}�b�v��x���W��
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//�}�b�v�`�b�v���ꂼ��̍��W���擾
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * (-hIndex - 1) + mapLeftPos.y, 0);
			isHit = IsHitPlayerWithMapChip(player, checkPos, mapData[hIndex][wIndex], mapChipPos);
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//�V��ɂԂ����Ă������̃t���O�������Ă���
		bool inIsHitTop = player.GetIsHitTop();
		// �ȑO�Ԃ����Ă��Ȃ��̂ɂԂ���Ȃ�fallSpeed���[���ɂ��A����������悤��
		if (!inIsHitTop)
		{
			player.SetIsHitTop(true);
			player.SetFallSpeed(0.0f);

			
		}
	}
	else
	{
		player.SetIsHitTop(false);
	}
}



/// <summary>
/// �G�l�~�[�̓����蔻����Ƃ�����̉����߂�����
/// </summary>
/// <param name="enemy">�G�l�~�[�̃C���X�^���X</param>
/// <param name="map">�}�b�v�̃C���X�^���X</param>
/// <param name="velocity">�G�l�~�[�̈ړ�����</param>
/// <returns>�����߂����ۂ̈ړ���</returns>
VECTOR EnemyColision::CheckEnemyHitWithMap(BaseEnemy& enemy, const Map& map, const VECTOR& velocity)
{
	// �T�C�Y���ŏ�����0�Ȃ瓮����������return
	if (VSize(velocity) == 0)		//VSize�Ńx�N�g���̃T�C�Y���Ƃ��Ă���0�Ȃ瓮���ĂȂ��Ȃ̂ł����ŕԂ�
	{
		return velocity;
	}
	//�Q�b�^�[�Ő��l��ϐ��ɑ��
	//���Əc�̃}�b�v�`�b�v�̐��������Ă���
	int mapXNum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//�G�l�~�[�̍��W�������Ă���
	VECTOR enemyPos = enemy.GetPos();
	//�}�b�v�f�[�^�������Ă���
	int** mapData = map.getMapData();
	VECTOR mapLeftPos = map.GetChipLeftPos();



	VECTOR ret = velocity;

	// ������Ȃ��Ȃ�܂ŌJ��Ԃ�
	bool loop = true;
	bool isFirstHit = true;	// ����œ���������
	while (loop)
	{
		loop = false;

		// �����̃v���C���[�̃|�W�V�������܂��o��
		VECTOR futurePos = VAdd(enemyPos, ret);

		// �S�}�b�v�`�b�v���J��Ԃ�
		for (int hIndex = 0; hIndex < mapYNum; hIndex++)
		{
			bool isHit = false;
			for (int wIndex = 0; wIndex < mapXNum; wIndex++)
			{
				//�}�b�v�`�b�v���ꂼ��̍��W���擾
				VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * (-hIndex - 1) + mapLeftPos.y, 0);
				//�}�b�v�`�b�v�ƃv���C���[�̓����蔻����݂�
				isHit = IsHitEnemyWithMapChip(enemy, futurePos, mapData[hIndex][wIndex], mapChipPos);

				// ����ɓ��������Ƃ�
				if (isHit && isFirstHit)
				{
					// ���㓖���蔻��Ń|�W�V������velocity�̕␳������Ƃ��A�����_�ȉ��̌덷���Y�܂��
					// �G��1�h�b�g�����炷�A���w�v�Z�����Ȃ��}�b�V�u�����蔻��ɂ͎ז��Ȃ̂ŏ���Ɋۂ߂Ă��܂��A
					// �ȍ~���߂ē����蔻��
					// pos��Velocity���ۂ߂�
					enemyPos.x = floorf(enemyPos.x);		//floorf�͏����_���ۂ߂�
					enemyPos.y = floorf(enemyPos.y);
					enemy.SetPos(enemyPos);
					ret.x = floorf(ret.x);
					ret.y = floorf(ret.y);
					isFirstHit = false;
					loop = true;	// ���[�v�p��
				}

				// �����������_�Ń}�b�v�`�b�v�̃��[�v����ʂ��邪�A������Ȃ��Ȃ�܂ŌJ��Ԃ����[�v�͌p��
				if (isHit && !isFirstHit)
				{
					// HACK: �������Ă����ꍇ��velocity��1�h�b�g���k�߂Ă����A������Ȃ��Ȃ�܂ŌJ��Ԃ�
					// ���̂܂܏k�߂Ă��܂��ƁA�΂߂̃x�N�g���̂Ƃ��i�Ⴆ�ΕǂɌ������ăW�����v�����Ƃ��j�ɃW�����v�̐������k�߂Ă��܂�
					// �����h�����߂ɁA
					// ����������k�߂Ă������ƂŁA�����������
					float absX = fabsf(ret.x);	// velocity��x�����̐�Βl
					float absY = fabsf(ret.y);	// velocity��y�����̐�Βl

					// x�������k�ߐ؂��Ă��Ȃ����x�������k�߂�
					bool shrinkX = (absX != 0.0f);	// x�������k�߂邩�ǂ���

					if (shrinkX)
					{
						if (ret.x > 0.0f)
						{
							ret.x -= 1.0f;
						}
						else
						{
							ret.x += 1.0f;
						}

						// �k�ߐ؂��������
						if (fabs(ret.x) < 1.0f)
						{
							ret.x = 0.0f;
						}
						loop = true;
					}
					else
					{
						if (ret.y > 0.0f)
						{
							ret.y -= 1.0f;
						}
						else
						{
							ret.y += 1.0f;
						}

						// �k�ߐ؂��������
						if (fabs(ret.y) < 1.0f)
						{
							ret.y = 0.0f;
						}
						loop = true;
					}
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
	}

	// MEMO: �������ňړ����ă}�b�v�˂��������ꍇ�͍l�����Ă��Ȃ�
	// MEMO: �������ׂ������ł����炷���߂ɁA�}�b�v�`�b�v�ƃv���C���[�̋����ł�������v�Z���O����Ƃ��A�F�X����̂̓A��

	return ret;
}

bool EnemyColision::IsHitEnemyWithMapChip(const BaseEnemy& enemy, const  VECTOR& futurePos, int mapData, VECTOR mapChipPos)
{
	// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
	if (mapData == -1)
	{
		return false;
	}
	//���ƍ����̎擾
	float enemyW = enemy.GetW();
	float enemyH = enemy.GetH();

	// �������Ă��邩�ǂ������ׂ�
	//���ƍ����𔼕��ɂ��Ē��S���W�����߂�
	float futurePosLeft = futurePos.x - enemyW * 0.5f;
	float futurePosRight = futurePos.x + enemyW * 0.5f;
	float futurePosTop = futurePos.y -  enemyH* 0.5f;
	float futurePosBottom = futurePos.y + enemyH * 0.5f;
	float targetLeft = mapChipPos.x - Map::CHIP_SIZE * 0.5f;
	float targetRight = mapChipPos.x + Map::CHIP_SIZE * 0.5f;
	float targetTop = mapChipPos.y - Map::CHIP_SIZE * 0.5f;
	float targetBottom = mapChipPos.y + Map::CHIP_SIZE * 0.5f;
	// ��`���m�̓����蔻��
	if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
		(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
		((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
			(targetTop > futurePosTop && targetTop < futurePosBottom)))
	{
		return true;
	}
	return false;
}

void EnemyColision::CheckIsGround(BaseEnemy& enemy, const  Map& map)
{
	//�Q�b�^�[�ŕK�v�Ȓl�������Ă���
	VECTOR enemyPos = enemy.GetPos();
	//���Əc�̃}�b�v�`�b�v�̐��������Ă���
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//�}�b�v�f�[�^�������Ă���
	int** mapData = map.getMapData();
	VECTOR mapLeftPos = map.GetChipLeftPos();


	// 1�h�b�g���ɂ��炵�ē�����Βn�ʂɑ����Ԃ����Ă��� �i�����_�����j
	auto checkPos = VGet(enemyPos.x, floorf(enemyPos.y) + 1.0f, enemyPos.z);
	bool isHit;
	// �S�}�b�v�`�b�v���J��Ԃ�
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//�}�b�v�`�b�v���ꂼ��̍��W���擾
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * hIndex + mapLeftPos.y, 0);
			//if (isHit == false)
			//{
			isHit = IsHitEnemyWithMapChip(enemy, checkPos, mapData[hIndex][wIndex], mapChipPos);
			//}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//�ڒn�����true��
		enemy.SetIsGround(true);
		// fallSpeed���[���ɂ��A�}���ȗ�����h��
		enemy.SetFallSpeed(0.0f);

		// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
		enemyPos.y = floorf(enemyPos.y);	// ���傤�ǒn�ʂɕt���ʒu��
	}
	else
	{
		enemy.SetIsGround(false);
	}
}

void EnemyColision::CheckIsTopHit(BaseEnemy& enemy, const  Map& map)
{
	//�Q�b�^�[�ŕK�v�Ȓl�������Ă���
	VECTOR enemyPos = enemy.GetPos();
	//���Əc�̃}�b�v�`�b�v�̐��������Ă���
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//�}�b�v�f�[�^�������Ă���
	int** mapData = map.getMapData();
	VECTOR mapLeftPos = map.GetChipLeftPos();


	// 1�h�b�g��ɂ��炵�ē�����Γ��オ�Ԃ����Ă��� �i�����_�����j
	auto checkPos = VGet(enemyPos.x, floorf(enemyPos.y) - 1.0f, enemyPos.z);
	bool isHit;
	//�}�b�v��x���W��
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//�}�b�v�`�b�v���ꂼ��̍��W���擾
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * hIndex + mapLeftPos.y, 0);
			isHit = IsHitEnemyWithMapChip(enemy, checkPos, mapData[hIndex][wIndex], mapChipPos);
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//�V��ɂԂ����Ă������̃t���O�������Ă���
		bool inIsHitTop = enemy.GetIsHitTop();
		// �ȑO�Ԃ����Ă��Ȃ��̂ɂԂ���Ȃ�fallSpeed���[���ɂ��A����������悤��
		if (!inIsHitTop)
		{
			enemy.SetIsHitTop(true);
			enemy.SetFallSpeed(0.0f);

			// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
			enemyPos.y = floorf(enemyPos.y);
		}
	}
	else
	{
		enemy.SetIsHitTop(false);
	}
}














