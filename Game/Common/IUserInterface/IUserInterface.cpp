/*
 *	@File	IUserInterface.cpp
 *	@Brief	UI�N���X�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "IUserInterface.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
IUserInterface::IUserInterface(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: m_maxScreenSize{ mscs }		// �ő�T�C�Y
	, m_screenSize{ scS }			// ��ʃT�C�Y
	, m_screenRate{ scS / mscs }	// ��ʊg�嗦
{
}
