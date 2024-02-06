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
#include "Game/PlayScene/System/FlagManager/FlagManager.h"
// �I�u�W�F�N�g
#include "Game/PlayScene/Objects/Sky_Play/Sky_Play.h"
#include "Game/PlayScene/Objects/Player/Player.h"
#include "Game/Common/CursorObject/CursorObject.h"
#include "PlayScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const int PlayScene::SHADOWMAP_SIZE = 512;		// �V���h�E�}�b�v�̃T�C�Y
const float PlayScene::AMBIENT_COLOR = 0.3f;	// �A���r�G���g���C�g�̐F
const int PlayScene::MAX_FOLLOW = 3;			// �ő�ǐՃp�X��
const float PlayScene::FLAG_START = 5.0f;		// �ō����x
// ���C�g�̈ʒu�E���C�g�̉�]�E���C�g�͈̔�
const SimpleMath::Vector3 PlayScene::LIGHT_POSITION = { 4.5f, 10.0f, 10.0f };
const SimpleMath::Quaternion PlayScene::LIGHT_ROTATION = { 0.80f, 0.30f, -0.20f, 0.50f };
const float PlayScene::LIGHT_THETA = 85.0f;

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

	// �V�[���J��
	if (IsCanUpdate())
	{
		// �ǐՃp�X��ǉ�
		if (_input->GetMouseTrack()->leftButton == MouseClick::PRESSED)
		{
			// �v���C���[�̍��W
			SimpleMath::Vector3 _playerPos = m_worldMouse->GetPosition();
			_playerPos.y = m_player->GetPosition().y;

			// ���̊J�n���W
			SimpleMath::Vector3 _flagPos = m_worldMouse->GetPosition();
			_flagPos.y = FLAG_START;

			m_player->AddFollowPath(_playerPos, MAX_FOLLOW);
			m_flagManager->AddFlag(_flagPos, _playerPos, MAX_FOLLOW);
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

	// �ǐՃp�X���ƃt���O������v���Ȃ��Ȃ�����t���O���폜
	if (m_flagManager->GetFlags().size() - m_player->GetFollowPath().size() > 0)
	{
		m_flagManager->PickFlag();
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

	// �t���O�}�l�[�W���̍X�V
	m_flagManager->Update();
}

//==============================================================================
// �`�揈��
//==============================================================================
void PlayScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	//==============================================================================
	// �����_�[�^�[�Q�b�g���V���h�E�}�b�v�p�ɕύX
	//==============================================================================
	auto _rtv = m_renderTexture->GetRenderTargetView();
	auto _dsv = m_depthStencil->GetDepthStencilView();
	_context->ClearRenderTargetView(_rtv, Colors::CornflowerBlue);
	_context->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	_context->OMSetRenderTargets(1, &_rtv, _dsv);
	D3D11_VIEWPORT _vp = { 0.0f, 0.0f, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0.0f, 1.0f };
	_context->RSSetViewports(1, &_vp);

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	//==============================================================================
	// ���C�g�̐ݒ�
	//==============================================================================
	// ���C�g�̕���
	SimpleMath::Vector3 _lightDir =
		SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, 1.0f), LIGHT_ROTATION);

	// �r���[�s����쐬
	SimpleMath::Matrix _lightView = SimpleMath::Matrix::CreateLookAt(
		LIGHT_POSITION,
		LIGHT_POSITION + _lightDir,
		SimpleMath::Vector3::UnitY
	);

	// �ˉe�s����쐬
	SimpleMath::Matrix _lightProj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(LIGHT_THETA), 1.0f, 0.1f, 250.0f);

	//==============================================================================
	// �V���h�E�o�b�t�@���쐬
	//==============================================================================
	// GPU����̃A�N�Z�X�����b�N
	D3D11_MAPPED_SUBRESOURCE _map;
	_context->Map(m_shadowConstant.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_map);

	// �V���h�E�o�b�t�@���X�V
	ShadowBuffer _shadowBuff = {};
	_shadowBuff.lightViewProj = XMMatrixTranspose(_lightView * _lightProj);
	_shadowBuff.lightPosition = LIGHT_POSITION;
	_shadowBuff.lightDirection = _lightDir;
	_shadowBuff.lightAmbient = SimpleMath::Color(AMBIENT_COLOR, AMBIENT_COLOR, AMBIENT_COLOR);
	*static_cast<ShadowBuffer*>(_map.pData) = _shadowBuff;

	// GPU����̃A�N�Z�X���A�����b�N
	_context->Unmap(m_shadowConstant.Get(), 0);

	//==============================================================================
	// �f�v�X�����_�̍쐬
	//==============================================================================
	ShaderLambda _depth = [&]()
		{
			_context->VSSetShader(m_vsDep.Get(), nullptr, 0);
			_context->PSSetShader(m_psDep.Get(), nullptr, 0);
		};

	//==============================================================================
	// �e�I�u�W�F�N�g��`�悷��
	//==============================================================================

	// �J�[�\���̕`��
	m_cursorObject->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	// �u���b�N�̕`��
	m_blockManager->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	// �v���C���[�̕`��
	m_player->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	// �t���O�̕`��
	m_flagManager->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	//==============================================================================
	// �����_�[�^�[�Q�b�g���f�t�H���g�ɖ߂�
	//==============================================================================
	auto _rtvDefault = DX::DeviceResources::GetInstance()->GetRenderTargetView();
	auto _dsvDefault = DX::DeviceResources::GetInstance()->GetDepthStencilView();
	auto _srvDefault = m_renderTexture->GetShaderResourceView();
	_context->ClearRenderTargetView(_rtvDefault, Colors::CornflowerBlue);
	_context->ClearDepthStencilView(_dsvDefault, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	_context->OMSetRenderTargets(1, &_rtvDefault, _dsvDefault);
	auto const _vpDefault = DX::DeviceResources::GetInstance()->GetScreenViewport();
	_context->RSSetViewports(1, &_vpDefault);

	//==============================================================================
	// �V���h�E�����_�̍쐬
	//==============================================================================
	ShaderLambda _shadow = [&]()
		{
			// �萔�o�b�t�@�̐ݒ�
			ID3D11Buffer* _buffer[] = { m_shadowConstant.Get(), m_lightConstant.Get() };
			_context->VSSetConstantBuffers(1, 1, _buffer);
			_context->PSSetConstantBuffers(1, 2, _buffer);

			// �쐬�����V���h�E�}�b�v�����\�[�X�Ƃ��Đݒ�
			_context->PSSetShaderResources(1, 1, &_srvDefault);

			// �e�N�X�`���T���v���[�̐ݒ�
			ID3D11SamplerState* _samplers[] = { _states->LinearWrap(), m_sampler.Get() };
			_context->PSSetSamplers(0, 2, _samplers);

			// �V�F�[�_�[�̐ݒ�
			_context->VSSetShader(m_vs.Get(), nullptr, 0);
			_context->PSSetShader(m_ps.Get(), nullptr, 0);
		};

	// ���[���h�}�E�X�̕`��
	m_worldMouse->Draw(_view, _projection);

	// ��̕`��
	m_sky->Draw(_context, *_states, _view, _projection);

	// �J�[�\���I�u�W�F�N�g�̕`��
	m_cursorObject->Draw(_context, *_states, _view, _projection, false, _shadow);

	// �u���b�N�̕`��
	m_blockManager->Draw(_context, *_states, _view, _projection, false, _shadow);

	// �v���C���[�̕`��
	m_player->Draw(_context, *_states, _view, _projection, false, _shadow);

	// �t���O�̕`��
	m_flagManager->Draw(_context, *_states, _view, _projection, false, _shadow);


	//==============================================================================
	// ���\�[�X�̊��蓖�Ă���������
	//==============================================================================
	ID3D11ShaderResourceView* _nullsrv[] = { nullptr };
	_context->PSSetShaderResources(1, 1, _nullsrv);

	// �f�o�b�O�`��
#ifdef _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
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
	m_flagManager.reset();
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
	m_cursorObject = std::make_unique<CursorObject>(
		L"Resources/Models/Flag.cmo", SimpleMath::Vector3::One * 0.4f);

	// �t���O�}�l�[�W���쐬
	m_flagManager = std::make_unique<FlagManager>();

	//==============================================================================
	// �V���h�E�}�b�v�֘A�̍쐬
	//==============================================================================
	RECT _rect = { 0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE };
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �����_�[�e�N�X�`���̍쐬
	{
		m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
		m_renderTexture->SetDevice(_device);
		m_renderTexture->SetWindow(_rect);
	}

	// �f�v�X�X�e���V���̍쐬
	{
		m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
		m_depthStencil->SetDevice(_device);
		m_depthStencil->SetWindow(_rect);
	}

	// �f�v�X���_�V�F�[�_�[�̍쐬
	{
		std::vector<uint8_t> _vsDep = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS_Depth.cso");
		DX::ThrowIfFailed(
			_device->CreateVertexShader(
				_vsDep.data(), _vsDep.size(), nullptr, m_vsDep.ReleaseAndGetAddressOf()
			)
		);
	}

	// �f�v�X�s�N�Z���V�F�[�_�[�̍쐬
	{
		std::vector<uint8_t> _psDep = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS_Depth.cso");
		DX::ThrowIfFailed(
			_device->CreatePixelShader(
				_psDep.data(), _psDep.size(), nullptr, m_psDep.ReleaseAndGetAddressOf()
			)
		);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// �萔�o�b�t�@�쐬�菇(�p��)			 //	�萔�o�b�t�@�쐬�菇(�ɋH)			//
	// [Shadow]								 //	[LightFov]							//
	// �@GPU�ECPU����̃A�N�Z�X������		 //	�@GPU���̂݃A�N�Z�X����				//
	// �A���\�[�X�̓_�C�i�~�b�N				 //	�A���\�[�X�̓f�t�H���g				//
	// �BCPU�����珑�����݂��ł���悤�ɐݒ� //	�BCPU�̃A�N�Z�X�͐�������			//
	//////////////////////////////////////////////////////////////////////////////////

	// �V���h�E�o�b�t�@�̍쐬
	{
		D3D11_BUFFER_DESC _desc = {};
		_desc.ByteWidth = static_cast<UINT>(sizeof(ShadowBuffer));
		_desc.Usage = D3D11_USAGE_DYNAMIC;
		_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(
			_device->CreateBuffer(&_desc, nullptr, m_shadowConstant.ReleaseAndGetAddressOf())
		);
	}

	// ���C�g�t�H�u�o�b�t�@�̍쐬
	{
		D3D11_BUFFER_DESC _desc = {};
		_desc.ByteWidth = static_cast<UINT>(sizeof(LightFovBuffer));
		_desc.Usage = D3D11_USAGE_DEFAULT;
		_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		_desc.CPUAccessFlags = 0;
		DX::ThrowIfFailed(
			_device->CreateBuffer(&_desc, nullptr, m_lightConstant.ReleaseAndGetAddressOf())
		);
	}

	// ���_�V�F�[�_�[�̍쐬
	{
		std::vector<uint8_t> _vs = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS.cso");
		DX::ThrowIfFailed(
			_device->CreateVertexShader(
				_vs.data(), _vs.size(), nullptr, m_vs.ReleaseAndGetAddressOf()
			)
		);
	}

	// �s�N�Z���V�F�[�_�[�̍쐬
	{
		std::vector<uint8_t> _ps = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS.cso");
		DX::ThrowIfFailed(
			_device->CreatePixelShader(
				_ps.data(), _ps.size(), nullptr, m_ps.ReleaseAndGetAddressOf()
			)
		);
	}

	// �T���v���[�̍쐬
	{
		D3D11_SAMPLER_DESC _desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
		_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
		_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		_desc.ComparisonFunc = D3D11_COMPARISON_LESS;
		_device->CreateSamplerState(&_desc, m_sampler.ReleaseAndGetAddressOf());
	}
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

	// ���C�g�o�b�t�@�̍X�V
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	LightFovBuffer _lightBuff = {};
	_lightBuff.fCosTheta = cosf(XMConvertToRadians(LIGHT_THETA / 2.0f));
	_context->UpdateSubresource(m_lightConstant.Get(), 0, nullptr, &_lightBuff, 0, 0);
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
	_string.DrawFormatString(states, { 0,175 }, Colors::Black, L"SettingPath::%d", m_player->GetFollowPath().size());
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
