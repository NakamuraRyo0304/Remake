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
// --���������Ώ�-- //

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

		// --���������Ώ�-- //

		// �X���u���b�N���i�[
		if (_name == "Flozen")	m_flozens.push_back(std::make_unique<Flozen>(_position));
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
		// ���t�g�u���b�N���i�[
		if (_name == "Lift")	m_lifts.push_back(std::make_unique<Lift>(_position));

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
	std::vector<IGameObject*> _objects;

	// --���������Ώ�-- //

	if (is_playing == false)
	{
		for (auto& obj : m_chara)   _objects.push_back(obj.get());
		for (auto& obj : m_air)	    _objects.push_back(obj.get());
	}
	for(auto& obj : m_flozens)	    _objects.push_back(obj.get());
	for(auto& obj : m_clouds)		_objects.push_back(obj.get());
	for(auto& obj : m_coins)		_objects.push_back(obj.get());
	for(auto& obj : m_goals)		_objects.push_back(obj.get());
	for(auto& obj : m_spikes)		_objects.push_back(obj.get());
	for(auto& obj : m_lifts)		_objects.push_back(obj.get());

	// �I�u�W�F�N�g�̍X�V
	for (auto& obj : _objects)
	{
		obj->Update();
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
	std::vector<IGameObject*> _objects;

	// --���������Ώ�-- //

	if (is_playing == false)
		for (auto& obj : m_chara)   _objects.push_back(obj.get());
	for (auto& obj : m_flozens)	    _objects.push_back(obj.get());
	for (auto& obj : m_clouds)		_objects.push_back(obj.get());
	for (auto& obj : m_coins)		_objects.push_back(obj.get());
	for (auto& obj : m_goals)		_objects.push_back(obj.get());
	for (auto& obj : m_spikes)		_objects.push_back(obj.get());
	for (auto& obj : m_lifts)		_objects.push_back(obj.get());

	// �I�u�W�F�N�g�̕`��
	for (auto& obj : _objects)
		obj->Draw(context, states, view, proj, wireframe, option);
}

//==============================================================================
// �I�t�Z�b�g�����Z(�Z���N�g�V�[���Ŏ�ɌĂяo��)
//==============================================================================
void BlockManager::SetOffset(const SimpleMath::Vector3& offset)
{
	// --���������Ώ�-- //

	for (auto& obj : m_flozens)	// �X���u���b�N
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_clouds)	// �_�u���b�N
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_coins)	// �R�C��
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_goals)	// �S�[���I�u�W�F�N�g
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_spikes)	// ���I�u�W�F�N�g
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_lifts)	// ���t�g�u���b�N
		obj->SetInitialPosition(obj->GetInitialPosition() + offset);
}

//==============================================================================
// �u���b�N�̎�ނ��珑���o���p�������Ԃ�
//==============================================================================
std::string BlockManager::GetBlockID(const ID& id)
{
	// --���������Ώ�-- //

	switch (id)
	{
	case ID::Obj_Flozen:	    return "Flozen";
	case ID::Obj_Coin:	        return "Coin";
	case ID::Obj_Cloud:		    return "Cloud";
	case ID::Obj_Player:		return "Player";
	case ID::Obj_Goal:		    return "Goal";
	case ID::Obj_Spike:		    return "Spike";
	case ID::Obj_Lift:		    return "Lift";
	default:		            return "";
	}
}

//==============================================================================
// �u���b�N�u����������
//==============================================================================
void BlockManager::ReplaceBlock()
{
	// --���������Ώ�-- //

	for (auto& obj : m_flozens)		// �X���u���b�N
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Flozen)    continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_flozens, obj);
	}
	for (auto& obj : m_clouds)		// �_�u���b�N
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Cloud)     continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_clouds, obj);
	}
	for (auto& obj : m_coins)		// �R�C��
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Coin)      continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_coins, obj);
	}
	for (auto& obj : m_air)			// �G�A�[
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Air)       continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_air, obj);
	}
	for (auto& obj : m_chara)		// �L����
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Player)    continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_chara, obj);
	}
	for (auto& obj : m_goals)		// �S�[���I�u�W�F�N�g
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Goal)      continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_goals, obj);
	}
	for (auto& obj : m_spikes)		// ��
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Spike)     continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_spikes, obj);
	}
	for (auto& obj : m_lifts)		// ���t�g�u���b�N
	{
		if (UserUtility::IsNull(obj.get()))    continue;
		if (obj->GetID() == ID::Obj_Lift)      continue;
		CreateBlock(obj->GetID(), obj->GetInitialPosition());
		UserUtility::RemoveVec(m_lifts, obj);
	}
}

//==============================================================================
// �u���b�N�쐬
//==============================================================================
void BlockManager::CreateBlock(ID id, SimpleMath::Vector3 pos)
{
	// --���������Ώ�-- //

	// ID����v�������m��ǉ�����

	if (id == ID::Obj_Flozen)	// �X���u���b�N
		m_flozens.push_back(std::make_unique<Flozen>(pos));
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
	if (id == ID::Obj_Lift)		// ���t�g�u���b�N
		m_lifts.push_back(std::make_unique<Lift>(pos));
}

//==============================================================================
// �u���b�N�z������Z�b�g����
//==============================================================================
void BlockManager::ClearBlocks()
{
	// --���������Ώ�-- //

	m_flozens.clear();
	m_clouds.clear();
	m_coins.clear();
	m_air.clear();
	m_chara.clear();
	m_goals.clear();
	m_spikes.clear();
	m_lifts.clear();
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
SimpleMath::Vector3 BlockManager::GetPlayerPosition() const
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
bool BlockManager::IsArrived() const
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
bool BlockManager::IsHitSpike() const
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
	if (UserUtility::IsNull(path))
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

	// --���������Ώ�-- //

	AddWriteObjects(&_objects, m_flozens);		// �X
	AddWriteObjects(&_objects, m_clouds);		// �_
	AddWriteObjects(&_objects, m_coins);		// �R�C��
	AddWriteObjects(&_objects, m_chara);		// ����L����
	AddWriteObjects(&_objects, m_goals);		// �S�[��
	AddWriteObjects(&_objects, m_spikes);		// ���G�l�~�[
	AddWriteObjects(&_objects, m_lifts);		// ���t�g


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