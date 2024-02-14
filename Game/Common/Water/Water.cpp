/*
 *  @File   Water.cpp
 *  @Brief  ���ʁB
 *  @Date   2024-02-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Water.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
// �C���v�b�g���C�A�E�g
const std::vector<D3D11_INPUT_ELEMENT_DESC> Water::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3)+ sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const float Water::WATER_SCALE = 40.0f;	// �摜�̃X�P�[��
const UINT Water::VERTEX_NUM = 16;		// ���_��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Water::Water()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(WaterConstant);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_waterConstantBuffer);

	// �R���X�^���g�o�b�t�@�̒l�n��
	WaterConstant _cbuffer = {};
	_cbuffer.Scale = WATER_SCALE;
	_context->UpdateSubresource(m_waterConstantBuffer.Get(), 0, NULL, &_cbuffer, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* _buffer[1] = { m_waterConstantBuffer.Get() };
	_context->VSSetConstantBuffers(1, 1, _buffer);
	_context->GSSetConstantBuffers(1, 1, _buffer);
	_context->PSSetConstantBuffers(1, 1, _buffer);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Water::~Water()
{
	m_primitive.reset();
	m_states.reset();
}

//==============================================================================
// �����֐�
//==============================================================================
void Water::Create(const wchar_t* path)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �V�F�[�_�[�̍쐬
	CreateShader();

	// �摜�̓ǂݍ���
	LoadTexture(path);

	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitive = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(_context);

	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(_device);
}

//==============================================================================
// �`��֐�
//==============================================================================
void Water::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// �|���S���̒��_���
	VertexPositionColorTexture _vertex[VERTEX_NUM] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector4::One,
		SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// �R���X�^���g�o�b�t�@�̒l�n��
	ConstantBuffer _cbuffer = {};
	_cbuffer.View = view.Transpose();
	_cbuffer.Proj = proj.Transpose();
	_cbuffer.World = m_world.Transpose();
	_cbuffer.Time = _timer;
	_context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &_cbuffer, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* _buffer[1] = { m_constantBuffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _buffer);
	_context->GSSetConstantBuffers(0, 1, _buffer);
	_context->PSSetConstantBuffers(0, 1, _buffer);

	// �T���v���[�X�e�[�g�̐ݒ�
	ID3D11SamplerState* _sampler[1] = { m_states->LinearWrap() };
	_context->PSSetSamplers(0, 1, _sampler);

	// ���ߏ����̐ݒ�
	ID3D11BlendState* _blendstate = m_states->NonPremultiplied();
	_context->OMSetBlendState(_blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// ���ʂ͉f��Ȃ����߃J�����O
	_context->RSSetState(m_states->CullClockwise());

	// �V�F�[�_��ݒ�
	_context->VSSetShader(m_vs.Get(), nullptr, 0);
	_context->GSSetShader(m_gs.Get(), nullptr, 0);
	_context->PSSetShader(m_ps.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^
	for (UINT i = 0; i < m_texture.size(); i++)
	{
		_context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	// �C���v�b�g���C�A�E�g�̓o�^
	_context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_primitive->Begin();
	m_primitive->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &_vertex[0], 4);
	m_primitive->End();

	// �V�F�[�_�̓o�^������
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}

//==============================================================================
// �e�N�X�`���ǂݍ��݊֐�
//==============================================================================
void Water::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(DX::DeviceResources::GetInstance()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture.push_back(texture);
}


//==============================================================================
// �V�F�[�_�[�쐬
//==============================================================================
void Water::CreateShader()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	auto _vs = DX::ReadData(L"Resources/Shaders/Water/WaterVS.cso");
	auto _gs = DX::ReadData(L"Resources/Shaders/Water/WaterGS.cso");
	auto _ps = DX::ReadData(L"Resources/Shaders/Water/WaterPS.cso");

	// �C���v�b�g���C�A�E�g�̍쐬
	_device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		_vs.data(), _vs.size(), m_inputLayout.GetAddressOf());

	// ���_�V�F�[�_�쐬
	DX::ThrowIfFailed(
		_device->CreateVertexShader(_vs.data(), _vs.size(), NULL, m_vs.ReleaseAndGetAddressOf()));

	// �W�I���g���V�F�[�_�쐬
	DX::ThrowIfFailed(
		_device->CreateGeometryShader(_gs.data(), _gs.size(), NULL, m_gs.ReleaseAndGetAddressOf()));

	// �s�N�Z���V�F�[�_�쐬
	DX::ThrowIfFailed(
		_device->CreatePixelShader(_ps.data(), _ps.size(), NULL, m_ps.ReleaseAndGetAddressOf()));

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(ConstantBuffer);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_constantBuffer);
}