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

#ifndef EXAMPLE_TIME_H_
#define EXAMPLE_TIME_H_

#include "../BlackTime/BlackTime.h"
#include <string>
#include <iostream>






void example_time()
{
    BlackLib::BlackTime *myTime = new BlackLib::BlackTime(10,20,30);

    std::cout << "Hour  : " << myTime->getHour()   << std::endl
              << "Minute: " << myTime->getMinute() << std::endl
              << "Second: " << myTime->getSecond() << std::endl;

    std::cout << myTime->toString("'Formatted myTime: ' hh:mm:ss") << std::endl;


    myTime->setTime(16,41,34);
    std::cout << myTime->toString("'Formatted myTime: ' hh:mm:ss") << std::endl << std::endl;



    myTime->addHour(5);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl;

    myTime->addHour(-28);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl;

    myTime->addHour(17);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl << std::endl;





    myTime->setTime(16,41,34);



    myTime->addMinute(5);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl;

    myTime->addMinute(-65);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl;

    myTime->addMinute(20);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl << std::endl;





    myTime->setTime(16,41,34);




    myTime->addSecond(5);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl;

    myTime->addSecond( -1*(1*3600 + 10*60 + 9) );
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl;

    myTime->addSecond(50);
    std::cout << myTime->toString("'Formatted time: 'hh:mm:ss") << std::endl << std::endl;





    myTime->setTime(16,41,34);



    std::cout << myTime->toString("'Formatted time : 'h:m:s") << std::endl;

    std::cout << myTime->toString("'12-hours system: 'hh-mm/ss ap") << std::endl;

    std::cout << myTime->toString("hh 'hours,' mm 'minutes, 'ss' seconds elapsed.\n'");






    std::cout << "Current time: " << myTime->getCurrentTime().toString("hh.mm.ss") << std::endl;






    std::cout << "Example elapsed time in BlackTime: "
              << BlackLib::BlackTime::fromSecondToTime(37230).toString("hh 'hours, 'mm 'minutes, 'ss 'seconds.\n'");

    std::cout << "Example elapsed time in seconds: "
              << BlackLib::BlackTime::fromTimeToSecond(*myTime);





    BlackLib::BlackTime myTime1(10,20,30);
    BlackLib::BlackTime myTime2(3,6,9);

    std::cout << "\nDifference1: "
            << (myTime1-myTime2).toString("hh 'hours, 'mm 'minutes, 'ss 'seconds.'");
    std::cout << "\nDifference2: "
            << (myTime2-myTime1).toString("hh 'hours, 'mm 'minutes, 'ss 'seconds.'");




    BlackLib::BlackTime tm;
    tm.start();

    for( int i = 0 ; i <5000 ; i++ )
    {
        usleep(100);
    }


    BlackLib::BlackTimeElapsed et = tm.restart();

    std::cout << "\nelapsed hour   :" << et.hour        << std::endl
              << "elapsed minute :" << et.minute      << std::endl
              << "elapsed second :" << et.second      << std::endl
              << "elapsed msecond:" << et.miliSecond  << std::endl
              << "elapsed usecond:" << et.microSecond << std::endl << std::endl;


    for( int i = 0 ; i <1000 ; i++ )
    {
        usleep(100);
    }

    et = tm.elapsed();

    std::cout << "elapsed hour   :" << et.hour        << std::endl
              << "elapsed minute :" << et.minute      << std::endl
              << "elapsed second :" << et.second      << std::endl
              << "elapsed msecond:" << et.miliSecond  << std::endl
              << "elapsed usecond:" << et.microSecond << std::endl;



}



#endif /* EXAMPLE_TIME_H_ */
