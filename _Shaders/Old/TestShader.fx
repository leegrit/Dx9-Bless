matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;
float4 Diffuse;

sampler2D BaseMap;

struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
};

VS_OUTPUT vs_main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;

	return output;
}

float4 ps_main(PS_INPUT input) : COLOR0
{
	float4 baseColor = tex2D(BaseMap, input.texcoord);

	return saturate(baseColor + Diffuse);
}

technique Default_Technique
{
	pass P0
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
	
};