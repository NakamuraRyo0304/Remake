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
const float Player::MAX_SPEED = 0.78f;		// �ō����x
const float Player::RANGE = 0.6f;			// �ō����ő��锼�a
const float Player::ARRIVE_RADIUS = 0.1f;	// �����݂Ȃ����a
const float Player::GIVEUP_TIME = 120.0f;	// �ړ����߃^�C�����~�b�g
const float Player::DEATH_LINE = -5.0f;		// ���S���C��
const float Player::DEATH_ROTATE = 30.0f;	// ���S���̉�]
const float Player::ROTATE_SPEED = 0.5f;	// ���񑬓x
const float Player::SCALE = 0.5f;			// ���f���̃X�P�[��
const float Player::GRAVITY = -0.05f;		// �d��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Player::Player()
	: IGameObject(L"Resources/Models/pBody.cmo", L"Resources/Models")
	, m_velocity{}			                // �ړ���
	, m_coinNum{ 0 }		                // �擾�ς݃R�C������
	, m_giveUpTime{}						// ���߃^�C��
	, is_fall{ true }		                // �����t���O
	, is_death{ false }		                // ���S�t���O
	, is_coinHit{ false }		            // �R�C���Փ˃t���O
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * SCALE);
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
	// �ړI�n�����݂��Ă��邩�������̏ꍇ�A�ړI�n��ǐՂ���
	if (not m_goalPoints.empty() && not is_death)
	{
		m_giveUpTime--;

		// �S�[�����W�̍������v���C���[�Ɠ��������ɂ���
		m_goalPoints[0].y = GetPosition().y;

		// �ڕW�ʒu�̕������v�Z����
		SimpleMath::Vector3 _dir = UserUtility::GetDirectionVector(GetPosition(), m_goalPoints[0]);
		_dir.Normalize();

		// �ړI�n�܂ł̋������v�Z
		auto _distanceToGoal = (m_goalPoints[0] - GetPosition()).Length();

		// ���x�̐ݒ�(�S�[�����ӗ̈���Ȃ�ō����x�ő���)
		float _speed = 0.0f;
		_speed = _distanceToGoal > RANGE ? MAX_SPEED : MAX_SPEED * (_distanceToGoal / RANGE);

		// �ړ����x�𒲐�
		SimpleMath::Vector3 _velocity = _dir * _speed;
		SimpleMath::Vector3 _newPosition = UserUtility::Lerp(GetPosition(), GetPosition() + _velocity);
		SetPosition(_newPosition);

		// �i�s�����ɍ��킹�ĉ�]
		float _angle = std::atan2(-_dir.x, -_dir.z);
		SimpleMath::Vector3 _rotation(0.0f, _angle, 0.0f);
		SetRotate(UserUtility::Lerp(GetRotate(), _rotation, ROTATE_SPEED));

		// ���ݒn����S�[���܂ł̋���
		float _hereToGoalDistance = SimpleMath::Vector3::Distance(GetPosition(), m_goalPoints[0]);

		// ���������� or ���Ԃ������肷���������
		if (_hereToGoalDistance < ARRIVE_RADIUS || m_giveUpTime < 0.0f)
		{
			UserUtility::RemoveVec(m_goalPoints, m_goalPoints[0]);
			m_giveUpTime = GIVEUP_TIME;
		}

		// ���s�X�e�[�g�ɕύX
		m_head->SetStatus(MoveStates::Walking);
	}
	else
	{
		m_giveUpTime = GIVEUP_TIME;

		// �A�C�h���X�e�[�g�ɕύX
		m_head->SetStatus(MoveStates::Idling);
	}

	// �����t���O��ON�̏ꍇ�A�d�͂�������
	if (is_fall)
	{
		SetPosition(GetPosition() + SimpleMath::Vector3::UnitY * GRAVITY);
	}

	// �}�g���N�X���v�Z
	CreateWorldMatrix();

	// ���S����
	if (GetPosition().y < DEATH_LINE)
	{
		is_death = true;
	}
	if (GetPosition().y < DEATH_LINE / 2)
	{
		float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());

		// ��]���Ȃ��痎���Ă���
		SetRotate(GetRotate() + SimpleMath::Vector3::UnitY * XMConvertToRadians(_timer * DEATH_ROTATE));
	}

	// �p�[�c�̍X�V
	m_head->Update();

	// �}�g���N�X���쐬
	m_head->SetParentMatrix(GetWorldMatrix());
}

//==============================================================================
// �`�揈��
//==============================================================================
void Player::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(SCALE);
	GetModel()->Draw(context, states, _scale * GetWorldMatrix(), view, proj, wireframe, option);

	// ����ȍ~�A�q�p�[�c�̕`����s��
	m_head->Draw(context, states, view, proj, wireframe, option);
}

//==============================================================================
// �ǐՃp�X��ǉ�����
//==============================================================================
void Player::AddFollowPath(const SimpleMath::Vector3& path, const int& max)
{
	// �ő吔���z������ǉ����Ȃ�
	if (m_goalPoints.size() >= max) return;

	m_goalPoints.push_back(path);
}
