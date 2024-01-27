/*
 *	@File	BlockManager.cpp
 *	@Brief	�u���b�N�Ǘ��N���X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"
#include "BlockManager.h"

//==============================================================================
// �u���b�N�̃C���N���[�h
//==============================================================================
#include "../Blocks/Sand/Sand.h"		// ���u���b�N
#include "../Blocks/Cloud/Cloud.h"		// �_�u���b�N
#include "../Blocks/Coin/Coin.h"		// �R�C���u���b�N


//==============================================================================
// �R���X�g���N�^
//==============================================================================
BlockManager::BlockManager(const wchar_t* stagePath)
	: m_stagePath{ stagePath }		// �X�e�[�W�p�X���i�[
{
	// Json�ǂݍ��݃V�X�e���쐬
	m_jsonHelper = std::make_unique<JsonHelper>();
	m_jsonHelper->Load(m_stagePath.c_str());

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
	m_parameter.clear();
}

//==============================================================================
// ����������
//==============================================================================
void BlockManager::Initialize()
{
	// �f�[�^���擾
	Json _data = m_jsonHelper->GetData();
	m_parameter.clear(); m_sands.clear(); m_clouds.clear(); m_coins.clear();

	for (int i = 0; i < _data.size(); i++)
	{
		// ���O���i�[
		auto& _name = _data[i]["Path"];

		// ���
		BlockKinds _kinds = BlockKinds::LENGTHB;

		// ���W�̕ϊ�
		float _x = static_cast<float>(_data[i]["Position"]["X"]);
		float _y = static_cast<float>(_data[i]["Position"]["Y"]);
		float _z = static_cast<float>(_data[i]["Position"]["Z"]);

		// ���u���b�N���i�[
		if (_name == "Sand")
		{
			m_sands.push_back(std::make_unique<Sand>(SimpleMath::Vector3(_x, _y, _z)));
			_kinds = BlockKinds::SANDB;
		}
		// �_�u���b�N���i�[
		if (_name == "Cloud")
		{
			m_clouds.push_back(std::make_unique<Cloud>(SimpleMath::Vector3(_x, _y, _z)));
			_kinds = BlockKinds::CLOUDB;
		}
		// �R�C���u���b�N���i�[
		if (_name == "Coin")
		{
			m_coins.push_back(std::make_unique<Coin>(SimpleMath::Vector3(_x, _y, _z)));
			_kinds = BlockKinds::COINB;
		}

		// �u���b�N�����i�[����
		m_parameter.push_back(BlockParameter(i, _kinds, SimpleMath::Vector3(_x, _y, _z)));
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
		sand->Update();
	}
	for (auto& cloud : m_clouds)
	{
		cloud->Update();
	}
	for (auto& coin : m_coins)
	{
		coin->Update();
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void BlockManager::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda option)
{
	// �I�u�W�F�N�g�̕`��
	for (auto& sand : m_sands)
	{
		sand->Draw(states, view, proj, option);
	}
	for (auto& cloud : m_clouds)
	{
		cloud->Draw(states, view, proj, option);
	}
	for (auto& coin : m_coins)
	{
		coin->Draw(states, view, proj, option);
	}
}

// �Փ˒ʒm�������Ȃ�
void BlockManager::NotificateHit(const BlockKinds& kinds, const bool& hit, const int& index)
{
	// �����ŏ����Ɉ�v����I�u�W�F�N�g���擾���đ���
	if (kinds == BlockKinds::SANDB && index >= 0 && index < m_sands.size())
	{
		m_sands[index]->NotificateHit(hit);
	}
	if (kinds == BlockKinds::CLOUDB && index >= 0 && index < m_clouds.size())
	{
		m_clouds[index]->NotificateHit(hit);
	}
	if (kinds == BlockKinds::COINB && index >= 0 && index < m_coins.size())
	{
		m_coins[index]->NotificateHit(hit);
	}
}

//==============================================================================
// �X�e�[�W�������o�� ����
//==============================================================================
void BlockManager::OutputStage()
{
	Json _json;
	for (size_t i = 0; i < m_parameter.size(); i++)
	{
		SimpleMath::Vector3 _pos = m_parameter[i].pos;

		_json[i]["Path"] = GetBlockKinds(m_parameter[i].kinds);
		_json[i]["Position"]["X"] = _pos.x;
		_json[i]["Position"]["Y"] = _pos.y;
		_json[i]["Position"]["Z"] = _pos.z;
	}

	// �f�[�^�������o��
	std::string _output = _json.dump(2);
	m_jsonHelper->Write(_output);
}

//==============================================================================
// �u���b�N�̎�ނ��珑���o���p�������Ԃ�
//==============================================================================
std::string BlockManager::GetBlockKinds(const BlockKinds& kinds)
{
	switch (kinds)
	{
	case BlockKinds::SANDB:
		return "Sand";
	case BlockKinds::CLOUDB:
		return "Cloud";
	case BlockKinds::COINB:
		return "Coin";
	default:
		return "nothing";
	}
}
