#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"Input.h"
#include "PlayerBullet.h"
#include"Vector3.h"
#include<list>

///自キャラ

class Player {
public:
	//初期化
	void Initialize(Model* model_, uint32_t textureHandle);
	//更新
	void Update();
	//回転
	void Rotate();
	//攻撃
	void Attack();
	// デストラクタ
	~Player();
	//描画
	void Draw(ViewProjection& viewProjection_);
	

	

	//キーボード入力
	Input* input_ = nullptr;
	

private:
	// 弾
	PlayerBullet* bullet_ = nullptr;
	std::list<PlayerBullet*> bullets_;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};