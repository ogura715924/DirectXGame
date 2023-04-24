#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"


///自キャラ

class Player {
public:
	//初期化
	void Initialize(Model* model_, uint32_t textureHandle);
	//更新
	void Update();
	//描画
	void Draw(ViewProjection& ViewProjection);

	//キーボード入力
	Input* input_ = nullptr;

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};