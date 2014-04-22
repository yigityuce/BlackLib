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



#ifndef BLACKLIB_H_
#define BLACKLIB_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>		// need for 	tostr() 	function
#include <stdlib.h>		// need for 	atoi() 		function 	in BlackADC::getIntValue()
#include <math.h>		// need for 	round() 	function 	in BlackADC::getParsedValue()
#include <cstdio>		// need for 	popen() 	function 	in BlackCore::executeShellCmd()
#include <dirent.h>		// need for 	dirent 		struct 		in BlackCore::searchDirectory()
#include <inttypes.h>		// need for 	strtoimax() 	function 	in BlackPWM::getNumericPeriodValue()
#include "BlackErr.h"		// Black Errors header file
#include "BlackDef.h"		// Black Definitions header file




// ########################################### BLACKCORE DECLARATION STARTS ########################################### //

/*! @brief Base class of the other classes.
 *
 *	This class is core of the @b BlackLib Library.
 *	It includes private functions like communicating with operating system and their limited versions to
 *	use from derived class.
 */
class BlackCore
{
	private:
		errorCore	*coreErrors; 			/*!< @brief is used to hold the errors of BlackCore class */
		std::string	capeMgrName;			/*!< @brief is used to hold the capemgr name */
		std::string	ocpName;			/*!< @brief is used to hold the ocp name */
		std::string	slotsFilePath;			/*!< @brief is used to hold the slots file path */

		/*! @brief Finds full name of capemgr name.
		*
		*  This function searches @b "/sys/devices/" directory,
		*  to find file/directory which starts with @b "bone_capemgr."
		*  @return True if successful, else false.
		*  @sa BlackCore::searchDirectory()
		*/
		bool 		findCapeMgrName();

		/*! @brief Finds full name of ocp name.
		*
		*  This function searches @b "/sys/devices/" directory,
		*  to find file/directory which starts with @b "ocp."
		*  @return True if successful, else false.
		*  @sa BlackCore::searchDirectory()
		*/
		bool 		findOcpName();

		/*! @brief Generates full path of slots file.
		*
		*  This function generates full slots file path with using capemgr name.
		*  And sets this path to BlackCore::slotsFilePath variable.
		*/
		void		setSlotsFilePath();

		/*! @brief Executes system call.
		*
		*  This function executes system commands with using popen() function.
		*  This example executes "ls" command with argument "la" and saves
		*  output to returnValue variable. @n @n
		*  <b> string returnValue = executeCommand("ls -la"); </b>
		*/
		std::string	executeCommand(std::string command);

		/*! @brief Searches specified directory to find specified file/directory.
		*
		*  @param[in] searchIn		searching directory
		*  @param[in] searchThis	search file/directory
		*  @return Full name of searching file/directory.
		*/
		std::string	searchDirectory(std::string searchIn, std::string searchThis);

		/*! @brief First declaration of this function.
		*/
		virtual bool	loadDeviceTree() = 0;



	protected:

		/*!
		 * This enum is used for defining ADC and PWM device driver names.
		 */
		enum ocpSearch	
		{ 
			ADC_helper	= 0, 	/*!< enumeration for @a helper name at BlackCore::searchDirectoryOcp() function parameter*/
			PWM_P8_13	= 1, 	/*!< enumeration for @a P8_13 pwm test name */
			PWM_P8_19	= 2, 	/*!< enumeration for @a P8_19 pwm_test name */
			PWM_P9_14	= 3, 	/*!< enumeration for @a P9_14 pwm_test name */
			PWM_P9_16	= 4, 	/*!< enumeration for @a P9_16 pwm_test name */
			PWM_P9_21	= 5, 	/*!< enumeration for @a P9_21 pwm_test name */
			PWM_P9_22	= 6, 	/*!< enumeration for @a P9_22 pwm_test name */
			PWM_P9_42	= 7  	/*!< enumeration for @a P9_42 pwm_test name */
		};

		/*! @brief Searches ocp directory to find specified file/directory.
		*
		* This function searches ocp directory only. It can be used from derived class.
		*  @param[in] searchThis	takes BlackCore::ocpSearch type variable(enum)
		*  @return Full name of searching file/directory.
		*/
		std::string	searchDirectoryOcp(BlackCore::ocpSearch searchThis);

		/*! @brief Exports errorCore struct to derived class.
		*
		*  @return errorCore struct pointer.
		*/
		errorCore	*getErrorsFromCore();

		/*! @brief Exports capemgr name to derived class.
		*
		*  @return BlackCore::capeMgrName variable.
		*/
		std::string	getCapeMgrName();

		/*! @brief Exports ocp name to derived class.
		*
		*  @return BlackCore::ocpName variable.
		*/
		std::string	getOcpName();

		/*! @brief Exports slots file path to derived class.
		*
		*  @return BlackCore::slotsFilePath variable.
		*/
		std::string	getSlotsFilePath();



	public:
		/*! @brief Constructor of BlackCore class.
		*
		* This function initializes errorCore struct and runs these functions:
		* @li findCapeMgrName()
		* @li findOcpName()
		* @li setSlotsFilePath()
		*/
				BlackCore();

		/*! @brief Destructor of BlackCore class.
		 *
		 */
		virtual 	~BlackCore();

};
// ############################################ BLACKCORE DECLARATION ENDS ############################################ //











// ######################################### BLACKCOREADC DECLARATION STARTS ########################################## //

/*! @brief Preparation phase of Beaglebone Black, to use analog input feature.
 *
 *	This class is core of the BlackADC class.
 *	It includes private functions which set Beaglebone Black for using analog input feature.
 */
class BlackCoreADC : virtual protected BlackCore
{
	private:
		errorCoreADC	*adcCoreErrors;		/*!< @brief is used to hold the errors of BlackCoreADC class */
		std::string	helperName;		/*!< @brief is used to hold the helper(analog input device driver) name */

		/*! @brief Loads ADC overlay to device tree.
		*
		*  This function loads @b "cape-bone-iio" overlay to device tree.
		*  This overlay performs pinmuxing and generates device driver.
		*  @return True if successful, else false.
		*/
		bool		loadDeviceTree();

		/*! @brief Finds full name of helper name.
		*
		*  This function searches @b "ocp.X" directory, to find directory which starts with
		*  @b "helper." by using searchDirectoryOcp() protected function at BlackCore class.
		*  @return True if successful, else false.
		*  @sa BlackCore::searchDirectoryOcp()
		*/
		bool 		findHelperName();



	protected:

		/*! @brief Exports errorCoreADC struct to derived class.
		*
		*  @return errorCoreADC struct pointer.
		*/
		errorCoreADC	*getErrorsFromCoreADC();

		/*! @brief Exports helper path to derived class.
		*
		*  @return Full path of helper.
		*/
		std::string	getHelperPath();



	public:

		/*! @brief Constructor of BlackCoreADC class.
		*
		* This function initializes errorCoreADC struct and runs these functions:
		* @li loadDeviceTree()
		* @li findHelperName()
		*/
				BlackCoreADC();

		/*! @brief Destructor of BlackCoreADC class.
		*
		*/
		virtual 	~BlackCoreADC();


		/*! @brief First declaration of this function.
		*/
		virtual std::string	getValue() = 0;
};
// ########################################## BLACKCOREADC DECLARATION ENDS ########################################### //











// ########################################### BLACKADC DECLARATION STARTS ############################################ //

/*! @brief Interacts with end user, to use ADC feature.
 *
 *	This class is end node to use analog inputs. End users interact with
 *	analog inputs from this class. It includes public functions for reading analog
 *	inputs, and includes enum type flags for error debugging.
 */
class BlackADC : virtual private BlackCoreADC
{
	private:
		errorADC	*adcErrors;	/*!< @brief is used to hold the errors of BlackADC class */
		std::string	ainPath;	/*!< @brief is used to hold the AINx file path */
		adc_name 	adcName;	/*!< @brief is used to hold the selected adc name */


	public:

		/*!
		 * This enum is used to define ADC debugging flags.
		 */
		enum flags 
		{ 	
			cpmgrErr	= 0,	/*!< enumeration for @a errorCore::capeMgrError status */
			ocpErr		= 1,	/*!< enumeration for @a errorCore::ocpError status */
			helperErr	= 2,	/*!< enumeration for @a errorCoreADC::helperError status */
			dtErr		= 3,	/*!< enumeration for @a errorCoreADC::dtError status */
			ReadErr 	= 4	/*!< enumeration for @a errorADC::readError status */
		};

		/*! @brief Constructor of BlackADC class.
		*
		* This function initializes errorADC struct, sets value path for reading analog input
		* and prints message related to errorCoreADC::dtError variable, for informing user
		* about the result of the initialization process.
		* @param [in] adc	name of adc (enum),(AINx)
		* @sa getOcpName()
		* @sa getHelperPath()
		* @sa adc_name
		*/
				BlackADC(adc_name adc);

		/*! @brief Destructor of BlackADC class.
		*
		*/
		virtual 	~BlackADC();

		/*! @brief Exports analog input DC value(mV).
		*
		*  This function reads specified file from path, where defined
		*  at BlackADC::ainPath variable. This file holds analog input voltage at milivolt level.
		*  @return @a String type analog input value. If file opening fails, it returns error message.
		*/
		std::string	getValue();

		/*! @brief Exports analog input DC value(mV).
		*
		*  This function reads specified file from path, where defined at BlackADC::ainPath
		*  variable. This file holds analog input voltage at milivolt level.
		* @return @a integer type analog input value. If file opening fails, it returns -1.
		*/
		int 		getNumericValue();

		/*! @brief Exports converted analog input DC value(Volt).
		*
		* This function gets value by using getNumericValue() function and converts this value to volt
		* level, according to input parameter.
		* @param [in] dap	convertion level (enum),(dapX) @a Expansion: digit after point
		* @return @a converted analog input value as float.
		* @sa getNumericValue()
		* @sa digit_after_point
		*/
		float 		getParsedValue(digit_after_point dap);

		/*! @brief Exports analog input pin name.
		*
		*  @return BlackADC::adcName variable.
		*/
		adc_name	getName();

		/*! @brief Is used for general debugging.
		*
		* @return True if any error occured, else false.
		* @sa errorADC
		*/
		bool 		fail();

		/*! @brief Is used for specific debugging.
		*
		* You can use this function, after call BlackADC member functions in your code. The
		* input parameter is used for finding out status of selected error.
		* @param [in] f		specific error type (enum)
		* @return Value of @a selected error.
		* @sa errorADC
		*/
		bool 		fail(BlackADC::flags f);
};
// ############################################ BLACKADC DECLARATION ENDS ############################################# //









// ######################################### BLACKCOREPWM DECLARATION STARTS ########################################## //

/*! @brief Preparation phase of Beaglebone Black, to use pwm feature.
 *
 *	This class is core of the BlackPWM class.
 *	It includes private functions which set Beaglebone Black for using pwm feature,
 *	and protected functions which are using for triggering initialization from derived
 *	class and pass variables to derived class.
 */
class BlackCorePWM : virtual protected BlackCore
{
	private:
		errorCorePWM	*pwmCoreErrors;		/*!< @brief is used to hold the errors of BlackCorePWM class */
		std::string	dtboFileName;		/*!< @brief is used to hold file name which will load to device tree */
		std::string	pwmName;		/*!< @brief is used to hold the selected pwm name */
		std::string	pwmTestName;		/*!< @brief is used to hold the pwm_test (pwm device driver) name */
		bool		isInitializeBefore;	/*!< @brief is used to hold initialization status */

		/*! @brief Loads PWM overlays to device tree.
		*
		*  This function loads @b "am33xx_pwm" and @b "bone_pwm_P?_?" overlay to device tree.
		*  Question marks at the second overlay, represents port and pin numbers of selected PWM
		*  output. This overlays perform pinmuxing and generate device drivers.
		*  @return True if successful, else false.
		*/
		bool		loadDeviceTree();

		/*! @brief Finds full name of pwm_test.
		*
		*  This function searches @b "ocp.X" directory to find directory starts with
		*  @b "pwm_test_X." by using searchDirectoryOcp() protected function at BlackCore class.
		*  @return True if successful, else false.
		*  @sa BlackCore::searchDirectoryOcp()
		*/
		bool 		findPwmTestName();

		/*! @brief Performs initialization for using Beaglebone Black's pwm feature.
		*
		*  This function calls loadDeviceTree() function and if it returns true, calls
		*  findPwmTestName() function. These are required to use pwm.
		*  This function only can be called from triggerInitialization() function.
		*  @return @a string type fail or successful message.
		*  @sa loadDeviceTree()
		*  @sa findPwmTestName()
		*  @sa triggerInitialization()
		*/
		std::string	initialize();

		/*! @brief Converts the pwm_pin_name type input parameter.
		*
		*  This function converts the input variable parseThis into a string.
		*
		*  @param [in] parseThis pwm_pin_name (enum)
		*  @return string type converted pwm name.
		*  @sa pwm_pin_name
		*/
		std::string	parsePwmName(pwm_pin_name parseThis);


	protected:

		/*! @brief Executes initialization.
		*
		*  This function checks isInitializeBefore and pwmTestError variables. Then
		*  it performs initialization or does nothing, by value of these variables.
		*
		*  @param [in] pwm_pin pwm pin name (enum)
		*  @return initialize() function's return value or fail message.
		*  @sa initialize()
		*  @sa isInitializeBefore
		*  @sa errorCorePWM::pwmTestError
		*/
		std::string	triggerInitialization(pwm_pin_name pwm_pin);

		/*! @brief Executes initialization.
		*
		*  This function checks isInitializeBefore and pwmTestError variables. Then
		*  it performs initialization or does nothing, by value of these variables.
		*
		*  @param [in] pwm_bus pwm bus name (enum)
		*  @return initialize() function's return value or fail message.
		*  @sa initialize()
		*  @sa isInitializeBefore
		*  @sa pwmTestError
		*/
		std::string	triggerInitialization(pwm_bus_name pwm_bus);

		/*! @brief Exports pwm name to derived class.
		*
		*  @return BlackCorePWM::pwmName variable.
		*/
		std::string	getPwmName();

		/*! @brief Exports pwm_test path to derived class.
		*
		*  @return Full path of pwm_test.
		*/
		std::string	getPwmTestPath();

		/*! @brief Exports errorCorePWM struct to derived class.
		*
		*  @return errorCorePWM struct pointer.
		*/
		errorCorePWM	*getErrorsFromCorePWM();

	public:

		/*! @brief Constructor of BlackCorePWM class.
		*
		* This function initializes errorCorePWM struct and isInitializeBefore variable.
		*/
				BlackCorePWM();

		/*! @brief Destructor of BlackCorePWM class.
		*
		*/
		virtual 	~BlackCorePWM();

		/*! @brief First declaration of this function.
		*/
		virtual std::string	getValue() = 0;
};
// ########################################## BLACKCOREPWM DECLARATION ENDS ########################################### //










// ########################################### BLACKPWM DECLARATION STARTS ############################################ //

/*! @brief Interacts with end user, to use PWM feature.
 *
 *	This class is end node to use pwm signals. End users interact with
 *	pwm signal from this class. It includes public functions to set and get properties of pwm signal.
 */
class BlackPWM : virtual private BlackCorePWM
{
	private:
		errorPWM	*pwmErrors;	/*!< @brief is used to hold the errors of BlackPWM class */
		pwm_pin_name	pwmPinName;	/*!< @brief is used to hold the selected pwm @b pin name */
		pwm_bus_name	pwmBusName;	/*!< @brief is used to hold the selected pwm @b bus name */
		std::string	periodPath;	/*!< @brief is used to hold the @a period file path */
		std::string	dutyPath;	/*!< @brief is used to hold the @a duty file path */
		std::string	runPath;	/*!< @brief is used to hold the @a run file path */
		std::string	polarityPath;	/*!< @brief is used to hold the @a polarity file path */


	public:
		/*!
		* This enum is used to define PWM debugging flags.
		*/
		enum flags
		{	
			periodFileErr	= 0,	/*!< enumeration for @a errorPWM::periodFileError status */
			dutyFileErr	= 1,	/*!< enumeration for @a errorPWM::dutyFileError status */
			runFileErr	= 2,	/*!< enumeration for @a errorPWM::runFileError status */
			polarityFileErr	= 3,	/*!< enumeration for @a errorPWM::polarityFileError status */
			outOfRangeErr	= 4,	/*!< enumeration for @a errorPWM::outOfRange status */
			dtErr		= 5,	/*!< enumeration for @a errorCorePWM::dtError status */
			dtSubSystemErr	= 6,	/*!< enumeration for @a errorCorePWM::dtSsError status */
			pwmTestErr	= 7,	/*!< enumeration for @a errorCorePWM::pwmTestError status */
			initializeErr	= 8,	/*!< enumeration for @a errorCorePWM::initializeError status */
			cpmgrErr	= 9,	/*!< enumeration for @a errorCore::capeMgrError status */
			ocpErr		= 10	/*!< enumeration for @a errorCore::ocpError status */
		};


		/*! @brief Constructor of BlackPWM class.
		*
		* This function initializes errorPWM struct, calls triggerInitialization() function for
		* generating pwm signal and prints this function's return value for informing user.
		* Then it sets file paths of period, duty, polarity and run files.
		* @param [in] pwm		pin type pwm name (enum)
		* @sa triggerInitialization()
		* @sa pwm_pin_name
		*/
				BlackPWM(pwm_pin_name pwm);

		/*! @brief Constructor of BlackPWM class.
		*
		* This function initializes errorPWM struct, calls triggerInitialization() function for
		* generating pwm signal and prints this function's return value for informing user.
		* Then it sets file paths of period, duty, polarity and run files.
		* @param [in] pwm_bus		bus type pwm name (enum)
		* @sa triggerInitialization()
		* @sa pwm_bus_name
		*/
				BlackPWM(pwm_bus_name pwm_bus);

		/*! @brief Destructor of BlackPWM class.
		*
		*/
		virtual 	~BlackPWM();

		/*! @brief Exports percentage value of duty cycle.
		*
		* This function calls getNumericPeriodValue() and getNumericDutyValue() functions for
		* finding out period and duty values of pwm. After do that, it calculates percentage value.
		*  @return @a String type percentage value.
		*  @sa getNumericPeriodValue()
		*  @sa getNumericDutyValue()
		*/
		std::string	getValue();

		/*! @brief Exports period value of pwm signal.
		*
		* This function reads specified file from path, where defined at BlackPWM::periodPath variable.
		* This file holds pwm period value at nanosecond (ns) level.
		*  @return @a string type period value. If file opening fails, it returns error message.
		*/
		std::string	getPeriodValue();

		/*! @brief Exports duty value of pwm signal.
		*
		* This function reads specified file from path, where defined at BlackPWM::dutyPath variable.
		* This file holds pwm duty value at nanosecond (ns) level.
		*  @return @a string type duty value. If file opening fails, it returns error message.
		*/
		std::string	getDutyValue();

		/*! @brief Exports run value of pwm signal.
		*
		* This function reads specified file from path, where defined at BlackPWM::runPath variable.
		* This file holds pwm run value. It only can be 1 or 0.
		*  @return @a string type run value. If file opening fails, it returns error message.
		*/
		std::string	getRunValue();

		/*! @brief Exports polarity value of pwm signal.
		*
		* This function reads specified file from path, where defined at BlackPWM::polarityPath variable.
		* This file holds pwm polarity value. It only can be 1 or 0.
		*  @return @a string type polarity value. If file opening fails, it returns error message.
		*/
		std::string	getPolarityValue();

		/*! @brief Exports numeric percentage value of duty cycle.
		*
		* This function calls getNumericPeriodValue() and getNumericDutyValue() functions, for finding
		* out the period and duty values of pwm. After do that it calculates percentage value.
		*  @return @a float type percentage value.
		*  @sa getNumericPeriodValue()
		*  @sa getNumericDutyValue()
		*/
		float		getNumericValue();

		/*! @brief Exports numeric period value of pwm signal.
		*
		* This function calls getPeriodValue() function, for finding out the period value.
		* After do that, this period value is converted to uint32_t type by using strtoimax() function.
		* @return @a uint32_t type period value.
		* @sa getPeriodValue()
		*/
		uint32_t	getNumericPeriodValue();

		/*! @brief Exports numeric duty value of pwm signal.
		*
		* This function calls getDutyValue() function, for finding out the duty value. After
		* do that, this duty value is converted to uint32_t type by using strtoimax() function.
		* @return @a uint32_t type duty value.
		* @sa getDutyValue()
		*/
		uint32_t	getNumericDutyValue();


		/*! @brief Sets percentage value of duty cycle.
		*
		* If input parameter is in range (from 0 to 100), this function changes duty value
		* without changing period value. For calculating new duty value, the current period
		* multiplies by entered percentage and this product subtracts from period.
		* After do that, this calculated value is saved to duty file.
		* @param [in] percentage new percantage value(float type)
		* @return True if setting new value is successful, else false.
		*/
		bool		setDutyPercent(float percentage);

		/*! @brief Sets period value of pwm signal.
		*
		* If input parameter is in range (from 0 to 10^9 or greater than current duty value),
		* this function changes period value by saving entered value to period file.
		* @param [in] period new period value(uint32_t type)
		* @return True if setting new period value is successful, else false.
		*/
		bool		setPeriodTime(uint32_t period);

		/*! @brief Sets space time value of pwm signal.
		*
		* If input parameter is in range (from 0 to current period value), this function
		* changes duty value by saving entered value to duty file.
		* @param [in] space new space time(uint32_t type)
		* @return True if setting new value is successful, else false.
		*/
		bool		setSpaceRatioTime(uint32_t space);

		/*! @brief Sets load time value of pwm signal.
		*
		* If input parameter is in range (from 0 to current period value), this function
		* changes duty value. For calculating new duty value, the entered value subtracts
		* from the current period. After do that, this calculated value is saved to@n
		* duty file.
		* @param [in] load new load time(uint32_t type)
		* @return True if setting new value is successful, else false.
		*/
		bool		setLoadRatioTime(uint32_t load);

		/*! @brief Sets polarity of pwm signal.
		*
		* This function sets polarity value to 1 or 0. The input parameter is converted to 1 or 0
		* and this value is saved to polarity file.
		* @param [in] polarity new polarity value(enum)
		* @return True if setting new polarity is successful, else false.
		* @sa pwm_polarity
		*/
		bool		setPolarity(pwm_polarity polarity);

		/*! @brief Sets run state of pwm signal.
		*
		* This function sets run value to 1 or 0. The input parameter is converted to 1 or 0 and
		* this value is saved to run file.
		* @param [in] state new run value(enum)
		* @return True if setting new run state is successful, else false.
		* @sa pwm_value
		*/
		bool		setRunState(pwm_value state);

		/*! @brief Toggles run state of pwm signal.
		*
		* This function sets run value to 1 or 0, by value of current state. This new value is
		* saved to run file.
		*/
		void		toggleRunState();

		/*! @brief Toggles polarity type of pwm signal.
		*
		* This function sets polarity value to 1 or 0, by value of current polarity. This new
		* value is saved to polarity file.
		*/
		void		tooglePolarity();

		/*! @brief Checks run state of pwm signal.
		*
		* This function calls getRunValue() function and evaluates return value.
		* @return False if return value equals to 0, else true.
		* @sa getRunValue()
		*/
		bool		isRunning();

		/*! @brief Checks polarity of pwm signal.
		*
		* This function calls getPolarityValue() function and evaluates return value.
		* @return True if return value equals to 0, else false.
		* @sa getPolarityValue()
		*/
		bool		isPolarityStraight();

		/*! @brief Checks polarity state of pwm signal.
		*
		* This function calls getPolarityValue() function and evaluates return value.
		* @return False if return value equals to 0, else true.
		* @sa getPolarityValue()
		*/
		bool		isPolarityReverse();

		/*! @brief Is used for general debugging.
		*
		* @return True if any error occured, else false.
		* @sa errorPWM
		*/
		bool 		fail();

		/*! @brief Is used for specific debugging.
		*
		* You can use this function, after call BlackPWM member functions in your code. The
		* input parameter is used for finding out status of selected error.
		* @param [in] f		specific error type (enum)
		* @return Value of @a selected error.
		* @sa errorPWM
		*/
		bool 		fail(BlackPWM::flags f);
};
// ########################################### BLACKPWM DECLARATION STARTS ############################################ //









// ######################################### BLACKCOREGPIO DECLARATION STARTS ######################################### //

/*! @brief Preparation phase of Beaglebone Black, for using gpio pins.
 *
 *	This class is core of the BlackGPIO class. It includes private functions which set Beaglebone
 *	Black for using gpio pins, and protected functions which are using for triggering initialization from
 *	derived class and pass variables to derived class.
 */
class BlackCoreGPIO : private BlackCore
{
	private:
		errorCoreGPIO	*gpioCoreError;		/*!< @brief is used to hold the errors of BlackCoreGPIO class */
		int		pinNumericName;		/*!< @brief is used to hold the selected pin number */
		int		pinNumericType;		/*!< @brief is used to hold the selected pin type */
		std::string	expPath;		/*!< @brief is used to hold the @a export file path */
		std::string	directionPath;		/*!< @brief is used to hold the @a direction file path */
		std::string	unExpPath;		/*!< @brief is used to hold the @a unexport file path */
		bool		isInitializeBefore;	/*!< @brief is used to hold initialization status */


		/*! @brief Device tree loading is not necessary for using GPIO feature.
		*
		*  But this function have to declare in this class again. Because it is a pure virtual
		*  function. It does nothing.
		*  @return false all time.
		*/
		bool		loadDeviceTree();

		/*! @brief Performs initialization for using Beaglebone Black's gpio pins.
		*
		*  This function sets filename variables, by value of input pin name variable.
		*  Then calls doExport() function and if it returns true, calls setDirection() function.
		*  This function only can be called from triggerInitialization() function.
		*  @param [in] pin gpio pin name (enum),(GPIO_x)
		*  @param [in] type gpio pin type (enum),(input/output)
		*  @return @a string type fail or successful message.
		*  @sa doExport()
		*  @sa setDirection()
		*  @sa triggerInitialization()
		*/
		std::string	initialize(gpio_name pin,gpio_type type);

		/*! @brief Exports pin.
		*
		*  This function exports pin to use it. This step is necessary.
		*  @return True if exporting is successful, else false.
		*/
		bool 		doExport();

		/*! @brief Sets the pin direction.
		*
		*  This function sets pin direction to input or output. Pin directions are input at default.
		*  @return True if setting direction is successful, else false.
		*/
		bool 		setDirection();

		/*! @brief Unexports pin to release it.
		*
		*  This function is reverse of pin exporting. But this step is not necessary.
		*  @return True if unexporting is successful, else false.
		*/
		bool 		doUnexport();

	protected:

		/*! @brief Executes initialization.
		*
		*  This function checks pin file, to ensure about pin is exported or not, and then checks
		*  isInitializeBefore variable. Then it performs initialization or does nothing,
		*  by value of this variable.
		*  @param [in] pin gpio pin name (enum),(GPIO_x)
		*  @param [in] type gpio pin type (enum),(input/output)
		*  @return initialize() function's return value or fail message.
		*  @sa initialize()
		*  @sa isInitializeBefore
		*/
		std::string	triggerInitialization(gpio_name pin,gpio_type type);

		/*! @brief Exports direction file path to derived class.
		*
		*  @return BlackCoreGPIO::directionPath variable.
		*/
		std::string	getDirectionFilePath();

		/*! @brief Exports errorCoreGPIO struct to derived class.
		*
		*  @return errorCoreGPIO struct pointer.
		*/
		errorCoreGPIO	*getErrorsFromCoreGPIO();

	public:

		/*! @brief Constructor of BlackCoreGPIO class.
		*
		* Initializes errorCoreGPIO struct and isInitializeBefore variable.
		*/
				BlackCoreGPIO();


		/*! @brief Destructor of BlackCoreGPIO class.
		*
		* This function unexports pin.
		*/
		virtual 	~BlackCoreGPIO();

		/*! @brief First declaration of this function.
		*/
		virtual std::string getValue() = 0;

};
// ########################################## BLACKCOREGPIO DECLARATION ENDS ########################################## //










// ########################################### BLACKGPIO DECLARATION STARTS ########################################### //

/*! @brief Interacts with end user, to use GPIO pins.
 *
 *	This class is end node to use GPIO. End users interact with
 *	gpio pins from this class. It includes public functions to set and get properties of GPIO pins.
 */
class BlackGPIO : virtual private BlackCoreGPIO
{
	private:
		errorGPIO	*gpioErrors;	/*!< @brief is used to hold the errors of BlackGPIO class */
		gpio_name 	pinName;	/*!< @brief is used to hold the selected GPIO pin name */
		gpio_type	pinType;	/*!< @brief is used to hold the selected GPIO pin type */
		std::string	valuePath;	/*!< @brief is used to hold the value file path */

		/*! @brief Checks the export state of GPIO pin.
		*
		* This function reads specified file from path, where defined at BlackGPIO::valuePath variable.
		* If this file can open successfully, this means pin is exported successfully.
		* @return False if file opening fails, else true.
		*/
		bool 		isExported();

		/*! @brief Checks direction of GPIO pin.
		*
		* This function reads specified file from path, where defined at BlackGPIO::directionPath
		* variable.
		* @return True if direction file can open successfully and its value is equal to defined direction when
		* class initialization, else false.
		*/
		bool 		isDirectionSet();

		/*! @brief Checks ready state of GPIO pin.
		*
		* This function calls isExported() and isDirectionSet() functions and evaluates return
		* values of these.
		* @return True if both functions return true, else false.
		* @sa isExported()
		* @sa isDirectionSet()
		*/
		bool 		isReady();


	public:

		/*!
		* This enum is used to define GPIO debugging flags.
		*/
		enum flags		
		{	
			exportFileErr		= 0,	/*!< enumeration for @a errorCoreGPIO::exportFileError status */
			exportErr		= 1,	/*!< enumeration for @a errorGPIO::exportError status */
			directionFileErr	= 2,	/*!< enumeration for @a errorCoreGPIO::directionFileError status */
			directionErr		= 3,	/*!< enumeration for @a errorGPIO::directionError status */
			readErr			= 4,	/*!< enumeration for @a errorGPIO::readError status */
			writeErr		= 5,	/*!< enumeration for @a errorGPIO::writeError status */
			forcingErr		= 6,	/*!< enumeration for @a errorGPIO::forcingError status */
			initializeErr		= 7	/*!< enumeration for @a errorCoreGPIO::initializeError status */
		};

		/*! @brief Constructor of BlackGPIO class.
		*
		* This function initializes errorGPIO struct, calls triggerInitialization() function for
		* generating GPIO pin, and prints this function's return value for informing user.
		* Then it sets value file path.
		* @param [in] pn		gpio pin name(enum)
		* @param [in] pt		gpio pin type(enum)
		* @sa triggerInitialization()
		* @sa gpio_name
		* @sa gpio_type
		*/
				BlackGPIO(gpio_name pn, gpio_type pt);

		/*! @brief Destructor of BlackGPIO class.
		*
		*/
		virtual 	~BlackGPIO();

		/*! @brief Exports value of gpio pin.
		*
		* This function checks pin ready state by calling isReady() function. If pin is ready, it reads
		* specified file from path, where defined at BlackGPIO::valuePath variable. This file
		* holds gpio pin value.
		*  @return @a string type GPIO pin value. If file opening fails or pin isn't ready, it returns
		*  error message.
		*/
		std::string	getValue();

		/*! @brief Exports name of gpio pin.
		*
		*  @return BlackGPIO::pinName variable.
		*/
		gpio_name	getName();

		/*! @brief Exports type of gpio pin.
		*
		*  @return BlackGPIO::pinType variable.
		*/
		gpio_type	getType();

		/*! @brief Sets value of GPIO pin.
		*
		* If pin type is output and pin is ready, this function sets pin value to 1 or 0. The input
		* parameter is converted to 1 or 0 and this value is saved to value file.
		* @param [in] v new pin value(enum)
		* @return True if setting new value is successful, else false.
		* @sa gpio_value
		*/
		bool 		setValue(gpio_value v);

		/*! @brief Checks value of GPIO pin.
		*
		* This function calls getValue() function and evaluates return value.
		* @return False if return value equals 0, else true.
		* @sa getValue()
		*/
		bool		isHigh();

		/*! @brief Toggles value of GPIO pin.
		*
		* If pin type is output, this function sets pin value to 1 or 0, by value of current state.
		* This new value is saved to value file.
		*/
		void 		toggleValue();

		/*! @brief Is used for general debugging.
		*
		* @return True if any error occured, else false.
		* @sa errorGPIO
		*/
		bool 		fail();

		/*! @brief Is used for specific debugging.
		*
		* You can use this function, after call BlackGPIO member functions in your code. The
		* input parameter is used for finding out status of selected error.
		* @param [in] f		specific error type (enum)
		* @return Value of @a selected error.
		* @sa errorGPIO
		*/
		bool 		fail(BlackGPIO::flags f);
};
// ############################################ BLACKGPIO DECLARATION ENDS ############################################ //


#endif /* BLACKLIB_H_ */
