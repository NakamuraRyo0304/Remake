/*
 *  @File   Diary.h
 *  @Brief  ���L�B
 *  @Date   2024-04-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DIARY
#define DIARY

class DrawSprite;
class Diary
{
public:

	// �R���X�g���N�^
	Diary();
	// �f�X�g���N�^
	~Diary();
	// ������
	void Initialize(float time, int collect, int maxCoin);
	// �X�V
	void Update();
	// �`��
	void Draw();

private:

	// ���������߂ĕ�������擾
	std::wstring CalcTimePer(const float& time) const;
	std::wstring CalcCoinPer(const int& collect, const int& max) const;

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;
	// �F
	DirectX::SimpleMath::Vector4 m_color;
};

#endif // DIARY