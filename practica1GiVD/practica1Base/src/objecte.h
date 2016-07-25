#ifndef OBJECTE_H
#define OBJECTE_H

#include <QObject>
#include <vector>
#include <Common.h>
#include <cara.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <material.h>

using namespace std;

typedef Common::vec4  point4;
typedef Common::vec3  point3;
typedef Common::vec2  point2;

// Classe que conte la representacio d'un objecte: geometria, topologia, material i textures
class Objecte : public QObject {

    Q_OBJECT
protected:
    QString nom;
    vector<Cara> cares;
    vector<point4> vertexs;
    vector<point3> normalVertexs;
    vector<point4>normals;
   // vector<point2> vecTextures;
    vector <int> point;
    GLuint buffer;

    int   numPoints;
    point4 *points;
    point4 *colors;
    point4 *normal;
    point2 *vecTextures;
    QOpenGLTexture *texture;
    int Index;

    QGLShaderProgram *program;
public:
    Material *m;
    Objecte(const int npoints, QObject *parent = 0);
    Objecte(const int npoints, QString n);

    ~Objecte();
    void initTextures();
    vec2 calculTexturaCoord(const vec4 &v);
    virtual void readObj(QString filename);

    virtual void make();
    virtual void toGPU(QGLShaderProgram *p);
    void aplicaTG(mat4 m);
    void aplicaTGnormals(mat4 m);
    virtual void draw();
    void calculaNormals();
    void calculaTextures();
    void quad( int a, int b, int c, int d );

private:
    void construeix_cara ( char **words, int nwords);
};



#endif // OBJECTE_H
