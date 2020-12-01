/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 11/30/2020
 * Description: Implements its like-named header file. Allows Pacman to be drawn
 * */
#include <GL/glut.h>
#include <math.h>
#include "ECE_Pacman.h"
#include <iostream>
//#include "map.h"

char map3[22][19] = {{'h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','0'},
                   {'v','c','c','c','c','c','c','c','c','c','c','c','c','c','c','c','c','c','v'},
                   {'v','c','h','h','h','h','h','0','c','0','c','h','h','h','h','h','0','c','v'},
                   {'v','c','c','c','c','v','c','c','c','v','c','c','c','v','c','c','c','c','v'},
                   {'h','0','c','0','c','v','c','h','h','h','h','0','c','v','c','0','c','h','v'},
                   {'v','p','c','v','c','c','c','c','c','m','c','c','c','c','c','v','c','p','v'},
                   {'v','c','h','v','c','h','h','0','c','0','c','h','h','0','c','h','0','c','v'},
                   {'v','c','c','c','c','c','c','c','c','v','c','c','c','c','c','c','c','c','v'},
                   {'h','h','h','0','c','0','0','h','h','h','h','0','0','0','c','h','h','h','v'},
                   {'0','0','0','v','c','v','0','0','0','0','0','0','0','v','c','v','0','0','0'},
                   //{'0','0','0','v','c','v','0','0','0','0','0','0','0','v','c','v','0','0','0'},
                   {'h','h','h','v','c','v','0','h','h','h','h','0','0','v','c','h','h','h','0'},
                   {'0','0','0','0','c','0','0','v','8','7','6','v','0','0','c','0','0','0','0'},
                   //{'0','0','0','0','c','0','0','v','0','0','0','v','0','0','c','0','0','0','0'},
                   {'h','h','h','0','c','0','0','h','0','0','h','v','0','0','c','h','h','h','0'},
                   {'0','0','0','v','c','v','0','0','0','0','0','0','0','v','c','v','0','0','0'},
                   //{'0','0','0','v','c','v','0','0','0','0','0','0','0','v','c','v','0','0','0'},
                   {'h','h','h','v','c','h','h','0','0','0','0','h','h','v','c','h','h','h','0'},
                   {'v','c','c','c','c','v','c','c','c','v','c','c','c','v','c','c','c','c','v'},
                   {'v','c','h','0','c','v','c','h','h','h','h','0','c','v','c','h','0','c','v'},
                   {'v','c','c','c','c','c','c','c','c','c','c','c','c','c','c','c','c','c','v'},
                   {'v','c','h','0','c','h','h','0','c','0','c','h','h','0','c','h','0','c','v'},//may need to specify b/w vert up and vert down
                   {'v','p','h','v','c','h','h','v','c','v','c','h','h','v','c','h','v','p','v'},
                   {'v','c','c','c','c','c','c','c','c','v','c','c','c','c','c','c','c','c','v'},
                   {'h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','v'}};
                   

ECE_Pacman::ECE_Pacman() {
    xx = 10;
    yy = 1;
    lifecount = 3;
    gamseState = 0;
    dir = 5;
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
            if (map[abs(15 - (int)round(pac.xx)) + 1][abs(10 - (int)round(pac.yy))] != 'v' && map[abs(15 - (int)round(pac.xx)) + 1][abs(10 -(int)round(pac.yy))] != 'h') 
            {
                return 1;
            }
            else return 0;
            break;
        case GLUT_KEY_DOWN:
            if (map[abs(15 - (int)round(pac.xx)) - 1][abs(10 - (int)round(pac.yy))] != 'v' && map[abs(15 - (int)round(pac.xx)) - 1][abs(10 - (int)round(pac.yy))] != 'h') 
            {
                return 1;
            }
            else return 0;
            break;
        case GLUT_KEY_RIGHT:
            if (map[abs(15 - (int)round(pac.xx)) ][abs(10 - (int)round(pac.yy)) - 1] != 'v' && map[abs(15 - (int)round(pac.xx)) ][abs(10 - (int)round(pac.yy)) - 1] != 'h') 
            {
                //std::cout<<map[abs(15 - pac.xx) ][abs(10 - pac.yy) + 1] <<std::endl;
                return 1;
            }
            else return 0;
            break;
        case GLUT_KEY_LEFT:
            if (map[abs(15 - (int)round(pac.xx))][abs(10 - (int)round(pac.yy)) + 1] != 'v' && map[abs(15 - (int)round(pac.xx))][abs(10 - (int)round(pac.yy)) + 1] != 'h') 
            {
                return 1;
            }
            else return 0;
            break;
    }
}
bool ECE_Pacman::canMove(int key) {
    switch(key) 
    {
        case GLUT_KEY_UP:
            if (map3[abs(15 - (int)round(xx) + 1)][abs(10 - (int)round(yy))] != 'v' && map3[abs(15 - (int)round(xx) + 1)][abs(10 -(int)round(yy))] != 'h') 
            {
                return true;
            }
            else return false;
            break;
        case GLUT_KEY_DOWN:
            if (map3[abs(15 - (int)round(xx)- 1 )][abs(10 - (int)round(yy))] != 'v' && map3[abs(15 - (int)round(xx) - 1)][abs(10 - (int)round(yy))] != 'h') 
            {
                return true;
            }
            else return false;
            break;
        case GLUT_KEY_RIGHT:
            if (map3[abs(15 - (int)round(xx)) ][abs(10 - (int)round(yy) -1)] != 'v' && map3[abs(15 - (int)round(xx)) ][abs(10 - (int)round(yy) - 1)] != 'h') 
            {
                //std::cout<<map[abs(15 - pac.xx) ][abs(10 - pac.yy) + 1] <<std::endl;
                return true;
            }
            else return false;
            break;
        case GLUT_KEY_LEFT:
            if (map3[abs(15 - (int)round(xx))][abs(10 - (int)round(yy) + 1)] != 'v' && map3[abs(15 - (int)round(xx))][abs(10 - (int)round(yy) + 1)] != 'h') 
            {
                return true;
            }
            else return false;
            break;
        default:
            return false;
    }
}

void ECE_Pacman::move() {
    //while(canMove) {
        switch(dir) {
            case GLUT_KEY_RIGHT:
                yy+= 1;
                //std::cout<< "pos: " << xx << ", " <<yy <<std::endl;
                break;
            case GLUT_KEY_LEFT:
                yy-= 1;
                break;
            case GLUT_KEY_UP:
                if (xx - 1 == 11 && yy == 9) break; //pesky wall
                else xx-= 1;
                break;
            case GLUT_KEY_DOWN:
                if (xx + 1 == 11 && yy == 9) break; 
                else xx+= 1;
                break;
            
        }
   // }
}
