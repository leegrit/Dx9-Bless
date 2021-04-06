float Far;

matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;


matrix TempViewMatrix;
matrix TempProjMatrix;

/* 나중에 따로 분리 */
/* For Light Data */
float3 Direction;
float3 Position;
float4 Ambient;
float  AmbientIntensity;
float4 Diffuse;
float  DiffuseIntensity;
float4 Specular;
float  SpecularIntensity;
float  SpecularPower;
float  Range;
float  Constant;
float  Linear;
float  Quadratic;

texture CubeTex;
sampler CubeSampler = sampler_state
{
	Texture = (CubeTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};


void PointLightVS(
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

float4 PointLightPS(
	float2 texcoord : TEXCOORD0
	) : COLOR0
{
	
	//float4 baseColor = tex2D(CubeSampler, texcoord);
	float4 depthMap  = tex2D(DepthSampler, texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, texcoord);
	float4 normalMap = tex2D(NormalSampler, texcoord);
	//float4 specularMap = tex2D(SpecularSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);
	 
	float linearZ = depthMap.y * Far;

	/*
	float4 worldPos;
	worldPos.x = (texcoord.x * 2.f - 1.f) * linearZ;
	worldPos.y = (texcoord.y * -2.f + 1.f) * linearZ;
	worldPos.z = depthMap.x * linearZ;
	worldPos.w = linearZ;

	worldPos = mul(worldPos, ProjMatrixInv);
	worldPos = mul(worldPos, ViewMatrixInv);
	*/

	float4 worldPos;
	worldPos.x = texcoord.x * 2.f - 1.f;
	worldPos.y = texcoord.y * -2.f + 1.f;
	worldPos.z = depthMap.x;
	worldPos.w = 1;

	worldPos = mul(worldPos, ProjMatrixInv);
	worldPos = mul(worldPos, ViewMatrixInv);

	worldPos = worldPos / worldPos.w;


	float3 finalColor = float3(0, 0, 0);

	// Create the vector between light position and pixel position
	float3 lightToPixelVec =  Position - worldPos.xyz;

	// Find the distance between the light pos and pixel pos
	float d = length(lightToPixelVec);

	// if pixel is too far, return zero
	if(d > Range)
		return stashMap;

	// Turn lightToPixelVec into a unit length vector describing
	// the pixels direction from the lights position
	lightToPixelVec = normalize(lightToPixelVec);

	float3 normal = normalMap * 2 - 1;
	normal = normalize(normal);

	// Calculate how much light the pixel gets by the angle
	// in which the light strikes the pixels surface
	float howMuchLight = dot(lightToPixelVec, normal);

	// if light is striking the front side of pixel
	if(howMuchLight > 0.0f)
	{
		// Add light to the finalColor of the pixel
		finalColor += (howMuchLight * albedoMap * Diffuse).rgb;

		// Calculate Light's Falloff factor
		finalColor /= Constant + (Linear * d) + (Quadratic * (d*d));
	}

	// make sure the values are between 1 and 0
	finalColor = saturate(finalColor);

	// Return Final color
	return float4(finalColor.rgb + stashMap.rgb, 1);
}



technique PointLight
{
	pass P0
	{
		VertexShader = compile vs_3_0 PointLightVS();
		PixelShader = compile ps_3_0 PointLightPS();
	}
}