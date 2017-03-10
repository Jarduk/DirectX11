cbuffer S_VSConstantBuffer
{
    matrix World;
    matrix View;
    matrix Projection;
};

cbuffer S_PSConstantBuffer
{
    float3 ViewDirection;
    float3 PointLightPosition;
    float4 AmbientLight;
    float4 LightColor;
    float  PointLightRange;
};

struct VS_INPUT
{
    float3 Position  : POSITION;
    float3 Normal    : NORMAL;
    float4 Color     : COLOR;
};

struct PS_INPUT
{
    float4 Position  : SV_POSITION;
    float3 Normal    : NORMAL;
    float4 Color     : COLOR;
    float3 WorldPos  : TEXCOORD;
};

PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;

    output.Position = mul(float4(input.Position, 1), World);
    output.WorldPos = output.Position.xyz;
    output.Position = mul(mul(output.Position, View), Projection);

    output.Normal = mul(input.Normal, (float3x3)World).xyz;

    output.Color = input.Color;

    return output;
}

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
    // return input color if no light is set
    if (PointLightRange <= 0)
    return input.Color;

    // get vector from the worldpos for this pixel to the pointlight position
    float3 lightDirection = PointLightPosition - input.WorldPos;

    // get distance
    float lightDistance = length(lightDirection);

    // apply ambient light
    float4 finalColor = float4(input.Color.rgb * AmbientLight.rgb * AmbientLight.a, 1);

    // if does't reach the position, return the color
    if (lightDistance > PointLightRange)
    return finalColor;

    // normalize so that it represents the direction
    lightDirection = normalize(lightDirection);

    input.Normal = normalize(input.Normal);

    // Calculate how much light the pixel gets by its angle to the light
    float lightAmount = dot(lightDirection, input.Normal);

    // if light hits the front side of the pixel
    if (lightAmount > 0.0f)
    {
        //calculate attenuation
        float attenuation = saturate(lightDistance / PointLightRange);
        attenuation *= attenuation;
        attenuation = 1 / (1 + 25 * attenuation) * saturate(4 * (1 - attenuation));

        // multiply light color with its intensity
        float3 lightColor = LightColor.rgb * LightColor.a;

        // add light to the final color of the pixel
        finalColor += float4(lightAmount * input.Color.rgb * lightColor * attenuation, input.Color.a);

        // add specular
        float3 Rn = reflect(lightDirection, input.Normal);
        finalColor = float4(finalColor.rgb + lightColor * pow(saturate(dot(Rn, normalize(ViewDirection))), 5) * attenuation, finalColor.a);
        finalColor = saturate(finalColor);
    }

    return finalColor;
}