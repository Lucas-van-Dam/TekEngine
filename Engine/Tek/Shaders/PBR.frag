#version 460 core

#define PI 3.1415926535897932384626433832795

layout(binding = 5) uniform samplerCube skyboxCube;
layout(binding = 6) uniform samplerCube irradianceMap;
layout(binding = 7) uniform samplerCube shadowCubes[10];



out vec4 FragColor;

in vec2 TexCoords;
in vec3 fragPosition;
in vec3 fragViewPos;
in vec4 fragLightSpacePos;
in vec3 fragNormal;

in vec3 T;
in vec3 Normal;

struct Light{
    //W = type
    vec4 position;
    //W = cutOff
    vec4 direction;
    //W = intensity
    vec4 lightColor;
    //directional light only
    mat4 projection;
    mat4 view;
};

layout(std140, binding = 1) buffer LightingBuffer {
    Light lights[];
};

uniform sampler2D texture_albedo;
uniform sampler2D texture_normal;
uniform sampler2D texture_roughness;
uniform sampler2D texture_metallic;

uniform bool useAlbedoTexture = true;
uniform bool useRoughnessTexture = true;
uniform bool useMetallicTexture = true;
uniform bool useNormalTexture = true;

uniform vec4 albedo;
uniform float roughness = -1;
uniform float metallic = -1;

float roughnessInternal;
float metallicInternal;

uniform sampler2D shadowMap;

uniform float far_plane;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
void main()
{
    vec3 V    = normalize(fragViewPos - fragPosition);
    vec3 N = normalize(Normal);
    vec3 fragTangent = normalize(T);
    fragTangent = normalize(fragTangent - dot(fragTangent, N) * N);
    vec3 fragBiTangent = cross(N, fragTangent);

    mat3 TBN = mat3(fragTangent, fragBiTangent, N);

    vec4 diffuseColor = useAlbedoTexture ? texture(texture_albedo, TexCoords).xyzw : albedo;

    roughnessInternal = useRoughnessTexture ? texture(texture_roughness, TexCoords).r : roughness;
    metallicInternal = useMetallicTexture ? texture(texture_metallic, TexCoords).r : metallic;

    N = useNormalTexture ? texture(texture_normal, TexCoords).rgb : N;
    //normal.y * -1;
    //normal = normalize(normal * 2.0 - 1.0);
    //normal = normalize((TBN) * normal);
    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo.xyz, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 1; i < lights.length(); i++)
    {
        // calculate per-light radiance
        vec3 L = normalize(lights[i].position.xyz - fragPosition);
        vec3 H = normalize(V + L);
        float distance = length(lights[i].position.xyz - fragPosition);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lights[i].lightColor.xyz * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);
        float G   = GeometrySmith(N, V, L, roughness);
        vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;

        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);

        // add to outgoing radiance Lo
        Lo += (kD * albedo.xyz / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }

    vec3 kS = fresnelSchlick(max(dot(N, V), 0.0), F0);
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;
    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse      = irradiance * albedo.rgb;
    vec3 ambient = (kD * diffuse);

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
}