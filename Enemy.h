#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Vector3.h"
#include "ViewProjection.h"


// 行動フェーズ
enum class Phase {
	Approach, // 接近する
	Leave,    // 離脱する
	};

class Enemy {
public:
	// 初期化
	void Initialize(Model* model_, const Vector3& velocity);
	// 更新
	void Update();
	// 描画
	void Draw(const ViewProjection& viewProjection_);


private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;
	// フェーズ
	Phase phase_;
};

