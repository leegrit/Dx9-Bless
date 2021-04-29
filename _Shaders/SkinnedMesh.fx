
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

bool HasNormalMap;

/* For HardwareSkinning */ 
float4x3 Palette[57];
int MaxVtxInf;

texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
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
	MipFilter = LINEAR;
};
texture EmissiveTex;
sampler EmissiveSampler = sampler_state
{
	Texture = (EmissiveTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};
texture SpecularMaskTex;
sampler SpecularMaskSampler = sampler_state
{
	Texture = (SpecularMaskTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
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
	float4 p = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float lastWeight = 0.0f;
	float inf = MaxVtxInf - 1;
	
	float4 t = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 b = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 n = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
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
			t += normalize(weights[i] * mul(float4(tangent, 0), mat));
			b += normalize(weights[i] * mul(float4(binormal, 0), mat));
			n += normalize(weights[i] * mul(float4(normal, 0), mat));
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
	t += normalize(lastWeight * mul(float4(tangent, 0), mat));
	b += normalize(lastWeight * mul(float4(binormal, 0), mat));
	n += normalize(lastWeight * mul(float4(normal, 0), mat));
	
	p.w = 1;
	

	/* Position */
	outPosition = mul(p, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	/* Depth */
	outDepthPos = outPosition;

	/* Texcoord */
	outTexcoord = texcoord;

	/* Normal */
	outNormal = normalize(mul(n, WorldMatrix));

	/* TangentWorldMat */
	outTangentWorldMat[0] = mul(float4(t.rgb, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[1] = mul(float4(b.rgb, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[2] = mul(float4(n.rgb, 0.0f), WorldMatrix).xyz;
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

	/* Specular */
	outSpecular = specular;
	outSpecular.a = specularMask.b + specularMask.g;
	
	/* Normal */
	outNormal = float4(normal * 0.5f + 0.5f, 1);

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


technique SkinnedMesh
{
	pass P0
	{
		VertexShader = compile vs_3_0 SkinnedMeshVS();
		PixelShader = compile ps_3_0 SkinnedMeshPS();
	}
};
