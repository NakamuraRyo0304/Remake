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

//==============================================================================
// ���C�u����
//==============================================================================
#include "Libraries/SystemManager/SystemManager.h"
#include "Libraries/Factories/ModelFactory.h"
#include "Libraries/Factories/GeometricFactory.h"
#include "Libraries/UserUtility.h"
// �V���O���g��
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Libraries/SystemDatas/SoundManager/SoundManager.h"
//==============================================================================
// �G�C���A�X��錾
//==============================================================================
using SHEDERLAM = std::function<void __cdecl()>;						// �����_���̌^

class IScene
{
private:

	std::shared_ptr<SystemManager> m_system;							// �V�X�e���}�l�[�W��
	DirectX::SimpleMath::Vector2 m_windowSize;							// �E�B���h�E�T�C�Y
	SCENE m_nextScene;													// ���̃V�[�����w�肷��
	bool is_changeFlag;													// �V�[���؂�ւ�����t���O
	float m_fadeSpeed;													// �t�F�[�h���x
	float m_fadeValue;													// �t�F�[�h�l
	bool is_fadeEnd;													// �t�F�[�h�I��

private:

	const float DEFAULT_CAMERA_ANGLE = 45.0f;							// �f�t�H���g�̃J�����A���O��
	const DirectX::SimpleMath::Vector2 FULL_HD = { 1920.0f,1080.0f };	// �t���X�N���[���T�C�Y

private:

	// �V�[�����̕ϐ��̏������֐�
	virtual void SetSceneValues() = 0;

	// �f�o�b�O�`��
	virtual void DebugDraw(DirectX::CommonStates& states) = 0;

public:

	//==============================================================================
	// ���ʊ֐��̒�`
	//==============================================================================

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

	// �I������
	virtual void Finalize() = 0;

	// ��ʈˑ��̏�����
	virtual void CreateWDResources() = 0;

public:

	//==============================================================================
	// �V�[�����Ŏg�p����
	//==============================================================================

	// �V�X�e���}�l�[�W�����擾
	inline const std::shared_ptr<SystemManager>& GetSystemManager() { return m_system; }

	// �J�����̃f�t�H���g�A���O�����擾�i45.0f�j
	inline const float& GetDefaultCameraAngle() { return DEFAULT_CAMERA_ANGLE; }

	// ��ʂ̃T�C�Y���擾
	inline const DirectX::SimpleMath::Vector2& GetWindowSize() { return m_windowSize; }

	// �t���X�N���[���T�C�Y���擾
	inline const DirectX::SimpleMath::Vector2& GetFullHDSize() { return FULL_HD; }

	// �t�F�[�h���I����Ċ��S�Ɏ��s�\�Ȃ�True��Ԃ�
	inline const bool& IsCanUpdate()
	{
		is_fadeEnd = static_cast<int>(GetFadeValue()) == 0;
		return is_fadeEnd;
	}

	// �J�ڐ�̃V�[���ݒ�
	inline void ChangeScene(const SCENE& nextScene)
	{
		m_nextScene = nextScene;
		is_changeFlag = true;
	}

	//==============================================================================
	// �Q�[�����C�����Ŏg�p����
	//==============================================================================

	// �t�F�[�h�p�J�ڑj�~�֐�
	inline void StopNextScene() { m_nextScene = SCENE::NONE; is_changeFlag = false;	}

	// ��ʃT�C�Y��ݒ肷��
	inline void SetWindowSize(const DirectX::SimpleMath::Vector2& size) { m_windowSize = size; }

	// ���̃V�[�����Q�b�g
	inline const SCENE& GetNextScene() { return m_nextScene; }

	// �V�[���t���O���Q�b�g
	inline const bool& IsChangeSceneFlag() { return is_changeFlag; }

	// �t�F�[�h���x�A�N�Z�T
	inline const float& GetFadeSpeed() { return m_fadeSpeed; }
	inline void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }

	// �t�F�[�h�l�A�N�Z�T
	inline const float& GetFadeValue() { return m_fadeValue; }
	inline void SetFadeValue(const float& value) { m_fadeValue = value; }
};

#endif // ISCENE