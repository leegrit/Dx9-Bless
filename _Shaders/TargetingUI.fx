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

VertexOutput TargetingUIVS(VertexInput input)
{
	VertexOutput output = (VertexOutput)0;
	
	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;

	return output;
}

float4 TargetingUIPS(PixelInput input) : COLOR0
{
	float4 color = tex2D(DiffuseSampler, input.texcoord);
	return color;
}


technique TargetingUI
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		ZEnable = false;
		VertexShader = compile vs_3_0 TargetingUIVS();
		PixelShader = compile ps_3_0 TargetingUIPS();
	}
};
