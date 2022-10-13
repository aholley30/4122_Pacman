#include <utility>
#include <thread>
#include <vector>
#include <memory>
/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 10/26/2020
 * Description: Header file to define ghost class
 * */
//#pragma once
using namespace std;
typedef pair<int, int> Pair;
extern bool isSick;
extern vector<Pair> mW;
//extern int gameState;
class ECE_Ghost {

    public:
        //current coordinates
        double xx, yy;
        //original coordinates
        double x1, y1;
        //0 = right, 1 = left, 2 = up, 3 = down
        int dir;
        bool couldMove;
        //if it is it's first time moving, adjust coordinate to whole #
        bool firstMove;
        //if a ghost was sick before being redraw, it needs to wait 5 sec
        bool wasSick; 
        bool isDead = false;
        int releaseTimer = 0;
        int limit;
        //pacman's coordinates, updated in main
        inline static int pxx = 10;
        inline static int pyy = 0;
        //0 = running, 1 = over
        inline static int gameState = 0;
        char color;
        static unique_ptr<ECE_Ghost> ghosts[4];

        //draw coordinates according to map array once, then position might change
        int drawnOnce = 0;
        //contructor
        ECE_Ghost(char color);
        //reset ghost positions
        void resetG();
        int exitCount();
        int updateMove(vector<Pair> &vec);
        bool canMove(int dir2);
        double getDistance(int x, int y);
        void cornerHandler();
        bool isUnique(Pair p, vector<Pair> vec);
        void move();
        //static std::vector<std::unique_ptr<ECE_Ghost>> ghostVec();
        void drawGhost();
        void initGhost(int row, int col);

        //static int canMove(int key, ECE_Ghost g, char map[22][19]);
        //static void updateMove(ECE_Ghost &g, int x, int y, std::vector<Pair> &vec);
        
        

};