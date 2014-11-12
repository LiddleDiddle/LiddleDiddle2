#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main() {

    //cos(x) returns a number between -1 and 1. To convert it into the range 0 to 1
    //you simply do (cos(x) + 1.0) * 0.5
    
    vec4 textureColor = texture(mySampler, fragmentUV);
    
    //Make crazy colors using time and position!
    color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5,
                 fragmentColor.g * (cos(fragmentPosition.y * 8.0 + time) + 1.0) * 0.5,
                 fragmentColor.b * (cos(fragmentPosition.x * 2.0 + time) + 1.0) * 0.5, fragmentColor.a) * textureColor;
}