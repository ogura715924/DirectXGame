#include "Player.h"
#include<cassert>
//#include"cassert.h"

void Player::Initialize(Model*model,uint32_t textureHandle) {
	//引数から受け取ったモデルが組み込まれているかチェック
	assert(model);
	//引数からモデルとテクスチャハンドルを受け取る
	model_ = model;
	textureHandle_ = textureHandle;

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}
void Player::Update(){
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}
void Player::Draw(ViewProjection&ViewProjection) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);
}
