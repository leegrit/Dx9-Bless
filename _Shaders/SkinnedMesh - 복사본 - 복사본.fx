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


/* For HardwareSkinning */
int BoneCount;
int BoneTextureWidth;
 
texture BoneTex;
 sampler BoneSampler = sampler_state
 {
	 Texture = (BoneTex);
 };

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


#ifndef MATRIX_PALETTE_SIZE_DEFAULT
#define MATRIX_PALETTE_SIZE_DEFAULT 26
#endif

const int MATRIX_PALETTE_SIZE = MATRIX_PALETTE_SIZE_DEFAULT;

matrix Palette[50];

int MaxVertexInf;

struct VS_SKIN_INPUT
{
	float4 pos;
	float3 blendWeights;
	float4 blendIndices;
	float3 nor;
};
struct VS_SKIN_OUTPUT
{
	float4 pos;
	float3 nor;
};

VS_SKIN_OUTPUT VS_Skin(const VS_SKIN_INPUT input, int numBones)
{
	VS_SKIN_OUTPUT output = (VS_SKIN_OUTPUT)0;

	float lastWeight = 1.0f;
	float weight;
	float blendWeights[3] = (float[3]) input.blendWeights;
	int indices[4] = (int[4])D3DCOLORtoUBYTE4(input.blendIndices);

	 for( int iBone = 0; (iBone < 3) && (iBone < numBones - 1); ++ iBone )
    {
        weight = blendWeights[ iBone ];
        lastWeight -= weight;
        output.pos.xyz += mul( input.pos, Palette[ indices[ iBone ] ] ) * weight;
        output.nor     += mul( input.nor, Palette[ indices[ iBone ] ] ) * weight;
    }
    
    output.pos.xyz += mul( input.pos, Palette[ indices[ numBones - 1 ] ] ) * lastWeight;
    output.nor     += mul( input.nor, Palette[ indices[ numBones - 1 ] ] ) * lastWeight;

    return output;
}












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
	//float boneTexel = 1 / (float)BoneTextureWidth;

	//float4 p = float4(0.0f,0.0f,0.0f,1.0f);
	//float lastWeight = 0.0f;
	//int numVertInfluences = 3;



	
/*
	for(int i = 0; i < numVertInfluences; i++)
	{
		lastWeight += weights[i];
		//float u = boneIndices[i] * boneTexel;
		//float v = 0;
		int baseIndex = 4 * boneIndices[i];
		int baseU = baseIndex % BoneTextureWidth;
		int baseV = baseIndex / BoneTextureWidth;
		float4x4 finalTransform =  float4x4(
			float4(tex2Dlod(BoneSampler, float4(float2(baseU, baseV), 0, 0))),
			float4(tex2Dlod(BoneSampler, float4(float2(baseU + boneTexel, baseV), 0, 0))),
			float4(tex2Dlod(BoneSampler, float4(float2(baseU + boneTexel*2, baseV), 0, 0))),
			float4(tex2Dlod(BoneSampler, float4(float2(baseU + boneTexel*3, baseV), 0, 0)))
		);
		p += weights[i] * mul(position, finalTransform);
	}
	//float u = boneIndices[3] * boneTexel;
	//float v = 0;
	int baseIndex = 4 * boneIndices[3];
	int baseU = baseIndex % BoneTextureWidth;
	int baseV = baseIndex / BoneTextureWidth;
	float4x4 finalTransform =  float4x4(
		float4(tex2Dlod(BoneSampler, float4(float2(baseU, baseV), 0, 0))),
		float4(tex2Dlod(BoneSampler, float4(float2(baseU + boneTexel*1, baseV), 0, 0))),
		float4(tex2Dlod(BoneSampler, float4(float2(baseU + boneTexel*2, baseV), 0, 0))),
		float4(tex2Dlod(BoneSampler, float4(float2(baseU + boneTexel*3, baseV), 0, 0)))
	);
	lastWeight = 1.0f - lastWeight;
	p += lastWeight * mul(position, finalTransform);
	p.w = 1.0f;
*/
	//VS_SKIN_INPUT vsi = {position, (float3)weights, boneIndices, normal};
	//VS_SKIN_OUTPUT vso = VS_Skin(vsi, BoneCount);


	//float4 boneTex = tex2Dlod(BoneSampler, float4(boneTexUV, 0, 0));

	/*
	float4 p = float4(0, 0, 0, 1);
	float lastWeight = 0.0f;
	int n = MaxVertexInf - 1;

	for (int i = 0; i < n; i++)
	{
		lastWeight += weights[i];
		p += weights[i] * mul(position, Palette[boneIndices[i]]);

	}
	lastWeight = 1.0f - lastWeight;
	p += lastWeight * mul(position, Palette[boneIndices[n]]);
	p.w = 1.0f;
	*/

	float4x4 skinTransform = 0;
	float3 N = normal;
	skinTransform += Palette[boneIndices.x] * weights.x;
	//N += normalize(mul(N, skinTransform));
	skinTransform += Palette[boneIndices.y] * weights.y;
	//N += normalize(mul(N, skinTransform));
	skinTransform += Palette[boneIndices.z] * weights.z;
	//N += normalize(mul(N, skinTransform));
	skinTransform += Palette[boneIndices.w] * weights.w;
	
	/*/
	float4 p = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float p0 = position[0];
	float p1 = position[1];
	float p2 = position[2];
	float p3 = position[3];

	float lastWeight = 0.0f;
	int i = 0;

	int idx0 = boneIndices[0] + p0 - p0;
	int idx1 = boneIndices[1] + p1 - p1;
	int idx2 = boneIndices[2] + p2 - p2;
	int idx3 = boneIndices[3] + p3 - p3;

	float weights0 = weights[0];
	float weights1 = weights[1];
	float weights2 = weights[2];
	float weights3 = weights[3];

	float weightsTotal = weights0 + weights1 + weights2 + weights3;

	p += weights0 * mul(position, Palette[idx0]);
	p += weights1 * mul(position, Palette[idx1]);
	p += weights2 * mul(position, Palette[idx2]);

	lastWeight = 1.0f - weights0 - weights1 - weights2 - weights3 + weights3;

	p += lastWeight * mul(position, Palette[idx3]);

	p.w = 1;

	//outPosition = mul(position, skinTransform);
	//outNormal = mul(float4(normal, 0.0f), skinTransform);
	//outTangentWorldMat[0] = mul(float4(tangent, 0.0f), skinTransform).xyz;
	//outTangentWorldMat[1] = mul(float4(binormal, 0.0f), skinTransform).xyz;
	//outTangentWorldMat[2] = mul(float4(normal, 0.0f), skinTransform).xyz;

	outTest = (float3)(Palette[0][1]);
	*/

	/* Position */
	outPosition = mul(position, skinTransform);
	outPosition = mul(outPosition, WorldMatrix);
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

technique SkinnedMesh
{
	pass P0
	{
		VertexShader = compile vs_3_0 SkinnedMeshVS();
		PixelShader = compile ps_3_0 SkinnedMeshPS();
	}
};
