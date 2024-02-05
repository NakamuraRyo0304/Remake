/*
 *	@File	PlayScene.cpp
 *	@Brief	�v���C�V�[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/Common/WorldMouse/WorldMouse.h"
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/System/StageCollision/StageCollision.h"
#include "Libraries/SystemDatas/DepthStencil/DepthStencil.h"
// �I�u�W�F�N�g
#include "Game/PlayScene/Objects/Sky_Play/Sky_Play.h"
#include "Game/PlayScene/Objects/Player/Player.h"
#include "Game/Common/CursorObject/CursorObject.h"
#include "PlayScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================


//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using CameraType = AdminCamera::Type;					// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v
using MouseClick = Mouse::ButtonStateTracker;			// �}�E�X�̃N���b�N

//==============================================================================
// �R���X�g���N�^
//==============================================================================
PlayScene::PlayScene(const int& number)
	: IScene()					// ���N���X�̃R���X�g���N�^
	, m_stageNumber{ number }	// �X�e�[�W�ԍ�
{
	Debug::DrawString::GetInstance().DebugLog(L"PlayScene�̃R���X�g���N�^���Ă΂�܂����B\n");

	// �X�|�b�g���C�g�͈̔�
	m_lightTheta = 70.0f;

	// ���C�g�̈ʒu
	m_lightPosition = SimpleMath::Vector3(4.5f, 10.0f, 10.0f);

	// ���C�g�̉�]
	m_lightRotate = SimpleMath::Quaternion::CreateFromYawPitchRoll(
		XMConvertToRadians(-90.0f), XMConvertToRadians(45.0f), 0.0f);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
PlayScene::~PlayScene()
{
}

//==============================================================================
// ����������
//==============================================================================
void PlayScene::Initialize()
{
	// ��ʈˑ��̏�����
	CreateWDResources();

	// �ϐ��̏�����
	SetSceneValues();

	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �萔�o�b�t�@�̓��e�X�V
	LightFovBuffer cb = {};
	cb.fCosTheta = cosf(XMConvertToRadians(m_lightTheta / 2.0f));
	context->UpdateSubresource(m_lightConstant.Get(), 0, nullptr, &cb, 0, 0);

	// BGM��炷
	//auto _se = SoundManager::GetInstance();
	//_se->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_TEST, RepeatType::LOOP);
}

//==============================================================================
// �X�V����
//==============================================================================
void PlayScene::Update()
{
	auto _input = Input::GetInstance();
	auto _key = Keyboard::Get().GetState();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// �}�E�X�̉E�{�^����������Ă�����X�|�b�g���C�g����]������
	if (_key.Up)
	{
		float pitch = 0.001f;
		SimpleMath::Quaternion q = SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, pitch, 0.0f);
		m_lightRotate = q * m_lightRotate;
	}
	if (_key.Down)
	{
		float yaw = 0.001f;
		SimpleMath::Quaternion q = SimpleMath::Quaternion::CreateFromYawPitchRoll(yaw, 0.0f, 0.0f);
		m_lightRotate = q * m_lightRotate;
	}
	if (_key.Right)
	{
		float pitch = 0.001f;
		SimpleMath::Quaternion q = SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, -pitch, 0.0f);
		m_lightRotate = q * m_lightRotate;
	}
	if (_key.Left)
	{
		float yaw = 0.001f;
		SimpleMath::Quaternion q = SimpleMath::Quaternion::CreateFromYawPitchRoll(-yaw, 0.0f, 0.0f);
		m_lightRotate = q * m_lightRotate;
	}

	// �V�[���J��
	if (IsCanUpdate())
	{
		// �ǐՃp�X��ǉ�
		if (_input->GetMouseTrack()->leftButton == MouseClick::PRESSED)
		{
			SimpleMath::Vector3 _followPath = m_worldMouse->GetPosition();
			_followPath.y = m_player->GetPosition().y;
			m_player->PushBackFollowPath(_followPath);
		}

		// �S�[��������N���A��(���Z���N�g)
		if (m_blockManager->IsArrived())
		{
			m_adminCamera->SetInterpolation(true);// ��ԃ��[�h�ɂ���
			if (m_adminCamera->GetType() != CameraType::Select1_Floating)
			{
				m_adminCamera->SetType(CameraType::Select1_Floating);
			}
			ChangeScene(SCENE::SELECT);
		}

		// ���񂾂�ēǂݍ���
		if (m_player->IsDeath())
		{
			m_adminCamera->SetInterpolation(true);// ��ԃ��[�h�ɂ���
			if (m_adminCamera->GetType() != CameraType::Death_Following)
			{
				m_adminCamera->SetType(CameraType::Death_Following);
			}

			// �v���C����ǂ�������
			m_adminCamera->SetTarget(m_player->GetPosition());
			m_adminCamera->SetPosition(m_player->GetPosition() + SimpleMath::Vector3::UnitY);
			ChangeScene(SCENE::PLAY);
		}
	}

	// �J�����̍X�V
	m_adminCamera->Update();

	// ���[���h�}�E�X�̍X�V
	m_worldMouse->Update();
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
	m_cursorObject->Update();

	// �X�J�C���̍X�V(�J�����𒆐S�ɃX�J�C�����Z�b�g����@�`��؂��h��)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

	// �u���b�N�̍X�V
	m_blockManager->Update();

	// �v���C���[�̍X�V
	m_player->Update();

	// �����蔻��̍X�V
	m_stageCollision->Update(m_player.get(), m_blockManager.get());
}

//==============================================================================
// �`�揈��
//==============================================================================
void PlayScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// -------------------------------------------------------------------------- //
	// Pass1 �V���h�E�}�b�v�̍쐬
	// -------------------------------------------------------------------------- //

	auto rtv = m_shadowMapRT->GetRenderTargetView();
	auto srv = m_shadowMapRT->GetShaderResourceView();
	auto dsv = m_shadowMapDS->GetDepthStencilView();

	// �����_�[�^�[�Q�b�g��ύX�ishadowMapRT�j
	context->ClearRenderTargetView(rtv, SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f));
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, dsv);

	// �r���[�|�[�g��ݒ�
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0.0f, 1.0f };
	context->RSSetViewports(1, &vp);

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// ------------------------------------------------ //
	// ���C�g��Ԃ̃r���[�s��Ǝˉe�s����쐬����
	// ------------------------------------------------ //

	// ���C�g�̕���
	SimpleMath::Vector3 lightDir =
		SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_lightRotate);

	// �r���[�s����쐬
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(
		m_lightPosition,
		m_lightPosition + lightDir,
		SimpleMath::Vector3::UnitY
	);

	// �ˉe�s����쐬
	SimpleMath::Matrix proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(m_lightTheta), 1.0f, 0.1f, 250.0f);

	// -------------------------------------------------------------------------- //
	// �萔�o�b�t�@���X�V
	// -------------------------------------------------------------------------- //

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
	context->Map(m_shadowConstant.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �V���h�E�o�b�t�@���X�V
	ShadowBuffer cb = {};
	SimpleMath::Matrix m = view * proj;
	cb.lightViewProj = XMMatrixTranspose(m);
	cb.lightPosition = m_lightPosition;
	cb.lightDirection = lightDir;
	cb.lightAmbient = SimpleMath::Color(0.3f, 0.3f, 0.3f);

	*static_cast<ShadowBuffer*>(mappedResource.pData) = cb;

	// GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
	context->Unmap(m_shadowConstant.Get(), 0);

	// ------------------------------------------------ //
	// �e�ɂȂ郂�f����`�悷��
	// ------------------------------------------------ //

	// �u���b�N�̕`��
	m_blockManager->Draw(context, *states, view, proj, false, [&]()
		{
			context->VSSetShader(m_VS_Depth.Get(), nullptr, 0);
			context->PSSetShader(m_PS_Depth.Get(), nullptr, 0);
		}
	);

	// �v���C���[�̕`��
	m_player->Draw(context, *states, view, proj, false, [&]()
		{
			context->VSSetShader(m_VS_Depth.Get(), nullptr, 0);
			context->PSSetShader(m_PS_Depth.Get(), nullptr, 0);
		}
	);

	// -------------------------------------------------------------------------- //
	// �����_�[�^�[�Q�b�g�ƃr���[�|�[�g�����ɖ߂�
	// -------------------------------------------------------------------------- //
	auto renderTarget = DX::DeviceResources::GetInstance()->GetRenderTargetView();
	auto depthStencil = DX::DeviceResources::GetInstance()->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);
	auto const viewport = DX::DeviceResources::GetInstance()->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// �V�F�[�_�[�̐ݒ�
	auto _shadow = [&]() {
		// �萔�o�b�t�@�̐ݒ�
		ID3D11Buffer* cbuf[] = { m_shadowConstant.Get(), m_lightConstant.Get() };
		context->VSSetConstantBuffers(1, 1, cbuf);
		context->PSSetConstantBuffers(1, 2, cbuf);

		// �쐬�����V���h�E�}�b�v�����\�[�X�Ƃ��Đݒ�
		context->PSSetShaderResources(1, 1, &srv);

		// �e�N�X�`���T���v���[�̐ݒ�
		ID3D11SamplerState* samplers[] = { states->LinearWrap(), m_shadowMapSampler.Get() };
		context->PSSetSamplers(0, 2, samplers);

		// �V�F�[�_�[�̐ݒ�
		context->VSSetShader(m_VS.Get(), nullptr, 0);
		context->PSSetShader(m_PS.Get(), nullptr, 0); };

	// ���[���h�}�E�X�̕`��
	m_worldMouse->Draw(_view, _projection);

	// �J�[�\���I�u�W�F�N�g�̕`��
	m_cursorObject->Draw(context, *states, _view, _projection, false, _shadow);

	// ��̕`��
	m_sky->Draw(context, *states, _view, _projection);

	// �u���b�N�̕`��
	m_blockManager->Draw(context, *states, _view, _projection, false, _shadow);

	// �v���C���[�̕`��
	m_player->Draw(context, *states, _view, _projection, false, _shadow);

	// ���\�[�X�̊��蓖�Ă���������ishadowMapRT�j
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	context->PSSetShaderResources(1, 1, nullsrv);

	// �f�o�b�O�`��
#ifdef _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*states, _view, _projection, Colors::Green);
	DebugDraw(*states);
#endif
}

//==============================================================================
// �I������
//==============================================================================
void PlayScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
	m_player.reset();
	m_worldMouse.reset();
	m_blockManager.reset();
	m_stageCollision.reset();
	m_cursorObject.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void PlayScene::CreateWDResources()
{
	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// �X�J�C���I�u�W�F�N�g�쐬
	m_sky = std::make_unique<Sky_Play>();

	// �v���C���[�쐬
	m_player = std::make_unique<Player>();

	// ���[���h�}�E�X�쐬
	m_worldMouse = std::make_unique<WorldMouse>();

	// �u���b�N�}�l�[�W���쐬
	m_blockManager = std::make_unique<BlockManager>(GetStagePath());

	// �X�e�[�W�R���W�����쐬
	m_stageCollision = std::make_unique<StageCollision>();

	// �J�[�\���I�u�W�F�N�g�쐬
	m_cursorObject = std::make_unique<CursorObject>();




	RECT rect = { 0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE };

	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �����_�[�e�N�X�`���̍쐬�i�V���h�E�}�b�v�p�j
	m_shadowMapRT = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_shadowMapRT->SetDevice(device);
	m_shadowMapRT->SetWindow(rect);

	// �f�v�X�X�e���V���̍쐬�i�V���h�E�}�b�v�p�j
	m_shadowMapDS = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_shadowMapDS->SetDevice(device);
	m_shadowMapDS->SetWindow(rect);

	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> vs_depth = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS_Depth.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs_depth.data(), vs_depth.size(), nullptr, m_VS_Depth.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> ps_depth = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS_Depth.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_depth.data(), ps_depth.size(), nullptr, m_PS_Depth.ReleaseAndGetAddressOf())
	);

	// �萔�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(ShadowBuffer));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	// GPU (�ǂݎ���p) �� CPU (�������ݐ�p) �̗�������A�N�Z�X�ł��郊�\�[�X
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�����e��ύX�ł���悤�ɂ���
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_shadowConstant.ReleaseAndGetAddressOf()));

	// �萔�o�b�t�@�̍쐬
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(LightFovBuffer));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;	// GPU�̓ǂݎ��Ə������݂��\�Ȉ�ʓI�ȃ��\�[�X
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc.CPUAccessFlags = 0;	// CPU�̓A�N�Z�X���Ȃ��̂�0
	DX::ThrowIfFailed(device->CreateBuffer(&bufferDesc, nullptr, m_lightConstant.ReleaseAndGetAddressOf()));

	// ���_�V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs.data(), vs.size(), nullptr, m_VS.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�[�̍쐬�i�V���h�E�}�b�v�p�j
	std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(), nullptr, m_PS.ReleaseAndGetAddressOf())
	);

	// �T���v���[�̍쐬�i�V���h�E�}�b�v�p�j
	D3D11_SAMPLER_DESC sampler_desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
	sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS;
	device->CreateSamplerState(&sampler_desc, m_shadowMapSampler.ReleaseAndGetAddressOf());
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void PlayScene::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetInterpolation(false);	// ��Ԃ�؂�

	// �v���C���[�h�ɂ���
	m_worldMouse->ToPlayMode();

	// �u���b�N�̏����ݒ�
	m_blockManager->SetPlay(true);
	m_blockManager->Initialize();

	// �v���C���[�̍��W��Ԃ�
	m_player->SetPosition(m_blockManager->GetPlayerPosition());

	// �J�[�\���I�u�W�F�N�g�Ƀ��[���h�}�E�X�̍��W��ݒ�
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void PlayScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 },  Colors::Black, L"PlayScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::Black, L"StageNum::%.d", m_stageNumber);
	_string.DrawFormatString(states, { 0,125 }, Colors::Black, L"PlayerPos::%.2f,%.2f,%.2f",
		m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	_string.DrawFormatString(states, { 0,150 }, Colors::Black, L"WorldMouse::%.2f,%.2f,%.2f",
		m_worldMouse->GetPosition().x, m_worldMouse->GetPosition().y, m_worldMouse->GetPosition().z);
	_string.DrawFormatString(states, { 0,175 }, Colors::Black, L"SettingPath::%d", m_player->GetGoalPoints().size());
	_string.DrawFormatString(states, { 0,200 }, Colors::Black, L"HaveCoinNum::%d", m_player->GetCoinNum());
}

//==============================================================================
// �X�e�[�W�̃p�X���擾����
//==============================================================================
const wchar_t* PlayScene::GetStagePath()
{
	switch (m_stageNumber)
	{
	case 1:
		return L"Resources/Stages/sample1.json";
	case 2:
		return L"Resources/Stages/sample2.json";
	case 3:
		return L"Resources/Stages/sample3.json";


	default:
		return L"Resources/Stages/sample1.json";
	}
}
