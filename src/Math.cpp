#include "Math.h"

const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::NegativeUnitX(-1.0f, 0.0f);
const Vector2 Vector2::NegativeUnitY(0.0f, -1.0f);

const Vector3 Vector3::Zero(0.0f, 0.0f, 0.f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NegativeUnitX(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NegativeUnitY(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::NegativeUnitZ(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Infinity(Math::Infinity, Math::Infinity, Math::Infinity);
const Vector3 Vector3::NegativeInfinity(Math::NegativeInfinity, Math::NegativeInfinity, Math::NegativeInfinity);

static float m3Ident[3][3] = {
        {1.0f, 0.0f, 0.0f}, //
        {0.0f, 1.0f, 0.0f}, //
        {0.0f, 0.0f, 1.0f}  //
};

const Matrix3 Matrix3::Identity(m3Ident);

static float m4Ident[4][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f}, //
        {0.0f, 1.0f, 0.0f, 0.0f}, //
        {0.0f, 0.0f, 1.0f, 0.0f}, //
        {0.0f, 0.0f, 0.0f, 1.0f}  //
};

const Matrix4 Matrix4::Identity(m4Ident);

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

Vector2 Vector2::Transform(const Vector2& vec, const Matrix3& mat, float w /*= 1.0f*/)
{
    Vector2 result;
    result.x = vec.x * mat.matrix[0][0] + vec.y * mat.matrix[1][0] + w * mat.matrix[2][0];
    result.y = vec.x * mat.matrix[0][1] + vec.y * mat.matrix[1][1] + w * mat.matrix[2][1];

    return result;
}

Vector3 Vector3::Transform(const Vector3& vec, const Matrix4& mat, float w /*= 1.0f*/)
{
    Vector3 result;
    result.x = vec.x * mat.matrix[0][0] + vec.y * mat.matrix[1][0] + vec.z * mat.matrix[2][0] + w * mat.matrix[3][0];
    result.y = vec.x * mat.matrix[0][1] + vec.y * mat.matrix[1][1] + vec.z * mat.matrix[2][1] + w * mat.matrix[3][1];
    result.z = vec.x * mat.matrix[0][2] + vec.y * mat.matrix[1][2] + vec.z * mat.matrix[2][2] + w * mat.matrix[3][2];

    return result;
}

Vector3 Vector3::TransformWithPerspDiv(const Vector3& v, const Matrix4& m, float w /*= 1.0f*/)
{
    Vector3 result;
    result.x = v.x * m.matrix[0][0] + v.y * m.matrix[1][0] + v.z * m.matrix[2][0] + w * m.matrix[3][0];
    result.y = v.x * m.matrix[0][1] + v.y * m.matrix[1][1] + v.z * m.matrix[2][1] + w * m.matrix[3][1];
    result.z = v.x * m.matrix[0][2] + v.y * m.matrix[1][2] + v.z * m.matrix[2][2] + w * m.matrix[3][2];
    float transformedW = v.x * m.matrix[0][3] + v.y * m.matrix[1][3] + v.z * m.matrix[2][3] + w * m.matrix[3][3];

    if (!Math::NearZero(Math::Abs(transformedW))) {
        transformedW = 1.0f / transformedW;
        result *= transformedW;
    }

    return result;
}

Vector3 Vector3::Transform(const Vector3& v, const Quaternion& q)
{
    Vector3 qv(q.x, q.y, q.z);
    Vector3 result = v;
    result += 2.0f * Vector3::Cross(qv, Vector3::Cross(qv, v) + q.w * v);

    return result;
}

void Matrix4::Invert()
{
    float tmp[12];
    float src[16];
    float dst[16];
    float det;

    // row 1 to col 1
    src[0] = matrix[0][0];
    src[4] = matrix[0][1];
    src[8] = matrix[0][2];
    src[12] = matrix[0][3];

    // row 2 to col 2
    src[1] = matrix[1][0];
    src[5] = matrix[1][1];
    src[9] = matrix[1][2];
    src[13] = matrix[1][3];

    // row 3 to col 3
    src[2] = matrix[2][0];
    src[6] = matrix[2][1];
    src[10] = matrix[2][2];
    src[14] = matrix[2][3];

    // row 4 to col 4
    src[3] = matrix[3][0];
    src[7] = matrix[3][1];
    src[11] = matrix[3][2];
    src[15] = matrix[3][3];

    // cofactors
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];

    dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];
    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];

    dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

    // determinant
    det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

    det = 1 / det;
    for (int j = 0; j < 16; j++) {
        dst[j] *= det;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = dst[i * 4 + j];
        }
    }
}

Matrix4 Matrix4::CreateFromQuaternion(const class Quaternion& q)
{
    float m[4][4];

    m[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
    m[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
    m[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
    m[0][3] = 0.0f;

    m[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
    m[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
    m[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
    m[1][3] = 0.0f;

    m[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
    m[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
    m[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;

    return Matrix4(m);
}
