matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;

/* For Specular */
float3 EyePosition;

/* 나중에 따로 분리 */
/* For Light Data */
float3 Direction;
float3 Position;
float4 Ambient;
float  AmbientIntensity;
float4 Diffuse;
float  DiffuseIntensity;
float4 Specular;
float  SpecularIntensity;
float  SpecularPower;
float  Constant;
float  Linear;
float  Quadratic;

/* For CasCadeShadowMapping */
matrix LightViewMatrix[4];
matrix LightProjMatrix[4];




texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU = wrap;
    AddressV = wrap;*/
};
/* DepthMap */
// rgb = emissive
// a = depth
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;*/
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
};
/* NormalMap */
// rgb = worldNormal
// a = shadow depth
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;*/
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
};
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;*/
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
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

texture RimLightColorTex;
sampler RimLightColorSampler = sampler_state
{
	Texture = (RimLightColorTex);
};

texture SoftShadowTex;
sampler SoftShadowSampler = sampler_state
{
	Texture = (SoftShadowTex);
};

texture LightTex;
sampler LightSampler = sampler_state
{
	Texture = (LightTex);
};


texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	/*MinFilter = POINT;
	MagFilter = POINT;*/
};


struct VertexInputType
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
	
};

struct PixelInputType
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
};

PixelInputType DirectionalLightVS(VertexInputType input)
{
	PixelInputType output;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;
	
	return output;
}

void DirectionalLightPS(float2 texcoord : TEXCOORD0,
	out float4 outLightIntensity : COLOR0 ,
	out float4 outAmbientIntensity : COLOR1,
	out float4 outSpecularIntensity : COLOR2,
	out float4 outRimLight : COLOR3) 
{

	float4 depthMap = tex2D(DepthSampler, texcoord);
	//float4 albedoMap = tex2D(AlbedoSampler, input.texcoord);
	float4 normalMap = tex2D(NormalSampler, texcoord);
	float4 specularMap = tex2D(SpecularSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);
	float4 vtxNormalMap = tex2D(VtxNormalSampler, texcoord);
	float4 effectMaskMap = tex2D(EffectMaskSampler, texcoord);
	float4 effectParamMap = tex2D(EffectParamSampler, texcoord);
	float4 rimLightColorMap = tex2D(RimLightColorSampler, texcoord);

	/* Skybox */
	//if (specularMap.a <= 0.0001)
	//	return albedoMap;

	float shadowFactor  = tex2D(SoftShadowSampler, texcoord).r;

	/* Calculate world position */
	float4 worldPos;
	worldPos.x = texcoord.x * 2.f - 1.f;
	worldPos.y = texcoord.y * -2.f + 1.f;
	worldPos.z = depthMap.a;
	worldPos.w = 1;

	worldPos = mul(worldPos, ProjMatrixInv);
	worldPos = mul(worldPos, ViewMatrixInv);
	worldPos = worldPos / worldPos.w;


	float3 normal = normalMap * 2 - 1;
	normal = normalize(normal);
	float3 lightDir = normalize(-Direction);
	float3 finalColor;
	finalColor = float3(0, 0, 0);
	float lightIntensity = saturate(dot(lightDir, normal.rgb));

	/* depthMap.rgb is emissive */
	float3 emissive = depthMap.rgb;
	float3 ambient =  Ambient.rgb;
	finalColor += lightIntensity * shadowFactor * Diffuse.rgb;// + ambient + emissive;

	float3 vtxNormal = vtxNormalMap * 2 - 1;
	vtxNormal = normalize(vtxNormal);


	float rimWidth = effectParamMap.r;
	float3 toCamPos = normalize(EyePosition - worldPos.rgb);
	float rimLightIntensity = smoothstep(1.0f - rimWidth, 1.0f, 1 - max(0, dot(vtxNormal, toCamPos)));
	float3 rimFinal = /*lightIntensity.rgb **/rimLightColorMap.rgb * rimLightIntensity * effectMaskMap.r;
	
	// 림라이트 그냥 적용 잘 되는지 테스트용
	// 잘 된다.
	/* Rim Light Test */
	/*
	float rimWidth = 1;
	float3 toCamPos = normalize(EyePosition - worldPos);
	float rimLightColor = smoothstep(1.0f - rimWidth, 1.0f, 1 - max(0, dot(normal, toCamPos)));
	*/
	//float rimWidth = 0.8f;
	//float3 toCamPos = normalize(EyePosition - worldPos);
	//float rimLightColor = smoothstep(1.0f - rimWidth, 1.0f, 1 - max(0, dot(normal, toCamPos)));

	/* Calculate Specular */
	float3 specular = float3(0, 0, 0); 
	if(finalColor.x > 0)
	{
		float3 viewDirection = normalize(EyePosition.xyz - worldPos.xyz);
		float3 reflection = 2 * lightIntensity * normal - lightDir;  //reflect(lightDir, normal);
		reflection = normalize(reflection);
		float specularIntensity = saturate(dot(reflection, viewDirection));

		specular = pow(specularIntensity, SpecularPower);
		if (specularMap.a > 0)
			specular = (specular  /** specularMap.rgb*/) * shadowFactor;
		else
			specular = float4(0, 0, 0, 0);//specular * shadowFactor * specularMap.rgb;
	}
	finalColor = saturate(finalColor);

	//float3 rimFinal = finalColor.rgb * rimLightColor * 1.0f;

	
	outLightIntensity = float4(finalColor.rgb,1);
	/*if (normalMap.a == 0)
		outLightIntensity = float4(1, 1, 1, 1);*/
	outAmbientIntensity = float4(ambient.rgb, 0);
	outSpecularIntensity = float4(specular.rgb, 0);
	outRimLight = float4(rimFinal, 0);

}


technique DirectionalLight
{
	pass P0
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		BlendOp = ADD;
		SrcBlend = ONE;
		DestBlend = ONE;
		VertexShader = NULL;//compile vs_3_0 DirectionalLightVS();
		PixelShader = compile ps_3_0 DirectionalLightPS();
	}
};
