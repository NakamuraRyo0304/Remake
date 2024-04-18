/*
 *	@File	Transition.cpp
 *	@Brief	��ʐ؂�ւ��̃g�����W�V�����B
 *	@Date	2023-10-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Transition.h"

 // �C���v�b�g���C�A�E�g�̍쐬
const std::vector<D3D11_INPUT_ELEMENT_DESC> Transition::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// �R���X�g���N�^
Transition::Transition()
	:
	m_vertice(),
	m_color()
{
}

// �f�X�g���N�^
Transition::~Transition()
{
}

// �쐬
void Transition::Create(const wchar_t* path)
{
	// �f�o�C�X���\�[�X���擾
	auto pDR = DX::DeviceResources::GetInstance();

	// �摜�̓ǂݍ���
	LoadTexture(path);

	// �V�F�[�_�[�̍쐬
	CreateShader();

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());

	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(pDR->GetD3DDevice());
}

// �e�N�X�`���̓ǂݍ���
void Transition::LoadTexture(const wchar_t* path)
{
	// �摜��ǂݍ���
	auto pDR = DX::DeviceResources::GetInstance();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(pDR->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture = texture;
}

// �V�F�[�_�[�̍쐬
void Transition::CreateShader()
{
	// �f�o�C�X���擾
	auto pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shaders/Transition/VS_Transition.cso");
	device->CreateVertexShader(vs.data(), vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> gs = DX::ReadData(L"Resources/Shaders/Transition/GS_Transition.cso");
	device->CreateGeometryShader(gs.data(), gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shaders/Transition/PS_Transition.cso");
	device->CreatePixelShader(ps.data(), ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// �C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		vs.data(), vs.size(), m_inputLayout.GetAddressOf());

	// �V�F�[�_�[�̍쐬
	device->CreateVertexShader(vs.data(), vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	device->CreateGeometryShader(gs.data(), gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	device->CreatePixelShader(ps.data(), ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// �R���X�^���g�o�b�t�@�̍쐬
	CreateConstBuffer();
}

// �R���X�^���g�o�b�t�@�̍쐬
void Transition::CreateConstBuffer()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// �R���X�^���g�o�b�t�@���쐬����
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = NULL;
	device->CreateBuffer(&desc, nullptr, &m_constBuffer);
}

// �`��
void Transition::Draw(const float& timer)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// ���_���
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3::Zero,	// ���_�̈ʒu
		SimpleMath::Vector4::One,	// �F���
		SimpleMath::Vector2::Zero	// �e�N�X�`���̈ʒu
		)
	};

	// �V�F�[�_�[�ɓn���o�b�t�@���쐬
	ConstBuffer cbuff;
	cbuff.Diffuse = m_color;
	cbuff.Time = SimpleMath::Vector4(timer, 0, 0, 0);

	context->UpdateSubresource(m_constBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* buff[1] = { m_constBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, buff);
	context->GSSetConstantBuffers(0, 1, buff);
	context->PSSetConstantBuffers(0, 1, buff);

	// �摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// �������菈��
	context->OMSetBlendState(m_states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ��
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// �J�����O�͍�����
	context->RSSetState(m_states->CullNone());

	// �V�F�[�_���Z�b�g����
	context->VSSetShader(m_verShader.Get(), nullptr, 0);
	context->GSSetShader(m_geoShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixShader.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	// �C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, vertex, 4);
	m_batch->End();

	// �V�F�[�_�̓o�^������
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}