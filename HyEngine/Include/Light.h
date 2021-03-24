#pragma once

namespace HyEngine
{
	class ENGINE_DLL Light
	{
	public :
		inline ELightType& Type() { return m_lightType; }
		inline D3DXVECTOR4& Direction() { return m_direction; }
		inline D3DXVECTOR4& Position() { return m_position; }
		inline D3DXVECTOR4& Ambient() { return m_ambient; }
		inline D3DXVECTOR4& AmbientIntensity() { return m_ambientIntensity; }
		inline D3DXVECTOR4& Diffuse() { return m_diffuse; }
		inline D3DXVECTOR4& DiffuseIntensity() { return m_diffuseIntensity; }
		inline D3DXVECTOR4& Specular() { return m_specular; }
		inline D3DXVECTOR4& SpecularIntensity() { return m_specularIntensity; }
		inline float&		SpecularPower() { return m_specularPower; }
	private :
		ELightType m_lightType;
		D3DXVECTOR4 m_direction; // using directional light
		D3DXVECTOR4 m_position; // using point light
 		D3DXVECTOR4 m_ambient;
		D3DXVECTOR4 m_ambientIntensity;
		D3DXVECTOR4 m_diffuse;
		D3DXVECTOR4 m_diffuseIntensity;
		D3DXVECTOR4 m_specular;
		D3DXVECTOR4 m_specularIntensity;
		float		m_specularPower;

	public :
		static Light * CreateDirectionalLight()
		{
			Light * light = new Light();
			light->Type() = ELightType::DIRECTIONAL;
			D3DXVECTOR4 dir = D3DXVECTOR4(-1, -1, -1, 1);
			D3DXVec4Normalize(&dir, &dir);
			light->Direction() = dir;
			light->Ambient() = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
			light->AmbientIntensity() = D3DXVECTOR4(1, 1, 1, 1);
			light->Diffuse() = D3DXVECTOR4(1, 1, 1, 1);
			light->DiffuseIntensity() = D3DXVECTOR4(1, 1, 1, 1);
			light->Specular() = D3DXVECTOR4(1, 1, 1, 1);
			light->SpecularIntensity() = D3DXVECTOR4(1, 1, 1, 1);
			light->SpecularPower() = 20;

			return light;
		}
	};
}

