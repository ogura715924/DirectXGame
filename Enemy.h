#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Vector3.h"
#include "ViewProjection.h"
#include"EnemyBullet.h"
#include<list>


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
	//攻撃
	void Fire();
	//デストラクタ
	~Enemy();

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
	// 弾
	EnemyBullet* bullet_ = nullptr;
	std::list<EnemyBullet*> bullets_;
};

//自機クラスの前方宣言
class Player {

	//自キャラ
	Player* player_ = nullptr;

};
