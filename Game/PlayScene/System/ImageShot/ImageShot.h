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
public:

    // �R���X�g���N�^
    ImageShot();
    // �f�X�g���N�^
    ~ImageShot();
    // �X�N���[���V���b�g���B�e���Ďw�肳�ꂽ�t�@�C���p�X�ɕۑ�����(�p�X�A�R�s�[��(�����ł���))
    HRESULT TakePic(const wchar_t* filePath, const wchar_t* copy = nullptr);
    // �X�N�V����`�悷��
    void Draw(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate);

private:

    // �o�b�N�o�b�t�@���擾����
    HRESULT GetBackBuffer();
    // �o�b�N�o�b�t�@�̉��
    void ReleaseBackBuffer();

private:

    // �o�b�N�o�b�t�@
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer;
    // �X�v���C�g�`��
    std::unique_ptr<DrawSprite> m_sprite;

};

#endif // SCREENSHOT_H
