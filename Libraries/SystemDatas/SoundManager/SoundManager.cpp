/*
 *	@File	SoundManager.cpp
 *	@Brief	SEの再生に使うマネージャクラス。
 *	@Date	2023-09-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "SoundManager.h"

//==============================================================================
// コンストラクタ
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

	// リソースの作成
	Create();

	for (auto& i : m_volumes)
	{
		i = 1.0f;
	}
}

//==============================================================================
// 音を鳴らす
//==============================================================================
void SoundManager::PlaySound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, SE_MODE playType)
{
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Stop();
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Play(playType);

	// ならしたら元に戻す
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = 1.0f;
}

//==============================================================================
// オーディオエンジンの更新
//==============================================================================
void SoundManager::Update()
{
	// オーディオエンジンの更新
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
// 音量設定
//==============================================================================
void SoundManager::SetVolume(const float& volume, const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME)
{
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = volume;
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->SetVolume(
		m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]);
}

//==============================================================================
// 音の減衰
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
// サウンドエフェクトインスタンスの正絵師
//==============================================================================
void SoundManager::Create()
{
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		// サウンドエフェクトインスタンスを作成する
		m_soundEffectInstances[i] = m_waveBank->CreateInstance(i);
		m_volumes[i] = 1.0f;
	}
}
