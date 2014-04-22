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


#ifndef BLACKERR_H_
#define BLACKERR_H_

/*! @brief Holds BlackCore errors.
 *
 *	This struct is base of the ERROR DATA STRUCT.
 *	The rest of error data structs include this.
 */
struct errorCore
{
	/*! @brief @b capemgr directory finding error.
	 *
	 *  Its value can change, when finding @a capemgr.X name, at @n
	 *  @li findCapeMgrName()
	 *
	 *  function in BlackCore class.
	 *  @sa BlackCore::findCapeMgrName()
	 */
	bool capeMgrError;


	/*! @brief @b ocp directory finding error.
	 *
	 *  Its value can change, when finding @a ocp.X name, at @n
	 *  @li findOcpName()
	 *
	 *  function in BlackCore class.
	 *  @sa BlackCore::findOcpName()
	 */
	bool ocpError;
};




/*! @brief Holds BlackCoreADC errors.
 *
 *	This struct holds ADC core errors and includes pointer of errorCore struct.
 */
struct errorCoreADC
{
	/*! @brief Pointer of errorCore struct which stores errors of BlackCore class.
	 *
	 *  This struct initializes and sets value, at constructer of BlackCoreADC class.
	 *  Gets value with @n
	 *  @li getErrorsFromCore()
	 *
	 *  function in BlackCore class.
	 *  @sa BlackCoreADC::BlackCoreADC()
	 *  @sa BlackCore::getErrorsFromCore()
	 */
	errorCore *coreErrors;


	/*! @brief @b helper directory finding error.
	*
	*  Its value can change, when finding @a helper.X name, at @n
	*  @li findHelperName()
	*
	*  function in BlackCoreADC class.
	*  @sa BlackCoreADC::findHelperName()
	*/
	bool helperError;


	/*! @brief <b> Device tree</b> loading error.
	*
	*  Its value can change, when loading adc overlay to device tree, at @n
	*  @li loadDeviceTree()
	*
	*  function in BlackCoreADC class.
	*  @sa BlackCoreADC::loadDeviceTree()
	*/
	bool dtError;
};





/*! @brief Holds BlackADC errors.
 *
 *	This struct holds ADC errors and includes pointer of errorCoreADC struct.
 */
struct errorADC
{
	/*! @brief Pointer of errorCoreADC struct which stores errors of BlackCoreADC class.
	*
	*  This struct initializes and sets value, at constructer of BlackADC class. @n
	*  Gets value with @n
	*  @li getErrorsFromCoreADC()
	*
	*  function in BlackCoreADC class.
	*  @sa BlackADC::BlackADC()
	*  @sa BlackCoreADC::getErrorsFromCoreADC()
	*/
	errorCoreADC *adcCoreErrors;


	/*! @brief <b> Value file</b> reading error.
	*
	*  Its value can change, when opening analog input's value file, at @n
	*  @li getValue()
	*  @li getNumericValue()
	*  @li getParsedValue()
	*
	*  function in BlackADC class.
	*  @sa BlackADC::getValue()
	*  @sa BlackADC::getNumericValue()
	*  @sa BlackADC::getParsedValue()
	*/
	bool readError;
};




/*! @brief Holds BlackCorePWM errors.
 *
 *	This struct holds PWM core errors and includes pointer of errorCore struct.
 */
struct errorCorePWM
{
	/*! @brief Pointer of errorCore struct which stores errors of BlackCore class.
	 *
	 *  This struct initializes and sets value, at constructer in BlackCorePWM class. @n
	 *  Gets value with @n
	 *  @li getErrorsFromCore()
	 *
	 *  function in BlackCore class.
	 *  @sa BlackCorePWM::BlackCorePWM()
	 *  @sa BlackCore::getErrorsFromCore()
	 */
	errorCore *coreErrors;


	/*! @brief @b Device @b tree loading error.
	*
	*  Its value can change, when loading subsystem pwm overlay to device tree, at @n
	*  @li loadDeviceTree()
	*  @li initialize()
	*
	*  function in BlackCorePWM class.
	*  @sa BlackCorePWM::loadDeviceTree()
	*  @sa BlackCorePWM::initialize()
	*/
	bool dtSsError;


	/*! @brief @b Device @b tree loading error.
	*
	*  Its value can change, when loading pwm overlay to device tree, at @n
	*  @li loadDeviceTree()
	*  @li initialize()
	*
	*  function in BlackCorePWM class.
	*  @sa BlackCorePWM::loadDeviceTree()
	*  @sa BlackCorePWM::initialize()
	*/
	bool dtError;


	/*! @brief @b pwm_test directory finding error.
	*
	*  Its value can change, when finding @a pwm_test_X.Y name, at @n
	*  @li findPwmTestName()
	*  @li initialize()
	*
	*  function in BlackCorePWM class.
	*  @sa BlackCorePWM::findPwmTestName()
	*  @sa BlackCorePWM::initialize()
	*/
	bool pwmTestError;


	/*! @brief @b PWM @b initialization error.
	*
	*  Its value can change, when triggering pwm initialization, at @n
	*  @li triggerInitialization()
	*  @li initialize()
	*
	*  function in BlackCorePWM class.
	*  @sa BlackCorePWM::triggerInitialization()
	*  @sa BlackCorePWM::initialize()
	*/
	bool initializeError;
};




/*! @brief Holds BlackPWM errors.
 *
 *	This struct holds PWM errors and includes pointer of errorCorePWM struct.
 */
struct errorPWM
{
	/*! @brief Pointer of errorCorePWM struct, which stores errors of BlackCorePWM class.
	*
	*  This struct initializes and sets value, at constructer in BlackPWM class. @n
	*  Gets value with @n
	*  @li getErrorsFromCorePWM()
	*
	*  function in BlackCorePWM class.
	*  @sa BlackPWM::BlackPWM()
	*  @sa BlackCorePWM::getErrorsFromCorePWM()
	*/
	errorCorePWM *pwmCoreErrors;


	/*! @brief @b Period @b file reading error.
	*
	*  Its value can change, when opening pwm's period value file, at @n
	*  @li getValue()
	*  @li getNumericValue()
	*  @li getPeriodValue()
	*  @li getNumericPeriodValue()
	*  @li setPeriodTime()
	*  @li setSpaceRatioTime()
	*  @li setLoadRatioTime()
	*
	*  function in BlackPWM class.
	*  @sa BlackPWM::getValue()
	*  @sa BlackPWM::getNumericValue()
	*  @sa BlackPWM::getPeriodValue()
	*  @sa BlackPWM::getNumericPeriodValue()
	*  @sa BlackPWM::setPeriodTime()
	*  @sa BlackPWM::setSpaceRatioTime()
	*  @sa BlackPWM::setLoadRatioTime()
	*/
	bool periodFileError;


	/*! @brief @b Duty @b file reading error.
	*
	*  Its value can change, when opening pwm's duty value file, at @n
	*  @li getValue()
	*  @li getNumericValue()
	*  @li getDutyValue()
	*  @li getNumericDutyValue()
	*  @li setDutyPercent()
	*  @li setPeriodTime()
	*  @li setSpaceRatioTime()
	*  @li setLoadRatioTime()
	*
	*  function in BlackPWM class.
	*  @sa BlackPWM::getValue()
	*  @sa BlackPWM::getNumericValue()
	*  @sa BlackPWM::getDutyValue()
	*  @sa BlackPWM::getNumericDutyValue()
	*  @sa BlackPWM::setDutyPercent()
	*  @sa BlackPWM::setPeriodTime()
	*  @sa BlackPWM::setSpaceRatioTime()
	*  @sa BlackPWM::setLoadRatioTime()
	*/
	bool dutyFileError;


	/*! @brief @b Run @b file reading error.
	*
	*  Its value can change, when opening pwm's run value file, at @n
	*  @li getRunValue()
	*  @li isRunning()
	*  @li setRunState()
	*  @li toggleRunState()
	*
	*  function in BlackPWM class.
	*  @sa BlackPWM::getRunValue()
	*  @sa BlackPWM::isRunning()
	*  @sa BlackPWM::setRunState()
	*  @sa BlackPWM::toggleRunState()
	*/
	bool runFileError;


	/*! @brief @b Polarity @b file reading error.
	*
	*  Its value can change, when opening pwm's polarity value file, at @n
	*  @li getPolarityValue()
	*  @li isPolarityStraight()
	*  @li isPolarityReverse()
	*  @li setPolarity()
	*  @li tooglePolarity()
	*
	*  function in BlackPWM class.
	*  @sa BlackPWM::getPolarityValue()
	*  @sa BlackPWM::isPolarityStraight()
	*  @sa BlackPWM::isPolarityReverse()
	*  @sa BlackPWM::setPolarity()
	*  @sa BlackPWM::tooglePolarity()
	*/
	bool polarityFileError;


	/*! @brief Out of range value error.
	*
	*  Its value can change, when setting some variables of pwm, at @n
	*  @li setDutyPercent()
	*  @li setPeriodTime()
	*  @li setSpaceRatioTime()
	*  @li setLoadRatioTime()
	*
	*  function in BlackPWM class.
	*  @sa BlackPWM::setDutyPercent()
	*  @sa BlackPWM::setPeriodTime()
	*  @sa BlackPWM::setSpaceRatioTime()
	*  @sa BlackPWM::setLoadRatioTime()
	*/
	bool outOfRange;
};




/*! @brief Holds BlackCoreGPIO errors.
 *
 *	This struct holds GPIO core errors and includes pointer of errorCore struct.
 */
struct errorCoreGPIO
{
	/*! @brief Pointer of errorCore struct, which stores errors of BlackCore class.
	 *
	 *  This struct initializes and sets value, at constructer in BlackCoreGPIO class. @n
	 *  Gets value with @n
	 *  @li getErrorsFromCore()
	 *
	 *  function in BlackCore class.
	 *  @sa BlackCoreGPIO::BlackCoreGPIO()
	 *  @sa BlackCore::getErrorsFromCore()
	 */
	errorCore *coreErrors;


	/*! @brief @b Export @b file opening error.
	*
	*  Its value can change, when exporting pin, at @n
	*  @li doExport()
	*  @li initialize()
	*
	*  function in BlackCoreGPIO class.
	*  @sa BlackCoreGPIO::doExport()
	*  @sa BlackCoreGPIO::initialize()
	*/
	bool exportFileError;


	/*! @brief @b Direction @b file opening error.
	*
	*  Its value can change, when setting direction of pin, at @n
	*  @li setDirection()
	*  @li initialize()
	*
	*  function in BlackCoreGPIO class.
	*  @sa BlackCoreGPIO::setDirection()
	*  @sa BlackCoreGPIO::initialize()
	*/
	bool directionFileError;


	/*! @brief @b GPIO @b initialization error.
	*
	*  Its value can change, when triggering gpio initialization, at @n
	*  @li triggerInitialization()
	*  @li initialize()
	*
	*  function in BlackCoreGPIO class.
	*  @sa BlackCoreGPIO::triggerInitialization()
	*  @sa BlackCoreGPIO::initialize()
	*/
	bool initializeError;
};




/*! @brief Holds BlackGPIO errors.
 *
 *	This struct holds GPIO errors and includes pointer of errorCoreGPIO struct.
 */
struct errorGPIO
{
	/*! @brief Pointer of errorCoreGPIO struct, which stores errors of BlackCoreGPIO class.
	*
	*  This struct initializes and sets value, at constructer in BlackGPIO class. @n
	*  Gets value with @n
	*  @li getErrorsFromCoreGPIO()
	*
	*  function in BlackCoreGPIO class.
	*  @sa BlackGPIO::BlackGPIO()
	*  @sa BlackCoreGPIO::getErrorsFromCoreGPIO()
	*/
	errorCoreGPIO *gpioCoreErrors;


	/*! @brief Pin @b didn't @b export error.
	*
	*  Its value can change, when checking GPIO pin's export status, at @n
	*  @li isExported()
	*  @li isReady()
	*  @li getValue()
	*  @li isHigh()
	*  @li toggleValue()
	*  @li setValue()
	*
	*  function in BlackGPIO class.
	*  @sa BlackGPIO::isExported()
	*  @sa BlackGPIO::isReady()
	*  @sa BlackGPIO::getValue()
	*  @sa BlackGPIO::isHigh()
	*  @sa BlackGPIO::toggleValue()
	*  @sa BlackGPIO::setValue()
	*/
	bool exportError;


	/*! @brief Pin direction @b didn't @b set error.
	*
	*  Its value can change, when checking GPIO pin's direction, at @n
	*  @li isDirectionSet()
	*  @li isReady()
	*  @li getValue()
	*  @li isHigh()
	*  @li toggleValue()
	*  @li setValue()
	*
	*  function in BlackGPIO class.
	*  @sa BlackGPIO::isDirectionSet()
	*  @sa BlackGPIO::isReady()
	*  @sa BlackGPIO::getValue()
	*  @sa BlackGPIO::isHigh()
	*  @sa BlackGPIO::toggleValue()
	*  @sa BlackGPIO::setValue()
	*/
	bool directionError;


	/*! @brief @b Value @b file reading error.
	*
	*  Its value can change, when opening gpio pin's value file, at @n
	*  @li getValue()
	*  @li isHigh()
	*  @li toggleValue()
	*
	*  function in BlackGPIO class.
	*  @sa BlackGPIO::getValue()
	*  @sa BlackGPIO::isHigh()
	*  @sa BlackGPIO::toggleValue()
	*/
	bool readError;


	/*! @brief @b Value @b file writing error.
	*
	*  Its value can change, when opening gpio pin's value file, at @n
	*  @li setValue()
	*
	*  function in BlackGPIO class.
	*  @sa BlackGPIO::setValue()
	*/
	bool writeError;


	/*! @brief Pin @b write forcing error.
	*
	*  Its value can change, when trying to write something to input type gpio, at @n
	*  @li setValue()
	*
	*  function in BlackGPIO class.
	*  @sa BlackGPIO::setValue()
	*/
	bool forcingError;
};


#endif /* BLACKERR_H_ */
