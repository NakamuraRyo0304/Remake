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
private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	BG_Clear();
	~BG_Clear();

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

#endif // BG_CLEAR