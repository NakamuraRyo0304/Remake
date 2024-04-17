/*
 *  @File   Logo.h
 *  @Brief  �^�C�g�����S�B
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LOGO
#define LOGO

class DrawSprite;
class Logo
{
public:

	// �F���擾����
	DirectX::SimpleMath::Vector4 GetColor() const { return m_color; }
	// �F��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

	// �R���X�g���N�^
	Logo(DirectX::SimpleMath::Vector2 scRate);
	// �f�X�g���N�^
	~Logo();
	// ������
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color, DirectX::SimpleMath::Vector2 rate);
	// �`��
	void Draw();

private:

	// �摜�T�C�Y
	static const RECT_U SIZE;

private:

	// ��ʔ䗦
	DirectX::SimpleMath::Vector2 m_screenRate;
	// �X�v���C�g�`��
	std::unique_ptr<DrawSprite> m_sprite;
	// ���W
	DirectX::SimpleMath::Vector2 m_position;
	// �g�嗦
	DirectX::SimpleMath::Vector2  m_rate;
	// �F
	DirectX::SimpleMath::Vector4 m_color;

};

#endif // LOGO