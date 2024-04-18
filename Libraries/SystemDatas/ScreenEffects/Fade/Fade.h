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
public:

	// �t�F�[�h�̍ő�l�̎擾
	float GetMaxValue() const { return MAX_NUM; }
	// �t�F�[�h�I���𔻒肷��֐�
	bool GetEndFlag() const { return is_endFlag; }
	// �t�F�[�h�̒l�擾
	float GetFadeValue() const { return m_fadeValue; }
	// �t�F�[�h�̑��x�ݒ�
	void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }
	// ���[���摜�̕ύX
	void SetRuleTexture(const wchar_t* path = L"Resources/Textures/Transitions/Rule_Rot.png") { m_filePath = path; }

	// �R���X�g���N�^
	Fade(float speed);
	// �f�X�g���N�^
	~Fade();
	// ������
	void Initialize();
	// �X�V
	void Update(DirectX::XMVECTORF32 color);
	// �`��
	void Draw();
	// �t�F�[�h�C�����J�n
	void SetFadeIn();
	// �t�F�[�h�A�E�g���J�n
	void SetFadeOut();
	// ���Z�b�g
	void Reset();

private:

	// �ő�l/�ŏ��l
	const float MAX_NUM = 255.0f;
	const float MIN_NUM = 0.0f;
	const float SPEED = 1.5f;

private:

	// �g�����W�V����
	std::unique_ptr<Transition> m_transition;
	// ���[���摜�̃p�X
	const wchar_t* m_filePath;
	// �t�F�[�h���x
	float m_fadeSpeed;
	// �t�F�[�h�̐��l0-255
	float m_fadeValue;
	// �t�F�[�h�C�����J�n����t���O
	bool is_fadeInFlag;
	// �t�F�[�h�A�E�g���J�n����t���O
	bool is_fadeOutFlag;
	// �t�F�[�h�I������t���O
	bool is_endFlag;

};

#endif // FADE