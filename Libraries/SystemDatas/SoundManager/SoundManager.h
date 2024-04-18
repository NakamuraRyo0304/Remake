/*
 *	@File	SoundManager.h
 *	@Brief	SE�̍Đ��Ɏg���}�l�[�W���N���X�B
 *	@Date	2023-09-08
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SOUNDMANAGER
#define SOUNDMANAGER

 // �T�E���h���X�g
#include "SoundList.h"

class SoundManager
{
public:

    // �Đ����[�h
    enum SE_MODE { ONCE, LOOP };

public:

    // �C���X�^���X���擾
    static SoundManager* GetInstance()
    {
        static SoundManager instance;
        return &instance;
    }
    // �f�X�g���N�^
	~SoundManager() = default;
    // �X�V
    void Update();
    // �T�E���h��炷
    void PlaySound(const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME, SE_MODE playType);
    // �T�E���h���~����
    void StopSound(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME);
    // ���ʂ��擾����
    const float& GetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME);
    // ���ʂ𒲐�����
    void SetVolume(const XACT_WAVEBANK_AUDIOPACK& XACT_WAVEBANK_AUDIOPACK_TYPE_NAME, float volume);
    // �S�Ẳ��̐ݒ������������
    void InitAllSounds(const float& volume = 0.5f);

private:

    // �R���X�g���N�^
    SoundManager();
    // ���\�[�X�ۑ��֐�
	void Create();

private:

    // �I�[�f�B�I�G���W��
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
    // �E�F�[�u�o���N
    std::unique_ptr<DirectX::WaveBank> m_waveBank;
    // �T�E���h�G�t�F�N�g�C���X�^���X
    std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];
    // �e���ڂɑΉ���������
    float m_volumes[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];

};

#endif // SOUNDMANAGER