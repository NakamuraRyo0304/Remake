/*
 *	@File	Stage0Camera.h
 *	@Brief	�X�e�[�W�O�i�G�f�B�^�j�̃Z���N�g�J�����B
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

// �e�J�����N���X
#include "Game/Bases/BaseCamera.h"

#ifndef STAGE0CAMERA
#define STAGE0CAMERA

class Stage0Camera : public BaseCamera
{
public:

	// �R���X�g���N�^
	Stage0Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~Stage0Camera();
	// �X�V����
	void Update() override;
};

#endif // STAGE0CAMERA