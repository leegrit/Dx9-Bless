
matrix WorldMatrix;
/* For Shadow Map */
matrix LightViewMatrix;
matrix LightProjMatrix;

/* For Skinning */
bool IsSkinnedMesh;
float4x3 Palette[57];
int MaxVtxInf;

void ShadowMapVS(
	float4 position : POSITION,
	float4 weights : BLENDWEIGHT0,
	int4 boneIndices : BLENDINDICES0,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0
)
{
	if (IsSkinnedMesh)
	{
		float4 p = float4(0.0f, 0.0f, 0.0f, 1.0f);
		float lastWeight = 0.0f;
		float inf = MaxVtxInf - 1;

		for (int i = 0; i < inf; i++)
		{
			lastWeight += weights[i];
			float4x4 mat = float4x4
				(
					float4(Palette[boneIndices[i]][0], 0),
					float4(Palette[boneIndices[i]][1], 0),
					float4(Palette[boneIndices[i]][2], 0),
					float4(Palette[boneIndices[i]][3], 1)
					);
			p += weights[i] * mul(position, mat);
		}
		lastWeight = 1.0f - lastWeight;
		float4x4 mat = float4x4
			(
				float4(Palette[boneIndices[inf]][0], 0),
				float4(Palette[boneIndices[inf]][1], 0),
				float4(Palette[boneIndices[inf]][2], 0),
				float4(Palette[boneIndices[inf]][3], 1)
				);
		p += lastWeight * mul(position, mat);

		p.w = 1;

		outPosition = mul(p, WorldMatrix);
	}
	else
	{
		outPosition = mul(position, WorldMatrix);
	}
	outPosition = mul(outPosition, LightViewMatrix);
	outPosition = mul(outPosition, LightProjMatrix);

    /* Depth */ 
	outDepthPos = outPosition;

}

/* For CascadeShadow */

void ShadowMapPS(
	float4 depthPos : TEXCOORD0,
	out float4 outLightDepth : COLOR0
)
{
	float lightDepth = (float)depthPos.z / depthPos.w;
	outLightDepth = float4(lightDepth, lightDepth, lightDepth, lightDepth);
}


technique ShadowMap
{
	pass P0
	{
		CULLMODE = NONE;
		VertexShader = compile vs_3_0 ShadowMapVS();
		PixelShader = compile ps_3_0 ShadowMapPS();
	}
};