#pragma once


namespace HyEngine
{
	struct Particle
	{
		D3DXVECTOR3 position;
		D3DCOLOR color;
		static const DWORD FVF;
	};

	struct Attribute
	{
		Attribute()
		{
			lifeTime = 0.0f;
			age = 0.0f;
			isAlive = true;
			cameraDistance = 0;
		}

		D3DXVECTOR3 position;
		D3DXVECTOR3 velocity;
		D3DXVECTOR3 acceleration;
		float cameraDistance;
		float lifeTime; // how long the particle lives for before dying
		float age; // current age of the particle
		D3DXCOLOR color; // current color of the particle
		D3DXCOLOR colorFade; // how the color fades with respect to time
		bool isAlive;
	};
}