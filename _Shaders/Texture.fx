matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


texture DiffuseTex;
sampler DiffuseSampler = sampler_state
{
	Texture = (DiffuseTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

texture AlphaMaskTex;
sampler AlphaMaskSampler = sampler_state
{
	Texture = (AlphaMaskTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

struct VertexInput
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
};
struct VertexOutput
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
};
struct PixelInput
{
	float2 texcoord : TEXCOORD0;
};

VertexOutput TextureVS(VertexInput input)
{
	VertexOutput output = (VertexOutput)0;
	
	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;

	return output;
}

float4 TexturePS(PixelInput input) : COLOR0
{
	float4 color = tex2D(DiffuseSampler, input.texcoord);
	clip(color.a);
	return color;
}


technique Texture
{
	pass P0
	{
		CullMode = NONE;
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 TextureVS();
		PixelShader = compile ps_3_0 TexturePS();
	}
};
