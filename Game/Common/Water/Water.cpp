/*
 *  @File   Water.cpp
 *  @Brief  ���ʁB
 *  @Date   2024-02-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Water.h"

// �C���v�b�g���C�A�E�g
const std::vector<D3D11_INPUT_ELEMENT_DESC> Water::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3)+ sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const float Water::SCALE = 40.0f;	// �摜�̃X�P�[��
const UINT Water::VERTEX_NUM = 16;	// ���_��

// �R���X�g���N�^
Water::Water()
{
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(WaterConstant);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_waterConstantBuffer);

	// �R���X�^���g�o�b�t�@�̒l�n��
	WaterConstant cbuff = {};
	cbuff.Scale = SCALE;
	context->UpdateSubresource(m_waterConstantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* buff[1] = { m_waterConstantBuffer.Get() };
	context->VSSetConstantBuffers(1, 1, buff);
	context->GSSetConstantBuffers(1, 1, buff);
	context->PSSetConstantBuffers(1, 1, buff);
}

// �f�X�g���N�^
Water::~Water()
{
	m_primitive.reset();
	m_states.reset();
}

// ����
void Water::Create(const wchar_t* path)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �V�F�[�_�[�̍쐬
	CreateShader();
	// �摜�̓ǂݍ���
	LoadTexture(path);
	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitive = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(device);
}

// �`��
void Water::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// �|���S���̒��_���
	VertexPositionColorTexture vertex[VERTEX_NUM] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3::Zero, SimpleMath::Vector4::One, SimpleMath::Vector2::Zero),
	};

	// �R���X�^���g�o�b�t�@�̒l�n��
	ConstantBuffer cbuff = {};
	cbuff.View = view.Transpose();
	cbuff.Proj = proj.Transpose();
	cbuff.World = m_world.Transpose();
	cbuff.Time = timer;
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* buff[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, buff);
	context->GSSetConstantBuffers(0, 1, buff);
	context->PSSetConstantBuffers(0, 1, buff);

	// �T���v���[�X�e�[�g�̐ݒ�
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// ���ߏ����̐ݒ�
	ID3D11BlendState* blendState = m_states->NonPremultiplied();
	context->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// ���ʂ͉f��Ȃ����߃J�����O
	context->RSSetState(m_states->CullClockwise());

	// �V�F�[�_��ݒ�
	context->VSSetShader(m_vs.Get(), nullptr, 0);
	context->GSSetShader(m_gs.Get(), nullptr, 0);
	context->PSSetShader(m_ps.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^
	for (UINT i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	// �C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_primitive->Begin();
	m_primitive->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_primitive->End();

	// �V�F�[�_�̓o�^������
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

// �e�N�X�`���ǂݍ��݊֐�
void Water::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(DX::DeviceResources::GetInstance()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture.push_back(texture);
}

// �V�F�[�_�[�쐬
void Water::CreateShader()
{
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	auto vs = DX::ReadData(L"Resources/Shaders/Water/WaterVS.cso");
	auto gs = DX::ReadData(L"Resources/Shaders/Water/WaterGS.cso");
	auto ps = DX::ReadData(L"Resources/Shaders/Water/WaterPS.cso");

	// �C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		vs.data(), vs.size(), m_inputLayout.GetAddressOf());

	// ���_�V�F�[�_�쐬
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs.data(), vs.size(), NULL, m_vs.ReleaseAndGetAddressOf()));

	// �W�I���g���V�F�[�_�쐬
	DX::ThrowIfFailed(
		device->CreateGeometryShader(gs.data(), gs.size(), NULL, m_gs.ReleaseAndGetAddressOf()));

	// �s�N�Z���V�F�[�_�쐬
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(), NULL, m_ps.ReleaseAndGetAddressOf()));

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstantBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_constantBuffer);
}