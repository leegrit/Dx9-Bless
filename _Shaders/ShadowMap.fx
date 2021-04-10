
matrix WorldMatrix;
/* For Shadow Map */
matrix LightViewMatrix;
matrix LightProjMatrix;

void ShadowMapVS(
	float4 position : POSITION,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, LightViewMatrix);
	outPosition = mul(outPosition, LightProjMatrix);

    /* Depth */ 
	outDepthPos = outPosition;

}

void ShadowMapPS(
	float4 depthPos : TEXCOORD0,
	out float4 outLightDepth : COLOR0
)
{
	float lightDepth = (float)depthPos.z / depthPos.w;
	outLightDepth = float4(lightDepth, lightDepth, lightDepth, 1);
}

technique ShadowMap
{
	pass P0
	{
		VertexShader = compile vs_3_0 ShadowMapVS();
		PixelShader = compile ps_3_0 ShadowMapPS();
	}
};