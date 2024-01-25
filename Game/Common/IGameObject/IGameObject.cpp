/*
 *	@File	IGameObject.cpp
 *	@Brief	ゲームオブジェクト。
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/Factories/ModelFactory.h"
#include "IGameObject.h"

//==============================================================================
// コンストラクタ
//==============================================================================
IGameObject::IGameObject(const wchar_t* path, const wchar_t* dpath)
	: m_world{}						// ワールド行列
	, m_parentMatrix{}				// 親ワールド行列
	, m_position{}					// 座標
	, m_initialPosition{}			// 初期座標
	, m_scale{}						// スケール
	, m_rotate{}					// 回転
	, m_filePath{ path }			// モデルパス
	, m_directoryPath{ dpath }		// ディレクトリパス
	, m_id{ ID::Default }			// オブジェクトID
	, m_name{ L"未設定" }			// オブジェクトの名前
	, m_weight{}					// オブジェクトの重さ
{
	m_position = SimpleMath::Vector3::Zero;
	m_initialPosition = SimpleMath::Vector3::Zero;
	m_world = SimpleMath::Matrix::Identity;
	m_parentMatrix = SimpleMath::Matrix::Identity;
	m_scale = SimpleMath::Vector3::One;
	m_rotate = SimpleMath::Vector3::Zero;
	m_id = ID::Default;
	m_name = L"未設定";
	m_weight = NON_WEIGHT;
}

//==============================================================================
// ワールドマトリクスを作成
//==============================================================================
void IGameObject::CreateWorldMatrix()
{
	// スケールを変更
	SimpleMath::Matrix _scale =
		SimpleMath::Matrix::CreateScale(GetScale());
	// 回転を変更
	SimpleMath::Matrix _rotate =
		SimpleMath::Matrix::CreateFromYawPitchRoll(GetRotate());
	// 座標を変更
	SimpleMath::Matrix _trans =
		SimpleMath::Matrix::CreateTranslation(GetPosition());

	// 変更したデータを反映
	m_world = _scale * _rotate * _trans;
}

//==============================================================================
// モデルを作成する
//==============================================================================
void IGameObject::CreateModel()
{
	m_model = ModelFactory::CreateModel(m_filePath, m_directoryPath);
}

//==============================================================================
// モデルを破棄する
//==============================================================================
void IGameObject::ReleaseModel()
{
	m_model.reset();
	m_VS.Reset();
	m_PS.Reset();
	m_GS.Reset();
}

//==============================================================================
// 頂点シェーダーを作成する
//==============================================================================
void IGameObject::CreateVSShader(const wchar_t* vsPath)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// パスを読み込む
	std::vector<uint8_t> _vs = DX::ReadData(vsPath);

	// シェーダーを作成
	DX::ThrowIfFailed(
		_device->CreateVertexShader(_vs.data(), _vs.size(), nullptr,m_VS.ReleaseAndGetAddressOf())
	);
}

//==============================================================================
// ピクセルシェーダーを作成する
//==============================================================================
void IGameObject::CreatePSShader(const wchar_t* psPath)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// パスを読み込む
	std::vector<uint8_t> _ps = DX::ReadData(psPath);

	// シェーダーを作成
	DX::ThrowIfFailed(
		_device->CreatePixelShader(_ps.data(), _ps.size(), nullptr, m_PS.ReleaseAndGetAddressOf())
	);
}

//==============================================================================
// ジオメトリシェーダーを作成する
//==============================================================================
void IGameObject::CreateGSShader(const wchar_t* gsPath)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// パスを読み込む
	std::vector<uint8_t> _gs = DX::ReadData(gsPath);

	// シェーダーを作成
	DX::ThrowIfFailed(
		_device->CreateGeometryShader(_gs.data(), _gs.size(), nullptr, m_GS.ReleaseAndGetAddressOf())
	);
}
