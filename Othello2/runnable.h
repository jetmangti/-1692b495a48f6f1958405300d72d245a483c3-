#ifndef RUNNABLE_H
#define RUNNABLE_H
#include <thread>
/***********************************************************************************7
 * Martin Hlipala xhlipa00
 * Adam Bak xbakad00
 *
 * All rights reserved
 *
*/
class Runnable{
    public:
        std::thread t;
        void start(){
            this->t = std::thread(&Runnable::run, this);
        }
    protected:
        virtual void run(){
        }
};

#endif // RUNNABLE_H
