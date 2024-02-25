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

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
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
    /// <param name="WAVEBANKXACT_WAVEBANK_AUDIOPACK_TYPE_NAME">鳴らしたい音のID</param>
    /// <param name="playType">ループか単発か(trueでループ、falseで単発)</param>
    /// <returns>なし</returns>
    void PlaySound(const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME, SE_MODE playType);

    /// <summary>
    /// サウンドを停止する
    /// </summary>
    /// <param name="XACT_WAVEBANK_AUDIOPACK_TYPE_NAME">止めたい音のID</param>
    /// <returns>なし</returns>
    void StopSound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME);

    /// <summary>
    /// 音量を取得する
    /// </summary>
    /// <param name="XACT_WAVEBANK_AUDIOPACK_TYPE_NAME">取得したい音量のID</param>
    /// <returns>音量</returns>
    const float& GetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME);

    /// <summary>
    /// 音量を調整する
    /// </summary>
    /// <param name="XACT_WAVEBANK_AUDIOPACK_TYPE_NAME">調整したい音のID</param>
    /// <param name="volume">音量</param>
    /// <returns>なし</returns>
    void SetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, float volume);

    /// <summary>
    /// 全ての音の設定を初期化する
    /// </summary>
    /// <param name="volume">音量（デフォルトは0.5f）</param>
    /// <returns>なし</returns>
    void InitAllSounds(const float& volume = 0.5f);

private:
    /// <summary>
    /// リソース保存関数
    /// </summary>
    /// <param name="引数無し">/param>
    /// <returns>なし</returns>
	void Create();
};

#endif // SOUNDMANAGER