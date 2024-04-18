/*
 *	@File	IScene.h
 *	@Brief	�V�[���̃C���^�[�t�F�[�X
 *	@Date	2024-04-18
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ISCENE
#define	ISCENE

class IScene
{
public:

	// �R���X�g���N�^
	IScene() = default;
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

	// �V�[�����̕ϐ��̏������֐�
	virtual void SetSceneValues() = 0;
	// �f�o�b�O�`��
	virtual void DebugDraw(DirectX::CommonStates& states) = 0;

};

#endif // ISCENE