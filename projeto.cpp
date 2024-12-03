#include <GL/glut.h>
#include <math.h>
#include <iluminacao.h>

int ombro = 0, cotovelo = 0, mao = 0, dedoMeio = 0, dedoEsq = 0, DedoDir = 0;
float anguloLuzX = 0.0;
float anguloLuzY = 0.0;
float anguloLuzZ = 0.0;
// Variáveis para ângulo de rotação da câmera
float cameraYaw = 0.0;   // Rotação em torno do eixo Y (olhar para esquerda/direita)
float cameraPitch = 0.0; // Rotação em torno do eixo X (olhar para cima/baixo)
// Distância inicial da câmera
float cameraDistance = 10.0;

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

    glPushMatrix();

    GLfloat posicaoLuz[] = {1.0, 1.0, 1.0, 0.0}; // 0: luz direcional 1: pontual
    glRotatef(anguloLuzX, 1.0, 0.0, 0.0);
    glRotatef(anguloLuzY, 0.0, 1.0, 0.0);
    glRotatef(anguloLuzZ, 0.0, 0.0, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glPopMatrix();

    glLoadIdentity();

    // camera
    float camX = cameraDistance * cos(cameraPitch * M_PI / 180.0) * sin(cameraYaw * M_PI / 180.0);
    float camY = cameraDistance * sin(cameraPitch * M_PI / 180.0);
    float camZ = cameraDistance * cos(cameraPitch * M_PI / 180.0) * cos(cameraYaw * M_PI / 180.0);

    gluLookAt(camX, camY, camZ, // Posição da câmera
              0.0, 0.0, 0.0,    // Ponto que a câmera olha
              0.0, 1.0, 0.0);   // Vetor "up" (para cima)

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
    glTranslatef(0.5, 0.0, 0.0);

    // dedo meio
    GLfloat materialAmarelo[] = {1.0, 1.0, 0.0, 1.0};
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
    const float movimento = 0.5; // Incremento para zoom e movimentação
    switch (tecla)
    {
    case 'w': // Aproxima a câmera do objeto
        cameraDistance -= movimento;
        if (cameraDistance < 1.0) // Evita que a câmera chegue muito perto
            cameraDistance = 1.0;
        glutPostRedisplay();
        break;

    case 's': // Afasta a câmera do objeto
        cameraDistance += movimento;
        glutPostRedisplay();
        break;

    case 'a': // Move a câmera em um círculo (esquerda)
        cameraYaw -= 5.0; // Ajusta o ângulo de rotação em torno do eixo Y
        glutPostRedisplay();
        break;

    case 'd': // Move a câmera em um círculo (direita)
        cameraYaw += 5.0; // Ajusta o ângulo de rotação em torno do eixo Y
        glutPostRedisplay();
        break;

    case 'o':
        ombro = (ombro + 5) % 360;
        glutPostRedisplay();
        break;
    case 'O':
        ombro = (ombro - 5) % 360;
        glutPostRedisplay();
        break;
    case 'c':
        cotovelo = (cotovelo + 5) % 360;
        glutPostRedisplay();
        break;
    case 'C':
        cotovelo = (cotovelo - 5) % 360;
        glutPostRedisplay();
        break;

    case 'm':
        mao = (mao + 5) % 360;
        glutPostRedisplay();
        break;
    case 'M':
        mao = (mao - 5) % 360;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    }
}


void tecladoEspecial(int tecla, int x, int y)
{
    const float movimento = 0.1;
    const float rotacao = 5.0; // Incremento de rotação em graus

    switch (tecla)
    {
    case GLUT_KEY_UP:
        cameraPitch += rotacao; // Rotação para cima
        if (cameraPitch > 89.0) // Limita o ângulo para evitar problemas
            cameraPitch = 89.0;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        cameraPitch -= rotacao; // Rotação para baixo
        if (cameraPitch < -89.0)
            cameraPitch = -89.0;
        glutPostRedisplay();
        break;

    case GLUT_KEY_LEFT:
        cameraYaw -= rotacao; // Rotação para a esquerda
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        cameraYaw += rotacao; // Rotação para a direita
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