#vertexShader
#version 330 core
layout(location = 0)in vec3 pos;
layout(location = 1)in vec2 texCoord;

uniform mat4 _proj;
uniform mat4 _view;
uniform mat4 _model;

out vec2 texCoord0;

void main()
{
	gl_Position = _proj * _view * _model * vec4(pos, 1);
	// gl_Position = vec4(pos, 1);
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
	// color = vec4(1, 1, 1, 1);
}