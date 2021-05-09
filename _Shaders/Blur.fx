matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float2 SourceSize;


texture SourceTex;
sampler SourceSampler = sampler_state
{
	Texture = (SourceTex);
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = wrap;
    AddressV = wrap;*/
};

void BlurVS
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

float4 BlurPS(float2 texcoord:TEXCOORD0) : COLOR0
{
	float4 color = tex2D(SourceSampler, texcoord);

	float2 arr[8] = 
	  {
        float2(-1, -1), float2(0, -1), float2(1, -1),
        float2(-1, 0),                float2(1, 0),
        float2(-1, 1), float2(0, 1), float2(1, 1)
    };

	int colorWeight = 1;
	float x;
	float y;
	float2 uv;

	for(int blur = 1; blur < 8; blur++)
	{
		for(int i = 0; i < 8; i++)
		{
			x = arr[i].x * blur / SourceSize.x;
			y = arr[i].y * blur / SourceSize.y;

			uv = texcoord + float2(x, y);

			color = color + tex2D(SourceSampler, uv);

			colorWeight ++;
		}	
	}
	color /= colorWeight;

	return color;
}

technique Blur
{
	pass P0
	{
		ZEnable = false;
		VertexShader = compile vs_3_0 BlurVS();
		PixelShader = compile ps_3_0 BlurPS();
	}
};
