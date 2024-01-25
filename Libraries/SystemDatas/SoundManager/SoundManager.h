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

private:

    // �I�[�f�B�I�G���W���ւ̃|�C���^
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

    // �E�F�[�u�o���N�ւ̃|�C���^
    std::unique_ptr<DirectX::WaveBank> m_waveBank;

    // �T�E���h�G�t�F�N�g�C���X�^���X
    std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstances[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];

    // �e���ڂɑΉ���������
    float m_volumes[XACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT];

private:

    // �V���O���g��
    SoundManager();

public:

    /// <summary>
    /// �T�E���h�}�l�[�W�����Q��
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�T�E���h�}�l�[�W���V���O���g��</returns>
    static SoundManager* GetInstance()
    {
        static SoundManager sm;

        return &sm;
    }
	~SoundManager() = default;

    /// <summary>
    /// �I�[�f�B�I�G���W���̍X�V
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    void Update();
    /// <summary>
    /// �T�E���h��炷
    /// </summary>
    /// <param name="WAVEBANKXACT_WAVEBANK_AUDIOPACK_TYPE_NAME">�Ȃ炵��������ID</param>
    /// <param name="playType">���[�v���P����(true�Ń��[�v�Afalse�ŒP��)</param>
    /// <returns>�Ȃ�</returns>
    void PlaySound(const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME, SE_MODE playType);
    /// <summary>
    /// �w�肵�����̉��ʒ���
    /// </summary>
    /// <param name="volume">����</param>
    /// <param name="WAVEBANKXACT_WAVEBANK_AUDIOPACK_ENTRY_COUNT_TYPE_NAME">����ID</param>
    /// <returns>�Ȃ�</returns>
    void SetVolume(const float& volume, const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME);
    /// <summary>
    /// �w�肵�����̉��ʂ��擾
    /// </summary>
    /// <param name="WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME">�擾����������ID</param>
    /// <returns>�w�肵�����̉���</returns>
    const float& GetVolume(const XACT_WAVEBANK_AUDIOPACK& WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME) { return m_volumes[WAVEBANKXACT_WAVEBANK_SKBX_TYPE_NAME]; }
    /// <summary>
    /// �����t�F�[�h������
    /// </summary>
    /// <param name="speed">���x</param>
    /// <returns>�Ȃ�</returns>
    void FadeVolume(const float& speed);

private:
    /// <summary>
    /// ���\�[�X�ۑ��֐�
    /// </summary>
    /// <param name="��������">/param>
    /// <returns>�Ȃ�</returns>
	void Create();
};

#endif // SOUNDMANAGER