/*
 *	@File	Stage4Camera.h
 *	@Brief	�X�e�[�W�S�̃Z���N�g�J�����B
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

// �e�J�����N���X
#include "Game/Bases/BaseCamera.h"

#ifndef STAGE4CAMERA
#define STAGE4CAMERA

class Stage4Camera : public BaseCamera
{
public:

	// �R���X�g���N�^
	Stage4Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~Stage4Camera();
	// �X�V����
	void Update() override;
};

#endif // STAGE4CAMERA