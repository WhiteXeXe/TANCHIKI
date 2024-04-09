#include <gl/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define NUM_OF_MINI_BRICKS_BLOCKS 500
#define NUM_OF_MINI_CEMENT_BLOCKS 101
#define BOOM_ANIMATION_FRAMES 10


float moveSpeed = 0.02;

struct tankSettings
{
    float xPos;
    float yPos;
    float angle;
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

float bricksLoc[NUM_OF_MINI_BRICKS_BLOCKS][3] = {   // live, x location, y location

	{1, -0.15, -0.7},
    {1, 0.1, -0.7},
    {1, -0.2, -0.7},
    {1, 0.15, -0.7},
    {1, -0.15, -0.65},
    {1, 0.1, -0.65},
    {1, -0.2, -0.65},
    {1, 0.15, -0.65},
    {1, -0.15, -0.6},
    {1, 0.1, -0.6},
    {1, -0.2, -0.6},
    {1, 0.15, -0.6},
    {1, -0.15, -0.55},
    {1, 0.1, -0.55},
    {1, -0.2, -0.55},
    {1, 0.15, -0.55},
    {1, -0.15, -0.5},
    {1, 0.1, -0.5},
    {1, -0.2, -0.5},
    {1, 0.15, -0.5},

	{ 1, -1, -0.55 },
    {1, -0.95, -0.55},
    {1, -0.9, -0.55},
    {1, -0.85, -0.55},
    {1, -0.8, -0.55},
    {1, -0.75, -0.55},
    {1, -0.7, -0.55},
    {1, -0.65, -0.55},
    {1, -0.6, -0.55},
    {1, -0.55, -0.55},
    {1, -0.5, -0.55},
    {1, -0.45, -0.55},
    {1, -0.4, -0.55},
    {1, -0.35, -0.55},
    {1, -0.3, -0.55},
    {1, -0.25, -0.55},
    {1, -0.2, -0.55},
    {1, 0.1, -0.55},
    {1, 0.15, -0.55},
    {1, 0.2, -0.55},
    {1, 0.25, -0.55},
    {1, 0.3, -0.55},
    {1, 0.35, -0.55},
    {1, 0.4, -0.55},
    {1, 0.45, -0.55},
    {1, 0.5, -0.55},
    {1, 0.55, -0.55},
    {1, 0.6, -0.55},
    {1, 0.65, -0.55},
    {1, 0.7, -0.55},
    {1, 0.75, -0.55},
    {1, 0.8, -0.55},
    {1, 0.85, -0.55},
    {1, 0.9, -0.55},
    {1, 0.95, -0.55},
    {1, 1, -0.55},

	{1, -1, -0.5},
    {1, -0.95, -0.5},
    {1, -0.9, -0.5},
    {1, -0.85, -0.5},
    {1, -0.8, -0.5},
    {1, -0.75, -0.5},
    {1, -0.7, -0.5},
    {1, -0.65, -0.5},
    {1, -0.6, -0.5},
    {1, -0.55, -0.5},
    {1, -0.5, -0.5},
    {1, -0.45, -0.5},
    {1, -0.4, -0.5},
    {1, -0.35, -0.5},
    {1, -0.3, -0.5},
    {1, -0.25, -0.5},
    {1, -0.2, -0.5},
    {1, -0.15, -0.5},

    {1, 0.1, -0.5},
    {1, 0.15, -0.5},
    {1, 0.2, -0.5},
    {1, 0.25, -0.5},
    {1, 0.3, -0.5},
    {1, 0.35, -0.5},
    {1, 0.4, -0.5},
    {1, 0.45, -0.5},
    {1, 0.5, -0.5},
    {1, 0.55, -0.5},
    {1, 0.6, -0.5},
    {1, 0.65, -0.5},
    {1, 0.7, -0.5},
    {1, 0.75, -0.5},
    {1, 0.8, -0.5},
    {1, 0.85, -0.5},
    {1, 0.9, -0.5},
    {1, 0.95, -0.5},
    {1, 1, -0.5},

	{1, -1, -0.25},
    {1, -0.95, -0.25},
    {1, -0.9, -0.25},
    {1, -0.85, -0.25},
    {1, -0.8, -0.25},
    {1, -0.75, -0.25},
    {1, -0.7, -0.25},
    {1, -0.65, -0.25},
    {1, -0.6, -0.25},
    {1, -0.55, -0.25},
    {1, -0.5, -0.25},
    {1, -0.45, -0.25},
    {1, -0.4, -0.25},
    {1, -0.35, -0.25},
    {1, -0.3, -0.25},
    {1, -0.25, -0.25},
    {1, -0.2, -0.25},
    {1, -0.15, -0.25},
    {1, -0.1, -0.25},
    {1, -0.05, -0.25},
    {1, 0, -0.25},
    {1, 0.05, -0.25},
    {1, 0.1, -0.25},
    {1, 0.15, -0.25},
    {1, 0.2, -0.25},
    {1, 0.25, -0.25},
 
    {1, 0.4, -0.25},
    {1, 0.45, -0.25},
    {1, 0.5, -0.25},
    {1, 0.55, -0.25},
    {1, 0.6, -0.25},
    {1, 0.65, -0.25},
    {1, 0.7, -0.25},
    {1, 0.75, -0.25},
    {1, 0.8, -0.25},
    {1, 0.85, -0.25},
    {1, 0.9, -0.25},
    {1, 0.95, -0.25},
    {1, 1, -0.25},
    {1, -1, -0.3},
    {1, -0.95, -0.3},
    {1, -0.9, -0.3},
    {1, -0.85, -0.3},
    {1, -0.8, -0.3},
    {1, -0.75, -0.3},
    {1, -0.7, -0.3},
    {1, -0.65, -0.3},
    {1, -0.6, -0.3},
    {1, -0.55, -0.3},
    {1, -0.5, -0.3},
    {1, -0.45, -0.3},
    {1, -0.4, -0.3},
    {1, -0.35, -0.3},
    {1, -0.3, -0.3},
    {1, -0.25, -0.3},
    {1, -0.2, -0.3},
    {1, -0.15, -0.3},
    {1, -0.1, -0.3},
    {1, -0.05, -0.3},
    {1, 0, -0.3},
    {1, 0.05, -0.3},
    {1, 0.1, -0.3},
    {1, 0.15, -0.3},
    {1, 0.2, -0.3},
    {1, 0.25, -0.3},

    {1, 0.4, -0.3},
    {1, 0.45, -0.3},
    {1, 0.5, -0.3},
    {1, 0.55, -0.3},
    {1, 0.6, -0.3},
    {1, 0.65, -0.3},
    {1, 0.7, -0.3},
    {1, 0.75, -0.3},
    {1, 0.8, -0.3},
    {1, 0.85, -0.3},
    {1, 0.9, -0.3},
    {1, 0.95, -0.3},
    {1, 1, -0.3},

    {1, -0.7, 0.75},
    {1, -0.65, 0.75},
    {1, -0.6, 0.75},
    {1, -0.55, 0.75},
    {1, -0.5, 0.75},
    {1, -0.45, 0.75},
    {1, -0.4, 0.75},
    {1, -0.35, 0.75},
    {1, -0.3, 0.75},
    {1, -0.25, 0.75},
    {1, -0.2, 0.75},
    {1, -0.15, 0.75},
    {1, -0.1, 0.75},
    {1, -0.05, 0.75},
    {1, 0, 0.75},
    {1, 0.05, 0.75},
    {1, 0.1, 0.75},
    {1, 0.15, 0.75},
    {1, 0.2, 0.75},
    {1, 0.25, 0.75},
    
    {1, 0.4, 0.75},
    {1, 0.45, 0.75},
    {1, 0.5, 0.75},
    {1, 0.55, 0.75},
    {1, 0.6, 0.75},
    {1, 0.65, 0.75},
    {1, 0.7, 0.75},
    { 1, -0.75, 0.75 },

   
    
    {1, 0.25, -0.3},
    {1, 0.4, -0.3},
    {1, 0.45, -0.3},
    {1, 0.2, -0.25},
    {1, 0.25, -0.25},
    {1, 0.4, -0.25},
    {1, 0.45, -0.25},
    {1, 0.2, -0.2},
    {1, 0.25, -0.2},
    {1, 0.4, -0.2},
    {1, 0.45, -0.2},
    {1, 0.2, -0.15},
    {1, 0.25, -0.15},
    {1, 0.4, -0.15},
    {1, 0.45, -0.15},
    {1, 0.2, -0.1},
    {1, 0.25, -0.1},
    {1, 0.4, -0.1},
    {1, 0.45, -0.1},
    {1, 0.2, -0.05},
    {1, 0.25, -0.05},
    {1, 0.4, -0.05},
    {1, 0.45, -0.05},
    {1, 0.2, 0},
    {1, 0.25, 0},
    {1, 0.4, 0},
    {1, 0.45, 0},
    {1, 0.2, 0.05},
    {1, 0.25, 0.05},
    {1, 0.4, 0.05},
    {1, 0.45, 0.05},
    {1, 0.2, 0.1},
    {1, 0.25, 0.1},
    {1, 0.4, 0.1},
    {1, 0.45, 0.1},
    {1, 0.2, 0.15},
    {1, 0.25, 0.15},
    {1, 0.4, 0.15},
    {1, 0.45, 0.15},
    {1, 0.2, 0.2},
    {1, 0.25, 0.2},
    {1, 0.4, 0.2},
    {1, 0.45, 0.2},
    {1, 0.2, 0.25},
    {1, 0.25, 0.25},
    {1, 0.4, 0.25},
    {1, 0.45, 0.25},
    {1, 0.2, 0.3},
    {1, 0.25, 0.3},
    {1, 0.4, 0.3},
    {1, 0.45, 0.3},
    {1, 0.2, 0.35},
    {1, 0.25, 0.35},
    {1, 0.4, 0.35},
    {1, 0.45, 0.35},
    {1, 0.2, 0.4},
    {1, 0.25, 0.4},
    {1, 0.4, 0.4},
    {1, 0.45, 0.4},
    {1, 0.2, 0.45},
    {1, 0.25, 0.45},
    {1, 0.4, 0.45},
    {1, 0.45, 0.45},
    {1, 0.2, 0.5},
    {1, 0.25, 0.5},
    {1, 0.4, 0.5},
    {1, 0.45, 0.5},
    {1, 0.2, 0.55},
    {1, 0.25, 0.55},
    {1, 0.4, 0.55},
    {1, 0.45, 0.55},
    {1, 0.2, 0.6},
    {1, 0.25, 0.6},
    {1, 0.4, 0.6},
    {1, 0.45, 0.6},
    {1, 0.2, 0.65},
    {1, 0.25, 0.65},
    {1, 0.4, 0.65},
    {1, 0.45, 0.65},
    {1, 0.2, 0.7},
    {1, 0.25, 0.7},
    {1, 0.4, 0.7},
    {1, 0.45, 0.7},
    {1, 0.2, 0.75},
    {1, 0.25, 0.75},
    {1, 0.4, 0.75},
    {1, 0.45, 0.75}

};

float cementLoc[NUM_OF_MINI_CEMENT_BLOCKS][3] = {
    // гараж
    {0, -0.15, -0.95},
    {0, 0.1, -0.95},
    {0, -0.15, -0.9},
    {0, 0.1, -0.9},
    {0, -0.15, -0.85},
    {0, 0.1, -0.85},
    {0, -0.15, -0.8},
    {0, 0.1, -0.8},
    {0, -0.15, -0.75},
    {0, 0.1, -0.75},
    // боковые ограждения
    {0, -15, -0.75},
    {0, -0.95, -0.75},
    {0, -0.9, -0.75},
    {0, -0.85, -0.75},
    {0, -0.8, -0.75},
    {0, -0.75, -0.75},
    {0, -0.7, -0.75},
    {0, -0.65, -0.75},
    {0, -0.6, -0.75},
    {0, -0.55, -0.75},
    {0, -0.5, -0.75},
    {0, -0.45, -0.75},
    {0, -0.4, -0.75},
    {0, -0.35, -0.75},
    {0, -0.3, -0.75},
    {0, -0.25, -0.75},
    {0, -0.2, -0.75},
    {0, -0.15, -0.75},
    
    {0, 0.1, -0.75},
    {0, 0.15, -0.75},
    {0, 0.2, -0.75},
    {0, 0.25, -0.75},
    {0, 0.3, -0.75},
    {0, 0.35, -0.75},
    {0, 0.4, -0.75},
    {0, 0.45, -0.75},
    {0, 0.5, -0.75},
    {0, 0.55, -0.75},
    {0, 0.6, -0.75},
    {0, 0.65, -0.75},
    {0, 0.7, -0.75},
    {0, 0.75, -0.75},
    {0, 0.8, -0.75},
    {0, 0.85, -0.75},
    {0, 0.9, -0.75},
    {0, 0.95, -0.75},
    {0, 1, -0.75},


	{0, -1, 0.9},
    {0, -0.95, 0.9},
    {0, -0.9, 0.9},
    {0, -0.85, 0.9},
    {0, -0.8, 0.9},
    {0, -0.75, 0.9},
    {0, -0.7, 0.9},
    {0, -0.65, 0.9},
    {0, -0.6, 0.9},
    {0, -0.55, 0.9},
    {0, -0.5, 0.9},
    {0, -0.45, 0.9},
    {0, -0.4, 0.9},
    {0, -0.35, 0.9},
    {0, -0.3, 0.9},
    {0, -0.25, 0.9},
    {0, -0.2, 0.9},
    {0, -0.15, 0.9},
    {0, -0.1, 0.9},
    {0, -0.05, 0.9},
    {0, 0, 0.9},
    {0, 0.05, 0.9},
    {0, 0.1, 0.9},
    {0, 0.15, 0.9},
    {0, 0.2, 0.9},
    {0, 0.25, 0.9},
    {0, 0.3, 0.9},
    {0, 0.35, 0.9},
    {0, 0.4, 0.9},
    {0, 0.45, 0.9},
    {0, 0.5, 0.9},
    {0, 0.55, 0.9},
    {0, 0.6, 0.9},
    {0, 0.65, 0.9},
    {0, 0.7, 0.9},
    {0, 0.75, 0.9},
    {0, 0.8, 0.9},
    {0, 0.85, 0.9},
    {0, 0.9, 0.9},
    {0, 0.95, 0.9},
    {0, 1, 0.9},



    { 0, 0.75, 0.75 },
    {0, 0.8, 0.75},
    {0, 0.85, 0.75},
    {0, 0.9, 0.75},
    {0, 0.95, 0.75},
    {0, 1, 0.75},


    {0, -0.8, 0.75},
    {0, -0.85, 0.75},
    {0, -0.9, 0.75},
    {0, -0.95, 0.75},
    {0, -1, 0.75}



};

struct tankSettings you;

void startSettings()
{
    you.xPos = 0;
    you.yPos = -0.84;
    you.bulletSet.time_anim = 0;
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

void rotatePoint(float *x, float *y, float angle) {
    float rad = angle * 3.1415926535 / 180.0;
    float xNew = *x * cos(rad) - *y * sin(rad);
    float yNew = *x * sin(rad) + *y * cos(rad);
    *x = xNew + you.xPos;
    *y = yNew + you.yPos;
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
        rotatePoint(&x, &y, you.angle);
        glVertex2f(x, y);
    }

    glColor3f(1.0f, 0.63f, 0.27f);
    for (int i = 0; i < 28; i++) {
        float x = coordSecondColor[i][0], y = coordSecondColor[i][1];
        rotatePoint(&x, &y, you.angle);
        glVertex2f(x, y);
    }

    glColor3f(0.97f, 0.84f, 0.47f);
    for (int i = 0; i < 22; i++) {
        float x = coordThirdColor[i][0], y = coordThirdColor[i][1];
        rotatePoint(&x, &y, you.angle);
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
     {1.0f, 1.0f, 1.0f},  // Белый (#FFFFFF)
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

void draw_bullet_global() // здесь немного перепутаны координаты
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



void update(int value) { // обязательная функция обновления экрана (нужен для анимации пули)

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

	createBrickWall();
    createCementWall();
    draw_bullet_global();
    draw_bullet_effects_for_global_tank();
    draw_block_zone();
    draw_global_tank_up();
    

    glutSwapBuffers();
}




void keyboard(char key) {
    switch (key) {
    case 'w':
    case 'W':
    case 'ц':
    case 'Ц':

        you.angle = 0.0;
        if (you.yPos <= 0.85f)
            check_block_entity(1);

        printf("x = %f, y = %f\n", you.xPos, you.yPos);
        break;


    case 's':
    case 'S':
    case 'ы':
    case 'Ы':

        you.angle = 180.0;

        if (you.yPos >= -0.85f)
            check_block_entity(2);

        printf("x = %f, y = %f\n", you.xPos, you.yPos);
        break;


    case 'A':
    case 'a':
    case 'ф':
    case 'Ф':

        you.angle = 90.0;
        if (you.xPos >= -0.86)
			check_block_entity(3);

        


        printf("x = %f, y = %f\n", you.xPos, you.yPos);

        break;
    case 'd':
    case 'D':
    case 'в':
    case 'В':

        you.angle = 270;

        if (you.xPos <= 0.86)
			check_block_entity(4);


        printf("x = %f, y = %f\n", you.xPos, you.yPos);

        break;
    case ' ':
        you.bulletSet.live = 1;
        break;

    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);


    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 0);

    glutCreateWindow("Tanchik");
    glClearColor(0.1, 0.1, 0.1, 0);

    startSettings();
    glutTimerFunc(10, update, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);



    glutMainLoop();
    return 0;
}