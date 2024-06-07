#version 410 core

// Estrutura da fonte de luz ambiente global
struct AmbientLight {
    vec3 ambient; // Componente de luz ambiente global
};

// Estrutura de uma fonte de luz direcional
struct DirectionalLight {
    vec3 direction;     // Direção da luz, espaço do mundo

    vec3 ambient;       // Componente de luz ambiente
    vec3 diffuse;       // Componente de luz difusa
    vec3 specular;      // Componente de luz especular
};

// Estrutura de uma fonte de luz pontual
struct PointLight {
    vec3 position;      // Posição do ponto de luz, espaço do mundo

    vec3 ambient;       // Componente de luz ambiente
    vec3 diffuse;       // Componente de luz difusa
    vec3 specular;      // Componente de luz especular

    float constant;     // Coeficiente de atenuação constante
    float linear;       // Coeficiente de atenuação linear
    float quadratic;    // Coeficiente de atenuação quadrática
};

// Estrutura de uma fonte de luz cónica
struct SpotLight {
    vec3 position;      // Posição do foco de luz, espaço do mundo

    vec3 ambient;       // Componente de luz ambiente
    vec3 diffuse;       // Componente de luz difusa
    vec3 specular;      // Componente de luz especular

    float constant;     // Coeficiente de atenuação constante
    float linear;       // Coeficiente de atenuação linear
    float quadratic;    // Coeficiente de atenuação quadrática

    float spotCutoff, spotExponent;
    vec3 spotDirection;
};

struct Material {
    vec3 emissive;
    vec3 ambient;       // Ka
    vec3 diffuse;       // kd
    vec3 specular;      // ke
    float shininess;
};

uniform mat4 View;
uniform mat4 Model;

uniform sampler2D textureMapping;

uniform int EnabledLights[4];
uniform AmbientLight ambientLight; // Fonte de luz ambiente global
uniform DirectionalLight directionalLight; // Fonte de luz direcional
uniform PointLight pointLight[2]; // Duas fontes de luz pontual
uniform SpotLight spotLight; // Fonte de luz cónica

uniform Material material;

in vec3 vPositionEyeSpace;
in vec3 normalMapping;
in vec2 uvMapping;
vec3 diffuseColor;

out vec4 fColor; // Cor final do fragmento

vec4 calcAmbientLight(AmbientLight);
vec4 calcDirectionalLight(DirectionalLight, out vec4);
vec4 calcPointLight(PointLight, out vec4);
vec4 calcSpotLight(SpotLight, out vec4);

void main() {
    // Cor do Material
    diffuseColor = texture(textureMapping, uvMapping).rgb;

    // Cálculo da componente emissiva do material.
    vec4 emissive = vec4(material.emissive, 1.f);

    // Luz Ambiente Global
    vec4 ambient = vec4(0.f);

    // Cálculo do efeito da iluminação no fragmento.
    int totalEnabledLights = 0;
    vec4 lights[4];

    // Contribuição da fonte de luz ambiente
    if (EnabledLights[0] == 1)
        ambient = calcAmbientLight(ambientLight);

    // Contribuição da fonte de luz direcional
    if (EnabledLights[1] == 1)
        ambient += calcDirectionalLight(directionalLight, lights[totalEnabledLights++]);

    // Contribuição de cada fonte de luz Pontual
    if (EnabledLights[2] == 1)
        for(int i = 0; i < 2; i++)
            ambient += calcPointLight(pointLight[i], lights[totalEnabledLights++]);

    // Contribuição da fonte de luz cónica
    if (EnabledLights[3] == 1)
        ambient += calcSpotLight(spotLight, lights[totalEnabledLights++]);

    // Cálculo da cor final do fragmento.
    fColor = emissive + ambient / totalEnabledLights;

    for(int i = 0; i < totalEnabledLights; i++)
        fColor += lights[i];
}

vec4 calcAmbientLight(AmbientLight light) {
    // Cálculo da contribuição da fonte de luz ambiente global, para a cor do objeto.
    return vec4(material.ambient * light.ambient, 1.f);
}

vec4 calcDirectionalLight(DirectionalLight light, out vec4 var) {
    // Cálculo da reflexão da componente da luz difusa.
    vec3 lightDirectionEyeSpace = (View * vec4(light.direction, 0.f)).xyz;
    vec3 L = normalize(-lightDirectionEyeSpace); // Direção inversa à da direção luz.
    float NdotL = max(dot(normalMapping, L), 0.f);
    vec4 diffuse = vec4(diffuseColor * light.diffuse, 1.f) * NdotL;

    // Cálculo da reflexão da componente da luz especular.
    vec3 V = normalize(-vPositionEyeSpace);
    vec3 R = reflect(-L, normalMapping);
    float RdotV = max(dot(R, V), 0.f);
    vec4 specular = pow(RdotV, material.shininess) * vec4(light.specular * material.specular, 1.f);

    var = diffuse + specular;

    // Cálculo da reflexão da componente da luz ambiente.
    return calcAmbientLight(AmbientLight(light.ambient));
}

vec4 calcPointLight(PointLight light, out vec4 var) {
    // Cálculo da reflexão da componente da luz difusa.
    vec3 lightPositionEyeSpace = (View * vec4(light.position, 1.f)).xyz;
    vec3 L = normalize(lightPositionEyeSpace - vPositionEyeSpace);
    float NdotL = max(dot(normalMapping, L), 0.f);
    vec4 diffuse = vec4(diffuseColor * light.diffuse, 1.f) * NdotL;

    // Cálculo da reflexão da componente da luz especular.
    vec3 V = normalize(-vPositionEyeSpace);
    vec3 R = reflect(-L, normalMapping);
    float RdotV = max(dot(R, V), 0.f);
    vec4 specular = pow(RdotV, material.shininess) * vec4(light.specular * material.specular, 1.f);

    // Atenuação
    float dist = length(lightPositionEyeSpace - vPositionEyeSpace);
    float attenuation = 1.f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    var = attenuation * (diffuse + specular);

    // Cálculo da reflexão da componente da luz ambiente.
    return calcAmbientLight(AmbientLight(light.ambient));
}

vec4 calcSpotLight(SpotLight light, out vec4 var) {
    // Cálculo da reflexão da componente da luz difusa.
    vec3 lightPositionEyeSpace = (View * vec4(light.position, 1.f)).xyz;
    vec3 L = normalize(lightPositionEyeSpace - vPositionEyeSpace);
    float NdotL = max(dot(normalMapping, L), 0.f);
    vec4 diffuse = vec4(diffuseColor * light.diffuse, 1.f) * NdotL;

    // Cálculo da reflexão da componente da luz especular.
    vec3 V = normalize(-vPositionEyeSpace);
    vec3 R = reflect(-L, normalMapping);
    float RdotV = max(dot(R, V), 0.f);
    vec4 specular = pow(RdotV, material.shininess) * vec4(light.specular * material.specular, 1.f);

    // Atenuação
    float dist = length(lightPositionEyeSpace - vPositionEyeSpace);
    float attenuation = 1.f / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    // Contribuição do ângulo do cone
    float spotEffect = dot(normalize(-L), normalize(light.spotDirection));
    if (spotEffect > cos(radians(light.spotCutoff)))
        attenuation *= pow(spotEffect, light.spotExponent);
    else
        attenuation = 0.f;

    var = attenuation * (diffuse + specular);

    // Cálculo da reflexão da componente da luz ambiente.
    return calcAmbientLight(AmbientLight(light.ambient));
}
