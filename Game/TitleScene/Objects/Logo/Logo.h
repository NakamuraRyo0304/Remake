/*
 *  @File   Logo.h
 *  @Brief  �^�C�g�����S�B
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LOGO
#define LOGO

class Logo
{
private:

	// ��ʔ䗦
	DirectX::SimpleMath::Vector2 m_screenRate;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scRate">��ʔ䗦</param>
	/// <returns>�Ȃ�</returns>
	Logo(DirectX::SimpleMath::Vector2 scRate);
	~Logo();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize();

};

#endif // LOGO