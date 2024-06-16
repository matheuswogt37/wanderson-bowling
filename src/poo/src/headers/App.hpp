#ifndef App_hpp
#define App_hpp

#include <iostream>
#include "headers/Console.hpp"

class App {
    private:
        Console *console;

        void run();
        void update();
        void render();
        void end();
    public:
        App();
        ~App();
        void start();

};

#endif