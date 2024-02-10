/*
 *  @File   MomentCanv.h
 *  @Brief  �N���A�����u�Ԃ̉摜��\������B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef MOMENTCANV
#define MOMENTCANV

//==============================================================================
// �X�v���C�g�`��N���X
//==============================================================================
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class MomentCanv
{
private:

	// �X�v���C�g�`��
	std::unique_ptr<DrawSprite> m_sprite;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	MomentCanv();
	~MomentCanv();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize();

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="color">�F</param>
	/// <param name="rate">�g�嗦</param>
	/// <param name="origin">���S�ʒu</param>
	/// <param name="rect">�؂���ʒu</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate, DirectX::SimpleMath::Vector2 origin, RECT_U rect);
};

#endif // MOMENTCANV