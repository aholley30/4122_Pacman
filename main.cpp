/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 10/29/2020
 * Description: Draws a static, 3d representation of a pacman game using OpenGl
 * */
#include "ECE_Pacman.h"
#include "ECE_Ghost.h"
#include <GL/glut.h>
#include <math.h>
#include "map.h"
#include <iostream>


#define ESC 27


ECE_Pacman pac = ECE_Pacman();



GLUquadricObj *c = gluNewQuadric();
GLUquadricObj *d = gluNewQuadric();
GLUquadricObj *p = gluNewQuadric();
//gluQuadricDrawStyle(GLU_SMOOTH);
// Camera position
float x = 30.0, y = 15.0, z = 15.0; // 33 ,10 , 15
float z_angle = 0.0;
float deltaMove = 0.0; // initially camera doesn't move
//static float g_lightPos[4] = {-95.0, 10.0, 5.0, 10.0 };  // added: Position of light



// Mouse drag control
int isDragging = 0; //  true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

// Camera direction
float lx = 0.0, ly = 0.0; // camera points initially along y-axis


//Update the display
void update(void)
{   
    
    glPushMatrix();
    ECE_Pacman::drawPacMan(pac);
    glPopMatrix();
    //std::cout<<"current pos: " << pac.xx << ", " << pac.yy << std::endl;
    glutPostRedisplay(); // redisplay everything
}
//initialize display
void init() {
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR | GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    //pac.xx =10;
    //pac.yy =1;
}
//allow display to be resized while maintaing aspect ratio
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}
//draws a wall: blue cylinder with spheres on both ends to give a curved shape
//param dir specifies whether to draw horizontal or vertical wall
void drawCylinder(int dir) {
    
    glColor4f(0,0,1,1);
    switch(dir) {
        case 1: //horizontal
            glPushMatrix();
                glPushMatrix();
                glTranslatef(0.0, -1.0, 0.0); 
                glutSolidSphere(0.1, 20, 20); // add sphere to other end
                
                glPopMatrix();
                glRotatef(90.0,1.0,0.0,0.0); //make horizontal
                gluCylinder(d,0.1,0.1, 1, 20,20); //draw wall
                glutSolidSphere(0.1, 20, 20); //add sphere to end
            glPopMatrix();
            break;
        case 2: //vertical
            glPushMatrix();
                glPushMatrix();
                glTranslatef(1.0, 0.0, 0.0); //add sphere to end
                glutSolidSphere(0.1, 20, 20);
                glPopMatrix();

                glRotatef(90.0,0.0,1.0,0.0); //make vertical
                gluCylinder(c,0.1,0.1, 1, 20,20); //draw wall
                glutSolidSphere(0.1, 20, 20); //add sphere to other end
            glPopMatrix();
            break;
             
    }
    
           
    
}
//draws a powerUp
void drawPowerUp() {
    glColor3f(0.77, 0.70, 0.345);
    glPushMatrix();
        gluCylinder(c,0.2,0.2, 0.1, 20,20); //draw base of coin
        glTranslatef(0.0,0.0,0.1);
        gluDisk(p,0.0,0.2,40,20); //draw top
    glPopMatrix();
}
//draws a coin
void drawCoin() {
    glColor3f(192.0/255.0, 192.0/255.0, 192.0/255.0);
    glPushMatrix();
        glutSolidSphere(0.1, 20, 20); // tiny dot
    glPopMatrix();
}
//draws whole scene: walls, ghosts, pacman, etc. Sets cam location
void renderScene() {

    // Clear color and depth buffers
    glClearColor(0.0, 0.0, 0.0, 1.0); // background is black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();

    // Set the camera centered at (x,y,1) and looking along directional
    // vector (lx, ly, 0), with the z-axis pointing up
    gluLookAt(
        x, y, z,
        lx, ly, 0.0,
        0.0, 0.0, 1.0);
    
    int rowRed = 0;
    int colRed = 0;
    //wrap whole map in push/pop in order to rotate it easier
    glPushMatrix();
    //change view angle when "R" is pressed
    glRotatef(z_angle,0.0,0.0,1.0); 
    //iterate over map array to draw items in right place
    for (int row = 0; row < 22; ++row) {
        for (int col = 0; col < 19; ++col) {
            char elem = map[row][col];
            switch(elem) {
                //draw vertical walls
                case 'v':
                    glPushMatrix();
                    glTranslatef(15 - row, 10 - col, -1.0);
                    drawCylinder(2);
                    glPopMatrix();
                    
                    //fill in some missing walls
                    if (map[row+1][col] == 'h' && (row < 18 || row == 20)) {
                        glPushMatrix();
                        glTranslatef(15 - row - 1, 10 - col, -1.0);
                        drawCylinder(2);
                        glPopMatrix();
                    }
                    //complete the upper boxes
                    if (row == 19 && (col == 3 || col == 7 || col == 13 || col == 16)) {
                        //1x1 box
                        if (col == 3 || col == 16) {
                            glPushMatrix();
                            glTranslatef(15 - row, 10 - col + 1, -1.0);
                            drawCylinder(2);
                            glPopMatrix();
                        }
                        //1x2 box
                        else {
                            glPushMatrix();
                            glTranslatef(15 - row, 10 - col + 2, -1.0);
                            drawCylinder(2);
                            glPopMatrix();
                        }
                        
                    }
                    
                    break;
                //draw a coin    
                case 'c':
                    glPushMatrix();
                    glTranslatef(15 - row, 10 - col, -1.0);
                    
                    drawCoin();
                    glPopMatrix();
                    break;
                //draw power up
                case 'p':
                    glPushMatrix();
                    glTranslatef(15 - row, 10 - col, -1.0);
                    
                    drawPowerUp();
                    glPopMatrix();
                    break;
                //draw pacman
                case 'm':
                    
                        glPushMatrix();
                        //glTranslatef(15 - row, 10 - col, -1.0);
                        //std::cout<< pac.xx << " " << pac.yy << std::endl;
                        ECE_Pacman::drawPacMan(pac);
                        glPopMatrix();
                        
                    
                    break;
                //draw horizontal walls
                case 'h':
                    glPushMatrix();
                    glTranslatef(15 - row, 10 - col, -1.0);
                    drawCylinder(1);
                    glPopMatrix();
                    break;
                //red ghost couldn't fit in map array; is drawn with Pink Ghost
                case '5':
                    break;
                //draw green ghost
                case '6':
                    glPushMatrix();
                    glTranslatef(15 - row + 0.5, 10 - col, -1.0);
                    ECE_Ghost::drawGreenGhost();
                    glPopMatrix();
                    break;
                //draw Pink and Red ghosts
                case '7':
                    glPushMatrix();
                    glTranslatef(15 - row + 0.5, 10 - col, -1.0);
                    ECE_Ghost::drawPinkGhost();
                    glPopMatrix();
                    rowRed = row;
                    colRed = col;
                    glPushMatrix();
                    glTranslatef(15 - rowRed - 0.5, 10 - colRed, -1.0);
                    ECE_Ghost::drawRedGhost();
                    glPopMatrix();
                    break;
                //draw orange ghost
                case '8':
                    glPushMatrix();
                    glTranslatef(15 - row + 0.5, 10 - col, -1.0);
                    ECE_Ghost::drawOrangeGhost();
                    glPopMatrix();
                    break;
                

            }
        }
    }

    glPopMatrix();
    
    glutSwapBuffers(); //draw everything
    
    
}
//allow key presses to effect something on display
void processNormalKeys(unsigned char key, int xx, int yy)
{
    //close window
    if (key == ESC || key == 'q' || key == 'Q')
    {
        exit(0);
    } 
    //adjust angle by 5 degrees
    else if (key == 'R') {
        z_angle = ((int)z_angle - 5) % 360;
        glutPostRedisplay();
    }
    else if (key == 's') {
        std::cout << "Coins: " << pac.coinCount <<std::endl;
        std::cout << "PowerUps: " << pac.puCount <<std::endl;
    }

}
//move map up or down
void pressSpecialKey(int key, int xx, int yy)
{
    switch(key) 
    {
    case GLUT_KEY_UP: 
    if (ECE_Pacman::canMove(key, map, pac)) {
        //std::cout << map[15 - pac.xx - 1][10 - pac.yy] <<std::endl;
        //std::cout << "x: " << 15 - pac.xx - 1 << " y: " << 10 - pac.yy << std::endl;
        if (map[15-pac.xx][10-pac.yy] == 'c') {
            pac.coinCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        else if (map[15-pac.xx][10-pac.yy] == 'p') {
            pac.puCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        pac.xx--;
        //std::cout<<"current pos: " << 15 - pac.xx << ", " << 10 - pac.yy << std::endl;
        update();
    } break;
    case GLUT_KEY_DOWN:
    if (ECE_Pacman::canMove(key, map, pac)) {
        //std::cout << map[15 - pac.xx + 1][10 - pac.yy] <<std::endl;
        //std::cout << "x: " << 15 - pac.xx + 1 << " y: " << 10 - pac.yy << std::endl;
        if (map[15-pac.xx][10-pac.yy] == 'c') {
            pac.coinCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        else if (map[15-pac.xx][10-pac.yy] == 'p') {
            pac.puCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        pac.xx++;
        //std::cout<<"current pos: " << 15 - pac.xx << ", " << 10 - pac.yy << std::endl;
        update();
    } break;
    case GLUT_KEY_RIGHT:
    if (ECE_Pacman::canMove(key, map, pac)) {
        //std::cout << map[15 - pac.xx][10 - pac.yy + 1] <<std::endl;
        //std::cout << "x: " << 15 - pac.xx << " y: " << 10 - pac.yy + 1 << std::endl;
        if (map[15-pac.xx][10-pac.yy] == 'c') {
            pac.coinCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        else if (map[15-pac.xx][10-pac.yy] == 'p') {
            pac.puCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        
        if (pac.xx == 4 && pac.yy == 10) {
            pac.xx = 4;
            pac.yy = -9;
        } else {
            pac.yy++;
        }

        //std::cout<<"current pos: " << pac.xx << ", " << pac.yy << std::endl;
        update();
    } break;
    case GLUT_KEY_LEFT:
    //std::cout<<"left" <<std::endl;
    if (ECE_Pacman::canMove(key, map, pac) || (pac.xx == 4 && pac.yy == -8)) {
        //std::cout << map[15 - pac.xx][10 - pac.yy - 1] <<std::endl;
        //std::cout << "x: " << 15 - pac.xx << " y: " << 10 - pac.yy - 1 << std::endl;
        if (map[15-pac.xx][10-pac.yy] == 'c') {
            pac.coinCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        else if (map[15-pac.xx][10-pac.yy] == 'p') {
            pac.puCount++;
            map[15-pac.xx][10-pac.yy] = '0';
        }
        if (pac.xx == 4 && pac.yy == -8) {
            pac.xx = 4;
            pac.yy = 10;
        } 
        else {
            pac.yy--;
        }
        
        //std::cout<<"current pos: " << pac.xx << ", " << pac.yy << std::endl;
        update();
    } break;
    }
    
    
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_RGB);
    glutInitWindowPosition(100, 1);
    glutInitWindowSize(1600, 800);
    glutCreateWindow("ECE 4122 Pacman");
    init();
    glutReshapeFunc(changeSize); // window reshape callback
    glutDisplayFunc(renderScene); // (re)display callback
    glutIdleFunc(update); // incremental update
    glutKeyboardFunc(processNormalKeys); // process standard key clicks
    glutSpecialFunc(pressSpecialKey); // process special key pressed

    glutMainLoop();
    return 0;

}