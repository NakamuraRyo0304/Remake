/*
 *  @File   DrawPath.cpp
 *  @Brief  �p�X�`��N���X�B
 *  @Date   2024-04-10
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DrawPath.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
DrawPath::DrawPath(float width)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	void const* _byte;	size_t _size;

	// �x�[�V�b�N�G�t�F�N�g�̍쐬�Ɛݒ�
	m_basicEffect = std::make_unique<BasicEffect>(_device);
	m_basicEffect->SetVertexColorEnabled(true);
	m_basicEffect->GetVertexShaderBytecode(&_byte, &_size);

	// �v���~�e�B�u�̍쐬
	m_primitive = std::make_unique<PrimitiveBatch<VertexPositionColor>>(_context, static_cast<size_t>(width));

	// �C���v�b�g���C�A�E�g�̍쐬
	_device->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount,
		_byte, _size, m_inputLayout.GetAddressOf());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
DrawPath::~DrawPath()
{
	m_basicEffect.reset();
	m_primitive.reset();
	m_inputLayout.Reset();
}

//==============================================================================
// �`��֐�
//==============================================================================
void DrawPath::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj)
{
	// ���̓A�Z���u���̐ݒ�i�C���v�b�g���C�A�E�g�j
	context->IASetInputLayout(m_inputLayout.Get());

	// �o�̓}�l�[�W���̐ݒ�
	context->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states.DepthDefault(), 0);

	// �s���ݒ�
	m_basicEffect->SetWorld(SimpleMath::Matrix::Identity);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(context);

	// �`��J�n
	m_primitive->Begin();

	// �n�_�ƏI�_��ݒ肵�ĕ`�悷��
	VertexPositionColor _v1(SimpleMath::Vector3(0,0,0), Colors::Red);
	VertexPositionColor _v2(SimpleMath::Vector3(10, 10, 0), Colors::Red);
	m_primitive->DrawLine(_v1, _v2);

	// �`��I��
	m_primitive->End();
}
