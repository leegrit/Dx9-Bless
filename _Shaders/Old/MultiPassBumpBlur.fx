// for vertex shader
vector LightPosition;
vector EyePosition;
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;


// For Pixel Shader
float4 Ambient;
float4 Specular;
float4 Diffuse;
float SpecularPower;

sampler2D BaseMap;
sampler2D BumpMap;
sampler2D EmissionMap;




struct VS_INPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal : NORMAL0;
	float3 binormal : BINORMAL0;
	float3 tangent : TANGENT0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
	float3 viewDirection : TEXCOORD1;
	float3 lightDirection : TEXCOORD2;
};

struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
	float3 viewDirection : TEXCOORD1;
	float3 lightDirection : TEXCOORD2;
};



VS_OUTPUT bumpVS_main(VS_INPUT input)
{
	

    VS_OUTPUT output;



    // 입력받은 버텍스 위치를 월드 공간으로 변환한다.
    output.position = mul(input.position, WorldMatrix);
    output.position = mul(output.position,ViewMatrix);
    output.position = mul(output.position, ProjMatrix);

    // UV값은 그대로 넘겨준다.
    output.texcoord = input.texcoord;


    // object Position은 view space까지 변환한다. (계산을 위함)
    float3 objectPosition = (float3)mul(input.position, WorldMatrix);
    objectPosition = mul(objectPosition, (float3x3)ViewMatrix);

    // 여기서 EyePosition은 ViewSpace에 존재한다.
    // projection 연산을 거치지 않은 값이기 때문
    // EyePosition과 objectPosition을 통해 방향을 구한다.
    // eye(camera)에서 오브젝트 바라보는 방향
    float3 viewDirection = (float3)EyePosition - objectPosition;
    float3 lightDirection = (float3)LightPosition - objectPosition;

    // 여기서 각 normal, binormal, tangent를 뷰스페이스 까지만
    // 계산하는 이유가 뭘까 - 단순 계산을 위해서?
    // 어차피 이 값은 direction 연산용으로만 쓰이고 사용되지 않는다.
    // 굳이 프로젝션 연산까지 해줄 필요가 없음 
    float3 normal = mul(input.normal, (float3x3)WorldMatrix);
    normal = mul(normal, (float3x3)ViewMatrix);
    float3 binormal = mul(input.binormal, (float3x3)WorldMatrix);
    binormal = mul(binormal, (float3x3)ViewMatrix);
    float3 tangent = mul(input.tangent, (float3x3)WorldMatrix);
    tangent = mul(tangent, (float3x3)ViewMatrix );

    output.viewDirection.x = dot(tangent, viewDirection);
    output.viewDirection.y = dot(binormal, viewDirection);
    output.viewDirection.z = dot(normal, viewDirection);

    output.lightDirection.x = dot(tangent, lightDirection);
    output.lightDirection.y = dot(binormal, lightDirection);
    output.lightDirection.z = dot(normal, lightDirection);

    return output;
}


float4 bumpPS_main(PS_INPUT input) : COLOR0
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
	
	float4 emissionMap = tex2D(EmissionMap, input.texcoord);

	//emissionMap = emissionMap * 3;

    float4 ret = saturate(totalAmbient + totalDiffuse + totalSpecular + emissionMap);
    ret.w = emissionMap.w;

    return ret;
}



struct BlurInput




technique Default_Technique
{
	pass BumpMapping
	{
		VertexShader = compile vs_3_0 bumpVS_main();
		PixelShader = compile ps_3_0 bumpPS_main();
	}
    pass Blur
    {

    }
};