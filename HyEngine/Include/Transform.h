#pragma once

namespace HyEngine
{
	
	class ENGINE_DLL Transform/* : public Component*/
	{
	public:
		//----------------------------------------------------------------------------------------------------------------
		// CONSTRUCTOR / DESTRUCTOR
		//----------------------------------------------------------------------------------------------------------------
		Transform
		(
			class GameObject* owner,
			const Vector3& position = Vector3(0.0f, 0.0f, 0.0f),
			const Quaternion& rotation = Quaternion::Identity(),
			const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f)
		);
		~Transform();
		Transform& operator=(const Transform&);

		//----------------------------------------------------------------------------------------------------------------
		// GETTERS & SETTERS
		//----------------------------------------------------------------------------------------------------------------
		// 검증됨
		inline void SetXRotationDeg(float xDeg) { m_rotation = Quaternion::FromAxisAngle(Vector3::Right, xDeg * DEG2RAD); }
		inline void SetYRotationDeg(float yDeg) { m_rotation = Quaternion::FromAxisAngle(Vector3::Up, yDeg * DEG2RAD); }
		inline void SetZRotationDeg(float zDeg) { m_rotation = Quaternion::FromAxisAngle(Vector3::Forward, zDeg * DEG2RAD); }
	
		inline void SetRotationDeg(float xDeg, float yDeg, float zDeg)
		{
			m_rotation = Quaternion::FromAxisAngle(Vector3::Right, (-xDeg) * DEG2RAD);
			RotateAroundGlobalYAxisDegrees(yDeg);
			RotateAroundGlobalZAxisDegrees(zDeg);
		}
		
		inline void SetScale(float x, float y, float z) { m_scale = Vector3(x, y, z); }
		inline void SetScale(const Vector3& scale) { m_scale = scale; }
		inline void SetUniformScale(float scale) { m_scale = Vector3(scale, scale, scale); }
		inline void SetPosition(float x, float y, float z) { m_position = Vector3(x, y, z); }
		inline void SetPosition(const Vector3& position) { m_position = position; }
		void SetRotationEuler(const Vector3& euler);
		void SetRotationEuler(const Quaternion& quaternion);
		//----------------------------------------------------------------------------------------------------------------
		// TRANSFORMATIONS
		//----------------------------------------------------------------------------------------------------------------
		void Translate(const Vector3& translation);
		void Translate(float x, float y, float z);
		void Scale(const Vector3& scale);


		void RotateAroundPointAndAxis(const Vector3& axis, float angle, const Vector3& point);
		inline void RotateAroundAxisRadians(const Vector3& axis, float angle) { RotateInWorldSpace(Quaternion::FromAxisAngle((const D3DXVECTOR3)axis, angle)); }
		inline void RotateAroundAxisDegrees(const Vector3& axis, float angle) { RotateInWorldSpace(Quaternion::FromAxisAngle((const D3DXVECTOR3)axis, angle * DEG2RAD)); }


		inline void RotateAroundLocalXAxisDegrees(float angle) { RotateInLocalSpace(Quaternion::FromAxisAngle((const D3DXVECTOR3)Vector3::XAxis, std::forward<float>(angle * DEG2RAD))); }
		inline void RotateAroundLocalYAxisDegrees(float angle) { RotateInLocalSpace(Quaternion::FromAxisAngle((const D3DXVECTOR3)Vector3::YAxis, std::forward<float>(angle * DEG2RAD))); }
		inline void RotateAroundLocalZAxisDegrees(float angle) { RotateInLocalSpace(Quaternion::FromAxisAngle((const D3DXVECTOR3)Vector3::ZAxis, std::forward<float>(angle * DEG2RAD))); }
		inline void RotateAroundGlobalXAxisDegrees(float angle) { RotateAroundAxisDegrees(Vector3::XAxis, std::forward<float>(angle)); }
		inline void RotateAroundGlobalYAxisDegrees(float angle) { RotateAroundAxisDegrees(Vector3::YAxis, std::forward<float>(angle)); }
		inline void RotateAroundGlobalZAxisDegrees(float angle) { RotateAroundAxisDegrees(Vector3::ZAxis, std::forward<float>(angle)); }

		inline void RotateInWorldSpace(const Quaternion& quaternion) { m_rotation = quaternion * m_rotation; }
		inline void RotateInLocalSpace(const Quaternion& quaternion) { m_rotation = m_rotation * quaternion; }

		Vector3 Forward();
		Vector3 Right();
		Vector3 Up();


		inline void ResetPosition() { m_position = Vector3(0, 0, 0); }
		inline void ResetRotation() { m_rotation = Quaternion::Identity(); }
		inline void ResetScale() { m_scale = Vector3(1, 1, 1); }
		inline void Reset() { ResetScale(); ResetRotation(); ResetPosition(); }

		D3DXMATRIX WorldTransformationMatrix() const;
		D3DXMATRIX WorldTransformationMatrix_NoScale() const;
		D3DXMATRIX RotationMatrix() const;

		static D3DXMATRIX NormalMatrix(const D3DXMATRIX& world);

		D3DXMATRIX GetWorldMatrix();

		void CalculateHierarchy(GameObject* parent);

		D3DXVECTOR3 CalcOffset(D3DXVECTOR3 offset);

		GameObject* GetGameObject();

		inline bool IsUseQuaternion() { return m_rotationEuler == Vector3::Zero; }

		// -----------------------------------------------------------
		// PUBLIC METHODS
		// ---------------------------------------------------------------
		
		void LookAt(Transform& target);
		void LookAt(Vector3& position);

		void LookAtEuler(Transform& target);
		void LookAtEuler(D3DXVECTOR3& position);


		void RotateEuler(const Vector3& eulers);



		//----------------------------------------------------------------------------------------------------------------
		// DATA
		//----------------------------------------------------------------------------------------------------------------
		Vector3			 m_position;
		Quaternion		 m_rotation = Quaternion::Identity();
		// 주의  오일러 값을 건들게 되면 쿼터니언 값은 무시됩니다.
		Vector3			 m_rotationEuler = Vector3::Zero;
		Vector3		     m_scale;
		const Vector3    m_originalPosition;
		const Quaternion m_originalRotation;

		D3DXMATRIX m_worldMatrix;

		private:
			class GameObject* m_pOwner;
	public:

	public:

	};

}