#include "SubsetTextures.fx"



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
	float4 albedo = tex2D(AlbedoSampler[passID], texcoord);
	float4 emissive = tex2D(EmissiveSampler[passID], texcoord);
	float4 specular = tex2D(SpecularSampler[passID], texcoord);
	float4 specularMask =tex2D(SpecularMaskSampler[passID], texcoord);


	/* Depth */
	float depth =  (float)depthPosition.z / depthPosition.w;  


	outDepth = float4(emissive.r, emissive.g, emissive.b, depth);

    /* Albedo */
    outAlbedo = albedo;

	/* Specular */
	outSpecular = specular;
	// 수정 필요
	outSpecular.a = 1 - specularMask.r;
	
	/* Normal */
	//outNormal = float4(normal * 0.5f + 0.5f, 1);


	/* BumpMap Sampling */
	float4 bumpMap = tex2D(NormalSampler[passID], texcoord);
		
	/* convert -1 ~ 1*/
	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 tangent = normalize(tangentWorldMat[0]);
	float3 binormal = normalize(tangentWorldMat[1]);


	/* Calculate bumpNormal */
	float3 bumpNormal = (bumpMap.x * tangent) + (bumpMap.y * binormal) + (bumpMap.z * normal);
	bumpNormal = normalize(bumpNormal);

	outNormal = float4(bumpNormal * 0.5f + 0.5f, 1);
	

}


technique StaticMesh
{
	pass P0
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P1
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
		PixelShader = compile ps_3_0 StaticMeshPS(0);
	}
	pass P0
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
	pass P11
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(11);
	}
	pass P12
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(12);
	}
	pass P13
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(13);
	}
	pass P14
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(14);
	}
	/*pass P15
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(15);
	}*/
	/*pass P16
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(16);
	}
	pass P17
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(17);
	}
	pass P18
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(18);
	}
	pass P19
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(19);
	}
	pass P20
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(20);
	}
	pass P21
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(21);
	}
	pass P22
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(22);
	}
	pass P23
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(23);
	}
	pass P24
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(24);
	}
	pass P25
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(25);
	}
	pass P26
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(26);
	}
	pass P27
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(27);
	}
	pass P28
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(28);
	}
	pass P29
	{
		CULLMODE = CCW;
		AlphaBlendEnable = false;
		VertexShader = compile vs_3_0 StaticMeshVS();
		PixelShader = compile ps_3_0 StaticMeshPS(29);
	}*/
};


