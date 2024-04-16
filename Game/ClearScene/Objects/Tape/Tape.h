/*
 *  @File   Tape.h
 *  @Brief  �e�[�v�B
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TAPE
#define TAPE

class DrawSprite;
class Tape
{
public:

	// �R���X�g���N�^
	Tape();
	// �f�X�g���N�^
	~Tape();
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

#endif // TAPE