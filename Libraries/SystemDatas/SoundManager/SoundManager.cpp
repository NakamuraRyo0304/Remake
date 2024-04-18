/*
 *	@File	SoundManager.cpp
 *	@Brief	SE�̍Đ��Ɏg���}�l�[�W���N���X�B
 *	@Date	2023-09-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "SoundManager.h"

// �R���X�g���N�^
SoundManager::SoundManager()
	:
	m_volumes{ 1.0f }
{
	AUDIO_ENGINE_FLAGS engine = AudioEngine_Default;
#ifdef _DEBUG
	engine |= AudioEngine_Debug;
#endif
	m_audioEngine = std::make_unique<AudioEngine>(engine);

	m_waveBank = std::make_unique<WaveBank>(m_audioEngine.get(), L"Resources/Sounds/AudioPack.xwb");

	// ���\�[�X�̍쐬
	Create();

	for (auto& volume : m_volumes)
	{
		volume = 1.0f;
	}
}

// ����炷
void SoundManager::PlaySound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, SE_MODE playType)
{
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Stop();
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Play(playType);

	// �Ȃ炵���猳�ɖ߂�
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = 1.0f;
}

// �����~�߂�
void SoundManager::StopSound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME)
{
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Stop();
}

// �X�V
void SoundManager::Update()
{
	// �I�[�f�B�I�G���W���̍X�V
	if (!m_audioEngine->Update())
	{
		if (m_audioEngine->IsCriticalError())
		{
			OutputDebugString(L"AudioEngine Error!\n");
		}
	}
}

// ���ʂ��擾
const float& SoundManager::GetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME)
{
	return m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME];
}

// ���ʂ�ݒ�
void SoundManager::SetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, float volume)
{
	// ���ʂ�ݒ肷��i�͈͂�0.0����1.0�j
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->SetVolume(volume);

	// �{�����[����ێ�
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = volume;
}

// �T�E���h�G�t�F�N�g�C���X�^���X�̍쐬
void SoundManager::Create()
{
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		// �T�E���h�G�t�F�N�g�C���X�^���X���쐬����
		m_soundEffectInstances[i] = m_waveBank->CreateInstance(i);
		m_volumes[i] = 1.0f;
	}
}

// �����ݒ�
void SoundManager::InitAllSounds(const float& volume)
{
	// ���ʂ�����������
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		SetVolume(static_cast<XACT_WAVEBANK_AUDIOPACK>(i), volume);
	}

	// �S�Ẳ����~����
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		StopSound(static_cast<XACT_WAVEBANK_AUDIOPACK>(i));
	}
}