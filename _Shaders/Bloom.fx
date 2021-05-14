
float2 SourceSize;


texture SourceTex;
sampler SourceSampler = sampler_state
{
	Texture = (SourceTex);
};


float4 BloomPS(float2 texcoord:TEXCOORD0) : COLOR0
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
			x = arr[i].x * blur / 1024;
			y = arr[i].y * blur / 768;

			uv = texcoord + float2(x, y);

			color = color + tex2D(SourceSampler, uv);

			colorWeight ++;
		}	
	}
	color /= colorWeight;

	return color;
}

technique Bloom
{
	pass P0
	{
		ZEnable = false;
		VertexShader = NULL;
		PixelShader = compile ps_3_0 BloomPS();
	}
};
