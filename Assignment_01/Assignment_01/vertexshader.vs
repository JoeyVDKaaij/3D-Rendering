#version 330

in vec3 vertex;
in vec3 color;
uniform vec2 offset;
uniform float increment = 0;
uniform int columns = 3;
uniform int rows = 3;
uniform float clock = 0;
uniform float scaleSpeed = 1;
uniform vec2 mousePosition;
uniform float distance;

out vec3 fColor;
out float fIncrement;
out float fColumns;
out float fRows;
out float fClock;
out float fScaleSpeed;
out vec2 fMousePosition;
out float fDistance;

void main (void) {
    gl_Position = vec4(vertex,1) + vec4(offset,0,0);
    fColor = color;
    fIncrement = increment;
    fColumns = columns;
    fRows = rows;
    fClock = clock;
    fMousePosition = mousePosition;
    fDistance = distance;
    fScaleSpeed = scaleSpeed;
}

