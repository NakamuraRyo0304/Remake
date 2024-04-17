/*
 *  @File   BG_Select.h
 *  @Brief  �o�b�N�O���E���h�B
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BG_SELECT
#define BG_SELECT

class DrawSprite;
class BG_Select
{
public:

	// �R���X�g���N�^
	BG_Select();
	// �f�X�g���N�^
	~BG_Select();
	// ������
	void Initialize();
	// �`��
	void Draw();

private:

	// �A���t�@�l
	static const float ALPHA;

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;

};

#endif // BG_SELECT