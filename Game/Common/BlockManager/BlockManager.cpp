/*
 *	@File	BlockManager.cpp
 *	@Brief	�u���b�N�Ǘ��N���X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"
#include "Libraries/UserUtility.h"
#include "BlockManager.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
BlockManager::BlockManager(const wchar_t* stagePath)
	: m_stagePath{ stagePath }		// �X�e�[�W�p�X���i�[
{
	// Json�ǂݍ��݃V�X�e���쐬
	m_jsonHelper = std::make_unique<JsonHelper>();

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
BlockManager::~BlockManager()
{
	m_jsonHelper.reset();
	m_stagePath.clear();
	ClearBlocks();
}

//==============================================================================
// ����������
//==============================================================================
void BlockManager::Initialize()
{
	// �f�[�^��ǂݍ���
	m_jsonHelper->Load(m_stagePath.c_str());

	// �f�[�^���擾
	Json _data = m_jsonHelper->GetData();
	ClearBlocks();

	for (int i = 0; i < _data.size(); i++)
	{
		// ���O���i�[
		auto& _name = _data[i]["Path"];

		// ���W�̕ϊ�
		float _x = static_cast<float>(_data[i]["Position"]["X"]);
		float _y = static_cast<float>(_data[i]["Position"]["Y"]);
		float _z = static_cast<float>(_data[i]["Position"]["Z"]);
		SimpleMath::Vector3 _position = SimpleMath::Vector3(_x, _y, _z);

		// ���u���b�N���i�[
		if (_name == "Sand")
			m_sands.push_back(std::make_unique<Sand>(_position));
		// �R�C�����i�[
		if (_name == "Coin")
			m_coins.push_back(std::make_unique<Coin>(_position));
		// �_�u���b�N���i�[
		if (_name == "Cloud")
			m_clouds.push_back(std::make_unique<Cloud>(_position));
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void BlockManager::Update()
{
	// �I�u�W�F�N�g�̍X�V
	for (auto& sand : m_sands)
	{
		if (UserUtility::IsNull(sand.get())) continue;
		if (sand->GetID() == ID::Deleted) continue;
		sand->Update();
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		if (cloud->GetID() == ID::Deleted) continue;
		cloud->Update();
	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;
		if (coin->GetID() == ID::Deleted) continue;
		coin->Update();
	}

	// �u�������{��
	ReplaceBlock();
}

//==============================================================================
// �`�揈��
//==============================================================================
void BlockManager::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda option)
{
	// �I�u�W�F�N�g�̕`��
	for (auto& sand : m_sands)
	{
		if (UserUtility::IsNull(sand.get())) continue;
		if (sand->GetID() == ID::Deleted) continue;
		sand->Draw(states, view, proj, option);
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		if (cloud->GetID() == ID::Deleted) continue;
		cloud->Draw(states, view, proj, option);
	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;
		if (coin->GetID() == ID::Deleted) continue;
		coin->Draw(states, view, proj, option);
	}
}

// �Փ˒ʒm�������Ȃ�
void BlockManager::NotificateHit(const ID& id, const bool& hit, const int& index)
{
	if (id == ID::Obj_Sand && index >= 0 && index < m_sands.size())
		m_sands[index]->NotificateHit(hit);
	if (id == ID::Obj_Cloud && index >= 0 && index < m_clouds.size())
		m_clouds[index]->NotificateHit(hit);
	if (id == ID::Obj_Coin && index >= 0 && index < m_coins.size())
		m_coins[index]->NotificateHit(hit);
}

//==============================================================================
// �X�e�[�W�������o�� ����
//==============================================================================
void BlockManager::OutputStage()
{
	// �I�u�W�F�N�g�z��
	std::vector<IGameObject*> _objects;
	for (auto& sand : m_sands)
	{
		_objects.push_back(sand.get());
	}
	for (auto& cloud : m_clouds)
	{
		_objects.push_back(cloud.get());
	}
	for (auto& coin : m_coins)
	{
		_objects.push_back(coin.get());
	}

	Json _json;
	int _index = 0;

	// _object�Ɋi�[���ꂽ�u���b�N���o�͂���
	while (_index < _objects.size())
	{
		// ������Ă�����X�L�b�v
		if (_objects[_index]->GetID() == ID::Deleted)
		{
			_index++;
			continue;
		}

		_json[_index]["Path"] = GetBlockID(_objects[_index]->GetID());
		SimpleMath::Vector3 _pos = _objects[_index]->GetInitialPosition();

		_json[_index]["Position"]["X"] = _pos.x;
		_json[_index]["Position"]["Y"] = _pos.y;
		_json[_index]["Position"]["Z"] = _pos.z;
		_index++;
	}

	// �f�[�^�������o��
	std::string _output = _json.dump(2);
	m_jsonHelper->Write(_output);
}

//==============================================================================
// �u���b�N�̎�ނ��珑���o���p�������Ԃ�
//==============================================================================
std::string BlockManager::GetBlockID(const ID& id)
{
	switch (id)
	{
	case ID::Obj_Sand:
		return "Sand";
	case ID::Obj_Coin:
		return "Coin";
	case ID::Obj_Cloud:
		return "Cloud";
	default:
		return "";
	}
}

//==============================================================================
// �u���b�N�u����������
//==============================================================================
void BlockManager::ReplaceBlock()
{
	for (auto& sand : m_sands)
	{
		if (UserUtility::IsNull(sand.get())) continue;

		// �u���b�N��������Ă����ꍇ
		if (sand->GetID() == ID::Deleted)
		{
			UserUtility::RemoveVec(m_sands, sand);
			continue;
		}

		// �����Ȃ�X�L�b�v
		if (sand->GetID() == ID::Obj_Sand) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(sand->GetID(), sand->GetInitialPosition());
		UserUtility::RemoveVec(m_sands, sand);
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;

		// �u���b�N��������Ă����ꍇ
		if (cloud->GetID() == ID::Deleted)
		{
			UserUtility::RemoveVec(m_clouds, cloud);
			continue;
		}

		// �����Ȃ�X�L�b�v
		if (cloud->GetID() == ID::Obj_Cloud) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(cloud->GetID(), cloud->GetInitialPosition());
		UserUtility::RemoveVec(m_clouds, cloud);
	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;

		// �u���b�N��������Ă����ꍇ
		if (coin->GetID() == ID::Deleted)
		{
			UserUtility::RemoveVec(m_coins, coin);
			continue;
		}

		// �����Ȃ�X�L�b�v
		if (coin->GetID() == ID::Obj_Coin) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(coin->GetID(), coin->GetInitialPosition());
		UserUtility::RemoveVec(m_coins, coin);
	}
}

//==============================================================================
// �u���b�N�쐬
//==============================================================================
void BlockManager::CreateBlock(ID id, SimpleMath::Vector3 pos)
{
	// ID����v�������m��ǉ�����

	if (id == ID::Obj_Sand)		// ���u���b�N
		m_sands.push_back(std::make_unique<Sand>(pos));
	if (id == ID::Obj_Cloud)	// �_�u���b�N
		m_clouds.push_back(std::make_unique<Cloud>(pos));
	if (id == ID::Obj_Coin)		// �R�C��
		m_coins.push_back(std::make_unique<Coin>(pos));
}

//==============================================================================
// �u���b�N�z������Z�b�g����
//==============================================================================
void BlockManager::ClearBlocks()
{
	m_sands.clear();
	m_clouds.clear();
	m_coins.clear();
}
