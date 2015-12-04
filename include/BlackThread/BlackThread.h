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



#ifndef BLACKTHREAD_H_
#define BLACKTHREAD_H_

#include <cstdint>
#include <pthread.h>
#include <sched.h>
#include <vector>
#include <unistd.h>






namespace BlackLib
{
    #define WAIT_THREAD_FINISH(thrd) (thrd)->waitUntilFinish();     //!< Application waits until thread finished at this line where this macro used.


    // ########################################### BLACKTHREAD DECLARATION STARTS ############################################ //

    /*! @brief Interface class for user specific thread class.
    *
    *    This class is the base class of the user defined thread class. This class
    *    includes all functions which are necessary for the basic thread struct. This class
    *    is a pure abstract class so users can't instantiate object from it. Users have to
    *    derive their own class(es) from the BlackThread class and they have to re-implement
    *    or override some functions. This class uses pthread on the base so it is compatible
    *    with multiplatforms.
    *
    * @par Example
    @verbatim
    EXAMPLE PROJECT FILE TREE:

        myThreadProject
         |-> src
             |-> BlackLib
                 |-> BlackDirectory
                     |-> BlackDirectory.cpp
                     |-> BlackDirectory.h
                 |-> BlackThread
                     |-> BlackThread.cpp
                     |-> BlackThread.h
                 |-> BlackMutex
                     |-> BlackMutex.cpp
                     |-> BlackMutex.h
                 |-> BlackTime
                     |-> BlackTime.cpp
                     |-> BlackTime.h
                 |-> BlackADC
                     |-> BlackADC.cpp
                     |-> BlackADC.h
                 |-> BlackGPIO
                     |-> BlackGPIO.cpp
                     |-> BlackGPIO.h
                 |-> BlackI2C
                     |-> BlackI2C.cpp
                     |-> BlackI2C.h
                 |-> BlackPWM
                     |-> BlackPWM.cpp
                     |-> BlackPWM.h
                 |-> BlackSPI
                     |-> BlackSPI.cpp
                     |-> BlackSPI.h
                 |-> BlackUART
                     |-> BlackUART.cpp
                     |-> BlackUART.h
                 |-> BlackCore.cpp
                 |-> BlackCore.h
                 |-> BlackDef.h
                 |-> BlackErr.h
                 |-> BlackLib.h
            |-> myThreadProject.cpp
    @endverbatim
    *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
    *  include BlackThread.h or another source files with adding this line to your project file (myThreadProject.cpp at
    *  the example):
    *  @code{.cpp}
    *      #include "BlackLib/BlackThread/BlackThread.h"
    *  @endcode
    *  @n@n If BlackLib source files are located at same level with your project file (myThreadProject.cpp at the
    *  example), you have to include BlackThread.h or another source files with adding this line to your project file:
    *  @code{.cpp}
    *      #include "BlackThread/BlackThread.h"
    *  @endcode
    *  @n @n
    *  @code{.cpp}
    *  // Filename: myThreadProject.cpp
    *  // Author:   Yiğit Yüce - ygtyce@gmail.com
    *
    *  #include <iostream>
    *  #include "BlackLib/BlackThread/BlackThread.h"
    *
    *  class Task1 : public BlackLib::BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onPauseHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onResumeHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onStopHandler()
    *           {
    *               // do something here
    *           }
    *  };
    *
    *
    *  class Task2 : public BlackLib::BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onStopHandler()
    *           {
    *               // do something here
    *           }
    *  };
    *
    *
    *  int main()
    *  {
    *       Task1 *t1 = new Task1();
    *       Task2 *t2 = new Task2();
    *
    *       t1->run();
    *       t2->run();
    *
    *       // do some other things here
    *
    *       WAIT_THREAD_FINISH(t1)
    *       WAIT_THREAD_FINISH(t2)
    *
    *       return 0;
    *  }
    * @endcode
    * @n @n
    * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
    * @code{.cpp}
    *  // Filename: myThreadProject.cpp
    *  // Author:   Yiğit Yüce - ygtyce@gmail.com
    *
    *  #include <iostream>
    *  #include "BlackLib/BlackThread/BlackThread.h"
    *  using namespace BlackLib;
    *
    *  class Task1 : public BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onPauseHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onResumeHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onStopHandler()
    *           {
    *               // do something here
    *           }
    *  };
    *
    *
    *  class Task2 : public BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               // do something here
    *           }
    *
    *           void onStopHandler()
    *           {
    *               // do something here
    *           }
    *  };
    *
    *
    *  int main()
    *  {
    *       Task1 *t1 = new Task1();
    *       Task2 *t2 = new Task2();
    *
    *       t1->run();
    *       t2->run();
    *
    *       // do some other things here
    *
    *       WAIT_THREAD_FINISH(t1)
    *       WAIT_THREAD_FINISH(t2)
    *
    *       return 0;
    *  }
    * @endcode
    *
    */
    class BlackThread
    {
        public:

            /*!
            * This enum is used to define thread's current state.
            */
            enum state
            {
                Stateless     = 0,            /*!< enumeration for @a stateless state thread */
                Running       = 1,            /*!< enumeration for @a running state thread */
                Stopped       = 2,            /*!< enumeration for @a stopped state thread */
                Paused        = 3             /*!< enumeration for @a paused state thread */
            };

            /*!
            * This enum is used to define thread's priority.
            */
            enum priority
            {
                PriorityDEFAULT  = -1,        /*!< enumeration for @a default priority thread */
                PriorityLOWEST   = 0,         /*!< enumeration for @a lowest priority thread */
                PriorityLOW      = 1,         /*!< enumeration for @a low priority thread */
                PriorityNORMAL   = 2,         /*!< enumeration for @a normal priority thread */
                PriorityHIGH     = 3,         /*!< enumeration for @a high priority thread */
                PriorityHIGHEST  = 4,         /*!< enumeration for @a highest priority thread */

                #ifdef SCHED_IDLE
                    PriorityIDLE = 5,         /*!< enumeration for @a idle priority thread */
                #endif
            };

            /*! @brief Constructor of BlackThread class.
            *
            * This function sets the thread state to "stateless", thread priority to "default"
            * and calculates platform depend priority values. This function calls when the users
            * derived class is instantiated.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *
            *       t1->run();
            *
            *       WAIT_THREAD_FINISH(t1)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa calculatePriorities()
            */
                                    BlackThread();

            /*! @brief Destructor of BlackThread class.
            *
            */
            virtual                 ~BlackThread();

            /*! @brief Changes the priority of thread.
            *
            * This function changes the thread's priority if the user's platform is
            * allowed for this operation.
            *
            * @param [in] tp    new thread priority
            *
            *  @return Current thread priority.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       t1->setPriority(BlackLib::BlackThread::PriorityHIGHEST);
            *
            *       t1->run();
            *
            *       t1->setPriority(BlackLib::BlackThread::PriorityLOWEST);
            *
            *       WAIT_THREAD_FINISH(t1)
            *
            *       return 0;
            *  }
            * @endcode
            */
            BlackThread::priority   setPriority(BlackThread::priority tp);


            /*! @brief Exports the priority of thread.
            *
            *  @return Current thread priority.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       t1->setPriority(BlackLib::BlackThread::PriorityHIGHEST);
            *
            *       t1->run();
            *
            *       std::cout << "current thread priority: " << t1->getPriority();
            *
            *       WAIT_THREAD_FINISH(t1)
            *
            *       return 0;
            *  }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // current thread priority: 4
            * @endcode
            */
            BlackThread::priority   getPriority();

            /*! @brief Exports the thread native id.
            *
            *  @return thread id.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *
            *       std::cout << "Current thread id: " << t1->getThreadId();
            *
            *       t1->run();
            *
            *       std::cout << "Current thread id: " << t1->getThreadId();
            *
            *       WAIT_THREAD_FINISH(t1)
            *
            *       return 0;
            *  }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current thread id: 0
            *   // Current thread id: 46231
            * @endcode
            */
            const pthread_t         getThreadId();

            /*! @brief Sleeps the thread for specified second(s).
            *
            * @param [in] sec    time in seconds
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   std::cout << "Main is a thread also and it will sleep 2 seconds now." << std::endl;
            *
            *   BlackLib::BlackThread::sleep(2);
            *
            *   std::cout << "Main thread woke up." << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Main is a thread also and it will sleep 2 seconds now.
            *   // Main thread woke up.
            * @endcode
            */
            static void             sleep(unsigned int sec);

            /*! @brief Sleeps the thread for specified milisecond(s).
            *
            * @param [in] msec    time in miliseconds
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   std::cout << "Main is a thread also and it will sleep 2000 miliseconds now." << std::endl;
            *
            *   BlackLib::BlackThread::msleep(2000);
            *
            *   std::cout << "Main thread woke up." << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Main is a thread also and it will sleep 2000 miliseconds now.
            *   // Main thread woke up.
            * @endcode
            */
            static void             msleep(unsigned int msec);

            /*! @brief Sleeps the thread for specified microsecond(s).
            *
            * @param [in] usec    time in microseconds
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   std::cout << "Main is a thread also and it will sleep 2000 microseconds now." << std::endl;
            *
            *   BlackLib::BlackThread::2sleep(2000);
            *
            *   std::cout << "Main thread woke up." << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Main is a thread also and it will sleep 2000 microseconds now.
            *   // Main thread woke up.
            * @endcode
            */
            static void             usleep(unsigned int usec);

            /*! @brief Yields thread.
            *
            *  Yields execution of the current thread to another thread.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       t1->yield();
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            */
            static void             yield();

            /*! @brief Runs thread.
            *
            *  This function creates and runs the thread if it's state is "stateless" or "stopped".
            *  All thread's entry point is BlackThread::threadFunction() function. This entry point
            *  function runs the onStartHandler() function in users derived class, after some
            *  preparation processes.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa threadFunction()
            * @sa onStartHandler()
            */
            void                    run();

            /*! @brief Stops thread execution.
            *
            *  This function stops and exits the thread function. After users call this function,
            *  thread starts the BlackThread::cleanUp() function. This clean up function runs the
            *  onStopHandler() function in users derived class, after some final processes.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       if( t1->isRunning() )
            *       {
            *           t1->stop();
            *       }
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa cleanUp()
            * @sa onStopHandler()
            */
            void                    stop();

            /*! @brief Waits thread until it finished.
            *
            *  This function joins the thread if thread's state is "running" or "paused". This means
            *  the program will wait here until the thread function (in other words @a onStartHandler
            *  function) finishes. This function should use before the last line of main code (before
            *  "return 0;" line at the main.cpp). Users can use WAIT_THREAD_FINISH() macro also. It is
            *  the same thing. If users don't use this function or macro and the program comes to last
            *  line of main, the program will exit and thread will be interrupted. This cause some fatal
            *  things.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       if( t1->isRunning() )
            *       {
            *           t1->stop();
            *       }
            *
            *       WAIT_THREAD_FINISH(t1)
            *       t2->waitUntilFinish();
            *
            *       return 0;
            *  }
            * @endcode
            */
            void                    waitUntilFinish();

            /*! @brief Exports thread's run state.
            *
            *  @return true if thread's state is "running" or "paused" else false.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       if( t1->isRunning() )
            *       {
            *           t1->stop();
            *       }
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            */
            bool                    isRunning();

            /*! @brief Exports thread's finish state.
            *
            *  @return true if thread's state is "stopped" else false.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       if( t1->isFinished() )
            *       {
            *           t1->run();
            *       }
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            */
            bool                    isFinished();

            /*! @brief Pauses thread execution.
            *
            *  Actually this function calls onPauseHandler() and then calls onResumeHandler() function
            *  only. Users should define the behaviour of thread when this function called(thread paused),
            *  by overloading onPauseHandler() and onResumeHandler() function on theirs own derived class.
            *  If users did not overload this/these function(s) on derived class, this function does nothing.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *
            *               this->pause();
            *
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onPauseHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onResumeHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa onPauseHandler()
            * @sa onResumeHandler()
            */
            void                    pause();



        private:

            bool                    isCreated;                  /*!< @brief is used to hold the thread is created or not */
            pthread_t               nativeThread;               /*!< @brief is used to hold the thread's posix id */
            BlackThread::state      threadState;                /*!< @brief is used to hold the thread state */
            BlackThread::priority   threadPriority;             /*!< @brief is used to hold the thread priority */
            std::vector<int>        priorities;                 /*!< @brief is used to hold the OS based calculated priority values */


            /*! @brief Thread's stop handler function.
            *
            *  This function should overload at user's derived class. This function calls from
            *  cleanUp() function. Users should not call this function directly.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa cleanUp()
            * @sa stop()
            */
            virtual void            onStopHandler();

            /*! @brief Thread's pause handler function.
            *
            *  This function should overload at user's derived class. This function calls from
            *  pause() function. Users should not call this function directly.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *
            *               this->pause();
            *
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onPauseHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onResumeHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa pause()
            */
            virtual void            onPauseHandler();

            /*! @brief Thread's resume handler function.
            *
            *  This function should overload at user's derived class. This function calls from
            *  pause() function. Users should not call this function directly.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *
            *               this->pause();
            *
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onPauseHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onResumeHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa pause()
            */
            virtual void            onResumeHandler();

            /*! @brief Thread's start handler function.
            *
            *  This function has to overload at user's derived class. This function calls from
            *  threadFunction() function and the threadFunction() calls from run() function. Users
            *  should not call this function directly.
            *
            * @par Example
            *  @code{.cpp}
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               // do something here
            *           }
            *
            *           void onStopHandler()
            *           {
            *               // do something here
            *           }
            *  };
            *
            *  int main()
            *  {
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            *
            * @sa threadFunction()
            * @sa run()
            */
            virtual void            onStartHandler() = 0;

            /*! @brief Sets thread's priority properties to posix type property holder.
            *
            *  This function calls from the run() function only. While the thread is creating,
            *  thread create function wants posix type property holder struct as parameter.
            *  This function is used for initializing this struct with given priorty. In run()
            *  function, thread will be created with this struct after initialized this struct.
            *
            *  Actually this function's mission is to do some background job and users should
            *  not call this function directly.
            *
            *  @return true if setting is successful else false.
            *
            * @sa run()
            */
            bool                    setAttribute(pthread_attr_t *attr, BlackThread::priority tp);

            /*! @brief Calculates OS depend priorty values.
            *
            *  This function's mission is to do some background job and users should
            *  not call this function directly.
            *
            * @sa priorities
            */
            void                    calculatePriorities();

            /*! @brief Thread's exit function.
            *
            *  This function calls onStopHandler() function when it called by posix thread's
            *  cleanup system.
            *
            *  This function's mission is to do some background job and users should not call
            *  this function directly.
            *
            * @sa onStopHandler()
            */
            static void             cleanUp(void *thread);

            /*! @brief Thread's main function.
            *
            *  This function is the main function of thread. The thread runs this function
            *  actually. It does some preparation operations like setting up the cleanup system.
            *  After that it runs onStartHandler() function and waits until it finished. Then the
            *  cleanup system is put into use.
            *
            *  This function's mission is to do some background job and users should not call
            *  this function directly.
            *
            * @sa onStartHandler()
            */
            static void*            threadFunction(void *thread);

    };

    // ############################################ BLACKTHREAD DECLARATION ENDS ############################################# //

} /* namespace BlackLib */

#endif /* BLACKTHREAD_H_ */
