#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LIGHT_ON 0
#define LIGHT_OFF 1
#define NUM_DISKS 3
int pos[16] = {10, 15, 20, 25, 30, 35, 40, 45, 50};
int peg[3] = {50, 150, 250};
int moves[10000][3];
int max_moves;
int POLES[3][10];
int top[3] = {-1, -1, -1};
static GLfloat theta = 0.0;
static GLfloat axis = 2;
float scale = 1.00f;
int reflect = 0;
float tx = 0, ty = 0, a = 150;
int shCounter = 0;
int se1 = 0, se2;
int baseXcoord = 250, baseYcoord = 95, dif = 4;
int legend = 1;
// int delayTime = 100;
int cnt, counter, speed = 7;
float ycoordinate, xcoordinate, zcoordinate;
int lightflag = 1, animationFlag = 1;
GLfloat shearMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.25f, 1.0f, 0.0f, 0.0f,
    0.25f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f};
GLfloat inverseShearMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    -0.25f, 1.0f, 0.0f, 0.0f,
    -0.25f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f};
void push(int p, int disk)
{
    POLES[p][++top[p]] = disk;
}
void pop(int p)
{
    top[p]--;
}
void tower(int n, int src, int temp, int dst)
{
    if (n > 0)
    {
        tower(n - 1, src, dst, temp);
        moves[cnt][0] = n;
        moves[cnt][1] = src;
        moves[cnt][2] = dst;
        cnt++;
        tower(n - 1, temp, src, dst);
    }
}
void drawPegs()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        glColor3f(0.25, 0.41, 0.88);
        glPushMatrix();
        glTranslatef(peg[i], 5, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(3, 50, 20, 20);
        // for drawing the circular ring at the bottom of each peg.
        glColor3f(0, 0, 0.5);
        glutSolidTorus(2, 45, 20, 20);
        glPopMatrix();
    }
}
void printString(char *text)
{
    for (int i = 0; i < strlen(text); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}
void drawText()
{
    glColor3f(0, 0.79, 1);
    glBegin(GL_POLYGON); // Yellow BOX
    glVertex3f(-73.8, 93.3, 0);
    glVertex3f(-73.8, 89.8, 0);
    glVertex3f(10.8, 89.8, 0);
    glVertex3f(10.8, 93.3, 0);
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON); // Yellow BOX
    glVertex3f(-73, 93, 0);
    glVertex3f(-73, 90, 0);
    glVertex3f(10, 90, 0);
    glVertex3f(10, 93, 0);
    glEnd();
    glColor3f(0, 0, 0);
    glRasterPos3f(-45, 90.5, 2);
    printString("Move : ");
    // Move :
    glColor3f(1, 0, 1);
    char str[5];
    sprintf(str, "%d", counter);
    glRasterPos3f(-17, 90.5, 2);
    printString(str);
    // $counter
    glRasterPos3f(-70, 80, 0);
    printString("NEXT: ");
    // NEXT:
    glColor3f(0, 0, 0);
    glRasterPos3f(-44, 80, 0);
    printString("Disk");
    // DISK
    glColor3f(0, 0.5, 0);
    char str1[10];
    sprintf(str1, "%d", moves[counter][0]); // disk no. = moves[counter][0]
    glRasterPos3f(-25, 80, 0);
    printString(str1);
    glColor3f(0, 0, 0);
    glRasterPos3f(-15, 80, 0);
    printString("from");
    // from
    glColor3f(0, 0, 0.5);
    char src[2];
    if (moves[counter][1] == 0)
        strcpy(src, "A");
    // src = A or B or C
    else if (moves[counter][1] == 1)
        strcpy(src, "B");
    else
        strcpy(src, "C");
    glRasterPos3f(5, 80, 0);
    printString(src);
    // src
    glColor3f(0, 0, 0);
    glRasterPos3f(15, 80, 0);
    printString("to");
    // to
    glColor3f(0, 0, 0.5);
    char dst[2];
    if (moves[counter][2] == 0)
        strcpy(dst, "A");
    // dst = A or B or C
    else if (moves[counter][2] == 1)
        strcpy(dst, "B");
    else
        strcpy(dst, "C");
    glRasterPos3f(25, 80, 0);
    printString(dst);
    // dst
    // Drawing A, B and C on top of each peg
    glColor3f(1, 0, 0);
    glRasterPos3f(peg[0], 1, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
    glRasterPos3f(peg[1], 1, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'B');
    glRasterPos3f(peg[2], 1, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
    glColor3f(0.502, 0.502, 0.502);
    glBegin(GL_POLYGON); // Yellow BOX
    glVertex3f(-73, 73.5, 0);
    glVertex3f(-73, 49, 0);
    glVertex3f(-10, 49, 0);
    glVertex3f(-10, 73.5, 0);
    glEnd();
    glColor3f(1, 1, 1);
    glRasterPos3f(-70, 70.5, 0);
    printString("Animation : ");
    if (animationFlag)
    {
        glColor3f(0, 1, 0);
        glRasterPos3f(-30, 70.5, 0);
        printString("ON");
    }
    else
    {
        glColor3f(1, 0, 0);
        glRasterPos3f(-30, 70.5, 0);
        printString("OFF");
    }
    glColor3f(1, 1, 1);
    glRasterPos3f(-70, 66.5, 0);
    printString("Lights : ");
    if (lightflag)
    {
        glColor3f(0, 1, 0);
        glRasterPos3f(-30, 66.5, 0);
        printString("ON");
    }
    else
    {
        glColor3f(1, 0, 0);
        glRasterPos3f(-30, 66.5, 0);
        printString("OFF");
    }
    glColor3f(1, 1, 1);
    glRasterPos3f(-70, 66.5 - 4, 0);
    printString("Scale: ");
    if (scale > 0.99f && scale < 1.01f)
        glColor3f(0, 1, 0);
    else
        glColor3f(1, 0, 0);
    // if then green else red
        glRasterPos3f(-30, 66.5 - 4, 0);
    char printScale[5];
    sprintf(printScale, "%.2f", scale);
    printString(printScale);
    glColor3f(1, 1, 1);
    glRasterPos3f(-70, 66.5 - 8, 0);
    printString("Tx: ");
    if (tx == 0)
        glColor3f(1, 0, 0);
    else
        glColor3f(0, 1, 0);
    // if then green else red
    glRasterPos3f(-30, 66.5 - 8, 0);
    char printTx[5];
    sprintf(printTx, "%.0f", tx);
    printString(printTx);
    glColor3f(1, 1, 1);
    glRasterPos3f(-70, 66.5 - 12, 0);
    printString("Ty: ");
    if (ty == 0)
        glColor3f(1, 0, 0);
    else
        glColor3f(0, 1, 0);
    glRasterPos3f(-30, 66.5 - 12, 0);
    char printTy[5];
    sprintf(printTy, "%.0f", ty);
    printString(printTy);
    glColor3f(1, 1, 1);
    glRasterPos3f(-70, 66.5 - 16, 0);
    printString("Speed: ");
    if (((speed / 7) + 1) != 1)
        glColor3f(0, 1, 0);
    else
        glColor3f(1, 0, 0);
    glRasterPos3f(-30, 66.5 - 16, 0);
    char printSpeed[5];
    sprintf(printSpeed, "%d", (speed / 7) + 1);
    printString(printSpeed);
    printString("x");
    glColor3f(0, 0, 0);
    glLineWidth(4);
    glBegin(GL_LINE_LOOP); // Yellow BOX
    glVertex3f(121, -7.7, 0);
    glVertex3f(148, -7.7, 0);
    glEnd();
    glColor3f(0.878, 0.066, 0.372);
    glRasterPos3f(100, -7, 0);
    printString("Press SPACE to start solving.");
    if (legend)
    {
        glColor3f(0, 0.79, 1);
        glBegin(GL_POLYGON); // blue BOX
        glVertex3f(baseXcoord - 50, baseYcoord + 4, 0);
        glVertex3f(baseXcoord - 50, baseYcoord, 0);
        glVertex3f(baseXcoord + 40, baseYcoord, 0);
        glVertex3f(baseXcoord + 40, baseYcoord + 4, 0);
        glEnd();
        glColor3f(0.1, 0.2, 0.2);
        glBegin(GL_POLYGON); // dark green BOX
        glVertex3f(baseXcoord - 103, baseYcoord, 0);
        glVertex3f(baseXcoord - 103, baseYcoord - 26.8, 0);
        glVertex3f(baseXcoord + 96, baseYcoord - 26.8, 0);
        glVertex3f(baseXcoord + 96, baseYcoord, 0);
        glEnd();
        glColor3f(0, 0, 0);
        glRasterPos3f(baseXcoord - 25.5, baseYcoord + 1, 0);
        printString("CONTROLS");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord - 100, baseYcoord - dif, 0);
        printString("Translation: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord - 58, baseYcoord - dif, 0);
        printString("WASD");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord - 100, baseYcoord - 2 * dif, 0);
        printString("Scaling: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord - 58, baseYcoord - 2 * dif, 0);
        printString("QE");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord - 100, baseYcoord - 3 * dif, 0);
        printString("Rotation: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord - 58, baseYcoord - 3 * dif, 0);
        printString("C/Middle Mouse");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord - 100, baseYcoord - 4 * dif, 0);
        printString("Reflection: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord - 58, baseYcoord - 4 * dif, 0);
        printString("R");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord - 100, baseYcoord - 5 * dif, 0);
        printString("Shearing: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord - 58, baseYcoord - 5 * dif, 0);
        printString("ZX");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord - 100, baseYcoord - 6 * dif, 0);
        printString("Breathing Effect: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord - 39.5, baseYcoord - 6 * dif, 0);
        printString("F");
        // COLUMN 2
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord + 5, baseYcoord - dif, 0);
        printString("Perspective: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord + 58, baseYcoord - dif, 0);
        printString("IJKLUO");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord + 5, baseYcoord - 2 * dif, 0);
        printString("Animation Speed: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord + 79.5, baseYcoord - 2 * dif, 0);
        printString("+-");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord + 5, baseYcoord - 3 * dif, 0);
        printString("Random Background: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord + 85, baseYcoord - 3 * dif, 0);
        printString("B");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord + 5, baseYcoord - 4 * dif, 0);
        printString("Next Move: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord + 49, baseYcoord - 4 * dif, 0);
        printString("Scroll Down");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord + 5, baseYcoord - 5 * dif, 0);
        printString("Undo Move: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord + 59, baseYcoord - 5 * dif, 0);
        printString("Scroll Up");
        glColor3f(1, 1, 1);
        glRasterPos3f(baseXcoord + 5, baseYcoord - 6 * dif, 0);
        printString("Disable Legend: ");
        glColor3f(0, 0.79, 1);
        glRasterPos3f(baseXcoord + 85, baseYcoord - 6 * dif, 0);
        printString("\\");
    }
    else
    {
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON); // dark green BOX
        glVertex3f(baseXcoord + 10.4, baseYcoord + 0.1, 0);
        glVertex3f(baseXcoord + 10.4, baseYcoord - 9.4, 0);
        glVertex3f(baseXcoord + 96.1, baseYcoord - 9.4, 0);
        glVertex3f(baseXcoord + 96.1, baseYcoord + 0.1, 0);
        glEnd();
        glColor3f(0.80 * 1.0, 1.0, 1);
        glBegin(GL_POLYGON); // dark green BOX
        glVertex3f(baseXcoord + 11, baseYcoord, 0);
        glVertex3f(baseXcoord + 11, baseYcoord - 9, 0);
        glVertex3f(baseXcoord + 96, baseYcoord - 9, 0);
        glVertex3f(baseXcoord + 96, baseYcoord, 0);
        glEnd();
        glColor3f(0, 0.55, 1);
        glRasterPos3f(baseXcoord + 15, baseYcoord - 4, 0);
        printString("ANUBHAV TEKRIWAL");
        glColor3f(0.133, 0.545, 0.133);
        glRasterPos3f(baseXcoord + 30, baseYcoord - 7, 0);
        printString("1AY20CS018");
    }
}
void smallLargeEffect()
{
    if (se2 == 2)
    {
        scale += 0.03;
        se2 = 0;
        glutIdleFunc(NULL);
    }
    se1++;
    if (se1 < 4)
        scale -= 0.03;
    else if (se1 < 14)
        scale += 0.03;
    else if (se1 < 21)
        scale -= 0.03;
    else
    {
        se1 = 0;
        se2++;
    }
    for (int m = 0; m < 10000; m++)
        for (int n = 0; n < 3500; n++)
            ;
    glutPostRedisplay();
}
void drawSolved()
{
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON); // yellow box
    glVertex3f(99.8, 75.1, 0);
    glVertex3f(99.8, 67.4, 0);
    glVertex3f(200.3, 67.4, 0);
    glVertex3f(200.3, 75.1, 0);
    glEnd();
    glColor3f(0.80 * 1.0, 1.0, 1);
    glBegin(GL_POLYGON); // yellow box
    glVertex3f(100, 75, 0);
    glVertex3f(100, 68, 0);
    glVertex3f(200, 68, 0);
    glVertex3f(200, 75, 0);
    glEnd();
    glColor3f(0, 0.55, 1);
    glRasterPos3f(113, 72, 0);
    printString("ANUBHAV TEKRIWAL");
    glColor3f(0.133, 0.545, 0.133);
    glRasterPos3f(127, 69, 0);
    printString("1AY20CS018");
    glColor3f(0.35, 0.35, 0.35);
    // glColor3f(1.0f, 0.843f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(-73, 94, 0);
    glVertex3f(-73, 89, 0);
    glVertex3f(15, 89, 0);
    glVertex3f(15, 94, 0);
    glEnd();
    glColor3f(0.678, 0.847, 0.902);
    glRasterPos3f(-65, 90.5, 2);
    printString("TOTAL MOVES :");
    glColor3f(0.9, 0.9, 0.9);
    char str[5];
    sprintf(str, "%d", counter);
    glRasterPos3f(-1, 90.5, 2);
    printString(str);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(50, 85, -5);
    glVertex3f(50, 80, -5);
    glVertex3f(250, 80, -5);
    glVertex3f(250, 85, -5);
    glEnd();
    glColor3f(1, 0, 1);
    glRasterPos3f(135, 81.5, 2);
    printString("Solved !!");
    smallLargeEffect();
}
void display()
{
    int i, j, k;
    if (shCounter > 0)
    {
        shCounter = 0;
        glMultMatrixf(shearMatrix);
    }
    else if (shCounter < 0)
    {
        shCounter = 0;
        glMultMatrixf(inverseShearMatrix);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (lightflag)
        glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(a, 0, 0);
    if (reflect)
        glScalef(-scale, scale, scale);
    else
        glScalef(scale, scale, scale);
    if (axis == 1)
        glRotatef(theta, 1, 0, 0);
    if (axis == 2)
        glRotatef(theta, 0, 1, 0);
    if (axis == 3)
        glRotatef(theta, 0, 0, 1);
    glTranslatef(tx, ty, 0);
    gluLookAt(xcoordinate, ycoordinate, zcoordinate, 0, 0, -1, 0, 1, 0);
    // PERSPECITVE VIEWING
    glTranslatef(-a, 0, 0);
    drawPegs();
    for (i = 0; i < 3; i++)
    {
        k = 0;
        for (j = 0; j <= top[i]; j++)
        {
            glPushMatrix();
            glTranslatef(peg[i], pos[k++], 0);
            glRotatef(90, 1, 0, 0);
            glColor3f(0.1 * POLES[i][j], 0.2 * POLES[i][j], 0);
            glutSolidTorus(2.0, 4 * POLES[i][j], 20, 20);
            glPopMatrix();
        }
    }
    glPopMatrix();
    glDisable(GL_LIGHTING);
    if (counter == max_moves)
        drawSolved();
    else
        drawText();
    if (lightflag)
        glEnable(GL_LIGHTING);
    glutSwapBuffers();
}
void lighting()
{
    GLfloat shininess[] = {50};
    GLfloat white[] = {0.6, 0.6, 0.6, 1};
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_position[] = {100, 60, 10, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);
}
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(1, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-80, 350, -10, 100, -500, 500);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    lighting();
}
void animate(int n, int src, int dest)
{
    int i;
    if (speed <= 0)
        speed = 1;
    for (i = pos[top[src] + 1]; i < 70; i += speed)
    {
        glPushMatrix();
        glTranslatef(peg[src], i, 0);
        glRotatef(85, 1, 0, 0);
        glColor3f(0.1 * n + 0.5, 0.2 * n + 0.5, 0 + 0.5);
        glutSolidTorus(2.0, 4 * n, 20, 20);
        glPopMatrix();
        glutSwapBuffers();
        display();
    }
    if (peg[src] < peg[dest])
        for (i = peg[src]; i <= peg[dest]; i += speed)
        {
            glPushMatrix();
            glTranslatef(i, 70, 0);
            glRotatef(85, 1, 0, 0);
            glColor3f(0.1 * n + 0.5, 0.2 * n + 0.5, 0 + 0.5);
            glutSolidTorus(2.0, 4 * n, 20, 20);
            glPopMatrix();
            glutSwapBuffers();
            display();
        }
    else
        for (i = peg[src]; i >= peg[dest]; i -= speed)
        {
            glPushMatrix();
            glTranslatef(i, 70, 0);
            glRotatef(85, 1, 0, 0);
            glColor3f(0.1 * n + 0.5, 0.2 * n + 0.5, 0 + 0.5);
            glutSolidTorus(2.0, 4 * n, 20, 20);
            glPopMatrix();
            glutSwapBuffers();
            display();
        }
    for (i = 70; i > pos[top[dest] + 1]; i -= speed)
    {
        glPushMatrix();
        glTranslatef(peg[dest], i, 0);
        glRotatef(85, 1, 0, 0);
        glColor3f(0.1 * n + 0.5, 0.2 * n + 0.5, 0 + 0.5);
        glutSolidTorus(2.0, 4 * n, 20, 20);
        glPopMatrix();
        glutSwapBuffers();
        display();
    }
}
void spinScene()
{
    theta += 4.0;
    if (theta > 360.0)
        axis = 1;
    if (theta > 720.0)
    {
        axis = 2;
        theta = 0;
        glutIdleFunc(NULL);
    }
    glutPostRedisplay();
}
void mouse(int btn, int state, int x, int y)
{
    if (btn == 4 && state == GLUT_DOWN)
    {
        scale = 1;
        reflect = 0;
        tx = 0;
        ty = 0;
        xcoordinate = 0;
        zcoordinate = 3;
        if (counter < max_moves)
        {
            pop(moves[counter][1]);
            if (animationFlag)
                animate(moves[counter][0], moves[counter][1], moves[counter][2]);
            push(moves[counter][2], moves[counter][0]);
            counter++;
        }
    }
    if (btn == 3 && state == GLUT_DOWN)
    {
        scale = 1;
        reflect = 0;
        tx = 0;
        ty = 0;
        xcoordinate = 0;
        zcoordinate = 3;
        if (counter > 0)
        {
            counter--;
            pop(moves[counter][2]);
            if (animationFlag)
                animate(moves[counter][0], moves[counter][2], moves[counter][1]);
            push(moves[counter][1], moves[counter][0]);
        }
    }
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        glutIdleFunc(spinScene);
    }
    glutPostRedisplay();
}
void restart()
{
    int i;
    memset(POLES, 0, sizeof(POLES));
    memset(moves, 0, sizeof(POLES));
    memset(top, -1, sizeof(top));
    theta = 0.0;
    axis = 2;
    scale = 1.0;
    reflect = 0;
    tx = 0;
    ty = 0;
    shCounter = 0;
    se1 = 0;
    se2 = 0;
    cnt = 0, counter = 0;
    xcoordinate = 0;
    ycoordinate = -0.3;
    zcoordinate = 3;
    max_moves = pow(2, NUM_DISKS) - 1;
    for (i = NUM_DISKS; i > 0; i--)
    {
        push(0, i);
    }
    tower(NUM_DISKS, 0, 1, 2);
}
void processMenuLighting(int option)
{
    switch (option)
    {
    case LIGHT_OFF:
        glDisable(GL_LIGHTING);
        lightflag = 0;
        break;
    case LIGHT_ON:
        glEnable(GL_LIGHTING);
        lightflag = 1;
        break;
    }
    glutPostRedisplay();
}
void processMenuMain2(int option)
{
    switch (option)
    {
    case 1:
        restart();
        glutPostRedisplay();
        break;
    case 10:
        glClearColor(1, 1, 1, 0);
        break;
    case 100:
        exit(0);
        break;
    }
}
void processMenuCamera(int option)
{
    switch (option)
    {
    case 119:
        ycoordinate += 0.1;
        break;
    case 115:
        ycoordinate -= 0.1;
        break;
    case 97:
        xcoordinate += 0.1;
        break;
    case 100:
        xcoordinate -= 0.1;
        break;
    case 113:
        zcoordinate += 0.1;
        break;
    case 101:
        zcoordinate -= 0.1;
        break;
    }
    glutPostRedisplay();
}
void processMenuAnimate(int option)
{
    switch (option)
    {
    case 0:
        animationFlag = 1;
        break;
    case 1:
        animationFlag = 0;
    }
}
void processMenuSolveCompletely(int option)
{
    while (counter < max_moves)
    {
        mouse(4, GLUT_DOWN, 0, 0);
        display();
        for (int m = 0; m < 20000; m++)
            for (int n = 0; n < 10000; n++)
                ;
    }
}
void createGLUTMenus()
{
    int menu = glutCreateMenu(processMenuLighting);
    glutAddMenuEntry("On", LIGHT_ON);
    glutAddMenuEntry("Off", LIGHT_OFF);
    int menuAnimate = glutCreateMenu(processMenuAnimate);
    glutAddMenuEntry("On", 0);
    glutAddMenuEntry("Off", 1);
    glutCreateMenu(processMenuMain2);
    glutAddSubMenu("Lights", menu);
    glutAddSubMenu("Disk Animation", menuAnimate);
    glutAddMenuEntry("Restart", 1);
    glutAddMenuEntry("Reset BG color", 10);
    glutAddMenuEntry("Quit", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void keyboard(unsigned char c, int x, int y)
{
    switch (c)
    {
    case ' ': // pressing SPACE means start solving till end
        keyboard('\\', 0, 0);
        processMenuSolveCompletely(1);
        break;
    case 'I':
    case 'i': // Perspective viewing using kb
        processMenuCamera(119);
        break;
    case 'K':
    case 'k':
        processMenuCamera(115);
        break;
    case 'j':
    case 'J':
        processMenuCamera(97);
        break;
    case 'L':
    case 'l':
        processMenuCamera(100);
        break;
    case 'U':
    case 'u':
        processMenuCamera(113);
        break;
    case 'O':
    case 'o':
        processMenuCamera(101);
        break;
    case 'B':
    case 'b': // random bg color on pressing 'b'
        glClearColor((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0, 0);
        break;
    case 'E':
    case 'e':
        scale += 0.05f;
        break;
    case 'Q':
    case 'q':
        scale -= 0.05f;
        break;
    case 'A':
    case 'a':
        tx -= 4;
        break;
    case 'D':
    case 'd':
        tx += 4;
        break;
    case 'S':
    case 's':
        ty -= 2;
        break;
    case 'W':
    case 'w':
        ty += 2;
        break;
    case 'R':
    case 'r':
        reflect = (reflect + 1) % 2;
        break;
    case 'X':
    case 'x':
        shCounter = 1;
        break;
    case 'Z':
    case 'z':
        shCounter = -1;
        break;
    case 'F':
    case 'f':
        glutIdleFunc(smallLargeEffect);
        break;
    case 'C':
    case 'c':
        mouse(GLUT_MIDDLE_BUTTON, GLUT_DOWN, 0, 0);
        break;
    case '+':
        if (speed < 30)
            speed += 7;
        break;
    case '-':
        speed -= 7;
        if (speed <= 0)
            speed = 1;
        break;
    case '\\':
        legend = (legend + 1) % 2;
        break;
    }
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tower of Hanoi - Anubhav");
    restart();
    init();
    glutDisplayFunc(display);
    createGLUTMenus();
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
