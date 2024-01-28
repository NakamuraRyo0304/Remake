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

//==============================================================================
// Json�ϊ��N���X
//==============================================================================
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"

//==============================================================================
// �u���b�N�̃C���N���[�h
//==============================================================================
#include "../Blocks/Sand/Sand.h"			// ���u���b�N
#include "../Blocks/Cloud/Cloud.h"			// �_�u���b�N
#include "../Blocks/Coin/Coin.h"			// �R�C���u���b�N
#include "../../Editor/Objects/Air/Air.h"	// �X�e�[�W�G�f�B�^�p����u���b�N

class BlockManager
{
private:

	// �u���b�N�I�u�W�F�N�g
	std::vector<std::unique_ptr<Sand>> m_sands;
	std::vector<std::unique_ptr<Cloud>> m_clouds;
	std::vector<std::unique_ptr<Coin>> m_coins;
	std::vector<std::unique_ptr<Air>> m_air;

	// Json�ǂݍ���
	std::unique_ptr<JsonHelper> m_jsonHelper;

	// �p�X�ۑ�
	std::wstring m_stagePath;

	// �����o�����t���O(�����팸)
	bool is_wrighting;

	// �v���C���̃t���O�iTrue�ŃG�f�B�^�p�`���؂�j
	bool is_playing;

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
	/// <param name="id">�u���b�N��ID</param>
	/// <param name="hit">�ݒ�@�ڐG���FTrue/��ڐG���FFalse</param>
	/// <param name="index">�Փ˂����I�u�W�F�N�g�ԍ�(-1�őS�ʒm)</param>
	/// <returns>�Ȃ�</returns>
	void NotificateHit(const ID& id, const bool& hit, const int& index);

	// �X�e�[�W�p�X��ݒ�
	void SetStagePath(const wchar_t* path) { m_stagePath = path; }

	// �X�e�[�W�������o��
	void OutputStage();

	// �Q�[���v���C����Ƃ���ON�ɂ���
	void SetPlay(bool play) { is_playing = play; }

	// ���C���[�t���[���̐؂�ւ��t���O�f�t�H���g��False
	void SetWireFrame(bool frame);

private:

	// �u���b�N��ID���當�����Ԃ�(�����o���p)
	std::string GetBlockID(const ID& id);

	// �u���b�N�̎�ނ�ύX����
	void ReplaceBlock();

	// �u���b�N�쐬
	void CreateBlock(ID id, DirectX::SimpleMath::Vector3 pos);

	// �z������Z�b�g����
	void ClearBlocks();

	// ��C�Ŗ��߂�
	void FillAir();

public:

	// ���u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Sand>>& GetSandBlock() { return m_sands; }
	// �_�u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Cloud>>& GetCloudBlock() { return m_clouds; }
	// �R�C���u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Coin>>& GetCoinBlock() { return m_coins; }
	// �G�A�[�u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Air>>& GetAirBlock() { return m_air; }

};

#endif // BLOCKMANAGER