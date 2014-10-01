 /*

 ########################################################################################
 #  BlackLib Library controls Beaglebone Black's inputs and outputs.			#
 #  Copyright (C) 2013-2014 by Yigit YUCE						#
 ########################################################################################
 #											#
 #  This file is part of BlackLib library.						#
 #											#
 #  BlackLib library is free software: you can redistribute it and/or modify		#
 #  it under the terms of the GNU Lesser General Public License as published by		#
 #  the Free Software Foundation, either version 3 of the License, or			#
 #  (at your option) any later version.							#
 #											#
 #  BlackLib library is distributed in the hope that it will be useful,			#
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of			#
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
 #  GNU Lesser General Public License for more details.					#
 #											#
 #  You should have received a copy of the GNU Lesser General Public License		#
 #  along with this program.  If not, see <http://www.gnu.org/licenses/>. 		#
 #											#
 #  For any comment or suggestion please contact the creator of BlackLib Library	#
 #  at ygtyce@gmail.com									#
 #											#
 ########################################################################################

 */


#include <iostream>
#include <unistd.h>
#include <unistd.h>
#include "BlackLib.h"
using namespace std;

void linePrint(int number,char symbol)
{
	for(int i=0;i<number;i++)
	{
		cout << symbol;
	}
	cout << endl;
}





int main()
{
	BlackADC 	analog(AIN4);		// initialization analog input
	BlackGPIO 	led1(GPIO_30,output);	// initialization first led
	BlackGPIO 	button1(GPIO_60,input);	// initialization first button
	BlackGPIO 	button2(GPIO_48,input);	// initialization second button
	BlackPWM 	pwmLed2(EHRPWM2A);	// initialization pwm with second led


	float percent = -30.0;

	led1.setValue(high);			// turn on the led1
	pwmLed2.setPeriodTime(5000000);		// set period of pwm to 5.000.000 nanosecond
	pwmLed2.setDutyPercent(0.0);		// set percentage of pwm to 0

	sleep(1);				// give some time to Beaglebone Black



	while(true)
	{
		// read button1 value
		cout << "Button1: \t" 		<< button1.getValue() 	<< endl;
		
		// read button2 value	
		cout << "Button2: \t" 		<< button2.getValue() 	<< endl;

		// read led1 value
		cout << "Led1: \t\t" 		<< led1.getValue() 	<< endl;

		// read analog input value at string type
		cout << "AIN4_str: \t" 		<< analog.getValue() 	<< endl;

		// give some time to Beaglebone Black
		usleep(1000);

		// read analog input value at integer type
		cout << "AIN4_int: \t" 		<< analog.getNumericValue() << endl;

		// give some time to Beaglebone Black
		usleep(1000);				

		// read parsed analog input value at X,YZ type		
		cout << "AIN4_mid: \t" 		<< analog.getParsedValue(dap2) 	<< endl;

		// read duty value of pwm at string type
		cout << "DUTY_str: \t" 		<< pwmLed2.getDutyValue() 	<< endl;

		// read duty value of pwm at integer type
		cout << "DUTY_int: \t" 		<< pwmLed2.getNumericDutyValue() << endl;

		// read period value of pwm at string type
		cout << "PERIOD_str: \t"	<< pwmLed2.getPeriodValue() 	<< endl;

		// read period value of pwm at integer type
		cout << "PERIOD_int: \t" 	<< pwmLed2.getNumericPeriodValue() << endl;

		// read percentage value of pwm at string type
		cout << "PERCENT_str: \t"	<< pwmLed2.getValue() 		<< endl;

		// read percentage value of pwm at float type
		cout << "PERCENT_flt: \t" 	<< pwmLed2.getNumericValue() 	<< endl;

		// read polarity value of pwm
		cout << "POLARTY_str: \t" 	<< pwmLed2.getPolarityValue() 	<< endl;

		// read run value of pwm
		cout << "RUN_str: \t"		<< pwmLed2.getRunValue() 	<< endl;





		// new percent value range controlling
		if( pwmLed2.fail(BlackPWM::outOfRangeErr) )
		{
			cout << endl << "New percentage value is out of range." << endl;
		}

		linePrint(100,'-');			// seperator
		sleep(1);				// wait 1 second

		led1.toggleValue();			// toogle led1

		pwmLed2.setDutyPercent(percent);	// set percentage of pwm
		percent += 5.0;				// increase percent

	}

	return 0;
}
