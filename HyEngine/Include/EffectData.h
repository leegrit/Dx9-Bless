#pragma once
#include "VectorData.h"
namespace HyEngine
{
#pragma pack(push, 1)
	struct EffectData
	{
		/* EffectType */
		// 0 : MeshEffect
		// 1 : TextureEffect
		int effectType;

		/* Start */
		VectorData startPos;
		VectorData startRot;
		VectorData startScale;

		/* End */
		VectorData endPos;
		VectorData endRot;
		VectorData endScale;

		/* Fade in out */
		bool fadeIn;
		bool fadeOut;

		/* Time */
		float lifeTime;
		float loopTime;

		/* Repeat */
		bool isRepeat;

		/* Billboard */
		bool isBillboard;

		/* Texture */
		char diffusePath[256];
		char alphaMaskPath[256];

		/* For TextureEffect */
		bool uvAnimation;
		VectorData uvDirection;
		float uvMoveSpeed;

		/* For MeshEffect */
		char meshPath[256];

		/* For SpriteEffect */
		char spritePath[256];
	};
#pragma pack(pop)
}

