matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


float ProgressAmount;


float Alpha;

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
texture ProgressBackTex;
sampler ProgressBackSampler = sampler_state
{
	Texture = (ProgressBackTex);
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

float4 TexturePS
(
    float2 texcoord : TEXCOORD0
) : COLOR0
{
    float4 imageColor = tex2D(ImageSampler, texcoord);
    return imageColor;
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
        return tex2D(ProgressBackSampler, texcoord);
    return tex2D(ProgressSampler, texcoord);
}

float4 ProgressVerticalPS
(
    float2 texcoord : TEXCOORD0
) : COLOR0
{
    if( 1 - texcoord.y > ProgressAmount)
        return tex2D(ProgressBackSampler, texcoord);
    return tex2D(ProgressSampler, texcoord);
}


float4 AlphaTexturePS
(
    float2 texcoord : TEXCOORD0
) : COLOR0
{
    float4 imageColor = tex2D(ImageSampler, texcoord);
    imageColor.a *= Alpha;
    return imageColor;
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
technique ProgressVerticalShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 ProgressVerticalPS();
    }
}

// Only texture
technique TextureShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 TexturePS();
    }
}


technique AlphaTexture
{
    pass P0
    {
        VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 AlphaTexturePS();
    }
}