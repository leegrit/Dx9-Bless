
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
float  Cone;
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
    MipFilter = None;
    AddressU = wrap;
    AddressV = clamp;*/
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
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
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;*/
};
texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
	MinFilter = POINT;
	MagFilter = POINT;
	/*MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;*/
};


void SpotLightVS(
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

float4 SpotLightPS(
	float2 texcoord : TEXCOORD0
	) : COLOR0
{
	
	//float4 baseColor = tex2D(CubeSampler, texcoord);
	float4 depthMap  = tex2D(DepthSampler, texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, texcoord);
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

	float3 normal = normalMap * 2 - 1;
	normal = normalize(normal);

	float3 finalColor = float3(0, 0, 0);

	// Create the vector between light position and pixels position
	float3 lightToPixelVec = Position - worldPos.xyz;

	// Find the distance between the light pos and pixel pos
	float distance = length(lightToPixelVec);

	// If pixel is too far, return stash color
	if(distance > Range)
		return stashMap;

	// Turn lightToPixelVec into a unit length vector describing
	// the pixels direction from the lights position
	lightToPixelVec = normalize(lightToPixelVec);

	// in which the light strikes the pixels surface
	float howMuchLight = dot(lightToPixelVec, normal);	

	// If light is striking the front side of the pixel
	if(howMuchLight > 0.0f)
	{
		// Add light to the finalColor of the pixel
		finalColor += albedoMap.rgb * Diffuse.rgb;
		
		// calculate Light's Distance Falloff factor
		finalColor /= (Constant + (Linear * distance)) + (Quadratic * (distance * distance));

		// Calculate falloff from center to edge of pointlight cone
		finalColor *= pow(max(dot(-lightToPixelVec, Direction), 0.0f), Cone);
	}

	// Make sure the values are between 1 and 0
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
		specular = specular * specularMap.rgb;
	}
	finalColor = saturate(finalColor + specular.rgb);

	// Return Final color
	return float4(finalColor.rgb + stashMap.rgb, 1);
}



technique SpotLight
{
	pass P0
	{
		ZEnable = false;
		AlphaBlendEnable = true;
		//BlendOp = ADD;
		SrcBlend = ONE;
		DestBlend = ONE;
		VertexShader = compile vs_3_0 SpotLightVS();
		PixelShader = compile ps_3_0 SpotLightPS();
	}
}