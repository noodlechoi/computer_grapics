#include "stdafx.h"
#include "shaders.h"

#include "camera.h"
#include "object.h"
#include "cube.h"
#include "pyramid.h"

#include "bg.h"

#include "light.h"

#define CUBE 0
#define PYRAMID 1

Camera camera;
Light light;
Cube cube;
Pyramid pyramid;
BG bg;

vector<Object *> objects;
int currentObject = CUBE;

void init();
void update(int value);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);

GLclampf g_color[4] = {0.8f, 0.8f, 0.8f, 1.0f};

// shader variables
GLuint shaderProgramID;

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Example1");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized" << std::endl;

    cout << "c: ����ü" << endl;
    cout << "p: �簢��" << endl;
    cout << "x: x���� �߽����� ȸ��" << endl;
    cout << "y: y���� �߽����� ȸ��" << endl;
    cout << "s: �ʱ�ȭ" << endl;
    cout << "q: ����" << endl;


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    shaderProgramID = initShader("vertex.vert", "fragment.frag");

    init();
    update(0);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}

GLvoid drawScene()
{
    glClearColor(g_color[0], g_color[1], g_color[2], g_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramID);

    camera.setCamera(shaderProgramID, 0);
    light.setLight(shaderProgramID, camera.getEye());

    bg.render(shaderProgramID);

    objects[currentObject]->render(shaderProgramID);

    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, 800, 800);
}

GLvoid keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':
        currentObject = CUBE;
        break;

    case 'p':
        currentObject = PYRAMID;
        break;

    case 'x':
        if (objects[currentObject]->getXAxisRotating())
            objects[currentObject]->setXAxisRotating(false);
        else
            objects[currentObject]->setXAxisRotating(true);
        break;

    case 'y':
        if (objects[currentObject]->getYAxisRotating())
            objects[currentObject]->setYAxisRotating(false);
        else
            objects[currentObject]->setYAxisRotating(true);
        break;

    case 's':
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->setXAxisRotating(false);
            objects[i]->setYAxisRotating(false);
            objects[i]->setRotate(glm::vec3(0, 0, 0));
        }
        break;

    // Exit
    case 'Q':
    case 'q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void init()
{
    cube.initBuffer();
    cube.initTexture();

    pyramid.initBuffer();
    pyramid.initTexture();

    bg.initBuffer();
    bg.initTexture();

    objects.push_back(&cube);
    objects.push_back(&pyramid);

    camera.setEye(glm::vec3(2, 3, 10.0f));
    camera.setzFar(100.f);
}

void update(int value)
{
    objects[currentObject]->update();

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, update, 0);
}
