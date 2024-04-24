/*
 *  @File   PlayArea.h
 *  @Brief  �v���C�V�[����UI�̃G���A�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYAREA
#define PLAYAREA

class DrawSprite;
class PlayArea
{
public:

	// ���W���擾
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// �F���擾
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// �F��ݒ�
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

	// �R���X�g���N�^
	PlayArea();
	// �f�X�g���N�^
	~PlayArea();
	// ������
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate);
	// �`��
	void Draw();

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;
	// ���W
	DirectX::SimpleMath::Vector2 m_position;
	// �g�嗦
	DirectX::SimpleMath::Vector2 m_rate;
	// �F
	DirectX::SimpleMath::Vector4 m_color;

};

#endif // PLAYAREA