#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 pPosition;
IN vec4 pNormal;
IN vec2 v_texcoord;
uniform sampler2D texMap;


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

uniform vec3 ambGlobal;
uniform tipusMaterial material;
uniform tipusLlum glLlums[3]; //0 puntual, 1 direccional, 2 Spotlight
uniform bool textureOn;
vec4 obs = vec4(0.0,0.0,10.0,1.0);

vec4 calculaAmbiental(int x){
    vec3 amb = glLlums[x].ambient * material.ambient;
    return vec4(amb, 1.0);
}

vec4 calculaDiffuse(int x){
    vec3 dif = glLlums[x].diffuse * material.diffuse;
    return vec4(dif, 1.0);
}

vec4 calculaSpecular(int x){
    vec3 spe = glLlums[x].specular * material.specular;
    return vec4(spe, 1.0);
}

vec4 calculaFormulaPre(int x){
    vec4 amb = calculaAmbiental(x);
    vec4 dif = calculaDiffuse(x);
    vec4 spe = calculaSpecular(x);
    float atenuacion;
    vec4 L ;

    if(x == 0) L = normalize(glLlums[x].position - pPosition);
    if(x == 1) L = normalize(glLlums[x].direction - pPosition);
    if(x == 2) {
        L = normalize(glLlums[x].position - pPosition);
        float cos = dot(glLlums[x].direction, L);
        if(cos <= glLlums[x].angle) {
            return vec4(glLlums[x].ambient * material.ambient, 1.0);
        }
    }
    float d = length(glLlums[x].position - pPosition);
    vec4 V = normalize(obs - pPosition);
    vec4 H = normalize(V+L);
    atenuacion = 1.0 / (glLlums[x].a* pow(d,2) + glLlums[x].b*d + glLlums[x].c);
    vec4 I = atenuacion *( dif *max(dot(L,pNormal),0.0)  + spe*pow(max(dot(pNormal,H),0.0), material.shininess) + amb);

    if(!glLlums[x].on) return vec4(0.0, 0.0, 0.0, 0.0);
    return I;
}

vec4 calculaFormula(){
    vec4 I1 = calculaFormulaPre(0);
    vec4 I2 = calculaFormulaPre(1);
    vec4 I3 = calculaFormulaPre(2);
    vec3 ambientGlobal = ambGlobal*material.ambient;
    vec4 I = vec4(ambientGlobal, 1.0) + I1 + I2 + I3;
    return I;
}

void main()
{
    vec4 I = calculaFormula();
    if(textureOn) {
        gl_FragColor = 0.25*I + 0.75*texture2D(texMap, v_texcoord);
    }else {
        gl_FragColor = I;
    }

    //gl_FragColor = I;
}
