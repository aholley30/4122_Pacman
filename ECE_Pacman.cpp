/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 10/29/2020
 * Description: Implements its like-named header file. Allows Pacman to be drawn
 * */
#include <GL/glut.h>
#include <math.h>
#include "ECE_Pacman.h"
#include <iostream>
//#include "map.h"



ECE_Pacman::ECE_Pacman() {
    xx = 10;
    yy = 1;
}

//draw Pacman
void ECE_Pacman::drawPacMan(ECE_Pacman pac) {
    
    glTranslatef(pac.xx,pac.yy, -1.0);
    glColor3f(1.0, 1.0, 0.0); //yellow
    glPushMatrix();
        glutSolidSphere(0.6, 20, 20); // makes him just big enough to go through maze w/o touching walls
    glPopMatrix();
}

int ECE_Pacman::canMove(int key, char map[22][19], ECE_Pacman pac) {
    switch(key) 
    {
        case GLUT_KEY_UP:
            if (map[abs(15 - pac.xx) + 1][abs(10 - pac.yy)] != 'v' && map[abs(15 - pac.xx) + 1][abs(10 - pac.yy)] != 'h') 
            {
                return 1;
            }
            else return 0;
            break;
        case GLUT_KEY_DOWN:
            if (map[abs(15 - pac.xx) - 1][abs(10 - pac.yy)] != 'v' && map[abs(15 - pac.xx) - 1][abs(10 - pac.yy)] != 'h') 
            {
                return 1;
            }
            else return 0;
            break;
        case GLUT_KEY_RIGHT:
            if (map[abs(15 - pac.xx) ][abs(10 - pac.yy) - 1] != 'v' && map[abs(15 - pac.xx) ][abs(10 - pac.yy) - 1] != 'h') 
            {
                //std::cout<<map[abs(15 - pac.xx) ][abs(10 - pac.yy) + 1] <<std::endl;
                return 1;
            }
            else return 0;
            break;
        case GLUT_KEY_LEFT:
            if (map[abs(15 - pac.xx)][abs(10 - pac.yy) + 1] != 'v' && map[abs(15 - pac.xx)][abs(10 - pac.yy) + 1] != 'h') 
            {
                return 1;
            }
            else return 0;
            break;
    }
}