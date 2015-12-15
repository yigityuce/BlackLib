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





#ifndef EXAMPLE_ADC_H_
#define EXAMPLE_ADC_H_


#include "../BlackADC/BlackADC.h"
#include <string>
#include <iostream>






void example_ADC()
{

    BlackLib::BlackADC analog(BlackLib::AIN4 );         // initialization analog input


    std::string valueStr;
    int         valueInt;
    float       valueFloat;


    valueStr = analog.getValue();


    usleep(1000);


    valueInt = analog.getNumericValue();


    usleep(1000);


    valueFloat = analog.getConvertedValue( BlackLib::dap2 );

    std::cout << "AIN_str: " << valueStr << std::endl;
    std::cout << "AIN_int: " << valueInt << std::endl;
    std::cout << "AIN_flt: " << valueFloat << std::endl;






    valueStr.clear();
    valueInt    = 0;
    valueFloat  = 0.0;

    analog >> valueStr;


    usleep(1000);


    analog >> valueInt;


    usleep(1000);


    analog >> valueFloat;

    std::cout << "AIN_str_operator: " << valueStr << std::endl;
    std::cout << "AIN_int_operator: " << valueInt << std::endl;
    std::cout << "AIN_flt_operator: " << valueFloat << std::endl;

}



#endif /* EXAMPLE_ADC_H_ */
