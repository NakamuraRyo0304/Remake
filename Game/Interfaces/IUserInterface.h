/*
 *	@File	IUserInterface.h
 *	@Brief	UIクラス。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#ifndef IUSERINTERFACE
#define IUSERINTERFACE

class IUserInterface
{
public:

	// デストラクタ
	virtual ~IUserInterface() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;

};

#endif // IUSERINTERFACE