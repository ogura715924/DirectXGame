#include "Player.h"
#include<cassert>
//#include"cassert.h"

void Player::Initialize(Model*model,uint32_t textureHandle) {
	//��������󂯎�������f�����g�ݍ��܂�Ă��邩�`�F�b�N
	assert(model);
	//�������烂�f���ƃe�N�X�`���n���h�����󂯎��
	model_ = model;
	textureHandle_ = textureHandle;

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
}
void Player::Update(){
	//�s���萔�o�b�t�@�ɓ]��
	worldTransform_.TransferMatrix();
}
void Player::Draw(ViewProjection&ViewProjection) {
	//3D���f����`��
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);
}
