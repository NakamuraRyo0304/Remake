/*
 *  @File   BaseUI.h
 *  @Brief  UI�̊��N���X�B
 *  @Date   2024-04-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BASEUI
#define BASEUI

// �C���^�[�t�F�[�X
#include "Game/Interfaces/IUserInterface.h"

// ���ʋ@�\
#include "Libraries/SystemDatas/Button/Button.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class BaseUI : public IUserInterface
{
public:

	// ��ʊg�嗦���擾
	const DirectX::SimpleMath::Vector2& GetScreenRate() { return m_screenRate; }
	// ��ʃT�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetScreenSize() { return m_screenSize; }
	// �ő��ʃT�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetMaxScreenSize() { return m_maxScreenSize; }


	// �R���X�g���N�^
	BaseUI(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// �f�X�g���N�^
	~BaseUI();

private:

	// ��ʃT�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;
	// �ő��ʃT�C�Y
	DirectX::SimpleMath::Vector2 m_maxScreenSize;
	// ��ʊg�嗦
	DirectX::SimpleMath::Vector2 m_screenRate;

};

#endif // BASEUI