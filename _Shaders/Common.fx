/* World */
matrix WorldMatrix;

/* View */
matrix ViewMatrix;
matrix ViewMatrixInv;

/* Projection */
matrix ProjMatrix;
matrix ProjMatrixInv;

/* For Light */
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

/* For G-Buffer */
// DepthTex contain the position 
texture DepthTex;
sampler DepthSampler = sampler_state
{
	Texture = (DepthTex);
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
};
// NormalTex contain the normal that translated to world space
// And converted to 0 ~ 1
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
};
texture StashTex;
sampler StashSampler = sampler_state
{
	Texture = (StashTex);
};


/* For GBuffer */
void UnPackGBuffer(float2 texcoord, out float4 albedo, out float4 worldPos, out float3 normal)
{
	float4 depthMap  = tex2D(DepthSampler, texcoord);
	float4 albedoMap = tex2D(AlbedoSampler, texcoord);
	float4 normalMap = tex2D(NormalSampler, texcoord);

	albedo = albedoMap;

	float4 pos; 
	/* To Projection space */
	pos.x = texcoord.x * 2.f - 1.f;
	pos.y = texcoord.y * -2.f + 1.f;
	pos.z = depthMap.x;
	pos.w = 1;

    /* To View Space */
	pos = mul(pos, ProjMatrixInv);
	/* To World Space */
	pos = mul(pos, ViewMatrixInv);

	pos = pos / pos.w;

	/* Final reconstruct from depth*/
	worldPos = pos;

	/* Final reconstruct normal */
	normal = normalMap * 2 - 1;
	normal = normalize(normal);
}
float4 GetStashColor(float2 texcoord)
{
	float4 stashMap = tex2D(StashSampler, texcoord);
	return stashMap;
}



/* For Light */
float4 CalcDirectionalLight()
{
	return float4(0, 0, 0,0 );
}

float4 CalcPointLight()
{
	return float4(0, 0, 0, 0);
}

float4 CalcSpotLight()
{
	return float4(0, 0, 0, 0);
}