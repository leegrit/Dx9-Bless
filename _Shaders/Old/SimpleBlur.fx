matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float2 SourceSize;
int BlurCount;

texture SourceTex;
sampler SourceSampler = sampler_state
{
	Texture = (SourceTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};


texture BlurMaskTex;
sampler BlurMaskSampler = sampler_state
{
	Texture = (BlurMaskTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};


void SimpleBlurVS(
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

float4 SimpleBlurPS(
	float2 texcoord : TEXCOORD0
	) : COLOR0
{
	//return float4(tex2D(BlurMaskSampler, texcoord).a, 0, 0, 1);
	float4 color = tex2D(SourceSampler, texcoord);
	//return color;
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
	float blurMaskValue;
	float4 blurMask;
	for(int blur = 1; blur < 4; blur++)
	{
		for(int i = 0; i < 8; i++)
		{
			x = arr[i].x * blur / SourceSize.x;
			y = arr[i].y * blur / SourceSize.y;

			uv = texcoord + float2(x, y);
			
			blurMask = tex2D(BlurMaskSampler, uv);
			blurMaskValue = blurMask.a;
			// Blur Mask에 값이 있다면 정상적으로 블러처리가 되겠지만
			// Blur mask의 해당 uv 값이 0이라면 블러처리되지 않고 원본 값이 그대로 반환된다.
			color = color + tex2D(SourceSampler, uv) * blurMaskValue;
			//
			if(blurMaskValue != 0)
				colorWeight++;
			//color = color + tex2D(SourceSampler, uv);
			//colorWeight ++;

		}
	}
	color /= colorWeight;

	return color;
}




technique SimpleBlur
{
	pass P0
	{
		VertexShader = compile vs_3_0 SimpleBlurVS();
		PixelShader = compile ps_3_0 SimpleBlurPS();
	}
}