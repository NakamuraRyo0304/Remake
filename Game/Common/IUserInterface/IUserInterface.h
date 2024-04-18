/*
 *	@File	IUserInterface.h
 *	@Brief	UIクラス。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#ifndef IUSERINTERFACE
#define IUSERINTERFACE

#include "Libraries/SystemDatas/Button/Button.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class IUserInterface
{
public:

	// 画面拡大率を取得
	const DirectX::SimpleMath::Vector2& GetScreenRate() { return m_screenRate; }
	// 画面拡大率を設定
	void SetScreenRate(const DirectX::SimpleMath::Vector2& rate) { m_screenRate = rate; }

	// 画面サイズを取得
	const DirectX::SimpleMath::Vector2& GetScreenSize() { return m_screenSize; }
	// 画面サイズを設定
	void SetScreenSize(const DirectX::SimpleMath::Vector2& size) { m_screenSize = size; }

	// 最大画面サイズを取得
	const DirectX::SimpleMath::Vector2& GetMaxScreenSize() { return m_maxScreenSize; }
	// 最大画面サイズを設定
	void SetMaxScreenSize(const DirectX::SimpleMath::Vector2& size) { m_maxScreenSize = size; }

	// コンストラクタ
	IUserInterface(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// デストラクタ
	~IUserInterface() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;

private:

	// 画面サイズ
	DirectX::SimpleMath::Vector2 m_screenSize;

	// 最大画面サイズ
	DirectX::SimpleMath::Vector2 m_maxScreenSize;

	// 画面拡大率
	DirectX::SimpleMath::Vector2 m_screenRate;

};

#endif // IUSERINTERFACE