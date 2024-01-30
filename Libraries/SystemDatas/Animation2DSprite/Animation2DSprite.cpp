/*
 *	@File	Animation2DSprite.cpp
 *	@Brief	2Dスプライトのアニメーションクラス。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Animation2DSprite.h"

constexpr auto PLAYER_TEXTURE_PATH = L"Resources/Textures/Editor/Buttons/LoadButton.dds";

//==============================================================================
// コンストラクタ
//==============================================================================
Animation2DSprite::Animation2DSprite()
{
}

//==============================================================================
// デストラクタ
//==============================================================================
Animation2DSprite::~Animation2DSprite()
{
}

//==============================================================================
// リソースの作成
//==============================================================================
void Animation2DSprite::CreateResources()
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	m_batch = std::make_unique<PrimitiveVertex>(_context);
	m_states = std::make_unique<CommonStates>(_device);
	m_shaders = std::make_unique<Shaders>();

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _tex;

	// ファイル読み込み
	CreateDDSTextureFromFile(_device, PLAYER_TEXTURE_PATH, nullptr, m_srv.ReleaseAndGetAddressOf());
}

//==============================================================================
// 描画関数
//==============================================================================
void Animation2DSprite::Draw()
{

}

//==============================================================================
// Name
//==============================================================================
void Animation2DSprite::CreateBillboard(SimpleMath::Vector3 eye, SimpleMath::Vector3 target, SimpleMath::Vector3 up)
{
	m_world = SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero, eye - target, up);

	// 回転を止めて常に正面に向ける
	SimpleMath::Matrix _rot = SimpleMath::Matrix::Identity;
	_rot._11 = -1;
	_rot._33 = -1;

	m_cameraPosition = eye;
	m_cameraTarget = target;

	// ビルボードのテクスチャを回転
	m_world = _rot * m_world;
}

//==============================================================================
// コンスタントバッファの作成
//==============================================================================
void Animation2DSprite::CreateConstBuffer()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// コンスタントバッファ定義
	D3D11_BUFFER_DESC _buffer = {};

	// 中身を空にする
	ZeroMemory(&_buffer, sizeof(_buffer));

	// 読み書きのモードをデフォルトにする
	_buffer.Usage = D3D11_USAGE_DEFAULT;

	// シェーダーで使うデータ構造体のサイズを格納
	_buffer.ByteWidth = sizeof(ConstBuffer);

	// バッファーを定数バッファーとして紐づける
	_buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// CPUから書き換えをできなくする
	_buffer.CPUAccessFlags = NULL;

	// 作成したバッファを格納
	_device->CreateBuffer(&_buffer, nullptr, &m_buffer);
}

