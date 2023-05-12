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

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
}
void Player::Update(){
	//�s���萔�o�b�t�@�ɓ]��
	worldTransform_.TransferMatrix();

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};
	//�L�����N�^�[�̈ړ��̑���
	const float kCharacterSpeed = 0.2f;

	// �����������Ńx�N�g����ύX(���E)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// �����������Ńx�N�g����ύX(�㉺)
	if (input_ -> PushKey(DIK_UP)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y += kCharacterSpeed;
	}

	//���W�ړ�(�x�N�g���̉��Z)
	worldTransform_.translation_ += move;

	worldTransform_.translation_ = sqrt(move.x * move.x + move.y * move.y);



}

void Player::Draw(ViewProjection&ViewProjection) {
	//3D���f����`��
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);

	
}
