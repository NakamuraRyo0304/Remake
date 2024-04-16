/*
 *	@File	Player.cpp
 *	@Brief	プレイヤー。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "Player.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float Player::MAX_SPEED = 0.78f;		// 最高速度
const float Player::RANGE = 0.6f;			// 最高速で走る半径
const float Player::ARRIVE_RADIUS = 0.1f;	// 到着みなし半径
const float Player::GIVEUP_TIME = 120.0f;	// 移動諦めタイムリミット
const float Player::DEATH_LINE = -5.0f;		// 死亡ライン
const float Player::DEATH_ROTATE = 30.0f;	// 死亡時の回転
const float Player::ROTATE_SPEED = 0.5f;	// 旋回速度
const float Player::SCALE = 0.5f;			// モデルのスケール
const float Player::GRAVITY = -0.05f;		// 重力

//==============================================================================
// コンストラクタ
//==============================================================================
Player::Player()
	: IGameObject(L"Resources/Models/pBody.cmo", L"Resources/Models")
	, m_velocity{}			                // 移動量
	, m_coinNum{ 0 }		                // 取得済みコイン枚数
	, m_giveUpTime{}						// 諦めタイム
	, is_fall{ true }		                // 落下フラグ
	, is_death{ false }		                // 死亡フラグ
	, is_coinHit{ false }		            // コイン衝突フラグ
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * SCALE);
	SetInitialScale(GetScale());

	// パーツの作成
	m_head = std::make_unique<Head>();
}

//==============================================================================
// デストラクタ
//==============================================================================
Player::~Player()
{
	m_goalPoints.clear();
	m_head.reset();
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Player::Update()
{
	// 目的地が存在しているかつ生存中の場合、目的地を追跡する
	if (not m_goalPoints.empty() && not is_death)
	{
		m_giveUpTime--;

		// ゴール座標の高さをプレイヤーと同じ高さにする
		m_goalPoints[0].y = GetPosition().y;

		// 目標位置の方向を計算する
		SimpleMath::Vector3 _dir = UserUtility::GetDirectionVector(GetPosition(), m_goalPoints[0]);
		_dir.Normalize();

		// 目的地までの距離を計算
		auto _distanceToGoal = (m_goalPoints[0] - GetPosition()).Length();

		// 速度の設定(ゴール周辺領域内なら最高速度で走る)
		float _speed = 0.0f;
		_speed = _distanceToGoal > RANGE ? MAX_SPEED : MAX_SPEED * (_distanceToGoal / RANGE);

		// 移動速度を調整
		SimpleMath::Vector3 _velocity = _dir * _speed;
		SimpleMath::Vector3 _newPosition = UserUtility::Lerp(GetPosition(), GetPosition() + _velocity);
		SetPosition(_newPosition);

		// 進行方向に合わせて回転
		float _angle = std::atan2(-_dir.x, -_dir.z);
		SimpleMath::Vector3 _rotation(0.0f, _angle, 0.0f);
		SetRotate(UserUtility::Lerp(GetRotate(), _rotation, ROTATE_SPEED));

		// 現在地からゴールまでの距離
		float _hereToGoalDistance = SimpleMath::Vector3::Distance(GetPosition(), m_goalPoints[0]);

		// 到着したら or 時間がかかりすぎたら消す
		if (_hereToGoalDistance < ARRIVE_RADIUS || m_giveUpTime < 0.0f)
		{
			UserUtility::RemoveVec(m_goalPoints, m_goalPoints[0]);
			m_giveUpTime = GIVEUP_TIME;
		}

		// 歩行ステートに変更
		m_head->SetStatus(MoveStates::Walking);
	}
	else
	{
		m_giveUpTime = GIVEUP_TIME;

		// アイドルステートに変更
		m_head->SetStatus(MoveStates::Idling);
	}

	// 落下フラグがONの場合、重力をかける
	if (is_fall)
	{
		SetPosition(GetPosition() + SimpleMath::Vector3::UnitY * GRAVITY);
	}

	// マトリクスを計算
	CreateWorldMatrix();

	// 死亡判定
	if (GetPosition().y < DEATH_LINE)
	{
		is_death = true;
	}
	if (GetPosition().y < DEATH_LINE / 2)
	{
		float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());

		// 回転しながら落ちていく
		SetRotate(GetRotate() + SimpleMath::Vector3::UnitY * XMConvertToRadians(_timer * DEATH_ROTATE));
	}

	// パーツの更新
	m_head->Update();

	// マトリクスを作成
	m_head->SetParentMatrix(GetWorldMatrix());
}

//==============================================================================
// 描画処理
//==============================================================================
void Player::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(SCALE);
	GetModel()->Draw(context, states, _scale * GetWorldMatrix(), view, proj, wireframe, option);

	// これ以降、子パーツの描画を行う
	m_head->Draw(context, states, view, proj, wireframe, option);
}

//==============================================================================
// 追跡パスを追加する
//==============================================================================
void Player::AddFollowPath(const SimpleMath::Vector3& path, const int& max)
{
	// 最大数を越えたら追加しない
	if (m_goalPoints.size() >= max) return;

	m_goalPoints.push_back(path);
}
