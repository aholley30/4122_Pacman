/* Author: Alessandria Holley
 * Class: ECE4122
 * Last Date Modified: 10/26/2020
 * Description: Header file to define ECE_Pacman class
 * */
class ECE_Pacman {
    public:
        ECE_Pacman();
        //0 = normal, 1 = over
        int gamseState;
        int xx, yy;
        //counts for coins and power ups
        int coinCount, puCount;
        //draws PacMan at the x and y coordinates specified by pac
        static void drawPacMan(ECE_Pacman pac);
        //returns 1 if pacman can move there, 0 if he can't
        static int canMove(int key, char map[22][19], ECE_Pacman pac); 
        //checks if there's a coin or power up at pacman's location
        static void coinPU(ECE_Pacman pac);
};