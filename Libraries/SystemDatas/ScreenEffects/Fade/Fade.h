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
public:

	// フェードの最大値の取得
	float GetMaxValue() const { return MAX_NUM; }
	// フェード終了を判定する関数
	bool GetEndFlag() const { return is_endFlag; }
	// フェードの値取得
	float GetFadeValue() const { return m_fadeValue; }
	// フェードの速度設定
	void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }
	// ルール画像の変更
	void SetRuleTexture(const wchar_t* path = L"Resources/Textures/Transitions/Rule_Rot.png") { m_filePath = path; }

	// コンストラクタ
	Fade(float speed);
	// デストラクタ
	~Fade();
	// 初期化
	void Initialize();
	// 更新
	void Update(DirectX::XMVECTORF32 color);
	// 描画
	void Draw();
	// フェードインを開始
	void SetFadeIn();
	// フェードアウトを開始
	void SetFadeOut();
	// リセット
	void Reset();

private:

	// 最大値/最小値
	const float MAX_NUM = 255.0f;
	const float MIN_NUM = 0.0f;
	const float SPEED = 1.5f;

private:

	// トランジション
	std::unique_ptr<Transition> m_transition;
	// ルール画像のパス
	const wchar_t* m_filePath;
	// フェード速度
	float m_fadeSpeed;
	// フェードの数値0-255
	float m_fadeValue;
	// フェードインを開始するフラグ
	bool is_fadeInFlag;
	// フェードアウトを開始するフラグ
	bool is_fadeOutFlag;
	// フェード終了判定フラグ
	bool is_endFlag;

};

#endif // FADE