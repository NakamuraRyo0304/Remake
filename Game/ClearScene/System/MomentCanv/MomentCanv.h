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

	// ���W
	DirectX::SimpleMath::Vector2 m_position;

	// ��ʊg�嗦
	DirectX::SimpleMath::Vector2 m_screenRate;

private:

	// �ŏI���W
	static const DirectX::SimpleMath::Vector2 LAST_POSITION;

	// �摜�̉�]�p�x
	static const float LAST_ROTATE;

	// �ړ��E��]���x
	static const float SPEED_TO_LAST;

	// ��ʊO�̍��W
	static const DirectX::SimpleMath::Vector2 OUT_POSITION;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenRate">��ʊg�嗦</param>
	/// <returns>�Ȃ�</returns>
	MomentCanv(DirectX::SimpleMath::Vector2 screenRate);
	~MomentCanv();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="color">�F</param>
	/// <param name="rate">�g�嗦</param>
	/// <param name="origin">���S�ʒu</param>
	/// <param name="rect">�؂���ʒu</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate, DirectX::SimpleMath::Vector2 origin, RECT_U rect);
};

#endif // MOMENTCANV