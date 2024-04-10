/*
 *  @File   DrawPath.h
 *  @Brief  �p�X�`��N���X�B
 *  @Date   2024-04-10
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWPATH
#define DRAWPATH

class DrawPath
{
private:

	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitive;

	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="width">����</param>
	/// <returns>�Ȃ�</returns>
	DrawPath(float width);
	~DrawPath();

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="context">�R���e�L�X�g</param>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
};

#endif // DRAWPATH