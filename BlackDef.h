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



#ifndef BLACKDEF_H_
#define BLACKDEF_H_


/*! \mainpage Main Page

@n
BlackLib library is wrote for controlling Beaglebone Black's feature. It takes power from C++
language. It is created for reading analog input, generating pwm signal and using gpio pins.
In addition to them, it includes debugging feature. So you can check errors after call any
function in the library.
- - - -
@n
<h2> Debugging </h2>
It always tracks member functions errors and records these errors to data
structures. All end nodes which interact with end users, have
overloaded fail() functions. So you can check all errors or specific error whichever
you want. @n @n

- - - -
@n
<h2> Class Hierarchy </h2>

- <h3> Library Core </h3>
BlackLib includes BlackCore class for doing core process. End users can't access to it.
Because it is abstract class and all member functions, except constructor and destructor,
are private or protected. @n @n

- <h3> Sub Level Cores </h3>
BlackLib includes sub level cores for GPIO, ADC and PWM features. Preparing, device tree loading or
initialization stages are realized in here, at sub level cores. Therefore, if you don't like end nodes
or you don't want to use these, you can derive your own class(es), from these sub level cores. But
end nodes designed for taking care of your all need. @n @n

- <h3> End Node Classes </h3>
End node classes are designed for interacting with end user. You can read, set or control
Beaglebone Black's ADC, GPIO or PWM features from these classes. These classes include
primary functions like read or set properties of Beaglebone Black's features and include additional functions
like ADC parser, gpio pin toggle etc. to make easier your life. @n @n

- - - -
@n
<h2> Definitions </h2>
BlackLib includes enum type definitions for your and Beaglebone Black's safety. GPIO, ADC,
PWM names; PWM, GPIO values; GPIO directions and a lot more features defined with enums.
It means you can't call some member functions without use this enums. These enums avoid
user errors like write 345 to gpio export file instead of 34. @n @n

- - - -
@n
<h2> Contact </h2>
For any comment or suggestion please contact the creator of BlackLib Library
at contact@blacklib.yigityuce.com @n @n

- - - -
@n

This manual is divided in the following sections:
- <a href="#"> <b> Classes </b></a>
	- <a href="annotated.html"> <b> Class List </b> </a>
	- <a href="classes.html"> <b> Class Index </b></a>
	- <a href="hierarchy.html"> <b> Class Hierarchy </b></a>
- <a href="files.html"> <b> Files </b></a>
- <a href="#"> <b> Members List </b></a>
	- <a href="functions.html"> <b> Class Members </b></a>
		- <a href="functions_func.html"> <b> Class Members - Functions </b></a>
		- <a href="functions_vars.html"> <b> Class Members - Variables</b></a>
		- <a href="functions_enum.html"> <b> Class Members - Enumarations</b></a>
		- <a href="functions_eval.html"> <b> Class Members - Enumarator</b></a>
	- <a href="globals.html"> <b> File Members </b></a>
		- <a href="globals_func.html"> <b> File Members - Functions </b></a>
		- <a href="globals_vars.html"> <b> File Members - Variables</b></a>
		- <a href="globals_enum.html"> <b> File Members - Enumarations</b></a>
		- <a href="globals_eval.html"> <b> File Members - Enumarator</b></a>
- \subpage user-manual "User Manuals"
- \subpage downloads "Downloads"
- \subpage contact "Contact"
*/



/*! \page user-manual User Manuals
User Manuals are pdf files which include basic library usage for end users. The user manuals languages
are English and Turkish for now. If you want to translate these user-manuals to your language,
you can contact at contact@blacklib.yigityuce.com with "BlackLib - User Manual Translate" subject. @n@n
You can download user manuals at these links below.
<CENTER>
| Language 	| Interpreter 	| Contact Adress 	| Download Link		|
| :----		| :----:	| :----			| :----:		|
| Turkish  	| Yigit Yuce    | ygtyce[at]gmail.com   | <a href="DOCUMENTS/TR/BlackLib-KullanimKilavuzu.pdf"> <b> BlackLib Kullanim Kilavuzu </b></a>|
| English	| Yigit Yuce    | ygtyce[at]gmail.com   | <a href="DOCUMENTS/EN/BlackLib-UserManual.pdf"> <b> BlackLib User-Manual </b></a>	|
</CENTER>

@n <hr> @n
You can download GPIO flags usage table at these links below.
<CENTER>
| Language 	| Interpreter 	| Contact Adress 	| Download Link  	|
| :----		| :----:	| :----			| :----:		|
| Turkish  	| Yigit Yuce    | ygtyce[at]gmail.com  	| <a href="DOCUMENTS/TR/GpioBayraklariKullanimTablosu.pdf"> <b> GPIO Bayraklari Kullanim Tablosu </b></a>	|
| English	| Yigit Yuce    | ygtyce[at]gmail.com   | <a href="DOCUMENTS/EN/GpioFlagsUsageTable.pdf"> <b> GPIO Flags Usage Table </b></a>	|
</CENTER>

*/


/*! \page downloads Downloads
You can download BlackLib and its document with described methods below.

@n @n
<h2>GitHub</h2>
You can download all files from github. You must run this command,
~~~~~~~~~~~~~~~~~~~~~
git clone https://github.com/yigityuce/BlackLib.git
~~~~~~~~~~~~~~~~~~~~~
then appear BlackLib directory in your current location. You can see this with "ls -l" command. You
should read README file or User-Manual.

Additionaly you can access source files and other documents of BlackLib project at GitHub.
<CENTER><a href="http://github.com/yigityuce/BlackLib" target="_blank" > <b> http://github.com/yigityuce/BlackLib </b></a></CENTER>

@n @n
<h2>SourceForge</h2>
You can download all files from sourceforge. You must click download button at project
page, then it redirects you a download page and downloading starts automatically.@n
<CENTER><a href="http://sourceforge.net/projects/blacklib/" target="_blank"> <b> BlackLib at SourceForge </b></a></CENTER>
*/


/*! \page contact Contact
For any comment or suggestion please contact the creator of BlackLib Library
at <b> contact@blacklib.yigityuce.com</b>@n @n
<hr>@n
Thanks for writing one of these subject below, when you're sending email.
<CENTER>
|  		| SUBJECT				|
| :----		| ----: 				|
| Translation  	| "BlackLib - User Manual Translate"    |
| Bug		| "BlackLib - Bug Report"		|
| Suggestion	| "BlackLib - Suggestion"		|
| Other		| "BlackLib - Other"			|
</CENTER>
*/











const std::string 	DEFAULT_CAPE_MGR_NUMBER = "8";		//!< If @b capemgr finding fails, it uses this number
const std::string 	DEFAULT_OCP_NUMBER 	= "2";		//!< If @b ocp finding fails, it uses this number
const std::string 	DEFAULT_HELPER_NUMBER 	= "14";		//!< If @b helper finding fails, it uses this number
const std::string 	DEFAULT_PWM_TEST_NUMBER = "15";		//!< If @b pwm_test finding fails, it uses this number
const std::string	SEARCH_DIR_NOT_FOUND	= "Not Found";	//!< If directory searching fails, it returns this string





/*!
 * This enum uses for selecting ADC input.
 */
enum adc_name
{ 	
	AIN0=0,		AIN1=1,
	AIN2=2,		AIN3=3,
	AIN4=4,		AIN5=5,
	AIN6=6
};



/*!
 * This enum uses for selecting parsing level of ADC value.
 */
enum digit_after_point	
{	
	dap1=1,		dap2=2,
	dap3=3
};




/*!
 *  This enum uses for selecting GPIO type.
 */
enum gpio_type 			
{
	input=0,	output=1	
};




/*!
 * This enum uses for setting GPIO output value.
 */
enum gpio_value			
{
	low=0,		high=1 		
};




/*!
 * This enum uses for selecting GPIO number.
 */
enum gpio_name 			
{
	GPIO_125=125, 	GPIO_123=123,
	GPIO_122=122,	GPIO_121=121,
	GPIO_120=120, 	GPIO_117=117,
	GPIO_49=49, 	GPIO_15=15,
	GPIO_48=48,	GPIO_51=51,
	GPIO_20=20, 	GPIO_38=38,
	GPIO_30=30,	GPIO_60=60,
	GPIO_31=31, 	GPIO_40=40,
	GPIO_39=39, 	GPIO_34=34,
	GPIO_35=35, 	GPIO_66=66,
	GPIO_67=67,	GPIO_69=69,
	GPIO_68=68, 	GPIO_45=45,
	GPIO_44=44, 	GPIO_23=23,
	GPIO_26=26, 	GPIO_47=47,
	GPIO_46=46, 	GPIO_27=27,
	GPIO_65=65,	GPIO_22=22,
	GPIO_63=63, 	GPIO_62=62,
	GPIO_37=37, 	GPIO_36=36,
	GPIO_33=33, 	GPIO_32=32,
	GPIO_61=61, 	GPIO_86=86,
	GPIO_88=88,	GPIO_87=87,
	GPIO_89=89, 	GPIO_10=10,
	GPIO_11=11, 	GPIO_81=81,
	GPIO_80=80, 	GPIO_78=78,
	GPIO_79=79, 	GPIO_76=76,
	GPIO_77=77, 	GPIO_74=74,
	GPIO_75=75, 	GPIO_72=72,
	GPIO_73=73,	GPIO_70=70,
	GPIO_71=71,	GPIO_14=14,
	GPIO_9=9, 	GPIO_8=8,
	GPIO_7=7,	GPIO_5=5,
	GPIO_4=4,	GPIO_3=3,
	GPIO_2=2
};



/*!
 * This enum uses for selecting PWM output by pin name.
 */
enum pwm_pin_name		
{
 	P8_13=0, 	P8_19=1,
	P9_14=2,	P9_16=3,
	P9_21=4, 	P9_22=5,
	P9_42=6
};




/*!
 * This enum uses for selecting PWM output by bus name.
 */
enum pwm_bus_name		
{
	EHRPWM2B=0,	EHRPWM2A=1,
	EHRPWM1A=2,	EHRPWM1B=3,
	EHRPWM0B=4,	EHRPWM0A=5,
	ECAP0=6
};




/*!
 * This enum uses for setting PWM state.
 */
enum pwm_value			
{	
	stop=0,		run=1 		
};




/*!
 * This enum uses for setting PWM polarity.
 */
enum pwm_polarity		
{	
	straight=0, 	reverse=1	
};



#endif /* BLACKDEF_H_ */
