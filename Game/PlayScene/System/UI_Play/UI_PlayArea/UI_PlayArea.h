/*
 *  @File   UI_PlayArea.h
 *  @Brief  �v���C�V�[����UI�̃G���A�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_PLAYAREA
#define UI_PLAYAREA

class DrawSprite;
class UI_PlayArea
{
private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;
	DirectX::SimpleMath::Vector2 m_position;
	DirectX::SimpleMath::Vector4 m_color;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	UI_PlayArea();
	~UI_PlayArea();

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="screenRate">��ʔ䗦</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::SimpleMath::Vector2 screenRate);

public:

	// ���W���擾
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// �F���擾
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// �F��ݒ�
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

};

#endif // UI_PLAYAREA