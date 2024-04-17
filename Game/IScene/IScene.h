/*
 *	@File	IScene.h
 *	@Brief	���N���X
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ISCENE
#define	ISCENE

#include "Game/GameMain.h"

#include "Libraries/SystemManager/SystemManager.h"
#include "Libraries/Factories/ModelFactory.h"
#include "Libraries/Factories/GeometricFactory.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Libraries/SystemDatas/SoundManager/SoundManager.h"

using SHEDERLAM = std::function<void __cdecl()>; // �����_���̌^

class IScene
{
public:

	// �t�F�[�h�p�J�ڑj�~�֐�
	void StopNextScene() { m_nextScene = SCENE::NONE; is_changeFlag = false; }
	// ��ʃT�C�Y��ݒ�
	void SetWindowSize(const DirectX::SimpleMath::Vector2& size) { m_windowSize = size; }
	// ���̃V�[�����擾
	SCENE GetNextScene() const { return m_nextScene; }
	// �V�[���t���O���擾
	bool IsChangeSceneFlag() const { return is_changeFlag; }
	// �t�F�[�h���x�A�N�Z�T
	float GetFadeSpeed() const { return m_fadeSpeed; }
	void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }
	// �t�F�[�h�l�A�N�Z�T
	float GetFadeValue() const { return m_fadeValue; }
	void SetFadeValue(const float& value) { m_fadeValue = value; }
	// �V�X�e���}�l�[�W�����擾
	const std::shared_ptr<SystemManager>& GetSystemManager() { return m_system; }
	// �J�����̃f�t�H���g�A���O�����擾�i45.0f�j
	const float& GetDefaultCameraAngle() { return DEFAULT_CAMERA_ANGLE; }
	// ��ʂ̃T�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetWindowSize() { return m_windowSize; }
	// �t���X�N���[���T�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetFullHDSize() { return FULL_HD; }
	// �t�F�[�h���I����Ċ��S�Ɏ��s�\�Ȃ�True��Ԃ�
	bool IsCanUpdate() { is_fadeEnd = static_cast<int>(GetFadeValue()) == 0; return is_fadeEnd; }
	// �J�ڐ�̃V�[���ݒ�
	void ChangeScene(const SCENE& nextScene) { m_nextScene = nextScene; is_changeFlag = true; }

	// �R���X�g���N�^
	IScene();
	// �f�X�g���N�^
	virtual ~IScene() = default;
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

private:

	const float DEFAULT_CAMERA_ANGLE = 45.0f;							// �f�t�H���g�̃J�����A���O��
	const DirectX::SimpleMath::Vector2 FULL_HD = { 1920.0f,1080.0f };	// �t���X�N���[���T�C�Y

private:

	// �V�[�����̕ϐ��̏������֐�
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

#endif // ISCENE