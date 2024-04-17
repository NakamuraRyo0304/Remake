/*
 *	@File	RayCast.h
 *	@Brief	レイを飛ばしてスクリーン座標をワールド座標に変換する。
 *	@Date	2023-05-26
 *  @Author NakamuraRyo
 */

class RayCast
{
public:

	// ワールド変換後のマウス座標の取得
	const DirectX::SimpleMath::Vector3& GetConvertedPosition() { return m_convertPosition; }

	// 行列を設定
	void SetMatrix(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
	{
		m_view = view; m_projection = proj;
	}

	// コンストラクタ
	RayCast();
	// デストラクタ
	~RayCast();
	// 更新
	void Update();

private:

	// レイを飛ばして地面との交点を取る
	DirectX::SimpleMath::Vector3 ShotRay();
	// スクリーン座標をワールド座標に変換する
	DirectX::SimpleMath::Vector3 ConvertScreenToWorld(int mx, int my, float fz, int width, int height,
		DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	// マウスをワールド座標に変換した値を保存する変数
	DirectX::SimpleMath::Vector3 m_convertPosition;
	// 行列
	DirectX::SimpleMath::Matrix m_view, m_projection;
	// スクリーンサイズ
	DirectX::SimpleMath::Vector2 m_screenSize;

};