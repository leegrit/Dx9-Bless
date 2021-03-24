matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float4 Color;

float4 Ambient;
float4 AmbientIntensity;
float4 Diffuse;
float4 DiffuseIntensity;
float4 Specular;
float4 SpecularIntensity;
float4 SpecularPower;

float4 LightDirection;
float4 CameraPosition;

float DissolveAmount;
float FringeAmount;


texture BaseMap;
sampler BaseSampler = sampler_state
{
	Texture = (BaseMap);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};


texture BumpMap;
sampler BumpSampler = sampler_state
{
	Texture = (BumpMap);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};

texture EmissionMap;
sampler EmissionSampler = sampler_state
{
	Texture = (EmissionMap);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};

texture DissolveMap;
sampler DissolveSampler = sampler_state
{
	Texture = (DissolveMap);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};



float4 Dissolve(float4 sourceColor, float2 texcoord,
                float dissolveAmount, float fringeAmount)
{
    float4 dissolveMap = tex2D(DissolveSampler ,texcoord);
    float dissolveValue = dissolveMap.x;

    if(dissolveValue <= dissolveAmount)
    {
        sourceColor = float4(0, 0, 0, 0);
    }
    else if((dissolveValue <= dissolveAmount + fringeAmount) && dissolveAmount != 0)
    {
        if(sourceColor.a == 0.0f)
            return sourceColor;
        sourceColor = sourceColor + float4(255, 255, 0, sourceColor.a);

    }
    return sourceColor;
}

void MeshVS(float4 position : POSITION,
            float3 normal : NORMAL, 
            float2 texcoord : TEXCOORD0,
            out float4 outPosition : POSITION,
            out float3 outNormal : NORMAL,
            out float3 outViewDir : TEXCOORD0,
            out float3 outLightDir : TEXCOORD1,
            out float2 outTexcoord : TEXCOORD2)
{
    outPosition = mul(position, WorldMatrix);
    outPosition = mul(outPosition, ViewMatrix);
    outPosition = mul(outPosition, ProjMatrix);

    float4 worldPosition = mul(position, WorldMatrix);

    outTexcoord = texcoord;

    outLightDir = -normalize(LightDirection);

    outViewDir = normalize(CameraPosition.xyz - worldPosition.xyz);

    // 월드 법선 벡터 구하기
    float3 worldNormal = mul(normal, (float3x3)WorldMatrix);
    worldNormal = normalize(worldNormal);
    outNormal = worldNormal;
}

void MeshPS(float3 normal : NORMAL,
            float3 viewDir : TEXCOORD0,
            float3 lightDir : TEXCOORD1,
            float2 texcoord : TEXCOORD2,
            out float4 outColor : COLOR0)
{
    float4 albedo = tex2D(BaseSampler, texcoord);

    // normalization / 래스터라이저 보간을 했기 때문에 정규화를 다시 해준다.
    normal = normalize(normal);
    viewDir = normalize(viewDir);
    lightDir = normalize(lightDir);
    

    // ambient 
    float4 ambientColor = Ambient * AmbientIntensity;

    // diffuse
    float4 diffuseColor = Diffuse * DiffuseIntensity * dot(lightDir, normal);

    float4 specularColor = float4(0,0,0,0);
    if(diffuseColor.r > 0)
    {
            // specular
    //float3 reflection = reflect(-lightDir, normal);
    //float4 specularColor = Specular * SpecularIntensity * pow(saturate(dot(reflection, viewDir)), SpecularPower);
    }
    outColor = saturate((ambientColor + diffuseColor) * albedo + specularColor);

   // outColor = Dissolve(outColor, texcoord, DissolveAmount, FringeAmount);

}            


void BumpVS
(
    float4 position : POSITION,
    float2 texcoord : TEXCOORD0,
    float3 normal :NORMAL,
    float3 binormal : BINORMAL,
    float3 tangent : TANGENT,
    out float4 outPosition : POSITION,
    out float2 outTexcoord : TEXCOORD0,
    out float3 outViewDir : TEXCOORD1,
    out float3 outLightDir : TEXCOORD2,
    out float3 outTangent : TEXCOORD3,
    out float3 outBinormal : TEXCOORD4,
    out float3 outNormal : TEXCOORD5
)
{
    outPosition = mul(position, WorldMatrix);
    outPosition = mul(outPosition, ViewMatrix);
    outPosition = mul(outPosition, ProjMatrix);
    outTexcoord = texcoord;


 float3 worldPos = mul(position, WorldMatrix);
    // 물체로 들어오는 빛의 방향 벡터를 월드 공간으로 변환하고
    // 이후 내적을 위해 역 방향으로 방향을 바꿔준다.
   
    outLightDir = normalize(LightDirection);

    
    // 노말값 월드공간으로
    float3 worldNormal = mul(normal, (float3x3)WorldMatrix);
    outNormal = normalize(worldNormal);

    // 탄젠트값 월드공간으로
    float3 worldTangent = mul(tangent, (float3x3)WorldMatrix);
    outTangent = normalize(worldTangent);

    // 바이노말값 월드공간으로.
    float3 worldBinormal = mul(binormal, (float3x3)WorldMatrix);
    outBinormal = normalize(worldBinormal);

    // 물체를 바라보는 시선 벡터를 월드공간으로 변환한다.
    outViewDir = normalize(worldPos.xyz - CameraPosition.xyz);


}

void BumpPS
(
    float2 texcoord : TEXCOORD0,
    float3 viewDir : TEXCOORD1,
    float3 lightDir : TEXCOORD2,
    float3 tangent : TEXCOORD3,
    float3 binormal : TEXCOORD4,
    float3 normal : TEXCOORD5,
    out float4 outColor : COLOR0
)
{
    viewDir = normalize(viewDir);
    lightDir = normalize(lightDir);
    tangent = normalize(tangent);
    binormal = normalize(binormal);
    normal = normalize(normal);

    float4 albedo = tex2D(BaseSampler, texcoord);
    float4 emission = tex2D(EmissionSampler,texcoord);
    // 법선맵 텍스처로부터 법선 읽어온다.
    float3 tangentNormal = tex2D(BumpSampler, texcoord);
    // rgb를 xyz 기준으로 변환한다.
    tangentNormal = normalize(tangentNormal * 2 - 1);

    // 변환행렬 만들기 (월드 -> 접선)
    float3x3 TBN = float3x3(tangent, binormal, normal);
    TBN = transpose(TBN); // 역행렬을 구해서 접선->월드

    float3 worldNormal = mul(TBN, tangentNormal); // 월드의 법선

    // ambient color
    float4 ambientColor = Ambient * AmbientIntensity;

    // diffuse color
    float4 diffuseColor = Diffuse * DiffuseIntensity * saturate(dot(-lightDir, worldNormal));

   //float4 specularColor = Specular * SpecularIntensity * pow(saturate(dot(reflection, -viewDir)), SpecularPower);
    float4 specularColor = 0;
    if(diffuseColor.x > 0)
    {
        //float3 reflection = reflect(lightDir, worldNormal);
      //  specularColor = saturate(dot(reflection, -viewDir));
        //specularColor = pow(specularColor, SpecularPower);

       // 여기부터 테스트
       /*
       float3 fvReflection  = normalize(((2.0f * tangentNormal)*(dot(tangentNormal,lightDir))) - lightDir);
       float3 fvViewDir = normalize(viewDir);
       float fRDotV = max(0.0f, dot(fvReflection, fvViewDir));
       specularColor = Specular * pow(fRDotV, SpecularPower);
       */

    }
    float4 emissionColor = pow(emission, 3);

    outColor = saturate((ambientColor + diffuseColor) * albedo + specularColor + emissionColor);
  


	/*float4 dissolveMap = tex2D(DissolveSampler, texcoord);
	float dissolveValue = dissolveMap.x;

	if (dissolveValue <= DissolveAmount)
	{
		outColor = float4(0, 0, 0, 0);
	}
	else if ((dissolveValue <= DissolveAmount + FringeAmount) && DissolveAmount != 0)
	{
		if (outColor.a != 0.0f)
			outColor = outColor + float4(255, 255, 0, outColor.a);
	}
*/

  //  outColor = Dissolve(outColor, texcoord, DissolveAmount, FringeAmount);
    
}

void ColorMeshVS(float4 position : POSITION,
            float3 normal : NORMAL,
            out float4 outPosition : POSITION,
            out float3 outNormal : NORMAL,
            out float3 outViewDir : TEXCOORD0,
            out float3 outLightDir : TEXCOORD1)
{
    outPosition = mul(position, WorldMatrix);
    outPosition = mul(outPosition, ViewMatrix);
    outPosition = mul(outPosition, ProjMatrix);

    float4 worldPosition = mul(position, WorldMatrix);


    outLightDir = -normalize(LightDirection);

    outViewDir = normalize(CameraPosition.xyz - worldPosition.xyz);

    // 월드 법선 벡터 구하기
    float3 worldNormal = mul(normal, (float3x3)WorldMatrix);
    worldNormal = normalize(worldNormal);
    outNormal = worldNormal;
}
void ColorMeshPS(float3 normal : NORMAL,
            float3 viewDir : TEXCOORD0,
            float3 lightDir : TEXCOORD1,
            out float4 outColor : COLOR0)
{
    // normalization / 래스터라이저 보간을 했기 때문에 정규화를 다시 해준다.
    normal = normalize(normal);
    viewDir = normalize(viewDir);
    lightDir = normalize(lightDir);
    

    // ambient 
    float4 ambientColor = Ambient * AmbientIntensity;

    // diffuse
    float4 diffuseColor = Diffuse * DiffuseIntensity * dot(lightDir, normal);

    // specular
    float3 reflection = reflect(lightDir, normal);
    float4 specularColor = Specular * SpecularIntensity * pow(saturate(dot(reflection, viewDir)), SpecularPower);

    outColor = saturate((ambientColor + diffuseColor) * Color + specularColor);
}

void MeshNoLightVS(float4 position : POSITION,
            float2 texcoord : TEXCOORD0,
            out float4 outPosition : POSITION,
            out float2 outTexcoord : TEXCOORD0)
{
    outPosition = mul(position, WorldMatrix);
    outPosition = mul(outPosition, ViewMatrix);
    outPosition = mul(outPosition, ProjMatrix);

    outTexcoord = texcoord;
}

void MeshNoLightPS(
            float2 texcoord : TEXCOORD0,
            out float4 outColor : COLOR0)
{
    float4 albedo = tex2D(BaseSampler, texcoord);
    
    outColor = albedo;

}            

void ColorNoLightVS(float4 position : POSITION,
            out float4 outPosition : POSITION)
{
    outPosition = mul(position, WorldMatrix);
    outPosition = mul(outPosition, ViewMatrix);
    outPosition = mul(outPosition, ProjMatrix);

}
float4 ColorNoLightPS() : COLOR0
{
   return Color;
}
technique MeshShading
{
    pass P0
    {
        VertexShader = compile vs_3_0 MeshVS();
		PixelShader = compile ps_3_0 MeshPS();
    }
}


technique BumpShading
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpVS();
		PixelShader = compile ps_3_0 BumpPS();
    }
}

technique ColorMeshShading
{
    pass P0
    {
         VertexShader = compile vs_3_0 ColorMeshVS();
		PixelShader = compile ps_3_0 ColorMeshPS();
    }
}
technique ColorNoLight
{
    pass P0
    {
        VertexShader = compile vs_3_0 ColorNoLightVS();
		PixelShader = compile ps_3_0 ColorNoLightPS();
    }
}

technique MeshNoLight
{
    pass P0
    {
        VertexShader = compile vs_3_0 MeshNoLightVS();
		PixelShader = compile ps_3_0 MeshNoLightPS();
    }
}

