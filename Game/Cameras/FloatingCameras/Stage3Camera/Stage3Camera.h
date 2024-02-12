/*
 *	@File	Stage3Camera.h
 *	@Brief	�X�e�[�W�R�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE3CAMERA
#define STAGE3CAMERA

class Stage3Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	Stage3Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage3Camera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
};

#endif // STAGE3CAMERA