#pragma once
#include "VectorData.h"
#include "ColorData.h"

namespace HyEngine
{
#pragma pack(push, 1)
	struct LightData
	{
		LightData();

		int lightType;
		VectorData direction;
		VectorData position;
		ColorData ambient;
		float ambientIntensity;
		ColorData diffuse;
		float diffuseIntensity;
		ColorData specular;
		float specularIntensity;
		float specularPower;
		float range;
		float cone;
		/* For Attenuation */
		float constant;
		float linear;
		float quadratic;
	};
#pragma pack(pop)
}

