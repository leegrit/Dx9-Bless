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
}float4 SoftShadowMappingPS22(PixelInputType input) : COLOR0
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
	// Shadow ????????? ?????? ?????? ???????????? shadowFactor??? 1??? 
	// ?????? ?????? ?????? ?????? factor??? 0?????? ???????????? ????????? ???????????? 
	// ?????? ????????? shadow factor??? ???????????? ???????????? ??? ?????? 
	// ?????? ?????? ?????? ????????????.
	// emissive, ambient??? ?????? ??????????????? ????????? ?????? ?????????.
	float shadowFactor = 1; // default 1
	// ?????? ????????? ????????? ????????? ????????? Bias ??? ??????
	//float bias = 0.06f;
	//float bias = 0.006f; origin
	float bias = 0.000000000000000000006f;
	/* Calculate  */
	// vertex??? light ???????????? ????????? ?????? ????????????.
	float3 projectTexcoord;

	int cascadeIndex = -1;
	float4 lightPos;
	float shadowDepth;


	for(int i = 0; i < 4; i++)
	{
		lightPos = mul(worldPos, LightViewMatrix[i]);
		lightPos = mul(lightPos, LightProjMatrix[i]);

		/* Light ???????????? Texture ????????? ?????????. */
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

float4 SoftShadowMappingPS(PixelInputType input, uniform int cascadeIndex, uniform sampler shadowDepthSampler) : COLOR0
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
	// Shadow ????????? ?????? ?????? ???????????? shadowFactor??? 1??? 
	// ?????? ?????? ?????? ?????? factor??? 0?????? ???????????? ????????? ???????????? 
	// ?????? ????????? shadow factor??? ???????????? ???????????? ??? ?????? 
	// ?????? ?????? ?????? ????????????.
	// emissive, ambient??? ?????? ??????????????? ????????? ?????? ?????????.
	float shadowFactor = 1; // default 1
	// ?????? ????????? ????????? ????????? ????????? Bias ??? ??????
	//float bias = 0.06f;
	//float bias = 0.006f; origin
	float bias = 0.0023f;
	//float bias = 0;

	/* Calculate  */
	// vertex??? light ???????????? ????????? ?????? ????????????.
	float3 projectTexcoord;

	float4 lightPos;
	float shadowDepth;

	lightPos = mul(worldPos, LightViewMatrix[cascadeIndex]);
	lightPos = mul(lightPos, LightProjMatrix[cascadeIndex]);

	projectTexcoord.x = lightPos.x / lightPos.w / 2.0f + 0.5f;
	projectTexcoord.y = -lightPos.y / lightPos.w / 2.0f + 0.5f;
	projectTexcoord.z = lightPos.z / lightPos.w / 2.0f + 0.5f;

	if((saturate(projectTexcoord.x) == projectTexcoord.x) && (saturate(projectTexcoord.y) == projectTexcoord.y) 
		&& (saturate(projectTexcoord.z) == projectTexcoord.z))
	{
		shadowDepth = tex2D(shadowDepthSampler, projectTexcoord.xy).r;
		float lightDepth = lightPos.z / lightPos.w;
		lightDepth = lightDepth - bias;
		shadowFactor = lightDepth < shadowDepth ?  1 : 0;
		if (shadowFactor == 1)
			discard;
	}
	else
		discard;

	return float4(shadowFactor, shadowFactor, shadowFactor, shadowFactor);
};


technique SoftShadowMapping_Temp
{
	pass P0
	{
		ZEnable = false;
		CULLMODE = CCW;
		VertexShader = compile vs_3_0 SoftShadowMappingVS();
		PixelShader = compile ps_3_0 SoftShadowMappingPS(0, ShadowDepthSampler0);
	}
};
technique SoftShadowMapping
{
	pass P0
	{
		ZEnable = false;
		CULLMODE = CCW;
		VertexShader = compile vs_3_0 SoftShadowMappingVS();
		PixelShader = compile ps_3_0 SoftShadowMappingPS(0, ShadowDepthSampler0);
	}
	pass P1
	{
		ZEnable = false;
		CULLMODE = CCW;
		VertexShader = compile vs_3_0 SoftShadowMappingVS();
		PixelShader = compile ps_3_0 SoftShadowMappingPS(1, ShadowDepthSampler1);
	}
	pass P2
	{
		ZEnable = false;
		CULLMODE = CCW;
		VertexShader = compile vs_3_0 SoftShadowMappingVS();
		PixelShader = compile ps_3_0 SoftShadowMappingPS(2, ShadowDepthSampler2);
	}
};