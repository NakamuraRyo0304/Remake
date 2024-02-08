/*
 *	@File	ImageShot.h
 *	@Brief	�X�N���[���V���b�g���쐬�擾����N���X
 *	@Date	2024-02-08
 *  @Author	NakamuraRyo
 */

#pragma once
#ifndef IMAGESHOT
#define IMAGESHOT

class DrawSprite;
class ImageShot
{
private:

    // �o�b�N�o�b�t�@
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer;

    // �X�v���C�g�`��
    std::unique_ptr<DrawSprite> m_sprite;

public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="��������"></param>
    /// <returns>�Ȃ�</returns>
    ImageShot();
    ~ImageShot();

    /// <summary>
    /// �X�N���[���V���b�g���B�e���Ďw�肳�ꂽ�t�@�C���p�X�ɕۑ�����
    /// </summary>
    /// <param name="filePath">�ۑ���̃p�X</param>
    /// <returns>�Ȃ�</returns>
    HRESULT TakePic(const wchar_t* filePath);

    /// <summary>
    /// �X�N�V����`�悷��
    /// </summary>
    /// <param name="pos">���W</param>
    /// <param name="rate">�g�嗦</param>
    /// <returns>�Ȃ�</returns>
    void Draw(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate);

private:

    // �o�b�N�o�b�t�@���擾����
    HRESULT GetBackBuffer();

    // �o�b�N�o�b�t�@�̉��
    void ReleaseBackBuffer();
};

#endif // SCREENSHOT_H
