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

// �R���X�g���N�^
BlockManager::BlockManager(const wchar_t* stagePath)
	:
	m_stagePath(stagePath),		// �X�e�[�W�p�X���i�[
	is_playing(false)			// �v���C�t���O
{
	// Json�ǂݍ��݃V�X�e���쐬
	m_jsonHelper = std::make_unique<JsonHelper>();
	// �_�C�A���O�A�N�Z�T�쐬
	m_dialog = std::make_unique<DiaLog>();

	// �u���b�N���N���A
	ClearBlocks();
}

// �f�X�g���N�^
BlockManager::~BlockManager()
{
	m_jsonHelper.reset();
	m_dialog.reset();
	m_stagePath.clear();
	ClearBlocks();
}

// ������
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

		// �X��
		if (_name == "Flozen")	m_flozens.push_back(std::make_unique<Flozen>(_position));
		// �_
		if (_name == "Cloud")	m_clouds.push_back(std::make_unique<Cloud>(_position));
		// �R�C��
		if (_name == "Coin")	m_coins.push_back(std::make_unique<Coin>(_position));
		// �v���C��
		if (_name == "Player")	m_chara.push_back(std::make_unique<EditChara>(_position));
		// �S�[��
		if (_name == "Goal")	m_goals.push_back(std::make_unique<Goal>(_position));
		// ��
		if (_name == "Spike")	m_spikes.push_back(std::make_unique<Spike>(_position));
		// ���t�g
		if (_name == "Lift")	m_lifts.push_back(std::make_unique<Lift>(_position));

		// �G�f�B�^���̂ݎ��s
		if (not is_playing)
		{
			// �����ꏊ�ɃG�A�[���������炻�̏ꏊ�̃G�A�[������
			if (not UserUtility::IsNull(m_air[i].get()) &&
				m_air[i]->GetPosition() == _position)
			{
				m_air[i].reset();
			}
		}
	}
}

// �X�V����
void BlockManager::Update()
{
	std::vector<IGameObject*> _objects;

	// --���������Ώ�-- //

	if (is_playing == false)
	{
		for (auto& obj : m_chara)   _objects.push_back(obj.get());	// �L����
		for (auto& obj : m_air)	    _objects.push_back(obj.get());	// �G�A�[
	}
	for(auto& obj : m_flozens)	    _objects.push_back(obj.get());	// �X��
	for(auto& obj : m_clouds)		_objects.push_back(obj.get());	// �_
	for(auto& obj : m_coins)		_objects.push_back(obj.get());	// �R�C��
	for(auto& obj : m_goals)		_objects.push_back(obj.get());	// �S�[��
	for(auto& obj : m_spikes)		_objects.push_back(obj.get());	// ��
	for(auto& obj : m_lifts)		_objects.push_back(obj.get());	// ���t�g

	// �I�u�W�F�N�g�̍X�V
	for (auto& obj : _objects)
	{
		obj->Update();
	}

	// �u�������{��
	ReplaceBlock();
}

// �`�揈��
void BlockManager::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	std::vector<BaseObject*> _objects;

	// --���������Ώ�-- //

	if (is_playing == false)
		for (auto& obj : m_chara)   _objects.push_back(obj.get());	// �L����
	for (auto& obj : m_flozens)	    _objects.push_back(obj.get());	// �X��
	for (auto& obj : m_clouds)		_objects.push_back(obj.get());	// �_
	for (auto& obj : m_coins)		_objects.push_back(obj.get());	// �R�C��
	for (auto& obj : m_goals)		_objects.push_back(obj.get());	// �S�[��
	for (auto& obj : m_spikes)		_objects.push_back(obj.get());	// ��
	for (auto& obj : m_lifts)		_objects.push_back(obj.get());	// ���t�g

	// �I�u�W�F�N�g�̕`��
	for (auto& obj : _objects)
		obj->Draw(context, states, view, proj, wireframe, option);
}

// �I�t�Z�b�g�����Z(�Z���N�g�V�[���Ŏ�ɌĂяo��)
void BlockManager::SetOffset(const SimpleMath::Vector3& offset)
{
	// --���������Ώ�-- //

	for (auto& obj : m_flozens)	// �X��
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_clouds)	// �_
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_coins)	// �R�C��
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_goals)	// �S�[��
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_spikes)	// ��
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_lifts)	// ���t�g
		obj->SetInitialPosition(obj->GetPosition() + offset);
}

// �u���b�N�̎�ނ��珑���o���p�������Ԃ�
std::string BlockManager::GetBlockID(const ID& id)
{
	// --���������Ώ�-- //

	switch (id)
	{
	case ID::Obj_Flozen:	    return "Flozen";// �X��
	case ID::Obj_Cloud:		    return "Cloud";	// �_
	case ID::Obj_Coin:	        return "Coin";	// �R�C��
	case ID::Obj_Player:		return "Player";// �L����
	case ID::Obj_Goal:		    return "Goal";	// �S�[��
	case ID::Obj_Spike:		    return "Spike";	// ��
	case ID::Obj_Lift:		    return "Lift";	// ���t�g
	default:		            return "";
	}
}

// �u���b�N�u����������
void BlockManager::ReplaceBlock()
{
	// --���������Ώ�-- //

	ReplaceObjects(ID::Obj_Flozen, m_flozens);	// �X��
	ReplaceObjects(ID::Obj_Cloud,  m_clouds);	// �_
	ReplaceObjects(ID::Obj_Coin,   m_coins);	// �R�C��
	ReplaceObjects(ID::Obj_Air,    m_air);		// �G�A�[
	ReplaceObjects(ID::Obj_Player, m_chara);	// �L����
	ReplaceObjects(ID::Obj_Goal,   m_goals);	// �S�[��
	ReplaceObjects(ID::Obj_Spike,  m_spikes);	// ��
	ReplaceObjects(ID::Obj_Lift,   m_lifts);	// ���t�g
}

// �u���b�N�쐬
void BlockManager::CreateBlock(ID id, SimpleMath::Vector3 pos)
{
	// --���������Ώ�-- //

	if (id == ID::Obj_Flozen)   m_flozens.push_back(std::make_unique<Flozen>(pos));	 // �X��
	if (id == ID::Obj_Cloud)	m_clouds.push_back(std::make_unique<Cloud>(pos));	 // �_
	if (id == ID::Obj_Coin)		m_coins.push_back(std::make_unique<Coin>(pos));		 // �R�C��
	if (id == ID::Obj_Air)		m_air.push_back(std::make_unique<Air>(pos));		 // �G�A�[
	if (id == ID::Obj_Player)	m_chara.push_back(std::make_unique<EditChara>(pos)); // �L����
	if (id == ID::Obj_Goal)		m_goals.push_back(std::make_unique<Goal>(pos));		 // �S�[��
	if (id == ID::Obj_Spike)	m_spikes.push_back(std::make_unique<Spike>(pos));	 // ��
	if (id == ID::Obj_Lift)		m_lifts.push_back(std::make_unique<Lift>(pos));		 // ���t�g
}

// �u���b�N�z������Z�b�g����
void BlockManager::ClearBlocks()
{
	// --���������Ώ�-- //

	ClearObjects(&m_flozens);		// �X��
	ClearObjects(&m_clouds);		// �_
	ClearObjects(&m_coins);			// �R�C��
	ClearObjects(&m_air);			// �G�A�[
	ClearObjects(&m_chara);			// �L����
	ClearObjects(&m_goals);			// �S�[��
	ClearObjects(&m_spikes);		// ��
	ClearObjects(&m_lifts);			// ���t�g
}

// �X�e�[�W�������o��
void BlockManager::OutputStage()
{
	// �p�X��ݒ�
	auto path = m_dialog->GetExpFilePath();
	if (UserUtility::IsNull(path))	return;
	else m_stagePath = path;

	// �p�X��ݒ�
	m_jsonHelper->SetPath(m_stagePath.c_str());

	// �I�u�W�F�N�g�z��
	std::vector<BaseObject*> object;

	//==============================================================================
	// �ǉ�����̂͂�������>>> �����o���p�z��ɃZ�b�g
	//==============================================================================

	// --���������Ώ�-- //

	AddWriteObjects(&object, m_flozens);	// �X��
	AddWriteObjects(&object, m_clouds);		// �_
	AddWriteObjects(&object, m_coins);		// �R�C��
	AddWriteObjects(&object, m_chara);		// �L����
	AddWriteObjects(&object, m_goals);		// �S�[��
	AddWriteObjects(&object, m_spikes);		// ��
	AddWriteObjects(&object, m_lifts);		// ���t�g


	//==============================================================================
	// <<<�ǉ�����̂͂����܂�
	//==============================================================================

	// �d�����Ă���f�[�^��P��f�[�^�ɂ���
	std::unordered_map<std::string, Json> unique;
	for (auto& obj : object)
	{
		std::string id = GetBlockID(obj->GetID());
		SimpleMath::Vector3 position = obj->GetInitialPosition();

		// �u���b�N�̎�ނƏ����ʒu�����ӂȃL�[�𐶐�
		// ID_X_Y_Z�Ƃ����P��L�[���쐬����(��FFlozen_1_2_1,Cloud_3_3_7)
		std::string uniqueKey = id + "_" + std::to_string(position.x) + "_"
			+ std::to_string(position.y) + "_" + std::to_string(position.z);

		// �L�[�����݂��Ȃ��ꍇ�A�G���g���Ƀf�[�^��ǉ�
		if (unique.find(uniqueKey) == unique.end())
		{
			unique[uniqueKey]["Path"] = id;
			unique[uniqueKey]["Position"]["X"] = position.x;
			unique[uniqueKey]["Position"]["Y"] = position.y;
			unique[uniqueKey]["Position"]["Z"] = position.z;
		}
	}

	// ���j�[�N�G���g�����\�[�g���čŏI�o�͂ɓo�^����
	std::vector<Json> sortedEntries;
	for (const auto& entry : unique)
	{
		sortedEntries.push_back(entry.second);
	}

	// �����񂪑����EXZ�����EY�����̗D��x�Ń\�[�g
	std::sort(sortedEntries.begin(), sortedEntries.end(), OutputSort());

	// �ŏI�o�͏���
	Json output;
	for (const auto& sortedEntry : sortedEntries)
	{
		output.push_back(sortedEntry);
	}

	// �C���f���g�����낦�ď����o��
	std::string str = output.dump(2);
	m_jsonHelper->Write(str);
}

// �G�A�[�Ŗ��߂�
void BlockManager::FillAir()
{
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			for (int z = 0; z < MAP_SIZE_Z; z++)
			{
				float fx = static_cast<float>(x);
				float fy = static_cast<float>(y);
				float fz = static_cast<float>(z);
				SimpleMath::Vector3 pos = SimpleMath::Vector3(fx, fy, fz);
				m_air.push_back(std::make_unique<Air>(pos));
			}
		}
	}
}

// �v���C���[�̍��W���擾����
SimpleMath::Vector3 BlockManager::GetPlayerPosition() const
{
	SimpleMath::Vector3 pos;

	// �v���C���[���P�����Ȃ��ꍇ�͂��̍��W��Ԃ�
	// �v���C���[���Q�ȏ゠��ꍇ�̓����_���ŕԂ�
	if (m_chara.size() == 1)
	{
		pos = m_chara[0]->GetInitialPosition();
	}
	else
	{
		// �����𐶐�����
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, static_cast<int>(m_chara.size()) - 1);

		// �����_����1�l�̃v���C���[��I�сA���̍��W��Ԃ�
		int idx = dist(gen);
		pos = m_chara[idx]->GetInitialPosition();
	}

	return pos;
}

// �S�[������擾
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

// ���̏Փˎ擾
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

// �G�N�X�v���[���[����p�X���擾����
void BlockManager::ReLoad(const wchar_t* path)
{
	// �J���Ȃ������Ƃ��̂��߂Ɉꎞ�ۑ�����
	std::wstring tmp = m_stagePath;

	// �_�C�A���O������Ă��Ȃ���Ε������Ԃ��Ȃ�
	if (UserUtility::IsNull(m_dialog.get())) return;

	// �u���b�N�����ׂĔj������
	ClearBlocks();

	// �p�X���Ȃ�������_�C�A���O����J��
	if (UserUtility::IsNull(path))
	{
		auto p = m_dialog->GetExpFilePath();
		if (not UserUtility::IsNull(p))
		{
			m_stagePath = p;
		}
	}
	else
	{
		m_stagePath = path;
	}

	// �t�@�C���̓��e�`�F�b�N(���g����Ȃ�ŏ��̃p�X���đ��)
	if (m_stagePath.empty())
	{
		m_stagePath = tmp;
	}

	// ����������
	Initialize();
}
