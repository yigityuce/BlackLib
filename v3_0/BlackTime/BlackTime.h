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



#ifndef BLACKTIME_H_
#define BLACKTIME_H_

#include <ctime>
#include <string>
#include <cmath>
#include <sys/time.h>


namespace BlackLib
{

    // ######################################### BLACKTIMEELAPSED DECLARATION STARTS ######################################### //

    /*! @brief Holds elapsed time properties.
    *
    *    This struct holds hour, minute, second, milisecond and microsecond properties of elapsed time.
    */
    struct BlackTimeElapsed
    {
        /*! @brief Default constructor of BlackTimeElapsed struct.
         *
         *  This function sets default value to variables.
         */
        BlackTimeElapsed()
        {
            hour        = 0;
            minute      = 0;
            second      = 0;
            miliSecond  = 0;
            microSecond = 0;
        }

        unsigned int hour;             /*!< @brief is used to hold the elapsed hour */
        unsigned int minute;           /*!< @brief is used to hold the elapsed minute */
        unsigned int second;           /*!< @brief is used to hold the elapsed second */
        unsigned int miliSecond;       /*!< @brief is used to hold the elapsed milisecond */
        unsigned int microSecond;      /*!< @brief is used to hold the elapsed microsecond */
    };

    // ########################################## BLACKTIMEELAPSED DECLARATION ENDS ########################################## //





    // ########################################### BLACKTIME DECLARATION STARTS ############################################ //

    /*! @brief Interacts with end user, to do basic time operations.
     *
     *    This class is end node to do basic time operations, to get current time and to measure the elapsed time.
     *
     * @par Example
      @verbatim
      EXAMPLE PROJECT FILE TREE:

         myTimeProject
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
             |-> myTimeProject.cpp
      @endverbatim
     *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
     *  include BlackTime.h or another source files with adding this line to your project file (myTimeProject.cpp at
     *  the example):
     *  @code{.cpp}
     *      #include "BlackLib/BlackTime/BlackTime.h"
     *  @endcode
     *  @n@n If BlackLib source files are located at same level with your project file (myTimeProject.cpp at the
     *  example), you have to include BlackTime.h or another source files with adding this line to your project file:
     *  @code{.cpp}
     *      #include "BlackTime/BlackTime.h"
     *  @endcode
     *  @n @n
     *  @code{.cpp}
     *  // Filename: myTimeProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackTime/BlackTime.h"
     *
     *  int main()
     *  {
     *      BlackLib::BlackTime myTime(16,41,34);
     *      std::cout << myTime.toString("'Formatted time: ' hh:mm:ss AP");
     *
     *      return 0;
     *  }
     * @endcode
     * @n @n
     * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
     * @code{.cpp}
     *  // Filename: myTimeProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackTime/BlackTime.h"
     *  using namespace BlackLib;
     *
     *  int main()
     *  {
     *      BlackTime myTime(16,41,34);
     *      std::cout << myTime.toString("'Formatted time: ' hh:mm:ss AP");
     *
     *      return 0;
     *  }
     * @endcode
     *
     */
    class BlackTime
    {
        public:

            /*! @brief Constructor of BlackTime class.
            *
            * This function initializes time values to 0.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *   BlackLib::BlackTime *myTimePtr = new BlackLib::BlackTime();
            *
            *   std::cout << myTime.getHour() << std::endl;
            *   std::cout << myTimePtr->getHour();
            * @endcode
            */
            BlackTime();

            /*! @brief Constructor of BlackTime class.
            *
            * @param [in] h    hour value
            * @param [in] m    minute value
            * @param [in] s    second value
            *
            * This function initializes time values to input parameters if they are valid.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime(16,41,34);
            *   BlackLib::BlackTime *myTimePtr = new BlackLib::BlackTime(16,41,34);
            *
            *   std::cout << myTime.getHour() << std::endl;
            *   std::cout << myTimePtr->getHour();
            * @endcode
            *
            * @sa BlackTime::isValid()
            */
            BlackTime(int h,int m,int s);

            /*! @brief Destructor of BlackTime class.
            *
            */
            virtual ~BlackTime();

            /*! @brief Exports hour value.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *   BlackLib::BlackTime *myTimePtr = new BlackLib::BlackTime(16,41,34);
            *
            *   std::cout << "myTime\'s hour value   : " << myTime.getHour() << std::endl;
            *   std::cout << "myTimePtr\'s hour value: " << myTimePtr->getHour();
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // myTime's hour value   : 0
            *   // myTimePtr's hour value: 16
            * @endcode
            */
            int  getHour();

            /*! @brief Exports minute value.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *   BlackLib::BlackTime *myTimePtr = new BlackLib::BlackTime(16,41,34);
            *
            *   std::cout << "myTime\'s minute value   : " << myTime.getMinute() << std::endl;
            *   std::cout << "myTimePtr\'s minute value: " << myTimePtr->getMinute();
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // myTime's minute value   : 0
            *   // myTimePtr's minute value: 41
            * @endcode
            */
            int  getMinute();

            /*! @brief Exports second value.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *   BlackLib::BlackTime *myTimePtr = new BlackLib::BlackTime(16,41,34);
            *
            *   std::cout << "myTime\'s second value   : " << myTime.getSecond() << std::endl;
            *   std::cout << "myTimePtr\'s second value: " << myTimePtr->getSecond();
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // myTime's second value   : 0
            *   // myTimePtr's second value: 34
            * @endcode
            */
            int  getSecond();

            /*! @brief Sets new time values if they are valid.
            *
            * @param [in] h    new hour value
            * @param [in] m    new minute value
            * @param [in] s    new second value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *   BlackLib::BlackTime *myTimePtr = new BlackLib::BlackTime(16,41,34);
            *
            *   myTime.setTime(12,34,56);
            *
            *   std::cout << myTime.toString("'Formatted myTime   : ' hh:mm:ss") << std::endl;
            *   std::cout << myTimePtr->toString("'Formatted myTimePtr: ' hh.mm.ss AP");
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Formatted myTime   : 12:34:56
            *   // Formatted myTimePtr: 04.41.34
            * @endcode
            */
            bool setTime(int h,int m,int s);

            /*! @brief Starts the time measurement.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *
            *   myTime.start();
            *
            *   // do some long operations
            *
            *       BlackLib::BlackTimeElapsed et = tm.restart();
            *       std::cout << "elapsed hour   :" << et.hour        << std::endl
            *                 << "elapsed minute :" << et.minute      << std::endl
            *                 << "elapsed second :" << et.second      << std::endl
            *                 << "elapsed msecond:" << et.miliSecond  << std::endl
            *                 << "elapsed usecond:" << et.microSecond << std::endl << std::endl;
            *
            *   // do some long operations again
            *
            *   // this measures elapsed time between the restart and current, not start and current.
            *       et = tm.elapsed();
            *       std::cout << "elapsed hour   :" << et.hour        << std::endl
            *                 << "elapsed minute :" << et.minute      << std::endl
            *                 << "elapsed second :" << et.second      << std::endl
            *                 << "elapsed msecond:" << et.miliSecond  << std::endl
            *                 << "elapsed usecond:" << et.microSecond << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // elapsed hour   :00
            *   // elapsed minute :5
            *   // elapsed second :43
            *   // elapsed msecond:56
            *   // elapsed usecond:29
            *
            *   // elapsed hour   :00
            *   // elapsed minute :12
            *   // elapsed second :6
            *   // elapsed msecond:37
            *   // elapsed usecond:28
            * @endcode
            */
            void start();

            /*! @brief Restarts the time measurement.
            *
            * @return the elapsed time between the current and start/restart function calls
            *
            * @par Example
            *  Example usage is shown in BlackTime::start() function's example.
            */
            BlackTimeElapsed restart();

            /*! @brief Exports the elapsed time.
            *
            * @return the elapsed time between the current and start/restart function calls
            *
            * @par Example
            *  Example usage is shown in BlackTime::start() function's example.
            */
            BlackTimeElapsed elapsed();

            /*! @brief Adds hours to current hour value.
            *
            * Users can add negative value also. If current hour is less than 0 or greater than 24 after
            * the add operation, it will convert the 24 hours time system.
            * @return the new time value.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime(16,41,34);
            *
            *   myTime.addHour(5);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            *
            *   myTime.addHour(-28);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            *
            *   myTime.addHour(17);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Formatted time: 21:41:34
            *   // Formatted time: 17:41:34
            *   // Formatted time: 10:41:34
            * @endcode
            */
            BlackTime& addHour(int h);

            /*! @brief Adds minutes to current minute value.
            *
            * Users can add negative value also. If current minute is less than 0 or greater than 60 after
            * the add operation, it will convert the 24 hours time system.
            * @return the new time value.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime(16,41,34);
            *
            *   myTime.addMinute(5);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            *
            *   myTime.addMinute(-65);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            *
            *   myTime.addMinute(20);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Formatted time: 16:46:34
            *   // Formatted time: 15:41:34
            *   // Formatted time: 16:01:34
            * @endcode
            */
            BlackTime& addMinute(int m);

            /*! @brief Adds seconds to current second value.
            *
            * Users can add negative value also. If current second is less than 0 or greater than 60 after
            * the add operation, it will convert the 24 hours time system.
            * @return the new time value.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime(16,41,34);
            *
            *   myTime.addSecond(5);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            *
            *   myTime.addSecond( -1*(1*3600 + 10*60 + 9) );
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            *
            *   myTime.addSecond(50);
            *   std::cout << myTime.toString("'Formatted time: 'hh:mm:ss") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Formatted time: 16:41:39
            *   // Formatted time: 15:31:30
            *   // Formatted time: 15:32:20
            * @endcode
            */
            BlackTime& addSecond(int s);

            /*! @brief Exports readable and formatted version of the time.
            *
            *    Formatted text rules:
            *
            *    Expression                   | Output
            *    ---------------------------- | -------------
            *    'plain text'                 | plain text
            *    single 'h' or 'H'            | hour without zero
            *    'hh' or 'HH' or 'hH' or 'Hh' | hour with zero
            *    single 'm' or 'M'            | minute without zero
            *    'mm' or 'MM' or 'mM' or 'HM' | minute with zero
            *    single 's' or 'S'            | second without zero
            *    'ss' or 'SS' or 'sS' or 'Ss' | second with zero
            *    seperator                    | allowed seperators are ':', '/', '.', '-' and ' '
            *    'ap' or 'AP'                 | prints "am" or "pm"
            *
            *
            * @return formatted time string.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime(16,5,34);
            *
            *   std::cout << myTime.toString("'Formatted time : 'h:m:s") << std::endl;
            *
            *   std::cout << myTime.toString("'12-hours system: 'hh-mm/ss ap") << std::endl;
            *
            *   std::cout << myTime.toString("hh 'hours,' mm 'minutes, 'ss' seconds elapsed.\n'");
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Formatted time : 16:5:34
            *   // 12-hours system: 04-05/34 pm
            *   // 16 hours, 05 minutes, 34 seconds elapsed.
            * @endcode
            */
            std::string toString(std::string format);



            /*! @brief Checks the validation of input parameters.
            *
            * Hour must be greater than 0 and less than 24,
            * minute must be greater than 0 and less than 60,
            * second must be greater than 0 and less than 60.
            *
            * @param [in] h    hour value
            * @param [in] m    minute value
            * @param [in] s    second value
            *
            * @return true if all values are valid else false.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *
            *   if( BlackLib::BlackTime::isValid(12,34,56) )
            *   {
            *       myTime.setTime(12,34,56);
            *   }
            *   else
            *   {
            *       myTime.setTime(0,0,0);
            *   }
            *
            *   std::cout << myTime.toString("'Formatted myTime: ' hh:mm:ss") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Formatted myTime: 12:34:56
            * @endcode
            */
            static bool      isValid(int h,int m,int s);

            /*! @brief Exports the current system time.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime  myTime();
            *
            *   std::cout << "Current time: " << myTime.getCurrentTime().toString("hh.mm.ss");
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current time: 15.30.56
            * @endcode
            */
            static BlackTime getCurrentTime();

            /*! @brief Converts seconds to %BlackTime.
            *
            * @param [in] s    second value
            *
            * @par Example
            *  @code{.cpp}
            *
            *   std::cout << "Example elapsed time in BlackTime: "
            *             << BlackLib::BlackTime::fromSecondToTime(37230).toString("hh 'hours, 'mm 'minutes, 'ss 'seconds.'");
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Example elapsed time in BlackTime: 10 hours, 20 minutes, 30 seconds.
            * @endcode
            */
            static BlackTime fromSecondToTime(long int s);

            /*! @brief Converts %BlackTime to seconds.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime(10,20,30);
            *
            *   std::cout << "Example elapsed time in seconds: "
            *             << BlackLib::BlackTime::fromTimeToSecond(myTime);
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Example elapsed time in seconds: 37230
            * @endcode
            */
            static long int  fromTimeToSecond(BlackTime t);

            /*! @brief Calculates difference of two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,9);
            *
            *   std::cout << "Difference1: "
            *             << (myTime1-myTime2).toString("hh 'hours, 'mm 'minutes, 'ss 'seconds.'") << std::endl;
            *
            *   std::cout << "Difference2: "
            *             << (myTime2-myTime1).toString("hh 'hours, 'mm 'minutes, 'ss 'seconds.'") << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Difference1: 07 hours, 14 minutes, 21 seconds.
            *   // Difference2: 16 hours, 45 minutes, 39 seconds.
            * @endcode
            */
            BlackTime  operator- (BlackTime t);

            /*! @brief Calculates sum of two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,39);
            *
            *   std::cout << "Sum: "
            *             << (myTime1+myTime2).toString("hh 'hours, 'mm 'minutes, 'ss 'seconds.'") << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Sum: 13 hours, 27 minutes, 09 seconds.
            * @endcode
            */
            BlackTime  operator+ (BlackTime t);

            /*! @brief Assigns one %BlackTime to other one.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2;
            *
            *   myTime2 = myTime1;
            *
            *   std::cout << "myTime2 = " << myTime2.toString("hh:mm:ss");
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // myTime2 = 10:20:30
            * @endcode
            */
            BlackTime& operator= (BlackTime t);

            /*! @brief Checks equality of two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,39);
            *
            *   std::cout << "is equal? : " << std::boolalpha << (myTime1 == myTime2);
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // is equal? : false
            * @endcode
            */
            bool       operator==(BlackTime t);

            /*! @brief Checks not equality of two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,39);
            *
            *   std::cout << "is not equal? : " << std::boolalpha << (myTime1 != myTime2);
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // is not equal? : true
            * @endcode
            */
            bool       operator!=(BlackTime t);

            /*! @brief Compares two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,39);
            *
            *   std::cout << "is lesser than myTime2? : " << std::boolalpha << (myTime1 < myTime2);
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // is lesser than myTime2? : false
            * @endcode
            */
            bool       operator< (BlackTime t);

            /*! @brief Compares two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,39);
            *
            *   std::cout << "is greater than myTime2? : " << std::boolalpha << (myTime1 > myTime2);
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // is greater than myTime2? : true
            * @endcode
            */
            bool       operator> (BlackTime t);

            /*! @brief Compares two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,39);
            *
            *   std::cout << "is lesser than or equal to myTime2? : " << std::boolalpha << (myTime1 <= myTime2);
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // is lesser than or equal to myTime2? : false
            * @endcode
            */
            bool       operator<=(BlackTime t);

            /*! @brief Compares two %BlackTime.
            *
            * @param [in] t    %BlackTime value
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackTime myTime1(10,20,30);
            *   BlackLib::BlackTime myTime2(3,6,39);
            *
            *   std::cout << "is greater than or equal to myTime2? : " << std::boolalpha << (myTime1 >= myTime2);
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // is greater than or equal to myTime2? : true
            * @endcode
            */
            bool       operator>=(BlackTime t);



        private:
            int hour;                    /*!< @brief is used to hold the hour value */
            int minute;                  /*!< @brief is used to hold the minute value */
            int second;                  /*!< @brief is used to hold the second value */
            timeval measureStartTime;    /*!< @brief is used to hold the start point for measuring elapsed time */
    };


    // ############################################ BLACKTIME DECLARATION ENDS ############################################# //



} /* namespace BlackLib */

#endif /* BLACKTIME_H_ */
