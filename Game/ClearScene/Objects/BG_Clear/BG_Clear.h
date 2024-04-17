/*
 *  @File   BG_Clear.h
 *  @Brief  �o�b�N�O���E���h�B
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BG_CLEAR
#define BG_CLEAR

class DrawSprite;
class BG_Clear
{
public:

	// �R���X�g���N�^
	BG_Clear();
	// �f�X�g���N�^
	~BG_Clear();
	// ������
	void Initialize();
	/// �`��
	void Draw();

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;
};

#endif // BG_CLEAR