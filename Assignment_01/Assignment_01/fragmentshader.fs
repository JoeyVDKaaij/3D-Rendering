#version 330

in vec3 fColor;
in float fIncrement;
in float fColumns;
in float fRows;
in float fClock;
in float fScaleSpeed;
in vec2 fMousePosition;
in float fDistance;
out vec4 sColor;


void main (void)
{
    float scale = sin(fClock / 1000 * fScaleSpeed);

    vec2 procUV = vec2((fColor.x - 0.5) * scale, (fColor.y - 0.5) * scale);

    float xCell = floor(procUV.x * fColumns);
    float yCell = floor(procUV.y * fRows);

    float checker = mod(xCell + yCell, 2.0);

    vec2 colorPosition = fColor.xy;
    colorPosition /= 2;
    colorPosition += 0.25;

    vec2 vecDistance = colorPosition - fMousePosition;
    float distanceLength = sqrt(pow(vecDistance.x, 2.0) + pow(vecDistance.y, 2.0));
    float visibilityDistance = distanceLength / fDistance;

    checker *= 1 - visibilityDistance;

    // Output to screen
    sColor = vec4(checker, checker, checker, 1.0);
}

