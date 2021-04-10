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

/* For Shadow */
matrix LightViewMatrix;
matrix LightProjMatrix;
float3 LightPosition;




texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
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
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
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
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};
texture ShadowDepthTex;
sampler ShadowDepthSampler = sampler_state
{
	Texture = (ShadowDepthTex);
};

texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
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
	/* 여기부터 테스트 반드시 나중에 지울것 */
	//----------------------------------------------------------
	//float4 lightDepth = tex2D(ShadowDepthSampler, input.texcoord);
	//lightDepth.a = 1;
	//return lightDepth;




	//------------------------------------------------------------

	float4 depthMap = tex2D(DepthSampler, input.texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, input.texcoord);
	float4 normalMap = tex2D(NormalSampler, input.texcoord);
	float4 specularMap = tex2D(SpecularSampler, input.texcoord);
	float4 stashMap = tex2D(StashSampler, input.texcoord);

	/* Calculate world position */
	float4 worldPos;
	worldPos.x = input.texcoord.x * 2.f - 1.f;
	worldPos.y = input.texcoord.y * -2.f + 1.f;
	worldPos.z = depthMap.a;
	worldPos.w = 1;

	worldPos = mul(worldPos, ProjMatrixInv);
	worldPos = mul(worldPos, ViewMatrixInv);
	worldPos = worldPos / worldPos.w;

	/* Calculate Shadow */
	// Shadow 연산을 통해 빛을 받는곳은 shadowFactor를 1로 
	// 빛을 받지 않는 곳은 factor를 0으로 설정하여 이후에 계산되는 
	// 광원 연산에 shadow factor를 곱해주어 그림자가 진 곳은 
	// 빛을 받지 않게 설정한다.
	// emissive, ambient는 덧셈 연산이기에 영향을 받지 않는다.
	float shadowFactor = 1; // default 1
	// 부동 소수점 정밀도 문제를 해결할 Bias 값 설정
	float bias = 0.001f;

	/* Calculate  */
	// vertex의 light 공간으로 변환된 값이 필요하다.
	float2 projectTexcoord;

	float4 lightPos = mul(worldPos, LightViewMatrix);
	lightPos = mul(lightPos, LightProjMatrix);

	/* Light 기준으로 Texture 좌표를 구한다. */
	projectTexcoord.x = lightPos.x / lightPos.w / 2.0f + 0.5f;
	projectTexcoord.y = -lightPos.y / lightPos.w / 2.0f + 0.5f;


	if((saturate(projectTexcoord.x) == projectTexcoord.x) && (saturate(projectTexcoord.y) == projectTexcoord.y))
	{
		/* Light 기준으로 투영된 텍스처 좌표에서 Light기준 Depth값을 샘플링한다. */
		// GBuffer에서 NormalMap의 alpha값에 shadow depth값을 저장한다.
		float shadowDepth = tex2D(ShadowDepthSampler, projectTexcoord.xy).r;

		// 빛의 깊이를 계산한다.
		float lightDepth = lightPos.z / lightPos.w;
		// LightDepth에서 bias를 뺀다.
		lightDepth = lightDepth - bias;

		// Shadow Map값의 깊이와 빛의 깊이를 비교해서 조명처리할지 그림자처리할지 결정한다.
		// shadowFactor가 0이라면 조명 연산에 shadowFactor가 곱해져 조명연산이 무시된다.
		if(lightDepth < shadowDepth)
		{
			shadowFactor = 1;
		}
		else
		{
			shadowFactor = 0;
		}
	}

	float3 normal = normalMap * 2 - 1;
	normal = normalize(normal);
	float3 lightDir = normalize(-Direction);
	float3 finalColor;
	finalColor = float3(0, 0, 0);
	float lightIntensity = saturate(dot(lightDir, normal.rgb));

	/* depthMap.rgb is emissive */
	float3 emissive = depthMap.rgb;
	finalColor += lightIntensity * shadowFactor * albedoMap.rgb * Diffuse.rgb + emissive;

	

	/* Calculate Specular */
	float3 specular = float3(0, 0, 0); 
	if(finalColor.x > 0)
	{
		float3 viewDirection = normalize(EyePosition.xyz - worldPos.xyz);
		float3 reflection = 2 * lightIntensity * normal - lightDir;  //reflect(lightDir, normal);
		reflection = normalize(reflection);
		float specularIntensity = saturate(dot(reflection, viewDirection));

		specular = pow(specularIntensity, SpecularPower);
		specular = specular * shadowFactor * specularMap.rgb;
	}
	finalColor = saturate(finalColor + specular.rgb);

	// depth rgb is emissive color
	return float4(finalColor.rgb + stashMap.rgb, 1) ;//+ float4(depthMap.rgb, 1);

}


technique DirectionalLight
{
	pass P0
	{
		ZEnable = false;
		VertexShader = compile vs_3_0 DirectionalLightVS();
		PixelShader = compile ps_3_0 DirectionalLightPS();
	}
};
