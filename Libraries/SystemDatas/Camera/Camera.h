/*
 *	@File	Camera.h
 *	@Brief	�J�����̐ݒ�B
 *	@Date	2023-04-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CAMERA
#define CAMERA

class Camera
{
public:
	// �X�N���[���T�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

public:
	static const float DEFAULT_CAMERA_DISTANCE;	// �^�[�Q�b�g����̋���
	static const float DEFAULT_CAMERA_SPEED;	// �ړ����x
	static const float ARROW_SPEED;				// ��󑀍�̑��x
	static const int MAX_SCROLL_VALUE;			// �X�N���[������l
	static const int MIN_SCROLL_VALUE;			// �X�N���[�������l
	static const float FAR_PLANE;				// ���e�ŉ��l
	static const float NEAR_PLANE;				// ���e�ŋߒl
	static const float ANGLE_X_MAX;				// X����]�̏���l
	static const float ANGLE_X_MIN;				// X����]�̉����l

private:

	// �X�N���[�����W�A�z�C�[���l�A���[�h
	struct PrevMouse { DirectX::SimpleMath::Vector2 pos; int wheel; bool eagle; };

	// �O��̃}�E�X���
	PrevMouse m_prevMouse;

	// �}�E�X�z�C�[���̃X�N���[���l
	int m_scrollWheelValue;

	// ��]�p
	DirectX::SimpleMath::Vector2 m_angle;

	// �r���[�s��/�v���W�F�N�V�����s��/��]�s��
	DirectX::SimpleMath::Matrix m_view, m_projection, m_rotateMatrix;

	// �J�����̍��W/���Z�l
	DirectX::SimpleMath::Vector3 m_position, m_addEye;

	// �����_/���Z�l
	DirectX::SimpleMath::Vector3 m_target, m_addTarget;

	// ���_�ړ����[�h
	bool is_eagleMode, is_allowMode, is_zeroClamp;

public:
	Camera();
	~Camera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

private:
	/// <summary>
	/// �}�E�X�̃h���b�O�����������v�Z
	/// </summary>
	/// <param name="x">�X�N���[�����WX</param>
	/// <param name="y">�X�N���[�����WY</param>
	/// <returns>�Ȃ�</returns>
	void DraggedDistance(int x, int y);

	/// <summary>
	/// �r���[�s��̌v�Z
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void CalculateViewMatrix();

//--------------------------------------------------------//
//�A�N�Z�T                                                //
//--------------------------------------------------------//
public:
	/// <summary>
	/// �ˉe�s����쐬
	/// </summary>
	/// <param name="size">��ʃT�C�Y</param>
	/// <param name="angle">�J������p</param>
	/// <returns>�ˉe�s��</returns>
	const DirectX::SimpleMath::Matrix& CreateProjection(DirectX::SimpleMath::Vector2 size,float angle = 45.0f);
	/// <summary>
	/// �r���[�s����擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�r���[�s��</returns>
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }
	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�v���W�F�N�V�����s��</returns>
	const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	/// <summary>
	/// �J�����̈ʒu���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�J�����̈ʒu</returns>
	const DirectX::SimpleMath::Vector3& GetEyePosition() { return m_addEye; }
	/// <summary>
	/// �^�[�Q�b�g�̈ʒu���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�^�[�Q�b�g�̈ʒu</returns>
	const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	/// <summary>
	/// �J�����̈ʒu�����Z
	/// </summary>
	/// <param name="pos">���Z���W</param>
	/// <returns>�Ȃ�</returns>
	void AddEyePosition(const DirectX::SimpleMath::Vector3& pos) { m_addEye = pos; }
	/// <summary>
	/// �J�����̒����_�̈ʒu�����Z
	/// </summary>
	/// <param name="pos">���Z���W</param>
	/// <returns>�Ȃ�</returns>
	void AddTargetPosition(const DirectX::SimpleMath::Vector3& pos) { m_addTarget = pos; }
	/// <summary>
	/// �J�����̊p�x��ݒ�
	/// </summary>
	/// <param name="angle">�p�x</param>
	/// <returns>�Ȃ�</returns>
	void SetCameraAngle(const DirectX::SimpleMath::Vector2& angle) { m_angle = angle; }
	/// <summary>
	/// �}�E�X����̗L����
	/// </summary>
	/// <param name="flag">�g�p����True</param>
	/// <returns>�J�������}�E�X����\�ɂȂ�</returns>
	void SetEagleMode(const bool& flag = true) { is_eagleMode = flag; }
	/// <summary>
	/// �\���L�[����̗L����
	/// </summary>
	/// <param name="flag">�g�p����True</param>
	/// <returns>�J�������\���L�[����\�ɂȂ�</returns>
	void SetArrowMode(const bool& flag = true) { is_allowMode = flag; }
	/// <summary>
	/// �}�E�X�̃[���N�����v�̐؂�ւ�
	/// </summary>
	/// <param name="flag">�g�p����True</param>
	/// <returns>�}�E�X�z�C�[����0������0�ɐ؂肠����</returns>
	void IsZeroClamp(const bool& flag = true) { is_zeroClamp = flag; }

};

#endif // CAMERA
