matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float Amount;
float Alpha;

texture FillTex;
sampler FillSampler = sampler_state
{
	Texture = (FillTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};


void SkillProgressUIVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
};

void SkillProgressUIPS(
	float2 texcoord : TEXCOORD0,
	out float4 outColor : COLOR0
	)
{
	float4 fillColor = tex2D(FillSampler, texcoord);

	/*outColor = fillColor;
	return;*/

	float3 center = float3(0.5f, 0.5f, 0);
	float3 top = float3(0.5f, 0, 0);
	float3 curUV = float3(texcoord.xy, 0);
	float angle = 0;

	float3 centerToTop = top - center;
	float3 centerToCurUV = curUV - center;

	centerToTop = normalize(centerToTop);
	centerToCurUV = normalize(centerToCurUV);

	angle = acos(dot(centerToTop, centerToCurUV));
	angle = angle * (180.0f / 3.141592654f); // radian to degree
	
	angle = (centerToTop.x * centerToCurUV.x - centerToTop.y * centerToCurUV.x > 0.0f) ? angle : (-angle) + 360.0f;

	float condition = 360 * Amount;
	
	if(angle >= condition)
		discard;
	
	outColor = fillColor * Alpha;
};

technique SkillProgressUI
{
	pass P0
	{
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
		VertexShader = compile vs_3_0 SkillProgressUIVS();
		PixelShader = compile ps_3_0 SkillProgressUIPS();
	}
}

