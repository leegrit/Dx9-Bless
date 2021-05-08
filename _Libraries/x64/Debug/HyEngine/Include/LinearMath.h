#pragma once


namespace HyEngine
{

		const float XM_PI = 3.141592654f;
#define DEG2RAD (XM_PI / 180.0f)
#define RAD2DEG (180.0f / XM_PI)
#define PI		XM_PI
#define PI_DIV2 XM_PIDIV2
		struct ENGINE_DLL Vector3
		{
			static Vector3 Rand();
			static const D3DXVECTOR3 Zero;
			static const D3DXVECTOR3 Up;
			static const D3DXVECTOR3 Down;
			static const D3DXVECTOR3 Left;
			static const D3DXVECTOR3 Right;
			static const D3DXVECTOR3 Forward;
			static const D3DXVECTOR3 Back;
			static const D3DXVECTOR3 One;

			static const Vector3 Zero3;
			static const Vector3 Up3;
			static const Vector3 Down3;
			static const Vector3 Left3;
			static const Vector3 Right3;
			static const Vector3 Forward3;
			static const Vector3 Back3;

			static const Vector3 XAxis;
			static const Vector3 YAxis;
			static const Vector3 ZAxis;

			Vector3();
			Vector3(const Vector3& vec3);
			Vector3(float, float, float);
			Vector3(float);
			Vector3(const D3DXVECTOR3& vec3);

			operator D3DXVECTOR3() const;
			operator const D3DXVECTOR3() const;
			bool operator== (const Vector3&) const;
			bool operator!= (const Vector3&) const;
			inline Vector3 operator+(const Vector3& vec) const { return Vector3(this->x() + vec.x(), this->y() + vec.y(), this->z() + vec.z()); }
			inline Vector3 operator-(const Vector3& vec) const { return Vector3(this->x() - vec.x(), this->y() - vec.y(), this->z() - vec.z()); }
			inline Vector3& operator += (const Vector3& vec) { *this = *this + vec; return *this; }
			inline Vector3 operator*(float scalar) const { return Vector3(this->x() * scalar, this->y() * scalar, this->z() * scalar); }
			inline Vector3 operator/(float scalar) const { return Vector3(this->x() / scalar, this->y() / scalar, this->z() / scalar); }
			inline Vector3 operator+(float scalar) const { return Vector3(this->x() + scalar, this->y() + scalar, this->z() + scalar); }
			inline Vector3 operator-(float scalar) const { return Vector3(this->x() - scalar, this->y() - scalar, this->z() - scalar); }
			inline Vector3 operator- () const { return *this * -1; }

			inline float& Vector3::x() { return m_vector3.x; }
			inline float& Vector3::y() { return m_vector3.y; }
			inline float& Vector3::z() { return m_vector3.z; }
			inline float& Vector3::x() const { return const_cast<float&>(m_vector3.x); }
			inline float& Vector3::y() const { return const_cast<float&>(m_vector3.y); }
			inline float& Vector3::z() const { return const_cast<float&>(m_vector3.z); }

			void Normalize();
			const Vector3 Normalized() const;
			const std::string Print() const;
			Vector3 Cross(Vector3);
			float Dot(Vector3);
			Vector3 SquaredNorm();
			D3DXVECTOR3 m_vector3;
		};

		struct ENGINE_DLL Vector2
		{
			static const D3DXVECTOR2 Zero;
			static const D3DXVECTOR2 Up;
			static const D3DXVECTOR2 Down;
			static const D3DXVECTOR2 Left;
			static const D3DXVECTOR2 Right;

			static const Vector2 Zero2;
			static const Vector2 Up2;
			static const Vector2 Down2;
			static const Vector2 Left2;
			static const Vector2 Right2;

			Vector2();
			Vector2(const Vector2& vec);
			Vector2(const Vector3& vec);
			Vector2(float, float);
			Vector2(int, int);
			Vector2(unsigned, unsigned);
			Vector2(float);
			Vector2(const D3DXVECTOR3& vec);
			Vector2(const D3DXVECTOR2& vec);

			operator D3DXVECTOR3() const;
			operator D3DXVECTOR2() const;
			bool operator== (const Vector2&) const;
			inline Vector2& operator+= (const Vector2& vec) { *this = (D3DXVECTOR2)*this + (D3DXVECTOR2)vec; return *this; }

			inline float& Vector2::x() { return m_vector.x; }
			inline float& Vector2::y() { return m_vector.y; }
			inline float& Vector2::x() const { return const_cast<float&>(m_vector.x); }
			inline float& Vector2::y() const { return const_cast<float&>(m_vector.y); }

			void Normalize();
			const Vector2 Normalized() const;

			D3DXVECTOR2 m_vector;
		};

		class ENGINE_DLL Quaternion
		{
		public:
			static Quaternion Identity();
			static Quaternion FromAxisAngle(const D3DXVECTOR3& axis, const float angle);
			static Quaternion Lerp(const Quaternion& from, const Quaternion& to, float t);
			static Quaternion Slerp(const Quaternion& from, const Quaternion& to, float t);
			static Vector3 ToEulerRad(const Quaternion& quaternion);
			static Vector3 ToEulerDeg(const Quaternion& quaternion);
			static Quaternion EulerAnglesToQuaternion(float x, float y, float z);

			Quaternion(const D3DXMATRIX& matrix);
			Quaternion(const Quaternion& quaternion);
			Quaternion(float s, const D3DXVECTOR3& vec);

			operator D3DXQUATERNION() const { return D3DXQUATERNION(V.x(), V.y(), V.z(), S); }
			operator D3DXMATRIX() const { return Matrix(); }
			Quaternion  operator+(const Quaternion& q) const;
			Quaternion  operator*(const Quaternion& q) const;
			Quaternion  operator*(float c) const;
			bool		operator==(const Quaternion& q) const;
			float		Dot(const Quaternion& q) const;
			float		Len() const;
			Quaternion  Inverse() const;
			Quaternion  Conjugate() const;
			D3DXMATRIX	Matrix() const;
			Quaternion&	Normalize();
			float GetAngleXDeg() const;
			float GetAngleYDeg() const;
			float GetAngleZDeg() const;

			Vector3 TransformVector(const Vector3& vec) const;

			// https://stackoverflow.com/questions/12435671/quaternion-lookat-function
			static Quaternion CreateFromAxisAngle(Vector3 axis, float angle);
		
			// https://stackoverflow.com/questions/12435671/quaternion-lookat-function
			static Quaternion LookAt(Vector3 sourcePoint, Vector3 destPoint);

		public: // used by operator()s
			Quaternion(float s, const Vector3& v);
			Quaternion();

		public:
			Vector3 V;
			float S;
		};
	


}