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



#ifndef BLACKMUTEX_H_
#define BLACKMUTEX_H_

#include <pthread.h>

namespace BlackLib
{

    // ########################################### BLACKMUTEX DECLARATION STARTS ############################################ //

    /*! @brief Prevents accessing the same memory location at the same time from different threads.
    *
    *    The mutex is generally used for thread synchronization. It prevents collisions and crashes and protects
    *    any objects,variables and part of your codes. It provides this with allowing to access a memory location
    *    to one thread at a time.
    *
    *    @warning
    *    This class supports recursive mutex lock also. A thread can lock mutex more than once. If the unlock()
    *    function isn't called lock count times, the mutex won't unlocked.
    *
    * @par Example
    @verbatim
    EXAMPLE PROJECT FILE TREE:

        myMutexProject
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
            |-> myMutexProject.cpp
    @endverbatim
    *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
    *  include BlackMutex.h or another source files with adding this line to your project file (myMutexProject.cpp at
    *  the example):
    *  @code{.cpp}
    *      #include "BlackLib/BlackMutex/BlackMutex.h"
    *  @endcode
    *  @n@n If BlackLib source files are located at same level with your project file (myMutexProject.cpp at the
    *  example), you have to include BlackMutex.h or another source files with adding this line to your project file:
    *  @code{.cpp}
    *      #include "BlackMutex/BlackMutex.h"
    *  @endcode
    *  @n @n
    *  @code{.cpp}
    *  // Filename: myMutexProject.cpp
    *  // Author:   Yiğit Yüce - ygtyce@gmail.com
    *
    *  #include <iostream>
    *  #include "BlackLib/BlackThread/BlackThread.h"
    *  #include "BlackLib/BlackMutex/BlackMutex.h"
    *
    *  int number;
    *  BlackLib::BlackMutex *myMutex;
    *
    *  class Task1 : public BlackLib::BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               myMutex->lock();
    *               std::cout << "Task1 doing the following operations: \n";
    *               std::cout << "Global variable(number)\'s current value: \n";
    *               for( int i = 0 ; i < 10 ; i++)
    *               {
    *                   std::cout << ++number << " ";
    *               }
    *               std::cout << std::endl;
    *               myMutex->unlock();
    *           }
    *  };
    *
    *  class Task2 : public BlackLib::BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               myMutex->lock();
    *               std::cout << "Task2 doing the following operations: \n";
    *               std::cout << "Global variable(number)\'s current value: \n";
    *               for( int i = 0 ; i < 15 ; i++)
    *               {
    *                   std::cout << --number << " ";
    *               }
    *               std::cout << std::endl;
    *               myMutex->unlock();
    *           }
    *  };
    *
    *
    *  int main()
    *  {
    *       myMutex = new BlackLib::BlackMutex();
    *       number  = 0;
    *
    *       Task1 *t1 = new Task1();
    *       Task2 *t2 = new Task2();
    *
    *       t1->run();
    *       t2->run();
    *
    *
    *       WAIT_THREAD_FINISH(t1)
    *       WAIT_THREAD_FINISH(t2)
    *
    *       return 0;
    *  }
    * @endcode
    * @code{.cpp}
    *   // Possible Output:
    *   // Task1 doing the following operations:
    *   // Global variable(number)'s current value: 1 2 3 4 5 6 7 8 9 10
    *   // Task2 doing the following operations:
    *   // Global variable(number)'s current value: 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
    * @endcode
    * @n @n
    * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
    * @code{.cpp}
    *  // Filename: myMutexProject.cpp
    *  // Author:   Yiğit Yüce - ygtyce@gmail.com
    *
    *  #include <iostream>
    *  #include "BlackLib/BlackThread/BlackThread.h"
    *  #include "BlackLib/BlackMutex/BlackMutex.h"
    *  using namespace BlackLib;
    *
    *  int number;
    *  BlackMutex *myMutex;
    *
    *  class Task1 : public BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               myMutex->lock();
    *               std::cout << "Task1 doing the following operations: \n";
    *               std::cout << "Global variable(number)\'s current value: \n";
    *               for( int i = 0 ; i < 10 ; i++)
    *               {
    *                   std::cout << ++number << " ";
    *               }
    *               std::cout << std::endl;
    *               myMutex->unlock();
    *           }
    *  };
    *
    *  class Task2 : public BlackThread
    *  {
    *       public:
    *           void onStartHandler()
    *           {
    *               myMutex->lock();
    *               std::cout << "Task2 doing the following operations: \n";
    *               std::cout << "Global variable(number)\'s current value: \n";
    *               for( int i = 0 ; i < 15 ; i++)
    *               {
    *                   std::cout << --number << " ";
    *               }
    *               std::cout << std::endl;
    *               myMutex->unlock();
    *           }
    *  };
    *
    *
    *  int main()
    *  {
    *       myMutex = new BlackMutex();
    *       number  = 0;
    *
    *       Task1 *t1 = new Task1();
    *       Task2 *t2 = new Task2();
    *
    *       t1->run();
    *       t2->run();
    *
    *
    *       WAIT_THREAD_FINISH(t1)
    *       WAIT_THREAD_FINISH(t2)
    *
    *       return 0;
    *  }
    * @endcode
    * @code{.cpp}
    *   // Possible Output:
    *   // Task1 doing the following operations:
    *   // Global variable(number)'s current value: 1 2 3 4 5 6 7 8 9 10
    *   // Task2 doing the following operations:
    *   // Global variable(number)'s current value: 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
    * @endcode
    */
    class BlackMutex
    {
        public:

            /*!
            * This enum is used to define mutex recursive mode.
            */
            enum mutexMode
            {
                NonRecursive    = 0,            /*!< enumeration for @a non-recursive type mutex */
                Recursive       = 1             /*!< enumeration for @a recursive type mutex */
            };

            /*! @brief Constructor of BlackMutex class.
            *
            * This function initializes mutex.
            *
            * @par Example
            *  @code{.cpp}
            *  ...
            *  ...
            *
            *  thread definitions, global variables etc.
            *  ...
            *  ...
            *  ...
            *
            *  int main()
            *  {
            *       // default is non-recursive mode
            *       BlackLib::BlackMutex myMutex();
            *
            *       BlackLib::BlackMutex *myMutexPtr = new BlackLib::BlackMutex(BlackLib::BlackMutex::Recursive);
            *
            *       ...
            *       ...
            *       ...
            *
            *       thread operations
            *
            *       ...
            *       ...
            *
            *       return 0;
            *  }
            * @endcode
            *
            */
            BlackMutex(BlackMutex::mutexMode mm = BlackMutex::NonRecursive);

            /*! @brief Destructor of BlackMutex class.
            *
            */
            virtual ~BlackMutex();

            /*! @brief Locks the mutex.
            *
            * This function locks the mutex. If mutex is locked before it waits until mutex is unlocked.
            *
            * @return true if mutex lock is success else false.
            *
            * @warning This function waits until the mutex locked so it blocks the thread until mutex lock is successful.
            * @par Example
            *  @code{.cpp}
            *  ...
            *  ...
            *
            *  int number;
            *  BlackLib::BlackMutex *myMutex;
            *
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *               std::cout << "Task1 doing the following operations: \n";
            *               std::cout << "Global variable(number)\'s current value: \n";
            *               for( int i = 0 ; i < 10 ; i++)
            *               {
            *                   std::cout << ++number << " ";
            *               }
            *               std::cout << std::endl;
            *               myMutex->unlock();
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *               std::cout << "Task2 doing the following operations: \n";
            *               std::cout << "Global variable(number)\'s current value: \n";
            *               for( int i = 0 ; i < 15 ; i++)
            *               {
            *                   std::cout << --number << " ";
            *               }
            *               std::cout << std::endl;
            *               myMutex->unlock();
            *           }
            *  };
            *  ...
            *  ...
            *  ...
            *
            *  int main()
            *  {
            *       myMutex = new BlackLib::BlackMutex();
            *       number  = 0;
            *
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Task1 doing the following operations:
            *   // Global variable(number)'s current value: 1 2 3 4 5 6 7 8 9 10
            *   // Task2 doing the following operations:
            *   // Global variable(number)'s current value: 9 8 7 6 5 4 3 2 1 0 -1 -2 -3 -4 -5
            * @endcode
            */
            bool lock();

            /*! @brief Tries lock the mutex.
            *
            * This function tries lock the mutex. This function does not wait until lock the mutex. If mutex is already
            * locked, this function returns immediatly with false value.
            *
            * @return true if mutex lock is success else false.
            *
            * @par Example
            *  @code{.cpp}
            *  ...
            *  ...
            *
            *  int number;
            *  BlackLib::BlackMutex *myMutex;
            *
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *               std::cout << "Task1 doing the following operations: \n";
            *               std::cout << "Global variable(number)\'s current value: \n";
            *               for( int i = 0 ; i < 10 ; i++)
            *               {
            *                   std::cout << ++number << " ";
            *               }
            *               std::cout << std::endl;
            *               myMutex->unlock();
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               if( myMutex->tryLock() )
            *               {
            *                   std::cout << "Task2 doing the following operations: \n";
            *                   std::cout << "Global variable(number)\'s current value: \n";
            *                   for( int i = 0 ; i < 15 ; i++)
            *                   {
            *                       std::cout << --number << " ";
            *                   }
            *                      std::cout << std::endl;
            *                   myMutex->unlock();
            *               }
            *               else
            *               {
            *                   std::cout << "Task2 couldn\'t lock the mutex. ";
            *               }
            *           }
            *  };
            *  ...
            *  ...
            *  ...
            *
            *  int main()
            *  {
            *       myMutex = new BlackLib::BlackMutex();
            *       number  = 0;
            *
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Task1 doing the following operations:
            *   // Global variable(number)'s current value: 1 2 3 4 5 6 Task2 couldn't lock the mutex. 7 8 9 10
            * @endcode
            */
            bool tryLock();

            /*! @brief Locks the mutex until the time expires.
            *
            * This function tries lock the mutex. If mutex is already locked, this function waits mutex to be unlocked
            * and tries to lock until the time expires. If time is expired and the mutex still can't be lockable, the
            * function returns false.
            *
            * @param [in] sec    time in seconds
            *
            * @return true if mutex lock is success until the time expires else false.
            *
            * @par Example
            *  @code{.cpp}
            *  ...
            *  ...
            *
            *  int number;
            *  BlackLib::BlackMutex *myMutex;
            *
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *               std::cout << "Task1 doing the following operations: \n";
            *               std::cout << "Global variable(number)\'s current value: \n";
            *               for( int i = 0 ; i < 10 ; i++)
            *               {
            *                   std::cout << ++number << " ";
            *               }
            *               std::cout << std::endl;
            *
            *               BlackLib::BlackThread::sleep(10);
            *
            *               myMutex->unlock();
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               if( myMutex->timedLock(5) )
            *               {
            *                   std::cout << "Task2 doing the following operations: \n";
            *                   std::cout << "Global variable(number)\'s current value: \n";
            *                   for( int i = 0 ; i < 15 ; i++)
            *                   {
            *                       std::cout << --number << " ";
            *                   }
            *                      std::cout << std::endl;
            *                   myMutex->unlock();
            *               }
            *               else
            *               {
            *                   std::cout << "Task2 couldn\'t lock the mutex. ";
            *               }
            *           }
            *  };
            *  ...
            *  ...
            *  ...
            *
            *  int main()
            *  {
            *       myMutex = new BlackLib::BlackMutex();
            *       number  = 0;
            *
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Task1 doing the following operations:
            *   // Global variable(number)'s current value: 1 2 3 4 5 6 7 8 9 10
            *   // Task2 couldn't lock the mutex.
            * @endcode
            */
            bool timedLock(unsigned int sec);

            /*! @brief Unlocks the mutex.
            *
            * This function unlocks the mutex. If mutex is already unlocked it does nothing.
            *
            * @return true if mutex unlock is success else false.
            *
            * @warning This function waits until the mutex unlocked so it blocks the thread until mutex unlock is successful.
            * @par Example
            * Example usage is shown in BlackMutex::lock() and BlackMutex::tryLock() functions' example.
            */
            bool unlock();

            /*! @brief Checks the mutex lock state.
            *
            * This function checks the lock status of mutex.
            *
            * @return true if mutex is locked else false.
            *
            * @par Example
            *  @code{.cpp}
            *  ...
            *  ...
            *
            *  int number;
            *  BlackLib::BlackMutex *myMutex;
            *
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *               for( int i = 0 ; i < 10 ; i++)
            *               {
            *                   BlackLib::BlackThread::sleep(1);
            *               }
            *
            *               myMutex->unlock();
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *
            *               for( int i = 0 ; i < 15 ; i++)
            *               {
            *                   BlackLib::BlackThread::sleep(1);
            *               }
            *
            *               myMutex->unlock();
            *           }
            *  };
            *  ...
            *  ...
            *  ...
            *
            *  int main()
            *  {
            *       myMutex = new BlackLib::BlackMutex();
            *       number  = 0;
            *
            *       Task1 *t1 = new Task1();
            *       Task2 *t2 = new Task2();
            *
            *       t1->run();
            *       t2->run();
            *
            *       std::cout << "Mutex is locked? : " << std::boolalpha << myMutex->isLocked() << std::endl;
            *       BlackLib::BlackThread::sleep(30);
            *       std::cout << "Mutex is locked? : " << std::boolalpha << myMutex->isLocked() << std::endl;
            *
            *       WAIT_THREAD_FINISH(t1)
            *       WAIT_THREAD_FINISH(t2)
            *
            *       return 0;
            *  }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Mutex is locked? : true
            *   // Mutex is locked? : false
            * @endcode
            */
            bool isLocked();

            /*! @brief Checks the mutex recursiveness.
            *
            * @par Example
            *  @code{.cpp}
            *  ...
            *  ...
            *
            *  thread definitions, global variables etc.
            *  ...
            *  ...
            *  ...
            *
            *  int main()
            *  {
            *       // default is non-recursive mode
            *       BlackLib::BlackMutex myMutex();
            *
            *       BlackLib::BlackMutex *myMutexPtr = new BlackLib::BlackMutex(BlackLib::BlackMutex::Recursive);
            *
            *       ...
            *       ...
            *       ...
            *
            *       thread operations
            *
            *       std::cout << "myMutex is recursive?    : " << std::boolalpha << myMutex.isRecursive() << std::endl;
            *       std::cout << "myMutexPtr is recursive? : " << std::boolalpha << myMutexPtr->isRecursive() << std::endl;
            *
            *       ...
            *       ...
            *
            *       return 0;
            *  }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // myMutex is recursive?    : false
            *   // myMutexPtr is recursive? : true
            * @endcode
            *
            */
            bool isRecursive();

            /*! @brief Exports the mutex lock count.
            *
            * @return number of lock count of mutex.
            *
            * @par Example
            *  @code{.cpp}
            *  ...
            *  ...
            *
            *  int number;
            *  BlackLib::BlackMutex *myMutex;
            *
            *  class Task1 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *               for( int i = 0 ; i < 10 ; i++)
            *               {
            *                   BlackLib::BlackThread::sleep(1);
            *               }
            *
            *               myMutex->unlock();
            *           }
            *  };
            *
            *  class Task2 : public BlackLib::BlackThread
            *  {
            *       public:
            *           void onStartHandler()
            *           {
            *               myMutex->lock();
            *
            *               if( myMutex->isRecursive() )
            *               {
            *                   for( int i=0 ; i<14 ; i++)
            *                   {
            *                       myMutex->lock();
            *                   }
            *               }
            *
            *               std::cout << "Mutex locked " << myMutex->getLockedCount() << " times.\n";
            *
            *               for( int i = 0 ; i < 15 ; i++)
            *               {
            *                   BlackLib::BlackThread::sleep(1);
            *               }
            *

            *               for( unsigned int i=0 ; i<myMutex->getLockedCount() ; i++)
            *               {
            *                   myMutex->unlock();
            *               }

            *           }
            *  };
            *  ...
            *  ...
            *  ...
            *
            *  int main()
            *  {
            *       myMutex = new BlackLib::BlackMutex(BlackLib::BlackMutex::Recursive);
            *       number  = 0;
            *
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
            * @code{.cpp}
            *   // Possible Output:
            *   // Mutex locked 15 times.
            * @endcode
            */
            unsigned int getLockedCount();

        private:
            pthread_mutex_t mutex;               /*!< @brief is used to hold the mutex posix data structure */
            unsigned int    lockCount;           /*!< @brief is used to hold the mutex lock count */
            mutexMode       mode;                /*!< @brief is used to hold the mutex mode property */
    };

    // ############################################ BLACKMUTEX DECLARATION ENDS ############################################# //


} /* namespace BlackLib */

#endif /* BLACKMUTEX_H_ */
