#version 330 core 

vec3[3] vertices = vec3[3](
	vec3(-0.5, -0.5, 0.0),
	vec3(0.0, 0.5, 0.0),
	vec3(0.5, -0.5, 0.0)
);

void main()
{
	vec3 pos = vertices[gl_VertexID];
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}