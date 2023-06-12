#include "PlayerBullet.h"
#include<assert.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("ng.png");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

}
void PlayerBullet::Update() {

	//ワールドトランスフォームの更新　場所動かすときに使える
	worldTransform_.UpdateMatrix();
}
void PlayerBullet::Draw(const ViewProjection& viewProjection_) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
};
