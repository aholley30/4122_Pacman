#ifndef GAMEPIECE
#define GAMEPIECE

class gamePiece {

    public:
        virtual void move() = 0;
        virtual bool canMove(int dir) = 0;
        virtual void draw() = 0;

};


#endif