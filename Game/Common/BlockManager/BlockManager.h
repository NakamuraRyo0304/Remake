/*
 *	@File	BlockManager.h
 *	@Brief	�u���b�N�Ǘ��N���X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BLOCKMANAGER
#define BLOCKMANAGER

#include "Game/Bases/BaseObject.h"						// �I�u�W�F�N�g�̊��N���X
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"// JSON�֘A
#include "Libraries/SystemDatas/DiaLog/DiaLog.h"		// �_�C�A���O
#include "../Blocks/Flozen/Flozen.h"					// �X�u���b�N
#include "../Blocks/Cloud/Cloud.h"						// �_�u���b�N
#include "../Blocks/Coin/Coin.h"						// �R�C���u���b�N
#include "../../Editor/Objects/Air/Air.h"				// �X�e�[�W�G�f�B�^�p����u���b�N
#include "../../Editor/Objects/EditChara/EditChara.h"	// �X�e�[�W�G�f�B�^�p�v���C��
#include "../Blocks/Goal/Goal.h"						// �S�[���I�u�W�F�N�g
#include "../Blocks/Spike/Spike.h"						// ���I�u�W�F�N�g

class BlockManager
{
public:

	// �t�@�C���������[�h����
	void ReLoad(const wchar_t* path = nullptr);
	// �X�e�[�W�������o��
	void OutputStage();
	// ���j�[�N�ȃf�[�^�������o��
	void OutputUniqueData(std::vector<BaseObject*>& data);

	// �X���u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Flozen>>&    GetFlozens() { return m_flozens; }
	// �_�u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Cloud>>&     GetClouds() { return m_clouds; }
	// �R�C���u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Coin>>&      GetCoins() { return m_coins; }
	// �S�[���I�u�W�F�N�g�̔z����Q��
	std::vector<std::unique_ptr<Goal>>&      GetGoals() { return m_goals; }
	// ���I�u�W�F�N�g�̔z����Q��
	std::vector<std::unique_ptr<Spike>>&     GetSpikes() { return m_spikes; }
	// �G�A�[�u���b�N�̔z����Q��
	std::vector<std::unique_ptr<Air>>&       GetAirs() { return m_air; }
	// �v���C���u���b�N�̔z����Q��
	std::vector<std::unique_ptr<EditChara>>& GetPlayers() { return m_chara; }
	// �X�e�[�W�p�X���擾
	const wchar_t* GetStagePath() { return m_stagePath.c_str(); }
	// �X�e�[�W�p�X��ݒ�
	void SetStagePath(const wchar_t* path) { m_stagePath = path; }
	// �v���C���[�h��ݒ�
	void SetPlay(bool play) { is_playing = play; }
	// �I�t�Z�b�g
	void SetOffset(const DirectX::SimpleMath::Vector3& offset);
	// �v���C���̍��W���擾����
	DirectX::SimpleMath::Vector3 GetPlayerPosition() const;
	// �S�[������̎擾
	bool IsArrived() const;
	// ���̏Փ˂��擾
	bool IsHitSpike() const;

public:

	// �R���X�g���N�^
	BlockManager(const wchar_t* stagePath);
	// �f�X�g���N�^
	~BlockManager();
	// ������
	void Initialize();
	// �X�V
	void Update();
	/// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr);

private:

	// �t�@���N�^
	// �A�E�g�v�b�g���̃\�[�g����
	struct OutputSort
	{
		bool operator()(const Json& a, const Json& b) const
		{
			// �D��x�@�@ID�̕��������Z�����Ƀ\�[�g
			if (a["Path"].get<std::string>().length() != b["Path"].get<std::string>().length())
			{
				return a["Path"].get<std::string>().length() < b["Path"].get<std::string>().length();
			}

			// �D��x�A�@ID�������ꍇ�AXZ���W�̏����Ƀ\�[�g
			if (a["Path"].get<std::string>() == b["Path"].get<std::string>())
			{
				if (a["Position"]["X"] != b["Position"]["X"])
				{
					return a["Position"]["X"] < b["Position"]["X"];
				}
				if (a["Position"]["Z"] != b["Position"]["Z"])
				{
					return a["Position"]["Z"] < b["Position"]["Z"];
				}
			}

			// �D��x�B�@Y���W�̏����Ƀ\�[�g
			return a["Position"]["Y"] < b["Position"]["Y"];
		}
	};

	// �}�b�v�̃T�C�Y
	static const int MAP_SIZE_X = 10;
	static const int MAP_SIZE_Y = 5;
	static const int MAP_SIZE_Z = 10;

private:

	// �v�f���O�p�֐�
	template<typename T>
	inline void RemoveVec(std::vector<T>& vec, const T& val)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (*it == val)
			{
				it = vec.erase(it);
				if (it == vec.end()) break;
			}
		}
	}
	// �I�u�W�F�N�g�u�������֐�
	template<typename T>
	void ReplaceObjects(const ID& id, std::vector<T>& objects)
	{
		for (auto& obj : objects)
		{
			if (obj.get() == nullptr) continue;
			if (obj->GetID() == id) continue;
			CreateBlock(obj->GetID(), obj->GetInitialPosition());
			RemoveVec(objects, obj);
		}
	}
	// �����o���p�I�u�W�F�N�g�ǉ��֐�
	template <typename T>
	void AddWriteObjects(std::vector<BaseObject*>* objects, std::vector<T>& wish)
	{
		// ��Ȃ珈�����Ȃ�
		if (wish.empty()) return;

		// �I�u�W�F�N�g��ǉ�����
		for (auto& obj : wish)
		{
			objects->push_back(obj.get());
		}
	}
	// �N���A�֐�
	template <typename T>
	bool ClearObjects(std::vector<T>* objects)
	{
		objects->clear();

		return objects->empty();
	}

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

private:

	// �u���b�N�I�u�W�F�N�g
	std::vector<std::unique_ptr<Flozen>>    m_flozens;	// �X��
	std::vector<std::unique_ptr<Cloud>>     m_clouds;	// �_
	std::vector<std::unique_ptr<Coin>>      m_coins;	// �R�C��
	std::vector<std::unique_ptr<Air>>       m_air;		// ����p�G�A�[
	std::vector<std::unique_ptr<EditChara>> m_chara;	// �L����
	std::vector<std::unique_ptr<Goal>>      m_goals;	// �S�[��
	std::vector<std::unique_ptr<Spike>>     m_spikes;	// �X�p�C�N
	// Json�ǂݍ���
	std::unique_ptr<JsonHelper> m_jsonHelper;
	// �_�C�A���O����
	std::unique_ptr<DiaLog> m_dialog;
	// �p�X�ۑ�
	std::wstring m_stagePath;
	// �v���C���̃t���O�iTrue�ŃG�f�B�^�p�`���؂�j
	bool is_playing;

};

#endif // BLOCKMANAGER