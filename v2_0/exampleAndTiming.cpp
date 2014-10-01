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


#include "BlackLib.h"

#include "exampleAndTiming/exampleAndTiming_GPIO.h"
#include "exampleAndTiming/exampleAndTiming_ADC.h"
#include "exampleAndTiming/exampleAndTiming_PWM.h"
#include "exampleAndTiming/exampleAndTiming_SPI.h"
#include "exampleAndTiming/exampleAndTiming_UART.h"
#include "exampleAndTiming/exampleAndTiming_I2C.h"


int main()
{
    exampleAndTiming_GPIO();
    exampleAndTiming_ADC();
    exampleAndTiming_PWM();
    exampleAndTiming_SPI();
    exampleAndTiming_UART();
    exampleAndTiming_I2C();

    return 0;
}
