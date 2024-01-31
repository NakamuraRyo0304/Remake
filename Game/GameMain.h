/*
 *	@File	GameMain.h
 *	@Brief	�Q�[�����[�v�������N���X
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GAMEMAIN
#define GAMEMAIN

 // �O���錾
class IScene;
class Fade;

// TODO: �V�[���P�F�V�[��ID�̒ǉ�
enum class SCENE : int
{
    NONE,       // ID����

    TITLE,      // �^�C�g���V�[��
    SELECT,     // �Z���N�g�V�[��
    PLAY,       // �Q�[���V�[��
    EDIT,       // ����V�[��
    EXIT,       // �I��
};

class GameMain
{
private:

    // �X�N���[���T�C�Y
    DirectX::SimpleMath::Vector2 m_screenSize;

    // �����̃V�[���A�ߋ��̃V�[��
    SCENE m_nextScene, m_prevScene;

    // ���ݏ�������V�[��
    std::unique_ptr<IScene> m_nowScene;

    // �t�F�[�h�I�u�W�F�N�g
    std::unique_ptr<Fade> m_fade;

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

    // �X�e�[�W�ԍ�
    int m_stageNumber;

public:
    GameMain();
    ~GameMain();

    /// <summary>
    /// ����������
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    void Initialize();
    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    void Update();
    /// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    void Draw();
    /// <summary>
    /// �I������
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    void Finalize();
    /// <summary>
    /// �V�[���̐V�K�쐬
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    void CreateScene();
    /// <summary>
    /// �V�[���̍폜
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    void DeleteScene();
    /// <summary>
    /// ��ʈˑ��A�f�o�C�X�ˑ��̏�����
    /// </summary>
    /// <param name="screenWidth">��ʉ���</param>
    /// <param name="screenHeight">��ʏc��</param>
    /// <returns>�Ȃ�</returns>
    void CreateWDResources(const int& screenWidth, const int& screenHeight);

    // �V�[���L���X�^    // �����FT = �ϊ��������^�� / scene ���̃V�[��
    template<typename T>
    T* CastSceneType(std::unique_ptr<IScene>& scene)
    {
        return dynamic_cast<T*>(scene.get());
    }

    // �\�t�g���I������
    inline void ExitApp() { PostQuitMessage(0); }
};

#endif // GAMEMAIN