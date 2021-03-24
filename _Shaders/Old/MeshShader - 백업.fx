matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;



float4 Ambient;
float4 AmbientIntensity;
float4 Diffuse;
float4 DiffuseIntensity;
float4 Specular;
float4 SpecularIntensity;
float4 SpecularPower;
float4 LightDirection;

texture BaseTex;
sampler BaseSampler = sampler_state
{
	Texture = (BaseTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};



void MeshVS(float4 position : POSITION,
            float3 normal : NORMAL, 
            float2 texcoord : TEXCOORD0,
            out float4 outPosition : POSITION,
            out float3 outNormal : NORMAL,
            out float3 outViewPos : TEXCOORD0,
            out float3 outLightDir : TEXCOORD1,
            out float2 outTexcoord : TEXCOORD2)
{
    outPosition = mul(position, WorldMatrix);
    outPosition = mul(outPosition, ViewMatrix);
    outPosition = mul(outPosition, ProjMatrix);

    outLightDir = -normalize((float3)LightDirection);

    // 광원 계산을 view space에서 하기 위해
    // position과 normal값을 viewSpace로 옮겨준다.
    float4 viewPos = mul(position, WorldMatrix);
    viewPos = mul(viewPos, ViewMatrix);

    outViewPos = -normalize((float3)viewPos);

    float4 viewNormal = mul(float4(normal, 1), WorldMatrix);
    viewNormal = mul(viewNormal, ViewMatrix);

    outNormal = normalize((float3)viewNormal);

    outTexcoord = texcoord;
}

void MeshPS(float3 normal : NORMAL,
            float3 viewPos : TEXCOORD0,
            float3 lightDir : TEXCOORD1,
            float2 texcoord : TEXCOORD2,
            out float4 outColor : COLOR0)
{
    float4 baseMap = tex2D(BaseSampler, texcoord);

    // compute the reflection vector
    float3 reflect = normalize(2 * dot(normal, lightDir) * normal - lightDir);

    // compute ambient 
    float4 ambientColor = Ambient * AmbientIntensity;

    // Compute Diffuse
    float4 diffuseColor = Diffuse * DiffuseIntensity * max(0, dot(normal, lightDir));

    // compute specular 
    float4 specularColor = Specular * SpecularIntensity * pow(max(0, dot(reflect, viewPos)), SpecularPower);

    float4 finalColor = (ambientColor + diffuseColor) * baseMap + specularColor;

    outColor = finalColor;


}            


technique MeshShading
{
    pass P0
    {
        VertexShader = compile vs_3_0 MeshVS();
		PixelShader = compile ps_3_0 MeshPS();
    }
}