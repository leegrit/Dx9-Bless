matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float DissolveAmount;
float FringeAmount;



float ProgressAmount;

texture ImageTex;
sampler ImageSampler = sampler_state
{
	Texture = (ImageTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};

// for progress
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

// for progress
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


void TextureVS
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

float4 PanelPS
(
    float2 texcoord : TEXCOORD0
) : COLOR0
{
    float4 imageColor = tex2D(ImageSampler, texcoord);
    return imageColor;
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


technique PanelShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 PanelPS();
    }
}

technique ButtonShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 PanelPS();
    }
}

technique ProgressShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 ProgressPS();
    }
}
