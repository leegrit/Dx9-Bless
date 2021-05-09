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
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
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
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
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
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
};

/* For Cascade ShadowMapping */
texture ShadowDepthTex0;
sampler ShadowDepthSampler0 = sampler_state
{
	Texture = (ShadowDepthTex0);
};
texture ShadowDepthTex1;
sampler ShadowDepthSampler1 = sampler_state
{
	Texture = (ShadowDepthTex1);
};
texture ShadowDepthTex2;
sampler ShadowDepthSampler2 = sampler_state
{
	Texture = (ShadowDepthTex2);
};
texture ShadowDepthTex3;
sampler ShadowDepthSampler3 = sampler_state
{
	Texture = (ShadowDepthTex3);
};

texture SoftShadowTex;
sampler SoftShadowSampler = sampler_state
{
	Texture = (SoftShadowTex);
};



texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
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

float4 DirectionalLightPS(PixelInputType input) : COLOR0
{
	/*테스트*/
	//-----------------------------------------------
	//float4 softShadowMap = tex2D(SoftShadowSampler, input.texcoord);
	//return softShadowMap;

	//-----------------------------------------------
	float4 depthMap = tex2D(DepthSampler, input.texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, input.texcoord);
	float4 normalMap = tex2D(NormalSampler, input.texcoord);
	float4 specularMap = tex2D(SpecularSampler, input.texcoord);
	float4 stashMap = tex2D(StashSampler, input.texcoord);

	/* Skybox */
	//if (specularMap.a <= 0.0001)
	//	return albedoMap;

	float shadowFactor  = tex2D(SoftShadowSampler, input.texcoord).a;

	/* Calculate world position */
	float4 worldPos;
	worldPos.x = input.texcoord.x * 2.f - 1.f;
	worldPos.y = input.texcoord.y * -2.f + 1.f;
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
	float3 ambient = albedoMap.rgb * Ambient.rgb;
	finalColor += lightIntensity * shadowFactor * albedoMap.rgb * Diffuse.rgb + ambient + emissive;

	

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
			specular = (specular + (specular * specularMap.rgb)) * shadowFactor;
		else
			specular = float4(0, 0, 0, 0);//specular * shadowFactor * specularMap.rgb;
	}
	finalColor = saturate(finalColor + specular.rgb);

	return float4(finalColor.rgb, 1);
	// depth rgb is emissive color
	//return float4(finalColor.rgb + stashMap.rgb, 1) ;//+ float4(depthMap.rgb, 1);

}


technique DirectionalLight
{
	pass P0
	{
		ZEnable = false;
		/*AlphaBlendEnable = true;
		SrcBlend = SRCCOLOR;
		DestBlend = DestColor;*/
		VertexShader = compile vs_3_0 DirectionalLightVS();
		PixelShader = compile ps_3_0 DirectionalLightPS();
	}
};
