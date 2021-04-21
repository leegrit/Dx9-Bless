float Far;
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

bool HasNormalMap;


/* For HardwareSkinning */
int BoneCount;
int BoneTextureWidth;


texture BoneTex;
 sampler BoneSampler = sampler_state
 {
	 Texture = (BoneTex);
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



void SkinnedMeshVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD0,
	float4 weights : BLENDWEIGHT0,
	int4 boneIndices : BLENDINDICES0,
	float3 tangent : TANGENT0,
	float3 binormal : BINORMAL0,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0,
	out float3 outNormal : NORMAL,
	out float2 outTexcoord : TEXCOORD1,
	out float3x3 outTangentWorldMat : TEXCOORD2,
	out float3 outTest : TEXCOORD6
)
{
	float perTexel = 1 / 16;

	float4 p = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float lastWeight = 0.0f;
	float n = 4 - 1;

	for(int i = 0; i < n; i++)
	{
		lastWeight += weights[i];
		float baseU = (boneIndices[i] * 4) % 16;
		float baseV = 0;
		if(boneIndices[i] != 0)
			baseV = (boneIndices[i] * 4) / 16;
		//float 
		baseU = baseU * perTexel;
		baseV = baseV * perTexel;

		float offset = 16 * perTexel;

		float4x4 mat = float4x4
		(
			tex2Dlod(BoneSampler, float4(float2(baseU, baseV), 0, 0)),
			tex2Dlod(BoneSampler, float4(float2(baseU + perTexel, baseV), 0, 0)),
			tex2Dlod(BoneSampler, float4(float2(baseU + perTexel * 2, baseV), 0, 0)),
			tex2Dlod(BoneSampler, float4(float2(baseU + perTexel * 3, baseV), 0, 0))
		);
		mat = mat * 20;
		mat = mat - 10;
		p += weights[i] * mul(position, mat);
	}
	lastWeight = 1.0f - lastWeight;

	float baseU = (boneIndices[n] * 4) % 16;
	float baseV = 0;
	if (boneIndices[i] != 0)
		baseV = (boneIndices[n] * 4) / 16;
	//float baseV = (boneIndices[n] * 64) / 64;
	baseU = baseU * perTexel;
	baseV = baseV * perTexel;

	float offset = 16 * perTexel;

	float4x4 mat2 = float4x4
	(
		tex2Dlod(BoneSampler, float4(float2(baseU, baseV), 0, 0)),
		tex2Dlod(BoneSampler, float4(float2(baseU + perTexel, baseV), 0, 0)),
		tex2Dlod(BoneSampler, float4(float2(baseU + perTexel * 2, baseV), 0, 0)),
		tex2Dlod(BoneSampler, float4(float2(baseU + perTexel * 3, baseV), 0, 0))
	);
	mat2 = mat2 * 20;
	mat2 = mat2 - 10;
	p += lastWeight * mul(position, mat2);
	p.w = 1;

	//outTest = (float3)(mat[0].rgb);
	outTest = p.rgb;

	/* Position */
	//outPosition = mul(position, skinTransform);
	outPosition = mul(p, WorldMatrix);
	//outPosition = mul(outPosition, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	/* Depth */
	outDepthPos = outPosition;

	/* Texcoord */
	outTexcoord = texcoord;

	/* Normal */
	outNormal = normalize(mul(normal, WorldMatrix));

	/* TangentWorldMat */
	outTangentWorldMat[0] = mul(float4(tangent, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[1] = mul(float4(binormal, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[2] = mul(float4(normal, 0.0f), WorldMatrix).xyz;
}

void SkinnedMeshPS(
	float4 depthPosition : TEXCOORD0,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD1,
	float3x3 tangentWorldMat : TEXCOORD2,
	float3 Test : TEXCOORD6,
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
	/* Test */
	outAlbedo = float4(Test.rgb, 1);

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

technique HardwareSkinning
{
	pass P0
	{
		VertexShader = compile vs_3_0 SkinnedMeshVS();
		PixelShader = compile ps_3_0 SkinnedMeshPS();
	}
};
