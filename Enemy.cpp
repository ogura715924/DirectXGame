#include "Enemy.h"
#include<assert.h>
#include <cassert>

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
	worldTransform_.translation_.z -= velocity_.z;

}

void Enemy::Draw(const ViewProjection& viewProjection_) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}