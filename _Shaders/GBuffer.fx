float Far;
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

bool HasNormalMap;
bool HasSpecularMap;
bool HasEmissiveMap;

/* For Shadow Map */
matrix LightViewMatrix;
matrix LightProjMatrix;

texture SkyboxTex;
samplerCUBE SkyboxSampler = sampler_state
{
	Texture = (SkyboxTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = None;
	AddressU = Mirror;
	AddressV = Mirror;
};

texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
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
/* Specular */
// rgb = specularMap
// a = specularMask
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
texture EmissiveTex;
sampler EmissiveSampler = sampler_state
{
	Texture = (EmissiveTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};
texture SpecularMaskTex;
sampler SpecularMaskSampler = sampler_state
{
	Texture = (SpecularMaskTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;
};


void GBufferVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD0,
	float3 tangent : TANGENT0,
	float3 binormal : BINORMAL0,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0,
	out float3 outNormal : NORMAL,
	out float2 outTexcoord : TEXCOORD1,
	out float3x3 outTangentWorldMat : TEXCOORD2
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

    /* Depth */ 
	outDepthPos = outPosition;

    /* Texcoord */ 
	outTexcoord = texcoord;

    /* Normal */
	outNormal = normalize(mul(float4(normal, 0.f), WorldMatrix));

	/* TangentWorldMat */
	outTangentWorldMat[0] = mul(float4(tangent, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[1] = mul(float4(binormal, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[2] = mul(float4(normal, 0.0f), WorldMatrix).xyz;
}

void GBufferPS(
	float4 depthPosition : TEXCOORD0,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD1,
	float3x3 tangentWorldMat : TEXCOORD2,
	out float4 outDepth : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outNormal : COLOR2,
	out float4 outSpecular : COLOR3
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 emissive = tex2D(EmissiveSampler, texcoord);
	float4 specular = tex2D(SpecularSampler, texcoord);
	float4 specularMask =tex2D(SpecularMaskSampler, texcoord);


	/* Depth */
	float depth =  (float)depthPosition.z / depthPosition.w;  


	outDepth = float4(emissive.r, emissive.g, emissive.b, depth);

    /* Albedo */
    outAlbedo = albedo;

	/* Specular */
	outSpecular = specular;
	outSpecular.a = specularMask.b;
	
	/* Normal */
	outNormal = float4(normal * 0.5f + 0.5f, 1);

	if(HasNormalMap == true)
	{
		/* BumpMap Sampling */
		float4 bumpMap = tex2D(NormalSampler, texcoord);
		
		/* convert -1 ~ 1*/
		bumpMap = (bumpMap * 2.0f) - 1.0f;

		float3 tangent = normalize(tangentWorldMat[0]);
		float3 binormal = normalize(tangentWorldMat[1]);


		/* Calculate bumpNormal */
		float3 bumpNormal = (bumpMap.x * tangent) + (bumpMap.y * binormal) + (bumpMap.z * normal);
		bumpNormal = normalize(bumpNormal);

		outNormal = float4(bumpNormal * 0.5f + 0.5f, 1);
	
	}
}
void GBufferSkyboxVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float3 texcoord : TEXCOORD0,
	float3 tangent : TANGENT0,
	float3 binormal : BINORMAL0,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0,
	out float3 outNormal : NORMAL,
	out float3 outTexcoord : TEXCOORD1,
	out float3x3 outTangentWorldMat : TEXCOORD2
)
{
	/* Position */
	outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	/* Depth */
	outDepthPos = outPosition;

	/* Texcoord */
	outTexcoord = texcoord;

	/* Normal */
	outNormal = normalize(mul(float4(normal, 0.f), WorldMatrix));

	/* TangentWorldMat */
	outTangentWorldMat[0] = mul(float4(tangent, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[1] = mul(float4(binormal, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[2] = mul(float4(normal, 0.0f), WorldMatrix).xyz;
}
void GBufferSkyboxPS(
	float4 depthPosition : TEXCOORD0,
	float3 normal : NORMAL,
	float3 texcoord : TEXCOORD1,
	float3x3 tangentWorldMat : TEXCOORD2,
	out float4 outDepth : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outNormal : COLOR2,
	out float4 outSpecular : COLOR3
)
{
	float4 albedo = texCUBE(SkyboxSampler, texcoord);

	outDepth = float4(0, 0, 0, 0);
	outAlbedo = albedo;
	outNormal = float4(0, 0, 0, 0);
	outSpecular = float4(0, 0, 0, 0);

}

void GBufferWithShadowVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD0,
	float3 tangent : TANGENT0,
	float3 binormal : BINORMAL0,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0,
	out float4 outLightDepthPos : TEXCOORD1,
	out float3 outNormal : NORMAL,
	out float2 outTexcoord : TEXCOORD2,
	out float3x3 outTangentWorldMat : TEXCOORD3
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

    /* Depth */ 
	outDepthPos = outPosition;

	/* Shadow Depth */
	outLightDepthPos = mul(position, WorldMatrix);
	outLightDepthPos = mul(outLightDepthPos, LightViewMatrix);
	outLightDepthPos = mul(outLightDepthPos, LightProjMatrix);

    /* Texcoord */ 
	outTexcoord = texcoord;

    /* Normal */
	outNormal = normalize(mul(float4(normal, 0.f), WorldMatrix));

	/* TangentWorldMat */
	outTangentWorldMat[0] = mul(float4(tangent, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[1] = mul(float4(binormal, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[2] = mul(float4(normal, 0.0f), WorldMatrix).xyz;
}

void GBufferWithShadowPS(
	float4 depthPosition : TEXCOORD0,
	float4 lightDepthPos : TEXCOORD1,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD2,
	float3x3 tangentWorldMat : TEXCOORD3,
	out float4 outDepth : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outNormal : COLOR2,
	out float4 outSpecular : COLOR3
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 emissive = tex2D(EmissiveSampler, texcoord);
	float4 specular = tex2D(SpecularSampler, texcoord);



	/* Depth */
	float depth =  (float)depthPosition.z / depthPosition.w;  
	outDepth = float4(emissive.r, emissive.g, emissive.b, depth);

	/* LightDepth */
	float lightDepth = (float)lightDepthPos.z / lightDepthPos.w;
	outNormal.a = lightDepth;

    /* Albedo */
    outAlbedo = albedo;

	/* Specular */
	outSpecular = specular;
	
	/* Normal */
	outNormal.rgb = float3(normal * 0.5f + 0.5f).rgb;

	if(HasNormalMap == true)
	{
		/* BumpMap Sampling */
		float4 bumpMap = tex2D(NormalSampler, texcoord);
		
		/* convert -1 ~ 1*/
		bumpMap = (bumpMap * 2.0f) - 1.0f;

		float3 tangent = normalize(tangentWorldMat[0]);
		float3 binormal = normalize(tangentWorldMat[1]);


		/* Calculate bumpNormal */
		float3 bumpNormal = (bumpMap.x * tangent) + (bumpMap.y * binormal) + (bumpMap.z * normal);
		bumpNormal = normalize(bumpNormal);

		outNormal.rgb = float3(bumpNormal * 0.5f + 0.5f).rgb;
	
	}
};

technique GBuffer
{
	pass P0
	{
		VertexShader = compile vs_3_0 GBufferVS();
		PixelShader = compile ps_3_0 GBufferPS();
	}
};

technique GBuffer_Skybox
{
	pass P0
	{
		ZWRITEENABLE = false;
		CULLMODE = CW;
		VertexShader = compile vs_3_0 GBufferSkyboxVS();
		PixelShader = compile ps_3_0 GBufferSkyboxPS();
	}
};


technique GBufferWithShadow
{
	pass P0
	{
		VertexShader = compile vs_3_0 GBufferWithShadowVS();
		PixelShader = compile ps_3_0 GBufferWithShadowPS();
	}
};