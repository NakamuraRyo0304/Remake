/*
 *	@File	PlayScene.cpp
 *	@Brief	プレイシーン。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/Common/WorldMouse/WorldMouse.h"
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/System/StageCollision/StageCollision.h"
#include "Libraries/SystemDatas/DepthStencil/DepthStencil.h"
#include "Game/PlayScene/System/FlagManager/FlagManager.h"
// オブジェクト
#include "Game/PlayScene/Objects/Sky_Play/Sky_Play.h"
#include "Game/PlayScene/Objects/Player/Player.h"
#include "Game/Common/CursorObject/CursorObject.h"
#include "PlayScene.h"

//==============================================================================
// 定数の設定
//==============================================================================
const int PlayScene::SHADOWMAP_SIZE = 512;		// シャドウマップのサイズ
const float PlayScene::AMBIENT_COLOR = 0.3f;	// アンビエントライトの色
const int PlayScene::MAX_FOLLOW = 3;			// 最大追跡パス数
const float PlayScene::FLAG_START = 5.0f;		// 最高高度
// ライトの位置・ライトの回転・ライトの範囲
const SimpleMath::Vector3 PlayScene::LIGHT_POSITION = { 4.5f, 10.0f, 10.0f };
const SimpleMath::Quaternion PlayScene::LIGHT_ROTATION = { 0.80f, 0.30f, -0.20f, 0.50f };
const float PlayScene::LIGHT_THETA = 85.0f;

//==============================================================================
// エイリアス宣言
//==============================================================================
using KeyCode = Keyboard::Keys;							// キーコード
using CameraType = AdminCamera::Type;					// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;				// サウンドのタイプ
using MouseClick = Mouse::ButtonStateTracker;			// マウスのクリック

//==============================================================================
// コンストラクタ
//==============================================================================
PlayScene::PlayScene(const int& number)
	: IScene()					// 基底クラスのコンストラクタ
	, m_stageNumber{ number }	// ステージ番号
{
	Debug::DrawString::GetInstance().DebugLog(L"PlaySceneのコンストラクタが呼ばれました。\n");
}

//==============================================================================
// デストラクタ
//==============================================================================
PlayScene::~PlayScene()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void PlayScene::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();

	// BGMを鳴らす
	//auto _se = SoundManager::GetInstance();
	//_se->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_TEST, RepeatType::LOOP);
}

//==============================================================================
// 更新処理
//==============================================================================
void PlayScene::Update()
{
	auto _input = Input::GetInstance();
	auto _key = Keyboard::Get().GetState();

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// シーン遷移
	if (IsCanUpdate())
	{
		// 追跡パスを追加
		if (_input->GetMouseTrack()->leftButton == MouseClick::PRESSED)
		{
			// プレイヤーの座標
			SimpleMath::Vector3 _playerPos = m_worldMouse->GetPosition();
			_playerPos.y = m_player->GetPosition().y;

			// 旗の開始座標
			SimpleMath::Vector3 _flagPos = m_worldMouse->GetPosition();
			_flagPos.y = FLAG_START;

			m_player->AddFollowPath(_playerPos, MAX_FOLLOW);
			m_flagManager->AddFlag(_flagPos, _playerPos, MAX_FOLLOW);
		}

		// ゴールしたらクリアへ(仮セレクト)
		if (m_blockManager->IsArrived())
		{
			m_adminCamera->SetInterpolation(true);// 補間モードにする
			if (m_adminCamera->GetType() != CameraType::Select1_Floating)
			{
				m_adminCamera->SetType(CameraType::Select1_Floating);
			}
			ChangeScene(SCENE::SELECT);
		}

		// 死んだら再読み込み
		if (m_player->IsDeath())
		{
			m_adminCamera->SetInterpolation(true);// 補間モードにする
			if (m_adminCamera->GetType() != CameraType::Death_Following)
			{
				m_adminCamera->SetType(CameraType::Death_Following);
			}

			// プレイヤを追いかける
			m_adminCamera->SetTarget(m_player->GetPosition());
			m_adminCamera->SetPosition(m_player->GetPosition() + SimpleMath::Vector3::UnitY);
			ChangeScene(SCENE::PLAY);
		}
	}

	// 追跡パス数とフラグ数が一致しなくなったらフラグを削除
	if (m_flagManager->GetFlags().size() - m_player->GetFollowPath().size() > 0)
	{
		m_flagManager->PickFlag();
	}

	// カメラの更新
	m_adminCamera->Update();

	// ワールドマウスの更新
	m_worldMouse->Update();
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
	m_cursorObject->Update();

	// スカイ球の更新(カメラを中心にスカイ球をセットする　描画切れを防ぐ)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

	// ブロックの更新
	m_blockManager->Update();

	// プレイヤーの更新
	m_player->Update();

	// 当たり判定の更新
	m_stageCollision->Update(m_player.get(), m_blockManager.get());

	// フラグマネージャの更新
	m_flagManager->Update();
}

//==============================================================================
// 描画処理
//==============================================================================
void PlayScene::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	//==============================================================================
	// レンダーターゲットをシャドウマップ用に変更
	//==============================================================================
	auto _rtv = m_renderTexture->GetRenderTargetView();
	auto _dsv = m_depthStencil->GetDepthStencilView();
	_context->ClearRenderTargetView(_rtv, Colors::CornflowerBlue);
	_context->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	_context->OMSetRenderTargets(1, &_rtv, _dsv);
	D3D11_VIEWPORT _vp = { 0.0f, 0.0f, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0.0f, 1.0f };
	_context->RSSetViewports(1, &_vp);

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	//==============================================================================
	// ライトの設定
	//==============================================================================
	// ライトの方向
	SimpleMath::Vector3 _lightDir =
		SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, 1.0f), LIGHT_ROTATION);

	// ビュー行列を作成
	SimpleMath::Matrix _lightView = SimpleMath::Matrix::CreateLookAt(
		LIGHT_POSITION,
		LIGHT_POSITION + _lightDir,
		SimpleMath::Vector3::UnitY
	);

	// 射影行列を作成
	SimpleMath::Matrix _lightProj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(LIGHT_THETA), 1.0f, 0.1f, 250.0f);

	//==============================================================================
	// シャドウバッファを作成
	//==============================================================================
	// GPUからのアクセスをロック
	D3D11_MAPPED_SUBRESOURCE _map;
	_context->Map(m_shadowConstant.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_map);

	// シャドウバッファを更新
	ShadowBuffer _shadowBuff = {};
	_shadowBuff.lightViewProj = XMMatrixTranspose(_lightView * _lightProj);
	_shadowBuff.lightPosition = LIGHT_POSITION;
	_shadowBuff.lightDirection = _lightDir;
	_shadowBuff.lightAmbient = SimpleMath::Color(AMBIENT_COLOR, AMBIENT_COLOR, AMBIENT_COLOR);
	*static_cast<ShadowBuffer*>(_map.pData) = _shadowBuff;

	// GPUからのアクセスをアンロック
	_context->Unmap(m_shadowConstant.Get(), 0);

	//==============================================================================
	// デプスラムダの作成
	//==============================================================================
	ShaderLambda _depth = [&]()
		{
			_context->VSSetShader(m_vsDep.Get(), nullptr, 0);
			_context->PSSetShader(m_psDep.Get(), nullptr, 0);
		};

	//==============================================================================
	// 影オブジェクトを描画する
	//==============================================================================

	// カーソルの描画
	m_cursorObject->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	// ブロックの描画
	m_blockManager->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	// プレイヤーの描画
	m_player->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	// フラグの描画
	m_flagManager->Draw(_context, *_states, _lightView, _lightProj, false, _depth);

	//==============================================================================
	// レンダーターゲットをデフォルトに戻す
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
	// シャドウラムダの作成
	//==============================================================================
	ShaderLambda _shadow = [&]()
		{
			// 定数バッファの設定
			ID3D11Buffer* _buffer[] = { m_shadowConstant.Get(), m_lightConstant.Get() };
			_context->VSSetConstantBuffers(1, 1, _buffer);
			_context->PSSetConstantBuffers(1, 2, _buffer);

			// 作成したシャドウマップをリソースとして設定
			_context->PSSetShaderResources(1, 1, &_srvDefault);

			// テクスチャサンプラーの設定
			ID3D11SamplerState* _samplers[] = { _states->LinearWrap(), m_sampler.Get() };
			_context->PSSetSamplers(0, 2, _samplers);

			// シェーダーの設定
			_context->VSSetShader(m_vs.Get(), nullptr, 0);
			_context->PSSetShader(m_ps.Get(), nullptr, 0);
		};

	// ワールドマウスの描画
	m_worldMouse->Draw(_view, _projection);

	// 空の描画
	m_sky->Draw(_context, *_states, _view, _projection);

	// カーソルオブジェクトの描画
	m_cursorObject->Draw(_context, *_states, _view, _projection, false, _shadow);

	// ブロックの描画
	m_blockManager->Draw(_context, *_states, _view, _projection, false, _shadow);

	// プレイヤーの描画
	m_player->Draw(_context, *_states, _view, _projection, false, _shadow);

	// フラグの描画
	m_flagManager->Draw(_context, *_states, _view, _projection, false, _shadow);


	//==============================================================================
	// リソースの割り当てを解除する
	//==============================================================================
	ID3D11ShaderResourceView* _nullsrv[] = { nullptr };
	_context->PSSetShaderResources(1, 1, _nullsrv);

	// デバッグ描画
#ifdef _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
#endif
}

//==============================================================================
// 終了処理
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
// 画面、デバイス依存の初期化
//==============================================================================
void PlayScene::CreateWDResources()
{
	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// スカイ球オブジェクト作成
	m_sky = std::make_unique<Sky_Play>();

	// プレイヤー作成
	m_player = std::make_unique<Player>();

	// ワールドマウス作成
	m_worldMouse = std::make_unique<WorldMouse>();

	// ブロックマネージャ作成
	m_blockManager = std::make_unique<BlockManager>(GetStagePath());

	// ステージコリジョン作成
	m_stageCollision = std::make_unique<StageCollision>();

	// カーソルオブジェクト作成
	m_cursorObject = std::make_unique<CursorObject>(
		L"Resources/Models/Flag.cmo", SimpleMath::Vector3::One * 0.4f);

	// フラグマネージャ作成
	m_flagManager = std::make_unique<FlagManager>();

	//==============================================================================
	// シャドウマップ関連の作成
	//==============================================================================
	RECT _rect = { 0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE };
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// レンダーテクスチャの作成
	{
		m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
		m_renderTexture->SetDevice(_device);
		m_renderTexture->SetWindow(_rect);
	}

	// デプスステンシルの作成
	{
		m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
		m_depthStencil->SetDevice(_device);
		m_depthStencil->SetWindow(_rect);
	}

	// デプス頂点シェーダーの作成
	{
		std::vector<uint8_t> _vsDep = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS_Depth.cso");
		DX::ThrowIfFailed(
			_device->CreateVertexShader(
				_vsDep.data(), _vsDep.size(), nullptr, m_vsDep.ReleaseAndGetAddressOf()
			)
		);
	}

	// デプスピクセルシェーダーの作成
	{
		std::vector<uint8_t> _psDep = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS_Depth.cso");
		DX::ThrowIfFailed(
			_device->CreatePixelShader(
				_psDep.data(), _psDep.size(), nullptr, m_psDep.ReleaseAndGetAddressOf()
			)
		);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// 定数バッファ作成手順(頻繁)			 //	定数バッファ作成手順(極稀)			//
	// [Shadow]								 //	[LightFov]							//
	// ①GPU・CPUからのアクセスを許可		 //	①GPU側のみアクセス許可				//
	// ②リソースはダイナミック				 //	②リソースはデフォルト				//
	// ③CPU側から書き込みをできるように設定 //	③CPUのアクセスは制限する			//
	//////////////////////////////////////////////////////////////////////////////////

	// シャドウバッファの作成
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

	// ライトフォブバッファの作成
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

	// 頂点シェーダーの作成
	{
		std::vector<uint8_t> _vs = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS.cso");
		DX::ThrowIfFailed(
			_device->CreateVertexShader(
				_vs.data(), _vs.size(), nullptr, m_vs.ReleaseAndGetAddressOf()
			)
		);
	}

	// ピクセルシェーダーの作成
	{
		std::vector<uint8_t> _ps = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS.cso");
		DX::ThrowIfFailed(
			_device->CreatePixelShader(
				_ps.data(), _ps.size(), nullptr, m_ps.ReleaseAndGetAddressOf()
			)
		);
	}

	// サンプラーの作成
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
// シーン内の変数初期化関数
//==============================================================================
void PlayScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetInterpolation(false);	// 補間を切る

	// プレイモードにする
	m_worldMouse->ToPlayMode();

	// ブロックの初期設定
	m_blockManager->SetPlay(true);
	m_blockManager->Initialize();

	// プレイヤーの座標を返す
	m_player->SetPosition(m_blockManager->GetPlayerPosition());

	// カーソルオブジェクトにワールドマウスの座標を設定
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());

	// ライトバッファの更新
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	LightFovBuffer _lightBuff = {};
	_lightBuff.fCosTheta = cosf(XMConvertToRadians(LIGHT_THETA / 2.0f));
	_context->UpdateSubresource(m_lightConstant.Get(), 0, nullptr, &_lightBuff, 0, 0);
}

//==============================================================================
// デバッグ描画
//==============================================================================
void PlayScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
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
// ステージのパスを取得する
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
