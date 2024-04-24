#define _CRT_SECURE_NO_WARNINGS

#include <gl/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NUM_OF_MINI_BRICKS_BLOCKS 500
#define NUM_OF_MINI_CEMENT_BLOCKS 500
#define BOOM_ANIMATION_FRAMES 10

int menuChoose = 0;
float moveSpeed = 0.02;

struct tankSettings
{
    float xPos;
    float yPos;
    float angle;
    int live;

    float saveXPos;
    float saveYPos;
    int flagAutoMove;
    int tickToShoot;
    int timerMove;
    int botSpeed;

    struct
    {
        float dx;
        float dy;
        float angle_bull;
        short live;
        short anim_bool;
        short time_anim;

        float an_x;
        float an_y;
    } bulletSet;
};


float bricksLoc[NUM_OF_MINI_BRICKS_BLOCKS][3] = {0};
float cementLoc[NUM_OF_MINI_CEMENT_BLOCKS][3] = {0};


struct tankSettings enemy[4];
struct tankSettings you;

void startSettings()
{
    you.xPos = 0;
    you.yPos = -0.84;
    you.live = 1;
    you.bulletSet.time_anim = 0;

    enemy[0].live = 1;
    enemy[0].xPos = -0.8;
    enemy[0].yPos = 0.12;
    enemy[0].angle = 270;
    enemy[0].saveXPos = 0;
    enemy[0].saveYPos = 0;
    enemy[0].flagAutoMove = 4;

    enemy[1].live = 1;
    enemy[1].xPos = 0.7;
    enemy[1].yPos = 0.12;
    enemy[1].angle = 90;
    enemy[1].saveXPos = 0;
    enemy[1].saveYPos = 0;
    enemy[1].flagAutoMove = 1;

    enemy[2].live = 1;
    enemy[2].saveXPos = 0;
    enemy[2].saveYPos = 0;
    enemy[2].flagAutoMove = 2;

    enemy[3].live = 1;
    enemy[3].saveXPos = 0;
    enemy[3].saveYPos = 0;
    enemy[3].flagAutoMove = 2;
}

void draw_mini_cement_block(double x, double y)
{
    float firstcol[9][2] = {
            {x, y},
            {x + 0.01, y},
            {x + 0.02, y},
            {x + 0.03, y},
            {x + 0.04, y},
            {x + 0.04, y + 0.01},
            {x + 0.04, y + 0.02},
            {x + 0.04, y + 0.03},
            {x + 0.04, y + 0.04}
    };

    float secondcol[7][2] = {
            {x, y + 0.01},
            {x, y + 0.02},
            {x, y + 0.03},
            {x, y + 0.04},
            {x + 0.01, y + 0.04},
            {x + 0.02, y + 0.04},
            {x + 0.03, y + 0.04},
    };

    float thirdcol[9][2] = {
            {x + 0.01, y + 0.01},
            {x + 0.01, y + 0.02},
            {x + 0.01, y + 0.03},
            {x + 0.02, y + 0.01},
            {x + 0.02, y + 0.02},
            {x + 0.02, y + 0.03},
            {x + 0.03, y + 0.01},
            {x + 0.03, y + 0.02},
            {x + 0.03, y + 0.03},
    };

    glBegin(GL_POINTS);

    glColor3f(1, 1, 1);
    for (int i = 0; i < 9; i++) {
        float x = thirdcol[i][0], y = thirdcol[i][1];
        glVertex2f(x, y);
    }

    glColor3f(0.78, 0.78, 0.78);
    for (int i = 0; i < 7; i++) {
        float x = secondcol[i][0], y = secondcol[i][1];
        glVertex2f(x, y);
    }

    glColor3f(0.48, 0.49, 0.48);
    for (int i = 0; i < 9; i++) {
        float x = firstcol[i][0], y = firstcol[i][1];
        glVertex2f(x, y);
    }

    glEnd();
}

void draw_mini_brick_block(double x, double y)
{
    float firstcol[13][2] = {
            {x, y},
            {x, y + 0.01},
            {x, y + 0.02},
            {x, y + 0.03},
            {x + 0.01, y + 0.03},
            {x + 0.02, y + 0.03},
            {x + 0.03, y + 0.03},
            {x + 0.04, y + 0.03},
            {x + 0.01, y},
            {x + 0.02, y},
            {x + 0.03, y},
            {x + 0.04, y},
            {x + 0.02, y + 0.04}
    };

    float secondcol[9][2] = {
            {x + 0.01, y + 0.01},
            {x + 0.01, y + 0.02},
            {x + 0.02, y + 0.02},
            {x + 0.03, y + 0.02},
            {x + 0.04, y + 0.02},
            {x, y + 0.04},
            {x + 0.01, y + 0.04},
            {x + 0.03, y + 0.04},
            {x + 0.04, y + 0.04}
    };

    float thirdcol[3][2] = {
            {x + 0.02, y + 0.01},
            {x + 0.03, y + 0.01},
            {x + 0.04, y + 0.01}
    };

    glBegin(GL_POINTS);

    glColor3f(0.48, 0.49, 0.48);
    for (int i = 0; i < 13; i++) {
        float x = firstcol[i][0], y = firstcol[i][1];
        glVertex2f(x, y);
    }

    glColor3f(0.65, 0.19, 0);
    for (int i = 0; i < 9; i++) {
        float x = secondcol[i][0], y = secondcol[i][1];
        glVertex2f(x, y);
    }

    glColor3f(0.77, 0.44, 0);
    for (int i = 0; i < 3; i++) {
        float x = thirdcol[i][0], y = thirdcol[i][1];
        glVertex2f(x, y);
    }
    glEnd();
}

void createCementWall()
{
    for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
    {
        draw_mini_cement_block(cementLoc[i][1], cementLoc[i][2]);
    }
}

void createBrickWall()
{
    for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
    {
        if (bricksLoc[i][0] == 1)
        {
            draw_mini_brick_block(bricksLoc[i][1], bricksLoc[i][2]);
        }
    }
}

void rotatePointyou(float *x, float *y, float angle) {
    float rad = angle * 3.1415926535 / 180.0;
    float xNew = *x * cos(rad) - *y * sin(rad);
    float yNew = *x * sin(rad) + *y * cos(rad);
    *x = xNew + you.xPos;
    *y = yNew + you.yPos;
}

void rotatePointenemy_one(float *x, float *y, float angle)
{
    float rad = angle * 3.1415926535 / 180.0;
    float xNew = *x * cos(rad) - *y * sin(rad);
    float yNew = *x * sin(rad) + *y * cos(rad);
    *x = xNew + enemy[0].xPos;
    *y = yNew + enemy[0].yPos;
}

void rotatePointenemy_two(float *x, float *y, float angle)
{
    float rad = angle * 3.1415926535 / 180.0;
    float xNew = *x * cos(rad) - *y * sin(rad);
    float yNew = *x * sin(rad) + *y * cos(rad);
    *x = xNew + enemy[1].xPos;
    *y = yNew + enemy[1].yPos;
}

void rotatePointenemy_three(float *x, float *y, float angle)
{
    float rad = angle * 3.1415926535 / 180.0;
    float xNew = *x * cos(rad) - *y * sin(rad);
    float yNew = *x * sin(rad) + *y * cos(rad);
    *x = xNew + enemy[2].xPos;
    *y = yNew + enemy[2].yPos;
}

void rotatePointenemy_four(float *x, float *y, float angle)
{
    float rad = angle * 3.1415926535 / 180.0;
    float xNew = *x * cos(rad) - *y * sin(rad);
    float yNew = *x * sin(rad) + *y * cos(rad);
    *x = xNew + enemy[3].xPos;
    *y = yNew + enemy[3].yPos;
}

void draw_global_tank_up()
{

    glPointSize(5);
    glBegin(GL_POINTS);



    float coordFirstColor[35][2] = {
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


    float coordSecondColor[28][2] = {
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

    float coordThirdColor[22][2] = {
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

    glColor3f(0.67, 0.48, 0);
    for (int i = 0; i < 35; i++) {
        float x = coordFirstColor[i][0], y = coordFirstColor[i][1];
        rotatePointyou(&x, &y, you.angle);
        glVertex2f(x, y);
    }

    glColor3f(1.0f, 0.63f, 0.27f);
    for (int i = 0; i < 28; i++) {
        float x = coordSecondColor[i][0], y = coordSecondColor[i][1];
        rotatePointyou(&x, &y, you.angle);
        glVertex2f(x, y);
    }

    glColor3f(0.97f, 0.84f, 0.47f);
    for (int i = 0; i < 22; i++) {
        float x = coordThirdColor[i][0], y = coordThirdColor[i][1];
        rotatePointyou(&x, &y, you.angle);
        glVertex2f(x, y);
    }

    glEnd();


}

void draw_enemy_tank_up_one()
{

    glPointSize(5);
    glBegin(GL_POINTS);



    float coordFirstColor[35][2] = {
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


    float coordSecondColor[28][2] = {
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

    float coordThirdColor[22][2] = {
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

    glColor3f(0.28, 0.44, 0.56);
    for (int i = 0; i < 35; i++) {
        float x = coordFirstColor[i][0], y = coordFirstColor[i][1];
        rotatePointenemy_one(&x, &y, enemy[0].angle);
        glVertex2f(x, y);
    }

    glColor3f(0.73f, 0.74f, 0.73f);
    for (int i = 0; i < 28; i++) {
        float x = coordSecondColor[i][0], y = coordSecondColor[i][1];
        rotatePointenemy_one(&x, &y, enemy[0].angle);
        glVertex2f(x, y);
    }

    glColor3f(1.0f, 1.0f, 1.00f);
    for (int i = 0; i < 22; i++) {
        float x = coordThirdColor[i][0], y = coordThirdColor[i][1];
        rotatePointenemy_one(&x, &y, enemy[0].angle);
        glVertex2f(x, y);
    }

    glEnd();
}

void draw_enemy_tank_up_two()
{

    glPointSize(5);
    glBegin(GL_POINTS);



    float coordFirstColor[35][2] = {
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


    float coordSecondColor[28][2] = {
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

    float coordThirdColor[22][2] = {
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

    glColor3f(0.28, 0.44, 0.56);
    for (int i = 0; i < 35; i++) {
        float x = coordFirstColor[i][0], y = coordFirstColor[i][1];
        rotatePointenemy_two(&x, &y, enemy[1].angle);
        glVertex2f(x, y);
    }

    glColor3f(0.73f, 0.74f, 0.73f);
    for (int i = 0; i < 28; i++) {
        float x = coordSecondColor[i][0], y = coordSecondColor[i][1];
        rotatePointenemy_two(&x, &y, enemy[1].angle);
        glVertex2f(x, y);
    }

    glColor3f(1.0f, 1.0f, 1.00f);
    for (int i = 0; i < 22; i++) {
        float x = coordThirdColor[i][0], y = coordThirdColor[i][1];
        rotatePointenemy_two(&x, &y, enemy[1].angle);
        glVertex2f(x, y);
    }

    glEnd();
}

void draw_enemy_tank_up_three()
{

    glPointSize(5);
    glBegin(GL_POINTS);



    float coordFirstColor[35][2] = {
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


    float coordSecondColor[28][2] = {
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

    float coordThirdColor[22][2] = {
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

    glColor3f(0.28, 0.44, 0.56);
    for (int i = 0; i < 35; i++) {
        float x = coordFirstColor[i][0], y = coordFirstColor[i][1];
        rotatePointenemy_three(&x, &y, enemy[2].angle);
        glVertex2f(x, y);
    }

    glColor3f(0.73f, 0.74f, 0.73f);
    for (int i = 0; i < 28; i++) {
        float x = coordSecondColor[i][0], y = coordSecondColor[i][1];
        rotatePointenemy_three(&x, &y, enemy[2].angle);
        glVertex2f(x, y);
    }

    glColor3f(1.0f, 1.0f, 1.00f);
    for (int i = 0; i < 22; i++) {
        float x = coordThirdColor[i][0], y = coordThirdColor[i][1];
        rotatePointenemy_three(&x, &y, enemy[2].angle);
        glVertex2f(x, y);
    }

    glEnd();
}

void draw_enemy_tank_up_four()
{

    glPointSize(5);
    glBegin(GL_POINTS);



    float coordFirstColor[35][2] = {
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


    float coordSecondColor[28][2] = {
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

    float coordThirdColor[22][2] = {
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

    glColor3f(0.28, 0.44, 0.56);
    for (int i = 0; i < 35; i++) {
        float x = coordFirstColor[i][0], y = coordFirstColor[i][1];
        rotatePointenemy_four(&x, &y, enemy[3].angle);
        glVertex2f(x, y);
    }

    glColor3f(0.73f, 0.74f, 0.73f);
    for (int i = 0; i < 28; i++) {
        float x = coordSecondColor[i][0], y = coordSecondColor[i][1];
        rotatePointenemy_four(&x, &y, enemy[3].angle);
        glVertex2f(x, y);
    }

    glColor3f(1.0f, 1.0f, 1.00f);
    for (int i = 0; i < 22; i++) {
        float x = coordThirdColor[i][0], y = coordThirdColor[i][1];
        rotatePointenemy_four(&x, &y, enemy[3].angle);
        glVertex2f(x, y);
    }

    glEnd();
}

void draw_block_zone()
{
    glColor3f(0.29f, 0.27f, 0.27f);

    glBegin(GL_QUADS);

    glVertex2f(-0.93f, 1.1f);
    glVertex2f(-1.1f, 1.1f);
    glVertex2f(-1.1f, -1.1f);
    glVertex2f(-0.93f, -1.1f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(-1.1f, -0.93f);
    glVertex2f(-1.1f, -1.1f);
    glVertex2f(1.1f, -1.1f);
    glVertex2f(1.1f, -0.93f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(0.93f, 1.1f);
    glVertex2f(1.1f, 1.1f);
    glVertex2f(1.1f, -1.1f);
    glVertex2f(0.93f, -1.1f);

    glEnd();


    glBegin(GL_QUADS);

    glVertex2f(-1.1f, 0.93f);
    glVertex2f(-1.1f, 1.1f);
    glVertex2f(1.1f, 1.1f);
    glVertex2f(1.1f, 0.93f);

    glEnd();

}

void check_block_entity(short flag)
{
    if (flag == 1)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (you.yPos + 0.0001 + 0.05 >= cementLoc[i][2] - moveSpeed && you.yPos - 0.0001 <= cementLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (you.xPos + 0.04 >= cementLoc[i][1] - 0.0001 && you.xPos - 0.04 < cementLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (you.yPos >= 0)
                    {
                        if (cementLoc[i][2] - you.yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            you.yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (you.yPos < 0)
                    {
                        if (fabs(cementLoc[i][2]) - fabs(you.yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            you.yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(you.yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (you.yPos + 0.0001 + 0.05 >= bricksLoc[i][2] - moveSpeed && you.yPos - 0.0001 <= bricksLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (you.xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && you.xPos - 0.04 < bricksLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (you.yPos >= 0)
                    {
                        if (bricksLoc[i][2] - you.yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            you.yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (you.yPos < 0)
                    {
                        if (fabs(bricksLoc[i][2]) - fabs(you.yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            you.yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(you.yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        you.yPos += moveSpeed;
    }


    if (flag == 2)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (you.yPos - 0.0001 - 0.09 <= cementLoc[i][2] + moveSpeed && you.yPos + 0.0001 >= cementLoc[i][2])
                        &&
                        (you.xPos + 0.04 >= cementLoc[i][1] - 0.0001 && you.xPos - 0.04 <= cementLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (you.yPos >= 0)
                    {
                        if (cementLoc[i][2] - you.yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            you.yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (you.yPos <= 0)
                    {
                        if (fabs(you.yPos) - fabs(cementLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            you.yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(you.yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (you.yPos - 0.0001 - 0.09 <= bricksLoc[i][2] + moveSpeed && you.yPos + 0.0001 >= bricksLoc[i][2])
                        &&
                        (you.xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && you.xPos - 0.04 <= bricksLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (you.yPos >= 0)
                    {
                        if (bricksLoc[i][2] - you.yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            you.yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (you.yPos <= 0)
                    {
                        if (fabs(you.yPos) - fabs(bricksLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            you.yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(you.yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        you.yPos -= moveSpeed;
    }


    if (flag == 3)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (you.yPos + 0.04 >= cementLoc[i][2] - 0.0001 && you.yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (you.xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= cementLoc[i][1] + 0.04 && you.xPos + 0.0001 >= cementLoc[i][1])
                        )
                {

                    if (you.xPos >= 0)
                    {
                        if (cementLoc[i][1] - 0.001 - you.xPos <= 0)
                        {
                            you.xPos = cementLoc[i][1] + 0.12;
                        }

                    }

                    if (you.xPos < 0)
                    {
                        if (fabs(you.xPos) - fabs(cementLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            you.xPos = cementLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (you.yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && you.yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (you.xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= bricksLoc[i][1] + 0.04 && you.xPos + 0.0001 >= bricksLoc[i][1])
                        )
                {

                    if (you.xPos >= 0)
                    {
                        if (bricksLoc[i][1] - 0.001 - you.xPos <= 0)
                        {
                            you.xPos = bricksLoc[i][1] + 0.12;
                        }

                    }

                    if (you.xPos < 0)
                    {
                        if ( fabs(you.xPos) - fabs(bricksLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            you.xPos = bricksLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }
        you.xPos -= moveSpeed;
    }

    if (flag == 4)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (you.yPos + 0.04 >= cementLoc[i][2] - 0.0001 && you.yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (you.xPos + 0.0001 + 0.05 + moveSpeed >= cementLoc[i][1] && you.xPos - 0.0001 <= cementLoc[i][1])
                        )
                {
                    if (you.xPos >= 0)
                    {
                        if (cementLoc[i][1] - you.xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            you.xPos = cementLoc[i][1] - 0.08;

                        }
                    }
                    if (you.xPos <= 0)
                    {
                        if (fabs(you.xPos) - fabs(cementLoc[i][1]) - 0.08 - moveSpeed <= 0)
                        {
                            you.xPos = cementLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][1]) - fabs(you.xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (you.yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && you.yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (you.xPos + 0.0001 + 0.05 + moveSpeed >= bricksLoc[i][1] && you.xPos - 0.0001 <= bricksLoc[i][1])
                        )
                {
                    if (you.xPos >= 0)
                    {
                        if (bricksLoc[i][1] - you.xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            you.xPos = bricksLoc[i][1] - 0.08;

                        }
                    }
                    if (you.xPos <= 0)
                    {
                        if (fabs(you.xPos) - fabs(bricksLoc[i][1]) - 0.08  - moveSpeed <= 0)
                        {
                            you.xPos = bricksLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][1]) - fabs(you.xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        you.xPos += moveSpeed;
    }






}

void check_block_entity_enemy_one(int flag)
{
    if (flag == 1)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[0].yPos + 0.0001 + 0.05 >= cementLoc[i][2] - moveSpeed && enemy[0].yPos - 0.0001 <= cementLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[0].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[0].xPos - 0.04 < cementLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[0].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[0].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[0].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[0].yPos < 0)
                    {
                        if (fabs(cementLoc[i][2]) - fabs(enemy[0].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[0].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[0].yPos + 0.0001 + 0.05 >= bricksLoc[i][2] - moveSpeed && enemy[0].yPos - 0.0001 <= bricksLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[0].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[0].xPos - 0.04 < bricksLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[0].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[0].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[0].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[0].yPos < 0)
                    {
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[0].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[0].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[0].yPos += moveSpeed;
    }


    if (flag == 2)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[0].yPos - 0.0001 - 0.09 <= cementLoc[i][2] + moveSpeed && enemy[0].yPos + 0.0001 >= cementLoc[i][2])
                        &&
                        (enemy[0].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[0].xPos - 0.04 <= cementLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[0].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[0].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[0].yPos <= 0)
                    {
                        if (fabs(enemy[0].yPos) - fabs(cementLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[0].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[0].yPos - 0.0001 - 0.09 <= bricksLoc[i][2] + moveSpeed && enemy[0].yPos + 0.0001 >= bricksLoc[i][2])
                        &&
                        (enemy[0].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[0].xPos - 0.04 <= bricksLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[0].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[0].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[0].yPos <= 0)
                    {
                        if (fabs(enemy[0].yPos) - fabs(bricksLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[0].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[0].yPos -= moveSpeed;
    }


    if (flag == 3)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[0].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[0].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[0].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= cementLoc[i][1] + 0.04 && enemy[0].xPos + 0.0001 >= cementLoc[i][1])
                        )
                {

                    if (enemy[0].xPos >= 0)
                    {
                        if (cementLoc[i][1] - 0.001 - enemy[0].xPos <= 0)
                        {
                            enemy[0].xPos = cementLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[0].xPos < 0)
                    {
                        if (fabs(enemy[0].xPos) - fabs(cementLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[0].xPos = cementLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[0].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[0].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[0].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= bricksLoc[i][1] + 0.04 && enemy[0].xPos + 0.0001 >= bricksLoc[i][1])
                        )
                {

                    if (enemy[0].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - 0.001 - enemy[0].xPos <= 0)
                        {
                            enemy[0].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[0].xPos < 0)
                    {
                        if ( fabs(enemy[0].xPos) - fabs(bricksLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[0].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }
        enemy[0].xPos -= moveSpeed;
    }

    if (flag == 4)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[0].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[0].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[0].xPos + 0.0001 + 0.05 + moveSpeed >= cementLoc[i][1] && enemy[0].xPos - 0.0001 <= cementLoc[i][1])
                        )
                {
                    if (enemy[0].xPos >= 0)
                    {
                        if (cementLoc[i][1] - enemy[0].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].xPos = cementLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[0].xPos <= 0)
                    {
                        if (fabs(enemy[0].xPos) - fabs(cementLoc[i][1]) - 0.08 - moveSpeed <= 0)
                        {
                            enemy[0].xPos = cementLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][1]) - fabs(enemy[0].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[0].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[0].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[0].xPos + 0.0001 + 0.05 + moveSpeed >= bricksLoc[i][1] && enemy[0].xPos - 0.0001 <= bricksLoc[i][1])
                        )
                {
                    if (enemy[0].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - enemy[0].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[0].xPos = bricksLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[0].xPos <= 0)
                    {
                        if (fabs(enemy[0].xPos) - fabs(bricksLoc[i][1]) - 0.08  - moveSpeed <= 0)
                        {
                            enemy[0].xPos = bricksLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][1]) - fabs(enemy[0].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[0].xPos += moveSpeed;
    }
}

void check_block_entity_enemy_two(int flag)
{
    if (flag == 1)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[1].yPos + 0.0001 + 0.05 >= cementLoc[i][2] - moveSpeed && enemy[1].yPos - 0.0001 <= cementLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[1].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[1].xPos - 0.04 < cementLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[1].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[1].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[1].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[1].yPos < 0)
                    {
                        if (fabs(cementLoc[i][2]) - fabs(enemy[1].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[1].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[1].yPos + 0.0001 + 0.05 >= bricksLoc[i][2] - moveSpeed && enemy[1].yPos - 0.0001 <= bricksLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[1].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[1].xPos - 0.04 < bricksLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[1].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[1].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[1].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[1].yPos < 0)
                    {
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[1].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[1].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[1].yPos += moveSpeed;
    }


    if (flag == 2)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[1].yPos - 0.0001 - 0.09 <= cementLoc[i][2] + moveSpeed && enemy[1].yPos + 0.0001 >= cementLoc[i][2])
                        &&
                        (enemy[1].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[1].xPos - 0.04 <= cementLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[1].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[1].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[1].yPos <= 0)
                    {
                        if (fabs(enemy[1].yPos) - fabs(cementLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[1].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[1].yPos - 0.0001 - 0.09 <= bricksLoc[i][2] + moveSpeed && enemy[1].yPos + 0.0001 >= bricksLoc[i][2])
                        &&
                        (enemy[1].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[1].xPos - 0.04 <= bricksLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[1].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[1].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[1].yPos <= 0)
                    {
                        if (fabs(enemy[1].yPos) - fabs(bricksLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[1].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[1].yPos -= moveSpeed;
    }


    if (flag == 3)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[1].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[1].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[1].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= cementLoc[i][1] + 0.04 && enemy[1].xPos + 0.0001 >= cementLoc[i][1])
                        )
                {

                    if (enemy[1].xPos >= 0)
                    {
                        if (cementLoc[i][1] - 0.001 - enemy[1].xPos <= 0)
                        {
                            enemy[1].xPos = cementLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[1].xPos < 0)
                    {
                        if (fabs(enemy[1].xPos) - fabs(cementLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[1].xPos = cementLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[1].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[1].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[1].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= bricksLoc[i][1] + 0.04 && enemy[1].xPos + 0.0001 >= bricksLoc[i][1])
                        )
                {

                    if (enemy[1].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - 0.001 - enemy[1].xPos <= 0)
                        {
                            enemy[1].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[1].xPos < 0)
                    {
                        if ( fabs(enemy[1].xPos) - fabs(bricksLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[1].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }
        enemy[1].xPos -= moveSpeed;
    }

    if (flag == 4)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[1].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[1].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[1].xPos + 0.0001 + 0.05 + moveSpeed >= cementLoc[i][1] && enemy[1].xPos - 0.0001 <= cementLoc[i][1])
                        )
                {
                    if (enemy[1].xPos >= 0)
                    {
                        if (cementLoc[i][1] - enemy[1].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].xPos = cementLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[1].xPos <= 0)
                    {
                        if (fabs(enemy[1].xPos) - fabs(cementLoc[i][1]) - 0.08 - moveSpeed <= 0)
                        {
                            enemy[1].xPos = cementLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][1]) - fabs(enemy[1].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[1].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[1].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[1].xPos + 0.0001 + 0.05 + moveSpeed >= bricksLoc[i][1] && enemy[1].xPos - 0.0001 <= bricksLoc[i][1])
                        )
                {
                    if (enemy[1].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - enemy[1].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[1].xPos = bricksLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[1].xPos <= 0)
                    {
                        if (fabs(enemy[1].xPos) - fabs(bricksLoc[i][1]) - 0.08  - moveSpeed <= 0)
                        {
                            enemy[1].xPos = bricksLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][1]) - fabs(enemy[1].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[1].xPos += moveSpeed;
    }
}

void check_block_entity_enemy_three(int flag)
{
    if (flag == 1)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[2].yPos + 0.0001 + 0.05 >= cementLoc[i][2] - moveSpeed && enemy[2].yPos - 0.0001 <= cementLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[2].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[2].xPos - 0.04 < cementLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[2].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[2].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[2].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[2].yPos < 0)
                    {
                        if (fabs(cementLoc[i][2]) - fabs(enemy[2].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[2].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[2].yPos + 0.0001 + 0.05 >= bricksLoc[i][2] - moveSpeed && enemy[2].yPos - 0.0001 <= bricksLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[2].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[2].xPos - 0.04 < bricksLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[2].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[2].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[2].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[2].yPos < 0)
                    {
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[2].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[2].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[2].yPos += moveSpeed;
    }


    if (flag == 2)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[2].yPos - 0.0001 - 0.09 <= cementLoc[i][2] + moveSpeed && enemy[2].yPos + 0.0001 >= cementLoc[i][2])
                        &&
                        (enemy[2].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[2].xPos - 0.04 <= cementLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[2].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[2].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[2].yPos <= 0)
                    {
                        if (fabs(enemy[2].yPos) - fabs(cementLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[2].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[2].yPos - 0.0001 - 0.09 <= bricksLoc[i][2] + moveSpeed && enemy[2].yPos + 0.0001 >= bricksLoc[i][2])
                        &&
                        (enemy[2].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[2].xPos - 0.04 <= bricksLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[2].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[2].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[2].yPos <= 0)
                    {
                        if (fabs(enemy[2].yPos) - fabs(bricksLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[2].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[2].yPos -= moveSpeed;
    }


    if (flag == 3)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[2].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[2].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[2].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= cementLoc[i][1] + 0.04 && enemy[2].xPos + 0.0001 >= cementLoc[i][1])
                        )
                {

                    if (enemy[2].xPos >= 0)
                    {
                        if (cementLoc[i][1] - 0.001 - enemy[2].xPos <= 0)
                        {
                            enemy[2].xPos = cementLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[2].xPos < 0)
                    {
                        if (fabs(enemy[2].xPos) - fabs(cementLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[2].xPos = cementLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[2].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[2].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[2].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= bricksLoc[i][1] + 0.04 && enemy[2].xPos + 0.0001 >= bricksLoc[i][1])
                        )
                {

                    if (enemy[2].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - 0.001 - enemy[2].xPos <= 0)
                        {
                            enemy[2].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[2].xPos < 0)
                    {
                        if ( fabs(enemy[2].xPos) - fabs(bricksLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[2].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }
        enemy[2].xPos -= moveSpeed;
    }

    if (flag == 4)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[2].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[2].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[2].xPos + 0.0001 + 0.05 + moveSpeed >= cementLoc[i][1] && enemy[2].xPos - 0.0001 <= cementLoc[i][1])
                        )
                {
                    if (enemy[2].xPos >= 0)
                    {
                        if (cementLoc[i][1] - enemy[2].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].xPos = cementLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[2].xPos <= 0)
                    {
                        if (fabs(enemy[2].xPos) - fabs(cementLoc[i][1]) - 0.08 - moveSpeed <= 0)
                        {
                            enemy[2].xPos = cementLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][1]) - fabs(enemy[2].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[2].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[2].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[2].xPos + 0.0001 + 0.05 + moveSpeed >= bricksLoc[i][1] && enemy[2].xPos - 0.0001 <= bricksLoc[i][1])
                        )
                {
                    if (enemy[2].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - enemy[2].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[2].xPos = bricksLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[2].xPos <= 0)
                    {
                        if (fabs(enemy[2].xPos) - fabs(bricksLoc[i][1]) - 0.08  - moveSpeed <= 0)
                        {
                            enemy[2].xPos = bricksLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][1]) - fabs(enemy[2].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[2].xPos += moveSpeed;
    }
}

void check_block_entity_enemy_four(int flag)
{
    if (flag == 1)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[3].yPos + 0.0001 + 0.05 >= cementLoc[i][2] - moveSpeed && enemy[3].yPos - 0.0001 <= cementLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[3].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[3].xPos - 0.04 < cementLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[3].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[3].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[3].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[3].yPos < 0)
                    {
                        if (fabs(cementLoc[i][2]) - fabs(enemy[3].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].yPos = cementLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[3].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[3].yPos + 0.0001 + 0.05 >= bricksLoc[i][2] - moveSpeed && enemy[3].yPos - 0.0001 <= bricksLoc[i][2] + 0.03 - moveSpeed)
                        &&
                        (enemy[3].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[3].xPos - 0.04 < bricksLoc[i][1] + 0.0001 + 0.04)
                        )
                {
                    if (enemy[3].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[3].yPos - 0.001 - moveSpeed - 0.07 <= 0)
                        {
                            enemy[3].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                    }

                    if (enemy[3].yPos < 0)
                    {
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[3].yPos) - 0.02 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].yPos = bricksLoc[i][2] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[3].yPos) - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[3].yPos += moveSpeed;
    }


    if (flag == 2)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[3].yPos - 0.0001 - 0.09 <= cementLoc[i][2] + moveSpeed && enemy[3].yPos + 0.0001 >= cementLoc[i][2])
                        &&
                        (enemy[3].xPos + 0.04 >= cementLoc[i][1] - 0.0001 && enemy[3].xPos - 0.04 <= cementLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[3].yPos >= 0)
                    {
                        if (cementLoc[i][2] - enemy[3].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[3].yPos <= 0)
                    {
                        if (fabs(enemy[3].yPos) - fabs(cementLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].yPos = cementLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(cementLoc[i][2]) - fabs(enemy[3].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[3].yPos - 0.0001 - 0.09 <= bricksLoc[i][2] + moveSpeed && enemy[3].yPos + 0.0001 >= bricksLoc[i][2])
                        &&
                        (enemy[3].xPos + 0.04 >= bricksLoc[i][1] - 0.0001 && enemy[3].xPos - 0.04 <= bricksLoc[i][1] + 0.04 + 0.0001)
                        )
                {
                    if (enemy[3].yPos >= 0)
                    {
                        if (bricksLoc[i][2] - enemy[3].yPos + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                    }


                    if (enemy[3].yPos <= 0)
                    {
                        if (fabs(enemy[3].yPos) - fabs(bricksLoc[i][2]) + 0.01 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].yPos = bricksLoc[i][2] + 0.12;
                            continue;
                        }
                        if (fabs(bricksLoc[i][2]) - fabs(enemy[3].yPos) - 0.04 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[3].yPos -= moveSpeed;
    }


    if (flag == 3)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[3].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[3].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[3].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= cementLoc[i][1] + 0.04 && enemy[3].xPos + 0.0001 >= cementLoc[i][1])
                        )
                {

                    if (enemy[3].xPos >= 0)
                    {
                        if (cementLoc[i][1] - 0.001 - enemy[3].xPos <= 0)
                        {
                            enemy[3].xPos = cementLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[3].xPos < 0)
                    {
                        if (fabs(enemy[3].xPos) - fabs(cementLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[3].xPos = cementLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[3].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[3].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[3].xPos - 0.0001 - 0.04 - moveSpeed - 0.02 <= bricksLoc[i][1] + 0.04 && enemy[3].xPos + 0.0001 >= bricksLoc[i][1])
                        )
                {

                    if (enemy[3].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - 0.001 - enemy[3].xPos <= 0)
                        {
                            enemy[3].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }

                    if (enemy[3].xPos < 0)
                    {
                        if ( fabs(enemy[3].xPos) - fabs(bricksLoc[i][1]) - 0.04 - 0.001 <= 0)
                        {
                            enemy[3].xPos = bricksLoc[i][1] + 0.12;
                        }

                    }
                }
            }
        }
        enemy[3].xPos -= moveSpeed;
    }

    if (flag == 4)
    {
        for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
        {
            if (cementLoc[i][0] == 0)
            {
                if (
                        (enemy[3].yPos + 0.04 >= cementLoc[i][2] - 0.0001 && enemy[3].yPos - 0.04 <= cementLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[3].xPos + 0.0001 + 0.05 + moveSpeed >= cementLoc[i][1] && enemy[3].xPos - 0.0001 <= cementLoc[i][1])
                        )
                {
                    if (enemy[3].xPos >= 0)
                    {
                        if (cementLoc[i][1] - enemy[3].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].xPos = cementLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[3].xPos <= 0)
                    {
                        if (fabs(enemy[3].xPos) - fabs(cementLoc[i][1]) - 0.08 - moveSpeed <= 0)
                        {
                            enemy[3].xPos = cementLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(cementLoc[i][1]) - fabs(enemy[3].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
        {
            if (bricksLoc[i][0] == 1)
            {
                if (
                        (enemy[3].yPos + 0.04 >= bricksLoc[i][2] - 0.0001 && enemy[3].yPos - 0.04 <= bricksLoc[i][2] + 0.0001 + 0.04)
                        &&
                        (enemy[3].xPos + 0.0001 + 0.05 + moveSpeed >= bricksLoc[i][1] && enemy[3].xPos - 0.0001 <= bricksLoc[i][1])
                        )
                {
                    if (enemy[3].xPos >= 0)
                    {
                        if (bricksLoc[i][1] - enemy[3].xPos - 0.08 - 0.001 - moveSpeed <= 0)
                        {
                            enemy[3].xPos = bricksLoc[i][1] - 0.08;

                        }
                    }
                    if (enemy[3].xPos <= 0)
                    {
                        if (fabs(enemy[3].xPos) - fabs(bricksLoc[i][1]) - 0.08  - moveSpeed <= 0)
                        {
                            enemy[3].xPos = bricksLoc[i][1] - 0.08;
                            continue;
                        }
                        if (fabs(bricksLoc[i][1]) - fabs(enemy[3].xPos) - 0.08 - 0.001 - moveSpeed > 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
        enemy[3].xPos += moveSpeed;
    }
}

void draw_bullet_effects_for_global_tank()
{
    double anim_x;
    double anim_y;

    if (you.bulletSet.time_anim == 0)
    {
        you.bulletSet.an_x = you.bulletSet.dx;
        you.bulletSet.an_y = you.bulletSet.dy;
    }

    anim_x = you.bulletSet.an_x;
    anim_y = you.bulletSet.an_y;

    GLfloat colors[10][3] = {
            {1.0f, 1.0f, 1.0f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
    };

    if (you.bulletSet.anim_bool == 1 && you.bulletSet.time_anim < BOOM_ANIMATION_FRAMES) {

        int randomIndex = rand() % 3;

        glColor3fv(colors[randomIndex]);

        glBegin(GL_POINTS);
        for (int i = 0; i < 30; ++i) {
            float angle = 2 * 3.14159516 * rand() / RAND_MAX;
            float radius = 0.05 * rand() / RAND_MAX;
            glVertex2f(anim_x + radius * cos(angle), anim_y + radius * sin(angle));
        }
        you.bulletSet.time_anim += 1;
        glEnd();
    }
    else if (you.bulletSet.time_anim == BOOM_ANIMATION_FRAMES)
    {
        you.bulletSet.anim_bool = 0;
        you.bulletSet.time_anim = 0;

    }
}

void draw_bullet_global()
{
    if (you.bulletSet.live == 1)
    {
        if (you.bulletSet.dx < 0.92 && you.bulletSet.dx > -0.92 && you.bulletSet.dy < 0.92 && you.bulletSet.dy > -0.92)
        {
            for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
            {
                if (bricksLoc[i][0] == 1)
                {
                    if (
                            (bricksLoc[i][2] - 0.001 <= you.bulletSet.dy && bricksLoc[i][2] + 0.055 >= you.bulletSet.dy)
                            &&
                            (bricksLoc[i][1] - 0.001 - 0.015 <= you.bulletSet.dx && bricksLoc[i][1] + 0.055 >= you.bulletSet.dx)
                            )
                    {
                        you.bulletSet.anim_bool = 1;
                        bricksLoc[i][0] = 0;
                        you.bulletSet.live = 0;
                        break;
                    }
                }
            }

            for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
            {
                if (cementLoc[i][0] == 0)
                {
                    if (
                            (cementLoc[i][2] - 0.001 <= you.bulletSet.dy && cementLoc[i][2] + 0.055 >= you.bulletSet.dy)
                            &&
                            (cementLoc[i][1] - 0.001 - 0.015 <= you.bulletSet.dx && cementLoc[i][1] + 0.055 >= you.bulletSet.dx)
                            )
                    {
                        you.bulletSet.anim_bool = 1;
                        cementLoc[i][0] = 0;
                        you.bulletSet.live = 0;
                        break;
                    }
                }
            }

            glColor3f(0.502f, 0.502f, 0.502f);
            if (you.bulletSet.angle_bull == 0.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(you.bulletSet.dx - 0.004, you.bulletSet.dy);
                glVertex2d(you.bulletSet.dx + 0.004, you.bulletSet.dy);

                glVertex2d(you.bulletSet.dx - 0.004, you.bulletSet.dy + 0.01);
                glVertex2d(you.bulletSet.dx + 0.004, you.bulletSet.dy + 0.01);

                glVertex2d(you.bulletSet.dx, you.bulletSet.dy + 0.015);
                glVertex2d(you.bulletSet.dx, you.bulletSet.dy + 0.015);



                glEnd();
                you.bulletSet.dy += 0.01;
            }
            if (you.bulletSet.angle_bull == 180.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(you.bulletSet.dx - 0.004, you.bulletSet.dy);
                glVertex2d(you.bulletSet.dx + 0.004, you.bulletSet.dy);

                glVertex2d(you.bulletSet.dx - 0.004, you.bulletSet.dy - 0.01);
                glVertex2d(you.bulletSet.dx + 0.004, you.bulletSet.dy - 0.01);

                glVertex2d(you.bulletSet.dx, you.bulletSet.dy - 0.015);
                glVertex2d(you.bulletSet.dx, you.bulletSet.dy - 0.015);
                glEnd();
                you.bulletSet.dy -= 0.01;
            }
            if (you.bulletSet.angle_bull == 270.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(you.bulletSet.dx, you.bulletSet.dy - 0.004);
                glVertex2d(you.bulletSet.dx, you.bulletSet.dy + 0.004);

                glVertex2d(you.bulletSet.dx + 0.01, you.bulletSet.dy - 0.004);
                glVertex2d(you.bulletSet.dx + 0.01, you.bulletSet.dy + 0.004);

                glVertex2d(you.bulletSet.dx + 0.015, you.bulletSet.dy);
                glVertex2d(you.bulletSet.dx + 0.015, you.bulletSet.dy);
                glEnd();

                you.bulletSet.dx += 0.01;
            }
            if (you.bulletSet.angle_bull == 90.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(you.bulletSet.dx, you.bulletSet.dy - 0.004);
                glVertex2d(you.bulletSet.dx, you.bulletSet.dy + 0.004);

                glVertex2d(you.bulletSet.dx - 0.01, you.bulletSet.dy - 0.004);
                glVertex2d(you.bulletSet.dx - 0.01, you.bulletSet.dy + 0.004);

                glVertex2d(you.bulletSet.dx - 0.015, you.bulletSet.dy);
                glVertex2d(you.bulletSet.dx - 0.015, you.bulletSet.dy);
                glEnd();
                you.bulletSet.dx -= 0.01;

            }
            if (you.bulletSet.dx <= enemy[0].xPos + 0.05 && you.bulletSet.dx >= enemy[0].xPos - 0.05 && enemy[0].live == 1)
                if (you.bulletSet.dy <= enemy[0].yPos + 0.05 && you.bulletSet.dy >= enemy[0].yPos - 0.05 && enemy[0].live == 1)
                {
                    enemy[0].live = 0;
                    you.bulletSet.anim_bool = 1;
                    you.bulletSet.live = 0;
                }

            if (you.bulletSet.dx <= enemy[1].xPos + 0.05 && you.bulletSet.dx >= enemy[1].xPos - 0.05 && enemy[1].live == 1)
                if (you.bulletSet.dy <= enemy[1].yPos + 0.05 && you.bulletSet.dy >= enemy[1].yPos - 0.05 && enemy[1].live == 1)
                {
                    enemy[1].live = 0;
                    you.bulletSet.anim_bool = 1;
                    you.bulletSet.live = 0;
                }

            if (you.bulletSet.dx <= enemy[2].xPos + 0.05 && you.bulletSet.dx >= enemy[2].xPos - 0.05 && enemy[2].live == 1)
                if (you.bulletSet.dy <= enemy[2].yPos + 0.05 && you.bulletSet.dy >= enemy[2].yPos - 0.05 && enemy[2].live == 1)
                {
                    enemy[2].live = 0;
                    you.bulletSet.anim_bool = 1;
                    you.bulletSet.live = 0;
                }

            if (you.bulletSet.dx <= enemy[3].xPos + 0.05 && you.bulletSet.dx >= enemy[3].xPos - 0.05 && enemy[3].live == 1)
                if (you.bulletSet.dy <= enemy[3].yPos + 0.05 && you.bulletSet.dy >= enemy[3].yPos - 0.05 && enemy[3].live == 1)
                {
                    enemy[3].live = 0;
                    you.bulletSet.anim_bool = 1;
                    you.bulletSet.live = 0;
                }


        }
        else
        {
            you.bulletSet.anim_bool = 1;
            you.bulletSet.live = 0;
        }
    }
    else
    {
        you.bulletSet.dx = you.xPos;
        you.bulletSet.dy = you.yPos;
        you.bulletSet.angle_bull = you.angle;
    }
}

void draw_bullet_enemy_one()
{
    if (enemy[0].bulletSet.live == 1)
    {
        if (enemy[0].bulletSet.dx < 0.92 && enemy[0].bulletSet.dx > -0.92 && enemy[0].bulletSet.dy < 0.92 && enemy[0].bulletSet.dy > -0.92)
        {
            for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
            {
                if (bricksLoc[i][0] == 1)
                {
                    if (
                            (bricksLoc[i][2] - 0.001 <= enemy[0].bulletSet.dy && bricksLoc[i][2] + 0.055 >= enemy[0].bulletSet.dy)
                            &&
                            (bricksLoc[i][1] - 0.001 - 0.015 <= enemy[0].bulletSet.dx && bricksLoc[i][1] + 0.055 >= enemy[0].bulletSet.dx)
                            )
                    {
                        enemy[0].bulletSet.anim_bool = 1;
                        bricksLoc[i][0] = 0;
                        enemy[0].bulletSet.live = 0;
                        break;
                    }
                }
            }

            for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
            {
                if (cementLoc[i][0] == 0)
                {
                    if (
                            (cementLoc[i][2] - 0.001 <= enemy[0].bulletSet.dy && cementLoc[i][2] + 0.055 >= enemy[0].bulletSet.dy)
                            &&
                            (cementLoc[i][1] - 0.001 - 0.015 <= enemy[0].bulletSet.dx && cementLoc[i][1] + 0.055 >= enemy[0].bulletSet.dx)
                            )
                    {
                        enemy[0].bulletSet.anim_bool = 1;
                        cementLoc[i][0] = 0;
                        enemy[0].bulletSet.live = 0;
                        break;
                    }
                }
            }

            glColor3f(0.502f, 0.502f, 0.502f);
            if (enemy[0].bulletSet.angle_bull == 0.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[0].bulletSet.dx - 0.004, enemy[0].bulletSet.dy);
                glVertex2d(enemy[0].bulletSet.dx + 0.004, enemy[0].bulletSet.dy);

                glVertex2d(enemy[0].bulletSet.dx - 0.004, enemy[0].bulletSet.dy + 0.01);
                glVertex2d(enemy[0].bulletSet.dx + 0.004, enemy[0].bulletSet.dy + 0.01);

                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy + 0.015);
                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy + 0.015);



                glEnd();
                enemy[0].bulletSet.dy += 0.01;
            }
            if (enemy[0].bulletSet.angle_bull == 180.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[0].bulletSet.dx - 0.004, enemy[0].bulletSet.dy);
                glVertex2d(enemy[0].bulletSet.dx + 0.004, enemy[0].bulletSet.dy);

                glVertex2d(enemy[0].bulletSet.dx - 0.004, enemy[0].bulletSet.dy - 0.01);
                glVertex2d(enemy[0].bulletSet.dx + 0.004, enemy[0].bulletSet.dy - 0.01);

                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy - 0.015);
                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy - 0.015);
                glEnd();
                enemy[0].bulletSet.dy -= 0.01;
            }
            if (enemy[0].bulletSet.angle_bull == 270.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy - 0.004);
                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy + 0.004);

                glVertex2d(enemy[0].bulletSet.dx + 0.01, enemy[0].bulletSet.dy - 0.004);
                glVertex2d(enemy[0].bulletSet.dx + 0.01, enemy[0].bulletSet.dy + 0.004);

                glVertex2d(enemy[0].bulletSet.dx + 0.015, enemy[0].bulletSet.dy);
                glVertex2d(enemy[0].bulletSet.dx + 0.015, enemy[0].bulletSet.dy);
                glEnd();

                enemy[0].bulletSet.dx += 0.01;
            }
            if (enemy[0].bulletSet.angle_bull == 90.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy - 0.004);
                glVertex2d(enemy[0].bulletSet.dx, enemy[0].bulletSet.dy + 0.004);

                glVertex2d(enemy[0].bulletSet.dx - 0.01, enemy[0].bulletSet.dy - 0.004);
                glVertex2d(enemy[0].bulletSet.dx - 0.01, enemy[0].bulletSet.dy + 0.004);

                glVertex2d(enemy[0].bulletSet.dx - 0.015, enemy[0].bulletSet.dy);
                glVertex2d(enemy[0].bulletSet.dx - 0.015, enemy[0].bulletSet.dy);
                glEnd();
                enemy[0].bulletSet.dx -= 0.01;

            }
            if (enemy[0].bulletSet.dx <= you.xPos + 0.05 && enemy[0].bulletSet.dx >= you.xPos - 0.05 && you.live == 1 && enemy[0].live == 1)
                if (enemy[0].bulletSet.dy <= you.yPos + 0.05 && enemy[0].bulletSet.dy >= you.yPos - 0.05 && you.live == 1 && enemy[0].live == 1)
                {
                    you.live = 0;
                    enemy[0].bulletSet.anim_bool = 1;
                    enemy[0].bulletSet.live = 0;
                }

        }
        else
        {
            enemy[0].bulletSet.anim_bool = 1;
            enemy[0].bulletSet.live = 0;
        }
    }
    else
    {
        enemy[0].bulletSet.dx = enemy[0].xPos;
        enemy[0].bulletSet.dy = enemy[0].yPos;
        enemy[0].bulletSet.angle_bull = you.angle;
    }
}

void draw_bullet_effects_for_enemy_one()
{
    double anim_x;
    double anim_y;

    if (enemy[0].bulletSet.time_anim == 0)
    {
        enemy[0].bulletSet.an_x = enemy[0].bulletSet.dx;
        enemy[0].bulletSet.an_y = enemy[0].bulletSet.dy;
    }

    anim_x = enemy[0].bulletSet.an_x;
    anim_y = enemy[0].bulletSet.an_y;

    GLfloat colors[10][3] = {
            {1.0f, 1.0f, 1.0f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
    };

    if (enemy[0].bulletSet.anim_bool == 1 && enemy[0].bulletSet.time_anim < BOOM_ANIMATION_FRAMES) {

        int randomIndex = rand() % 3;

        glColor3fv(colors[randomIndex]);

        glBegin(GL_POINTS);
        for (int i = 0; i < 30; ++i) {
            float angle = 2 * 3.14159516 * rand() / RAND_MAX;
            float radius = 0.05 * rand() / RAND_MAX;
            glVertex2f(anim_x + radius * cos(angle), anim_y + radius * sin(angle));
        }
        enemy[0].bulletSet.time_anim += 1;
        glEnd();
    }
    else if (enemy[0].bulletSet.time_anim == BOOM_ANIMATION_FRAMES)
    {
        enemy[0].bulletSet.anim_bool = 0;
        enemy[0].bulletSet.time_anim = 0;

    }
}

void move_and_shoot_enemy_one()
{
    if (enemy[0].live == 1) {
        if (enemy[0].timerMove < enemy[0].botSpeed)
            enemy[0].timerMove++;
        else {
            if (enemy[0].yPos == enemy[0].saveYPos && enemy[0].xPos == enemy[0].saveXPos) {
                enemy[0].flagAutoMove = 1 + (rand() % 4 - 1 + 1);
            }

            enemy[0].saveXPos = enemy[0].xPos;
            enemy[0].saveYPos = enemy[0].yPos;

            if (enemy[0].flagAutoMove == 1) {
                enemy[0].angle = 0;
            }
            else if (enemy[0].flagAutoMove == 2) {
                enemy[0].angle = 180;
            }
            else if (enemy[0].flagAutoMove == 3){
                enemy[0].angle = 90;
            }
            else if (enemy[0].flagAutoMove == 4){
                enemy[0].angle = 270;
            }

            check_block_entity_enemy_one(enemy[0].flagAutoMove);
            enemy[0].timerMove = 0;
        }

        if (enemy[0].tickToShoot < 100)
            enemy[0].tickToShoot++;
        else {

            if (enemy[0].flagAutoMove == 1) {
                enemy[0].bulletSet.angle_bull = 0;
                enemy[0].bulletSet.live = 1;
            }
            else if (enemy[0].flagAutoMove == 2) {
                enemy[0].bulletSet.angle_bull = 180;
                enemy[0].bulletSet.live = 1;
            }
            else if (enemy[0].flagAutoMove == 3){
                enemy[0].bulletSet.angle_bull = 90;
                enemy[0].bulletSet.live = 1;
            }
            else if (enemy[0].flagAutoMove == 4){
                enemy[0].bulletSet.angle_bull = 270;
                enemy[0].bulletSet.live = 1;
            }


            enemy[0].tickToShoot = 0;
        }


    }
}

void draw_bullet_enemy_two()
{
    if (enemy[1].bulletSet.live == 1)
    {
        if (enemy[1].bulletSet.dx < 0.92 && enemy[1].bulletSet.dx > -0.92 && enemy[1].bulletSet.dy < 0.92 && enemy[1].bulletSet.dy > -0.92)
        {
            for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
            {
                if (bricksLoc[i][0] == 1)
                {
                    if (
                            (bricksLoc[i][2] - 0.001 <= enemy[1].bulletSet.dy && bricksLoc[i][2] + 0.055 >= enemy[1].bulletSet.dy)
                            &&
                            (bricksLoc[i][1] - 0.001 - 0.015 <= enemy[1].bulletSet.dx && bricksLoc[i][1] + 0.055 >= enemy[1].bulletSet.dx)
                            )
                    {
                        enemy[1].bulletSet.anim_bool = 1;
                        bricksLoc[i][0] = 0;
                        enemy[1].bulletSet.live = 0;
                        break;
                    }
                }
            }

            for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
            {
                if (cementLoc[i][0] == 0)
                {
                    if (
                            (cementLoc[i][2] - 0.001 <= enemy[1].bulletSet.dy && cementLoc[i][2] + 0.055 >= enemy[1].bulletSet.dy)
                            &&
                            (cementLoc[i][1] - 0.001 - 0.015 <= enemy[1].bulletSet.dx && cementLoc[i][1] + 0.055 >= enemy[1].bulletSet.dx)
                            )
                    {
                        enemy[1].bulletSet.anim_bool = 1;
                        cementLoc[i][0] = 0;
                        enemy[1].bulletSet.live = 0;
                        break;
                    }
                }
            }

            glColor3f(0.502f, 0.502f, 0.502f);
            if (enemy[1].bulletSet.angle_bull == 0.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[1].bulletSet.dx - 0.004, enemy[1].bulletSet.dy);
                glVertex2d(enemy[1].bulletSet.dx + 0.004, enemy[1].bulletSet.dy);

                glVertex2d(enemy[1].bulletSet.dx - 0.004, enemy[1].bulletSet.dy + 0.01);
                glVertex2d(enemy[1].bulletSet.dx + 0.004, enemy[1].bulletSet.dy + 0.01);

                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy + 0.015);
                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy + 0.015);



                glEnd();
                enemy[1].bulletSet.dy += 0.01;
            }
            if (enemy[1].bulletSet.angle_bull == 180.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[1].bulletSet.dx - 0.004, enemy[1].bulletSet.dy);
                glVertex2d(enemy[1].bulletSet.dx + 0.004, enemy[1].bulletSet.dy);

                glVertex2d(enemy[1].bulletSet.dx - 0.004, enemy[1].bulletSet.dy - 0.01);
                glVertex2d(enemy[1].bulletSet.dx + 0.004, enemy[1].bulletSet.dy - 0.01);

                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy - 0.015);
                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy - 0.015);
                glEnd();
                enemy[1].bulletSet.dy -= 0.01;
            }
            if (enemy[1].bulletSet.angle_bull == 270.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy - 0.004);
                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy + 0.004);

                glVertex2d(enemy[1].bulletSet.dx + 0.01, enemy[1].bulletSet.dy - 0.004);
                glVertex2d(enemy[1].bulletSet.dx + 0.01, enemy[1].bulletSet.dy + 0.004);

                glVertex2d(enemy[1].bulletSet.dx + 0.015, enemy[1].bulletSet.dy);
                glVertex2d(enemy[1].bulletSet.dx + 0.015, enemy[1].bulletSet.dy);
                glEnd();

                enemy[1].bulletSet.dx += 0.01;
            }
            if (enemy[1].bulletSet.angle_bull == 90.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy - 0.004);
                glVertex2d(enemy[1].bulletSet.dx, enemy[1].bulletSet.dy + 0.004);

                glVertex2d(enemy[1].bulletSet.dx - 0.01, enemy[1].bulletSet.dy - 0.004);
                glVertex2d(enemy[1].bulletSet.dx - 0.01, enemy[1].bulletSet.dy + 0.004);

                glVertex2d(enemy[1].bulletSet.dx - 0.015, enemy[1].bulletSet.dy);
                glVertex2d(enemy[1].bulletSet.dx - 0.015, enemy[1].bulletSet.dy);
                glEnd();
                enemy[1].bulletSet.dx -= 0.01;

            }
            if (enemy[1].bulletSet.dx <= you.xPos + 0.05 && enemy[1].bulletSet.dx >= you.xPos - 0.05 && you.live == 1 && enemy[1].live == 1)
                if (enemy[1].bulletSet.dy <= you.yPos + 0.05 && enemy[1].bulletSet.dy >= you.yPos - 0.05 && you.live == 1 && enemy[1].live == 1)
                {
                    you.live = 0;
                    enemy[1].bulletSet.anim_bool = 1;
                    enemy[1].bulletSet.live = 0;
                }

        }
        else
        {
            enemy[1].bulletSet.anim_bool = 1;
            enemy[1].bulletSet.live = 0;
        }
    }
    else
    {
        enemy[1].bulletSet.dx = enemy[1].xPos;
        enemy[1].bulletSet.dy = enemy[1].yPos;
        enemy[1].bulletSet.angle_bull = you.angle;
    }
}

void draw_bullet_effects_for_enemy_two()
{
    double anim_x;
    double anim_y;

    if (enemy[1].bulletSet.time_anim == 0)
    {
        enemy[1].bulletSet.an_x = enemy[1].bulletSet.dx;
        enemy[1].bulletSet.an_y = enemy[1].bulletSet.dy;
    }

    anim_x = enemy[1].bulletSet.an_x;
    anim_y = enemy[1].bulletSet.an_y;

    GLfloat colors[10][3] = {
            {1.0f, 1.0f, 1.0f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
    };

    if (enemy[1].bulletSet.anim_bool == 1 && enemy[1].bulletSet.time_anim < BOOM_ANIMATION_FRAMES) {

        int randomIndex = rand() % 3;

        glColor3fv(colors[randomIndex]);

        glBegin(GL_POINTS);
        for (int i = 0; i < 30; ++i) {
            float angle = 2 * 3.14159516 * rand() / RAND_MAX;
            float radius = 0.05 * rand() / RAND_MAX;
            glVertex2f(anim_x + radius * cos(angle), anim_y + radius * sin(angle));
        }
        enemy[1].bulletSet.time_anim += 1;
        glEnd();
    }
    else if (enemy[1].bulletSet.time_anim == BOOM_ANIMATION_FRAMES)
    {
        enemy[1].bulletSet.anim_bool = 0;
        enemy[1].bulletSet.time_anim = 0;

    }
}

void move_and_shoot_enemy_two()
{
    if (enemy[1].live == 1) {
        if (enemy[1].timerMove < enemy[1].botSpeed)
            enemy[1].timerMove++;
        else {
            if (enemy[1].yPos == enemy[1].saveYPos && enemy[1].xPos == enemy[1].saveXPos) {
                enemy[1].flagAutoMove = 1 + (rand() % 4 - 1 + 1);
            }

            enemy[1].saveXPos = enemy[1].xPos;
            enemy[1].saveYPos = enemy[1].yPos;

            if (enemy[1].flagAutoMove == 1) {
                enemy[1].angle = 0;
            }
            else if (enemy[1].flagAutoMove == 2) {
                enemy[1].angle = 180;
            }
            else if (enemy[1].flagAutoMove == 3){
                enemy[1].angle = 90;
            }
            else if (enemy[1].flagAutoMove == 4){
                enemy[1].angle = 270;
            }

            check_block_entity_enemy_two(enemy[1].flagAutoMove);
            enemy[1].timerMove = 0;
        }

        if (enemy[1].tickToShoot < 100)
            enemy[1].tickToShoot++;
        else {

            if (enemy[1].flagAutoMove == 1) {
                enemy[1].bulletSet.angle_bull = 0;
                enemy[1].bulletSet.live = 1;
            }
            else if (enemy[1].flagAutoMove == 2) {
                enemy[1].bulletSet.angle_bull = 180;
                enemy[1].bulletSet.live = 1;
            }
            else if (enemy[1].flagAutoMove == 3){
                enemy[1].bulletSet.angle_bull = 90;
                enemy[1].bulletSet.live = 1;
            }
            else if (enemy[1].flagAutoMove == 4){
                enemy[1].bulletSet.angle_bull = 270;
                enemy[1].bulletSet.live = 1;
            }


            enemy[1].tickToShoot = 0;
        }


    }
}

void draw_bullet_enemy_three()
{
    if (enemy[2].bulletSet.live == 1)
    {
        if (enemy[2].bulletSet.dx < 0.92 && enemy[2].bulletSet.dx > -0.92 && enemy[2].bulletSet.dy < 0.92 && enemy[2].bulletSet.dy > -0.92)
        {
            for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
            {
                if (bricksLoc[i][0] == 1)
                {
                    if (
                            (bricksLoc[i][2] - 0.001 <= enemy[2].bulletSet.dy && bricksLoc[i][2] + 0.055 >= enemy[2].bulletSet.dy)
                            &&
                            (bricksLoc[i][1] - 0.001 - 0.015 <= enemy[2].bulletSet.dx && bricksLoc[i][1] + 0.055 >= enemy[2].bulletSet.dx)
                            )
                    {
                        enemy[2].bulletSet.anim_bool = 1;
                        bricksLoc[i][0] = 0;
                        enemy[2].bulletSet.live = 0;
                        break;
                    }
                }
            }

            for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
            {
                if (cementLoc[i][0] == 0)
                {
                    if (
                            (cementLoc[i][2] - 0.001 <= enemy[2].bulletSet.dy && cementLoc[i][2] + 0.055 >= enemy[2].bulletSet.dy)
                            &&
                            (cementLoc[i][1] - 0.001 - 0.015 <= enemy[2].bulletSet.dx && cementLoc[i][1] + 0.055 >= enemy[2].bulletSet.dx)
                            )
                    {
                        enemy[2].bulletSet.anim_bool = 1;
                        cementLoc[i][0] = 0;
                        enemy[2].bulletSet.live = 0;
                        break;
                    }
                }
            }

            glColor3f(0.502f, 0.502f, 0.502f);
            if (enemy[2].bulletSet.angle_bull == 0.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[2].bulletSet.dx - 0.004, enemy[2].bulletSet.dy);
                glVertex2d(enemy[2].bulletSet.dx + 0.004, enemy[2].bulletSet.dy);

                glVertex2d(enemy[2].bulletSet.dx - 0.004, enemy[2].bulletSet.dy + 0.01);
                glVertex2d(enemy[2].bulletSet.dx + 0.004, enemy[2].bulletSet.dy + 0.01);

                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy + 0.015);
                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy + 0.015);



                glEnd();
                enemy[2].bulletSet.dy += 0.01;
            }
            if (enemy[2].bulletSet.angle_bull == 180.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[2].bulletSet.dx - 0.004, enemy[2].bulletSet.dy);
                glVertex2d(enemy[2].bulletSet.dx + 0.004, enemy[2].bulletSet.dy);

                glVertex2d(enemy[2].bulletSet.dx - 0.004, enemy[2].bulletSet.dy - 0.01);
                glVertex2d(enemy[2].bulletSet.dx + 0.004, enemy[2].bulletSet.dy - 0.01);

                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy - 0.015);
                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy - 0.015);
                glEnd();
                enemy[2].bulletSet.dy -= 0.01;
            }
            if (enemy[2].bulletSet.angle_bull == 270.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy - 0.004);
                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy + 0.004);

                glVertex2d(enemy[2].bulletSet.dx + 0.01, enemy[2].bulletSet.dy - 0.004);
                glVertex2d(enemy[2].bulletSet.dx + 0.01, enemy[2].bulletSet.dy + 0.004);

                glVertex2d(enemy[2].bulletSet.dx + 0.015, enemy[2].bulletSet.dy);
                glVertex2d(enemy[2].bulletSet.dx + 0.015, enemy[2].bulletSet.dy);
                glEnd();

                enemy[2].bulletSet.dx += 0.01;
            }
            if (enemy[2].bulletSet.angle_bull == 90.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy - 0.004);
                glVertex2d(enemy[2].bulletSet.dx, enemy[2].bulletSet.dy + 0.004);

                glVertex2d(enemy[2].bulletSet.dx - 0.01, enemy[2].bulletSet.dy - 0.004);
                glVertex2d(enemy[2].bulletSet.dx - 0.01, enemy[2].bulletSet.dy + 0.004);

                glVertex2d(enemy[2].bulletSet.dx - 0.015, enemy[2].bulletSet.dy);
                glVertex2d(enemy[2].bulletSet.dx - 0.015, enemy[2].bulletSet.dy);
                glEnd();
                enemy[2].bulletSet.dx -= 0.01;

            }
            if (enemy[2].bulletSet.dx <= you.xPos + 0.05 && enemy[2].bulletSet.dx >= you.xPos - 0.05 && you.live == 1 && enemy[2].live == 1)
                if (enemy[2].bulletSet.dy <= you.yPos + 0.05 && enemy[2].bulletSet.dy >= you.yPos - 0.05 && you.live == 1 && enemy[2].live == 1)
                {
                    you.live = 0;
                    enemy[2].bulletSet.anim_bool = 1;
                    enemy[2].bulletSet.live = 0;
                }

        }
        else
        {
            enemy[2].bulletSet.anim_bool = 1;
            enemy[2].bulletSet.live = 0;
        }
    }
    else
    {
        enemy[2].bulletSet.dx = enemy[2].xPos;
        enemy[2].bulletSet.dy = enemy[2].yPos;
        enemy[2].bulletSet.angle_bull = you.angle;
    }
}

void draw_bullet_effects_for_enemy_three()
{
    double anim_x;
    double anim_y;

    if (enemy[2].bulletSet.time_anim == 0)
    {
        enemy[2].bulletSet.an_x = enemy[2].bulletSet.dx;
        enemy[2].bulletSet.an_y = enemy[2].bulletSet.dy;
    }

    anim_x = enemy[2].bulletSet.an_x;
    anim_y = enemy[2].bulletSet.an_y;

    GLfloat colors[10][3] = {
            {1.0f, 1.0f, 1.0f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
    };

    if (enemy[2].bulletSet.anim_bool == 1 && enemy[2].bulletSet.time_anim < BOOM_ANIMATION_FRAMES) {

        int randomIndex = rand() % 3;

        glColor3fv(colors[randomIndex]);

        glBegin(GL_POINTS);
        for (int i = 0; i < 30; ++i) {
            float angle = 2 * 3.14159516 * rand() / RAND_MAX;
            float radius = 0.05 * rand() / RAND_MAX;
            glVertex2f(anim_x + radius * cos(angle), anim_y + radius * sin(angle));
        }
        enemy[2].bulletSet.time_anim += 1;
        glEnd();
    }
    else if (enemy[2].bulletSet.time_anim == BOOM_ANIMATION_FRAMES)
    {
        enemy[2].bulletSet.anim_bool = 0;
        enemy[2].bulletSet.time_anim = 0;

    }
}

void move_and_shoot_enemy_three()
{
    if (enemy[2].live == 1) {
        if (enemy[2].timerMove < enemy[2].botSpeed)
            enemy[2].timerMove++;
        else {
            if (enemy[2].yPos == enemy[2].saveYPos && enemy[2].xPos == enemy[2].saveXPos) {
                enemy[2].flagAutoMove = 1 + (rand() % 4 - 1 + 1);
            }

            enemy[2].saveXPos = enemy[2].xPos;
            enemy[2].saveYPos = enemy[2].yPos;

            if (enemy[2].flagAutoMove == 1) {
                enemy[2].angle = 0;
            }
            else if (enemy[2].flagAutoMove == 2) {
                enemy[2].angle = 180;
            }
            else if (enemy[2].flagAutoMove == 3){
                enemy[2].angle = 90;
            }
            else if (enemy[2].flagAutoMove == 4){
                enemy[2].angle = 270;
            }

            check_block_entity_enemy_three(enemy[2].flagAutoMove);
            enemy[2].timerMove = 0;
        }

        if (enemy[2].tickToShoot < 100)
            enemy[2].tickToShoot++;
        else {

            if (enemy[2].flagAutoMove == 1) {
                enemy[2].bulletSet.angle_bull = 0;
                enemy[2].bulletSet.live = 1;
            }
            else if (enemy[2].flagAutoMove == 2) {
                enemy[2].bulletSet.angle_bull = 180;
                enemy[2].bulletSet.live = 1;
            }
            else if (enemy[2].flagAutoMove == 3){
                enemy[2].bulletSet.angle_bull = 90;
                enemy[2].bulletSet.live = 1;
            }
            else if (enemy[2].flagAutoMove == 4){
                enemy[2].bulletSet.angle_bull = 270;
                enemy[2].bulletSet.live = 1;
            }
            enemy[2].tickToShoot = 0;
        }
    }
}

void draw_bullet_enemy_four()
{
    if (enemy[3].bulletSet.live == 1)
    {
        if (enemy[3].bulletSet.dx < 0.92 && enemy[3].bulletSet.dx > -0.92 && enemy[3].bulletSet.dy < 0.92 && enemy[3].bulletSet.dy > -0.92)
        {
            for (int i = 0; i < NUM_OF_MINI_BRICKS_BLOCKS; i++)
            {
                if (bricksLoc[i][0] == 1)
                {
                    if (
                            (bricksLoc[i][2] - 0.001 <= enemy[3].bulletSet.dy && bricksLoc[i][2] + 0.055 >= enemy[3].bulletSet.dy)
                            &&
                            (bricksLoc[i][1] - 0.001 - 0.015 <= enemy[3].bulletSet.dx && bricksLoc[i][1] + 0.055 >= enemy[3].bulletSet.dx)
                            )
                    {
                        enemy[3].bulletSet.anim_bool = 1;
                        bricksLoc[i][0] = 0;
                        enemy[3].bulletSet.live = 0;
                        break;
                    }
                }
            }

            for (int i = 0; i < NUM_OF_MINI_CEMENT_BLOCKS; i++)
            {
                if (cementLoc[i][0] == 0)
                {
                    if (
                            (cementLoc[i][2] - 0.001 <= enemy[3].bulletSet.dy && cementLoc[i][2] + 0.055 >= enemy[3].bulletSet.dy)
                            &&
                            (cementLoc[i][1] - 0.001 - 0.015 <= enemy[3].bulletSet.dx && cementLoc[i][1] + 0.055 >= enemy[3].bulletSet.dx)
                            )
                    {
                        enemy[3].bulletSet.anim_bool = 1;
                        cementLoc[i][0] = 0;
                        enemy[3].bulletSet.live = 0;
                        break;
                    }
                }
            }

            glColor3f(0.502f, 0.502f, 0.502f);
            if (enemy[3].bulletSet.angle_bull == 0.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[3].bulletSet.dx - 0.004, enemy[3].bulletSet.dy);
                glVertex2d(enemy[3].bulletSet.dx + 0.004, enemy[3].bulletSet.dy);

                glVertex2d(enemy[3].bulletSet.dx - 0.004, enemy[3].bulletSet.dy + 0.01);
                glVertex2d(enemy[3].bulletSet.dx + 0.004, enemy[3].bulletSet.dy + 0.01);

                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy + 0.015);
                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy + 0.015);



                glEnd();
                enemy[3].bulletSet.dy += 0.01;
            }
            if (enemy[3].bulletSet.angle_bull == 180.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[3].bulletSet.dx - 0.004, enemy[3].bulletSet.dy);
                glVertex2d(enemy[3].bulletSet.dx + 0.004, enemy[3].bulletSet.dy);

                glVertex2d(enemy[3].bulletSet.dx - 0.004, enemy[3].bulletSet.dy - 0.01);
                glVertex2d(enemy[3].bulletSet.dx + 0.004, enemy[3].bulletSet.dy - 0.01);

                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy - 0.015);
                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy - 0.015);
                glEnd();
                enemy[3].bulletSet.dy -= 0.01;
            }
            if (enemy[3].bulletSet.angle_bull == 270.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy - 0.004);
                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy + 0.004);

                glVertex2d(enemy[3].bulletSet.dx + 0.01, enemy[3].bulletSet.dy - 0.004);
                glVertex2d(enemy[3].bulletSet.dx + 0.01, enemy[3].bulletSet.dy + 0.004);

                glVertex2d(enemy[3].bulletSet.dx + 0.015, enemy[3].bulletSet.dy);
                glVertex2d(enemy[3].bulletSet.dx + 0.015, enemy[3].bulletSet.dy);
                glEnd();

                enemy[3].bulletSet.dx += 0.01;
            }
            if (enemy[3].bulletSet.angle_bull == 90.0)
            {
                glPointSize(5.0f);
                glBegin(GL_POINTS);

                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy - 0.004);
                glVertex2d(enemy[3].bulletSet.dx, enemy[3].bulletSet.dy + 0.004);

                glVertex2d(enemy[3].bulletSet.dx - 0.01, enemy[3].bulletSet.dy - 0.004);
                glVertex2d(enemy[3].bulletSet.dx - 0.01, enemy[3].bulletSet.dy + 0.004);

                glVertex2d(enemy[3].bulletSet.dx - 0.015, enemy[3].bulletSet.dy);
                glVertex2d(enemy[3].bulletSet.dx - 0.015, enemy[3].bulletSet.dy);
                glEnd();
                enemy[3].bulletSet.dx -= 0.01;

            }
            if (enemy[3].bulletSet.dx <= you.xPos + 0.05 && enemy[3].bulletSet.dx >= you.xPos - 0.05 && you.live == 1 && enemy[3].live == 1)
                if (enemy[3].bulletSet.dy <= you.yPos + 0.05 && enemy[3].bulletSet.dy >= you.yPos - 0.05 && you.live == 1 && enemy[3].live == 1)
                {
                    you.live = 0;
                    enemy[3].bulletSet.anim_bool = 1;
                    enemy[3].bulletSet.live = 0;
                }

        }
        else
        {
            enemy[3].bulletSet.anim_bool = 1;
            enemy[3].bulletSet.live = 0;
        }
    }
    else
    {
        enemy[3].bulletSet.dx = enemy[3].xPos;
        enemy[3].bulletSet.dy = enemy[3].yPos;
        enemy[3].bulletSet.angle_bull = you.angle;
    }
}

void draw_bullet_effects_for_enemy_four()
{
    double anim_x;
    double anim_y;

    if (enemy[3].bulletSet.time_anim == 0)
    {
        enemy[3].bulletSet.an_x = enemy[3].bulletSet.dx;
        enemy[3].bulletSet.an_y = enemy[3].bulletSet.dy;
    }

    anim_x = enemy[3].bulletSet.an_x;
    anim_y = enemy[3].bulletSet.an_y;

    GLfloat colors[10][3] = {
            {1.0f, 1.0f, 1.0f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.525f, 0.125f, 0.437f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
            {0.878f, 0.227f, 0.020f},
    };

    if (enemy[3].bulletSet.anim_bool == 1 && enemy[3].bulletSet.time_anim < BOOM_ANIMATION_FRAMES) {

        int randomIndex = rand() % 3;

        glColor3fv(colors[randomIndex]);

        glBegin(GL_POINTS);
        for (int i = 0; i < 30; ++i) {
            float angle = 2 * 3.14159516 * rand() / RAND_MAX;
            float radius = 0.05 * rand() / RAND_MAX;
            glVertex2f(anim_x + radius * cos(angle), anim_y + radius * sin(angle));
        }
        enemy[3].bulletSet.time_anim += 1;
        glEnd();
    }
    else if (enemy[3].bulletSet.time_anim == BOOM_ANIMATION_FRAMES)
    {
        enemy[3].bulletSet.anim_bool = 0;
        enemy[3].bulletSet.time_anim = 0;

    }
}

void move_and_shoot_enemy_four()
{
    if (enemy[3].live == 1) {
        if (enemy[3].timerMove < enemy[3].botSpeed)
            enemy[3].timerMove++;
        else {
            if (enemy[3].yPos == enemy[3].saveYPos && enemy[3].xPos == enemy[3].saveXPos) {
                enemy[3].flagAutoMove = 1 + (rand() % 4 - 1 + 1);
            }

            enemy[3].saveXPos = enemy[3].xPos;
            enemy[3].saveYPos = enemy[3].yPos;

            if (enemy[3].flagAutoMove == 1) {
                enemy[3].angle = 0;
            }
            else if (enemy[3].flagAutoMove == 2) {
                enemy[3].angle = 180;
            }
            else if (enemy[3].flagAutoMove == 3){
                enemy[3].angle = 90;
            }
            else if (enemy[3].flagAutoMove == 4){
                enemy[3].angle = 270;
            }

            check_block_entity_enemy_four(enemy[3].flagAutoMove);
            enemy[3].timerMove = 0;
        }

        if (enemy[3].tickToShoot < 100)
            enemy[3].tickToShoot++;
        else {

            if (enemy[3].flagAutoMove == 1) {
                enemy[3].bulletSet.angle_bull = 0;
                enemy[3].bulletSet.live = 1;
            }
            else if (enemy[3].flagAutoMove == 2) {
                enemy[3].bulletSet.angle_bull = 180;
                enemy[3].bulletSet.live = 1;
            }
            else if (enemy[3].flagAutoMove == 3){
                enemy[3].bulletSet.angle_bull = 90;
                enemy[3].bulletSet.live = 1;
            }
            else if (enemy[3].flagAutoMove == 4){
                enemy[3].bulletSet.angle_bull = 270;
                enemy[3].bulletSet.live = 1;
            }


            enemy[3].tickToShoot = 0;
        }


    }
}

void lose_window(){

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(165, 150, 0);
    glScalef(0.1, 0.1, 0.1);


    char* text = "YOU LOSE";
    int len = strlen(text);
    for (int i = 0; i < len; ++i) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }

    glPopMatrix();
    glFlush();
}

void win_window(){

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(165, 150, 0);
    glScalef(0.1, 0.1, 0.1);


    char* text = "YOU WIN";
    int len = strlen(text);
    for (int i = 0; i < len; ++i) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }

    glPopMatrix();
    glFlush();
}

void update(int value) {

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void menu() {

    if (menuChoose == 0) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0, 0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 400.0, 0.0, 300.0);

        glColor3f(1.0, 1.0, 1.0);

        glPushMatrix();
        glTranslatef(165, 160, 0);
        glScalef(0.1, 0.1, 0.1);

        char *text = "1 EASY";
        int len = strlen(text);
        for (int i = 0; i < len; ++i) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
        }


        glPushMatrix();
        glTranslatef(-500, 150, 0);

        char *text1 = "2 HARD";
        int len1 = strlen(text1);
        for (int i = 0; i < len1; ++i) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, text1[i]);
        }

        glPushMatrix();
        glTranslatef(-515, 150, 0);


        char *text2 = "3 ULTRA HARD";
        int len2 = strlen(text2);
        for (int i = 0; i < len2; ++i) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, text2[i]);
        }

        glPopMatrix();

        glFlush();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (menuChoose == 0) {
        menu();
    }


    if (menuChoose == 1) {

        glClearColor(0.1, 0.1, 0.1, 0);

        createBrickWall();
        createCementWall();
        draw_block_zone();
        if (you.live > 0) {
            draw_global_tank_up();
            draw_bullet_global();
            draw_bullet_effects_for_global_tank();
        }
        if (enemy[0].live == 1) {
            move_and_shoot_enemy_one();
            draw_enemy_tank_up_one();
            draw_bullet_enemy_one();
            draw_bullet_effects_for_enemy_one();
        }
        if (enemy[1].live == 1) {
            move_and_shoot_enemy_two();
            draw_enemy_tank_up_two();
            draw_bullet_enemy_two();
            draw_bullet_effects_for_enemy_two();
        }
        if (you.live == 0) {
            glClearColor(1, 0, 0, 0);
            lose_window();
        }
        if (enemy[0].live + enemy[1].live == 0) {
            glClearColor(0.0, 0.2, 0.13, 1.0);
            win_window();
        }
    }

    if (menuChoose == 2) {

        glClearColor(0.1, 0.1, 0.1, 0);

        createBrickWall();
        createCementWall();
        draw_block_zone();
        if (you.live > 0) {
            draw_global_tank_up();
            draw_bullet_global();
            draw_bullet_effects_for_global_tank();
        }
        if (enemy[0].live == 1) {
            move_and_shoot_enemy_one();
            draw_enemy_tank_up_one();
            draw_bullet_enemy_one();
            draw_bullet_effects_for_enemy_one();
        }
        if (enemy[1].live == 1) {
            move_and_shoot_enemy_two();
            draw_enemy_tank_up_two();
            draw_bullet_enemy_two();
            draw_bullet_effects_for_enemy_two();
        }

        if (enemy[2].live == 1) {
            move_and_shoot_enemy_three();
            draw_enemy_tank_up_three();
            draw_bullet_enemy_three();
            draw_bullet_effects_for_enemy_three();
        }

        if (you.live == 0) {
            glClearColor(1, 0, 0, 0);
            lose_window();
        }
        if (enemy[0].live + enemy[1].live + enemy[2].live == 0) {
            glClearColor(0.0, 0.2, 0.13, 1.0);
            win_window();
        }
    }

    if (menuChoose == 3) {

        glClearColor(0.1, 0.1, 0.1, 0);

        createBrickWall();
        createCementWall();
        draw_block_zone();
        if (you.live > 0) {
            draw_global_tank_up();
            draw_bullet_global();
            draw_bullet_effects_for_global_tank();
        }
        if (enemy[0].live == 1) {
            move_and_shoot_enemy_one();
            draw_enemy_tank_up_one();
            draw_bullet_enemy_one();
            draw_bullet_effects_for_enemy_one();
        }
        if (enemy[1].live == 1) {
            move_and_shoot_enemy_two();
            draw_enemy_tank_up_two();
            draw_bullet_enemy_two();
            draw_bullet_effects_for_enemy_two();
        }

        if (enemy[2].live == 1) {
            move_and_shoot_enemy_three();
            draw_enemy_tank_up_three();
            draw_bullet_enemy_three();
            draw_bullet_effects_for_enemy_three();
        }

        if (enemy[3].live == 1) {
            move_and_shoot_enemy_four();
            draw_enemy_tank_up_four();
            draw_bullet_enemy_four();
            draw_bullet_effects_for_enemy_four();
        }

        if (you.live == 0) {
            glClearColor(1, 0, 0, 0);
            lose_window();
        }
        if (enemy[0].live + enemy[1].live + enemy[2].live + enemy[3].live == 0) {
            glClearColor(0.0, 0.2, 0.13, 1.0);
            win_window();
        }
    }

    glutSwapBuffers();
}

void keyboard(char key) {

    if (menuChoose == 0) {
        switch (key) {
            case '1':
                menuChoose = 1;
                enemy[0].botSpeed = 10;
                enemy[1].botSpeed = 10;
                FILE* fileCem = fopen("map\\cementLocFirst.txt", "r");
                int N;
                fscanf(fileCem, "%d\n", &N);
                double a, b, c;
                for (int i = 0; i < N; i++) {
                    fscanf(fileCem, "%lf %lf %lf\n", &a, &b, &c);
                    cementLoc[i][0] = a;
                    cementLoc[i][1] = b;
                    cementLoc[i][2] = c;
                }
                fclose(fileCem);

                FILE* fileBri = fopen("map\\bricksLocFirst.txt", "r");
                fscanf(fileBri, "%d\n", &N);
                for (int i = 0; i < N; i++) {
                    fscanf(fileBri, "%lf %lf %lf\n", &a, &b, &c);
                    bricksLoc[i][0] = a;
                    bricksLoc[i][1] = b;
                    bricksLoc[i][2] = c;
                }
                fclose(fileBri);
                break;
            case '2':

                menuChoose = 2;
                enemy[0].botSpeed = 5;
                enemy[1].botSpeed = 5;
                enemy[2].botSpeed = 5;
                fileCem = fopen("map\\cementLocSecond.txt", "r");
                fscanf(fileCem, "%d\n", &N);
                for (int i = 0; i < N; i++) {
                    fscanf(fileCem, "%lf %lf %lf\n", &a, &b, &c);
                    cementLoc[i][0] = a;
                    cementLoc[i][1] = b;
                    cementLoc[i][2] = c;
                }
                fclose(fileCem);

                fileBri = fopen("map\\bricksLocSecond.txt", "r");
                fscanf(fileBri, "%d\n", &N);
                for (int i = 0; i < N; i++) {
                    fscanf(fileBri, "%lf %lf %lf\n", &a, &b, &c);
                    bricksLoc[i][0] = a;
                    bricksLoc[i][1] = b;
                    bricksLoc[i][2] = c;
                }
                fclose(fileBri);

                enemy[2].xPos = 0.025;
                enemy[2].yPos = 0.8;
                enemy[2].angle = 180;

                break;
            case '3':
                menuChoose = 3;
                enemy[0].botSpeed = 3;
                enemy[1].botSpeed = 3;
                enemy[2].botSpeed = 3;
                enemy[3].botSpeed = 3;
                fileCem = fopen("map\\cementLocThird.txt", "r");
                fscanf(fileCem, "%d\n", &N);
                for (int i = 0; i < N; i++) {
                    fscanf(fileCem, "%lf %lf %lf\n", &a, &b, &c);
                    cementLoc[i][0] = a;
                    cementLoc[i][1] = b;
                    cementLoc[i][2] = c;
                }
                fclose(fileCem);

                fileBri = fopen("map\\bricksLocThird.txt", "r");
                fscanf(fileBri, "%d\n", &N);
                for (int i = 0; i < N; i++) {
                    fscanf(fileBri, "%lf %lf %lf\n", &a, &b, &c);
                    bricksLoc[i][0] = a;
                    bricksLoc[i][1] = b;
                    bricksLoc[i][2] = c;
                }
                fclose(fileBri);

                enemy[2].xPos = 0.25;
                enemy[2].yPos = 0.5;
                enemy[2].angle = 180;

                enemy[3].xPos = -0.25;
                enemy[3].yPos = 0.7;
                enemy[3].angle = 180;
                break;
        }
    } else {
        switch (key) {
            case 'w':
            case 'W':

                you.angle = 0.0;

                check_block_entity(1);

                printf("x = %f, y = %f\n", you.xPos, you.yPos);
                break;


            case 's':
            case 'S':

                you.angle = 180.0;


                check_block_entity(2);

                printf("x = %f, y = %f\n", you.xPos, you.yPos);
                break;


            case 'A':
            case 'a':


                you.angle = 90.0;

                check_block_entity(3);

                printf("x = %f, y = %f\n", you.xPos, you.yPos);

                break;
            case 'd':
            case 'D':


                you.angle = 270;


                check_block_entity(4);


                printf("x = %f, y = %f\n", you.xPos, you.yPos);

                break;
            case ' ':
                you.bulletSet.live = 1;
                break;
        }
    }
}


int main(int argc, char** argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);


    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 0);
    
    glutCreateWindow("Tanchik");
    glClearColor(0.1, 0.1, 0.1, 0);

    startSettings();
    glutTimerFunc(10, update, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc((void*)keyboard);

    glutMainLoop();
    return 0;
}
