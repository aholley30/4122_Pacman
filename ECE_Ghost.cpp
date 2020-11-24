/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 10/26/2020
 * Description: implements the functions in ECE_Ghost.h, allows ghosts to be drawn
 * */
#include <GL/glut.h>
#include <math.h>
#include "ECE_Ghost.h"
#include <iostream>

GLUquadricObj *g = gluNewQuadric();
//draw red ghost
void ECE_Ghost::drawRedGhost() {
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        gluCylinder(g,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5); //move sphere so that it's on top of cylinder
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}
//drw pink ghost
void ECE_Ghost::drawPinkGhost() {
    glColor3f(1.0, 192.0/255.0, 203.0/255.0);
    glPushMatrix();
        gluCylinder(g,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5);
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}
//draw green ghost
void ECE_Ghost::drawGreenGhost() {
    glColor3f(44.0/255.0, 166.0/255.0, 152.0/255.0);
    glPushMatrix();
        gluCylinder(g,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5);
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}
//draw orange ghost
void ECE_Ghost::drawOrangeGhost() {
    glColor3f(235.0/255.0, 183.0/255.0, 79.0/255.0);
    glPushMatrix();
        gluCylinder(g,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5);
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}