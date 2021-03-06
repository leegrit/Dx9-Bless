
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

/* For HardwareSkinning */ 
float4x3 Palette[57];
int MaxVtxInf;

texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
};

texture MaskTex;
sampler MaskSampler = sampler_state
{
	Texture = (MaskTex);
	AddressU = Border;
	AddressV = Border;
};


struct SkinnedVtxIn
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
	float4 weights : BLENDWEIGHT0;
	int4 boneIndices : BLENDINDICES0;
};




struct VertexInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD0;
};

struct PixelOutput
{
	float4 vtxNormal : COLOR0;
	float4 EffectMask : COLOR1;
	float4 EffectParam : COLOR2;
	float4 RimLightColor : COLOR3;
};

int RimLightFactor;
//bool IsRimLight;

float RimLightWidth;
float4 RimLightColor;

int BloomFactor;

bool IsSkinnedMesh;

bool IsMasked; 
float2 UVMoveFactor;

PixelInputType SkinnedMeshVS(SkinnedVtxIn input)
{
	PixelInputType output;


		float4 p = float4(0.0f, 0.0f, 0.0f, 1.0f);
		float lastWeight = 0.0f;
		float inf = MaxVtxInf - 1;

		float4 n = float4(0.0f, 0.0f, 0.0f, 0.0f);

		for (int i = 0; i < inf; i++)
		{
			lastWeight += input.weights[i];
			float4x4 mat = float4x4
				(
					float4(Palette[input.boneIndices[i]][0], 0),
					float4(Palette[input.boneIndices[i]][1], 0),
					float4(Palette[input.boneIndices[i]][2], 0),
					float4(Palette[input.boneIndices[i]][3], 1)
					);
			p += input.weights[i] * mul(input.position, mat);
			n += normalize(input.weights[i] * mul(float4(input.normal, 0), mat));
		}
		lastWeight = 1.0f - lastWeight;
		float4x4 mat = float4x4
			(
				float4(Palette[input.boneIndices[inf]][0], 0),
				float4(Palette[input.boneIndices[inf]][1], 0),
				float4(Palette[input.boneIndices[inf]][2], 0),
				float4(Palette[input.boneIndices[inf]][3], 1)
				);
		p += lastWeight * mul(input.position, mat);
		n += normalize(lastWeight * mul(float4(input.normal, 0), mat));

		p.w = 1;

		/* Position */
		output.position = mul(p, WorldMatrix);
		output.position = mul(output.position, ViewMatrix);
		output.position = mul(output.position, ProjMatrix);


		/* Texcoord */
		output.texcoord = input.texcoord;

		/* Normal */
		output.normal = mul(float4(n.rgb, 0.0f), WorldMatrix).xyz;
		output.normal = float4(output.normal * 0.5f + 0.5f, 1);
		return output;
	


	
}

PixelInputType MeshVS(VertexInputType input)
{
	PixelInputType output = (PixelInputType)0;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.normal = mul(float4(input.normal.rgb,0.0 ), WorldMatrix);
	output.normal = float4(output.normal * 0.5f + 0.5f, 1);

	output.texcoord = input.texcoord;

	return output;
}

PixelOutput EffectBufferPS(PixelInputType input)
{
	PixelOutput output = (PixelOutput)0;

	float2 texcoord2 = input.texcoord;
	texcoord2 += UVMoveFactor;
	float4 maskTex = tex2D(MaskSampler, texcoord2);

	output.vtxNormal = float4( input.normal.rgb, 0);
	output.EffectMask.r = RimLightFactor;
	output.EffectMask.g = BloomFactor;
	if (IsMasked)
	{
		//float temp = BloomFactor * maskTex.r > 0 ? 1 : 0;
		output.EffectMask.g = BloomFactor * maskTex.r;
	}
	output.EffectParam.r = RimLightWidth;
	output.RimLightColor = RimLightColor;
	/* For Bloom */
	//float4 albedo = tex2D(AlbedoSampler, input.texcoord);
	//float brightness = dot(albedo.rgb, float3(1, 1, 1)/*float3(0.2126f, 0.7152f, 0.0722f)*/);
	// Bloom ?????? ?????? ??????
	// brigtness?? 0.99???????? effect mask?? ????????
	// PostRender???? ???? mask ?????? ???? albedo?? ???????? ?? ??????????.
	//if (brightness > 0.99)
		//output.BloomTexture = albedo;// *BloomFactor;



	return output;
}


technique EffectBuffer_Skinned
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = ADD;
		SrcBlend = ONE;
		DestBlend = ONE;
		VertexShader = compile vs_3_0 SkinnedMeshVS();
		PixelShader = compile ps_3_0 EffectBufferPS();
	}
}

technique EffectBuffer
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = ADD;
		SrcBlend = ONE;
		DestBlend = ONE;
		CULLMODE = NONE;
		VertexShader = compile vs_3_0 MeshVS();
		PixelShader = compile ps_3_0 EffectBufferPS();
	}
}


