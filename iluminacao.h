//configura iluminacao
#include <GL/glut.h>

// angulo da luz
float anguloLuzX = 0.0;
float anguloLuzY = 0.0;
float anguloLuzZ = 0.0;

void inicializaIluminacao()
{
    GLfloat posicaoLuz[] = {1.0, 1.0, 1.0, 0.0}; // 0: luz direcional 1: pontual
    glRotatef(anguloLuzX, 1.0, 0.0, 0.0);
    glRotatef(anguloLuzY, 0.0, 1.0, 0.0);
    glRotatef(anguloLuzZ, 0.0, 0.0, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    GLfloat luzAmbiente[] = {0.2, 0.2, 0.2, 1.0}; // rgb + opacidade
    GLfloat luzDifusa[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat luzEspecular[] = {1.0, 1.0, 1.0, 1.0};


    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}