// 원래 float3이였는데
// SetVector로 Set이 가능해서 바꿈
vector LightPosition;
vector EyePosition;
matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;

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

VS_OUTPUT main(VS_INPUT input)
{
   // float3 tangent;
    //float3 binormal;
   // float3 c1 = cross(input.normal, float3(0, 0, 1));
    //float3 c2 = cross(input.normal, float3(0, 1, 0));
  


    VS_OUTPUT output;



    // 입력받은 버텍스 위치를 월드 공간으로 변환한다.
    output.position = mul(input.position, WorldMatrix);
    output.position = mul(output.position,ViewMatrix);
    output.position = mul(output.position, ProjMatrix);

    // UV값은 그대로 넘겨준다.
    output.texcoord = input.texcoord;
    output.viewDirection = float3(0, 0, 0);
    output.lightDirection = float3(0, 0, 0);
    
    return output;

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