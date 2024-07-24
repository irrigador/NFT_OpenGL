#include <GL/glut.h>
#include <GL/gl.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>  // Para usar std::rand e std::srand
#include <ctime>    // Para usar std::time

GLfloat Aspecto;
float angle = 0.0f;
int rotating, forma;
float triangleSize = 1.0f;

bool LuzAmbEhMax = false; // Variável usada nas funções de iluminação

// Matriz de combinações de cores
GLfloat colorCombinations[8][3] = {
    {1.0f, 0.0f, 1.0f},
    {1.0f, 0.98f, 0.098f},
    {1.0f, 0.65f, 1.0f},
    {1.0f, 1.0f, 0.0f},
    {0.4f, 0.8f, 0.67f},
    {0.5f, 0.0f, 0.0f},
    {1.0f, 0.5f, 0.0f},
    {0.5f, 0.0f, 1.0f}
};

void PosicaoObservador()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, Aspecto, 0.01, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -0, 0, 0, -8, 0.0f, 1.0f, 0.0f);
}

void AjusteJanela(int w, int h)
{
    if (h == 0)  h = 1;
    Aspecto = 1.0f * (w*5) / (h*5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    PosicaoObservador();
}

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0); // cor do texto
    glRasterPos2f(-0.7, 0.0); // posição do texto
    const char* text = "UERN | Prof Dr.: Lima Jr | Aluno: Pedro Guilherme | Projeto final: Rasenshuriken";

    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
    glFlush();
}

void fim()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0); // cor do texto
    glRasterPos2f(-0.7, 0.0); // posição do texto
    const char* text = "UERN | data: 24/07/2024 | Mossoro/RN";
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
    glFlush();
}

// Funções de iluminação
void DefineLuzESPECULAR(void)
{
    // Define variação de cores (reflexão da luz) para o objeto
    GLfloat LuzAmbiente[] = { 0.1f, 0.1f, 0.1f };
    GLfloat LuzAmbienteMAX[] = { 1.0f, 1.0f, 1.0f };
    //------------------------------------------------------------
    GLfloat LuzDifusa[] = { 0.75f, 0.60f, 0.23f, 1.0f };
    //------------------------------------------------------------
    GLfloat LuzEspecular[] = { 0.63f, 0.55f, 0.37f, 1.0f };
    GLfloat Especularidade[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //------------------------------------------------------------
    GLfloat PosicaoLuz0[] = { 3.0f, 3.0f, 0.0f, 1.0f };
    GLfloat PosicaoLuz1[] = { -3.0f, -3.0f, 0.0f, 1.0f };

    // ****************  Fonte de Luz 0
    glEnable(GL_COLOR_MATERIAL);
    // Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    // Define os parametros da Luz número Zero
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0);
    glEnable(GL_LIGHT0);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);
    // Define a reflectância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, Especularidade);
    // Define a concentração do brilho.
    glMateriali(GL_FRONT, GL_SHININESS, 112);

    // ****************  Fonte de Luz 1
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
    // Define os parametros da Luz número Um
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1);
    glEnable(GL_LIGHT1);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);
    // Define a reflectância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, Especularidade);
    // Define a concentração do brilho.
    glMateriali(GL_FRONT, GL_SHININESS, 11);
}

void DefineLuzAMBIENTE(void)
{
    glDisable(GL_LIGHTING);
    return;
}

void DefineLuzDIFUSA(void)
{
    GLfloat LuzAmbiente[] = { 0.24725f, 0.1995f, 0.07f };
    GLfloat LuzAmbienteMAX[] = { 1, 1, 1 };
    GLfloat LuzDifusa[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
    GLfloat LuzEspecular[] = { 0, 0, 0, 1.0f };
    GLfloat PosicaoLuz0[] = { 3.0f, 3.0f, 0.0f, 1.0f };
    GLfloat PosicaoLuz1[] = { -3.0f, -3.0f, 0.0f, 1.0f };
    GLfloat Especularidade[] = { 0, 0, 0, 1 };

    // ****************  Fonte de Luz 0
    glEnable(GL_COLOR_MATERIAL);
    // Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Ativa o uso da luz ambiente
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);

    // Define os parâmetros da Luz número Zero
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0);
    glEnable(GL_LIGHT0);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);
    // Define a concentração do brilho.
    glMateriali(GL_FRONT, GL_SHININESS, 51);

    // ****************  Fonte de Luz 1
    // Ativa o uso da luz ambiente
    if (LuzAmbEhMax)
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
    else
        glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);

    // Define os parâmetros da Luz número Um
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1);
    glEnable(GL_LIGHT1);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);
    // Define a concentração do brilho.
    //glMateriali(GL_FRONT, GL_SHININESS, 20); // Comentado, se não necessário
}

void display()
{
    switch (forma) {
    case 1:
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2f(0.0f, triangleSize * 0.03125f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-triangleSize * 0.03125f, -triangleSize * 0.03125f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(triangleSize * 0.03125f, -triangleSize * 0.03125f);
        glEnd();

        glPopMatrix();

        glutSwapBuffers();
        break;
    case 3:
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        for (int i = 0; i < 8; ++i) {
            glBegin(GL_TRIANGLES);
            glColor3f(colorCombinations[i][0], colorCombinations[i][1], colorCombinations[i][2]);
            glVertex2f(0.0f, triangleSize * 0.03125f);
            glColor3f(colorCombinations[(i + 1) % 8][0], colorCombinations[(i + 1) % 8][1], colorCombinations[(i + 1) % 8][2]);
            glVertex2f(-triangleSize * 0.03125f, -triangleSize * 0.03125f);
            glColor3f(colorCombinations[(i + 2) % 8][0], colorCombinations[(i + 2) % 8][1], colorCombinations[(i + 2) % 8][2]);
            glVertex2f(triangleSize * 0.03125f, -triangleSize * 0.03125f);
            glEnd();
        }

        glPopMatrix();

        glutSwapBuffers();
        break;
    case 0:
        init();
        glutSwapBuffers();
        break;

    case 2:
        fim();
        glutSwapBuffers();
        break;

    case 4:  // Novo caso para replicar triângulos com cores únicas
        glClear(GL_COLOR_BUFFER_BIT);

        // Inicializa a semente para a geração de cores aleatórias
        std::srand(static_cast<unsigned>(std::time(0)));

        for (int i = 0; i < 300; ++i) {
            glPushMatrix();
            // Gera cores aleatórias
            GLfloat r = static_cast<GLfloat>(std::rand()) / RAND_MAX;
            GLfloat g = static_cast<GLfloat>(std::rand()) / RAND_MAX;
            GLfloat b = static_cast<GLfloat>(std::rand()) / RAND_MAX;

            // Define a cor aleatória
            glColor3f(r, g, b);

            // Define a posição aleatória
            float x = static_cast<GLfloat>(std::rand()) / RAND_MAX * 2.0f - 1.0f;
            float y = static_cast<GLfloat>(std::rand()) / RAND_MAX * 2.0f - 1.0f;

            glBegin(GL_TRIANGLES);
            glVertex2f(x, y + triangleSize * 0.03125f);
            glVertex2f(x - triangleSize * 0.03125f, y - triangleSize * 0.03125f);
            glVertex2f(x + triangleSize * 0.03125f, y - triangleSize * 0.03125f);
            glEnd();

            glPopMatrix();
        }

        glutSwapBuffers();
        break;
    }
}

void timer(int value)
{
    if (rotating) {
        angle += 6.0f; // 6 degrees per frame
        if (angle >= 360.0f)
            angle -= 360.0f;

        glutPostRedisplay();
    }

    glutPostRedisplay(); // atualiza a cena continuamente
    glutTimerFunc(1, timer, 0); // chama a função novamente após 16ms (60fps)
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'z':
        rotating = 0;
        break;
    case 'x':
        rotating = 1;
        break;
    case 'p':
        forma = 1;
        break;
    case 'o':
        forma = 2;
        break;
    case 'a':
        triangleSize *= 2.0f;
        break;
    case 's':
        triangleSize /= 2.0f;
        break;
    case 'q':
        angle += 180.0f;
        break;
    case 'w':
    case 'W':
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        break;
    case 'n':
        DefineLuzESPECULAR();
        break;
    case 'b':
        DefineLuzDIFUSA();
        break;
    case 'm':
        DefineLuzAMBIENTE();
        break;
    case 'l':  // Novo caso para replicar triângulo com todas as cores
        forma = 4;
       
        break;
    case 'k':  // Novo caso para replicar triângulo com todas as cores
        forma = 3;
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1040, 880);
    glutCreateWindow("NFT| RasenShuriken");

    glutDisplayFunc(display);
    glutTimerFunc(33, timer, 1);
    glutKeyboardFunc(keyboard);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutMainLoop();

    return 0;
}