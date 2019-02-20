#vertexShader
#version 330 core
layout(location = 0)in vec3 pos;
layout(location = 1)in vec2 texCoord;

uniform mat4 _proj;
uniform mat4 _view;

out vec2 texCoord0;

void main()
{
	gl_Position = _proj * _view * vec4(pos, 1);
	texCoord0 = texCoord;
}

#fragmentShader
#version 330 core
layout(location = 0)out vec4 color;

uniform sampler2D _texture;

in vec2 texCoord0;

void main()
{
	color = texture2D(_texture, texCoord0);
}