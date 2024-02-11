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

class DrawNumber;
class UI_PlayArea;
class UI_Play final : public IUserInterface
{
private:

	// ������`�悷��
	std::unique_ptr<DrawNumber> m_nums[4];

	// UI�G���A
	std::unique_ptr<UI_PlayArea> m_area;

	// �R�C����
	int m_coinNum, m_maxCoinNum;


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
	// �R�C���̍ő吔��ݒ�
	void SetCoinMaxNum(const int& num) { m_maxCoinNum = num; }

};

#endif // UI_PLAY