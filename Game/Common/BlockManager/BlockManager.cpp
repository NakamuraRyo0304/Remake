/*
 *	@File	BlockManager.cpp
 *	@Brief	�u���b�N�Ǘ��N���X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"
#include "Libraries/UserUtility.h"
#include <random>
#include "BlockManager.h"

// �����p���� //
///////////////////////////////////////////
// �u���b�N��ǉ�������X�V����֐�      //
// Initialize Update Draw                //
// SelectOffset GetBlockID ReplaceBlock  //
// ClearBlocks CreateBlock OutputStage   //
///////////////////////////////////////////

//==============================================================================
// �R���X�g���N�^
//==============================================================================
BlockManager::BlockManager(const wchar_t* stagePath)
	: m_stagePath{ stagePath }		// �X�e�[�W�p�X���i�[
	, is_playing{ false }			// �v���C�t���O
{
	// Json�ǂݍ��݃V�X�e���쐬
	m_jsonHelper = std::make_unique<JsonHelper>();

	// �_�C�A���O�A�N�Z�T�쐬
	m_dialog = std::make_unique<DiaLog>();

	// �u���b�N���N���A
	ClearBlocks();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
BlockManager::~BlockManager()
{
	m_jsonHelper.reset();
	m_dialog.reset();
	m_stagePath.clear();
	ClearBlocks();
}

//==============================================================================
// ����������
//==============================================================================
void BlockManager::Initialize()
{
	// ��x�f�[�^���폜
	ClearBlocks();

	// �G�f�B�^���[�h�̎��A����p�G�A�[�Ŗ��߂�
	if (is_playing == false)
	{
		FillAir();
	}

	// �f�[�^��ǂݍ���
	m_jsonHelper->Load(m_stagePath.c_str());

	// �f�[�^���擾
	Json _data = m_jsonHelper->GetData();

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
		if (_name == "Sand")	m_sands.push_back(std::make_unique<Sand>(_position));
		// �R�C�����i�[
		if (_name == "Coin")	m_coins.push_back(std::make_unique<Coin>(_position));
		// �_�u���b�N���i�[
		if (_name == "Cloud")	m_clouds.push_back(std::make_unique<Cloud>(_position));
		// �v���C���u���b�N���i�[
		if (_name == "Player")	m_chara.push_back(std::make_unique<EditChara>(_position));
		// �S�[���I�u�W�F�N�g���i�[
		if (_name == "Goal")	m_goals.push_back(std::make_unique<Goal>(_position));
		// ���I�u�W�F�N�g���i�[
		if (_name == "Spike")	m_spikes.push_back(std::make_unique<Spike>(_position));

		// �v���C���[�h�̓X�L�b�v(�����̈Ӗ����Ȃ�����)
		if (is_playing == true) continue;

		// �����ꏊ�ɃG�A�[���������炻�̏ꏊ�̃G�A�[������
		if (UserUtility::IsNull(m_air[i].get())) continue;
		if (m_air[i]->GetPosition() == _position)
		{
			m_air[i].reset();
		}
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void BlockManager::Update()
{
	// �I�u�W�F�N�g�̍X�V
	for (auto& sand : m_sands)		// ���u���b�N
	{
		if (UserUtility::IsNull(sand.get())) continue;
		sand->Update();
	}
	for (auto& cloud : m_clouds)	// �_�u���b�N
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		cloud->Update();
	}
	for (auto& coin : m_coins)		// �R�C��
	{
		if (UserUtility::IsNull(coin.get())) continue;
		coin->Update();
	}
	for (auto& goal : m_goals)		// �S�[���I�u�W�F�N�g
	{
		if (UserUtility::IsNull(goal.get())) continue;
		goal->Update();
	}
	for (auto& spike : m_spikes)	// ���I�u�W�F�N�g
	{
		if (UserUtility::IsNull(spike.get())) continue;
		spike->Update();
	}

	// �v���C���[�h�̓X�L�b�v
	if (is_playing == true) return;

	for (auto& chara : m_chara)		// �L�����I�u�W�F�N�g
	{
		if (UserUtility::IsNull(chara.get())) continue;
		chara->Update();
	}
	for (auto& air : m_air)			// �G�A�[
	{
		if (UserUtility::IsNull(air.get())) continue;
		air->Update();
	}

	// �u�������{��
	ReplaceBlock();
}

//==============================================================================
// �`�揈��
//==============================================================================
void BlockManager::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	// �I�u�W�F�N�g�̕`��
	for (auto& sand : m_sands)		// ���u���b�N
	{
		if (UserUtility::IsNull(sand.get())) continue;
		sand->Draw(context, states, view, proj, wireframe, option);
	}
	for (auto& cloud : m_clouds)	// �_�u���b�N
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		cloud->Draw(context, states, view, proj, wireframe, option);
	}
	for (auto& coin : m_coins)		// �R�C��
	{
		if (UserUtility::IsNull(coin.get())) continue;
		coin->Draw(context, states, view, proj, wireframe, option);
	}
	for (auto& goal : m_goals)		// �S�[���I�u�W�F�N�g
	{
		if (UserUtility::IsNull(goal.get())) continue;
		goal->Draw(context, states, view, proj, wireframe, option);
	}
	for (auto& spike : m_spikes)	// ���I�u�W�F�N�g
	{
		if (UserUtility::IsNull(spike.get())) continue;
		spike->Draw(context, states, view, proj, wireframe, option);
	}

	// �v���C���[�h�̓X�L�b�v
	if (is_playing == true) return;

	for (auto& chara : m_chara)		// �L�����I�u�W�F�N�g
	{
		if (UserUtility::IsNull(chara.get())) continue;
		chara->Draw(context, states, view, proj, wireframe, option);
	}
}

//==============================================================================
// �I�t�Z�b�g�����Z(�Z���N�g�V�[���Ŏ�ɌĂяo��)
//==============================================================================
void BlockManager::SelectOffset(const SimpleMath::Vector3& offset)
{
	// �I�u�W�F�N�g�̕`��
	for (auto& sand : m_sands)		// ���u���b�N
	{
		if (UserUtility::IsNull(sand.get())) continue;
		sand->SetPosition(sand->GetInitialPosition() + offset);
	}
	for (auto& cloud : m_clouds)	// �_�u���b�N
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		cloud->SetPosition(cloud->GetInitialPosition() + offset);
	}
	for (auto& coin : m_coins)		// �R�C��
	{
		if (UserUtility::IsNull(coin.get())) continue;
		coin->SetPosition(coin->GetInitialPosition() + offset);
	}
	for (auto& goal : m_goals)		// �S�[���I�u�W�F�N�g
	{
		if (UserUtility::IsNull(goal.get())) continue;
		goal->SetPosition(goal->GetInitialPosition() + offset);
	}
	for (auto& spike : m_spikes)	// ���I�u�W�F�N�g
	{
		if (UserUtility::IsNull(spike.get())) continue;
		spike->SetPosition(spike->GetInitialPosition() + offset);
	}
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
	case ID::Obj_Player:
		return "Player";
	case ID::Obj_Goal:
		return "Goal";
	case ID::Obj_Spike:
		return "Spike";
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
		if (sand->GetID() == ID::Obj_Sand) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(sand->GetID(), sand->GetInitialPosition());
		UserUtility::RemoveVec(m_sands, sand);
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		if (cloud->GetID() == ID::Obj_Cloud) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(cloud->GetID(), cloud->GetInitialPosition());
		UserUtility::RemoveVec(m_clouds, cloud);
	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;
		if (coin->GetID() == ID::Obj_Coin) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(coin->GetID(), coin->GetInitialPosition());
		UserUtility::RemoveVec(m_coins, coin);
	}
	for (auto& air : m_air)
	{
		if (UserUtility::IsNull(air.get())) continue;
		if (air->GetID() == ID::Obj_Air) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(air->GetID(), air->GetInitialPosition());
		UserUtility::RemoveVec(m_air, air);
	}
	for (auto& chara : m_chara)
	{
		if (UserUtility::IsNull(chara.get())) continue;
		if (chara->GetID() == ID::Obj_Player) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(chara->GetID(), chara->GetInitialPosition());
		UserUtility::RemoveVec(m_chara, chara);
	}
	for (auto& goal : m_goals)
	{
		if (UserUtility::IsNull(goal.get())) continue;
		if (goal->GetID() == ID::Obj_Goal) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(goal->GetID(), goal->GetInitialPosition());
		UserUtility::RemoveVec(m_goals, goal);
	}
	for (auto& spike : m_spikes)
	{
		if (UserUtility::IsNull(spike.get())) continue;
		if (spike->GetID() == ID::Obj_Spike) continue;

		// ���O�ɑΉ������u���b�N�ɕύX����
		CreateBlock(spike->GetID(), spike->GetInitialPosition());
		UserUtility::RemoveVec(m_spikes, spike);
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
	if (id == ID::Obj_Air)		// �G�A�[����
		m_air.push_back(std::make_unique<Air>(pos));
	if (id == ID::Obj_Player)	// �v���C��
		m_chara.push_back(std::make_unique<EditChara>(pos));
	if (id == ID::Obj_Goal)		// �S�[���I�u�W�F�N�g
		m_goals.push_back(std::make_unique<Goal>(pos));
	if (id == ID::Obj_Spike)	// ���I�u�W�F�N�g
		m_spikes.push_back(std::make_unique<Spike>(pos));
}

//==============================================================================
// �u���b�N�z������Z�b�g����
//==============================================================================
void BlockManager::ClearBlocks()
{
	m_sands.clear();
	m_clouds.clear();
	m_coins.clear();
	m_air.clear();
	m_chara.clear();
	m_goals.clear();
	m_spikes.clear();
}

//==============================================================================
// �G�A�[�Ŗ��߂�
//==============================================================================
void BlockManager::FillAir()
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			for (int z = 0; z < 10; z++)
			{
				auto _pos = SimpleMath::Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
				m_air.push_back(std::make_unique<Air>(_pos));
			}
		}
	}
}

//==============================================================================
// �v���C���[�̍��W���擾����
//==============================================================================
SimpleMath::Vector3 BlockManager::GetPlayerPosition()
{
	SimpleMath::Vector3 _playerPosition;

	// �v���C���[���P�����Ȃ��ꍇ�͂��̍��W��Ԃ�
	// �v���C���[���Q�ȏ゠��ꍇ�̓����_���ŕԂ�
	if (m_chara.size() == 1)
	{
		_playerPosition = m_chara[0]->GetInitialPosition();
	}
	else
	{
		// ����������̃Z�b�g�A�b�v
		std::random_device _rd;
		std::mt19937 _gen(_rd());
		std::uniform_int_distribution<size_t> _distribution(0, m_chara.size() - 1);

		// �����_����1�l�̃v���C���[��I�сA���̍��W��Ԃ�
		size_t _randomIndex = _distribution(_gen);
		_playerPosition = m_chara[_randomIndex]->GetInitialPosition();
	}

	return _playerPosition;
}

//==============================================================================
// �S�[������擾
//==============================================================================
bool BlockManager::IsArrived()
{
	if (m_goals.empty()) return false;

	for (auto& goal : m_goals)
	{
		if (goal->IsHitFlag())
		{
			return true;
		}
	}
	return false;
}

//==============================================================================
// ���̏Փˎ擾
//==============================================================================
bool BlockManager::IsHitSpike()
{
	if (m_spikes.empty()) return false;

	for (auto& spike : m_spikes)
	{
		if (spike->IsHitFlag())
		{
			return true;
		}
	}
	return false;
}

//==============================================================================
// �G�N�X�v���[���[����p�X���擾����
//==============================================================================
void BlockManager::ReLoad(const wchar_t* path)
{
	// �J���Ȃ������Ƃ��̂��߂Ɉꎞ�ۑ�����
	std::wstring _tmp = m_stagePath;

	// �_�C�A���O������Ă��Ȃ���Ε������Ԃ��Ȃ�
	if (UserUtility::IsNull(m_dialog.get())) return;

	// �u���b�N�����ׂĔj������
	ClearBlocks();

	// �p�X���Ȃ�������_�C�A���O����J��
	if (path == nullptr)
	{
		auto _path = m_dialog->GetExpFilePath();
		if (not UserUtility::IsNull(_path))
		{
			m_stagePath = _path;
		}
	}
	else
	{
		m_stagePath = path;
	}

	// �t�@�C���̓��e�`�F�b�N(���g����Ȃ�ŏ��̃p�X���đ��)
	if (m_stagePath.empty())
	{
		m_stagePath = _tmp;
	}

	// ����������
	Initialize();
}

//==============================================================================
// �X�e�[�W�������o��
//==============================================================================
void BlockManager::OutputStage()
{
	// �p�X��ݒ�
	auto _path = m_dialog->GetExpFilePath();
	if (not UserUtility::IsNull(_path))
	{
		m_stagePath = _path;
	}
	else
	{
		return;
	}

	// �p�X��ݒ�
	m_jsonHelper->SetPath(m_stagePath.c_str());

	// �I�u�W�F�N�g�z��
	std::vector<IGameObject*> _objects;

	//==============================================================================
	// �ǉ�����̂͂�������>>> �����o���p�z��ɃZ�b�g
	//==============================================================================

	AddWriteObjects(&_objects, m_sands);		// ��
	AddWriteObjects(&_objects, m_clouds);		// �_
	AddWriteObjects(&_objects, m_coins);		// �R�C��
	AddWriteObjects(&_objects, m_chara);		// ����L����
	AddWriteObjects(&_objects, m_goals);		// �S�[��
	AddWriteObjects(&_objects, m_spikes);		// ���G�l�~�[


	//==============================================================================
	// <<<�ǉ�����̂͂����܂�
	//==============================================================================

	// �d�����Ă���f�[�^��P��f�[�^�ɂ���
	std::unordered_map<std::string, Json> _uEntry;
	for (auto& obj : _objects)
	{
		std::string _id = GetBlockID(obj->GetID());
		SimpleMath::Vector3 _pos = obj->GetInitialPosition();

		// �u���b�N�̎�ނƏ����ʒu�����ӂȃL�[�𐶐�
		// ID_X_Y_Z�Ƃ����P��L�[���쐬����(��FSand_1_2_1,Cloud_3_3_7)
		std::string _uKey = _id + "_" + std::to_string(_pos.x) + "_"
			+ std::to_string(_pos.y) + "_" + std::to_string(_pos.z);

		// �L�[�����݂��Ȃ��ꍇ�A�G���g���Ƀf�[�^��ǉ�
		if (_uEntry.find(_uKey) == _uEntry.end())
		{
			_uEntry[_uKey]["Path"] = _id;
			_uEntry[_uKey]["Position"]["X"] = _pos.x;
			_uEntry[_uKey]["Position"]["Y"] = _pos.y;
			_uEntry[_uKey]["Position"]["Z"] = _pos.z;
		}
	}

	// ���j�[�N�G���g�����\�[�g���čŏI�o�͂ɓo�^����
	std::vector<Json> _sortedEntries;
	for (const auto& entry : _uEntry)
	{
		_sortedEntries.push_back(entry.second);
	}

	// �����񂪑����EXZ�����EY�����̗D��x�Ń\�[�g
	std::sort(_sortedEntries.begin(), _sortedEntries.end(), SortPriority());

	// �ŏI�o�͔z��
	Json _output;
	// ���ёւ���Json�f�[�^���ŏI�o�͔z��Ɋi�[
	for (const auto& sortedEntry : _sortedEntries)
	{
		_output.push_back(sortedEntry);    // second = Json�^�f�[�^
	}

	// �C���f���g�����낦�ď����o��
	std::string _str = _output.dump(2);
	m_jsonHelper->Write(_str);
}