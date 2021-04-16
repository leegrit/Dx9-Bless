#pragma once
#include "GameObject.h"

namespace HyEngine
{

	class ENGINE_DLL Camera : public GameObject
	{
	public:
		explicit Camera(class Scene* scene, GameObject* parent, std::wstring tag);
		//explicit Camera(class Scene* scene, GameObject* parent, std::wstring tag, const Vector3& originPos, const Quaternion& originRot, const Vector3& originScale);
		virtual ~Camera();

		virtual void Initialize();
		//virtual void CameraUpdate();
		virtual void Update() override;

		static Camera* Create(Scene* scene, std::wstring tag)
		{
			Camera* camera = new Camera(scene, nullptr, tag);
			camera->Initialize();
			return camera;
		}

		void SetProjectionMatrix(float fovy, float screenAspect, float screenNear, float screenFar);
		void SetBasicProjection();
		void SetLongProjection();
		void SetViewMatrix(const D3DXVECTOR3& target);
		void SetViewMatrix(const D3DXVECTOR3 & eye, const D3DXVECTOR3 & target);
		float GetNear() const;
		float GetFar() const;
		Vector3 GetPosition() const;
		Quaternion GetRotation() const;
		Vector3 GetRotationEuler() const;
		D3DXMATRIX GetViewMatrix() const;
		D3DXMATRIX GetProjectionMatrix() const;
		D3DXMATRIX GetLongProjectionMatrix() const;
		D3DXMATRIX GetProjectionMatrix(float fovy, float screenAspect, float screenNear, float screenFar);
		D3DXMATRIX GetIdentityViewMatrix() const;
		D3DXMATRIX GetOrthoMatrix() const;

		void SetPosition(float x, float y, float z);
		void SetRotationEuler(float x, float y, float z);
		class Transform* GetTransform();
		//void Rotate();

		// source = mosue position
		void UnProjection(_Out_ D3DXVECTOR3 * origin, _Out_  D3DXVECTOR3 * direction, Vector3 source);

		void ShakeUpdate();
		void Shake(float shakeDuration, float shakeAmount = 0.7f, float decreaseFactor = 1.0f);

	private:
		void FrustumUpdate();
		bool IsInFrustum(D3DXVECTOR3 & position);
		bool IsInFrustumWithMesh(D3DXVECTOR3 & position, float radius);
	public : // Culling
		
		void ViewFrustumCulling(GameObject* obj);
		void ViewFrustumCulling(const std::vector<GameObject*>& objs);
		
		bool IsInFrustumWithOutFar(D3DXVECTOR3& position);
	protected :

	protected:
		
		float m_moveSpeed = 1; 
		float m_rotSpeed = 1; 

		float m_fovy = D3DXToRadian(60.f);
		float m_aspect = WinMaxWidth / WinMaxHeight;
		float m_defaultNear = 1.f;
		float m_defaultFar = 2000.f;
		float m_longestFar = 5000.f;
		float m_near = 1;
		float m_far = 2000.f;
		

		D3DXMATRIX m_matProj;
		D3DXMATRIX m_matLongProj;
		D3DXMATRIX m_matView;
		D3DXMATRIX m_matIdentityView;
		D3DXMATRIX m_matOrtho;

		float shakeDuration = 0;
		float shakeAmount = 0;
		float decreaseFactor = 0;
		Vector3 originPos;

		D3DXPLANE m_leftPlane;
		D3DXPLANE m_rightPlane;
		D3DXPLANE m_topPlane;
		D3DXPLANE m_bottomPlane;
		D3DXPLANE m_nearPlane;
		D3DXPLANE m_farPlane;
	};
}

