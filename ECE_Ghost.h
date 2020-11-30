#include <utility>
#include <thread>
#include <vector>
/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 10/26/2020
 * Description: Header file to define ghost class
 * */
//#pragma once
typedef std::pair<int, int> Pair;
extern bool isSick;
extern std::vector<Pair> mW;
//extern int gameState;
class ECE_Ghost {

    public:
        
        double xx, yy;
        double x1, y1;
        //0 = right, 1 = left, 2 = up, 3 = down
        int dir;
        bool couldMove;
        bool firstMove;
        bool wasSick;
        inline static int pxx = 10;
        inline static int pyy = 0;
        char color;
        //int isSick;
        //draw coordinates according to map array once, then position might change
        int drawnOnce = 0;
        ECE_Ghost(char color);
        //reset ghost position
        void resetG();
        int exitCount();
        int updateMove(std::vector<Pair> &vec);
        bool canMove(int dir2);
        double getDistance(int x, int y);
        void cornerHandler();
        bool isUnique(Pair p, std::vector<Pair> vec);
        void move();
        inline static int gameState = 0;
        static void drawRedGhost(ECE_Ghost g);
        static void drawPinkGhost(ECE_Ghost g);
        static void drawGreenGhost(ECE_Ghost g);
        static void drawOrangeGhost(ECE_Ghost g);
        //static int canMove(int key, ECE_Ghost g, char map[22][19]);
        //static void updateMove(ECE_Ghost &g, int x, int y, std::vector<Pair> &vec);
        
        

};