/*
 *	@File	Transition.cpp
 *	@Brief	��ʐ؂�ւ��̃g�����W�V�����B
 *	@Date	2023-10-28
 *  @Author NakamuraRyo
 */

#include "pch.h"

#include "Transition.h"

 //==============================================================================
 // �C���v�b�g���C�A�E�g�̍쐬
 //==============================================================================
const std::vector<D3D11_INPUT_ELEMENT_DESC> Transition::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Transition::Transition()
	: m_vertice{}
	, m_color{}
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Transition::~Transition()
{
}

//==============================================================================
// �쐬�֐�
//==============================================================================
void Transition::Create(const wchar_t* path)
{
	// �f�o�C�X���\�[�X���擾
	auto _pDR = DX::DeviceResources::GetInstance();

	// �摜�̓ǂݍ���
	LoadTexture(path);

	// �V�F�[�_�[�̍쐬
	CreateShader();

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(_pDR->GetD3DDeviceContext());

	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(_pDR->GetD3DDevice());
}

//==============================================================================
// �e�N�X�`���̓ǂݍ���
//==============================================================================
void Transition::LoadTexture(const wchar_t* path)
{
	// �摜��ǂݍ���
	auto _pDR = DX::DeviceResources::GetInstance();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(_pDR->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture = texture;
}

//==============================================================================
// �V�F�[�_�[�̍쐬
//==============================================================================
void Transition::CreateShader()
{
	// �f�o�C�X���擾
	auto _pDR = DX::DeviceResources::GetInstance();
	auto _device = _pDR->GetD3DDevice();

	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	std::vector<uint8_t> _vs = DX::ReadData(L"Resources/Shaders/Transition/VS_Transition.cso");
	_device->CreateVertexShader(_vs.data(), _vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> _gs = DX::ReadData(L"Resources/Shaders/Transition/GS_Transition.cso");
	_device->CreateGeometryShader(_gs.data(), _gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> _ps = DX::ReadData(L"Resources/Shaders/Transition/PS_Transition.cso");
	_device->CreatePixelShader(_ps.data(), _ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// �C���v�b�g���C�A�E�g�̍쐬
	_device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		_vs.data(), _vs.size(), m_inputLayout.GetAddressOf());

	// �V�F�[�_�[�̍쐬
	_device->CreateVertexShader(_vs.data(), _vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	_device->CreateGeometryShader(_gs.data(), _gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	_device->CreatePixelShader(_ps.data(), _ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// �R���X�^���g�o�b�t�@�̍쐬
	CreateConstBuffer();
}

//==============================================================================
// �R���X�^���g�o�b�t�@�̍쐬
//==============================================================================
void Transition::CreateConstBuffer()
{
	DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();
	auto _device = _pDR->GetD3DDevice();

	// �R���X�^���g�o�b�t�@���쐬����
	D3D11_BUFFER_DESC _buffDesc = {};
	ZeroMemory(&_buffDesc, sizeof(_buffDesc));
	_buffDesc.Usage = D3D11_USAGE_DEFAULT;
	_buffDesc.ByteWidth = sizeof(ConstBuffer);
	_buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_buffDesc.CPUAccessFlags = NULL;
	_device->CreateBuffer(&_buffDesc, nullptr, &m_constBuffer);
}

//==============================================================================
// �`�揈��
//==============================================================================
void Transition::Render(const float& timer)
{
	DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();

	// ���_���
	VertexPositionColorTexture _vertex[4] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3::Zero,	// ���_�̈ʒu
		SimpleMath::Vector4::One,	// �F���
		SimpleMath::Vector2::Zero	// �e�N�X�`���̈ʒu
		)
	};

	//�V�F�[�_�[�ɓn���o�b�t�@���쐬����
	ConstBuffer _throwBuff;
	_throwBuff.Diffuse = m_color;
	_throwBuff.Time = SimpleMath::Vector4(timer, 0, 0, 0);

	// ConstBuffer����ID3D11Buffer�ւ̕ϊ�
	_context->UpdateSubresource(m_constBuffer.Get(), 0, NULL, &_throwBuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* _buffer[1] = { m_constBuffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _buffer);
	_context->GSSetConstantBuffers(0, 1, _buffer);
	_context->PSSetConstantBuffers(0, 1, _buffer);

	// �摜�p�T���v���[�̓o�^
	ID3D11SamplerState* _sampler[1] = { m_states->LinearWrap() };
	_context->PSSetSamplers(0, 1, _sampler);

	// �������菈��
	_context->OMSetBlendState(m_states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// �J�����O�͍�����
	_context->RSSetState(m_states->CullNone());

	// �V�F�[�_���Z�b�g����
	_context->VSSetShader(m_verShader.Get(), nullptr, 0);
	_context->GSSetShader(m_geoShader.Get(), nullptr, 0);
	_context->PSSetShader(m_pixShader.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	_context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	// �C���v�b�g���C�A�E�g�̓o�^
	_context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, _vertex, 4);
	m_batch->End();

	// �V�F�[�_�̓o�^������
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}