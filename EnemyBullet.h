#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"

class EnemyBullet {
public:
	
	void Intialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection&viewProjection);

	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
	// メンバ関数の追加
	bool IsDead() const { return isDead_; }

	private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	    // モデル
	    Model* model_=nullptr;
	// テクスチャハンドル
	    uint32_t textureHandle_ = 0u;
		//寿命
	    static const int32_t kLifeTime = 60 * 5;
		
};
