float Far;
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

bool HasNormalMap;

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
	out float4 outNormal : COLOR2
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);

	/* Depth */
	float depth =  (float)depthPosition.z / depthPosition.w;  
	outDepth = float4(depth, depth, depth, 0);

    /* Albedo */
    outAlbedo = albedo;

	
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


technique GBuffer
{
	pass P0
	{
		
		VertexShader = compile vs_3_0 GBufferVS();
		PixelShader = compile ps_3_0 GBufferPS();
	}
};
