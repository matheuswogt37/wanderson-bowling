#ifndef Pos_hpp
#define Pos_hpp

class Pos {
    private:
        int x, y;

    public:
        Pos(int x, int y);
        ~Pos();
        void setPos(int x, int y);
        int getX();
        int getY();
};

#endif