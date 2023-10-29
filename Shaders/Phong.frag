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
	return dot_product; // Difuzn� slo�ka sv�tla
}

void main(){
	vec3 lightVector;
	vec3 diffuse;

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
			float theta = dot(lights[i].lightDir, normalize(-lights[i].position));
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
	vec4 oColor=vec4(objectColor,1.0);
	vec3 viewDir = normalize(cameraPos - vec3(ex_WorldPos)); // V
	vec3 reflectDir = reflect(-lightVector, ex_WorldNormal); // R
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // ��m d�le t�m men�� odraz
	//float specularStrength = 0.5;
	//vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f); // posledn� slo�ka je barva sv�tla
	//frag_colour = ambient + diffuse + vec4(specular,1.f)+spec;
	//frag_colour = ambient + (vec4(diffuse, 1.0) * texture(textureUnitID, uv)) + spec;
	frag_colour =ambient + (vec4(diffuse, 1.0) * texture(textureUnitID, uv)) + spec;
};