#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 aColor;

out vec4 ourColor;
out vec2 texCoords;

uniform mat4 u_Transformation;

void main() {
	gl_Position = u_Transformation * vec4(position.xyz, 1.0f);
	texCoords = tex;
	ourColor = vec4(aColor.xyz, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoords;
in vec4 ourColor;

uniform sampler2D u_Texture;
uniform sampler2D u_OtherTexture;

void main() {
    vec4 texColor = mix(texture(u_Texture, texCoords), texture(u_OtherTexture, texCoords), 0.5);
	color = texColor * ourColor;
}