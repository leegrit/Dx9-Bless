//https://m.blog.naver.com/PostView.nhn?blogId=since860321&logNo=130176043844&proxyReferer=https:%2F%2Fwww.google.com%2F
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

float4 CameraPosition;
float4 LightDirection;

// light properties
float4 Ambient;
float4 AmbientIntensity;
float4 Diffuse;
float4 DiffuseIntensity;
float4 Specular;
float4 SpecularIntensity;
float4 SpecularPower;

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

    // 물체로 들어오는 빛의 방향 벡터를 월드 공간으로 변환하고
    // 이후 내적을 위해 역 방향으로 방향을 바꿔준다.
    float3 worldPos = mul(position, WorldMatrix);
    outLightDir = -normalize(LightDirection);

    // 물체를 바라보는 시선 벡터를 월드공간으로 변환한다.
    float3 worldEyeDir = CameraPosition.xyz - worldPos.xyz;
    outViewDir = normalize(worldEyeDir);

    // 노말값 월드공간으로
    float3 worldNormal = mul(normal, (float3x3)WorldMatrix);
    outNormal = normalize(worldNormal);

    // 탄젠트값 월드공간으로
    float3 worldTangent = mul(tangent, (float3x3)WorldMatrix);
    outTangent = normalize(worldTangent);

    // 바이노말값 월드공간으로.
    float3 worldBinormal = mul(binormal, (float3x3)WorldMatrix);
    outBinormal = normalize(worldBinormal);
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
    float4 diffuseColor = Diffuse * DiffuseIntensity * saturate(dot(lightDir, worldNormal));

    float3 reflection = reflect(lightDir, worldNormal);
    float4 specularColor = Specular * SpecularIntensity * pow(saturate(dot(reflection, viewDir)), SpecularPower);

    float4 emissionColor = pow(emission, 3);

    outColor = (ambientColor + diffuseColor) * albedo + specularColor + emissionColor;
  
}


technique BumpShading
{
    pass P0
    {
        VertexShader = compile vs_3_0 BumpVS();
		PixelShader = compile ps_3_0 BumpPS();
    }
}