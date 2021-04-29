matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

bool HasNormalMap;
bool HasSpecularMap;
bool HasEmissiveMap;

texture AlbedoTex0;
texture AlbedoTex0;
texture AlbedoTex0;
texture AlbedoTex0;
texture AlbedoTex0;
texture AlbedoTex0;
texture AlbedoTex0;
texture AlbedoTex0;
sampler AlbedoSampler[20] =
{
	sampler_state { Texture = (AlbedoTex0); },
	sampler_state { Texture = (AlbedoTex1); },
	sampler_state { Texture = (AlbedoTex2); },
	sampler_state { Texture = (AlbedoTex3); },
	sampler_state { Texture = (AlbedoTex4); },
	sampler_state { Texture = (AlbedoTex5); },
	sampler_state { Texture = (AlbedoTex6); },
	sampler_state { Texture = (AlbedoTex7); },
	sampler_state { Texture = (AlbedoTex8); },
	sampler_state { Texture = (AlbedoTex9); },
	sampler_state { Texture = (AlbedoTex10); },
	sampler_state { Texture = (AlbedoTex11); },
	sampler_state { Texture = (AlbedoTex12); },
	sampler_state { Texture = (AlbedoTex13); },
	sampler_state { Texture = (AlbedoTex14); },
	sampler_state { Texture = (AlbedoTex15); },
	sampler_state { Texture = (AlbedoTex16); },
	sampler_state { Texture = (AlbedoTex17); },
	sampler_state { Texture = (AlbedoTex18); },
	sampler_state { Texture = (AlbedoTex19); }
};
//texture Tex;
//sampler Samp[4] = 
//{
//	sampler_state { Texture = (Tex); },
//	sampler_state { Texture = (Tex); },
//	sampler_state { Texture = (Tex); },
//	sampler_state { Texture = (Tex); }
//};
//texture AlbedoTex0;
//texture AlbedoTex1;
//texture AlbedoTex2;
//texture AlbedoTex3;
//texture AlbedoTex4;
//texture AlbedoTex5;
//texture AlbedoTex6;
//texture AlbedoTex7;
//texture AlbedoTex8;
//texture AlbedoTex9;
//texture AlbedoTex10;
//texture AlbedoTex11;
//texture AlbedoTex12;
//texture AlbedoTex13;
//texture AlbedoTex14;
//texture AlbedoTex15;
//texture AlbedoTex16;
//texture AlbedoTex17;
//texture AlbedoTex18;
//texture AlbedoTex19;
//texture AlbedoTex20;
//sampler AlbedoSampler[20] =
//{
//	sampler_state { Texture = (AlbedoTex0); },
//	sampler_state { Texture = (AlbedoTex1); },
//	sampler_state { Texture = (AlbedoTex2); },
//	sampler_state { Texture = (AlbedoTex3); },
//	sampler_state { Texture = (AlbedoTex4); },
//	sampler_state { Texture = (AlbedoTex5); },
//	sampler_state { Texture = (AlbedoTex6); },
//	sampler_state { Texture = (AlbedoTex7); },
//	sampler_state { Texture = (AlbedoTex8); },
//	sampler_state { Texture = (AlbedoTex9); },
//	sampler_state { Texture = (AlbedoTex10); },
//	sampler_state { Texture = (AlbedoTex11); },
//	sampler_state { Texture = (AlbedoTex12); },
//	sampler_state { Texture = (AlbedoTex13); },
//	sampler_state { Texture = (AlbedoTex14); },
//	sampler_state { Texture = (AlbedoTex15); },
//	sampler_state { Texture = (AlbedoTex16); },
//	sampler_state { Texture = (AlbedoTex17); },
//	sampler_state { Texture = (AlbedoTex18); },
//	sampler_state { Texture = (AlbedoTex19); }
//};

//sampler AlbedoSampler= sampler_state
//{
//	Texture = (AlbedoTex);
//};
/* NormalMap */
// rgb = worldNormal
// a = shadow depth
texture NormalTex;
sampler NormalSampler = sampler_state
{
	Texture = (NormalTex);
};
/* Specular */
// rgb = specularMap
// a = specularMask
texture SpecularTex;
sampler SpecularSampler = sampler_state
{
	Texture = (SpecularTex);
};
texture EmissiveTex;
sampler EmissiveSampler = sampler_state
{
	Texture = (EmissiveTex);
};
texture SpecularMaskTex;
sampler SpecularMaskSampler = sampler_state
{
	Texture = (SpecularMaskTex);
};

texture DiffuseMaskTex;
sampler DiffuseMaskSampler = sampler_state
{
	Texture = (DiffuseMaskTex);
};


void StaticMeshVS(
	float4 position : POSITION,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD0,
	float3 tangent : TANGENT0,
	float3 binormal : BINORMAL0,
	out float4 outPosition : POSITION,
	out float4 outDepthPos : TEXCOORD0,
	out float3 outNormal : NORMAL,
	out float2 outTexcoord : TEXCOORD1,
	out float3x3 outTangentWorldMat : TEXCOORD2
)
{
    /* Position */ 
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

    /* Depth */ 
	outDepthPos = outPosition;

    /* Texcoord */ 
	outTexcoord = texcoord;

    /* Normal */
	outNormal = normalize(mul(float4(normal, 0.f), WorldMatrix));

	/* TangentWorldMat */
	outTangentWorldMat[0] = mul(float4(tangent, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[1] = mul(float4(binormal, 0.0f), WorldMatrix).xyz;
	outTangentWorldMat[2] = mul(float4(normal, 0.0f), WorldMatrix).xyz;
}

void StaticMeshPS(
	float4 depthPosition : TEXCOORD0,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD1,
	float3x3 tangentWorldMat : TEXCOORD2,
	uniform int passID, 
	out float4 outDepth : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outNormal : COLOR2,
	out float4 outSpecular : COLOR3
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 emissive = tex2D(EmissiveSampler, texcoord);
	float4 specular = tex2D(SpecularSampler, texcoord);
	float4 specularMask =tex2D(SpecularMaskSampler, texcoord);


	/* Depth */
	float depth =  (float)depthPosition.z / depthPosition.w;  


	outDepth = float4(emissive.r, emissive.g, emissive.b, depth);

    /* Albedo */
    outAlbedo = albedo;

	/* Specular */
	outSpecular = specular;
	outSpecular.a = specularMask.b;
	
	/* Normal */
	outNormal = float4(normal * 0.5f + 0.5f, 1);

	//if(HasNormalMap == true)
	//{
		/* BumpMap Sampling */
		float4 bumpMap = tex2D(NormalSampler, texcoord);
		
		/* convert -1 ~ 1*/
		bumpMap = (bumpMap * 2.0f) - 1.0f;

		float3 tangent = normalize(tangentWorldMat[0]);
		float3 binormal = normalize(tangentWorldMat[1]);


		/* Calculate bumpNormal */
		float3 bumpNormal = (bumpMap.x * tangent) + (bumpMap.y * binormal) + (bumpMap.z * normal);
		bumpNormal = normalize(bumpNormal);

		outNormal = float4(bumpNormal * 0.5f + 0.5f, 1);
	
	//}
}

void StaticMaskedMeshPS(
	float4 depthPosition : TEXCOORD0,
	float3 normal : NORMAL,
	float2 texcoord : TEXCOORD1,
	float3x3 tangentWorldMat : TEXCOORD2,
	out float4 outDepth : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outNormal : COLOR2,
	out float4 outSpecular : COLOR3
	)
{
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 emissive = tex2D(EmissiveSampler, texcoord);
	float4 specular = tex2D(SpecularSampler, texcoord);
	float4 specularMask =tex2D(SpecularMaskSampler, texcoord);
	float4 diffuseMask = tex2D(DiffuseMaskSampler, texcoord);

	if(diffuseMask.g == 0)
		discard;

	/* Depth */
	float depth =  (float)depthPosition.z / depthPosition.w;  


	outDepth = float4(emissive.r, emissive.g, emissive.b, depth);

    /* Albedo */
    outAlbedo = albedo;

	/* Specular */
	outSpecular = specular;
	outSpecular.a = specularMask.b;
	
	/* Normal */
	outNormal = float4(normal * 0.5f + 0.5f, 1);

	//if(HasNormalMap == true)
	//{
		/* BumpMap Sampling */
		float4 bumpMap = tex2D(NormalSampler, texcoord);
		
		/* convert -1 ~ 1*/
		bumpMap = (bumpMap * 2.0f) - 1.0f;

		float3 tangent = normalize(tangentWorldMat[0]);
		float3 binormal = normalize(tangentWorldMat[1]);


		/* Calculate bumpNormal */
		float3 bumpNormal = (bumpMap.x * tangent) + (bumpMap.y * binormal) + (bumpMap.z * normal);
		bumpNormal = normalize(bumpNormal);

		outNormal = float4(bumpNormal * 0.5f + 0.5f, 1);
	
	//}
}
//technique StaticMesh
//{
//	pass P0
//	{
//		//AlbedoSampler = { Texture = (AlbedoTex); };
//		CULLMODE = CCW;
//		AlphaBlendEnable = false;
//		VertexShader = compile vs_3_0 StaticMeshVS();
//		PixelShader = compile ps_3_0 StaticMeshPS();
//	}
//};

technique StaticMesh
{
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	/*pass P1
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(1);
	}
	pass P2
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(2);
	}
	pass P3
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(3);
	}
	pass P4
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(4);
	}
	pass P5
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(5);
	}
	pass P6
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(6);
	}
	pass P7
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(7);
	}
	pass P8
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(8);
	}
	pass P9
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(9);
	}
	pass P10
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(10);
	}
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}*/
};

technique StaticMaskedMesh
{
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMaskedMeshPS();
	}
};
