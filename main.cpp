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
#include <string.h>
#include <thread>
#include <vector>

int gameState;
int count = 0; //to count iterations, alternative to making threads sleep
#define ESC 27
//TODO: make vector of missing wall coordinates -> pass to dij - done
//TODO: reverse direction of ghosts when sick
//TODO: add  delay to ghosts on start, 2 each - done
//TODO: make ghosts killable - once killed, respawn after 5 sec
//TODO: make green ghost move
//make ghosts continously move

//make pacman continuously move - done

ECE_Pacman pac = ECE_Pacman();

bool isSick = false;
int drawnOnce = 0;
ECE_Ghost red = ECE_Ghost('r');
ECE_Ghost pink = ECE_Ghost('p');
ECE_Ghost green = ECE_Ghost('g');
ECE_Ghost orange = ECE_Ghost('o');

//std::thread thread;
bool firstRelease = true;
int sickTimer = 0;
int releaseTimer[4] = {0}; //for when ghosts get eaten
typedef std::pair<int, int> Pair; 
std::vector<Pair> mW; //missed wall coordinates
bool vecInit = true; //make sure vector is only initialized once
GLUquadricObj *c = gluNewQuadric();
GLUquadricObj *d = gluNewQuadric();
GLUquadricObj *p = gluNewQuadric();
//gluQuadricDrawStyle(GLU_SMOOTH);
// Camera position
float x = 30.0, y = 15.0, z = 15.0; // 33 ,10 , 15
float z_angle = 0.0;
float deltaMove = 0.0; // initially camera doesn't move
//static float g_lightPos[4] = {-95.0, 10.0, 5.0, 10.0 };  // added: Position of light
//std::thread t1;
bool enableGhosts = false;
int countp = 0;
// Mouse drag control
int isDragging = 0; //  true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

int gxx, gyy;
// Camera direction
float lx = 0.0, ly = 0.0; // camera points initially along y-axis

void coinPU() {
    if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'c') {
        pac.coinCount++;
        map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
    }
    else if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'p') {
        pac.puCount++;
        isSick = true;
        map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
    }
}

//reset the map, add coins and power ups back
void resetMap() {
    for(int i = 0; i < 22; i++) {
        for(int j = 0; j < 19; j++) {
            map1[i][j] = ogMap[i][j];
        }
    }
    int lives = pac.lifecount;
    //std::cout<<"lives: "<< lives<<std::endl;
    if(pac.lifecount >= 1) {
        pac = ECE_Pacman();
        pac.lifecount = lives;
        //pac.gamseState = 0;
    }
    else {
        pac = ECE_Pacman();
    }
    
    ECE_Ghost::pxx = pac.xx;
    ECE_Ghost::pyy = pac.yy;
    green.resetG();
    red.resetG();
    orange.resetG();
    pink.resetG();
    isSick = false;
    count = 0;
    countp = 0;
    //std::cout<< "gamestate: " << pac.gamseState <<std::endl;
    glutPostRedisplay();
}
//Update the display
int runThreads = 0;



void update(void)
{   
    //std::thread thread(ECE_Ghost::updateMove,red,std::make_pair(pac.xx,pac.yy));
    if (pac.coinCount >= 152 && pac.puCount == 4) {
        resetMap();
        pac.gamseState = 1;
        gameState = 1;
        pac.win = 1;
    } 
    
        
    //}
    else {
        //glPushMatrix();
        //ECE_Pacman::drawPacMan(pac);
        //ECE_Ghost g[4] = {green, red, pink, orange};
        //std::cout<<"gamestate: " << gameState <<std::endl;
        ECE_Ghost::pxx = pac.xx;
        ECE_Ghost::pyy = pac.yy;
        if (ECE_Ghost::gameState == 1) {
            //std::cout<< pac.lifecount <<std::endl;
            if(pac.lifecount > 1) {
                pac.lifecount--;
                //std::cout<<"updated lives: " << pac.lifecount <<std::endl;
                resetMap();
                gameState = 0;
                ECE_Ghost::gameState = 0;
                pac.gamseState = 0;
            }
            else {
                pac.gamseState = 1;
                //gameState = 1;
                //ECE_Ghost::gameState = 1;
            }
            
        }
        //ECE_Ghost::ghostInit( g, std::make_pair(pac.xx,pac.yy));
        
        // ECE_Ghost::updateMove(red,pac.xx,pac.yy);
        // ECE_Ghost::updateMove(pink,pac.xx,pac.yy);
        // ECE_Ghost::updateMove(green,pac.xx,pac.yy);
        // ECE_Ghost::updateMove(orange,pac.xx,pac.yy);
        
        std::thread th[4];
        if (enableGhosts) {
            if (count % 5 == 0) {
                if (red.wasSick) {
                    releaseTimer[0]++;
                    if (releaseTimer[0] >= 200) {
                        red.wasSick = false;
                        th[0] = std::thread(&ECE_Ghost::move,std::ref(red));
                        th[0].join();
                        releaseTimer[0] = 0;
                    }
                }
                else {
                    th[0] = std::thread(&ECE_Ghost::move,std::ref(red));
                    th[0].join(); 
                }
                
            }
            if (count >= 200 && count % 6 == 0) {
                if (green.wasSick) {
                    releaseTimer[1]++;
                    if(releaseTimer[1] >= 200) {
                        green.wasSick = false;
                        th[1] = std::thread(&ECE_Ghost::move,std::ref(green));
                        th[1].join();
                        releaseTimer[1] = 0;
                    }
                }
                else {
                    th[1] = std::thread(&ECE_Ghost::move,std::ref(green));
                    th[1].join();
                }
                
            }
            if (count >= 350 && count % 7 == 0) {
                if (pink.wasSick) {
                    releaseTimer[2]++;
                    if(releaseTimer[2] >= 200) {
                        pink.wasSick = false;
                        th[2] = std::thread(&ECE_Ghost::move,std::ref(pink));
                        th[2].join();
                        releaseTimer[2] = 0;
                    }
                }
                else {
                    th[2] = std::thread(&ECE_Ghost::move,std::ref(pink));
                    th[2].join();
                }
            }
            if (count >= 550 && count % 8 == 0) {
                if (orange.wasSick) {
                    releaseTimer[3]++;
                    if(releaseTimer[3] >= 200) {
                        orange.wasSick = false;
                        th[3] = std::thread(&ECE_Ghost::move,std::ref(orange));
                        th[3].join();
                        releaseTimer[3] = 0;
                    }
                }
                else {
                    th[3] = std::thread(&ECE_Ghost::move,std::ref(orange));
                    th[3].join();
                }
            }
            if (isSick) {
                sickTimer++;
                //std::cout<<sickTimer<<std::endl;
                if (sickTimer >= 400) {
                    isSick = false;
                    //printf("not sick anymore");
                    sickTimer = 0;
                }
            }
        }

        if(pac.canMove(pac.dir) && countp % 2 == 0) {
            coinPU();
            pac.move();
        }
        //ECE_Ghost::updateMove(green, pac.xx,pac.yy,mW );
        //th[1] = std::thread(ECE_Ghost::updateMove,std::ref(pink),pac.xx,pac.yy);
        //th[2] = std::thread(ECE_Ghost::updateMove,std::ref(green),pac.xx,pac.yy);;
        //th[3] = std::thread(ECE_Ghost::updateMove,std::ref(orange),pac.xx,pac.yy);;
       if(ECE_Ghost::gameState == 1) {
           pac.gamseState = 1;
           gameState = 1;
       }
        //for (auto& threads : th) threads.join();
        
        //std::cout << red.xx << ", " << red.yy <<std::endl;
        //ECE_Ghost::drawRedGhost(red);
        //idk = std::thread([ths] { this->aStarSearch(map1,Pair(15-green.xx,10-green.yy),Pair(15-pac.xx,10-pac.yy), green); });
        //std::thread thread(dijkstra::aStarSearch,map1,Pair(15-red.xx,10-red.yy),Pair(15-pac.xx,10-pac.yy));
        //glPopMatrix();
        if (enableGhosts) count++;
    }
    countp++;
    //std::cout<<"current pos: " << pac.xx << ", " << pac.yy << std::endl;
    glutPostRedisplay(); // redisplay everything
}
bool isUnique(Pair p, std::vector<Pair> vec) {
    if (vec.empty()) return true;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == p) {
            //std::cout <<"wall at: " << p.first << ", " << p.second << std::endl;
            return false;
        } 
    }
    return true;
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
/* Draw a character string.
 *
 * @param x        The x position
 * @param y        The y position
 * @param z        The z position
 * @param string   The character string
 */
void drawString(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);  // Updates the position
  }
}
        
//draws whole scene: walls, ghosts, pacman, etc. Sets cam location
void renderScene() {
    if (vecInit) {
        //add 15, 10 back
        mW.push_back(std::make_pair(6,9));
        mW.push_back(std::make_pair(6,7));
        mW.push_back(std::make_pair(8,5));
        mW.push_back(std::make_pair(8,3));
        mW.push_back(std::make_pair(4,1));
        mW.push_back(std::make_pair(2,7));
        mW.push_back(std::make_pair(2,9));
        mW.push_back(std::make_pair(2,16));
        mW.push_back(std::make_pair(4,15));
        mW.push_back(std::make_pair(6,13));
        mW.push_back(std::make_pair(8,13));
        mW.push_back(std::make_pair(6,16));
        mW.push_back(std::make_pair(8,11));
        mW.push_back(std::make_pair(12,5));
        mW.push_back(std::make_pair(16,3));
        mW.push_back(std::make_pair(18,3));
        mW.push_back(std::make_pair(18,7));
        mW.push_back(std::make_pair(18,9));
        mW.push_back(std::make_pair(18,13));
        mW.push_back(std::make_pair(18,16));
        mW.push_back(std::make_pair(16,16));
        mW.push_back(std::make_pair(4,3));
        mW.push_back(std::make_pair(16,11));
        mW.push_back(std::make_pair(14,7));
        mW.push_back(std::make_pair(12,3));
        mW.push_back(std::make_pair(12,13));
        mW.push_back(std::make_pair(4,-10));
        mW.push_back(std::make_pair(4,11));
        vecInit = false;
    }
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
    if (pac.gamseState == 0) 
    {
        
        int rowRed = 0;
        int colRed = 0;
        //wrap whole map in push/pop in order to rotate it easier
        glPushMatrix();
        //change view angle when "R" is pressed
        glRotatef(z_angle, 0.0, 0.0, 1.0);
        //iterate over map array to draw items in right place
        for (int row = 0; row < 22; ++row)
        {
            for (int col = 0; col < 19; ++col)
            {
                char elem = map1[row][col];
                switch (elem)
                {
                //draw vertical walls
                case 'v':
                    glPushMatrix();
                    glTranslatef(15 - row, 10 - col, -1.0);
                    drawCylinder(2);
                    glPopMatrix();
                    
                    //fill in some missing walls
                    if (map1[row+1][col] == 'h' && (row < 18 || row == 20)) {
                        glPushMatrix();
                        glTranslatef(15 - row - 1, 10 - col, -1.0);
                        if (isUnique(std::make_pair(row -1,col), mW)) {
                            mW.push_back(std::make_pair(row - 1,col));
                        }
                        drawCylinder(2);
                        glPopMatrix();
                    }
                    //complete the upper boxes
                    if (row == 19 && (col == 3 || col == 7 || col == 13 || col == 16)) {
                        //1x1 box
                        if (col == 3 || col == 16) {
                            glPushMatrix();
                            glTranslatef(15 - row, 10 - col + 1, -1.0);
                            if (isUnique(std::make_pair(row,col+1), mW)) {
                                mW.push_back(std::make_pair(row,col+1));
                            }
                            drawCylinder(2);
                            glPopMatrix();
                        }
                        //1x2 box
                        else {
                            glPushMatrix();
                            glTranslatef(15 - row, 10 - col + 2, -1.0);
                            if (isUnique(std::make_pair(row,col+2), mW)) {
                                mW.push_back(std::make_pair(row,col+2));
                            }
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
                        gameState = pac.gamseState;
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
                    if (green.drawnOnce == 0) {
                        green.xx = 15 - row + 0.5;
                        green.x1 = green.xx;
                        green.yy = 10 - col;
                        green.y1 = green.yy;
                    }
                    ECE_Ghost::drawGreenGhost(green);
                    green.drawnOnce = 1;
                    glPopMatrix();
                    break;
                //draw Pink and Red ghosts
                case '7':
                    glPushMatrix();
                    //glTranslatef(15 - row + 0.5, 10 - col, -1.0);
                    if (pink.drawnOnce == 0) {
                        pink.xx = 15 - row + 0.5;
                        pink.yy = 10 - col;
                        pink.x1 = pink.xx;
                        pink.y1 = pink.yy;
                    }
                    ECE_Ghost::drawPinkGhost(pink);
                    pink.drawnOnce = 1;
                    glPopMatrix();
                    rowRed = row;
                    colRed = col;
                    glPushMatrix();
                    //glTranslatef(15 - rowRed - 0.5, 10 - colRed, -1.0);
                    if (red.drawnOnce == 0) {
                        red.xx = 15 - rowRed - 0.5;
                        red.yy = 10 - colRed;
                        red.x1 = red.xx;
                        red.y1 = red.yy;
                        //std::cout << red.xx << ", " << red.yy << std::endl;
                    }
                    ECE_Ghost::drawRedGhost(red);
                    red.drawnOnce = 1;
                    glPopMatrix();
                    break;
                //draw orange ghost
                case '8':
                    glPushMatrix();
                    //glTranslatef(15 - row + 0.5, 10 - col, -1.0);
                    if (orange.drawnOnce == 0) {
                        orange.xx = 15 - row + 0.5;
                        orange.yy = 10 - col;
                        orange.x1 = orange.xx;
                        orange.y1 = orange.yy;
                    }
                    ECE_Ghost::drawOrangeGhost(orange);
                    orange.drawnOnce = 1;
                    glPopMatrix();
                    break;
                }
            }
        }

        glPopMatrix();
    }
    else {
        glPushMatrix();
        //char string[11] = "Game Over!";
        glColor3f(1.0, 1.0, 1.0);
        if (pac.win == 1) {
            char string[20] = "Game Over. You won!";
            drawString(0,0,1,string);
        } else {
            char string[23] = "Game Over. You lost :(";
            drawString(0,0,1,string);
        }
        char string2[] = "press p to play again";
        drawString(7,3.5,1,string2);
        
       
        
        
        glPopMatrix();

    }
    
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
    else if (key == 'R' && pac.gamseState == 0) {
        z_angle = ((int)z_angle - 5) % 360;
        glutPostRedisplay();
    }
    else if (key == 's' && pac.gamseState == 0) {
        std::cout << "Coins: " << pac.coinCount <<std::endl;
        std::cout << "PowerUps: " << pac.puCount <<std::endl;
    }
    else if (key == 'p') {
        //std::cout << "play again" << std::endl;
        //std::cout << "lives: " << pac.lifecount <<std::endl;
        pac.gamseState = 0;
        resetMap();
        pac.lifecount = 4;
        //update();
    }
    else if (key == 'g') {
        enableGhosts = !enableGhosts;
    }
    else if (key == 'm') {
        std::cout << "pacman grid: " << pac.xx << ", " << pac.yy <<std::endl;
        std::cout << "pacman map: " <<15 - pac.xx << ", " << 10 - pac.yy <<std::endl;
        //std::cout << "red: " << red.xx << ", " << red.yy <<std::endl;
    }

}
//move pacman based on key press
void pressSpecialKey(int key, int xx, int yy)
{
    switch(key) 
    {
    case GLUT_KEY_UP: 
    if (pac.canMove(key) && pac.gamseState == 0 && isUnique(std::make_pair(15 -pac.xx+1, 10 - pac.yy), mW)) {
        //std::cout << map1[15 - pac.xx - 1][10 - pac.yy] <<std::endl;
        //std::cout << 15 -pac.xx+1 << ", " << 10 - pac.yy << "is unique" << std::endl;
        if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'c') {
            pac.coinCount++;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        else if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'p') {
            pac.puCount++;
            isSick = true;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        //pac.xx--;
        pac.dir = key;
        //std::cout << "x: " << 15- pac.xx << " y: " << 10 - pac.yy << std::endl;
        //std::cout<<"current pos: " << 15 - pac.xx << ", " << 10 - pac.yy << std::endl;
        update();
    } break;
    case GLUT_KEY_DOWN:
    if (pac.canMove(key) && pac.gamseState == 0 && isUnique(std::make_pair(15 -pac.xx-1, 10 - pac.yy), mW)) {
        //std::cout << map[15 - pac.xx + 1][10 - pac.yy] <<std::endl;
        //std::cout << "x: " << 15 - pac.xx + 1 << " y: " << 10 - pac.yy << std::endl;
        
        if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'c') {
            pac.coinCount++;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        else if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'p') {
            pac.puCount++;
            isSick = true;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        //pac.xx++;
        pac.dir = key;
        //std::cout << "x: " << 15 - pac.xx << " y: " << 10 - pac.yy << std::endl;
        //ECE_Ghost::pxx = pac.xx;
        //std::cout<<"current pos: " << 15 - pac.xx << ", " << 10 - pac.yy << std::endl;
        update();
    } break;
    case GLUT_KEY_RIGHT:
    if (pac.canMove(key) && pac.gamseState == 0 && isUnique(std::make_pair(15 -pac.xx, 10 - pac.yy - 1), mW)) {
        //std::cout << map[15 - pac.xx][10 - pac.yy + 1] <<std::endl;
        //enableGhosts = true;
        //std::cout << "x: " << 15 - pac.xx << " y: " << 10 - pac.yy + 1 << std::endl;
        if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'c') {
            pac.coinCount++;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        else if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'p') {
            pac.puCount++;
            isSick = true;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        
        if ((int)round(pac.xx) == 4 && (int)round(pac.yy) == 10) {
            pac.dir = 0;
            pac.xx = 4;
            pac.yy = -9;
        } else {
            pac.dir = key;
            //pac.yy++;
        }

        //std::cout<<"current pos: " << pac.xx << ", " << pac.yy << std::endl;
        //std::cout << "x: " << 15 - pac.xx << " y: " << 10 - pac.yy << std::endl;
        update();
    } break;
    case GLUT_KEY_LEFT:
    //std::cout<<"left" <<std::endl;
    if ((pac.canMove(key) || (pac.xx == 4 && pac.yy == -8)) && pac.gamseState == 0 && isUnique(std::make_pair(15 -pac.xx, 10 - pac.yy + 1), mW)) {
        //std::cout << map[15 - pac.xx][10 - pac.yy - 1] <<std::endl;
        //std::cout << "x: " << pac.xx << " y: " << pac.yy << std::endl;
        //std::cout << 15 -pac.xx << ", " << 10 - pac.yy + 1 << "is unique" << std::endl;
        //std::cout << "x: " << 15 - pac.xx << " y: " << 10 - pac.yy - 1 << std::endl;
        if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'c') {
            pac.coinCount++;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        else if (map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] == 'p') {
            pac.puCount++;
            isSick = true;
            map1[15-(int)round(pac.xx)][10-(int)round(pac.yy)] = '0';
        }
        if ((int)round(pac.xx) == 4 && (int)round(pac.yy) == -8) {
            pac.dir = 1;
            pac.xx = 4;
            pac.yy = 10;
        } 
        else {
            pac.dir = key;
            //pac.yy--;
        }
        
        //std::cout<<"current pos: " << pac.xx << ", " << pac.yy << std::endl;
        //std::cout << "x: " << 15 - pac.xx << " y: " << 10 - pac.yy << std::endl;
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