/*
 *	@File	Stage1Camera.h
 *	@Brief	�X�e�[�W�P�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

// �e�J�����N���X
#include "Game/Bases/BaseCamera.h"

#ifndef STAGE1CAMERA
#define STAGE1CAMERA

class Stage1Camera : public BaseCamera
{
public:

	// �R���X�g���N�^
	Stage1Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~Stage1Camera();
	// �X�V����
	void Update() override;
};

#endif // STAGE1CAMERA