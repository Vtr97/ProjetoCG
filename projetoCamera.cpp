#include <GL/glut.h>
#include <math.h>
#include <algorithm>
#include "iluminacao.h"


// partes do braço
int ombro = 0, cotovelo = 0, mao = 0, dedoMeio = 0, dedoEsq = 0, dedoDir = 0;

// variaveis da camera
float angulo = 0.0;
float distancia = 10.0;

void inicializa()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING); // ativa a iluminacao
    glEnable(GL_LIGHT0);

    // configuracao da luz
    inicializaIluminacao();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float posX = distancia * cos(angulo);
    float posZ = distancia * sin(angulo);

    // camera
    gluLookAt(posX, 5.0, posZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // ajusta o eixo Z para encaixar a figura
    glTranslatef(0.0, 0.0, -5.0);

    // Movimento do ombro
    glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((float)ombro, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // Parte superior do braço
    GLfloat materialVermelho[] = {0.7, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialVermelho);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Movimento do cotovelo
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((float)cotovelo, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // parte inferior do braço
    GLfloat materialVerde[] = {0.0, 0.7, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialVerde);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Movimento do pulso
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((float)mao, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    // mao
    GLfloat materialAzul[] = {0.0, 0.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialAzul);
    glPushMatrix();
    glScalef(1.0, 0.2, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // articulação dedo meio
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef((float)dedoMeio, 0.0, 0.0, 1.0);
    glRotatef((float)dedoEsq, 0.0, 0.0, 1.0);
    glRotatef((float)dedoDir, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    // dedo meio
    GLfloat materialAmarelo[] = {1.0, 1.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialAmarelo);
    glPushMatrix();
    glScalef(1, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // articulação dedo Esq
    glTranslatef(-0.5, 0, 0);
    glTranslatef(0.5, 0.0, 0.40);

    // dedo Esq
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialAmarelo);
    glPushMatrix();
    glScalef(1, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();


    // articulação dedo Dir
    glTranslatef(-0.5, 0, -0.40);
    glTranslatef(0.5, 0.0, -0.40);

    // dedo Dir
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialAmarelo);
    glPushMatrix();
    glScalef(1, 0.2, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y)
{

    switch (tecla)
    {
    case 'w':
        distancia -= 1.0; // move a camera para mais perto
        glutPostRedisplay();
        break;

    case 's':
        distancia += 1.0;
        glutPostRedisplay();
        break;

    case 'o':
        ombro = std::min((ombro + 5),90);
        glutPostRedisplay();
        break;
    case 'O':
        ombro = std::max((ombro - 5),-180);
        glutPostRedisplay();
        break;
    case 'c':
        cotovelo = std::min((cotovelo + 5),130);
        glutPostRedisplay();
        break;
    case 'C':
        cotovelo = std::max((cotovelo - 5),0);
        glutPostRedisplay();
        break;

    case 'm':
        mao = std::min((mao + 5),90);
        glutPostRedisplay();
        break;
    case 'M':
        mao = std::max((mao - 5),-90);
        glutPostRedisplay();
        break;
    case 'd':
        dedoEsq = std::min((dedoEsq + 5), 40); // Limita a 90°
        dedoMeio = std::min((dedoMeio + 5), 40);
        dedoDir = std::min((dedoDir + 5), 40);
        glutPostRedisplay();
    break;

    case 'D':
        dedoEsq = std::max((dedoEsq - 5), 0); // Limita a 0°
        dedoMeio = std::max((dedoMeio - 5), 0);
        dedoDir = std::max((dedoDir - 5), 0);
        glutPostRedisplay();
        break;
    
    case 27:
        exit(0);
        break;
    }
}

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_LEFT:
        angulo += 0.05;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        angulo -= 0.05;
        glutPostRedisplay();
        break;
    }
}

void reshape(int largura, int altura)
{
    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(65.0, (float)largura / (float)altura, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Teste Projeto");

    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);

    glutMainLoop();

    return 0;
}