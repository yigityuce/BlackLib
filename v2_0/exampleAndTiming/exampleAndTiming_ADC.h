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





#ifndef EXAMPLEANDTIMING_ADC_H_
#define EXAMPLEANDTIMING_ADC_H_


#include "../BlackADC.h"
#include <string>
#include <iostream>
#include "Timing.h"






void exampleAndTiming_ADC()
{
    Timing adcTiming;

    adcTiming.startMeasure("1. Constructor");
    BlackLib::BlackADC analog(BlackLib::AIN4 );         // initialization analog input
    adcTiming.endMeasure("1. Constructor");


    std::string valueStr;
    int         valueInt;
    float       valueFloat;


    adcTiming.startMeasure("2. BlackADC::getValue()");
    valueStr = analog.getValue();
    adcTiming.endMeasure("2. BlackADC::getValue()");


    usleep(1000);


    adcTiming.startMeasure("3. BlackADC::getNumericValue()");
    valueInt = analog.getNumericValue();
    adcTiming.endMeasure("3. BlackADC::getNumericValue()");


    usleep(1000);


    adcTiming.startMeasure("4. BlackADC::getConvertedValue()");
    valueFloat = analog.getConvertedValue( BlackLib::dap2 );
    adcTiming.endMeasure("4. BlackADC::getConvertedValue()");

    std::cout << "AIN_str: " << valueStr << std::endl;
    std::cout << "AIN_int: " << valueInt << std::endl;
    std::cout << "AIN_flt: " << valueFloat << std::endl;






    valueStr.clear();
    valueInt    = 0;
    valueFloat  = 0.0;

    adcTiming.startMeasure("5. BlackADC::operator>>(std::string)");
    analog >> valueStr;
    adcTiming.endMeasure("5. BlackADC::operator>>(std::string)");


    usleep(1000);


    adcTiming.startMeasure("6. BlackADC::operator>>(int)");
    analog >> valueInt;
    adcTiming.endMeasure("6. BlackADC::operator>>(int)");


    usleep(1000);


    adcTiming.startMeasure("7. BlackADC::operator>>(float)");
    analog >> valueFloat;
    adcTiming.endMeasure("7. BlackADC::operator>>(float)");

    std::cout << "AIN_str_operator: " << valueStr << std::endl;
    std::cout << "AIN_int_operator: " << valueInt << std::endl;
    std::cout << "AIN_flt_operator: " << valueFloat << std::endl;


    std::cout << adcTiming.getAllMeasureTable();
    adcTiming.saveToFile("BlackADC_timing_results.out");

}



#endif /* EXAMPLEANDTIMING_ADC_H_ */
