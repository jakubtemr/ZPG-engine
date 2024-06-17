#version 400
#define MAX_LIGHTS 4

struct Light {
	int type;
    vec3 position;
	vec3 barva;
	vec3 lightDir;
	float cutOff;
};

uniform sampler2D textureUnitID;
uniform int lightsCount;
uniform Light lights[MAX_LIGHTS];

uniform vec3 cameraPos;
uniform vec3 objectColor;
uniform vec3 ambientColor;

in vec4 ex_WorldPos;
in vec3 ex_WorldNormal;
in vec2 uv;

out vec4 frag_colour;

float lightCalc(vec3 lightVector){
    float dot_product = max(dot(lightVector, normalize(ex_WorldNormal)), 0.0);
    
    if(dot_product < 0.0) return 0.0; 

    return dot_product; 
}

void main(){
	vec3 lightVector;
	vec4 texColor = texture(textureUnitID, uv);
	//vec3 diffuse=texColor.rgb;
	vec3 diffuse = vec3(0.5);

	for(int i = 0; i < lightsCount; i++) {
		if(lights[i].type == 0){
			lightVector = normalize(lights[i].position - vec3(ex_WorldPos));
			diffuse += ((lightCalc(lightVector) * lights[i].barva));
		}
		else if(lights[i].type == 1) {
			lightVector = normalize(-lights[i].position);
			diffuse += ((lightCalc(lightVector) * lights[i].barva));
		}
		else if(lights[i].type == 2) {
			//float theta = dot(lights[i].lightDir, normalize(-lights[i].position));
			//lightVector = normalize(lights[i].position - vec3(ex_WorldPos));
			lightVector = normalize(cameraPos - vec3(ex_WorldPos));
			//lightVector = normalize(ex_WorldPos.xyz - lights[i].position);
			//float theta = dot(normalize(lights[i].lightDir), normalize(lightVector));
			float theta = dot(normalize(lights[i].lightDir), normalize(lightVector));

			if(theta > lights[i].cutOff) 
			{       
				diffuse += (lightCalc(lightVector) * lights[i].barva);
			}
		else{
			diffuse += (lightCalc(vec3 (0.f,0.f,0.f)) * lights[i].barva);
			}
		}
	}

	vec4 ambient = vec4( ambientColor, 1.0);
	vec3 viewDir = normalize(cameraPos - vec3(ex_WorldPos)); 
	vec3 reflectDir = reflect(-lightVector, ex_WorldNormal); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); 

	frag_colour = ambient + (vec4(diffuse, 1.0) * texture(textureUnitID, uv)) + spec;
};