/*
 *	@File	SoundManager.h
 *	@Brief	SEの再生に使うマネージャクラス。
 *	@Date	2023-09-08
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SOUNDMANAGER
#define SOUNDMANAGER

 // サウンドリスト
#include "SoundList.h"

class SoundManager
{
public:

    // 再生モード
    enum SE_MODE { ONCE, LOOP };

public:

    // インスタンスを取得
    static SoundManager* GetInstance()
    {
        static SoundManager instance;
        return &instance;
    }
    // デストラクタ
	~SoundManager() = default;
    // 更新
    void Update();
    // サウンドを鳴らす
    void PlaySound(const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME, SE_MODE playType);
    // サウンドを停止する
    void StopSound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME);
    // 音量を取得する
    const float& GetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME);
    // 音量を調整する
    void SetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, float volume);
    // 全ての音の設定を初期化する
    void InitAllSounds(const float& volume = 0.5f);

private:

    // コンストラクタ
    SoundManager();
    // リソース保存関数
	void Create();

private:

    // オーディオエンジン
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
    // ウェーブバンク
    std::unique_ptr<DirectX::WaveBank> m_waveBank;
    // サウンドエフェクトインスタンス
    std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];
    // 各項目に対応した音量
    float m_volumes[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];

};

#endif // SOUNDMANAGER