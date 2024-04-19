/*
 *	@File	Stage3Camera.h
 *	@Brief	�X�e�[�W�R�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

// �e�J�����N���X
#include "Game/Bases/BaseCamera.h"

#ifndef STAGE3CAMERA
#define STAGE3CAMERA

class Stage3Camera : public BaseCamera
{
public:

	// �R���X�g���N�^
	Stage3Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~Stage3Camera();
	// �X�V
	void Update() override;
};

#endif // STAGE3CAMERA