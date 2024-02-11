/*
 *  @File   DrawNumber.h
 *  @Brief  �����̕`��N���X�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWNUMBER
#define DRAWNUMBER

//==============================================================================
// �X�v���C�g�`��
//==============================================================================
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class DrawNumber
{
private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;

	// ���W�E���S�ʒu
	DirectX::SimpleMath::Vector2 m_position, m_origin;

	// �g�嗦
	DirectX::SimpleMath::Vector2 m_rate;

	// �F
	DirectX::SimpleMath::Vector4 m_color;

	// ���N�g
	RECT_U m_rect;


private:

	// �X�v���C�g�̃T�C�Y(�P�u���b�N)
	static const UINT SIZE;

public:

	// �f�B�W�b�g
	enum Digits
	{
		One,
		Ten,

		Length
	};

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	DrawNumber();
	~DrawNumber();

	/// <summary>
	/// ������`�悷��
	/// </summary>
	/// <param name="num">����</param>
	/// <param name="digits">����</param>
	/// <returns>�Ȃ�</returns>
	void Draw(UINT num, Digits digits);

private:

	/// <summary>
	/// ������؂���
	/// </summary>
	/// <param name="num">����</param>
	/// <returns>���N�g</returns>
	RECT_U Cut(UINT num);

public:

	// ���W���擾����
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// ���W��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// �g�嗦���擾����
	const DirectX::SimpleMath::Vector2& GetRate() { return m_rate; }
	// �g�嗦��ݒ肷��
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }
	// �F���擾����
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// �F��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

};

#endif // DRAWNUMBER