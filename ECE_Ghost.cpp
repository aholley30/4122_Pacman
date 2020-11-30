/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 10/26/2020
 * Description: implements the functions in ECE_Ghost.h, allows ghosts to be drawn
 * */
#include <GL/glut.h>
#include <math.h>
#include "ECE_Ghost.h"
#include "dij.h"
//#include <thread>
#include <chrono>

#define RIGHT 0
#define LEFT 1
#define DOWN 3
#define UP 2
//#include <iostream>
//#include "dij.h"


char map2[22][19] = {{'h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','h','0'},
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
                   

GLUquadricObj *h = gluNewQuadric();
//draw red ghost
void ECE_Ghost::drawRedGhost(ECE_Ghost g) {
    glTranslatef(g.xx, g.yy, -1.0);
    if(isSick) {
        glColor3f(1.0,1.0,1.0);
    }
    else {
        glColor3f(1.0, 0.0, 0.0);
    }
    
    glPushMatrix();
        gluCylinder(h,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5); //move sphere so that it's on top of cylinder
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}
//drw pink ghost
void ECE_Ghost::drawPinkGhost(ECE_Ghost g) {
    glTranslatef(g.xx, g.yy, -1.0);
    if(isSick) {
        glColor3f(1.0, 1.0, 1.0);
    }
    else {
        glColor3f(1.0, 192.0/255.0, 203.0/255.0);
    }
    glPushMatrix();
        gluCylinder(h,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5);
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}
//draw green ghost
void ECE_Ghost::drawGreenGhost(ECE_Ghost g) {
    glTranslatef(g.xx, g.yy, -1.0);
    if(isSick) {
        glColor3f(1.0, 1.0, 1.0);
    }
    else {
        glColor3f(44.0/255.0, 166.0/255.0, 152.0/255.0);
    }
    
    glPushMatrix();
        gluCylinder(h,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5);
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}
//draw orange ghost
void ECE_Ghost::drawOrangeGhost(ECE_Ghost g) {
    glTranslatef(g.xx, g.yy, -1.0);
    if(isSick) {
        glColor3f(1.0, 1.0, 1.0);
    }
    else {
        glColor3f(235.0/255.0, 183.0/255.0, 79.0/255.0);
    }
    
    glPushMatrix();
        gluCylinder(h,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5);
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}
ECE_Ghost::ECE_Ghost(char color) {
    this->color = color;
    dir = 5;
    couldMove = true;
    firstMove = true;
}
void ECE_Ghost::resetG(){
    xx = x1;
    yy = y1;
    drawnOnce = 0;
    firstMove = true;
}

bool ECE_Ghost::isUnique(Pair p, std::vector<Pair> vec) {
    if (vec.empty()) return true;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == p) {
            //std::cout <<"wall at: " << p.first << ", " << p.second << std::endl;
            return false;
        } 
    }
    return true;
}
bool ECE_Ghost::canMove(int dir2) {
    
    switch(dir2) 
    {
        case 2:
            if (map2[abs(15 - (int)xx) + 1][abs(10 - (int)yy)] != 'v' && map2[abs(15 - (int)xx) + 1][abs(10 - (int)yy)] != 'h') 
            {
                if (isUnique(std::make_pair(15-xx+1,10-yy),mW)) return true;
                else return false;
            }
            else return false;
            break;
        case 3:
            if (map2[abs(15 - (int)xx) - 1][abs(10 - (int)yy)] != 'v' && map2[abs(15 - (int)xx) - 1][abs(10 - (int)yy)] != 'h') 
            {
                if (isUnique(std::make_pair(15-xx-1,10-yy),mW)) return true;
                else return false;
            }
            else return false;
            break;
        case 0:
            if (map2[abs(15 - (int)xx) ][abs(10 - (int)yy) - 1] != 'v' && map2[abs(15 - (int)xx) ][abs(10 - (int)yy) - 1] != 'h') 
            {
                if (isUnique(std::make_pair(15-xx,10-yy-1),mW)) return true;
                else return false;
            }
            else return false;
            break;
        case 1:
            if (map2[abs(15 - (int)xx)][abs(10 - (int)yy) + 1] != 'v' && map2[abs(15 - (int)xx)][abs(10 - (int)yy) + 1] != 'h') 
            {
                if (isUnique(std::make_pair(15 - xx,10 - yy + 1),mW)) return true;
                else return false;
            }
            else return false;
            break;
    }
}
int ECE_Ghost::exitCount() {
    int exit = 0;
        if (canMove(0)) { // Check all directions and if its not a wall in that direction, increment the counter
            exit++;
        }
        if (canMove(1)) {
            exit++;
        }
        if (canMove(2)) {
            exit++;
        }
        if (canMove(3)) {
            exit++;
        }

        return exit;
}
double ECE_Ghost::getDistance(int x, int y) {
    int tmpx = pxx;
    int tmpy = pyy;

    if(isSick) {
        switch (color) {
            
            case 'r':
                //if (pxx > 5) { //-5 is as negative as the map gets for x axis
                    tmpx = 14 - pxx - 5; //14 is the max x coordinate
                    return (sqrt(((tmpx - x) * (tmpx - x)) + ((pyy - y) * (pyy - y))));
                //}
                //else return (sqrt(((-pxx - x) * (-pxx - x)) + ((pyy - y) * (pyy - y))));
            case 'g':
                //if (pyy > 7) {  //-7 is the minimum y coordinate
                    tmpy = 9 - pxx - 7; //9 is the max
                    return (sqrt(((pxx - x) * (pxx - x)) + ((tmpy - y) * (tmpy - y))));
                //}
                //return (sqrt(((pxx - x) * (pxx - x)) + ((-pyy - y) * (-pyy - y))));
            case 'o':
                //tmpx = pxx;
                //tmpy = pyy;
                //if (pxx > 5) { //-5 is as negative as the map gets for x axis
                    tmpx = 14 - pxx - 5; //14 is the max x coordinate
                //}
                //if (pyy > 7) {  //-7 is the minimum y coordinate
                    tmpy = 9 - pxx - 7; //9 is the max
                //}
                return (sqrt(((tmpx - x) * (tmpx - x)) + ((tmpy - y) * (tmpy - y))));
            case 'p':
                //tmpx = pxx;
                //tmpy = pyy;
                //if (pxx > 5) { //-5 is as negative as the map gets for x axis
                    tmpx = 14 - pxx - 5; //14 is the max x coordinate
                //}
                //if (pyy > 7) {  //-7 is the minimum y coordinate
                    tmpy = 9 - pxx - 7; //9 is the max
                //}
                return (sqrt(((tmpx - x) * (tmpx - x)) + ((tmpy - y) * (tmpy - y))));
        }
    }
    //std::cout<<pxx << ", " << pyy <<std::endl;
    //std::cout<<"Ghost: "<<xx << ", " << yy <<std::endl;
    return (sqrt(((pxx - x) * (pxx - x)) + ((pyy - y) * (pyy - y))));
}
void ECE_Ghost::cornerHandler()
{
    if (!canMove(dir))
    { // Checks whether if it were to keep moving in it current direction if it would hit a wall
        if (canMove(1) && dir != 0)
        { // Checks its new direction wouldnt make it hit a wall AND that its not reversing direction
            dir = 1;
        }
        else if (canMove(2) && dir != 3)
        {
            dir = 2;
        }
        else if (canMove(0) && dir != 1)
        {
            dir = 0;
        }
        else if (canMove(3))
        {
            //printf("path was taken");
            dir = 3;
        }
    }
}
 /**
     * Determines which direction to move by checking all potential moves around itself and comparing how close each
     * potential move will put it to the target tile. It then selects the move which puts it the closest to the
     * target tile
     * @param colGhost The colour of the current ghost
     * @param ghost Pass in a ghost object in case the chosen move technique must use another ghost to calculate where to move
     */
    void ECE_Ghost::move()
    {
        if(firstMove) {
            xx = round(xx);
            yy = round(yy);
            firstMove = false;
        }
        int tempDir;
        double distance = 999.0;
        //std::cout << exitCount() << std::endl;
        if (exitCount() >= 3 ) {
            if (dir != DOWN && canMove(UP)) {
                float d = getDistance(xx - 1, yy);
                //std::cout << "dist going up: " << d << std::endl;
                if(d < distance){
                    tempDir = UP;
                    distance = d;
                }
            }
            if (dir != LEFT && canMove(RIGHT)) {
                float d = getDistance(xx, yy + 1);
               // std::cout << "dist going right: " << d << std::endl;
                if(d < distance){
                    tempDir = RIGHT;
                    distance = d;
                }
            }
            if (dir != RIGHT && canMove(LEFT) ) {
                float d = getDistance(xx, yy - 1);
                //std::cout << "dist going left: " << d << std::endl;
                if(d < distance){
                    tempDir = LEFT;
                    distance = d;
                }
            }
            if (dir != UP && canMove(DOWN)) {
                float d = getDistance(xx + 1, yy);
                //std::cout << "dist going down: " << d << std::endl;
                if(d < distance){
                    tempDir = DOWN;
                    distance = d;
                }
            }
            dir = tempDir;
        } else {
            cornerHandler();
        }
        switch (dir) {
            case LEFT:
                yy--;
                break;
            case UP:
                xx--;
                break;
            case RIGHT:
                yy++;
                break;
            case DOWN:
                xx++;
                break;
        }
        if (xx == pxx && yy == pyy) {
            if (isSick) {
                resetG();
                wasSick = true;
            }
            else gameState = 1;
        }
    }

// void ECE_Ghost::move(std::vector<Pair> &vec) {
//     if(firstMove) {
//         xx = round(xx);
//         yy = round(yy);
//     }
//     updateMove(vec);
//     if(!canMove()) dir = 5;
//     switch(dir) {
//         case 0:
//             if(canMove()){
//                 printf("moved right");
//                 yy++;
//                 couldMove = true;
//             } 
//             break;
//         case 1:
//             if(canMove()) {
//                 printf("moved left");
//                 yy--;
//                 couldMove = true;
//             } 
//             break;
//         case 2:
//             if(canMove()){
//                 printf("moved up");
//                 xx--;
//                 couldMove = true;
//             }
//             break;
//         case 3:
//             if(canMove()) {
//                 printf("moved down");
//                 xx++;
//                 couldMove = true;
//             } 
//             break;
//         default:
//             couldMove = false;
//             while(!canMove()) {
//                 dir = rand()%(3 + 1);
//             }
//             std::cout << "chose direction randomly: " << dir <<std::endl;
//     }
//     if (xx == pxx && yy == pyy) {
//            //printf("updated gs");
//            gameState = 1;
//        }
// }
// void ECE_Ghost::updateMove(ECE_Ghost &g, int x, int y, std::vector<Pair> &vec) 
//     {
//         Pair p = std::make_pair(pxx,pyy);
//         std::pair<int,int> p2 = dij::aStarSearch(map2,std::make_pair(g.xx,g.yy),p, std::ref(vec));
//         if (p2.first != 0 && p2.second != 0) {
            
//             g.xx = 15 - p2.first;
//             g.yy = 10 - p2.second;
            
//         }
//        if (g.xx == pxx && g.yy == pyy) {
//            //printf("updated gs");
//            gameState = 1;
//        }
//     }

// int ECE_Ghost::canMove(int key, ECE_Ghost g, char map[22][19]) {
//     switch(key) 
//     {
//         case GLUT_KEY_UP:
//             if (map[abs(15 - (int)g.xx) + 1][abs(10 - (int)g.yy)] != 'v' && map[abs(15 - (int)g.xx) + 1][abs(10 - (int)g.yy)] != 'h') 
//             {
//                 return 1;
//             }
//             else return 0;
//             break;
//         case GLUT_KEY_DOWN:
//             if (map[abs(15 - (int)g.xx) - 1][abs(10 - (int)g.yy)] != 'v' && map[abs(15 - (int)g.xx) - 1][abs(10 - (int)g.yy)] != 'h') 
//             {
//                 return 1;
//             }
//             else return 0;
//             break;
//         case GLUT_KEY_RIGHT:
//             if (map[abs(15 - (int)g.xx) ][abs(10 - (int)g.yy) - 1] != 'v' && map[abs(15 - (int)g.xx) ][abs(10 - (int)g.yy) - 1] != 'h') 
//             {
//                 //std::cout<<map[abs(15 - g.xx) ][abs(10 - g.yy) + 1] <<std::endl;
//                 return 1;
//             }
//             else return 0;
//             break;
//         case GLUT_KEY_LEFT:
//             if (map[abs(15 - (int)g.xx)][abs(10 - (int)g.yy) + 1] != 'v' && map[abs(15 - (int)g.xx)][abs(10 - (int)g.yy) + 1] != 'h') 
//             {
//                 return 1;
//             }
//             else return 0;
//             break;
//     }
    
// }