// configura iluminacao
#include <GL/glut.h>

// angulo da luz
float anguloLuzX = 0.0;
float anguloLuzY = 0.0;
float anguloLuzZ = 0.0;

// variaveis da luz
GLfloat posicaoLuz[] = {1.0, 1.0, 1.0, 0.0}; // 0: luz direcional, 1: pontual
GLfloat luzAmbiente[] = {0.2, 0.2, 0.2, 1.0}; // rgb + opacidade
GLfloat luzDifusa[] = {0.8, 0.8, 0.8, 1.0};
GLfloat luzEspecular[] = {1.0, 1.0, 1.0, 1.0};

void ajustaIntensidade(GLfloat* luz, float incremento) {
    for (int i = 0; i < 3; ++i) {
        luz[i] = std::max(0.0f, std::min(1.0f, luz[i] + incremento));
    }
}

void inicializaIluminacao() {
    glRotatef(anguloLuzX, 1.0, 0.0, 0.0);
    glRotatef(anguloLuzY, 0.0, 1.0, 0.0);
    glRotatef(anguloLuzZ, 0.0, 0.0, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
}

void reiniciarIluminacao() {
    // Defina os valores padrão das configurações de iluminação
    luzAmbiente[0] = 0.2f; luzAmbiente[1] = 0.2f; luzAmbiente[2] = 0.2f; luzAmbiente[3] = 1.0f;
    luzDifusa[0] = 0.8f; luzDifusa[1] = 0.8f; luzDifusa[2] = 0.8f; luzDifusa[3] = 1.0f;
    luzEspecular[0] = 1.0f; luzEspecular[1] = 1.0f; luzEspecular[2] = 1.0f; luzEspecular[3] = 1.0f;
    inicializaIluminacao(); // Reaplica as configurações na cena
}
