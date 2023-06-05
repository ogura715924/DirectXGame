#include "WorldTransform.h"
#include <cmath>

// 行列の掛け算

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resultMultiply;
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			resultMultiply.m[row][column] =
			    m1.m[row][0] * m2.m[0][column] + m1.m[row][1] * m2.m[1][column] +
			    m1.m[row][2] * m2.m[2][column] + m1.m[row][3] * m2.m[3][column];
		}
	}
	return resultMultiply;
}

/// <summary>
/// アフィン変換行列作成
/// 各種引数はworldTransformのメンバ変数を割り当てる
/// </summary>
/// <param name="scale">ローカルスケール</param>
/// <param name="rot">ローカル回転量</param>
/// <param name="translate">ローカル座標</param>
/// <returns>ワールド行列</returns>
Matrix4x4 MakeMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
	Matrix4x4 result = {0};

	Matrix4x4 matScale = {0};
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
	matScale.m[3][3] = 1;

	// 1.X軸回転行列
	Matrix4x4 matRotX = {0};
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(rot.x);
	matRotX.m[2][1] = -sinf(rot.x);
	matRotX.m[1][2] = sinf(rot.x);
	matRotX.m[2][2] = cosf(rot.x);
	matRotX.m[3][3] = 1;

	// 2.Y軸回転行列
	Matrix4x4 matRotY = {0};
	matRotY.m[0][0] = cosf(rot.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sinf(rot.y);
	matRotY.m[2][0] = sinf(rot.y);
	matRotY.m[2][2] = cosf(rot.y);
	matRotY.m[3][3] = 1;

	// 3.Z軸回転行列
	Matrix4x4 matRotZ{0};

	matRotZ.m[0][0] = cosf(rot.z);
	matRotZ.m[1][0] = sinf(rot.z);
	matRotZ.m[0][1] = -sinf(rot.z);
	matRotZ.m[1][1] = cosf(rot.z);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	Matrix4x4 matRot = Multiply(Multiply(matRotZ,matRotX),matRotY);

	// 平行移動行列を宣言
	Matrix4x4 matTrans = {0};
	matTrans.m[0][0] = 1;
	matTrans.m[1][1] = 1;
	matTrans.m[2][2] = 1;
	matTrans.m[3][3] = 1;
	matTrans.m[3][0] = translate.x;
	matTrans.m[3][1] = translate.y;
	matTrans.m[3][2] = translate.z;

	// 戻り値　スケール*回転*平行移動;
	return Multiply(Multiply(matScale, matRot),matTrans);
}
