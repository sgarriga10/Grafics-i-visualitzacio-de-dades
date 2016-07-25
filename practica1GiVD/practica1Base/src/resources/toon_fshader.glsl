#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 fnormal;
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

uniform tipusMaterial material;
uniform tipusLlum glLlums[3]; //0 puntual, 1 direccional, 2 Spotlight


void main()
{
    float intensity;
    if(glLlums[1].on){
        intensity = dot(normalize(glLlums[1].direction.xyz), normalize(fnormal.xyz));
    } else{
        intensity = dot(vec4(0.0, 0.0, 0.0, 0.0), normalize(fnormal));
    }
    vec4 color;

    if (intensity > 0.95) color = vec4(1.0,0.5,0.5,1.0);
    else if (intensity > 0.5) color = vec4(0.6,0.3,0.3,1.0);
    else if (intensity > 0.25) color = vec4(0.4,0.2,0.2,1.0);
    else color = vec4(0.2,0.1,0.1,1.0);


    gl_FragColor = color;
    //gl_FragColor = vec4(0.25*color + 0.75*texture2D(texMap, v_texcoord));

}

