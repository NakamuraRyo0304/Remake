/*
 *	@File	GameMain.h
 *	@Brief	�Q�[�����[�v�������N���X
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GAMEMAIN
#define GAMEMAIN

// �e�V�[���̃C���N���[�h
#include "Game/BaseScene/BaseScene.h"

 // �O���錾
class Fade;

#ifdef _DEBUG
class Timer;
#endif

class GameMain
{
public:

    // �R���X�g���N�^
    GameMain();
    // �f�X�g���N�^
    ~GameMain();
    // ������
    void Initialize();
    // �X�V
    void Update();
    // �`��
    void Draw();
    // �I��
    void Finalize();
    // ��ʈˑ��A�f�o�C�X�ˑ��̏�����
    void CreateWDResources(const int& screenWidth, const int& screenHeight);
    // �V�[���̍쐬
    void CreateScene();
    // �V�[���̍폜
    void DeleteScene();
    // �\�t�g���I��
    inline void ExitApp() { PostQuitMessage(0); }
    // �V�[���L���X�^    // CastSceneType<�ϊ��������V�[���^>(�V�[��)
    template<typename T>
    T* CastSceneType(std::unique_ptr<BaseScene>& scene)
    {
        return dynamic_cast<T*>(scene.get());
    }

private:

    // �f�t�H���g�̃t�F�[�h���x
    const float DEFAULT_FADE_SPEED = 4.0f;
    // �v���C�V�[���̃t�F�[�h���x
    static const float PLAY_FADE_SPEED;
    // �g�����W�V�����̃p�X
    static const wchar_t* FADE_TEXTURE_PATH;
    // �g�����W�V�����̐F
    static const DirectX::XMVECTORF32 FADE_COLOR;

private:

    // �t�F�[�h�I�u�W�F�N�g
    std::unique_ptr<Fade> m_fade;
    // ���ݏ�������V�[��
    std::unique_ptr<BaseScene> m_nowScene;
    // �����̃V�[���A�ߋ��̃V�[��
    SCENE m_nextScene, m_prevScene;
    // �X�N���[���T�C�Y
    DirectX::SimpleMath::Vector2 m_screenSize;
    // �X�e�[�W�ԍ�/�ő�X�e�[�W�ԍ�/�R�C����
    int m_stageNumber, m_maxNumber, m_collectedCoin;
    // �N���A����
    float m_clearTime;

#ifdef _DEBUG
    // �^�C�}�[
    std::unique_ptr<Timer> m_timer;
#endif

};

#endif // GAMEMAIN