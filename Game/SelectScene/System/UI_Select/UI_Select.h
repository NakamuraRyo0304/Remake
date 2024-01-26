/*
 *	@File	UI_Select.h
 *	@Brief	�Z���N�gUI�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_SELECT
#define UI_SELECT

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Select final : public IUserInterface
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	UI_Select(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Select();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw() override;

};

#endif // UI_SELECT