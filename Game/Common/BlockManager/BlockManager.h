/*
 *	@File	BlockManager.h
 *	@Brief	�u���b�N�Ǘ��N���X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BLOCKMANAGER
#define BLOCKMANAGER

//==============================================================================
// �I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class JsonHelper;
class Sand;
class Cloud;
class Coin;
class BlockManager
{
public:

	// �u���b�N�̎��
	enum BlockKinds : UINT { SANDB, CLOUDB, COINB, LENGTHB };

	// �u���b�N�̎Q�Ɨp�p�����[�^�[
	struct BlockParameter
	{
		int index;
		BlockKinds kinds;
		DirectX::SimpleMath::Vector3 pos;
		BlockParameter(int index, BlockKinds kinds, const DirectX::SimpleMath::Vector3& pos)
			: index(index), kinds(kinds), pos(pos) {};
	};

private:

	// �u���b�N�I�u�W�F�N�g
	std::vector<std::unique_ptr<Sand>> m_sands;
	std::vector<std::unique_ptr<Cloud>> m_clouds;
	std::vector<std::unique_ptr<Coin>> m_coins;

	// �u���b�N�̖��O�E���W
	std::vector<BlockParameter> m_parameter;

	// Json�ǂݍ���
	std::unique_ptr<JsonHelper> m_jsonHelper;

	// �p�X�ۑ�
	std::wstring m_stagePath;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stagePath">�ǂݍ��݃X�e�[�W�p�X</param>
	/// <returns>�Ȃ�</returns>
	BlockManager(const wchar_t* stagePath);
	~BlockManager();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�v���W�F�N�V�����s��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr);

public:

	/// <summary>
	/// �Փ˒ʒm�𑗂�
	/// </summary>
	/// <param name="kinds">�ʒm�𑗂���</param>
	/// <param name="hit">�ݒ�@�ڐG���FTrue/��ڐG���FFalse</param>
	/// <param name="index">�Փ˂����I�u�W�F�N�g�ԍ�(-1�őS�ʒm)</param>
	/// <returns>�Ȃ�</returns>
	void NotificateHit(const BlockKinds& kinds, const bool& hit, const int& index);

	// �X�e�[�W�p�X��ݒ�
	void SetStagePath(const wchar_t* path) { m_stagePath = path; }

	// �X�e�[�W�������o��
	void OutputStage();

private:

	// �u���b�N�̎�ނ��當�����Ԃ�(�����o���p)
	std::string GetBlockKinds(const BlockKinds& kinds);

};

#endif // BLOCKMANAGER