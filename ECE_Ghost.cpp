/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 11/30/2020
 * Description: implements the functions in ECE_Ghost.h, allows ghosts to be drawn
 * Used some shortest path algorithm from https://github.com/tkilminster/pacman/blob/master/Ghost.h 
 * */
#include <GL/glut.h>
#include <math.h>
#include "ECE_Ghost.h"
#include "map.h"


#define RIGHT 0
#define LEFT 1
#define DOWN 3
#define UP 2

                   

GLUquadricObj *h = gluNewQuadric();

void ECE_Ghost::draw() {
    glTranslatef(xx, yy, -1.0);
    if(isSick) {
        glColor3f(1.0,1.0,1.0);
    }
    else {
        switch (color) {
            case 'r':
                glColor3f(1.0, 0.0, 0.0);
                break;
            case 'g':
                glColor3f(44.0/255.0, 166.0/255.0, 152.0/255.0);
                break;
            case 'p':
                glColor3f(1.0, 192.0/255.0, 203.0/255.0);
                break;
            case 'o':
                glColor3f(235.0/255.0, 183.0/255.0, 79.0/255.0);
                break;
            default:
                glColor3f(220.0/255.0, 217.0/255.0, 210.0/255.0);
        }
    }
    
    glPushMatrix();
        gluCylinder(h,0.5,0.5, 0.5, 20,20);
        glTranslatef(0.0, 0.0, 0.5); //move sphere so that it's on top of cylinder
        glutSolidSphere(0.5, 20, 20); 
    glPopMatrix();
}

void ECE_Ghost::initGhost(int row, int col) {
    if (drawnOnce == 0) {
        switch (color) {
            case 'r':
                xx = 15 - row - 0.5;
                x1 = xx;
                yy = 10 - col;
                y1 = yy;
                break;
            default:
                xx = 15 - row + 0.5;
                x1 = xx;
                yy = 10 - col;
                y1 = yy;
                break;
            
        }
        drawnOnce = 1;
    }
    if (!isDead) {
        drawnOnce = 1;
        draw();
    }
}

ECE_Ghost::ECE_Ghost(char color) {
    this->color = color;
    dir = 5;
    couldMove = true;
    firstMove = true;
    switch (color) {
        case 'r':
            limit = 25;
            break;
        case 'g':
            limit = 50;
            break;
        case 'p':
            limit = 100;
            break;
        case 'o':
            limit = 150;
            break;
        default:
            limit = 200;
    }
}

// std::vector<std::unique_ptr<ECE_Ghost>> ECE_Ghost::ghostVec() {

//     return {std::unique_ptr<ECE_Ghost>(new ECE_Ghost('r')), std::unique_ptr<ECE_Ghost>(new ECE_Ghost('p')), std::unique_ptr<ECE_Ghost>(new ECE_Ghost('g')), std::unique_ptr<ECE_Ghost>(new ECE_Ghost('o'))};
// }

void ECE_Ghost::resetG(){
    xx = x1;
    yy = y1;
    drawnOnce = 0;
    firstMove = true;
    wasSick = false;
    isDead = false;
}
//check if coordinates of proposed direction are allowed
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
            if (map1[abs(15 - (int)xx) + 1][abs(10 - (int)yy)] != 'v' && map1[abs(15 - (int)xx) + 1][abs(10 - (int)yy)] != 'h') 
            {
                if (isUnique(std::make_pair(15-xx+1,10-yy),mW)) return true;
                else return false;
            }
            else return false;
            break;
        case 3:
            if (map1[abs(15 - (int)xx) - 1][abs(10 - (int)yy)] != 'v' && map1[abs(15 - (int)xx) - 1][abs(10 - (int)yy)] != 'h') 
            {
                if (isUnique(std::make_pair(15-xx-1,10-yy),mW)) return true;
                else return false;
            }
            else return false;
            break;
        case 0:
            if (map1[abs(15 - (int)xx) ][abs(10 - (int)yy) - 1] != 'v' && map1[abs(15 - (int)xx) ][abs(10 - (int)yy) - 1] != 'h') 
            {
                if (isUnique(std::make_pair(15-xx,10-yy-1),mW)) return true;
                else return false;
            }
            else return false;
            break;
        case 1:
            if (map1[abs(15 - (int)xx)][abs(10 - (int)yy) + 1] != 'v' && map1[abs(15 - (int)xx)][abs(10 - (int)yy) + 1] != 'h') 
            {
                if (isUnique(std::make_pair(15 - xx,10 - yy + 1),mW)) return true;
                else return false;
            }
            else return false;
            break;
        default:
            return false;
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
    //change ghost's target tile to one that's opposit of pacman
    if(isSick) {
        switch (color) {
            case 'r':
                tmpx = 14 - pxx - 5; //14 is the max x coordinate, -5 is the min
                return (sqrt(((tmpx - x) * (tmpx - x)) + ((pyy - y) * (pyy - y))));
            case 'g':
                tmpy = 9 - pxx - 7; //9 is the max, -7 is the min
                return (sqrt(((pxx - x) * (pxx - x)) + ((tmpy - y) * (tmpy - y))));
            case 'o':
                tmpx = 14 - pxx - 5; //14 is the max x coordinate, -5 is the min
                tmpy = 9 - pyy - 7; //9 is the max, -7 is the min
                return (sqrt(((tmpx - x) * (tmpx - x)) + ((tmpy - y) * (tmpy - y))));
            case 'p':
                tmpx = 14 - pxx - 5; //14 is the max x coordinate
                tmpy = 9 - pyy - 7; //9 is the max, -7 is the min
                return (sqrt(((tmpx - x) * (tmpx - x)) + ((tmpy - y) * (tmpy - y))));
        }
    }

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
        if (isDead) {
            if (releaseTimer >= 50) {
                isDead = false;
                wasSick = false;
                drawnOnce = 0;
                releaseTimer = 0;
            }
            else {
                releaseTimer++;
            }
            return;
        }
        else if (exitCount() >= 3 ) {
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
        //check if ghost caught pacman or pacman caught ghost
        if (xx == pxx && yy == pyy) {
            if (isSick) {
                resetG();
                isDead = true;
                wasSick = true;
                drawnOnce = 1;
            }
            else gameState = 1;
        }
    }