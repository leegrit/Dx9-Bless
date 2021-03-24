matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;
float4 WorldPosition;
texture CubeTex;
sampler CubeSampler = sampler_state
{
	Texture = (CubeTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};


void GBufferVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0,
	out float3 outNormal : NORMAL,
	out float2 outTexcoord : TEXCOORD1
)
{
	position.w = 1;
	//float4 worldPos;
    outPosition = mul(position, WorldMatrix);
	//worldPos = outPosition;
	outPosition = mul(outPosition, ViewMatrix);
	//worldViewPos = outPosition;
	outPosition = mul(outPosition, ProjMatrix);

	// depth in view coordinate, store in x
//	float depth= (float)outPosition.z / (float)outPosition.w;
	
	outDepthPos = outPosition ;
	//outDepth .x = depth;
	//outDepth.y = 1;
	outTexcoord = texcoord;
	outNormal = normal;
}

void GBufferPS(
	float4 depthPosition : TEXCOORD0,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD1,
	out float4 outDepth : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outNormal : COLOR2
	)
{
	float4 baseColor = tex2D(CubeSampler, texcoord);
	


	float depth =  (float)depthPosition.z / depthPosition.w;  
	
	outDepth = float4(depth, depth, depth, 1);
	
	outAlbedo = baseColor;
	outAlbedo.a = 0.5f;

	outNormal.r = normal.x;
	outNormal.g = normal.y;
	outNormal.b = normal.z;
	outNormal.a = 1;
}

void GBufferWithBlurPS(
	float4 depthPosition : TEXCOORD0,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD1,
	out float4 outDepth : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outNormal : COLOR2,
	out float4 blurMask : COLOR3
	)
{
	float4 baseColor = tex2D(CubeSampler, texcoord);
	


	float depth =  (float)depthPosition.z / depthPosition.w;  
	
	outDepth = float4(depth, depth, depth, 1);
	
	outAlbedo = baseColor;

	outNormal.r = normal.x;
	outNormal.g = normal.y;
	outNormal.b = normal.z;
	outNormal.a = 1;

	blurMask.r = 0;
	blurMask.g = 0;
	blurMask.b = 0;
	blurMask.a = 1;
}


technique GBuffer
{
	pass P0
	{
		VertexShader = compile vs_3_0 GBufferVS();
		PixelShader = compile ps_3_0 GBufferPS();
	}
};

technique GBufferWithBlur
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_3_0 GBufferVS();
		PixelShader = compile ps_3_0 GBufferWithBlurPS();
	}
}