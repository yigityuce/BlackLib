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





#ifndef EXAMPLE_GPIO_H_
#define EXAMPLE_GPIO_H_




#include "../BlackGPIO/BlackGPIO.h"
#include <string>
#include <iostream>




void example_GPIO()
{

    BlackLib::BlackGPIO   led1(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);   // initialization first output, secure mode

    BlackLib::BlackGPIO   led2(BlackLib::GPIO_22,BlackLib::output, BlackLib::FastMode);     // initialization second output, fast mode
    BlackLib::BlackGPIO   button1(BlackLib::GPIO_60,BlackLib::input);                       // initialization first input, secure mode
    BlackLib::BlackGPIO   button2(BlackLib::GPIO_48,BlackLib::input, BlackLib::FastMode);   // initialization second input, fast mode



    led1.setValue(BlackLib::high);          // turn on the led1

    led2.setValue(BlackLib::high);




    std::string button1value;
    std::string button2value;
    std::string led1value;
    std::string led2value;


    button1value    = button1.getValue();

    button2value    = button2.getValue();



    led1value       = led1.getValue();

    led2value       = led2.getValue();

    sleep(1);




    led1.toggleValue();

    led2.toggleValue();

    sleep(1);





    std::string led1value_operator;
    int         led1NumericValue_operator;

    led1 >> led1value_operator;

    led1 << BlackLib::high;

    led1 >> led1NumericValue_operator;





    std::string led2value_operator;
    int         led2NumericValue_operator;

    led2 >> led2value_operator;

    led2 << BlackLib::high;

    led2 >> led2NumericValue_operator;

    sleep(1);

}



#endif /* EXAMPLE_GPIO_H_ */
