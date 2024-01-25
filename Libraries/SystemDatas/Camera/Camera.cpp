/*
 *	@File	Camera.cpp
 *	@Brief	�J�����̐ݒ�B
 *	@Date	2023-04-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Camera.h"

//==============================================================================
// �萔�̏�����
//==============================================================================
const float Camera::DEFAULT_CAMERA_DISTANCE = 20.0f;	// �^�[�Q�b�g����̋���
const float Camera::DEFAULT_CAMERA_SPEED = 0.05f;		// �ړ����x
const float Camera::ARROW_SPEED = 0.01f;				// ��󑀍�̑��x
const int	Camera::MAX_SCROLL_VALUE = 2000;			// �X�N���[������l
const int	Camera::MIN_SCROLL_VALUE = -1000;			// �X�N���[�������l
const float Camera::FAR_PLANE = 245.0f;					// ���e�ŉ��l
const float Camera::NEAR_PLANE = 0.1f;					// ���e�ŋߒl
const float Camera::ANGLE_X_MAX = 45.5f;				// X����]�̏���l
const float Camera::ANGLE_X_MIN = 44.0f;				// X����]�̉����l

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Camera::Camera()
	: m_screenSize{}			// ��ʂ̃T�C�Y
	, m_angle{}					// ��]�p
	, m_position{}				// ���W
	, m_addEye{}				// �ڐ��̉��Z���W
	, m_addTarget{}				// �����_�̉��Z���W
	, m_prevMouse{}				// �ߋ��̃}�E�X�̈ʒu
	, m_scrollWheelValue{}		// �}�E�X�z�C�[���̉�]��
	, m_view{}					// �r���[�s��
	, m_projection{}			// �v���W�F�N�V�����s��
	, m_rotateMatrix{}			// ��]��
	, is_allowMode{ false }		// �J�����̎��_�ړ��t���O(�\������)
	, is_eagleMode{ false }		// �J�����̎��_�ړ��t���O(�}�E�X����)
	, is_zeroClamp{ false }		// �}�E�X�z�C�[���̃[���N�����v
{
	// �}�E�X�̏������Z�b�g
	Mouse::Get().ResetScrollWheelValue();
	m_prevMouse.pos = SimpleMath::Vector2::Zero;
	m_prevMouse.wheel = 0;
	m_prevMouse.eagle = false;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Camera::~Camera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void Camera::Update()
{
	// �L�[�{�[�h�̃C���X�^���X�擾
	auto _kb = Keyboard::Get().GetState();
	// �}�E�X�̃C���X�^���X�擾
	auto _ms = Mouse::Get().GetState();

	// �}�E�X�̍��N���b�N���h���b�O�ŃJ�������W���X�V����
	if (_ms.leftButton)
	{
		// ���_�ړ����Ȃ���Ώ������Ȃ�
		if (not is_eagleMode) return;

		// �}�E�X�̃h���b�O�ɂ��J�����ړ�
		DraggedDistance(_ms.x, _ms.y);
	}

	// �}�E�X�̍��W��O��̒l�Ƃ��ĕۑ�
	m_prevMouse.pos.x = static_cast<float>(_ms.x); // X���W��ۑ�
	m_prevMouse.pos.y = static_cast<float>(_ms.y); // Y���W��ۑ�

	if (is_eagleMode)
	{
		m_scrollWheelValue = _ms.scrollWheelValue;
		if (m_scrollWheelValue > 0)
		{
			if (is_zeroClamp)
			{
				m_scrollWheelValue = 0;
				Mouse::Get().ResetScrollWheelValue();
			}
		}
	}

	// �r���[�s��̎Z�o
	CalculateViewMatrix();

	// �\���X�C�b�`���I�t�Ȃ瓮�����Ȃ�
	if (not is_allowMode) return;

	// �ړ���
	SimpleMath::Vector2 _moveVal = SimpleMath::Vector2::Zero;

	// �ړ��ʂ�ݒ�
	if (_kb.Right) { _moveVal.y =  ARROW_SPEED; }
	if (_kb.Left)  { _moveVal.y = -ARROW_SPEED; }
	if (_kb.Up)    { _moveVal.x =  ARROW_SPEED; }
	if (_kb.Down)  { _moveVal.x = -ARROW_SPEED; }

	// �p�x�ύX
	m_angle += _moveVal;
}

//==============================================================================
// �h���b�O���������̌v�Z
//==============================================================================
void Camera::DraggedDistance(int x, int y)
{
	// �}�E�X�|�C���^�̑O�񂩂�̕ψ�
	// DEFAULT_CAMERA_SPEED����Z���ăh���b�O�̈ړ��ʂ𒲐�����
	float _dx = static_cast<float>(x - m_prevMouse.pos.x) * DEFAULT_CAMERA_SPEED;
	float _dy = static_cast<float>(y - m_prevMouse.pos.y) * DEFAULT_CAMERA_SPEED;

	if (_dx != 0.0f || _dy != 0.0f)
	{
		// �}�E�X�|�C���^�̕ψʂ����ɁA�w���x���̉�]�p�����߂�
		float _angleX = _dy * XM_PI / 180.0f;
		float _angleY = _dx * XM_PI / 180.0f;

		// �p�x�̍X�V
		m_angle.x += _angleX;
		m_angle.y += _angleY;
	}
}

//==============================================================================
// �v���W�F�N�V�����s��̌v�Z
//==============================================================================
const SimpleMath::Matrix& Camera::CreateProjection(SimpleMath::Vector2 size, float angle)
{
	// ��ʃT�C�Y�ƃA���O���̕ۑ�
	m_screenSize = size;

	// ��p
	float _fieldOfView = XMConvertToRadians(angle);

	// ��ʏc����
	float _aspectRatio = size.x / size.y;

	// �J���������ԋ߂����e��
	float _nearPlane = NEAR_PLANE;

	// �J���������ԉ������e��
	float _farPlane = FAR_PLANE;

	// �J�����̃����Y�̍쐬
	SimpleMath::Matrix _projection =
		SimpleMath::Matrix::CreatePerspectiveFieldOfView(
			_fieldOfView, _aspectRatio, _nearPlane, _farPlane);

	// �J������p
	m_angle.x = angle;

	return m_projection = _projection;
}

//==============================================================================
// �r���[�s��̌v�Z
//==============================================================================
void Camera::CalculateViewMatrix()
{
	// �r���[�s����Z�o����
	SimpleMath::Matrix _rotY = SimpleMath::Matrix::CreateRotationY(m_angle.y);
	SimpleMath::Matrix _rotX = SimpleMath::Matrix::CreateRotationX(m_angle.x);

	// ��]�ʂ��v�Z
	SimpleMath::Matrix _rt = _rotY * _rotX;
	m_rotateMatrix = _rt;

	// �|�W�V����
	SimpleMath::Vector3    _eye(0.0f, 0.1f, 1.0f);

	// �J�����̌X���i�ڐ��̊p�x)
	SimpleMath::Vector3     _up(0.0f, 1.0f, 0.0f);
	SimpleMath::Vector3 _target(0.0f, 0.0f, 0.0f);

	_eye = SimpleMath::Vector3::Transform(_eye, _rt.Invert());
	_eye *= (DEFAULT_CAMERA_DISTANCE - static_cast<float>(m_scrollWheelValue / 100));
	_up  = SimpleMath::Vector3::Transform(_up,  _rt.Invert());

	// �f�t�H���g�̏����ʒu
	m_position = _eye + m_addEye;
	m_target = _target + m_addTarget;
	m_view = SimpleMath::Matrix::CreateLookAt(m_position, m_target, _up);
}