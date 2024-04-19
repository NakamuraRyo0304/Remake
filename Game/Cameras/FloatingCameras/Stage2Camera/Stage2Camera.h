/*
 *	@File	Stage2Camera.h
 *	@Brief	�X�e�[�W�Q�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

// �e�J�����N���X
#include "Game/Bases/BaseCamera.h"

#ifndef STAGE2CAMERA
#define STAGE2CAMERA

class Stage2Camera : public BaseCamera
{
public:

	// �R���X�g���N�^
	Stage2Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~Stage2Camera();
	// �X�V����
	void Update() override;
};

#endif // STAGE2CAMERA