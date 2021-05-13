
matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;

/* For Specular */
float3 EyePosition;


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
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;*/
};
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;*/
	//MinFilter = POINT;
	//MagFilter = POINT;
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;*/
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;*/
};
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;*/
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;*/
};
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;*/
	/*MinFilter = POINT;
	MagFilter = POINT;*/
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;*/
};
texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	/*MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;*/
	/*MinFilter = POINT;
	MagFilter = POINT;*/
};

texture LightTex;
sampler LightSampler = sampler_state
{
	Texture = (LightTex);
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

void PointLightPS(
	float2 texcoord : TEXCOORD0,
	out float4 outLightIntensity : COLOR0,
	out float4 outAmbientIntensity : COLOR1,
	out float4 outSpecularIntensity : COLOR2
	)
{
	
	//float4 baseColor = tex2D(CubeSampler, texcoord);
	float4 depthMap  = tex2D(DepthSampler, texcoord);
	//float4 albedoMap = tex2D(AlbedoSampler, texcoord);
	float4 normalMap = tex2D(NormalSampler, texcoord);
	float4 specularMap = tex2D(SpecularSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);
	 


	float4 worldPos;
	worldPos.x = texcoord.x * 2.f - 1.f;
	worldPos.y = texcoord.y * -2.f + 1.f;
	worldPos.z = depthMap.a;
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
	/*if(d > Range)
		discard;*/
	float distFactor = 1;
	if (d > Range)
		distFactor = 0;

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
		finalColor += (howMuchLight *  Diffuse).rgb;

		// Calculate Light's Falloff factor
		finalColor /= Constant + (Linear * d) + (Quadratic * (d*d));
	}

	// make sure the values are between 1 and 0
	finalColor = saturate(finalColor);

	/* Calculate Specular */
	float3 specular = float3(0, 0, 0); 
	if(finalColor.x > 0)
	{
		float3 viewDirection = normalize(EyePosition.xyz - worldPos.xyz);
		float3 lightDir = normalize(Position.xyz - worldPos.xyz);
		float3 reflection = reflect(lightDir, normal);
		reflection = normalize(reflection);
		float specularIntensity = saturate(dot(reflection, viewDirection));

		specular = pow(specularIntensity, SpecularPower);
		if(specularMap.a > 0)
			specular = specular;
		else
			specular = specular * specularMap.rgb;
	}
	finalColor = saturate(finalColor) * distFactor;
	outLightIntensity = float4(finalColor.rgb, 1);
	outAmbientIntensity = float4(0, 0, 0, 1);
	outSpecularIntensity = float4(specular.rgb, 1);


}



technique PointLight
{
	pass P0
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		//BlendOp = ADD;
		SrcBlend = ONE;
		DestBlend = ONE;
		VertexShader = compile vs_3_0 PointLightVS();
		PixelShader = compile ps_3_0 PointLightPS();
	}
	
}