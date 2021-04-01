#include "StandardEngineFramework.h"
#include "Transform.h"
#include "GameObject.h"


Transform::Transform(GameObject * owner, const Vector3 & position, const Quaternion & rotation, const Vector3 & scale)
	: 
	m_pOwner(owner),
	m_position(position)
	, m_rotation(rotation)
	, m_originalPosition(position)
	, m_originalRotation(rotation)
	, m_scale(scale)
{

}

Transform::~Transform()
{
}

Transform & Transform::operator=(const Transform &t)
{
	this->m_position = t.m_position;
	this->m_rotation = t.m_rotation;
	this->m_scale = t.m_scale;
	return *this;
}

void HyEngine::Transform::SetRotationEuler(const Vector3 & euler)
{
	RotateEuler(euler);
}

void HyEngine::Transform::SetRotationEuler(const Quaternion & quaternion)
{
	RotateEuler(Quaternion::ToEulerDeg(quaternion));
}

void Transform::Translate(const Vector3 & translation)
{
	m_position = m_position + translation;
}

void Transform::Translate(float x, float y, float z)
{
	m_position = m_position + Vector3(x, y, z);
}

void Transform::Scale(const Vector3 & scale)
{
	m_scale = scale;
}

void Transform::RotateAroundPointAndAxis(const Vector3 & axis, float angle, const Vector3 & point)
{
	Vector3 R(m_position - point);
	const Quaternion rot = Quaternion::FromAxisAngle((const D3DXVECTOR3)axis, angle);
	R = rot.TransformVector(R);
	m_position = point+R; 
}


Vector3 HyEngine::Transform::Forward()
{
	D3DXVECTOR3 forwardVec;
	memcpy(&forwardVec, &GetWorldMatrix().m[2][0], sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(&forwardVec, &forwardVec);


	return forwardVec;
}

Vector3 HyEngine::Transform::Right()
{
	D3DXVECTOR3 rightVec;
	memcpy(&rightVec, &GetWorldMatrix().m[0][0], sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(&rightVec, &rightVec);


	return rightVec;
}

Vector3 HyEngine::Transform::Up()
{
	D3DXVECTOR3 upVec;
	memcpy(&upVec, &GetWorldMatrix().m[1][0], sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(&upVec, &upVec);



	return upVec;
}

D3DXMATRIX Transform::WorldTransformationMatrix() const
{
	D3DXMATRIX output;
	D3DXMatrixAffineTransformation(&output, m_scale.x(),&(const D3DXVECTOR3)Vector3::Zero, &(const D3DXQUATERNION)m_rotation, &(const D3DXVECTOR3)m_position);
	return output;
}

D3DXMATRIX Transform::WorldTransformationMatrix_NoScale() const
{
	D3DXVECTOR3 scale = Vector3::One;
	D3DXVECTOR3 rotOrigin = Vector3::Zero;
	D3DXMATRIX output;
	return *D3DXMatrixAffineTransformation(&output, scale.x, &rotOrigin, &(const D3DXQUATERNION)m_rotation, &(D3DXVECTOR3)m_position);
}

D3DXMATRIX Transform::RotationMatrix() const
{
	return m_rotation.Matrix();
}

// builds normal matrix from world matrix, ignoring translation
// and using inverse-transpose of rotation/scale matrix
//https://stackoverflow.com/questions/13654401/why-transforming-normals-with-the-transpose-of-the-inverse-of-the-modelview-matr
// this link is about normal translation using inverse and transpose
// https://paroj.github.io/gltut/Illumination/Tut09%20Normal%20Transformation.html
// TODO : 검증이 필요하다.
// 포팅함 
D3DXMATRIX Transform::NormalMatrix(const D3DXMATRIX & world)
{
	D3DXMATRIX nrm = world;
	nrm._41 = nrm._42 = nrm._43 = 0;
	nrm._44 = 1;

	float det = D3DXMatrixDeterminant(&nrm);
	D3DXMatrixInverse(&nrm, &det, &nrm);
	D3DXMatrixTranspose(&nrm, &nrm);
	return nrm;
}

D3DXMATRIX HyEngine::Transform::GetWorldMatrix()
{
	//if(m_pOwner)
	//	CalculateHierarchy(m_pOwner->GetParent());
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matPos;

	D3DXMatrixScaling(&matScale, m_scale.x(), m_scale.y(), m_scale.z());
	//D3DXQUATERNION quaternion = m_rotation;
	if (m_rotationEuler == Vector3::Zero)
		D3DXMatrixRotationQuaternion(&matRot, &m_rotation.operator D3DXQUATERNION());
	else
		D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(m_rotationEuler.y()), D3DXToRadian(m_rotationEuler.x()), D3DXToRadian(m_rotationEuler.z()));


	D3DXMatrixTranslation(&matPos, m_position.x(), m_position.y(), m_position.z());

	m_worldMatrix = matScale * matRot * matPos;

	return m_worldMatrix;
}

void HyEngine::Transform::CalculateHierarchy(GameObject * parent)
{
	if (parent == nullptr)
		return;
	CalculateHierarchy(parent->GetParent());
	m_position += parent->m_pTransform->m_position;
	m_scale += parent->m_pTransform->m_scale;
	m_rotation = m_rotation + parent->m_pTransform->m_rotation;
}

D3DXVECTOR3 HyEngine::Transform::CalcOffset(D3DXVECTOR3 offset)
{
	D3DXVECTOR3 source = m_position;
	D3DXVECTOR3 rightDir = Right();
	D3DXVECTOR3 upDir = Up();
	D3DXVECTOR3 forwardDir = Forward();
	D3DXVECTOR3 resultPos =
		source +
		rightDir * offset.x+
		upDir * offset.y+
		forwardDir * offset.z;
	return resultPos;
}

GameObject * HyEngine::Transform::GetGameObject()
{
	return m_pOwner;
}


void Transform::LookAt(Transform & target)
{
	//D3DXMATRIX lookAtMat;
	//D3DXVECTOR3 vLook = m_position - target.m_position;
	//D3DXMatrixLookAtLH
	//(
	//	&lookAtMat,
	//	&m_position.operator const D3DXVECTOR3(),
	//	&vLook,
	//	&Up().operator const D3DXVECTOR3()
	//);
	//m_position = DxMath::WorldMat2PosVec(lookAtMat);
	//m_scale = DxMath::WorldMat2ScaleVec(lookAtMat);
	//Quaternion rot(lookAtMat);
	//m_rotation = rot;
	return LookAt(target.m_position);
}

void HyEngine::Transform::LookAt(Vector3 & position)
{
	//D3DXMATRIX lookAtMat;

	//D3DXVECTOR3 vLook = m_position - position;

	//D3DXMatrixLookAtLH(&lookAtMat, &m_position.operator D3DXVECTOR3(),
	//	&position.operator D3DXVECTOR3(), &Vector3::Up);

	//Quaternion rot(lookAtMat);
	//m_rotation = rot;
	

	//Quaternion temp = Quaternion::LookAt(m_position, position);


	//SetRotationDeg(-temp.GetAngleXDeg(), temp.GetAngleYDeg(), m_rotation.GetAngleZDeg());
	//ResetRotation();
	//RotateAroundLocalYAxisDegrees(temp.GetAngleYDeg());
	//RotateAroundLocalXAxisDegrees(-temp.GetAngleXDeg());
	m_rotation = m_rotation.LookAt(m_position, position);

	/*D3DXMATRIX lookAtMat;
	D3DXVECTOR3 vLook = m_position - position;
	D3DXMatrixLookAtLH
	(
		&lookAtMat,
		&m_position.operator const D3DXVECTOR3(),
		&vLook,
		&Up().operator const D3DXVECTOR3()
	);
	m_position = DxMath::WorldMat2PosVec(lookAtMat);
	m_scale = DxMath::WorldMat2ScaleVec(lookAtMat);
	Quaternion rot(lookAtMat);
	m_rotation = rot;*/
}

void Transform::RotateEuler(const Vector3 & eulers)
{
	m_rotationEuler = eulers;
}
void HyEngine::Transform::Refresh()
{
	m_positionOld = m_position;
	m_rotationOld = m_rotation;
	m_rotationEulerOld = m_rotationEuler;
	m_scaleOld = m_scale;
}
//
//void Transform::SetParent(Transform * parent)
//{
//	m_parent = parent;
//	if (m_parent == nullptr)
//		m_root = nullptr;
//	else if (m_parent->m_parent == nullptr)
//		m_root = m_parent;
//	else
//	{
//		m_root = m_parent->m_root;
//	}
//}
//
