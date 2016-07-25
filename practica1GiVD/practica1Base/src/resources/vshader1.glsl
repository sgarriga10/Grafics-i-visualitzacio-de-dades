#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif


IN vec4 vPosition;
IN vec4 vColor;
IN vec4 vNormal;
IN vec2 vCoordTexture;


OUT vec4 color;
OUT vec2 v_texcoord;

struct tipusLlum{
    vec4 position;
    vec4 direction;
    float angle;
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
    float a, b, c;
    bool on;
};

struct tipusMaterial{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 ambiGlobal;
uniform tipusMaterial material;
uniform  bool textureOn;
vec3 obs = vec3(0,0,10);
//uniform tipusLlum puntual;
//uniform tipusLlum direccional;
//uniform tipusLlum spotlight;
uniform tipusLlum glLlums[3]; //0 puntual, 1 direccional, 2 Spotlight



vec3 calculaAmbiental(int x){
    vec3 amb = glLlums[x].ambient * material.ambient;
    return amb;
}

vec3 calculaDiffuse(int x){
    vec3 dif = glLlums[x].diffuse * material.diffuse;
    return dif;
}

vec3 calculaSpecular(int x){
    vec3 spe = glLlums[x].specular * material.specular;
    return spe;
}

vec3 calculaFormulaPre(int x){
    vec3 amb = calculaAmbiental(x);
    vec3 dif = calculaDiffuse(x);
    vec3 spe = calculaSpecular(x);
    float atenuacion;
    vec3 L;
    if(x == 0) L= normalize(glLlums[x].position.xyz - vPosition.xyz);
    if(x == 1) L = normalize(glLlums[x].direction.xyz);
    if(x == 2) {
        L = normalize(glLlums[x].position.xyz - vPosition.xyz);
        float cos = dot(glLlums[x].direction.xyz, L);
        if(cos <= glLlums[x].angle) {
            return vec3(glLlums[x].ambient * material.ambient);
        }
    }
    vec3 V = normalize(obs - vPosition.xyz);
    vec3 H = normalize(V+L);
    float d = length(glLlums[x].position.xyz - vPosition.xyz);
    atenuacion = 1.0 / (glLlums[x].a* pow(d,2) + glLlums[x].b*d + glLlums[x].c);
    vec3 I = atenuacion *( dif* max(dot(L,vNormal.xyz),0.0) + spe*pow(max(dot(vNormal.xyz,H),0.0), material.shininess) + amb);
    if(!glLlums[x].on) return vec3(0.0, 0.0, 0.0);
    return I;
}

vec3 calculaFormula(){
    vec3 I1 = calculaFormulaPre(0);
    vec3 I2 = calculaFormulaPre(1);
    vec3 I3 = calculaFormulaPre(2);
    vec3 ambientGlobal = ambiGlobal*material.ambient;
    vec3 I = ambientGlobal + I1 + I2 + I3;
    return I;
}

void main()
{
    gl_Position = vPosition;
    v_texcoord = vCoordTexture;
    vec3 I = calculaFormula();

    vec4 a = vec4(glLlums[0].ambient[0], glLlums[0].ambient[1],glLlums[0].ambient[2], 1.0);
    vec4 b = vec4(glLlums[0].diffuse[0], glLlums[0].diffuse[1],glLlums[0].diffuse[2], 1.0);
    vec4 c = vec4(glLlums[0].specular[0], glLlums[0].specular[1],glLlums[0].specular[2], 1.0);
    vec4 d = vec4(glLlums[0].ambient[0], glLlums[0].ambient[1],glLlums[0].ambient[2], 1.0);
    vec4 f = vec4(glLlums[2].ambient[0], glLlums[2].ambient[1],glLlums[2].ambient[2], 1.0);

    color = vec4(I,1.0);

    //color = p+d;
}
