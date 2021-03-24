matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float ProgressAmount;

texture ProgressTex;
sampler ProgressSampler = sampler_state
{
	Texture = (ProgressTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};

texture BackgroundTex;
sampler BackgroundSampler = sampler_state
{
	Texture = (BackgroundTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};



void ProgressVS
(
    float4 position : POSITION,
    float2 texcoord : TEXCOORD0,
    out float4 outPosition : POSITION,
    out float2 outTexcoord : TEXCOORD0
)
{
    outPosition = mul(position, WorldMatrix);
    outPosition = mul(outPosition, ViewMatrix);
    outPosition = mul(outPosition, ProjMatrix);

    outTexcoord = texcoord;
}

float4 ProgressPS
(
    float2 texcoord : TEXCOORD0
) : COLOR0
{
    if(texcoord.x > ProgressAmount)
        return tex2D(BackgroundSampler, texcoord);
    return tex2D(ProgressSampler, texcoord);
}

technique ProgressShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 ProgressVS();
		PixelShader = compile ps_3_0 ProgressPS();
    }
}


