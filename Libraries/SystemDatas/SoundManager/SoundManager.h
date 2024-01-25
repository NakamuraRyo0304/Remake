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

private:

    // オーディオエンジンへのポインタ
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

    // ウェーブバンクへのポインタ
    std::unique_ptr<DirectX::WaveBank> m_waveBank;

    // サウンドエフェクトインスタンス
    std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];

    // 各項目に対応した音量
    float m_volumes[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];

private:

    // シングルトン
    SoundManager();

public:

    /// <summary>
    /// サウンドマネージャを参照
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>サウンドマネージャシングルトン</returns>
    static SoundManager* GetInstance()
    {
        static SoundManager sm;

        return &sm;
    }
	~SoundManager() = default;

    /// <summary>
    /// オーディオエンジンの更新
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    void Update();
    /// <summary>
    /// サウンドを鳴らす
    /// </summary>
    /// <param name="WAVEBANKXACT_WAVEBANK_AUDIOPACK_TYPE_NAME">ならしたい音のID</param>
    /// <param name="playType">ループか単発か(trueでループ、falseで単発)</param>
    /// <returns>なし</returns>
    void PlaySound(const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME, SE_MODE playType);
    /// <summary>
    /// 指定した音の音量調整
    /// </summary>
    /// <param name="volume">音量</param>
    /// <param name="WAVEBANKXACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT_TYPE_NAME">音のID</param>
    /// <returns>なし</returns>
    void SetVolume(const float& volume, const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME);
    /// <summary>
    /// 指定した音の音量を取得
    /// </summary>
    /// <param name="WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME">取得したい音のID</param>
    /// <returns>指定した音の音量</returns>
    const float& GetVolume(const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME) { return m_volumes[WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME]; }
    /// <summary>
    /// 音をフェードさせる
    /// </summary>
    /// <param name="speed">速度</param>
    /// <returns>なし</returns>
    void FadeVolume(const float& speed);

private:
    /// <summary>
    /// リソース保存関数
    /// </summary>
    /// <param name="引数無し">/param>
    /// <returns>なし</returns>
	void Create();
};

#endif // SOUNDMANAGER