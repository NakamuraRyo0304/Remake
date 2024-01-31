/*
 *	@File	Animation2DSprite.cpp
 *	@Brief	2D�X�v���C�g�̃A�j���[�V�����N���X�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Animation2DSprite.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Animation2DSprite::Animation2DSprite()
	: m_position{ SimpleMath::Vector3::Zero }	// ���[���h���W
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Animation2DSprite::~Animation2DSprite()
{
	m_states.reset();
	m_batch.reset();
	m_shaders.reset();
	m_srv.Reset();
}

//==============================================================================
// ���\�[�X�̍쐬
//==============================================================================
void Animation2DSprite::CreateResources(const wchar_t* path)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	m_batch = std::make_unique<PrimitiveVertex>(_context);
	m_states = std::make_unique<CommonStates>(_device);
	m_shaders = std::make_unique<Shaders>();

	// �摜�t�@�C����ǂݍ���
	CreateDDSTextureFromFile(_device, path, nullptr, m_srv.ReleaseAndGetAddressOf());

	// �R���X�^���g�o�b�t�@�̍쐬
	CreateConstBuffer();

	// �V�F�[�_�[�E�C���v�b�g���C�A�E�g�̍쐬
	CreateInputLayout(CreateShaders());
}

//==============================================================================
// �`��֐�
//==============================================================================
void Animation2DSprite::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// ���_��������������
	VertexPositionColorTexture _vertex =
		VertexPositionColorTexture(SimpleMath::Vector3::Zero, SimpleMath::Vector4::One, SimpleMath::Vector2::Zero);

	// ���W���X�V
	_vertex.position = m_position;

	// �V�F�[�_�[�ɃR���X�^���g�o�b�t�@��n��
	ConstBuffer _buffer;
	_buffer.View = view.Transpose();
	_buffer.Proj = proj.Transpose();
	_buffer.World = m_world.Transpose();
	_buffer.Move = SimpleMath::Vector4::One;

	// �󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	_context->UpdateSubresource(m_buffer.Get(), 0, NULL, &_buffer, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* _cbuffer[1] = { m_buffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _cbuffer);
	_context->GSSetConstantBuffers(0, 1, _cbuffer);
	_context->PSSetConstantBuffers(0, 1, _cbuffer);

	// �摜�p�T���v���[�̓o�^
	ID3D11SamplerState* _sampler[1] = { m_states->LinearWrap() };
	_context->PSSetSamplers(0, 1, _sampler);

	// �������`��w��
	ID3D11BlendState* _blendState = m_states->NonPremultiplied();

	// �������菈��(�F���Ȃ��Ƃ���͓���������)
	_context->OMSetBlendState(_blendState, nullptr, 0xFFFFFFFF);

	// �I�u�W�F�N�g�̑O��֌W��L����
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// �J�����O�͍�����
	_context->RSSetState(m_states->CullNone());

	// �V�F�[�_���Z�b�g����
	_context->VSSetShader(m_shaders->VS.Get(), nullptr, 0);
	_context->GSSetShader(m_shaders->GS.Get(), nullptr, 0);
	_context->PSSetShader(m_shaders->PS.Get(), nullptr, 0);

	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����
	_context->PSSetShaderResources(0, 1, m_srv.GetAddressOf());

	//�C���v�b�g���C�A�E�g�̓o�^
	_context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &_vertex, 1);
	m_batch->End();

	//�V�F�[�_�̉��
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}

//==============================================================================
// �r���{�[�h���֐�(Draw�֐����O�ɌĂяo��)
//==============================================================================
void Animation2DSprite::CreateBillboard(SimpleMath::Vector3 eye, SimpleMath::Vector3 target, SimpleMath::Vector3 up)
{
	m_world = SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero, eye - target, up);

	// ��]���~�߂ď�ɐ��ʂɌ�����
	SimpleMath::Matrix _rot = SimpleMath::Matrix::Identity;
	_rot._11 = -1;
	_rot._33 = -1;

	// �r���{�[�h�̃e�N�X�`������]
	m_world = _rot * m_world;
}

//==============================================================================
// �R���X�^���g�o�b�t�@�̍쐬
//==============================================================================
void Animation2DSprite::CreateConstBuffer()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// ��̃R���X�^���g�o�b�t�@���쐬
	D3D11_BUFFER_DESC _buffer = {};
	ZeroMemory(&_buffer, sizeof(_buffer));

	// �o�b�t�@�̐ݒ�
	_buffer.Usage = D3D11_USAGE_DEFAULT;					// �ǂݏ����̃��[�h���f�t�H���g�ɂ���
	_buffer.ByteWidth = sizeof(ConstBuffer);				// �萔�o�b�t�@�̃T�C�Y���i�[
	_buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// �萔�o�b�t�@�Ƃ��Ďg�p
	_buffer.CPUAccessFlags = NULL;							// CPU���珑�������𐧌�
	_device->CreateBuffer(&_buffer, nullptr, &m_buffer);	// �쐬�����o�b�t�@���i�[
}

//==============================================================================
// �V�F�[�_�[�̍쐬
//==============================================================================
std::vector<uint8_t> Animation2DSprite::CreateShaders()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �s�N�Z���V�F�[�_�[�쐬
	std::vector<uint8_t> _ps = DX::ReadData(L"Resources/Shaders/Normal/NormalPS.cso");
	DX::ThrowIfFailed(_device->CreatePixelShader(
		_ps.data(), _ps.size(), nullptr, m_shaders->PS.ReleaseAndGetAddressOf()));

	// ���_�V�F�[�_�[�쐬
	std::vector<uint8_t> _vs = DX::ReadData(L"Resources/Shaders/Normal/NormalVS.cso");
	DX::ThrowIfFailed(_device->CreateVertexShader(
		_vs.data(), _vs.size(), nullptr, m_shaders->VS.ReleaseAndGetAddressOf()));

	// �W�I���g���V�F�[�_�[�쐬
	std::vector<uint8_t> _gs = DX::ReadData(L"Resources/Shaders/Normal/NormalGS.cso");
	DX::ThrowIfFailed(_device->CreateGeometryShader(
		_gs.data(), _gs.size(), nullptr, m_shaders->GS.ReleaseAndGetAddressOf()));

	// ���ׂēǂݍ��񂾂璸�_�V�F�[�_�[��ԋp
	return _vs;
}

//==============================================================================
// �C���v�b�g���C�A�E�g�̍쐬
//==============================================================================
void Animation2DSprite::CreateInputLayout(std::vector<uint8_t> vs)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	DX::ThrowIfFailed(_device->CreateInputLayout(
		&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		vs.data(), vs.size(), m_inputLayout.GetAddressOf()));
}

