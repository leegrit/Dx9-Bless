#include "StandardEngineFramework.h"
#include "DxHelper.h"
#include "VertexTypes.h"

using namespace HyEngine;

void DxHelper::CalculateTangentBinormal(const BumpModelVertex * vertex1, const BumpModelVertex * vertex2, const BumpModelVertex * vertex3, _Out_ D3DXVECTOR3 * tangent, _Out_ D3DXVECTOR3 * binormal)
{
	float vector1[3], vector2[3];
	float tuVector[2], tvVector[2];
	float den;
	float length;


	/* Calculate the two vectors for this face */
	vector1[0] = vertex2->x - vertex1->x;
	vector1[1] = vertex2->y - vertex1->y;
	vector1[2] = vertex2->z - vertex1->z;

	vector2[0] = vertex3->x - vertex1->x;
	vector2[1] = vertex3->y - vertex1->y;
	vector2[2] = vertex3->z - vertex1->z;

	/* Calculate the tu and tv texture space vectors */
	tuVector[0] = vertex2->u - vertex1->u;
	tvVector[0] = vertex2->v - vertex1->v;

	tuVector[1] = vertex3->u - vertex1->u;
	tvVector[1] = vertex3->v - vertex1->v;

	/* Calculate the denominator of the tangent / binormal equation */
	den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

	/* Calculate the cross products and multiply by the coefficient to get the tangent and binormal */
	tangent->x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
	tangent->y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
	tangent->z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

	binormal->x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
	binormal->y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
	binormal->z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

	/* Calculate the length of this normal. */
	length = sqrt((tangent->x * tangent->x) + (tangent->y * tangent->y) + (tangent->z * tangent->z));

	/* Normalize the normal and then store it */
	tangent->x = tangent->x / length;
	tangent->y = tangent->y / length;
	tangent->z = tangent->z / length;
}

void DxHelper::CalculateNormal(const D3DXVECTOR3 * tangent, const D3DXVECTOR3 * binormal, D3DXVECTOR3 * normal)
{
	float length;


	/* Calculate the cross product of the tangent and binormal which will give the normal vector.*/
	normal->x = (tangent->y * binormal->z) - (tangent->z * binormal->y);
	normal->y = (tangent->z * binormal->x) - (tangent->x * binormal->z);
	normal->z = (tangent->x * binormal->y) - (tangent->y * binormal->x);

	/* Calculate the length of the normal.*/
	length = sqrt((normal->x * normal->x) + (normal->y * normal->y) + (normal->z * normal->z));

	/* Normalize the normal.*/
	normal->x = normal->x / length;
	normal->y = normal->y / length;
	normal->z = normal->z / length;
}

// void DxHelper::CalculateNormal(const D3DXVECTOR3 * tangent, const D3DXVECTOR3 * binormal, _Out_ D3DXVECTOR3* normal)
// {
// 	float length;
// 
// 
// 	/* Calculate the cross product of the tangent and binormal which will give the normal vector.*/
// 	normal->x = (tangent->y * binormal->z) - (tangent->z * binormal->y);
// 	normal->y = (tangent->z * binormal->x) - (tangent->x * binormal->z);
// 	normal->z = (tangent->x * binormal->y) - (tangent->y * binormal->x);
// 
// 	/* Calculate the length of the normal.*/
// 	length = sqrt((normal->x * normal->x) + (normal->y * normal->y) + (normal->z * normal->z));
// 
// 	/* Normalize the normal.*/
// 	normal->x = normal->x / length;
// 	normal->y = normal->y / length;
// 	normal->z = normal->z / length;
// }
