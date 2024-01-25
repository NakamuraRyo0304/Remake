/*
 *	@File	DisplayEffect.cpp
 *	@Brief	��ʌ��ʁB
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DisplayEffect.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const UINT DisplayEffect::VERTEX_COUNT = 1;	// ���_��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
DisplayEffect::DisplayEffect(RECT rect)
	: m_size{ rect }					// ��ʃT�C�Y
	, m_mode{ DisplayMode::Default }	// ��ʌ���
	, m_shaders{ nullptr }				// �V�F�[�_�[
	, m_worldPosition{}					// ���[���h�s��
	, m_scale{}							// �X�P�[���s��
	, m_rotate{}						// ��]�s��
{
	auto _pDR = DX::DeviceResources::GetInstance();
	m_renderTexture = std::make_unique<DX::RenderTexture>(_pDR->GetBackBufferFormat());
	m_renderTexture->SetDevice(_pDR->GetD3DDevice());
	m_renderTexture->SetWindow(rect);

	// ������Ԃ�ۑ�
	m_viewPointer = std::make_unique<ViewPointer>();
	m_viewPointer->pRenderTarget = _pDR->GetRenderTargetView();
	m_viewPointer->pDepthStencil = _pDR->GetDepthStencilView();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
DisplayEffect::~DisplayEffect()
{
	m_viewPointer.reset();
	m_shaders.reset();
	m_renderTexture->ReleaseDevice();
}

//==============================================================================
// ��ʌ��ʂ�ݒ肷��
//==============================================================================
void DisplayEffect::Initialize(const DisplayMode& mode)
{
	m_mode = mode;
	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();
	auto _device = _pDR->GetD3DDevice();

	// �V�F�[�_�[���쐬
	CreateShaders();
	SetDisplayMode(mode);

	// �v���~�e�B�u�o�b�`���쐬
	m_batch = std::make_unique<PrimitiveVertex>(_context);

	// �R�����X�e�[�g���쐬
	m_states = std::make_unique<CommonStates>(_device);
}

//==============================================================================
// ��ʌ��ʊJ�n
//==============================================================================
void DisplayEffect::Begin()
{
	// ���蓖�Ă��Ȃ���΃X�L�b�v
	if (m_mode == DisplayMode::Default) return;

	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();
	auto _rtv = m_renderTexture->GetRenderTargetView();

	// ������Ԃ�ۑ�
	m_viewPointer->pRenderTarget = _pDR->GetRenderTargetView();
	m_viewPointer->pDepthStencil = _pDR->GetDepthStencilView();

	// �V�F�[�_�[���\�[�X���擾
	m_shaderResouce = m_renderTexture->GetShaderResourceView();

	// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V����������
	_context->ClearRenderTargetView(_rtv, Colors::White);
	_context->ClearDepthStencilView(m_viewPointer->pDepthStencil, USER_DEPTH_MODE, 1.0f, 0);
	_context->OMSetRenderTargets(1, &_rtv, m_viewPointer->pDepthStencil);
}

//==============================================================================
// ��ʌ��ʏI��
//==============================================================================
void DisplayEffect::End()
{
	// ���蓖�Ă��Ȃ���΃X�L�b�v
	if (m_mode == DisplayMode::Default) return;

	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();

	// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V�������ɖ߂�
	_context->ClearRenderTargetView(m_viewPointer->pRenderTarget, Colors::CornflowerBlue);
	_context->ClearDepthStencilView(m_viewPointer->pDepthStencil, USER_DEPTH_MODE, 1.0f, 0);
	_context->OMSetRenderTargets(1, &m_viewPointer->pRenderTarget, m_viewPointer->pDepthStencil);
}

//==============================================================================
// �V�F�[�_�[���쐬����
//==============================================================================
void DisplayEffect::CreateShaders()
{
	// �V�F�[�_�[���쐬
	m_shaders = std::make_unique<ShaderPack>();

	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	auto _VS = ReadShader(L"Resources/Shaders/DisplayEffects/VGS/DisplayVS.cso");
	auto _GS = ReadShader(L"Resources/Shaders/DisplayEffects/VGS/DisplayGS.cso");
	auto _PS = ReadShader(L"Resources/Shaders/DisplayEffects/Brown/BrownPS.cso");

	// �C���v�b�g���C�A�E�g�̍쐬
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	_device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		_VS.data(), _VS.size(), m_inputLayout.GetAddressOf());

	// ���_�V�F�[�_�[�̍쐬
	_device->CreateVertexShader		(_VS.data(), _VS.size(), NULL, m_shaders->VS.ReleaseAndGetAddressOf());
	// �W�I���g���V�F�[�_�[�̍쐬
	_device->CreateGeometryShader	(_GS.data(), _GS.size(), NULL, m_shaders->GS.ReleaseAndGetAddressOf());
	// �s�N�Z���V�F�[�_�[�̍쐬
	_device->CreatePixelShader		(_PS.data(), _PS.size(), NULL, m_shaders->PS.ReleaseAndGetAddressOf());

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(ConstBuffer);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_buffer);
}

//==============================================================================
// �V�F�[�_�[�ǂݍ���
//==============================================================================
std::vector<uint8_t> DisplayEffect::ReadShader(const wchar_t* path)
{
	return DX::ReadData(path);
}

//==============================================================================
// Start-End�ɋ��܂ꂽ�I�u�W�F�N�g�Ɍ��ʂ�K�p����
//==============================================================================
void DisplayEffect::Apply(SimpleMath::Matrix& view, SimpleMath::Matrix& proj, const bool& flag)
{
	// ���蓖�Ă��Ȃ���Βʏ�̕`�������
	if (m_mode == DisplayMode::Default) return;

	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();

	// ���_���(VERTEX_COUNT)��ʏ�F�ŏ�����
	VertexPositionColorTexture _vertex[VERTEX_COUNT] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3::Zero, Colors::White, SimpleMath::Vector2::Zero),
	};

	// �V�F�[�_�[�ɓn���o�b�t�@���쐬
	ConstBuffer _constBuff;
	if (flag)	// �e���r���[�h�Ȃ烏�[���h���W�ɕϊ�����
	{
		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			// ���[���h���W���Z�b�g����
			_vertex[i] = VertexPositionColorTexture(m_worldPosition, Colors::White, SimpleMath::Vector2::Zero);
		}

		// �X�P�[���s��̌v�Z
		SimpleMath::Matrix _world = SimpleMath::Matrix::CreateScale(m_scale);

		// ��]�s��̌v�Z
		_world *= SimpleMath::Matrix::CreateRotationX(m_rotate.x);
		_world *= SimpleMath::Matrix::CreateRotationY(m_rotate.y);
		_world *= SimpleMath::Matrix::CreateRotationZ(m_rotate.z);

		// �ϊ����ăo�b�t�@�ɃZ�b�g����
		_constBuff.World = _world.Transpose();
		_constBuff.View = view.Transpose();
		_constBuff.Proj = proj.Transpose();
	}
	_constBuff.Time.x = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// �R���X�^���g�o�b�t�@�̕ϊ�
	_context->UpdateSubresource(m_buffer.Get(), 0, nullptr, &_constBuff, 0, 0);

	// �V�F�[�_�[�ɃR���X�^���g�o�b�t�@��n��
	ID3D11Buffer* _throwBuff[1] = { m_buffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _throwBuff);
	_context->GSSetConstantBuffers(0, 1, _throwBuff);
	_context->PSSetConstantBuffers(0, 1, _throwBuff);

	// �摜�p�T���v���[�̓o�^
	ID3D11SamplerState* _sampler[1] = { m_states->PointClamp() };
	_context->PSSetSamplers(0, 1, _sampler);

	// �������菈��
	_context->OMSetBlendState(m_states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ��
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// �J�����O��������ɐݒ�
	_context->RSSetState(m_states->CullNone());

	// �V�F�[�_�[��ݒ�
	_context->VSSetShader(m_shaders->VS.Get(), nullptr, 0);
	_context->GSSetShader(m_shaders->GS.Get(), nullptr, 0);
	_context->PSSetShader(m_shaders->PS.Get(), nullptr, 0);

	// ���\�[�X��ݒ�
	_context->PSSetShaderResources(0, 1, m_shaderResouce.GetAddressOf());

	// �C���v�b�g���C�A�E�g��o�^
	_context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, _vertex, VERTEX_COUNT);
	m_batch->End();

	// �V�F�[�_�[�̔j��
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}

//==============================================================================
// ��ʌ��ʂ�ݒ�
//==============================================================================
void DisplayEffect::SetDisplayMode(const DisplayMode& mode)
{
	m_mode = mode;

	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	std::vector<uint8_t> _shader;

	switch (mode)
	{
	case DisplayMode::Default:
		return;
	case DisplayMode::BrownTVEffect:
		_shader = ReadShader(L"Resources/Shaders/DisplayEffects/Brown/BrownPS.cso");
		break;
	case DisplayMode::MonochromeEffect:
		_shader = ReadShader(L"Resources/Shaders/DisplayEffects/Monochrome/MonochroPS.cso");
		break;
	default:
		break;
	}

	// �V�F�[�_�[���쐬
	_device->CreatePixelShader(_shader.data(), _shader.size(), NULL, m_shaders->PS.ReleaseAndGetAddressOf());
}
