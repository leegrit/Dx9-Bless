matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;

/* For CasCadeShadowMapping */
matrix LightViewMatrix[4];
matrix LightProjMatrix[4];




texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
};
/* DepthMap */
// rgb = emissive
// a = depth
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
};
/* NormalMap */
// rgb = worldNormal
// a = shadow depth
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
};
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
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

PixelInputType SoftShadowMappingVS(VertexInputType input)
{
	PixelInputType output;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;
	
	return output;
}

float4 SoftShadowMappingPS(PixelInputType input) : COLOR0
{
	float4 depthMap = tex2D(DepthSampler, input.texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, input.texcoord);
	float4 normalMap = tex2D(NormalSampler, input.texcoord);
	float4 specularMap = tex2D(SpecularSampler, input.texcoord);
	//float4 stashMap = tex2D(StashSampler, input.texcoord);

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
	//float bias = 0.06f;
	float bias = 0.006f;

	/* Calculate  */
	// vertex의 light 공간으로 변환된 값이 필요하다.
	float3 projectTexcoord;

	int cascadeIndex = -1;
	float4 lightPos;
	float shadowDepth;

		//lightPos = mul(worldPos, LightViewMatrix[0]);
		//lightPos = mul(lightPos, LightProjMatrix[0]);

		///* Light 기준으로 Texture 좌표를 구한다. */
		//projectTexcoord.x = lightPos.x / lightPos.w / 2.0f + 0.5f;
		//projectTexcoord.y = -lightPos.y / lightPos.w / 2.0f + 0.5f;
		//projectTexcoord.z = lightPos.z / lightPos.w / 2.0f + 0.5f;

		//if ((saturate(projectTexcoord.x) == projectTexcoord.x) && (saturate(projectTexcoord.y) == projectTexcoord.y)
		//	&& (saturate(projectTexcoord.z) == projectTexcoord.z))
		//{
		//	shadowDepth = tex2D(ShadowDepthSampler0, projectTexcoord.xy).a;
		//	float lightDepth = lightPos.z / lightPos.w;
		//	lightDepth = lightDepth - bias;
		//	if (lightDepth < shadowDepth)
		//	{
		//		shadowFactor = 1;
		//	}
		//	else
		//	{
		//		shadowFactor = 0;
		//	}
		//}
		//else
		//	shadowFactor = 1;

	for(int i = 0; i < 4; i++)
	{
		lightPos = mul(worldPos, LightViewMatrix[i]);
		lightPos = mul(lightPos, LightProjMatrix[i]);

		/* Light 기준으로 Texture 좌표를 구한다. */
		projectTexcoord.x = lightPos.x / lightPos.w / 2.0f + 0.5f;
		projectTexcoord.y = -lightPos.y / lightPos.w / 2.0f + 0.5f;
		projectTexcoord.z = lightPos.z / lightPos.w / 2.0f + 0.5f;

		if((saturate(projectTexcoord.x) == projectTexcoord.x) && (saturate(projectTexcoord.y) == projectTexcoord.y) 
		&& (saturate(projectTexcoord.z) == projectTexcoord.z))
		{	
			cascadeIndex = i;
			if (cascadeIndex == 0)
			{
				shadowDepth = tex2D(ShadowDepthSampler0, projectTexcoord.xy).a;
				float lightDepth = lightPos.z / lightPos.w;
				lightDepth = lightDepth - bias;

				if (lightDepth < shadowDepth)
				{
					shadowFactor = 1;
				}
				else
				{
					shadowFactor = 0;
				}
				break;
			}
			if (cascadeIndex == 1)
			{
				shadowDepth = tex2D(ShadowDepthSampler1, projectTexcoord.xy).a;
				float lightDepth = lightPos.z / lightPos.w;
				lightDepth = lightDepth - bias;

				if (lightDepth < shadowDepth)
				{
					shadowFactor = 1;
				}
				else
				{
					shadowFactor = 0;
				}
				break;
			}
			if (cascadeIndex == 2)
			{
				shadowDepth = tex2D(ShadowDepthSampler2, projectTexcoord.xy).a;

				float lightDepth = lightPos.z / lightPos.w;
				lightDepth = lightDepth - bias;

				if (lightDepth < shadowDepth)
				{
					shadowFactor = 1;
				}
				else
				{
					shadowFactor = 0;
				}
				break;
			}
			if (cascadeIndex == 3)
			{
				shadowDepth = tex2D(ShadowDepthSampler3, projectTexcoord.xy).a;

				float lightDepth = lightPos.z / lightPos.w;
				lightDepth = lightDepth - bias;

				if (lightDepth < shadowDepth)
				{
					shadowFactor = 1;
				}
				else
				{
					shadowFactor = 0;
				}
				break;
			}
			

		}
	}
	


	return float4(shadowFactor, shadowFactor, shadowFactor, shadowFactor);
	};


technique SoftShadowMapping
{
	pass P0
	{
		ZEnable = false;
		CULLMODE = CCW;
		VertexShader = compile vs_3_0 SoftShadowMappingVS();
		PixelShader = compile ps_3_0 SoftShadowMappingPS();
	}
};
