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
const int Player::MAX_PATH_NUM = 3;			// 最大パス数
const float Player::MAX_SPEED = 1.0f;		// 最高速度
const float Player::MS_RADIUS = 0.5f;		// 最高速で走る半径
const float Player::ARRIVE_RADIUS = 0.1f;	// 到着みなし半径

//==============================================================================
// コンストラクタ
//==============================================================================
Player::Player()
	: IGameObject(L"Resources/Models/Body.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
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
	// 配列が空じゃなかったら動かす
	if (not m_goalPoints.empty())
	{
		// 目標位置の方向を計算する
		SimpleMath::Vector3 _dir = UserUtility::GetDirectionVector(GetPosition(), m_goalPoints[0]);
		_dir.Normalize();

		// 目的地までの距離を計算
		auto _distanceToGoal = (m_goalPoints[0] - GetPosition()).Length();

		float _speed = 0.0f;
		if (_distanceToGoal > MS_RADIUS)
		{
			_speed = MAX_SPEED;
		}
		else
		{
			_speed = MAX_SPEED * (_distanceToGoal / MS_RADIUS);
		}

		// 移動速度を調整
		SimpleMath::Vector3 _velocity = _dir * _speed;
		SimpleMath::Vector3 _newPosition = UserUtility::Lerp(GetPosition(), GetPosition() + _velocity, 0.1f);
		SetPosition(_newPosition);

		// 進行方向に合わせて回転
		float _angle = std::atan2(-_dir.x, -_dir.z);
		SimpleMath::Vector3 _rotation(0.0f, _angle, 0.0f);
		SetRotate(UserUtility::Lerp(GetRotate(), _rotation, 0.1f));

		// 到着したら先頭を消す
		if ((m_goalPoints[0] - GetPosition()).Length() < ARRIVE_RADIUS)
		{
			UserUtility::RemoveVec(m_goalPoints, m_goalPoints[0]);
		}
	}

	// マトリクスを計算
	CreateWorldMatrix();

	// パーツの更新
	m_head->Update();

	// マトリクスを作成
	m_head->SetParentMatrix(GetWorldMatrix());
}

//==============================================================================
// 描画処理
//==============================================================================
void Player::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(0.5f);
	GetModel()->Draw(_context, states, _scale * GetWorldMatrix(), view, proj, false, no_use_here);

	// パーツの描画
	m_head->Draw(states, view, proj, no_use_here);
}

//==============================================================================
// 追跡パスを追加する
//==============================================================================
void Player::PushBackFollowPath(SimpleMath::Vector3 path)
{
	// 最大数を越えたら追加しない
	if (m_goalPoints.size() >= MAX_PATH_NUM) return;

	m_goalPoints.push_back(path);
}
