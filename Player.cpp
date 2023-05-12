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

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}
void Player::Update(){
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向でベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// 押した方向でベクトルを変更(上下)
	if (input_ -> PushKey(DIK_UP)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y += kCharacterSpeed;
	}

	//座標移動(ベクトルの加算)
	worldTransform_.translation_ += move;

	worldTransform_.translation_ = sqrt(move.x * move.x + move.y * move.y);



}

void Player::Draw(ViewProjection&ViewProjection) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);

	
}
