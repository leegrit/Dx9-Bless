matrix WorldMatrix;
matrix ViewMatrix;
matrix ViewMatrixInv;
matrix ProjMatrix;
matrix ProjMatrixInv;


matrix TempViewMatrix;
matrix TempProjMatrix;

float4 Diffuse;

float3 LightPosition;
float LightAmbient;
float LightRange;
float LightDiffuse;


float LightConstant;
float LightLinear;
float LightExp;

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
	float4 specularMap = tex2D(SpecularSampler, texcoord);
	float4 stashMap = tex2D(StashSampler, texcoord);
	 
	float4 diffuse = albedoMap;
	normalMap = normalize(normalMap);
  	//normalMap = float4((normalMap.xyz - 0.5f) * 2, normalMap.w);
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);


	
	float4 clipSpacePosition = float4(texcoord.x * 2.0f - 1.0f, 
			texcoord.y * 2.0f - 1.0f, depthMap.x, 1);
	
	
	float4 projSpacePosition = mul(clipSpacePosition, ProjMatrixInv);
	float4 worldSpacePosition = mul(projSpacePosition, ViewMatrixInv);
	worldSpacePosition = worldSpacePosition / worldSpacePosition.w;
	
	
	float3 lightToPixelVec = LightPosition - (float3)worldSpacePosition;



	// Find the distance between the light pos and pixel pos
	float d = length(lightToPixelVec);

	// create the ambient light
	float3 finalAmbient = diffuse * LightAmbient;

	// if pixel is too far, return pixel color with ambient light
	// 주변광을 다른 technique에서 처리하고 여기선 빛의 영향을 받는 부분만
	// 누적한다.
	if(d > LightRange)
		return float4(stashMap.rgb, diffuse.a);
		///return float4(finalAmbient + stashMap.rgb, diffuse.a);

	//Turn lightToPixelVec into a unit length vector describing
    //the pixels direction from the lights position
	lightToPixelVec /= d;
	//lightToPixelVec = normalize(lightToPixelVec);

	//Calculate how much light the pixel gets by the angle
    //in which the light strikes the pixels surface
	float howMuchLight = dot(lightToPixelVec, (float3)normalMap);

	//if(howMuchLight == 0)
	//	return float4(1, 1, 1, 1);
	//if(howMuchLight > 0)
	//	return float4(1, 0, 0, 1);
	//if(howMuchLight < 0)
	//	return float4(0, -howMuchLight, 0, 1);
	// if light is striking the front side of the pixel
	//howMuchLight = howMuchLight * -1;
	if(howMuchLight > 0.0f)
	{
		//Add light to the finalColor of the pixel
		finalColor += howMuchLight * diffuse * LightDiffuse;

		//Calculate Light's Falloff factor
		finalColor /= LightConstant + LightLinear * d + LightExp * d * d;
	}

 	//make sure the values are between 1 and 0, and add the ambient
    finalColor = saturate(finalColor + finalAmbient);

	return float4(finalColor + stashMap.rgb, diffuse.a);
}



technique PointLight
{
	pass P0
	{
		VertexShader = compile vs_3_0 PointLightVS();
		PixelShader = compile ps_3_0 PointLightPS();
	}
}