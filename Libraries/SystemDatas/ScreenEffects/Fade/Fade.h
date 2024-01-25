/*
 *	@File	Fade.h
 *	@Brief	画面遷移時のフェード処理。
 *	@Date	2023-06-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FADE
#define FADE

class Transition;
class Fade
{
private:
	// トランジション
	std::unique_ptr<Transition> m_transition;

	// ルール画像のパス
	const wchar_t* m_filePath;

private:

	// フェードインを開始するフラグ
	bool is_fadeInFlag;

	// フェードアウトを開始するフラグ
	bool is_fadeOutFlag;

	// フェード速度
	float m_fadeSpeed;

	// フェード終了判定フラグ
	bool is_endFlag;

	// フェードの数値0-255
	float m_fadeValue;

private:

	// 最大値/最小値
	const float MAX_NUM = 255.0f;
	const float MIN_NUM = 0.0f;
	const float SPEED = 1.5f;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="speed">フェードの速度</param>
	/// <returns>なし</returns>
	Fade(float speed);
	~Fade();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="color">色情報</param>
	/// <returns>なし</returns>
	void Update(DirectX::XMVECTORF32 color);
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw();
	/// <summary>
	/// フェードインを開始する関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void SetFadeIn();
	/// <summary>
	/// フェードアウトを開始する関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void SetFadeOut();
	/// <summary>
	/// フェード処理を行う前に呼び出す関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Reset();

	/// <summary>
	/// フェードの最大値の取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>フェードの最大値</returns>
	const float& GetMaxValue() { return MAX_NUM; }
	/// <summary>
	/// フェード終了を判定する関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>フェード終了でTrue</returns>
	const bool& GetEndFlag() { return is_endFlag; }
	/// <summary>
	/// フェードの値取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>フェードの値</returns>
	const float& GetFadeValue() { return m_fadeValue; }
	/// <summary>
	/// フェードの速度設定
	/// </summary>
	/// <param name="speed">フェード速度</param>
	/// <returns>なし</returns>
	void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }
	/// <summary>
	/// ルール画像の変更
	/// </summary>
	/// <param name="path">画像パス</param>
	/// <returns>なし</returns>
	void SetRuleTexture(const wchar_t* path = L"Resources/Textures/Transitions/Rule_Rot.png") { m_filePath = path; }
};

#endif // FADE