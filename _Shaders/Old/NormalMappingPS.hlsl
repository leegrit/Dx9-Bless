float4 Ambient;
float4 Specular;
float4 Diffuse;
float SpecularPower;

sampler2D BaseMap;
sampler2D BumpMap;

struct PS_INPUT
{
    float2 texcoord : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
    float3 lightDirection : TEXCOORD2;
};

float4 main(PS_INPUT input) : COLOR0
{
   
    
    float3 lightDirection = normalize(input.lightDirection);
    float3 normal = normalize((tex2D(BumpMap, input.texcoord).xyz * 2.0f) - 1.0f);
    float NDotL = dot(normal, lightDirection);

    float3 reflection = normalize(((2.0f * normal) * (NDotL)) - lightDirection);
    float3 viewDirection = normalize(input.viewDirection);
    float RDotV = max(0.0f, dot(reflection, viewDirection));

    float4 baseColor = tex2D(BaseMap, input.texcoord);

    float4 totalAmbient = Ambient * baseColor;
    float4 totalDiffuse = Diffuse * NDotL * baseColor;
    float4 totalSpecular = Specular * pow(RDotV, SpecularPower);


 //return float4(255, 0, 0, 255);
//return saturate(baseColor);
    //return saturate(totalAmbient + totalDiffuse + totalSpecular);
return float4(255, 0, 0, 255);
    //return totalAmbient;
}