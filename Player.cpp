#include "Player.h"
#include<cassert>
#include <imgui.h>
//#include"cassert.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// ��������󂯎�������f�����g�ݍ��܂�Ă��邩�`�F�b�N
	assert(model);
	// �������烂�f���ƃe�N�X�`���n���h�����󂯎��
	model_ = model;
	textureHandle_ = textureHandle;

	
	// X,Y,Z�����̃X�P�[�����O��ݒ�
	worldTransform_.scale_ = {5.0f, 1.0f, 1.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();

	
}
void Player::Update(){

	//�X�P�[�����O�s��̍쐬
	//�X�P�[�����O�s���錾
	Matrix4x4 matScale;//4�s4��
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1;

	//X����]�s���錾
	Matrix4x4 matRotX = {0};
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldTransform_.rotation_.x);
	matRotX.m[3][3] = 1;

	// Y����]�s���錾
	Matrix4x4 matRotY = {0};
	matRotY.m[0][0] = cosf(worldTransform_.rotation_.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sinf(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldTransform_.rotation_.y);
	matRotY.m[3][3] = 1;

	// Z����]�s���錾
	Matrix4x4 matRotZ = {0};
	matRotZ.m[0][0] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = sinf(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = -sinf(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;
//	Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	//���s�s���錾
	Matrix4x4 matTrans = {0};
	matTrans.m[0][0] = 1;
	matTrans.m[1][1] = 1;
	matTrans.m[2][2] = 1;
	matTrans.m[3][3] = 1;
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;
//	worldTransform_.matWorld_ = matScale * matRot * matTrans;

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
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.translation_.x = sqrt(move.x * move.x + move.y * move.y);
	worldTransform_.translation_.y = sqrt(move.x * move.x + move.y * move.y);
	worldTransform_.translation_.z = sqrt(move.x * move.x + move.y * move.y);

	//�s��X�V
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	//�L�����N�^�[�̍��W����ʕ\�����鏈��
	ImGui::Begin("");
	float playerpos[] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("PlayerPos",playerpos,0,1280);
	worldTransform_.translation_.x = playerpos[0];
	worldTransform_.translation_.y = playerpos[1];
	worldTransform_.translation_.z = playerpos[2];

	ImGui::End();
	

	//�ړ����E���W
	const float kMoveLimitX = 1280;
	const float kMoveLimitY = 720;

	//�͈͂𒴂��Ȃ�����
	move.x=max(move.x,-kMoveLimitX);
	move.x=min(move.x,+kMoveLimitX);
	//move.y=max(move.y -kMoveLimitY);
	move.y=min(move.y,+kMoveLimitY);

}

void Player::Draw(ViewProjection&ViewProjection) {
	//3D���f����`��
	model_->Draw(worldTransform_, ViewProjection, textureHandle_);

	
}
