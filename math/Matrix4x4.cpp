#include "Matrix4x4.h"

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {

	Vector3 result{
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};

	return result;
}

// ì‡êœ
float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

// í∑Ç≥(ÉmÉãÉÄ)
float Length(const Vector3& v) { return sqrtf(Dot(v, v)); }


// ê≥ãKâª
Vector3 Normalize(const Vector3& v) {
	float length = Length(v);
	return {v.x / length, v.y / length, v.z / length};
}