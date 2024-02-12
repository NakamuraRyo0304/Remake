/*
 *	@File	Stage4Camera.h
 *	@Brief	�X�e�[�W�S�̃Z���N�g�J�����B
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE4CAMERA
#define STAGE4CAMERA

class Stage4Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	Stage4Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage4Camera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
};

#endif // STAGE4CAMERA