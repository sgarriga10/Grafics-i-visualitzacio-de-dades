#include <objecte.h>
#include <readfile.h>

Objecte::Objecte(int npoints, QObject *parent) : numPoints(npoints) ,QObject(parent){
    points = new point4[numPoints];
    colors = new point4[numPoints];
    normal = new point4[numPoints];
    vecTextures = new point2[numPoints];

    vec3 ambient = vec3(0.0, 0.0, 0.0);
    vec3 diffuse = vec3(0.0, 0.0, 0.0);
    vec3 specular = vec3(0.0, 0.0, 0.0);
    float shininess = .0f;
    m = new Material(point3(0.2, 0.2, 0.2), point3(0.8, 0.0, 0.0), point3(1.0, 1.0, 1.0), 20.0);
}

Objecte::Objecte(int npoints, QString n) : numPoints(npoints){
    points = new point4[numPoints];
    colors = new point4[numPoints];
    normal = new point4[numPoints];
    vecTextures = new point2[numPoints];


    m = new Material(point3(0.2, 0.2, 0.2), point3(0.8, 0.0, 0.0), point3(1.0, 1.0, 1.0), 20.0);

    readObj(n);
    calculaNormals();
    make();
    initTextures();
}


Objecte::~Objecte(){
    delete points;
    delete colors;
    delete m;
    delete normal;
    delete vecTextures;

}

/**
 * @brief Objecte::toGPU
 * @param pr
 */
void Objecte::toGPU(QGLShaderProgram *pr) {
    program = pr;
    program->setUniformValue("texMap", 0);
    texture -> bind(0);

    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(vec4)*Index + sizeof(vec2) * Index, NULL, GL_STATIC_DRAW );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );

}


/**
 * Pintat en la GPU.
 * @brief Objecte::draw
 */
void Objecte::draw(){

    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, &points[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, &normal[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index +sizeof(point4)*Index,sizeof(point2)*Index, vecTextures);

    int vertexLocation = program->attributeLocation("vPosition");
    int normalLocation = program->attributeLocation("vNormal");
    int coordTextureLocation = program->attributeLocation("vCoordTexture");

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);


    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer("vNormal", GL_FLOAT, sizeof(point4)*Index, 4);

    program->enableAttributeArray(coordTextureLocation);
    program->setAttributeBuffer("vCoordTexture", GL_FLOAT,  sizeof(point4)*Index+sizeof(point4)*Index, 2);


    m->toGPU(program);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

}

void Objecte::make(){

    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };

    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            Index++;
        }
    }
    for(int i=0; i<Index; ++i) normal[i] = normalize(normalVertexs[point[i]]);
    calculaTextures();
}

void Objecte::readObj(QString filename){

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5) {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(point4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                construeix_cara (&ReadFile::words[1], nwords-1);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
            }
            else if (!strcmp (first_word, "usemtl")) {
            }
            // fadded
            else {
            }
        }
    }

}
void Objecte::initTextures(){
    qDebug() << "Initializing textures...";


    glActiveTexture(GL_TEXTURE0);
    texture = new QOpenGLTexture(QImage("://resources/textures/earth1.png"));
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->bind(0);

}
void Objecte::calculaNormals(){
    normalVertexs.resize(vertexs.size());
    for (unsigned int i=0; i<normalVertexs.size();i++)
        normalVertexs[i] = vec3(0.0, 0.0, 0.0);

    for (unsigned int i=0; i<cares.size(); i++){
        cares[i].calculaNormal(vertexs);
        vec3 faceNormal = cares[i].normal;
        for (unsigned int j=0; j<cares[i].idxVertices.size();j++){
            normalVertexs[cares[i].idxVertices[j]] += faceNormal;
            point.push_back(cares[i].idxVertices[j]);
        }
    }

    for (unsigned int i=0; i<normalVertexs.size();i++)
        normalVertexs[i] = normalize(normalVertexs[i]);
}

void Objecte::construeix_cara ( char **words, int nwords) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif


            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(this->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    this->cares.push_back(face);
}

void Objecte::calculaTextures()
{
    double u,v;

    for(unsigned int i = 0; i< Index; i++){
        u =(double) 0.5 + (atan2(normal[i].x,normal[i].z)/ (2*M_PI));
        v =(double) 0.5 - (asin(normal[i].y)/ M_PI);
        vecTextures[i] = vec2(u,v);
    }
}
void Objecte::aplicaTGnormals(mat4 m) {
    point4  *transformed_normals = new point4[Index];

    for ( int i = 0; i < Index; ++i ){
        transformed_normals[i] = m * normal[i];
    }

    transformed_normals = &transformed_normals[0];
    normal = &normal[0];

    for ( int i = 0; i < Index; ++i )
    {
        normal[i] = transformed_normals[i];
    }

    delete transformed_normals;

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * Index,
                     &normal[0] );
}

void Objecte::aplicaTG(mat4 m)
{
    point4  *transformed_points = new point4[Index];

    for ( int i = 0; i < Index; ++i ) {
        transformed_points[i] = m * points[i];
    }

    transformed_points = &transformed_points[0];
    points = &points[0];

    for ( int i = 0; i < Index; ++i )
    {
        points[i] = transformed_points[i];
    }

    delete transformed_points;

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * Index,
                     &points[0] );

}


