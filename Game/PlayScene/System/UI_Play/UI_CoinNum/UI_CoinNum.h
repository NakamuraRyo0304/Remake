/*
 *  @File   UI_CoinNum.h
 *  @Brief  �v���C�V�[����UI�̃R�C�����B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_COINNUM
#define UI_COINNUM

class DrawNumber;
class UI_CoinNum
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
	// �R�C���̖�����ݒ�
	void SetCoinNum(const int& num) { m_coinNum = num; }
	// �R�C���̍ő吔��ݒ�
	void SetCoinMaxNum(const int& num) { m_maxCoinNum = num; }


	// �R���X�g���N�^
	UI_CoinNum();
	// �f�X�g���N�^
	~UI_CoinNum();
	// ������
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate, DirectX::SimpleMath::Vector2 scRate);
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
	// �R�C����
	int m_coinNum, m_maxCoinNum;
};

#endif // UI_COINNUM