#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 aColor;

out vec4 ourColor;
out vec2 texCoords;

void main() {
	gl_Position = position;
	texCoords = tex;
	ourColor = vec4(aColor.xyz, 1.0);
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