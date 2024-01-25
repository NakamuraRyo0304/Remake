/*
 *	@File	Fade.h
 *	@Brief	��ʑJ�ڎ��̃t�F�[�h�����B
 *	@Date	2023-06-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FADE
#define FADE

class Transition;
class Fade
{
private:
	// �g�����W�V����
	std::unique_ptr<Transition> m_transition;

	// ���[���摜�̃p�X
	const wchar_t* m_filePath;

private:

	// �t�F�[�h�C�����J�n����t���O
	bool is_fadeInFlag;

	// �t�F�[�h�A�E�g���J�n����t���O
	bool is_fadeOutFlag;

	// �t�F�[�h���x
	float m_fadeSpeed;

	// �t�F�[�h�I������t���O
	bool is_endFlag;

	// �t�F�[�h�̐��l0-255
	float m_fadeValue;

private:

	// �ő�l/�ŏ��l
	const float MAX_NUM = 255.0f;
	const float MIN_NUM = 0.0f;
	const float SPEED = 1.5f;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="speed">�t�F�[�h�̑��x</param>
	/// <returns>�Ȃ�</returns>
	Fade(float speed);
	~Fade();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="color">�F���</param>
	/// <returns>�Ȃ�</returns>
	void Update(DirectX::XMVECTORF32 color);
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw();
	/// <summary>
	/// �t�F�[�h�C�����J�n����֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void SetFadeIn();
	/// <summary>
	/// �t�F�[�h�A�E�g���J�n����֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void SetFadeOut();
	/// <summary>
	/// �t�F�[�h�������s���O�ɌĂяo���֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Reset();

	/// <summary>
	/// �t�F�[�h�̍ő�l�̎擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�t�F�[�h�̍ő�l</returns>
	const float& GetMaxValue() { return MAX_NUM; }
	/// <summary>
	/// �t�F�[�h�I���𔻒肷��֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�t�F�[�h�I����True</returns>
	const bool& GetEndFlag() { return is_endFlag; }
	/// <summary>
	/// �t�F�[�h�̒l�擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�t�F�[�h�̒l</returns>
	const float& GetFadeValue() { return m_fadeValue; }
	/// <summary>
	/// �t�F�[�h�̑��x�ݒ�
	/// </summary>
	/// <param name="speed">�t�F�[�h���x</param>
	/// <returns>�Ȃ�</returns>
	void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }
	/// <summary>
	/// ���[���摜�̕ύX
	/// </summary>
	/// <param name="path">�摜�p�X</param>
	/// <returns>�Ȃ�</returns>
	void SetRuleTexture(const wchar_t* path = L"Resources/Textures/Transitions/Rule_Rot.png") { m_filePath = path; }
};

#endif // FADE