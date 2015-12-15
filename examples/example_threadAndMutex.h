 /*

 ####################################################################################
 #  BlackLib Library controls Beaglebone Black's inputs and outputs.                #
 #  Copyright (C) 2013-2015 by Yigit YUCE                                           #
 ####################################################################################
 #                                                                                  #
 #  This file is part of BlackLib library.                                          #
 #                                                                                  #
 #  BlackLib library is free software: you can redistribute it and/or modify        #
 #  it under the terms of the GNU Lesser General Public License as published by     #
 #  the Free Software Foundation, either version 3 of the License, or               #
 #  (at your option) any later version.                                             #
 #                                                                                  #
 #  BlackLib library is distributed in the hope that it will be useful,             #
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of                  #
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   #
 #  GNU Lesser General Public License for more details.                             #
 #                                                                                  #
 #  You should have received a copy of the GNU Lesser General Public License        #
 #  along with this program.  If not, see <http://www.gnu.org/licenses/>.           #
 #                                                                                  #
 #  For any comment or suggestion please contact the creator of BlackLib Library    #
 #  at ygtyce@gmail.com                                                             #
 #                                                                                  #
 ####################################################################################

 */

#ifndef EXAMPLE_THREADANDMUTEX_H_
#define EXAMPLE_THREADANDMUTEX_H_



#include "../BlackThread/BlackThread.h"
#include "../BlackMutex/BlackMutex.h"
#include <string>
#include <iostream>


int number;
BlackLib::BlackMutex *myMutex;



class Task1 : public BlackLib::BlackThread
{
   public:
    void onStartHandler()
    {
        myMutex->lock();
        std::cout << "Task1 doing the following operations: \n";
        std::cout << "Global variable(number)\'s current value: \n";
        for( int i = 0 ; i < 10 ; i++)
        {
            std::cout << ++number << " ";
            BlackLib::BlackThread::sleep(1);
        }
        std::cout << std::endl;
        myMutex->unlock();
    }
};

class Task2 : public BlackLib::BlackThread
{
   public:
    void onStartHandler()
    {
        BlackLib::BlackThread::sleep(3);
        if( myMutex->tryLock() )
        {
            std::cout << "Task2 doing the following operations: \n";
            std::cout << "Global variable(number)\'s current value: \n";
            for( int i = 0 ; i < 15 ; i++)
            {
                std::cout << --number << " ";
                BlackLib::BlackThread::sleep(1);
            }
                std::cout << std::endl;
            myMutex->unlock();
        }
        else
        {
            std::cout << "Task2 couldn\'t lock the mutex. ";
        }
    }
};


class Task3 : public BlackLib::BlackThread
{
  public:
    void onStartHandler()
    {
        if( myMutex->timedLock(20) )
        {
            std::cout << "Task3 doing the following operations: \n";
            std::cout << "Global variable(number)\'s current value: \n";
            for( int i = 0 ; i < 15 ; i++)
            {
                std::cout << ++number << " ";
            }
                std::cout << std::endl;
            myMutex->unlock();
        }
        else
        {
            std::cout << "Task3 couldn\'t lock the mutex. ";
        }
    }
};


class Task4 : public BlackLib::BlackThread
{

    private:
        std::string  myString;
        unsigned int tickTack;
        unsigned int currentLoop;
        bool         goAhead;


    public:

        Task4(unsigned int tt)
        {
            this->tickTack    = tt;
            this->myString    = "";
            this->currentLoop = 0;
            this->goAhead     = true;
        }

        void onStartHandler()
        {
            while( this->goAhead )
            {
                this->myString += "current loop is: " + BlackLib::tostr(this->currentLoop) + "\n";
                this->currentLoop++;
                BlackLib::BlackThread::sleep(this->tickTack);
            }
        }

        void onPauseHandler()
        {
            this->goAhead = false;     // exit from the while loop
        }

        void onResumeHandler()
        {
            this->myString += "my while loop is paused a short time ago.\n";
        }

        void onStopHandler()
        {
            this->myString += "i am exitting from thread.\n";
        }

        std::string getMessage()
        {
            return this->myString;
        }
};



void example_threadAndMutex()
{
    myMutex = new BlackLib::BlackMutex();
    number  = 0;

    Task1 *t1 = new Task1();
    Task2 *t2 = new Task2();
    Task3 *t3 = new Task3();
    Task4 *t4 = new Task4(1);

    t1->run();
    t2->run();
    t3->run();
    t4->run();


    BlackLib::BlackThread::sleep(20);
    t4->pause();


    bool conditionVariable = true;
    while( conditionVariable )
    {
        if( t4->isFinished() )
        {
            conditionVariable = false;
            std::cout << t4->getMessage();
        }
        else
        {
            sleep(2);
        }
    }



    WAIT_THREAD_FINISH(t1)
    WAIT_THREAD_FINISH(t2)
    t3->waitUntilFinish();
    t4->waitUntilFinish();
}

#endif /* EXAMPLE_THREADANDMUTEX_H_ */
