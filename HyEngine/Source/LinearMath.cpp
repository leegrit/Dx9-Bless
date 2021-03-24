#include "StandardEngineFramework.h"
#include "LinearMath.h"


// Caution !!!
// 검증 단계를 거쳐야함 
// 아직은 임시 사용


Vector3 Vector3::Rand()
{
	Vector3 v = Vector3(MathUtils::RandF(0, 1), MathUtils::RandF(0, 1), MathUtils::RandF(0, 1));
	return v.Normalized();
}
const std::string Vector3::Print() const
{
	std::string s = "(";
	s += std::to_string(m_vector3.x) + ", " + std::to_string(m_vector3.y) + ", " + std::to_string(m_vector3.z) + ")";
	return s;
}
Vector3 HyEngine::Vector3::Cross(Vector3 vec)
{

	D3DXVec3Cross(&m_vector3, &m_vector3, &vec.operator D3DXVECTOR3());
	return m_vector3;
}
float HyEngine::Vector3::Dot(Vector3 vec)
{
	return D3DXVec3Dot(&m_vector3, &vec.operator D3DXVECTOR3());
	
}
//Vector3 HyEngine::Vector3::SquaredNorm()
//{
//	/*m_vector3 *= m_vector3;
//	std::sqrt<D3DXVECTOR3>(m_vector3);
//	m_vector3 = std::pow(m_vector3, 2);
//	D3DXQUATERNION a;
//	d3dxqu
//
//	return Vector3();*/
//}
const D3DXVECTOR3 Vector3::Zero = D3DXVECTOR3();
const D3DXVECTOR3 Vector3::Up = D3DXVECTOR3(+0.0f, +1.0f, +0.0f);
const D3DXVECTOR3 Vector3::Down = D3DXVECTOR3(+0.0f, -1.0f, +0.0f);
const D3DXVECTOR3 Vector3::Left = D3DXVECTOR3(-1.0f, +0.0f, +0.0f);
const D3DXVECTOR3 Vector3::Right = D3DXVECTOR3(+1.0f, +0.0f, +0.0f);
const D3DXVECTOR3 Vector3::Forward = D3DXVECTOR3(+0.0f, +0.0f, +1.0f);
const D3DXVECTOR3 Vector3::Back = D3DXVECTOR3(+0.0f, +0.0f, -1.0f);
const D3DXVECTOR3 Vector3::One = D3DXVECTOR3(+1.0f, +1.0f, +1.0f);

const Vector3 Vector3::Zero3 = Vector3();
const Vector3 Vector3::Up3 = Vector3(+0.0f, +1.0f, +0.0f);
const Vector3 Vector3::Down3 = Vector3(+0.0f, -1.0f, +0.0f);
const Vector3 Vector3::Left3 = Vector3(-1.0f, +0.0f, +0.0f);
const Vector3 Vector3::Right3 = Vector3(+1.0f, +0.0f, +0.0f);
const Vector3 Vector3::Forward3 = Vector3(+0.0f, +0.0f, +1.0f);
const Vector3 Vector3::Back3 = Vector3(+0.0f, +0.0f, -1.0f);

const Vector3 Vector3::XAxis = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::YAxis = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ZAxis = Vector3(0.0f, 0.0f, 1.0f);


const D3DXVECTOR2 Vector2::Zero = D3DXVECTOR2();
const D3DXVECTOR2 Vector2::Up = D3DXVECTOR2(+0.0f, +1.0f);
const D3DXVECTOR2 Vector2::Down = D3DXVECTOR2(+0.0f, -1.0f);
const D3DXVECTOR2 Vector2::Left = D3DXVECTOR2(-1.0f, +0.0f);
const D3DXVECTOR2 Vector2::Right = D3DXVECTOR2(+1.0f, +0.0f);

const Vector2 Vector2::Zero2 = Vector2();
const Vector2 Vector2::Up2 = Vector2(+0.0f, +1.0f);
const Vector2 Vector2::Down2 = Vector2(+0.0f, -1.0f);
const Vector2 Vector2::Left2 = Vector2(-1.0f, +0.0f);
const Vector2 Vector2::Right2 = Vector2(+1.0f, +0.0f);


Vector3::Vector3() : m_vector3(D3DXVECTOR3(0.0f, 0.0f, 0.0f)) {}
Vector3::Vector3(const Vector3& v_in) : m_vector3(v_in.m_vector3) {}
Vector3::Vector3(const D3DXVECTOR3& v_in) { m_vector3 = v_in; }
Vector3::Vector3(float x, float y, float z) : m_vector3(x, y, z) {}
Vector3::Vector3(float x) : m_vector3(x, x, x) {}

Vector2::Vector2() : m_vector(D3DXVECTOR2(0.0f, 0.0f)) {}
Vector2::Vector2(const Vector3& v3) : m_vector(v3.x(), v3.y()) {}
Vector2::Vector2(const Vector2& v_in) : m_vector(v_in.m_vector) {}
Vector2::Vector2(float x, float y) : m_vector(x, y) {}
Vector2::Vector2(int x, int y) : m_vector(static_cast<float>(x), static_cast<float>(y)) {}
Vector2::Vector2(unsigned x, unsigned y) : m_vector(static_cast<float>(x), static_cast<float>(y)) {}
Vector2::Vector2(float f) : m_vector(f, f) {}
Vector2::Vector2(const D3DXVECTOR2& f2) : m_vector(f2) {}
Vector2::Vector2(const D3DXVECTOR3& f3) : m_vector(f3.x, f3.y) {}


Vector3::operator D3DXVECTOR3() const { return m_vector3; }

Vector3::operator const D3DXVECTOR3() const
{
	return m_vector3;
}

bool Vector3::operator==(const Vector3 &v) const { return v.m_vector3.x == m_vector3.x && v.m_vector3.y == m_vector3.y && v.m_vector3.z == m_vector3.z; }
bool Vector3::operator!=(const Vector3 &v) const { return v.m_vector3.x != m_vector3.x || v.m_vector3.y != m_vector3.y || v.m_vector3.z != m_vector3.z; }

Vector2::operator D3DXVECTOR3() const { return D3DXVECTOR3(m_vector.x, m_vector.y, 0); }
bool Vector2::operator==(const Vector2 &v) const { return v.m_vector.x == m_vector.x && v.m_vector.y == m_vector.y; }
Vector2::operator D3DXVECTOR2() const { return m_vector; }

void Vector3::Normalize()
{
	D3DXVec3Normalize(&m_vector3, &m_vector3);
}

const Vector3 Vector3::Normalized() const
{
	D3DXVECTOR3 v = m_vector3;
	D3DXVec3Normalize(&v, &m_vector3);
	return v;
}

void Vector2::Normalize()
{
	D3DXVec2Normalize(&m_vector, &m_vector);
}

const Vector2 Vector2::Normalized() const
{
	D3DXVECTOR2 v;
	D3DXVec2Normalize(&v, &m_vector);
	return v;
}


Quaternion::Quaternion(float s, const Vector3& v)
	:
	S(s),
	V(v)
{}


Quaternion::Quaternion() : S(0), V() {}

Quaternion::Quaternion(const D3DXMATRIX& rotMatrix)
{

	//const D3DXMATRIX & m = rotMatrix;
	//S = 0.5f * sqrt(m.r[0].m128_f32[0] + m.r[1].m128_f32[1] + m.r[2].m128_f32[2] + 1);
	//V.x = (m.r[2].m128_f32[1] - m.r[1].m128_f32[2]) / (4.0f * S);
	//V.y = (m.r[0].m128_f32[2] - m.r[2].m128_f32[0]) / (4.0f * S);
	//V.z = (m.r[1].m128_f32[0] - m.r[0].m128_f32[1]) / (4.0f * S);

	// Therefore, I decided to use decompose function to get the XM quaternion, which doesn't work
	// with my system as well. I have to rotate it 180degrees on Y to get the correct rotation
	//D3DXVECTOR3 scl = D3DXVECTOR3();
	//D3DXQUATERNION quat = D3DXQUATERNION();
	//D3DXVECTOR3 trans = D3DXVECTOR3();
	//D3DXMATRIX mat = D3DXMATRIX();
	//D3DXMatrixDecompose(&scl,&quat, &trans, D3DXMatrixTranspose(&mat, &rotMatrix));
	//
	////D3DXMATRIXDecompose(&scl, &quat, &trans, rotMatrix);

	//// hack zone
	////quat.m128_f32[2] *= -1.0f;

	////*this = Quaternion(quat.m128_f32[3], quat); //*Quaternion(0.0f, XM_PI, 0.0f);
	//*this = Quaternion(quat.m128_f32[3], quat).Conjugate(); //*Quaternion(0.0f, XM_PI, 0.0f);
	//int a = 5;


	// Conversion Matrix to Quaternion Ver1
	// https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

	D3DXQUATERNION q = D3DXQUATERNION();
	float trace = rotMatrix._11 + rotMatrix._22 + rotMatrix._33;
	if (trace > 0) {// I changed M_EPSILON to 0
		float s = 0.5f / sqrtf(trace + 1.0f);
		q.w = 0.25f / s;
		q.x = (rotMatrix._32 - rotMatrix._23) * s;
		q.y = (rotMatrix._13 - rotMatrix._32) * s;
		q.z = (rotMatrix._21 - rotMatrix._12) * s;
	}
	else {
		if (rotMatrix._11 > rotMatrix._22 && rotMatrix._11 > rotMatrix._33) {
			float s = 2.0f * sqrtf(1.0f + rotMatrix._11 - rotMatrix._22 - rotMatrix._33);
			q.w = (rotMatrix._32 - rotMatrix._23) / s;
			q.x = 0.25f * s;
			q.y = (rotMatrix._12 + rotMatrix._21) / s;
			q.z = (rotMatrix._13 + rotMatrix._31) / s;
		}
		else if (rotMatrix._22 > rotMatrix._33) {
			float s = 2.0f * sqrtf(1.0f + rotMatrix._22 - rotMatrix._11 - rotMatrix._33);
			q.w = (rotMatrix._13 - rotMatrix._31) / s;
			q.x = (rotMatrix._12 + rotMatrix._21) / s;
			q.y = 0.25f * s;
			q.z = (rotMatrix._23 + rotMatrix._32) / s;
		}
		else {
			float s = 2.0f * sqrtf(1.0f + rotMatrix._33 - rotMatrix._11 - rotMatrix._22);
			q.w = (rotMatrix._21 - rotMatrix._12) / s;
			q.x = (rotMatrix._13 + rotMatrix._31) / s;
			q.y = (rotMatrix._23 + rotMatrix._32) / s;
			q.z = 0.25f * s;
		}
	}

	this->V = Vector3(q.x, q.y, q.z);
	this->S = 1;
}

Quaternion::Quaternion(const Quaternion & quaternion)
{
	this->V = quaternion.V;
	this->S = quaternion.S;
}

Quaternion::Quaternion(float s, const D3DXVECTOR3 & v)
	:
	S(s),
	V(v.x, v.y, v.z)
{}


Quaternion Quaternion::Identity()
{
	return Quaternion(1, Vector3(0.0f, 0.0f, 0.0f));
}



Quaternion Quaternion::FromAxisAngle(const D3DXVECTOR3& axis, const float angle)
{
	const float half_angle = angle / 2;
	Quaternion Q = Quaternion::Identity();
	Q.S = cosf(half_angle);
	Q.V = axis * sinf(half_angle);
	return Q;
}

Quaternion Quaternion::Lerp(const Quaternion & from, const Quaternion & to, float t)
{
	return  from * (1.0f - t) + to * t;
}

Quaternion Quaternion::Slerp(const Quaternion & from, const Quaternion & to, float t)
{
	double alpha = std::acos(from.Dot(to));
	if (alpha < 0.00001) return from;
	double sina = std::sin(alpha);
	double sinta = std::sin(t * alpha);
	Quaternion interpolated = from * static_cast<float>(std::sin(alpha - t * alpha) / sina) +
		to * static_cast<float>(sinta / sina);
	interpolated.Normalize();
	return interpolated;
}

Vector3 Quaternion::ToEulerRad(const Quaternion& Q)
{
	// source: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
	double ysqr = Q.V.y() * Q.V.y();
	double t0 = -2.0f * (ysqr + Q.V.z() * Q.V.z()) + 1.0f;
	double t1 = +2.0f * (Q.V.x() * Q.V.y() - Q.S * Q.V.z());
	double t2 = -2.0f * (Q.V.x() * Q.V.z() + Q.S * Q.V.y());
	double t3 = +2.0f * (Q.V.y() * Q.V.z() - Q.S * Q.V.x());
	double t4 = -2.0f * (Q.V.x() * Q.V.x() + ysqr) + 1.0f;

	t2 = t2 > 1.0f ? 1.0f : t2;
	t2 = t2 < -1.0f ? -1.0f : t2;

	float pitch = static_cast<float>(std::asin(t2));
	float roll = static_cast<float>(std::atan2(t3, t4));
	float yaw = static_cast<float>(std::atan2(t1, t0));
	return Vector3(roll, pitch, yaw);	// ??? (probably due to wiki convention)
}

Vector3 Quaternion::ToEulerDeg(const Quaternion& Q)
{
	Vector3 eul = Quaternion::ToEulerRad(Q);
	eul.x() *= RAD2DEG;
	eul.y() *= RAD2DEG;
	eul.z() *= RAD2DEG;
	return eul;
}

Quaternion HyEngine::Quaternion::EulerAnglesToQuaternion(float x, float y, float z)
{
	double cx = cos(x*0.5);
	double cy = cos(y*0.5);
	double cz = cos(z*0.5);
	double sx = sin(x*0.5);
	double sy = sin(y*0.5);
	double sz = sin(z*0.5);

	Quaternion q;
	q.S = (float)((cz*cx*cy) + (sz*sx*sy));
	q.V.x() = (float)((cz*sx*cy) - (sz*cx*sy));
	q.V.y() = (float)((cz*cx*sy) + (sz*sx*cy));
	q.V.z() = (float)((sz*cx*cy) - (cz*sx*sy));
	return q;
}

float HyEngine::Quaternion::GetAngleXDeg() const
{
	return Quaternion::ToEulerDeg(*this).x();
}

float HyEngine::Quaternion::GetAngleYDeg() const
{
	return Quaternion::ToEulerDeg(*this).y();
}

float HyEngine::Quaternion::GetAngleZDeg() const
{
	return Quaternion::ToEulerDeg(*this).z();
}


Quaternion Quaternion::operator+(const Quaternion & q) const
{
	Quaternion result;
	D3DXVECTOR3 V1 = D3DXVECTOR3(V.x(), V.y(), V.z());
	D3DXVECTOR3 V2 = D3DXVECTOR3(q.V.x(), q.V.y(), q.V.z());

	result.S = this->S + q.S;
	result.V = V1 + V2;
	return result;
}

Quaternion Quaternion::operator*(const Quaternion & q) const
{
	Quaternion result;
	D3DXVECTOR3 V1 = D3DXVECTOR3(V.x(), V.y(), V.z());
	D3DXVECTOR3 V2 = D3DXVECTOR3(q.V.x(), q.V.y(), q.V.z());
	D3DXVECTOR3 V = D3DXVECTOR3();
	// s1s2 - v1.v2 
	result.S = this->S * q.S - D3DXVec3Dot(&V1, &V2);
	// s1v2 + s2v1 + v1xv2
	result.V = this->S * V2 + q.S * V1 + *D3DXVec3Cross(&V, &V1, &V2);
	return result;
}

Quaternion Quaternion::operator*(float c) const
{
	Quaternion result;
	result.S = c * S;
	result.V = Vector3(V.x()*c, V.y()*c, V.z()*c);
	return result;
}


bool Quaternion::operator==(const Quaternion& q) const
{
	double epsilons[4] = { 99999.0, 99999.0, 99999.0, 99999.0 };
	epsilons[0] = static_cast<double>(q.V.x()) - static_cast<double>(this->V.x());
	epsilons[1] = static_cast<double>(q.V.y()) - static_cast<double>(this->V.y());
	epsilons[2] = static_cast<double>(q.V.z()) - static_cast<double>(this->V.z());
	epsilons[3] = static_cast<double>(q.S) - static_cast<double>(this->S);
	bool same_x = std::abs(epsilons[0]) < 0.000001;
	bool same_y = std::abs(epsilons[1]) < 0.000001;
	bool same_z = std::abs(epsilons[2]) < 0.000001;
	bool same_w = std::abs(epsilons[3]) < 0.000001;
	return same_x && same_y && same_z && same_w;
}

float Quaternion::Dot(const Quaternion & q) const
{
	D3DXVECTOR3 V1 = D3DXVECTOR3(V.x(), V.y(), V.z());
	D3DXVECTOR3 V2 = D3DXVECTOR3(q.V.x(), q.V.y(), q.V.z());
	return std::max(-1.0f, std::min(S*q.S + D3DXVec3Dot(&V1, &V2), 1.0f));
}

float Quaternion::Len() const
{
	return sqrt(S*S + V.x()*V.x() + V.y()*V.y() + V.z()*V.z());
}

Quaternion Quaternion::Inverse() const
{
	Quaternion result;
	float f = 1.0f / (S*S + V.x()*V.x() + V.y()*V.y() + V.z()*V.z());
	result.S = f * S;
	result.V = Vector3(-V.x()*f, -V.y()*f, -V.z()*f);
	return result;
}

Quaternion Quaternion::Conjugate() const
{
	Quaternion result;
	result.S = S;
	result.V = Vector3(-V.x(), -V.y(), -V.z());
	return result;
}

D3DXMATRIX Quaternion::Matrix() const
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	float y2 = V.y() * V.y();
	float z2 = V.z() * V.z();
	float x2 = V.x() * V.x();
	float xy = V.x() * V.y();
	float sz = S * V.z();
	float xz = V.x() * V.z();
	float sy = S * V.y();
	float yz = V.y() * V.z();
	float sx = S * V.x();

	// -Z X -Y
	// LHS
	D3DXVECTOR3 r0 = D3DXVECTOR3(1.0f - 2.0f * (y2 + z2), 2 * (xy - sz), 2 * (xz + sy));
	D3DXVECTOR3 r1 = D3DXVECTOR3(2 * (xy + sz), 1.0f - 2.0f * (x2 + z2), 2 * (yz - sx));
	D3DXVECTOR3 r2 = D3DXVECTOR3(2 * (xz - sy), 2 * (yz + sx), 1.0f - 2.0f * (x2 + y2));
	D3DXVECTOR3 r3 = D3DXVECTOR3(0, 0, 0);

	//D3DXVECTOR3 r0 = D3DXVECTOR3Set(2 * (xy - sz), -2.0f * (xz + sy), -(1.0f - 2.0f * (y2 + z2)), 0);
	//D3DXVECTOR3 r1 = D3DXVECTOR3Set(-(1.0f - 2.0f * (x2 + z2)), 2.0f * (yz - sx), -2.0f * (xy + sz), 0);
	//D3DXVECTOR3 r2 = D3DXVECTOR3Set(-2 * (yz + sx), -(1.0f - 2.0f * (x2 + y2)), 2.0f * (xz - sy), 0);
	//D3DXVECTOR3 r3 = D3DXVECTOR3Set(0, 0, 0, 1);

	// RHS
	//D3DXVECTOR3 r0 = D3DXVECTOR3Set(1.0f - 2.0f * (y2 + z2), 2 * (xy + sz)		  , 2 * (xz - sy)		   , 0);
	//D3DXVECTOR3 r1 = D3DXVECTOR3Set(2 * (xy - sz)			 , 1.0f - 2.0f * (x2 + z2), 2 * (yz + sx)		   , 0);
	//D3DXVECTOR3 r2 = D3DXVECTOR3Set(2 * (xz + sy)			 , 2 * (yz - sx)		  , 1.0f - 2.0f * (x2 + y2), 0);
	//D3DXVECTOR3 r3 = D3DXVECTOR3Set(0						 , 0					  , 0					   , 1);

	//m.r[0] = r0;
	//m.r[1] = r1;
	//m.r[2] = r2;
	//m.r[3] = r3;
	m._11 = r0.x;
	m._12 = r0.y;
	m._13 = r0.z;
	m._21 = r1.x;
	m._22 = r1.y;
	m._23 = r1.z;
	m._31 = r2.x;
	m._32 = r2.y;
	m._33 = r2.z;


	return *D3DXMatrixTranspose(&m, &m); 
}

Quaternion& Quaternion::Normalize()
{
	float len = Len();
	if (len > 0.00001)
	{
		S = S / len;
		V.x() = V.x() / len;
		V.y() = V.y() / len;
		V.z() = V.z() / len;
	}
	return *this;
}

Vector3 Quaternion::TransformVector(const Vector3 & v) const
{
	Quaternion pure(0.0f, v);
	Quaternion rotated = *this * pure * this->Conjugate();
	return Vector3(rotated.V);
}

// https://stackoverflow.com/questions/12435671/quaternion-lookat-function
Quaternion HyEngine::Quaternion::CreateFromAxisAngle(Vector3 axis, float angle)
{
	float halfAngle = angle * .5f;
	float s = (float)std::sin(halfAngle);
	Quaternion q;
	q.V.x() = axis.x() * s;
	q.V.y() = axis.y() * s;
	q.V.z() = axis.z() * s;
	q.S = (float)std::cos(halfAngle);
	return q;
}
static Quaternion angleAxisf(const Vector3& axis, float angle) {
	auto s = std::sinf(angle / 2);
	auto u = axis.Normalized();
	return Quaternion(std::cosf(angle / 2),D3DXVECTOR3( u.x() * s, u.y() * s, u.z() * s));
}
//static Quaternion lookAt(const Vector3& sourcePoint, const Vector3& destPoint, const Vector3& front, const Vector3& up)
//{
//	Vector3 toVector = (destPoint - sourcePoint).Normalized();
//
//	//compute rotation axis
//	Vector3 rotAxis = front.cross(toVector).normalized();
//	if (rotAxis.squaredNorm() == 0)
//		rotAxis = up;
//
//	//find the angle around rotation axis
//	float dot = VectorMath::front().dot(toVector);
//	float ang = std::acosf(dot);
//
//	//convert axis angle to quaternion
//	return Eigen::AngleAxisf(rotAxis, ang);
//}
//static Quaternion LookAt2(Vector3 sourcePoint, Vector3 destPoint)
//{
//	Vector3 forwardVector = Vector3.Normalize(destPoint - sourcePoint);
//
//	Vector3 rotAxis = Vector3.Cross(Vector3.forward, forwardVector);
//	float dot = Vector3.Dot(Vector3.forward, forwardVector);
//
//	Quaternion q;
//	q.x = rotAxis.x;
//	q.y = rotAxis.y;
//	q.z = rotAxis.z;
//	q.w = dot + 1;
//
//	return q.normalize();
//}

// https://stackoverflow.com/questions/12435671/quaternion-lookat-function
Quaternion HyEngine::Quaternion::LookAt(Vector3 sourcePoint, Vector3 destPoint)
{
	D3DXVECTOR3 normalized;
	Vector3 forwardVector;
	D3DXVec3Normalize(&normalized, &(destPoint - sourcePoint).operator D3DXVECTOR3());
	forwardVector = normalized;

	float dot =  D3DXVec3Dot(&Vector3::Forward, &forwardVector.operator D3DXVECTOR3());
    //float dot = Vector3.Dot(Vector3.forward, forwardVector);

    if (std::abs(dot - (-1.0f)) < 0.000001f)
    {
        return Quaternion(3.1415926535897932f, Vector3(Vector3::Up.x, Vector3::Up.y, Vector3::Up.z) );
    }
    if (std::abs(dot - (1.0f)) < 0.000001f)
    {
        //return Quaternion();
		return Quaternion().Identity();
    }
	
    float rotAngle = (float)std::acos(dot);
	D3DXVECTOR3 temp_rotAxis;
	D3DXVec3Cross(&temp_rotAxis, &Vector3::Forward, &forwardVector.operator D3DXVECTOR3());
	Vector3 rotAxis = temp_rotAxis;




	D3DXVECTOR3 tempNorm;
	D3DXVec3Normalize(&tempNorm, &rotAxis.operator D3DXVECTOR3());
	rotAxis = tempNorm;
    return CreateFromAxisAngle(rotAxis, rotAngle);
}

