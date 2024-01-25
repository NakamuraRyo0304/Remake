/*
 *	@File	SoundManager.cpp
 *	@Brief	SE�̍Đ��Ɏg���}�l�[�W���N���X�B
 *	@Date	2023-09-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "SoundManager.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
SoundManager::SoundManager()
	: m_volumes{ 1.0f }
{
	AUDIO_ENGINE_FLAGS _eFlags = AudioEngine_Default;
#ifdef _DEBUG
	_eFlags |= AudioEngine_Debug;
#endif
	m_audioEngine = std::make_unique<AudioEngine>(_eFlags);

	m_waveBank = std::make_unique<WaveBank>(m_audioEngine.get(), L"Resources/Sounds/AudioPack.xwb");

	// ���\�[�X�̍쐬
	Create();

	for (auto& i : m_volumes)
	{
		i = 1.0f;
	}
}

//==============================================================================
// ����炷
//==============================================================================
void SoundManager::PlaySound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, SE_MODE playType)
{
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Stop();
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Play(playType);

	// �Ȃ炵���猳�ɖ߂�
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = 1.0f;
}

//==============================================================================
// �I�[�f�B�I�G���W���̍X�V
//==============================================================================
void SoundManager::Update()
{
	// �I�[�f�B�I�G���W���̍X�V
	if (!m_audioEngine->Update())
	{
		// No audio device is active
		if (m_audioEngine->IsCriticalError())
		{
			OutputDebugString(L"AudioEngine Error!\n");
		}
	}
}

//==============================================================================
// ���ʐݒ�
//==============================================================================
void SoundManager::SetVolume(const float& volume, const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME)
{
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = volume;
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->SetVolume(
		m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]);
}

//==============================================================================
// ���̌���
//==============================================================================
void SoundManager::FadeVolume(const float& speed)
{
	for (int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		m_volumes[i] -= speed;
		m_soundEffectInstances[i]->SetVolume(m_volumes[i]);
	}
}

//==============================================================================
// �T�E���h�G�t�F�N�g�C���X�^���X�̐��G�t
//==============================================================================
void SoundManager::Create()
{
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		// �T�E���h�G�t�F�N�g�C���X�^���X���쐬����
		m_soundEffectInstances[i] = m_waveBank->CreateInstance(i);
		m_volumes[i] = 1.0f;
	}
}
