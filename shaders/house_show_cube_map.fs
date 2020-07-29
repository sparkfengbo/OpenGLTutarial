#version 330 core

precision highp float;
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform sampler2D topBrand;
uniform sampler2D bottomDirection;

void main()
{
    float absX = abs(TexCoords.x);
    float absY = abs(TexCoords.y);
    float absZ = abs(TexCoords.z);
    int isXPositive = TexCoords.x > 0 ? 1 : 0;
    int isYPositive = TexCoords.y > 0 ? 1 : 0;
    int isZPositive = TexCoords.z > 0 ? 1 : 0;

    // POSITIVE Y
    if (bool(isYPositive) && absY >= absX && absY >= absZ) {
        if(absX <= 0.5 && absZ <= 0.5) {
            vec4 skyColor = texture(skybox, TexCoords);
            vec4 signalColor = texture(topBrand, vec2(-TexCoords.x + 0.5, TexCoords.z + 0.5));
            if (signalColor.a < 0.001) {
                FragColor = skyColor;
            } else {
                float factor = 0.4f;
                float r = skyColor.r * factor + signalColor.r *(1-factor) ;
                float g = skyColor.g * factor + signalColor.g *(1-factor);
                float b = skyColor.b * factor + signalColor.b *(1-factor);
                if (signalColor.r >= 0.6) {
                     FragColor = vec4(r, g, b, 1);
                } else {
                     FragColor = vec4(skyColor.r,skyColor.g,skyColor.b, 1);
                }
            }
        } else {
            FragColor = texture(skybox, TexCoords);
        }
    }
    // NEGATIVE Y
    else if (!bool(isYPositive) && absY >= absX && absY >= absZ) {
        if(absX <= 0.5 && absZ <= 0.5) {
            vec4 skyColor = texture(skybox, TexCoords);
            vec4 signalColor = texture(bottomDirection, vec2(-TexCoords.x + 0.5, TexCoords.z + 0.5));
            if (signalColor.a < 0.001) {
                FragColor = skyColor;
            } else {
                float factor = 0.4f;
                float r = skyColor.r * factor + signalColor.r *(1-factor) ;
                float g = skyColor.g * factor + signalColor.g *(1-factor);
                float b = skyColor.b * factor + signalColor.b *(1-factor);
                if (signalColor.r >= 0.6) {
                     FragColor = vec4(r, g, b, 1);
                } else {
                     FragColor = vec4(skyColor.r,skyColor.g,skyColor.b, 1);
                }
            }
        } else {
            FragColor = texture(skybox, TexCoords);
        }
    }
    else {
        FragColor = texture(skybox, TexCoords);
    }
}