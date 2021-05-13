matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


texture LightIntensityTex;
sampler LightIntensitySampler = sampler_state
{
	texture = (LightIntensityTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;*/
};

texture AmbientIntensityTex;
sampler AmbientIntensitySampler = sampler_state
{
	texture = (AmbientIntensityTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;*/
};


texture SpecularIntensityTex;
sampler SpecularIntensitySampler = sampler_state
{
	texture = (SpecularIntensityTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;*/
};


texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = AlbedoTex;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	//MipFilter = LINEAR;
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


VertexOutput DefaultVS(VertexInput input)
{
	VertexOutput output = (VertexOutput)0;

	output.position = mul(input.position, WorldMatrix);
	output.position = mul(output.position, ViewMatrix);
	output.position = mul(output.position, ProjMatrix);

	output.texcoord = input.texcoord;

	return output;
};


float4 DeferredBlendPS(PixelInput In) : COLOR0
{
	
	float4 color = tex2D(AlbedoSampler, In.texcoord);
	float4 lightIntensity = tex2D(LightIntensitySampler, In.texcoord);
	float4 ambientIntensity = tex2D(AmbientIntensitySampler, In.texcoord);
	float4 specularIntensity = tex2D(SpecularIntensitySampler, In.texcoord);

	float4 ambient = color * ambientIntensity;
	color = color * lightIntensity + ambient + specularIntensity;

	return color;
};

float4 DeferredBlendWithLUTFilterPS(PixelInput In) : COLOR0
{
	float4 color = tex2D(AlbedoSampler, In.texcoord);
	/*float4 shade = tex2D(LightSampler, In.texcoord);

	color = color * shade;

	color = float4(GetLutColor(color.rgb, LutSampler), 1.0f); */

	return color;
};

technique DeferredBlend
{
	pass P0
	{
		ZEnable = false;
		
		VertexShader = NULL;// compile vs_3_0 DefaultVS();
		PixelShader = compile ps_3_0 DeferredBlendPS();
	}
};

technique DeferredBlendWithLUTFilter
{
	pass P0
	{
		ZEnable = false;
		
		VertexShader = compile vs_3_0 DefaultVS();
		PixelShader = compile ps_3_0 DeferredBlendPS();
	}
};
