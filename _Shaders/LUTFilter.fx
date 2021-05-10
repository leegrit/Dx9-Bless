matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

texture ScreenTex;
sampler ScreenSampler = sampler_state
{
	Texture = (ScreenTex);
};

texture LutTex;
sampler LutSampler = sampler_state
{
	Texture = (LutTex);
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

float3 GetLutColor(float3 color, sampler2D LutSampler)
{
	float2 LutSize = float2(0.00390625, 0.0625) ; // 1 / float2(256, 16)
	float4 LutUV;
	color = saturate(color) * 15.0f;
	LutUV.w =  floor(color.b);
	LutUV.xy = (color.rg + 0.5) * LutSize;
	LutUV.x += LutUV.w * LutSize.y;
	LutUV.z = LutUV.x + LutSize.y;
	return lerp(tex2Dlod(LutSampler, LutUV.xyzz).rgb, tex2Dlod(LutSampler, LutUV.zyzz).rgb, color.b - LutUV.w);
};


VertexOutput LutFilterVS(VertexInput input)
{
	VertexOutput output = (VertexOutput)0;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;

	return output;
};


float4 LutFilterPS(PixelInput In) : COLOR0
{
	float4 color = tex2D(ScreenSampler,In.texcoord);
	
	//return float4(1, 0, 0, 1);

	return float4(GetLutColor(color.rgb, LutSampler), 1.0f);
};


technique LutFilter
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 LutFilterVS();
		PixelShader = compile ps_3_0 LutFilterPS();
	}
};
