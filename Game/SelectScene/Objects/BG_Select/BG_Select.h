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
private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;

private:

	// �A���t�@�l
	static const float ALPHA;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	BG_Select();
	~BG_Select();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize();

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw();
};

#endif // BG_SELECT