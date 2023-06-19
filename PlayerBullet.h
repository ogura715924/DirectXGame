#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"



class PlayerBullet {
public:

	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection_);
	bool isDead() const { return isDead_; }

	private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//ですタイマー
	int32_t deathTimer_ = kLifeTime;
	//ですフラグ
	bool isDead_ = false;
};

