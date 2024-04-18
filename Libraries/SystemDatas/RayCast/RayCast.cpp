/*
 *	@File	RayCast.cpp
 *	@Brief	レイを飛ばしてスクリーン座標をワールド座標に変換する。
 *	@Date	2023-05-26
 *  @Author NakamuraRyo
 */

 // 使用関数群の参考文献
 //-------------------------------------------------------------------------------------//
 //  まるぺけ
 //  その４８　スクリーン座標でワールド空間の地面を指す
 //  http://marupeke296.com/DXG_No48_PointGroundInScreen.html
 //  ⑦ 公開、スクリーン座標点と地面の交点算出関数より
 //-------------------------------------------------------------------------------------//

#include "pch.h"
#include "RayCast.h"

// コンストラクタ
RayCast::RayCast()
	:
	m_screenSize(),			// スクリーンのサイズ
	m_convertPosition()		// ワールド座標に変換した座標
{
	auto size = DX::DeviceResources::GetInstance()->GetOutputSize();
	m_screenSize = { static_cast<float>(size.right),static_cast<float>(size.bottom) };
}

// デストラクタ
RayCast::~RayCast()
{

}

// 更新
void RayCast::Update()
{
	// レイを飛ばして交点を求める
	m_convertPosition = ShotRay();
}

// レイを飛ばして地面との交点を出す
SimpleMath::Vector3 RayCast::ShotRay()
{
	// マウス座標を取得
	auto ms = Mouse::Get().GetState();

	// 最近、最遠、レイを定義
	SimpleMath::Vector3 nearPos;
	SimpleMath::Vector3 farPos;
	SimpleMath::Vector3 ray;

	// 最近距離をスクリーンからワールドに変換
	nearPos = ConvertScreenToWorld(ms.x, ms.y, 0.0f,
		static_cast<int>(m_screenSize.x), static_cast<int>(m_screenSize.y),
		m_view, m_projection);

	// 最遠距離をスクリーンからワールドに変換
	farPos = ConvertScreenToWorld(ms.x, ms.y, 1.0f,
		static_cast<int>(m_screenSize.x), static_cast<int>(m_screenSize.y),
		m_view, m_projection);

	// レイの方向を求める
	ray = farPos - nearPos;
	ray.Normalize();

	// Y座標打消しの初期化
	SimpleMath::Vector3 output = SimpleMath::Vector3::Zero;

	// 床との交差が起きている場合は交点、起きていない場合は遠くの壁との交点を出力
	if (ray.y <= 0)
	{
		// 床との交点を求める
		SimpleMath::Vector3 rayDot = XMVector3Dot(ray, SimpleMath::Vector3(0, 1, 0));
		SimpleMath::Vector3 nearDot = XMVector3Dot(-nearPos, SimpleMath::Vector3(0, 1, 0));
		output = nearPos + (nearDot / rayDot) * ray;

		// Yで交点XZを見つけて、Y要素を消す
		output.y = 0;
	}
	else
	{
		// 当たっていなければ最遠距離（実質的な無限）を出力
		output = farPos;
	}

	return output;
}

// 座標変換　スクリーン座標　→　ワールド座標
SimpleMath::Vector3 RayCast::ConvertScreenToWorld(int mx, int my, float fz,
	int width, int height, SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	// 各行列の逆行列を算出
	XMMATRIX reverseView, reverseProj, vp, reverseVp = XMMATRIX::XMMATRIX();

	// 逆行列に変換
	reverseView = XMMatrixInverse(nullptr, view);
	reverseProj = XMMatrixInverse(nullptr, proj);

	// ビューポートを初期化
	vp = XMMatrixIdentity();

	XMFLOAT4X4 matrix = XMFLOAT4X4::XMFLOAT4X4();

	// スケールとオフセットを変換
	matrix._11 =   width / 2.0f;
	matrix._22 = -height / 2.0f;
	matrix._41 =   width / 2.0f;
	matrix._42 =  height / 2.0f;

	// ビューポートに行列変換
	vp += XMLoadFloat4x4(&matrix);

	// ビューポートの逆行列を作成
	reverseVp = XMMatrixInverse(nullptr,vp);

	// 逆変換
	XMMATRIX reverseMatrix = reverseVp * reverseProj * reverseView;

	XMVECTOR output = XMVector3TransformCoord(
		SimpleMath::Vector3(static_cast<float>(mx), static_cast<float>(my), fz), reverseMatrix);

	return output;
}
