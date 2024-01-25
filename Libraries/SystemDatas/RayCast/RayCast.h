/*
 *	@File	RayCast.h
 *	@Brief	レイを飛ばしてスクリーン座標をワールド座標に変換する。
 *	@Date	2023-05-26
 *  @Author NakamuraRyo
 */

class RayCast
{
private:
	// マウスをワールド座標に変換した値を保存する変数
	DirectX::SimpleMath::Vector3 m_convertPosition;

	// 行列
	DirectX::SimpleMath::Matrix m_view, m_projection;

	// スクリーンサイズ
	DirectX::SimpleMath::Vector2 m_screenSize;

public:
	RayCast();
	~RayCast();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

private:

	/// <summary>
	/// レイを飛ばして地面との交点を取る
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>当たった地面との交点</returns>
	DirectX::SimpleMath::Vector3 ShotRay();

	/// <summary>
	/// スクリーン座標をワールド座標に変換する
	/// </summary>
	/// <param name="mx">マウスX</param>
	/// <param name="my">マウスY</param>
	/// <param name="fz">任意の値</param>
	/// <param name="width">画面横幅</param>
	/// <param name="height">画面縦幅</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <returns>変換後の座標</returns>
	DirectX::SimpleMath::Vector3 ConvertScreenToWorld(int mx, int my, float fz, int width, int height,
		DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

public:

	/// <summary>
	/// ワールド変換後のマウス座標の取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>ワールド座標になったマウス座標</returns>
	const DirectX::SimpleMath::Vector3& GetConvertedPosition() { return m_convertPosition; }

	/// <summary>
	/// 行列を設定
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <returns>なし</returns>
	void SetMatrix(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
	{ m_view = view; m_projection = proj; }
};