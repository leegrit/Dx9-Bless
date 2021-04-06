matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

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
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

    /* Depth */ 
	outDepthPos = outPosition;

    /* Texcoord */ 
	outTexcoord = texcoord;

    /* Normal */
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
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float depth =  (float)depthPosition.z / depthPosition.w;  
	
    /* Depth */ 
	outDepth = float4(depth, depth, depth, 1);
	
    /* Albedo */
    outAlbedo = albedo;

    /* Normal */
	outNormal.r = normal.x;
	outNormal.g = normal.y;
	outNormal.b = normal.z;
	outNormal.a = 1;

}


technique GBuffer
{
	pass P0
	{
		VertexShader = compile vs_3_0 GBufferVS();
		PixelShader = compile ps_3_0 GBufferPS();
	}
};
