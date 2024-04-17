/*
 *	@File	SoundManager.cpp
 *	@Brief	SEの再生に使うマネージャクラス。
 *	@Date	2023-09-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "SoundManager.h"

// コンストラクタ
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

	// リソースの作成
	Create();

	for (auto& volume : m_volumes)
	{
		volume = 1.0f;
	}
}

// 音を鳴らす
void SoundManager::PlaySound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, SE_MODE playType)
{
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Stop();
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Play(playType);

	// ならしたら元に戻す
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = 1.0f;
}

// 音を止める
void SoundManager::StopSound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME)
{
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->Stop();
}

// 更新
void SoundManager::Update()
{
	// オーディオエンジンの更新
	if (!m_audioEngine->Update())
	{
		if (m_audioEngine->IsCriticalError())
		{
			OutputDebugString(L"AudioEngine Error!\n");
		}
	}
}

// 音量を取得
const float& SoundManager::GetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME)
{
	return m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME];
}

// 音量を設定
void SoundManager::SetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, float volume)
{
	// 音量を設定する（範囲は0.0から1.0）
	m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME]->SetVolume(volume);

	// ボリュームを保持
	m_volumes[XACT_WAVEBANK_AUDIOPACK_TYPE_NAME] = volume;
}

// サウンドエフェクトインスタンスの作成
void SoundManager::Create()
{
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		// サウンドエフェクトインスタンスを作成する
		m_soundEffectInstances[i] = m_waveBank->CreateInstance(i);
		m_volumes[i] = 1.0f;
	}
}

// 初期設定
void SoundManager::InitAllSounds(const float& volume)
{
	// 音量を初期化する
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		SetVolume(static_cast<XACT_WAVEBANK_AUDIOPACK>(i), volume);
	}

	// 全ての音を停止する
	for (unsigned int i = 0; i < XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT; ++i)
	{
		StopSound(static_cast<XACT_WAVEBANK_AUDIOPACK>(i));
	}
}