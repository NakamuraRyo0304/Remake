/*
 *  @File   ScoreBoard.h
 *  @Brief  �Q�[���̃X�R�A��\������B
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SCOREBOARD
#define SCOREBOARD

class DrawNumber;
class ScoreBoard
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
	// ���l��ݒ�
	void SetNumber(const int& num) { m_number = num; }

	// �R���X�g���N�^
	ScoreBoard();
	// �f�X�g���N�^
	~ScoreBoard();
	// ������
	void Initialize(DirectX::SimpleMath::Vector2 pos,
		DirectX::SimpleMath::Vector4 color, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 scRate, double span);
	// �`��
	void Draw();

private:

	// �P�X�v���C�g�̃T�C�Y
	static const UINT SIZE;

private:

	// ������`�悷��
	std::unique_ptr<DrawNumber> m_nums[2];
	// ���W
	DirectX::SimpleMath::Vector2 m_position;
	// �F
	DirectX::SimpleMath::Vector4 m_color;
	// ���l
	int m_number;

};

#endif // SCOREBOARD