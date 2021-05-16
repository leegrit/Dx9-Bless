matrix ViewMatrixInv;
matrix ProjMatrixInv;



texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
};

texture VtxNormalTex;
sampler VtxNormalSampler = sampler_state
{
	Texture = (VtxNormalTex);
};

texture EffectMaskTex;
sampler EffectMaskSampler = sampler_state
{
	Texture = (EffectMaskTex);
};

texture EffectParamTex;
sampler EffectParamSampler = sampler_state
{
	Texture = (EffectParamTex);
};


texture LightIntensityTex;
sampler LightIntensitySampler = sampler_state
{
	Texture = (LightIntensityTex);
};

float3 EyePosition;


struct PixelOutput
{
	float4 color : COLOR0; // RimLightTexture
};


PixelOutput RimLightPS(float2 texcoord : TEXCOORD0)
{
	PixelOutput output = (PixelOutput)0;

	float4 depthMap = tex2D(DepthSampler, texcoord);
	float4 vtxNormalMap = tex2D(VtxNormalSampler, texcoord);
	float4 effectMaskMap = tex2D(EffectMaskSampler, texcoord);
	float4 effectParamMap = tex2D(EffectParamSampler, texcoord);
	float4 lightIntensity = tex2D(LightIntensitySampler, texcoord);
	

	float4 worldPos;
	worldPos.x = texcoord.x * 2.f - 1.f;
	worldPos.y = texcoord.y * -2.f + 1.f;
	worldPos.z = depthMap.a;
	worldPos.w = 1;

	worldPos = mul(worldPos, ProjMatrixInv);
	worldPos = mul(worldPos, ViewMatrixInv);
	worldPos = worldPos / worldPos.w;

	float3 normal = vtxNormalMap * 2 - 1;
	normal = normalize(normal);


	float rimWidth = effectParamMap.r;
	float3 toCamPos = normalize(EyePosition - worldPos.rgb);
	float rimLightIntensity = smoothstep(1.0f - rimWidth, 1.0f, 1 - max(0, dot(normal, toCamPos)));
	float3 rimFinal = /*lightIntensity.rgb **/ rimLightIntensity * effectMaskMap.r;
	output.color = float4(rimFinal, 1);

	return output;
};



technique RimLight
{
	pass P0
	{
		ZWriteEnable = false;
		AlphaBlendEnable = false;
		VertexShader = NULL;//compile vs_3_0 MeshVS();
		PixelShader = compile ps_3_0 RimLightPS();
	}
};


