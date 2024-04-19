/*
 *  @File   BaseScene.h
 *  @Brief  �V�[���̊��N���X�B
 *  @Date   2024-04-18
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BASESCENE
#define BASESCENE

// �C���^�[�t�F�[�X
#include "Game/Interfaces/IScene.h"

#include "Libraries/UserUtility.h"
#include "Libraries/SystemManager/SystemManager.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Libraries/SystemDatas/SoundManager/SoundManager.h"

using SHEDERLAM = std::function<void __cdecl()>; // �����_���̌^

// TODO: �V�[���P�F�V�[��ID�̒ǉ�
enum class SCENE : int
{
	NONE,       // ID����

	TITLE,      // �^�C�g���V�[��
	SELECT,     // �Z���N�g�V�[��
	PLAY,       // �Q�[���V�[��
	EDIT,       // ����V�[��
	CLEAR,      // �N���A�V�[��
	EXIT,       // �I��
};

class BaseScene : public IScene
{
public:

	// �V�X�e���}�l�[�W�����擾
	const std::shared_ptr<SystemManager>& GetSystemManager() { return m_system; }
	// ���̃V�[�����擾
	SCENE GetNextScene() const { return m_nextScene; }
	// �V�[���t���O���擾
	bool IsChangeSceneFlag() const { return is_changeFlag; }
	// ���s�\��Ԃ��擾
	bool IsCanUpdate() { is_fadeEnd = static_cast<int>(GetFadeValue()) == 0; return is_fadeEnd; }

	// �t�F�[�h�p�J�ڑj�~�֐�
	void StopNextScene() { m_nextScene = SCENE::NONE; is_changeFlag = false; }
	// ��ʂ̃T�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetWindowSize() { return m_windowSize; }
	// ��ʃT�C�Y��ݒ�
	void SetWindowSize(const DirectX::SimpleMath::Vector2& size) { m_windowSize = size; }

	// �t�F�[�h���x�A�N�Z�T
	float GetFadeSpeed() const { return m_fadeSpeed; }
	void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }

	// �t�F�[�h�l�A�N�Z�T
	float GetFadeValue() const { return m_fadeValue; }
	void SetFadeValue(const float& value) { m_fadeValue = value; }

	// �J�ڐ�̃V�[���ݒ�
	void ChangeScene(const SCENE& nextScene) { m_nextScene = nextScene; is_changeFlag = true; }

	// �R���X�g���N�^
	BaseScene();
	// �f�X�g���N�^
	virtual ~BaseScene() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
	// �I��
	virtual void Finalize() = 0;
	// ��ʈˑ��̏�����
	virtual void CreateWDResources() = 0;

public:

	// �f�t�H���g�̃J�����A���O��
	const float DEFAULT_CAMERA_ANGLE = 45.0f;
	// �t���X�N���[���T�C�Y
	const DirectX::SimpleMath::Vector2 FULL_HD = { 1920.0f,1080.0f };

private:

	// �V�[�����̕ϐ��̏�����
	virtual void SetSceneValues() = 0;
	// �f�o�b�O�`��
	virtual void DebugDraw(DirectX::CommonStates& states) = 0;

private:

	std::shared_ptr<SystemManager> m_system;							// �V�X�e���}�l�[�W��
	DirectX::SimpleMath::Vector2 m_windowSize;							// �E�B���h�E�T�C�Y
	SCENE m_nextScene;													// ���̃V�[�����w�肷��
	float m_fadeSpeed;													// �t�F�[�h���x
	float m_fadeValue;													// �t�F�[�h�l
	bool is_fadeEnd;													// �t�F�[�h�I��
	bool is_changeFlag;													// �V�[���؂�ւ�����t���O

};

#endif // BASESCENE