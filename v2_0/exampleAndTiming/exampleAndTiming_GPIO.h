 /*

 ####################################################################################
 #  BlackLib Library controls Beaglebone Black's inputs and outputs.                #
 #  Copyright (C) 2013-2014 by Yigit YUCE                                           #
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





#ifndef EXAMPLEANDTIMING_GPIO_H_
#define EXAMPLEANDTIMING_GPIO_H_




#include "../BlackGPIO.h"
#include <string>
#include <iostream>
#include "Timing.h"




void exampleAndTiming_GPIO()
{
    Timing gpioTiming;

    gpioTiming.startMeasure("1. Constructor");
    BlackLib::BlackGPIO   led1(BlackLib::GPIO_51,BlackLib::output, BlackLib::SecureMode);   // initialization first output, secure mode
    gpioTiming.endMeasure("1. Constructor");

    BlackLib::BlackGPIO   led2(BlackLib::GPIO_22,BlackLib::output, BlackLib::FastMode);     // initialization second output, fast mode
    BlackLib::BlackGPIO   button1(BlackLib::GPIO_60,BlackLib::input);                       // initialization first input, secure mode
    BlackLib::BlackGPIO   button2(BlackLib::GPIO_48,BlackLib::input, BlackLib::FastMode);   // initialization second input, fast mode



    gpioTiming.startMeasure("2.1. (SecureMode) BlackGPIO::setValue()");
    led1.setValue(BlackLib::high);          // turn on the led1
    gpioTiming.endMeasure("2.1. (SecureMode) BlackGPIO::setValue()");

    gpioTiming.startMeasure("2.2. (FastMode) BlackGPIO::setValue()");
    led2.setValue(BlackLib::high);
    gpioTiming.endMeasure("2.2. (FastMode) BlackGPIO::setValue()");




    std::string button1value;
    std::string button2value;
    std::string led1value;
    std::string led2value;


    gpioTiming.startMeasure("3.1. (SecureMode,InputType) BlackGPIO::getValue()");
    button1value    = button1.getValue();
    gpioTiming.endMeasure("3.1. (SecureMode,InputType) BlackGPIO::getValue()");

    gpioTiming.startMeasure("3.2. (FastMode,InputType) BlackGPIO::getValue()");
    button2value    = button2.getValue();
    gpioTiming.endMeasure("3.2. (FastMode,InputType) BlackGPIO::getValue()");



    gpioTiming.startMeasure("3.3. (SecureMode,OutputType) BlackGPIO::getValue()");
    led1value       = led1.getValue();
    gpioTiming.endMeasure("3.3. (SecureMode,OutputType) BlackGPIO::getValue()");

    gpioTiming.startMeasure("3.4. (FastMode,OutputType) BlackGPIO::getValue()");
    led2value       = led2.getValue();
    gpioTiming.endMeasure("3.4. (FastMode,OutputType) BlackGPIO::getValue()");

    sleep(1);




    gpioTiming.startMeasure("4.1. BlackGPIO::toggleValue() (SecureMode)");
    led1.toggleValue();
    gpioTiming.endMeasure("4.1. BlackGPIO::toggleValue() (SecureMode)");

    gpioTiming.startMeasure("4.2. BlackGPIO::toggleValue() (FastMode)");
    led2.toggleValue();
    gpioTiming.endMeasure("4.2. BlackGPIO::toggleValue() (FastMode)");

    sleep(1);





    std::string led1value_operator;
    int         led1NumericValue_operator;

    gpioTiming.startMeasure("5.1. (SecureMode) BlackGPIO::operator>>(std::string)");
    led1 >> led1value_operator;
    gpioTiming.endMeasure("5.1. (SecureMode) BlackGPIO::operator>>(std::string)");

    gpioTiming.startMeasure("7.1. (SecureMode) BlackGPIO::operator<<()");
    led1 << BlackLib::high;
    gpioTiming.endMeasure("7.1. (SecureMode) BlackGPIO::operator<<()");

    gpioTiming.startMeasure("6.1. (SecureMode) BlackGPIO::operator>>(int)");
    led1 >> led1NumericValue_operator;
    gpioTiming.endMeasure("6.1. (SecureMode) BlackGPIO::operator>>(int)");





    std::string led2value_operator;
    int         led2NumericValue_operator;

    gpioTiming.startMeasure("5.2. (FastMode) BlackGPIO::operator>>(std::string)");
    led2 >> led2value_operator;
    gpioTiming.endMeasure("5.2. (FastMode) BlackGPIO::operator>>(std::string)");

    gpioTiming.startMeasure("7.2. (FastMode) BlackGPIO::operator<<()");
    led2 << BlackLib::high;
    gpioTiming.endMeasure("7.2. (FastMode) BlackGPIO::operator<<()");

    gpioTiming.startMeasure("6.2. (FastMode) BlackGPIO::operator>>(int)");
    led2 >> led2NumericValue_operator;
    gpioTiming.endMeasure("6.2. (FastMode) BlackGPIO::operator>>(int)");

    sleep(1);




    std::cout << gpioTiming.getAllMeasureTable();
    gpioTiming.saveToFile("BlackGPIO_timing_results.out");
}



#endif /* EXAMPLEANDTIMING_GPIO_H_ */
