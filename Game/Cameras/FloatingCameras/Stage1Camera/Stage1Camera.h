/*
 *	@File	Stage1Camera.h
 *	@Brief	�X�e�[�W�P�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE1CAMERA
#define STAGE1CAMERA

class Stage1Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	Stage1Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage1Camera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
};

#endif // STAGE1CAMERA