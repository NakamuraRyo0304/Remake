/*
 *	@File	DrawSprite.h
 *	@Brief	�摜��`�悷��N���X�B
 *	@Date	2023-06-09
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWSPRITE
#define DRAWSPRITE

// �f�t�H���g�����ݒ�p�̌p��
struct RECT_U : public RECT
{
	RECT_U(LONG left = 0, LONG top = 0, LONG right = 1920, LONG bottom = 1080)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
};

class DrawSprite
{
public:

	// ��]�ʂ�ݒ�
	void CreateRotation(std::wstring key, const float& rotate);
	// ��]�ʂ��擾����
	const float GetRotate(std::wstring key) { auto it = m_rotate.find(key); return it->second; }

	// �R���X�g���N�^
	DrawSprite();
	// �f�X�g���N�^
	~DrawSprite();

	// �X�v���C�g�o�b�`���쐬
	void MakeSpriteBatch();
	// �X�v���C�g�����ׂăN���A����
	void Clear();

	// �摜��o�^����֐�
	void AddTextureData(std::wstring key, std::wstring path);
	// �`�揈��
	void DrawTexture(std::wstring key, DirectX::SimpleMath::Vector2 pos,
		DirectX::SimpleMath::Vector4 color, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 origin, RECT_U rect = RECT_U());

private:

	// �摜�̊i�[�z��
	std::map<std::wstring, std::wstring> m_textures;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// �摜��`�悷��ϐ�
	std::map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_SRV;
	// ��]��
	std::map <std::wstring, float> m_rotate;

};

#endif // DRAWSPRITE