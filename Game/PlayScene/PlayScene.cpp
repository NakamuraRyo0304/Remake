/*
 *	@File	PlayScene.cpp
 *	@Brief	プレイシーン。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"													// プリコンパイル済みヘッダー
#include "Game/Cameras/AdminCamera/AdminCamera.h"					// 統合カメラ
#include "Game/PlayScene/System/UI_Play/UI_Play.h"					// ユーザインターフェース
#include "Libraries/SystemDatas/Timer/Timer.h"						// タイマー

#include "Game/PlayScene/Objects/Sky_Play/Sky_Play.h"				// スカイドーム
#include "Game/PlayScene/System/ImageShot/ImageShot.h"				// スクリーンショット作成クラス
#include "Libraries/SystemDatas/DepthStencil/DepthStencil.h"		// デプスステンシル（シャドウマップ用）

#include "Game/Common/BlockManager/BlockManager.h"					// ブロック管理クラス
#include "Game/PlayScene/System/StageCollision/StageCollision.h"	// ステージ当たり判定
#include "Game/PlayScene/System/FlagManager/FlagManager.h"			// フラグ管理クラス
#include "Game/PlayScene/Objects/Player/Player.h"					// プレイヤー（ペンギン）
#include "Game/Common/WorldMouse/WorldMouse.h"						// ３Ｄ変換後のマウスシステム
#include "Game/Common/CursorObject/CursorObject.h"					// ３Ｄ変換後のマウスオブジェクト
#include "Game/Common/Water/Water.h"								// 海
#include "Game/PlayScene/Objects/Iceberg/Iceberg.h"					// 氷山

#include "PlayScene.h"												// プレイシーン

// 定数の設定(シャドウマップ)
const int PlayScene::SHADOWMAP_SIZE = 976;		// シャドウマップのサイズ
const float PlayScene::AMBIENT_COLOR = 0.25f;	// 環境光の色
const float PlayScene::LIGHT_THETA = 85.0f;		// ライトの範囲
// 定数の設定(フラグ追跡)
const int PlayScene::MAX_FOLLOW = 3;			// 最大追跡パス数
const float PlayScene::FLAG_START = 5.0f;		// 最高高度
const float PlayScene::FLAG_CURSOR_RATE = 0.4f;	// フラグカーソルの拡大率

// エイリアス宣言
using KeyCode = Keyboard::Keys;					// キーコード
using CameraType = AdminCamera::Type;			// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;		// サウンドのタイプ
using MouseClick = Mouse::ButtonStateTracker;	// マウスのクリック

// コンストラクタ
PlayScene::PlayScene(const int& number)
	:
	IScene(),				// 基底クラスのコンストラクタ
	m_stageNumber(number),	// ステージ番号
	m_gameTimer(0.0f),		// ゲームタイマー
	m_collectedCoin(0)		// 集めたコイン数
{
	Debug::DrawString::GetInstance().DebugLog(L"PlaySceneのコンストラクタが呼ばれました。\n");
}

// デストラクタ
PlayScene::~PlayScene()
{
	Debug::DrawString::GetInstance().DebugLog(L"PlaySceneのデストラクタが呼ばれました。\n");
	Finalize();
}

// 初期化
void PlayScene::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();

	// ボリューム設定・音量再生開始(BGM・環境音)
	auto sound = SoundManager::GetInstance();
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_BGM_DEFAULT, 0.25f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_DEFAULT, RepeatType::LOOP);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE,     RepeatType::LOOP);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE2,    RepeatType::LOOP);
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_SE_SLIDE, 0.7f);
}

// 更新
void PlayScene::Update()
{
	auto input = Input::GetInstance();
	auto key = Keyboard::Get().GetState();
	auto sound = SoundManager::GetInstance();

	// セレクトに戻る
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		ChangeScene(SCENE::SELECT);
	}

	// シーン遷移
	if (IsCanUpdate())
	{
		// タイマーの更新
		m_timer->Update(true);

		// 追跡パスを追加
		if (input->GetMouseTrack()->leftButton == MouseClick::PRESSED)
		{
			// プレイヤーの座標
			SimpleMath::Vector3 playerPosition = m_worldMouse->GetPosition();
			playerPosition.y = m_player->GetPosition().y;

			// 旗の開始座標
			SimpleMath::Vector3 flagPosition = m_worldMouse->GetPosition();
			flagPosition.y = FLAG_START;

			m_player->AddFollowPath(playerPosition, MAX_FOLLOW);
			m_flagManager->AddFlag(flagPosition, playerPosition, MAX_FOLLOW);
		}

		// コインが当たったら音を鳴らす
		if (m_player->IsCoinHit())
		{
			sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_COIN, RepeatType::ONCE);
			m_player->SetCoinHit(false);
		}

		// ゴールしたらクリアへ
		if (m_blockManager->IsArrived())
		{
			// シャッター音を鳴らす
			sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SLIDE, RepeatType::ONCE);

			// ゲームタイマー/集めたコイン数を取得
			m_timer->Stop();
			m_gameTimer = m_timer->GetCount();
			m_collectedCoin = m_player->GetCoinNum();

			// カメラ挙動
			m_adminCamera->SetInterpolation(true);// 補間モードにする
			if (m_adminCamera->GetType() != CameraType::Select1_Floating)
			{
				// クリアシーンで使うテクスチャの作成
				m_imageShot->TakePic(L"Resources/Textures/ScreenShot/image.dds",
					m_stageTexPath.c_str());	// コピーを作成してセレクトシーンで使う

				// カメラを設定(仮でセレクトフロ－ティング)
				m_adminCamera->SetType(CameraType::Select1_Floating);
			}
			ChangeScene(SCENE::CLEAR);
		}

		// 死亡またはボタンクリックで再読み込み
		if (m_player->IsDeath() || m_ui->IsPushRetry())
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
	m_stageCollision->Update(m_player.get());

	// フラグマネージャの更新
	m_flagManager->Update();

	// UIの更新
	int number = 0;
	for (auto& coin : m_blockManager->GetCoins())
	{
		if (coin->IsActive()) number++;
	}
	m_ui->SetCoinNum(number);
	m_ui->Update();

	// 氷山の更新
	m_iceberg->Update();
	m_smallberg->Update();
	m_bigberg->Update();
}

// 描画
void PlayScene::Draw()
{
	// レンダリング変数を取得
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// レンダーターゲットをシャドウマップ用に変更
	auto rtv = m_renderTexture->GetRenderTargetView();
	auto dsv = m_depthStencil->GetDepthStencilView();
	context->ClearRenderTargetView(rtv, Colors::CornflowerBlue);
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, dsv);
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0.0f, 1.0f };
	context->RSSetViewports(1, &vp);

	// ライトの設定
	SimpleMath::Vector3 lightDir =
		SimpleMath::Vector3::Transform(SimpleMath::Vector3::UnitZ, LIGHT_ROTATION);

	// ビュー行列
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(
		LIGHT_POSITION, LIGHT_POSITION + lightDir, SimpleMath::Vector3::UnitY);

	// プロジェクション行列
	SimpleMath::Matrix projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(LIGHT_THETA), 1.0f, LIGHT_NEAR, LIGHT_FAR);

	// シャドウバッファを作成 ロック->変換->アンロック
	D3D11_MAPPED_SUBRESOURCE resource;
	context->Map(m_shadowConstant.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	ShadowBuffer buffer = {};
	buffer.lightViewProj = XMMatrixTranspose(view * projection);
	buffer.lightPosition = LIGHT_POSITION;
	buffer.lightDirection = lightDir;
	buffer.lightAmbient = SimpleMath::Color(AMBIENT_COLOR, AMBIENT_COLOR, AMBIENT_COLOR);
	*static_cast<ShadowBuffer*>(resource.pData) = buffer;

	context->Unmap(m_shadowConstant.Get(), 0);

	// デプスラムダの作成
	ShaderLambda option = [&]() {
		context->VSSetShader(m_vsDep.Get(), nullptr, 0);
		context->PSSetShader(m_psDep.Get(), nullptr, 0); };

	// 影オブジェクトを描画する

	// カーソルの描画
	m_cursorObject->Draw(context, *states, view, projection, false, option);

	// ブロックの描画
	m_blockManager->Draw(context, *states, view, projection, false, option);

	// プレイヤーの描画
	m_player->Draw(context, *states, view, projection, false, option);

	// フラグの描画
	m_flagManager->Draw(context, *states, view, projection, false, option);

	// レンダーターゲットをデフォルトに戻す
	auto srv = m_renderTexture->GetShaderResourceView();
	rtv = DX::DeviceResources::GetInstance()->GetRenderTargetView();
	dsv = DX::DeviceResources::GetInstance()->GetDepthStencilView();
	context->ClearRenderTargetView(rtv, Colors::CornflowerBlue);
	context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &rtv, dsv);
	vp = DX::DeviceResources::GetInstance()->GetScreenViewport();
	context->RSSetViewports(1, &vp);

	// シャドウラムダの作成
	option = [&]() {
		// バッファ/リソースの設定
		ID3D11Buffer* buff[] = { m_shadowConstant.Get(), m_lightConstant.Get() };
		context->VSSetConstantBuffers(1, 1, buff);
		context->PSSetConstantBuffers(1, 2, buff);
		context->PSSetShaderResources(1, 1, &srv);

		// サンプラー/シェーダーの設定
		ID3D11SamplerState* samplers[] = { states->LinearWrap(), m_sampler.Get() };
		context->PSSetSamplers(0, 2, samplers);
		context->VSSetShader(m_vs.Get(), nullptr, 0);
		context->PSSetShader(m_ps.Get(), nullptr, 0); };


	// カメラのマトリクスを取得
	view = m_adminCamera->GetView();
	projection = m_adminCamera->GetProjection();

	// ワールドマウスの描画
	m_worldMouse->Draw(view, projection);

	// 空の描画
	m_sky->Draw(context, *states, view, projection);

	// カーソルオブジェクトの描画
	m_cursorObject->Draw(context, *states, view, projection, false, option);

	// ブロックの描画
	m_blockManager->Draw(context, *states, view, projection, false, option);

	// プレイヤーの描画
	m_player->Draw(context, *states, view, projection, false, option);

	// フラグの描画
	m_flagManager->Draw(context, *states, view, projection, false, option);

	// リソースの割り当てを解除する
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	context->PSSetShaderResources(1, 1, nullsrv);

	// 水面の描画
	m_water->Draw(view, projection);

	// 氷山の描画
	m_iceberg->Draw(context, *states, view, projection);
	m_smallberg->Draw(context, *states, view, projection);
	m_bigberg->Draw(context, *states, view, projection);

	// UIの描画
	m_ui->Draw();

	// デバッグ描画
#ifdef _DEBUG
	//auto _grid = GetSystemManager()->GetGridFloor();
	//_grid->Draw(*_states, _view, _projection, Colors::Green);
	//DebugDraw(*_states);
#endif
}

// 終了
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
	m_imageShot.reset();
	m_water.reset();
	m_ui.reset();
	m_timer.reset();
	m_iceberg.reset();
	m_smallberg.reset();
	m_bigberg.reset();
}

// 画面、デバイス依存の初期化
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
		L"Resources/Models/Flag.cmo", SimpleMath::Vector3::One * FLAG_CURSOR_RATE);

	// フラグマネージャ作成
	m_flagManager = std::make_unique<FlagManager>();

	// スクショ作成
	m_imageShot = std::make_unique<ImageShot>();

	// 水面作成
	m_water = std::make_unique<Water>();

	// UI作成
	m_ui = std::make_unique<UI_Play>(GetWindowSize(), GetFullHDSize());

	// タイマー作成
	m_timer = std::make_unique<Timer>(Timer::Mode::infinited);

	// 氷山作成
	m_iceberg   = std::make_unique<Iceberg>(SimpleMath::Vector3(0.0f, -25.0f, -50.0f), 8.0f, -10.0f);
	m_smallberg = std::make_unique<Iceberg>(SimpleMath::Vector3(0.0f, -30.0f, 25.0f), 5.0f, 0.0f);
	m_bigberg   = std::make_unique<Iceberg>(SimpleMath::Vector3(50.0f, -30.0f, 0.0f), 15.0f, -5.0f);

	// シャドウマップ関連の作成
	RECT rect = { 0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE };
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// レンダーテクスチャの作成
	{
		m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
		m_renderTexture->SetDevice(device);
		m_renderTexture->SetWindow(rect);
	}

	// デプスステンシルの作成
	{
		m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
		m_depthStencil->SetDevice(device);
		m_depthStencil->SetWindow(rect);
	}

	// デプスシェーダーの作成
	{
		// 頂点シェーダー
		std::vector<uint8_t> shader = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS_Depth.cso");
		DX::ThrowIfFailed(
			device->CreateVertexShader(
				shader.data(), shader.size(), nullptr, m_vsDep.ReleaseAndGetAddressOf()
			)
		);
		// ピクセルシェーダー
		shader = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS_Depth.cso");
		DX::ThrowIfFailed(
			device->CreatePixelShader(
				shader.data(), shader.size(), nullptr, m_psDep.ReleaseAndGetAddressOf()
			)
		);
	}
	// シャドウシェーダーの作成
	{
		// 頂点シェーダー
		std::vector<uint8_t> shader = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS.cso");
		DX::ThrowIfFailed(
			device->CreateVertexShader(
				shader.data(), shader.size(), nullptr, m_vs.ReleaseAndGetAddressOf()
			)
		);
		// ピクセルシェーダー
		shader = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS.cso");
		DX::ThrowIfFailed(
			device->CreatePixelShader(
				shader.data(), shader.size(), nullptr, m_ps.ReleaseAndGetAddressOf()
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

	// コンスタントバッファの作成
	{
		// シャドウ
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = static_cast<UINT>(sizeof(ShadowBuffer));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, nullptr, m_shadowConstant.ReleaseAndGetAddressOf())
		);
		// ライト
		desc.ByteWidth = static_cast<UINT>(sizeof(LightFovBuffer));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, nullptr, m_lightConstant.ReleaseAndGetAddressOf())
		);
	}

	// サンプラーの作成
	{
		D3D11_SAMPLER_DESC desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
		desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.ComparisonFunc = D3D11_COMPARISON_LESS;
		device->CreateSamplerState(&desc, m_sampler.ReleaseAndGetAddressOf());
	}
}

// シーン内の変数初期化関数
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

	// コリジョンの設定
	m_stageCollision->Initialize(m_blockManager.get());

	// プレイヤーの座標を返す
	m_player->SetPosition(m_blockManager->GetPlayerPosition());

	// カーソルオブジェクトにワールドマウスの座標を設定
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());

	// ライトバッファの更新
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	LightFovBuffer buff = {};
	buff.fCosTheta = cosf(XMConvertToRadians(LIGHT_THETA / 2.0f));
	context->UpdateSubresource(m_lightConstant.Get(), 0, nullptr, &buff, 0, 0);

	// 水面の画像を読み込む
	m_water->Create(L"Resources/Textures/ShaderTex/water.png");

	// コインの枚数を設定
	m_ui->SetCoinNum(static_cast<int>(m_blockManager->GetCoins().size()));

	// タイマースタート
	m_timer->Start();
}

// デバッグ描画
void PlayScene::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// 文字の描画
	string.DrawFormatString(states, { 0,0 },  Colors::DarkGreen, L"PlayScene");
	string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Timer::%.2f", timer.GetTotalSeconds());
	string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"StageNum::%.d", m_stageNumber);
	string.DrawFormatString(states, { 0,125 }, Colors::DarkGreen, L"PlayerPos::%.2f,%.2f,%.2f",
		m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	string.DrawFormatString(states, { 0,150 }, Colors::DarkGreen, L"WorldMouse::%.2f,%.2f,%.2f",
		m_worldMouse->GetPosition().x, m_worldMouse->GetPosition().y, m_worldMouse->GetPosition().z);
	string.DrawFormatString(states, { 0,175 }, Colors::DarkGreen, L"SettingPath::%d", m_player->GetFollowPath().size());
	string.DrawFormatString(states, { 0,200 }, Colors::DarkGreen, L"HaveCoinNum::%d", m_player->GetCoinNum());
	string.DrawFormatString(states, { 0,225 }, Colors::DarkGreen, L"CameraPos::%.2f,%.2f,%.2f",
		m_adminCamera->GetPosition().x, m_adminCamera->GetPosition().y, m_adminCamera->GetPosition().z);
}

// ステージのパスを取得する
const wchar_t* PlayScene::GetStagePath()
{
	// スクショ保存先パスを指定
	m_stageTexPath =
		L"Resources/Textures/Stages/Stage" + std::to_wstring(m_stageNumber) + L".dds";

	switch (m_stageNumber)
	{
	case 1:
		return L"Resources/Stages/sample1.json";
	case 2:
		return L"Resources/Stages/sample2.json";
	case 3:
		return L"Resources/Stages/sample3.json";
	case 4:
		return L"Resources/Stages/sample4.json";
	default:
		return L"Resources/Stages/sample1.json";
	}
}
