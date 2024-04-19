/*
 * @File   BaseUI.cpp
 * @Brief  UI�̊��N���X�B
 * @Date   2024-04-19
 * @Author NakamuraRyo
 */

#include "pch.h"
#include "BaseUI.h"

// �R���X�g���N�^
BaseUI::BaseUI(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	m_screenSize(scS),			// ��ʃT�C�Y
	m_maxScreenSize(mscs),		// �ő��ʃT�C�Y
	m_screenRate(scS / mscs)	// ��ʔ䗦
{
}

// �f�X�g���N�^
BaseUI::~BaseUI()
{
}
