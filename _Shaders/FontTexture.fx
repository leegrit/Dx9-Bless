matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


texture FontTex;
sampler FontSampler = sampler_state
{
	texture = FontTex;
	MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float4 Color;
float ColorIntensity;

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
	float2 texcoord : TEXCOORD;
};
struct PixelOutput
{
	float4 color : COLOR0;
};


VertexOutput FontVS(VertexInput input)
{
	VertexOutput output = (VertexOutput)0;

	 /* Position */ 
    output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;

	return output;
};

float4 FontPS(PixelInput input) : COLOR0
{
	float4 font = tex2D(FontSampler, input.texcoord);

	return font + (Color * ColorIntensity);
};

technique FontTexture
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 FontVS();
		PixelShader = compile ps_3_0 FontPS();
	}
};
