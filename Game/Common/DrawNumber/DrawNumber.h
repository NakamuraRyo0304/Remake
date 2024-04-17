/*
 *  @File   DrawNumber.h
 *  @Brief  �����̕`��N���X�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWNUMBER
#define DRAWNUMBER

// �X�v���C�g�`��
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class DrawNumber
{
public:

	// �f�B�W�b�g
	enum Digits
	{
		One,
		Ten,

		Length
	};

public:

	// ���W���擾����
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// ���W��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// �����g�嗦���擾����
	const DirectX::SimpleMath::Vector2& GetRate() { return m_rate; }
	// �����g�嗦��ݒ肷��
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }
	// ��ʊg�嗦��ݒ肷��
	void SetScreenRate(const DirectX::SimpleMath::Vector2& rate) { m_screenRate = rate; }
	// �F���擾����
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// �F��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

	// �R���X�g���N�^
	DrawNumber();
	// �f�X�g���N�^
	~DrawNumber();
	// �`��
	void Draw(UINT num, Digits digits);

private:

	// �X�v���C�g�̃T�C�Y(�P�u���b�N)
	static const UINT SIZE;

private:

	// ������؂���
	RECT_U Cut(UINT num);

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;
	// ���W
	DirectX::SimpleMath::Vector2 m_position;
	// ���S���W
	DirectX::SimpleMath::Vector2 m_origin;
	// �����g�嗦
	DirectX::SimpleMath::Vector2 m_rate;
	// ��ʊg�嗦
	DirectX::SimpleMath::Vector2 m_screenRate;
	// �F
	DirectX::SimpleMath::Vector4 m_color;
	// ���N�g
	RECT_U m_rect;

};

#endif // DRAWNUMBER