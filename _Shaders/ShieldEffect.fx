matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
};
texture AlphaMaskTex;
sampler AlphaMaskSampler = sampler_state
{
	Texture = (AlphaMaskTex);
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

float Alpha;
float2 UVMoveFactor;
float3 WorldPosition;
float3 EyePosition;
float RimWidth;


void ShieldEffectVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD0,
	float3 tangent : TANGENT0,
	float3 binormal : BINORMAL0,
	out float4 outPosition : POSITION,
	out float3 outNormal : NORMAL,
	out float2 outTexcoord : TEXCOORD0,
	out float3 outWorldPos : TEXCOORD1,
	out float3x3 outTangentWorldMat : TEXCOORD2
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);
	//float3 pos = outPosition;

	outTexcoord = texcoord;

	/* Normal */
	outNormal = normalize(mul(float4(normal, 0.f), WorldMatrix));

	/* TangentWorldMat */
	outTangentWorldMat[0] = mul(float4(tangent, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[1] = mul(float4(binormal, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[2] = mul(float4(normal, 0.0f), WorldMatrix).xyz;

	outWorldPos = outPosition;
}

void ShieldEffectPS(
	float2 texcoord : TEXCOORD0,
	float3 normal : NORMAL,
	float3 worldPos : TEXCOORD1,
	float3x3 tangentWorldMat : TEXCOORD2,
	out float4 outColor : COLOR0
)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 alphaMask = tex2D(AlphaMaskSampler, texcoord);

	/* BumpMap Sampling */
	float4 bumpMap = tex2D(NormalSampler, texcoord);

	/* convert -1 ~ 1*/
	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 tangent = normalize(tangentWorldMat[0]);
	float3 binormal = normalize(tangentWorldMat[1]);


	/* Calculate bumpNormal */
	float3 bumpNormal = (bumpMap.x * tangent) + (bumpMap.y * binormal) + (bumpMap.z * normal);
	bumpNormal = normalize(bumpNormal);

	//float4 normalResult = float4(bumpNormal * 0.5f + 0.5f, 1);


	//float3 toCamPos = normalize(EyePosition - WorldPosition);
	float3 toCamPos = float3(0, 0, -1);
	toCamPos = mul(toCamPos, (float3x3)WorldMatrix);
	toCamPos = normalize(toCamPos);
	float rimLightColor = smoothstep(1 - RimWidth, 1.0f, 1 - max(0, dot(bumpNormal, toCamPos)));
	//float rimLightColor = clamp(1 - max(0, dot(bumpNormal, toCamPos)), 1 - RimWidth, 1.0f);

	//if (rimLightColor <= (1 - RimWidth + 0.001f))
	//	rimLightColor = 0;
	//outColor = bumpMap;
	outColor = rimLightColor;
}

technique ShieldEffect
{
	pass P0
	{
		ZEnable = true;
		CULLMODE = CCW;
		LightEnable[0] = FALSE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 ShieldEffectVS();
		PixelShader = compile ps_3_0 ShieldEffectPS();
	}
};