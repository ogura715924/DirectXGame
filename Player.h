﻿#pragma once
#include"Model.h"
#include"WorldTransform.h"


///自キャラ

class Player {
public:
	//初期化
	void Initialize(Model* model_, uint32_t textureHandle);
	//更新
	void Update();
	//描画
	void Draw(ViewProjection& ViewProjection);

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};