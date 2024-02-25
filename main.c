#include <GL/freeglut.h>
#include <math.h>


float xPos = 0.0;
float yPos = 0.0;
float moveSpeed = 0.05;
float angle = 0.0;


void rotatePoint(float *x, float *y, float angle) {
    float rad = angle * 3.1415926535 / 180.0;
    float xNew = *x * cos(rad) - *y * sin(rad);
    float yNew = *x * sin(rad) + *y * cos(rad);
    *x = xNew + xPos;
    *y = yNew + yPos;
}



void draw_global_tank_up()
{
    
    glPointSize(5);
    glBegin(GL_POINTS);

    

    float coordFirstColor[35][2] = { // ���������� 1-�� �����
        {0.0f, 0.0f},
        {0.0f, -0.03f},
        {0.01f, -0.03f},
        {0.01f, -0.02f},
        {0.02f, -0.03f},
        {0.03f, -0.03f},
        {0.04f, -0.03f},
        {0.02f, -0.01f},
		{0.03f, -0.01f},
		{0.04f, -0.01f},
        {0.02f, 0.01f},
        {0.03f, 0.01f},
        {0.04f, 0.01f},
        {0.02f, 0.03f},
        {0.03f, 0.03f},
        {0.04f, 0.03f},
        {0.02f, 0.0f},
        {0.02f, 0.02f},
        {0.02f, -0.02f},
        {0.02f, -0.04f},
        {0.01f, -0.05f},
        {0.0f, -0.05f},
        {-0.01f, -0.05f},
        {-0.03f, -0.05f},
        {-0.04f, -0.05f},
        {0.03f, -0.05f},
        {0.04f, -0.05f},
        {-0.03f, -0.03f},
        {-0.04f, -0.03f},
        {-0.03f, -0.01f},
        {-0.04f, -0.01f},
        {-0.03f, 0.01f},
        {-0.04f, 0.01f},
        {-0.03f, 0.03f},
        {-0.04f, 0.03f},
    };

    
    float coordSecondColor[28][2] = {  // ���������� 2-�� �����
    	{0.0f, 0.01f},
        {0.01f, 0.01f},
        {0.01f, 0.02f},
        {-0.01f, 0.02f},
        {-0.01f, 0.01f},
        {0.01f, 0.0f},
        {0.01f, -0.01f},
        {0.0f, -0.01f},
        {0.0f, -0.02f},
        {-0.01f, -0.03f},
        {0.0f, -0.04f},
        {0.01f, -0.04f},
        {0.03f, -0.04f},
        {0.04f, -0.04f},
        {0.03f, -0.02f},
        {0.04f, -0.02f},
        {0.03f, 0.0f},
        {0.04f, 0.0f},
        {0.03f, 0.02f},
        {0.04f, 0.02f},
        {0.03f, 0.04f},
        {0.04f, 0.04f},
        {-0.02f, 0.04f},
        {-0.03f, 0.04f},
        {-0.03f, 0.02f},
        {-0.03f, 0.0f},
        {-0.03f, -0.02f},
        {-0.03f, -0.04f},

    };

    float coordThirdColor[22][2] = { // ���������� 3-�� �����
        {0.0f, 0.02f},
        {0.0f, 0.03f},
        {0.0f, 0.04f},
        {0.0f, 0.05f},
        {0.02f, 0.04f},
        {-0.01f, -0.04f},
        {-0.02f, -0.04f},
        {-0.01f, -0.02f},
        {-0.02f, -0.02f},
        {-0.01f, -0.01f},
        {-0.02f, -0.01f},
        {-0.01f, 0.0f},
        {-0.02f, 0.0f},
        {-0.02f, -0.03f},
        {-0.02f, 0.01f},
        {-0.02f, 0.02f},
        {-0.02f, 0.03f},
        {-0.04f, 0.0f},
        {-0.04f, 0.02f},
        {-0.04f, 0.04f},
        {-0.04f, -0.02f},
        {-0.04f, -0.04f},
    };
    

    glBegin(GL_POINTS);

    glColor3f(0.67, 0.48, 0); // ��������� 1-�� �����
    for (int i = 0; i < 35; i++) {
        float x = coordFirstColor[i][0], y = coordFirstColor[i][1];
        rotatePoint(&x, &y, angle);
        glVertex2f(x, y);
    }

    glColor3f(1.0f, 0.63f, 0.27f); // ��������� 2-�� �����
    for (int i = 0; i < 28; i++) {
        float x = coordSecondColor[i][0], y = coordSecondColor[i][1];
        rotatePoint(&x, &y, angle);
        glVertex2f(x, y);
    }

    glColor3f(0.97f, 0.84f, 0.47f); // ��������� 3-�� �����
    for (int i = 0; i < 22; i++) {
        float x = coordThirdColor[i][0], y = coordThirdColor[i][1];
        rotatePoint(&x, &y, angle);
        glVertex2f(x, y);
    }

    glEnd();

    
}

void draw_block_zone()
{
    glColor3f(0.29f, 0.27f, 0.27f);

    glBegin(GL_QUADS);

    glVertex2f(-0.95f, 1.1f);
    glVertex2f(-1.1f, 1.1f);
    glVertex2f(-1.1f, -1.1f);
    glVertex2f(-0.95f, -1.1f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(-1.1f, -0.95f);
    glVertex2f(-1.1f, -1.1f);
    glVertex2f(1.1f, -1.1f);
    glVertex2f(1.1f, -0.95f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(0.95f, 1.1f);
    glVertex2f(1.1f, 1.1f);
    glVertex2f(1.1f, -1.1f);
    glVertex2f(0.95f, -1.1f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(-1.1f, 0.95f);
    glVertex2f(-1.1f, 1.1f);
    glVertex2f(1.1f, 1.1f);
    glVertex2f(1.1f, 0.95f);

    glEnd();

}


void draw_blocks(double xRand, double yRand)
{
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(xRand - 0.05f, yRand + 0.05f);
    glVertex2f(xRand + 0.05f, yRand + 0.05f);
    glVertex2f(xRand + 0.05f, yRand - 0.05f);
    glVertex2f(xRand - 0.05f, yRand - 0.05f);

    glEnd();
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    draw_block_zone();
    draw_global_tank_up();
    draw_blocks(0.1, 0.1);
 

    glutSwapBuffers();
}




void keyboard(char key) {
    switch (key) {
    case 'w':
    case 'W':
    case '�':
    case '�':

        angle = 0.0;
        if (yPos <= 0.9f) yPos += moveSpeed;

        break;
    case 's':
    case 'S':
    case '�':
    case '�':

        angle = 180.0;
        if (yPos >= -0.9f) yPos -= moveSpeed;

        break;
    case 'a':
    case 'A':
    case '�':
    case '�':

        angle = 90.0;
        if (xPos >= -0.9) xPos -= moveSpeed;

        break;
    case 'd':
    case 'D':
    case '�':
    case '�':

    	angle = 270.0;
        if (xPos <= 0.9) xPos += moveSpeed;

        break;
    }
    glutPostRedisplay(); // �������, ��� ���������� ������ (����� �� �������� ��������� ������ �� ����)
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    
    glutInitWindowSize(1000, 1000); // ������ � ����� ������������������, � ����� �����
    glutInitWindowPosition(500, 0);
    
    glutCreateWindow("Tanchik");
    glClearColor(0.1, 0.1, 0.1, 0);


    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
   

    glutMainLoop();
    return 0;
}
