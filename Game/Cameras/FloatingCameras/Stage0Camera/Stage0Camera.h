/*
 *	@File	Stage0Camera.h
 *	@Brief	�X�e�[�W�O�i�G�f�B�^�j�̃Z���N�g�J�����B
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE0CAMERA
#define STAGE0CAMERA

class Stage0Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	Stage0Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage0Camera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
};

#endif // STAGE0CAMERA