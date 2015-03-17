#version 410

layout(location=0) in vec3 v_position;
layout(location=1) in vec3 v_normal;

// normalMatrix = transpose(inverse(mvMatrix))
layout(std140) uniform Matrices
{
    uniform mat4 mvpMatrix;
    uniform mat4 mvMatrix;
    uniform mat4 normalMatrix;
} matrices;

out vec3 f_position;
out vec3 f_normal;

void main()
{
    // we want the position and normal in view coordinates not projection
    f_position = (matrices.mvMatrix * vec4(v_position,1.0)).xyz;
    f_normal = normalize(matrices.normalMatrix * vec4(v_normal,1.0)).xyz;
    gl_Position = matrices.mvpMatrix * vec4(v_position,1.0);
}

