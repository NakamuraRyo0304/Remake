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

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Water::Water()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(WaterConstant);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_waterConstantBuffer);

	// �R���X�^���g�o�b�t�@�̍쐬
	WaterConstant _cbuff = {};
	_cbuff.Scale = 10.0f;
	_context->UpdateSubresource(m_waterConstantBuffer.Get(), 0, NULL, &_cbuff, 0, 0);

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
}

//==============================================================================
// �����֐�
//==============================================================================
void Water::Create(const wchar_t* path)
{
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �V�F�[�_�[�̍쐬
	CreateShader();

	// �摜�̓ǂݍ���
	LoadTexture(path);

	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(device);
}

//==============================================================================
// �`��֐�
//==============================================================================
void Water::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// ���_���(�|���S���̂S���_�̍��W���j
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector4::One,
		SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// �R���X�^���g�o�b�t�@�̍쐬
	ConstantBuffer cbuff = {};
	cbuff.View = view.Transpose();
	cbuff.Proj = proj.Transpose();
	cbuff.World = m_world.Transpose();
	cbuff.Time = _timer;

	// �󂯓n���p�o�b�t�@�̓��e�X�V
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	// �摜�p�T���v���[�̓o�^(�V�F�[�_�[��SamLinear)
	// Linear �ڂ₩�� Point ��������
	// Wrap ���[�v������ Clamp 0-1�ӊO�͓K���ɓh����
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// �������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// �J�����O�͂Ȃ�
	context->RSSetState(m_states->CullNone());

	// �V�F�[�_��ݒ�
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	// �C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	// �V�F�[�_�̓o�^������
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
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
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	auto VSData = DX::ReadData(L"Resources/Shaders/Water/WaterVS.cso");
	auto GSData = DX::ReadData(L"Resources/Shaders/Water/WaterGS.cso");
	auto PSData = DX::ReadData(L"Resources/Shaders/Water/WaterPS.cso");

	//�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.data(), VSData.size(), m_inputLayout.GetAddressOf());

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.data(), VSData.size(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.data(), GSData.size(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.data(), PSData.size(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constantBuffer);
}