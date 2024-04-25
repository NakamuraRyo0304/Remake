/*
 *	@File	UI_Play.h
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_PLAY
#define UI_PLAY

// �e�V�[���N���X
#include "Game/Bases/BaseUI.h"

class CoinNum;
class PlayArea;
class DrawKeys;
class UI_Play final : public BaseUI
{
public:

	// �R�C���̖�����ݒ�
	void SetCoinNum(const int& num) { m_coinNum = num; }
	// ���g���C�{�^���̏󋵎擾
	bool IsPushRetry() const { return is_retryPush; }

	// �R���X�g���N�^
	UI_Play(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// �f�X�g���N�^
	~UI_Play();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

public:

	// �L�[�̖��O
	enum KEY_NAME
	{
		WKEY,
		SKEY,
		AKEY,
		DKEY,
		RKEY,

		Length__key
	};

private:

	// UI�G���A
	std::unique_ptr<PlayArea> m_area;
	// �R�C����
	std::unique_ptr<CoinNum> m_coins;
	// ����t���O
	bool is_retryPush;
	// �L�[�`��
	std::map<KEY_NAME, std::unique_ptr<DrawKeys>> m_keys;
	// �摜�`��
	std::unique_ptr<DrawSprite> m_sprite;
	DirectX::SimpleMath::Vector2 m_coinTexPos, m_cameraTexPos;
	// �R�C����
	int m_coinNum;

};

#endif // UI_PLAY