/*
 *  @File   Seal.h
 *  @Brief  �V�[���B
 *  @Date   2024-02-15
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SEAL
#define SEAL

class DrawSprite;
class Seal
{
public:

	// �R���X�g���N�^
	Seal(const wchar_t* path);
	// �f�X�g���N�^
	~Seal();
	// ������
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 scRate, float rotate);
	// �`��
	void Draw();

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;
	// ���W
	DirectX::SimpleMath::Vector2 m_position;
	// �摜�g�嗦
	DirectX::SimpleMath::Vector2 m_rate;
	// ��ʔ䗦
	DirectX::SimpleMath::Vector2 m_scRate;

};

#endif // SEAL