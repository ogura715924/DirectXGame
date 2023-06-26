#include "Enemy.h"
#include<assert.h>
#include <cassert>



// デストラクタ
Enemy::~Enemy() {

	// bullet_の解放

	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}


void Enemy::Initialize(Model* model, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	
	// 引数からモデルとテクスチャハンドルを受け取る
	model_ = model;
	velocity_ = velocity;
	 //テクスチャ読み込み
	textureHandle_ = TextureManager::Load("jousi.png");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();



	
}

void Enemy::Update() {
	// ワールドトランスフォームの更新　場所動かすときに使える
	worldTransform_.UpdateMatrix();

	// 座標を移動させる
	worldTransform_.translation_.z -= 0.1f;

	//フェーズ
	switch (phase_) {
	case Phase::Approach:
	default:
		//移動(ベクトルを加算)
		worldTransform_.translation_.x += 0.1f;
		//既定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
	case Phase::Leave:
		//移動（ベクトルを加算）
		worldTransform_.translation_.x += 0.1f;
		worldTransform_.translation_.y += 0.1f;
		break;
	}


	//弾関連
	Fire();
		for (EnemyBullet* bullet : bullets_) {
			bullet->Update();
		}
		//デスフラグの立った弾を削除
	    bullets_.remove_if([](EnemyBullet* bullet) {
		    if (bullet->IsDead()) {
			    delete bullet;
			    return true;
		    }
		    return false;
	    });

	}


void Enemy::Fire() {
	// 弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);
	//弾を生成し初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Intialize(model_, worldTransform_.translation_);

	    // 弾を登録する
	    bullets_.push_back( newBullet);

}
		

void Enemy::Draw(const ViewProjection& viewProjection_) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	   
	
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}



