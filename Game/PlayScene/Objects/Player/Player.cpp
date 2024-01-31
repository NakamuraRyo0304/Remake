/*
 *	@File	Player.cpp
 *	@Brief	�v���C���[�B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "Player.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const int Player::MAX_PATH_NUM = 3;			// �ő�p�X��
const float Player::MAX_SPEED = 1.0f;		// �ō����x
const float Player::MS_RADIUS = 0.5f;		// �ō����ő��锼�a
const float Player::ARRIVE_RADIUS = 0.1f;	// �����݂Ȃ����a
const float Player::GIVEUP_TIME = 120.0f;	// �ړ����߃^�C�����~�b�g

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Player::Player()
	: IGameObject(L"Resources/Models/Body.cmo", L"Resources/Models")
	, m_velocity{}			// �ړ���
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
	SetInitialScale(GetScale());

	// �p�[�c�̍쐬
	m_head = std::make_unique<Head>();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Player::~Player()
{
	m_goalPoints.clear();
	m_head.reset();
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Player::Update()
{
	// �z�񂪋󂶂�Ȃ������瓮����
	if (not m_goalPoints.empty())
	{
		m_giveUpTime--;

		// �S�[�����W�̍������v���C���[�Ɠ��������ɂ���
		m_goalPoints[0].y = GetPosition().y;

		// �ڕW�ʒu�̕������v�Z����
		SimpleMath::Vector3 _dir = UserUtility::GetDirectionVector(GetPosition(), m_goalPoints[0]);
		_dir.Normalize();

		// �ړI�n�܂ł̋������v�Z
		auto _distanceToGoal = (m_goalPoints[0] - GetPosition()).Length();

		// ���x�̐ݒ�
		float _speed = 0.0f;
		if (_distanceToGoal > MS_RADIUS)
		{
			_speed = MAX_SPEED;
		}
		else
		{
			_speed = MAX_SPEED * (_distanceToGoal / MS_RADIUS);
		}

		// �ړ����x�𒲐�
		SimpleMath::Vector3 _velocity = _dir * _speed;
		SimpleMath::Vector3 _newPosition = UserUtility::Lerp(GetPosition(), GetPosition() + _velocity, 0.1f);
		SetPosition(_newPosition);

		// �i�s�����ɍ��킹�ĉ�]
		float _angle = std::atan2(-_dir.x, -_dir.z);
		SimpleMath::Vector3 _rotation(0.0f, _angle, 0.0f);
		SetRotate(UserUtility::Lerp(GetRotate(), _rotation, 0.1f));

		// ���ݒn����S�[���܂ł̋���
		float _hereToGoalDistance = SimpleMath::Vector3::Distance(GetPosition(), m_goalPoints[0]);

		// ���������� or ���Ԃ������肷���������
		if (_hereToGoalDistance < ARRIVE_RADIUS || m_giveUpTime < 0.0f)
		{
			UserUtility::RemoveVec(m_goalPoints, m_goalPoints[0]);
			m_giveUpTime = GIVEUP_TIME;
		}
	}
	else
	{
		m_giveUpTime = GIVEUP_TIME;
	}

	// �}�g���N�X���v�Z
	CreateWorldMatrix();

	// �p�[�c�̍X�V
	m_head->Update();

	// �}�g���N�X���쐬
	m_head->SetParentMatrix(GetWorldMatrix());
}

//==============================================================================
// �`�揈��
//==============================================================================
void Player::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(0.5f);
	GetModel()->Draw(_context, states, _scale * GetWorldMatrix(), view, proj, false, no_use_here);

	m_head->Draw(states, view, proj, no_use_here);
}

//==============================================================================
// �ǐՃp�X��ǉ�����
//==============================================================================
void Player::PushBackFollowPath(SimpleMath::Vector3 path)
{
	// �ő吔���z������ǉ����Ȃ�
	if (m_goalPoints.size() >= MAX_PATH_NUM) return;

	m_goalPoints.push_back(path);
}
