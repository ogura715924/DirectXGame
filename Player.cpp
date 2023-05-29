#include<cassert>
#include <imgui.h>
#include "Player.h"
#include"WorldTransform.h"
#include <assert.h>
#include <math.h>
#define _USE_MATH_DEFINES

Vector3 scale(1.0f, 1.0f, 1.0f);
Vector3 rot(0.0f, 0.0f, 0.0f);
Vector3 translate(0.0f, 0.0f, 0.0f);


void Player::Initialize(Model* model, uint32_t textureHandle) {
	// 引数から受け取ったモデルが組み込まれているかチェック
	assert(model);
	// 引数からモデルとテクスチャハンドルを受け取る
	model_ = model;
	textureHandle_ = textureHandle;

	
	// X,Y,Z方向のスケーリングを設定
	worldTransform_.scale_ = {5.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	Matrix4x4 worldMatrix = MakeMatrix(scale, rot, translate);
	
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
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.translation_.x = sqrt(move.x * move.x + move.y * move.y);
	worldTransform_.translation_.y = sqrt(move.x * move.x + move.y * move.y);
	worldTransform_.translation_.z = sqrt(move.x * move.x + move.y * move.y);

	//行列更新
	worldTransform_.matWorld_ = MakeMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	//キャラクターの座標を画面表示する処理
	ImGui::Begin("");
	float playerpos[] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("PlayerPos",playerpos,0,1280);
	worldTransform_.translation_.x = playerpos[0];
	worldTransform_.translation_.y = playerpos[1];
	worldTransform_.translation_.z = playerpos[2];

	ImGui::End();
	

	//移動限界座標
	const float kMoveLimitX = 1280;
	const float kMoveLimitY = 720;

	//範囲を超えない処理
	move.x=max(move.x,-kMoveLimitX);
	move.x=min(move.x,+kMoveLimitX);
	move.y = max(move.y, -kMoveLimitY);
	move.y=min(move.y,+kMoveLimitY);

}

void Player::Draw(ViewProjection&ViewProjection) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);
}
