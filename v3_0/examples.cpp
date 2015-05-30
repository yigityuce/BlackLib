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


#include "BlackLib.h"

#include "examples/example_GPIO.h"
#include "examples/example_ADC.h"
#include "examples/example_PWM.h"
#include "examples/example_SPI.h"
#include "examples/example_UART.h"
#include "examples/example_I2C.h"
#include "examples/example_directory.h"
#include "examples/example_threadAndMutex.h"
#include "examples/example_time.h"




int main()
{

    example_GPIO();
    example_ADC();
    example_PWM();
    example_SPI();
    example_UART();
    example_I2C();
    example_directory();
    example_threadAndMutex();
    example_time();


    return 0;
}
