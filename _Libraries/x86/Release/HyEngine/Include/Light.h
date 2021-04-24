#pragma once

namespace HyEngine
{
	class ENGINE_DLL Light : public Object
	{
	public :
		Light();
		~Light() = default;
	public :
		inline ELightType& Type() { return m_lightType; }
		inline D3DXVECTOR3& Direction() { return m_direction; }
		inline D3DXVECTOR3& Position() { return m_position; }
		inline D3DXCOLOR& Ambient() { return m_ambient; }
		inline float& AmbientIntensity() { return m_ambientIntensity; }
		inline D3DXCOLOR& Diffuse() { return m_diffuse; }
		inline float& DiffuseIntensity() { return m_diffuseIntensity; }
		inline D3DXCOLOR& Specular() { return m_specular; }
		inline float& SpecularIntensity() { return m_specularIntensity; }
		inline float&		SpecularPower() { return m_specularPower; }
		inline float&		Range() { return m_range; }
		inline float&		Cone() { return m_cone; }
		inline float&		Constant() { return m_constant; }
		inline float&		Linear() { return m_linear; }
		inline float&		Quadratic() { return m_quadratic; }
		inline bool&		IsCulled() { return m_bCulled; }
	private :
		ELightType m_lightType;
		D3DXVECTOR3 m_direction; // using directional light
		D3DXVECTOR3 m_position; // using point light
		D3DXCOLOR m_ambient;
		float m_ambientIntensity;
		D3DXCOLOR m_diffuse;
		float m_diffuseIntensity;
		D3DXCOLOR m_specular;
		float m_specularIntensity;
		float		m_specularPower;
		float		m_range;
		float	    m_cone;
		/* For Attenuation */
		float		m_constant;
		float		m_linear;
		float		m_quadratic;

		/* Culling */
		bool m_bCulled;

	public :
		static Light * CreateDirectionalLight()
		{
			Light * light = new Light();
			light->Type() = ELightType::DIRECTIONAL;
			D3DXVECTOR3 dir = D3DXVECTOR3(-1, -1, -1);
			D3DXVec3Normalize(&dir, &dir);
			light->Direction() = dir;
			light->Ambient() = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			light->AmbientIntensity() = D3DXCOLOR(1, 1, 1, 1);
			light->Diffuse() = D3DXCOLOR(1, 1, 1, 1);
			light->DiffuseIntensity() = D3DXCOLOR(1, 1, 1, 1);
			light->Specular() = D3DXCOLOR(1, 1, 1, 1);
			light->SpecularIntensity() = D3DXCOLOR(1, 1, 1, 1);
			light->SpecularPower() = 20;

			return light;
		}
	};
}

