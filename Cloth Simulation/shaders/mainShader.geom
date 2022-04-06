#version 440 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in vec3 vertWorldPos[];
in vec3 vertWorldNormal[];
in vec2 vertTexCoords[];

out vec3 fragWorldPos;
out vec3 fragWorldNormal;
out vec2 fragTexCoords;

void main() {
	//pass the triangle
	
	for(int i = 0; i < 3; i++){
		gl_Position = gl_in[i].gl_Position;
		fragWorldPos = vertWorldPos[i];
		fragWorldNormal = vertWorldNormal[i];
		fragTexCoords = vertTexCoords[i];
		EmitVertex();
	}
	EndPrimitive();
	
	
	//add another triangle with opposite normal
	for(int i = 2; i >= 0; i--){
		//gl_Position = projection * view * model * (gl_in[i].gl_Position + vec4(0.0, 0.0, +0.0004, 0.0)); //this reduces z fighting
		gl_Position = gl_in[i].gl_Position; //no z fighting since backfaces are culled
		fragWorldPos = vertWorldPos[i];
		fragWorldNormal = -vertWorldNormal[i];
		fragTexCoords = vertTexCoords[i];
		EmitVertex();
	}
	EndPrimitive();
	
}
