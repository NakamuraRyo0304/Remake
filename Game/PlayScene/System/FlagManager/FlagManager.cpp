/*
 *  @File   FlagManager.cpp
 *  @Brief  ���Ǘ��N���X�B
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "../../Objects/Flag/Flag.h"	// �t���O
#include  "Libraries/UserUtility.h"
#include "FlagManager.h"

// �R���X�g���N�^
FlagManager::FlagManager()
	:
	m_firstPosition()		// �擪���W
{
}

// �f�X�g���N�^
FlagManager::~FlagManager()
{
	m_flags.clear();
}

// �X�V
void FlagManager::Update()
{
	if (m_flags.empty()) return;

	// �擪���W��ۑ�
	m_firstPosition = m_flags[0]->GetPosition();

	for (int i = 0; i < m_flags.size(); i++)
	{
		m_flags[i]->Update();
	}
}

// �`��
void FlagManager::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	if (m_flags.empty()) return;

	for (int i = 0; i < m_flags.size(); i++)
	{
		m_flags[i]->Draw(context, states, view, proj, wireframe, option);
	}
}

// �t���O��ǉ�
void FlagManager::AddFlag(SimpleMath::Vector3 start, SimpleMath::Vector3 dropped, const int& max)
{
	// �ő吔���z������ǉ����Ȃ�
	if (m_flags.size() >= max) return;

	m_flags.push_back(std::make_unique<Flag>(start, dropped));
}

// �t���O���폜
void FlagManager::PickFlag()
{
	UserUtility::RemoveVec(m_flags, m_flags[0]);
}

// �擪�̃t���O��������������TRUE
bool FlagManager::IsFirstArrived()
{
	if (m_flags.empty()) return false;

	if (m_flags[0]->IsArrive())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �擪�̍��W���擾
const SimpleMath::Vector3& FlagManager::GetFirstPath()
{
	if (m_flags.empty()) return SimpleMath::Vector3::Zero;

	return m_firstPosition;
}
