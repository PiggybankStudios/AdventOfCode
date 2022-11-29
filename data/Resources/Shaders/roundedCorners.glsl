//======================== VERTEX_SHADER ========================

#version 130

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec2 Texture1Size;
uniform vec4 SourceRec1;

// layout(location = 0) 
in vec3 inPosition;
in vec4 inColor1;
in vec2 inTexCoord1;

out vec4 fColor1;
out vec2 fTexCoord1;
out vec2 fSampleCoord;
out vec3 fPosition;

void main()
{
	fPosition = inPosition;
	fColor1 = inColor1;
	fTexCoord1 = inTexCoord1;
	fSampleCoord = (SourceRec1.xy + (inTexCoord1 * SourceRec1.zw)) / Texture1Size;
	mat4 transformMatrix = ProjectionMatrix * (ViewMatrix * WorldMatrix);
	gl_Position = transformMatrix * vec4(inPosition, 1.0);
}

//======================== FRAGMENT_SHADER ========================

#version 130

uniform sampler2D Texture1;
uniform vec2 Texture1Size;

uniform vec4 Color1;
uniform float CircleRadius;
uniform vec2 ShiftVec; //used as rectangle size (aspect ratio and resolution info so we can interpret CircleRadius correctly)

in vec4 fColor1;
in vec2 fTexCoord1;
in vec2 fSampleCoord;
in vec3 fPosition;

out vec4 Result;

void main()
{
	vec4 sampleColor = texture(Texture1, fSampleCoord);
	Result = fColor1 * Color1 * sampleColor;
	vec2 worldCoord = vec2(fTexCoord1.x * ShiftVec.x, fTexCoord1.y * ShiftVec.y);
	
	if (worldCoord.x < CircleRadius && worldCoord.y < CircleRadius)
	{
		float distFromCenter = length(worldCoord - vec2(CircleRadius, CircleRadius));
		float smoothDelta = fwidth(distFromCenter);
		Result.a *= smoothstep(CircleRadius, CircleRadius-smoothDelta, distFromCenter);
	}
	if (worldCoord.x > ShiftVec.x - CircleRadius && worldCoord.y < CircleRadius)
	{
		float distFromCenter = length(worldCoord - vec2(ShiftVec.x - CircleRadius, CircleRadius));
		float smoothDelta = fwidth(distFromCenter);
		Result.a *= smoothstep(CircleRadius, CircleRadius-smoothDelta, distFromCenter);
	}
	if (worldCoord.x > ShiftVec.x - CircleRadius && worldCoord.y > ShiftVec.y - CircleRadius)
	{
		float distFromCenter = length(worldCoord - vec2(ShiftVec.x - CircleRadius, ShiftVec.y - CircleRadius));
		float smoothDelta = fwidth(distFromCenter);
		Result.a *= smoothstep(CircleRadius, CircleRadius-smoothDelta, distFromCenter);
	}
	if (worldCoord.x < CircleRadius && worldCoord.y > ShiftVec.y - CircleRadius)
	{
		float distFromCenter = length(worldCoord - vec2(CircleRadius, ShiftVec.y - CircleRadius));
		float smoothDelta = fwidth(distFromCenter);
		Result.a *= smoothstep(CircleRadius, CircleRadius-smoothDelta, distFromCenter);
	}
}