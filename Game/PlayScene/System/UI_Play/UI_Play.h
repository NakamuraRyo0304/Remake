/*
 *	@File	UI_Play.h
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_PLAY
#define UI_PLAY

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_CoinNum;
class UI_PlayArea;
class UI_Play final : public IUserInterface
{
private:

	// UI�G���A
	std::unique_ptr<UI_PlayArea> m_area;

	// �R�C����
	std::unique_ptr<UI_CoinNum> m_coins;

	// �R�C����
	int m_coinNum;

private:

	static const DirectX::SimpleMath::Vector4 BLACK;
	static const DirectX::SimpleMath::Vector4 WHITE;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	UI_Play(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Play();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw() override;

	// �R�C���̖�����ݒ�
	void SetCoinNum(const int& num) { m_coinNum = num; }
};

#endif // UI_PLAY