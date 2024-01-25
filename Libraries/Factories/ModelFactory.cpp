/*
 *	@File	ModelFactory.cpp
 *	@Brief	モデルを作成するファクトリークラス。
 *	@Date	2023-06-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "ModelFactory.h"

//==============================================================================
// モデルの作成
//==============================================================================
std::unique_ptr<Model> ModelFactory::CreateModel(const wchar_t* filename, const wchar_t* directory)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// モデルの作成(作成時のみの使い捨て)
	std::unique_ptr<EffectFactory> _fx =
		std::make_unique<EffectFactory>(_device);

	// ディレクトリの設定
	_fx->SetDirectory(directory);

	// モデルデータの読み込み
	std::unique_ptr<Model> _model = Model::CreateFromCMO(
		_device,
		filename,
		*_fx
	);

	// 作成したモデルを返却
	return _model;
}