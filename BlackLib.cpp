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


#include "BlackLib.h"





/*! @brief Uses for converting the different types variable to string type.
*
* @tparam T variable which will convert.
* @return String type value of your entered variable.
*/
template <typename T>
std::string	tostr(const T& t)
{
	std::ostringstream os;
	os << t;
	return os.str();
}








// ########################################### BLACKCORE DEFINITION STARTS ########################################### //
			BlackCore::BlackCore()
{
	this->coreErrors 		= new errorCore;
	this->coreErrors->capeMgrError 	= false;
	this->coreErrors->ocpError 	= false;

	this->findCapeMgrName();
	this->findOcpName();
	this->setSlotsFilePath();
}

			BlackCore::~BlackCore(){}

std::string	BlackCore::executeCommand(std::string command)
{
    FILE* pipe = popen(command.c_str(), "r");
    if ( pipe==NULL )
    {
    	return "ERROR";
    }

    char buffer[128];
    std::string result = "";

    while( !feof(pipe) )
    {
    	if( fgets(buffer, 128, pipe) != NULL )
    	{
    		result += buffer;
    	}
    }

    pclose(pipe);
    return result;
}

std::string	BlackCore::searchDirectory(std::string seachIn, std::string searchThis)
{
	std::string str;
	DIR *path;
	dirent *entry;

	path = opendir(seachIn.c_str());
	if( path != NULL  )
	{
		while( (entry = readdir(path)) != NULL)
		{
			if( entry->d_name[0] == '.')
			{
				continue;
			}

			str = entry->d_name;
			if(strstr(entry->d_name,searchThis.c_str()) != NULL )
			{
				closedir(path);
				return str;
			}
		}
	}
	closedir(path);

	return SEARCH_DIR_NOT_FOUND;
}

bool 		BlackCore::findCapeMgrName()
{
	std::string searchResult = this->searchDirectory("/sys/devices/","bone_capemgr.");

	if(searchResult == SEARCH_DIR_NOT_FOUND)
	{
		this->capeMgrName = "bone_capemgr." + DEFAULT_CAPE_MGR_NUMBER;
		this->coreErrors->capeMgrError = true;
		return false;
	}
	else
	{
	    this->capeMgrName = searchResult;
	    this->coreErrors->capeMgrError = false;
		return true;
	}
}

bool 		BlackCore::findOcpName()
{
	std::string searchResult = this->searchDirectory("/sys/devices/","ocp.");

	if(searchResult == SEARCH_DIR_NOT_FOUND)
	{
		this->ocpName = "ocp." + DEFAULT_OCP_NUMBER;
		this->coreErrors->ocpError = true;
		return false;
	}
	else
	{
	    this->ocpName = searchResult;
	    this->coreErrors->ocpError = false;
		return true;
	}
}

void		BlackCore::setSlotsFilePath()
{
	this->slotsFilePath = "/sys/devices/" + this->capeMgrName + "/slots";
}



std::string	BlackCore::searchDirectoryOcp(BlackCore::ocpSearch searchThis)
{
	std::string searchResult;
	std::string searchPath = "/sys/devices/" + this->getOcpName() + "/";

	switch(searchThis)
	{
		case ADC_helper:
		{
			searchResult = this->searchDirectory(searchPath,"helper.");
			break;
		}

		case PWM_P8_13:
		{
			searchResult = this->searchDirectory(searchPath,"pwm_test_P8_13.");
			break;
		}

		case PWM_P8_19:
		{
			searchResult = this->searchDirectory(searchPath,"pwm_test_P8_19.");
			break;
		}

		case PWM_P9_14:
		{
			searchResult = this->searchDirectory(searchPath,"pwm_test_P9_14.");
			break;
		}

		case PWM_P9_16:
		{
			searchResult = this->searchDirectory(searchPath,"pwm_test_P9_16.");
			break;
		}

		case PWM_P9_21:
		{
			searchResult = this->searchDirectory(searchPath,"pwm_test_P9_21.");
			break;
		}

		case PWM_P9_22:
		{
			searchResult = this->searchDirectory(searchPath,"pwm_test_P9_22.");
			break;
		}

		case PWM_P9_42:
		{
			searchResult = this->searchDirectory(searchPath,"pwm_test_P9_42.");
			break;
		}
	}


	if(searchResult == SEARCH_DIR_NOT_FOUND)
	{
		return SEARCH_DIR_NOT_FOUND;
	}
	else
	{
		return searchResult;
	}
}

errorCore 	*BlackCore::getErrorsFromCore()
{
	return (this->coreErrors);
}



std::string BlackCore::getCapeMgrName()
{
	return this->capeMgrName;
}

std::string	BlackCore::getOcpName()
{
	return this->ocpName;
}

std::string	BlackCore::getSlotsFilePath()
{
	return this->slotsFilePath;
}

// ############################################ BLACKCORE DEFINITION ENDS ############################################ //













// ######################################### BLACKCOREADC DEFINITION STARTS ########################################## //
BlackCoreADC::BlackCoreADC()
{
	this->adcCoreErrors 			= new errorCoreADC;
	this->adcCoreErrors->coreErrors 	= this->getErrorsFromCore();
	this->adcCoreErrors->helperError 	= false;
	this->adcCoreErrors->dtError 		= false;
	this->loadDeviceTree();
	this->findHelperName();
}

BlackCoreADC::~BlackCoreADC(){}


bool 		BlackCoreADC::loadDeviceTree()
{
	std::string file = this->getSlotsFilePath();
	std::ofstream slotsFile;
	slotsFile.open(file.c_str(),std::ios::out);
	if(slotsFile.fail())
	{
		slotsFile.close();
		this->adcCoreErrors->dtError = true;
		return false;
	}
	else
	{
		slotsFile << "cape-bone-iio";
		slotsFile.close();
		this->adcCoreErrors->dtError = false;
		return true;
	}
}

bool 		BlackCoreADC::findHelperName()
{
	std::string limitedSearchResult = this->searchDirectoryOcp(BlackCore::ADC_helper);

	if(limitedSearchResult == SEARCH_DIR_NOT_FOUND)
	{
		this->helperName = "helper." + DEFAULT_HELPER_NUMBER;
		this->adcCoreErrors->helperError = true;
		return false;
	}
	else
	{
		this->helperName = limitedSearchResult;
		this->adcCoreErrors->helperError = false;
		return true;
	}
}

std::string	BlackCoreADC::getHelperPath()
{
	std::string temp = "/sys/devices/" + this->getOcpName() + "/" + this->helperName;
	return temp;
}

errorCoreADC *BlackCoreADC::getErrorsFromCoreADC()
{
	return (this->adcCoreErrors);
}

// ########################################## BLACKCOREADC DEFINITION ENDS ########################################### //










// ########################################### BLACKADC DEFINITION STARTS ############################################ //
BlackADC::BlackADC(adc_name adc)
{
	this->adcErrors 		= new errorADC;
	this->adcErrors->adcCoreErrors 	= this->getErrorsFromCoreADC();
	this->adcErrors->readError 	= false;

	this->adcName 			= adc;
	this->ainPath 			= this->getHelperPath() + "/AIN" + tostr(this->adcName);

	if(this->adcErrors->adcCoreErrors->dtError)
	{
		std::cout << "Setting up analog slots failed.(AIN" << this->adcName << ")" << std::endl;
	}
	else
	{
		std::cout << "You can read analog value on AIN"  << this->adcName << std::endl;
	}
}


BlackADC::~BlackADC(){}


std::string BlackADC::getValue()
{
	std::ifstream adcValueFile;

	adcValueFile.open(ainPath.c_str(),std::ios::in);
	if(adcValueFile.fail())
	{
		std::string ret = "File couldn't open for read. (AIN" + tostr(this->adcName) + ")";

		adcValueFile.close();
		this->adcErrors->readError = true;
		return ret;
	}
	else
	{
		std::string readValue = "";
		adcValueFile >> readValue;

		adcValueFile.close();
		this->adcErrors->readError = false;
		return readValue;
	}
}

adc_name	BlackADC::getName()
{
	return this->adcName;
}


int 		BlackADC::getNumericValue()
{
	std::ifstream adcValueFile;

	adcValueFile.open(ainPath.c_str(),std::ios::in);
	if(adcValueFile.fail())
	{
		int ret = -1;

		adcValueFile.close();
		this->adcErrors->readError = true;
		return ret;
	}
	else
	{
		std::string readValueStr = "";
		int readValueInt;

		adcValueFile >> readValueStr;
		readValueInt = atoi(readValueStr.c_str());

		adcValueFile.close();
		this->adcErrors->readError = false;
		return readValueInt;
	}
}

float 		BlackADC::getParsedValue(digit_after_point mode)
{
	int valueInt 		= this->getNumericValue();
	float valueFloat 	= static_cast<float>(valueInt);

	if( mode == dap3 )
	{
		// shows 3 digit after point
		return (valueFloat)/1000;
	}

	if( mode == dap2 )
	{
		// shows 2 digit after point
		float tmp = round(valueFloat/10);
		return (tmp)/100;
	}


	if( mode == dap1 )
	{
		// shows 1 digit after point
		float tmp = round(valueFloat/100);
		return (tmp)/10;
	}

	return -1.0;
}

bool 		BlackADC::fail()
{
	return (this->adcErrors->adcCoreErrors->coreErrors->capeMgrError or
		this->adcErrors->adcCoreErrors->coreErrors->ocpError or
		this->adcErrors->adcCoreErrors->helperError or
		this->adcErrors->adcCoreErrors->dtError or
		this->adcErrors->readError
		);
}

bool 		BlackADC::fail(BlackADC::flags f)
{
	if(f==cpmgrErr)	{ return this->adcErrors->adcCoreErrors->coreErrors->capeMgrError;	}
	if(f==ocpErr)	{ return this->adcErrors->adcCoreErrors->coreErrors->ocpError;		}
	if(f==helperErr){ return this->adcErrors->adcCoreErrors->helperError;			}
	if(f==dtErr)	{ return this->adcErrors->adcCoreErrors->dtError;			}
	if(f==ReadErr)	{ return this->adcErrors->readError;					}

	return true;
}

// ############################################ BLACKADC DEFINITION ENDS ############################################# //












// ######################################### BLACKCOREPWM DEFINITION STARTS ########################################## //
BlackCorePWM::BlackCorePWM()
{
	this->pwmCoreErrors 				= new errorCorePWM;
	this->pwmCoreErrors->dtError 			= false;
	this->pwmCoreErrors->dtSsError 			= false;
	this->pwmCoreErrors->pwmTestError 		= false;
	this->pwmCoreErrors->initializeError		= false;
	this->pwmCoreErrors->coreErrors 		= this->getErrorsFromCore();
	this->isInitializeBefore			= false;
}

BlackCorePWM::~BlackCorePWM(){}



std::string	BlackCorePWM::triggerInitialization(pwm_pin_name pwm_pin)
{
	this->pwmName = this->parsePwmName(pwm_pin);

	if( this->pwmCoreErrors->pwmTestError )
	{
		this->pwmCoreErrors->initializeError 	= false;
		return this->initialize();
	}
	else
	{
		if( this->isInitializeBefore )
		{
			this->pwmCoreErrors->initializeError = true;
			return "You already initialize pwm " + this->pwmName + "\n";
		}
		else
		{
			this->pwmCoreErrors->initializeError = false;
			return this->initialize();
		}
	}
}


std::string	BlackCorePWM::triggerInitialization(pwm_bus_name pwm_pin)
{
	this->pwmName = this->parsePwmName( static_cast<pwm_pin_name>(pwm_pin) );

	if( this->pwmCoreErrors->pwmTestError )
	{
		this->pwmCoreErrors->initializeError = false;
		return this->initialize();
	}
	else
	{
		if( this->isInitializeBefore )
		{
			this->pwmCoreErrors->initializeError = true;
			return "You already initialize pwm " + this->pwmName + "\n";
		}
		else
		{
			this->pwmCoreErrors->initializeError = false;
			return this->initialize();
		}
	}
}

std::string	BlackCorePWM::initialize()
{
	this->isInitializeBefore = true;

	if( this->loadDeviceTree())
	{
		if( this->findPwmTestName() )
		{
			return ("You can generate PWM signal on "  + this->pwmName + "\n");
		}
		else
		{
			return ("Setting up PWM slots failed. (" + this->pwmName + ")\n");
		}
	}
	else
	{
		return ("Setting up PWM slots failed. (" + this->pwmName + ")\n");
	}
}

bool 		BlackCorePWM::loadDeviceTree()
{
	std::string file 		= this->getSlotsFilePath();
	this->dtboFileName 		= "bone_pwm_" + this->pwmName;

	std::ofstream slotsFile;

	slotsFile.open(file.c_str(),std::ios::out);
	if(slotsFile.fail())
	{
		slotsFile.close();
		this->pwmCoreErrors->dtSsError 	= true;
		this->pwmCoreErrors->dtError	= true;
		return false;
	}
	else
	{
		slotsFile << "am33xx_pwm";
		slotsFile.close();
		this->pwmCoreErrors->dtSsError	= false;
	}


	slotsFile.open(file.c_str(),std::ios::out);
	if(slotsFile.fail())
	{
		slotsFile.close();
		this->pwmCoreErrors->dtError	= true;
		return false;
	}
	else
	{
		slotsFile << this->dtboFileName;
		slotsFile.close();
		this->pwmCoreErrors->dtError	= false;
		return true;
	}
}

bool		BlackCorePWM::findPwmTestName()
{
	std::string limitedSearchResult;

	if(this->pwmName == "P8_13")
	{
		limitedSearchResult = this->searchDirectoryOcp(BlackCore::PWM_P8_13);
	}
	else if( this->pwmName == "P8_19")
	{
		limitedSearchResult = this->searchDirectoryOcp(BlackCore::PWM_P8_19);
	}
	else if( this->pwmName == "P9_14")
	{
		limitedSearchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_14);
	}
	else if( this->pwmName == "P9_16")
	{
		limitedSearchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_16);
	}
	else if( this->pwmName == "P9_21")
	{
		limitedSearchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_21);
	}
	else if( this->pwmName == "P9_22")
	{
		limitedSearchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_22);
	}
	else if( this->pwmName == "P9_42")
	{
		limitedSearchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_42);
	}
	else
	{
		limitedSearchResult = SEARCH_DIR_NOT_FOUND;
	}


	if(limitedSearchResult == SEARCH_DIR_NOT_FOUND)
	{
		this->pwmTestName = "pwm_test_" + this->pwmName + "." + DEFAULT_PWM_TEST_NUMBER;
		this->pwmCoreErrors->pwmTestError = true;
		return false;
	}
	else
	{
		this->pwmTestName = limitedSearchResult;
		this->pwmCoreErrors->pwmTestError = false;
		return true;
	}
}


std::string	BlackCorePWM::parsePwmName(pwm_pin_name parseThis)
{
	switch( static_cast<int>(parseThis) )
	{
		case 0:
		{
			return "P8_13";
			break;
		}
		case 1:
		{
			return "P8_19";
			break;
		}
		case 2:
		{
			return "P9_14";
			break;
		}
		case 3:
		{
			return "P9_16";
			break;
		}
		case 4:
		{
			return "P9_21";
			break;
		}
		case 5:
		{
			return "P9_22";
			break;
		}
		case 6:
		{
			return "P9_42";
			break;
		}
	}

	return "ERROR";
}

std::string	BlackCorePWM::getPwmName()
{
	return this->pwmName;
}

std::string	BlackCorePWM::getPwmTestPath()
{
	std::string temp = "/sys/devices/" + this->getOcpName() + "/" + this->pwmTestName;
	return temp;
}

errorCorePWM	*BlackCorePWM::getErrorsFromCorePWM()
{
	return (this->pwmCoreErrors);
}
// ########################################## BLACKCOREPWM DEFINITION ENDS ########################################### //












// ########################################### BLACKPWM DEFINITION STARTS ############################################ //
BlackPWM::BlackPWM(pwm_bus_name pwm_bus)
{
	this->pwmBusName 			= pwm_bus;
	this->pwmPinName 			= static_cast<pwm_pin_name>(pwm_bus);

	std::cout << this->triggerInitialization(pwm_bus);

	this->pwmErrors 			= new errorPWM;
	this->pwmErrors->pwmCoreErrors 		= this->getErrorsFromCorePWM();
	this->pwmErrors->dutyFileError 		= false;
	this->pwmErrors->periodFileError 	= false;
	this->pwmErrors->runFileError 		= false;
	this->pwmErrors->polarityFileError 	= false;
	this->pwmErrors->outOfRange 		= false;


	this->periodPath 			= this->getPwmTestPath() + "/period";
	this->dutyPath 				= this->getPwmTestPath() + "/duty";
	this->runPath 				= this->getPwmTestPath() + "/run";
	this->polarityPath 			= this->getPwmTestPath() + "/polarity";
}

BlackPWM::BlackPWM(pwm_pin_name pwm)
{
	this->pwmPinName 			= pwm;
	this->pwmBusName 			= static_cast<pwm_bus_name>(pwm);

	std::cout << this->triggerInitialization(pwm);

	this->pwmErrors 			= new errorPWM;
	this->pwmErrors->pwmCoreErrors 		= this->getErrorsFromCorePWM();
	this->pwmErrors->dutyFileError 		= false;
	this->pwmErrors->periodFileError 	= false;
	this->pwmErrors->runFileError 		= false;
	this->pwmErrors->polarityFileError 	= false;
	this->pwmErrors->outOfRange 		= false;


	this->periodPath 			= this->getPwmTestPath() + "/period";
	this->dutyPath 				= this->getPwmTestPath() + "/duty";
	this->runPath 				= this->getPwmTestPath() + "/run";
	this->polarityPath 			= this->getPwmTestPath() + "/polarity";
}

BlackPWM::~BlackPWM(){}




std::string	BlackPWM::getValue()
{
	float percent;
	percent = (static_cast<float>(this->getNumericPeriodValue()-this->getNumericDutyValue())) / this->getNumericPeriodValue();
	percent *= 100;
	return tostr(percent);
}

std::string	BlackPWM::getPeriodValue()
{
	std::ifstream periodValueFile;

	periodValueFile.open(this->periodPath.c_str(),std::ios::in);
	if(periodValueFile.fail())
	{
		std::string ret = "File couldn't open for read period. (" + this->getPwmName() + ")";

		periodValueFile.close();
		this->pwmErrors->periodFileError = true;
		return ret;
	}
	else
	{
		std::string readValue = "";
		periodValueFile >> readValue;

		periodValueFile.close();
		this->pwmErrors->periodFileError = false;
		return readValue;
	}
}

std::string BlackPWM::getDutyValue()
{
	std::ifstream dutyValueFile;

	dutyValueFile.open(this->dutyPath.c_str(),std::ios::in);
	if(dutyValueFile.fail())
	{
		std::string ret = "File couldn't open for read duty. (" + this->getPwmName() + ")";

		dutyValueFile.close();
		this->pwmErrors->dutyFileError = true;
		return ret;
	}
	else
	{
		std::string readValue = "";
		dutyValueFile >> readValue;

		dutyValueFile.close();
		this->pwmErrors->dutyFileError = false;
		return readValue;
	}
}

std::string BlackPWM::getRunValue()
{
	std::ifstream runValueFile;

	runValueFile.open(this->runPath.c_str(),std::ios::in);
	if(runValueFile.fail())
	{
		std::string ret = "File couldn't open for read pwm running status. (" + this->getPwmName() + ")";

		runValueFile.close();
		this->pwmErrors->runFileError = true;
		return ret;
	}
	else
	{
		std::string readValue = "";
		runValueFile >> readValue;

		runValueFile.close();
		this->pwmErrors->runFileError = false;
		return readValue;
	}
}

std::string BlackPWM::getPolarityValue()
{
	std::ifstream polarityValueFile;

	polarityValueFile.open(this->polarityPath.c_str(),std::ios::in);
	if(polarityValueFile.fail())
	{
		std::string ret = "File couldn't open for read polarity. (" + this->getPwmName() + ")";

		polarityValueFile.close();
		this->pwmErrors->polarityFileError = true;
		return ret;
	}
	else
	{
		std::string readValue = "";
		polarityValueFile >> readValue;

		polarityValueFile.close();
		this->pwmErrors->polarityFileError = false;
		return readValue;
	}
}

float		BlackPWM::getNumericValue()
{
	float percent;
	percent = (static_cast<float>(this->getNumericPeriodValue()-this->getNumericDutyValue())) / this->getNumericPeriodValue();
	percent *= 100;
	return percent;
}

uint32_t 	BlackPWM::getNumericPeriodValue()
{
	std::string periodStr = this->getPeriodValue();
	return strtoimax(periodStr.c_str(),nullptr,10);
}

uint32_t 	BlackPWM::getNumericDutyValue()
{
	std::string dutyStr = this->getDutyValue();
	return strtoimax(dutyStr.c_str(),nullptr,10);
}


bool		BlackPWM::isRunning()
{
	std::string runningStr = this->getRunValue();
	if( runningStr[0] == '0' )
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool		BlackPWM::isPolarityStraight()
{
	std::string polarityStr = this->getPolarityValue();
	if( polarityStr[0] == '0' )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool		BlackPWM::isPolarityReverse()
{
	std::string polarityStr = this->getPolarityValue();
	if( polarityStr[0] == '0' )
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool 		BlackPWM::setDutyPercent(float percantage)
{
	if( percantage > 100.0 or percantage < 0.0 )
	{
		this->pwmErrors->outOfRange = true;
		return false;
	}
	else
	{
		this->pwmErrors->outOfRange = false;
		percantage 					= percantage / 100 ;

		uint32_t period 			= this->getNumericPeriodValue();
		uint32_t writeThis 			= period - static_cast<uint32_t>( (static_cast<float>(period)) * percantage );

		std::ofstream dutyFile;
		dutyFile.open(this->dutyPath.c_str(),std::ios::out);
		if(dutyFile.fail())
		{
			dutyFile.close();
			this->pwmErrors->dutyFileError = true;
			return false;
		}
		else
		{
			dutyFile << writeThis;
			dutyFile.close();
			this->pwmErrors->dutyFileError = false;
			return true;
		}
	}
}

bool		BlackPWM::setPeriodTime(uint32_t period)
{
	uint32_t writeThis = period;

	if( writeThis > 1000000000 or writeThis < 0 or writeThis < this->getNumericDutyValue())
	{
		this->pwmErrors->outOfRange = true;
		return false;
	}
	else
	{
		this->pwmErrors->outOfRange = false;
		std::ofstream periodFile;
		periodFile.open(this->periodPath.c_str(),std::ios::out);
		if(periodFile.fail())
		{
			periodFile.close();
			this->pwmErrors->periodFileError = true;
			return false;
		}
		else
		{
			periodFile << writeThis;
			periodFile.close();
			this->pwmErrors->periodFileError = false;
			return true;
		}
	}
}

bool		BlackPWM::setSpaceRatioTime(uint32_t space)
{
	uint32_t writeThis = space;

	if( writeThis > this->getNumericPeriodValue() or writeThis < 0)
	{
		this->pwmErrors->outOfRange = true;
		return false;
	}
	else
	{
		this->pwmErrors->outOfRange = false;
		std::ofstream dutyFile;
		dutyFile.open(this->dutyPath.c_str(),std::ios::out);
		if(dutyFile.fail())
		{
			dutyFile.close();
			this->pwmErrors->dutyFileError = true;
			return false;
		}
		else
		{
			dutyFile << writeThis;
			dutyFile.close();
			this->pwmErrors->dutyFileError = false;
			return true;
		}
	}
}

bool		BlackPWM::setLoadRatioTime(uint32_t load)
{
	uint32_t writeThis = this->getNumericPeriodValue() - load;

	if( writeThis > this->getNumericPeriodValue() or writeThis < 0)
	{
		this->pwmErrors->outOfRange = true;
		return false;
	}
	else
	{
		this->pwmErrors->outOfRange = false;;
		std::ofstream dutyFile;
		dutyFile.open(this->dutyPath.c_str(),std::ios::out);
		if(dutyFile.fail())
		{
			dutyFile.close();
			this->pwmErrors->dutyFileError = true;
			return false;
		}
		else
		{
			dutyFile << writeThis;
			dutyFile.close();
			this->pwmErrors->dutyFileError = false;
			return true;
		}
	}
}

bool		BlackPWM::setPolarity(pwm_polarity polarity)
{
	int writeThis;

	if(polarity == reverse )
	{
		writeThis = 1;
	}

	if( polarity == straight )
	{
		writeThis = 0;
	}

	std::ofstream polarityFile;
	polarityFile.open(this->polarityPath.c_str(),std::ios::out);
	if(polarityFile.fail())
	{
		polarityFile.close();
		this->pwmErrors->polarityFileError = true;
		return false;
	}
	else
	{
		polarityFile << writeThis;
		polarityFile.close();
		this->pwmErrors->polarityFileError = false;
		return true;
	}
}

bool		BlackPWM::setRunState(pwm_value state)
{
	int writeThis;

	if(state == run)
	{
		writeThis = 1;
	}
	else
	{
		writeThis = 0;
	}

	std::ofstream runFile;
	runFile.open(this->runPath.c_str(),std::ios::out);
	if(runFile.fail())
	{
		runFile.close();
		this->pwmErrors->runFileError = true;
		return false;
	}
	else
	{
		runFile << writeThis;
		runFile.close();
		this->pwmErrors->runFileError = false;
		return true;
	}
}

void		BlackPWM::toggleRunState()
{
	if(this->isRunning())
	{
		this->setRunState(stop);
	}
	else
	{
		this->setRunState(run);
	}
}

void		BlackPWM::tooglePolarity()
{
	if( this->getPolarityValue() == "0" )
	{
		this->setPolarity(reverse);
	}
	else
	{
		this->setPolarity(straight);
	}
}

bool 		BlackPWM::fail()
{
	return (this->pwmErrors->outOfRange or
		this->pwmErrors->runFileError or
		this->pwmErrors->dutyFileError or
		this->pwmErrors->periodFileError or
		this->pwmErrors->polarityFileError or
		this->pwmErrors->pwmCoreErrors->dtError or
		this->pwmErrors->pwmCoreErrors->dtSsError or
		this->pwmErrors->pwmCoreErrors->pwmTestError or
		this->pwmErrors->pwmCoreErrors->initializeError or
		this->pwmErrors->pwmCoreErrors->coreErrors->ocpError or
		this->pwmErrors->pwmCoreErrors->coreErrors->capeMgrError
		);
}

bool 		BlackPWM::fail(BlackPWM::flags f)
{
	if(f==outOfRangeErr)	{ return this->pwmErrors->outOfRange;					}
	if(f==runFileErr)	{ return this->pwmErrors->runFileError;					}
	if(f==dutyFileErr)	{ return this->pwmErrors->dutyFileError;				}
	if(f==periodFileErr)	{ return this->pwmErrors->periodFileError;				}
	if(f==polarityFileErr)	{ return this->pwmErrors->polarityFileError;				}
	if(f==dtErr)		{ return this->pwmErrors->pwmCoreErrors->dtError;			}
	if(f==dtSubSystemErr)	{ return this->pwmErrors->pwmCoreErrors->dtSsError;			}
	if(f==pwmTestErr)	{ return this->pwmErrors->pwmCoreErrors->pwmTestError;			}
	if(f==initializeErr)	{ return this->pwmErrors->pwmCoreErrors->initializeError;		}
	if(f==ocpErr)		{ return this->pwmErrors->pwmCoreErrors->coreErrors->ocpError;		}
	if(f==cpmgrErr)		{ return this->pwmErrors->pwmCoreErrors->coreErrors->capeMgrError;	}

	return true;
}

// ########################################### BLACKPWM DEFINITION STARTS ############################################ //









// ######################################### BLACKCOREGPIO DEFINITION STARTS ######################################### //
BlackCoreGPIO::BlackCoreGPIO()
{
	this->pinNumericName 			= -1;
	this->pinNumericType 			= -1;
	this->gpioCoreError 			= new errorCoreGPIO;
	this->gpioCoreError->coreErrors 	= this->getErrorsFromCore();
	this->gpioCoreError->directionFileError = false;
	this->gpioCoreError->exportFileError	= false;
	this->gpioCoreError->initializeError	= false;
	this->isInitializeBefore 		= false;

}

BlackCoreGPIO::~BlackCoreGPIO()
{
	if( this->doUnexport() )
	{
		std::cout << "Finalization of pin " << this->pinNumericName << " is successful.\n";
	}
	else
	{
		std::cout << "Finalization of pin " << this->pinNumericName << " failed.\n";
	}
}

bool		BlackCoreGPIO::loadDeviceTree()
{
	return false;
}



bool 		BlackCoreGPIO::doExport()
{
	std::ofstream expFile;

	expFile.open(expPath.c_str(),std::ios::out);
	if(expFile.fail())
	{
		expFile.close();
		this->gpioCoreError->exportFileError = true;
		return false;
	}
	else
	{
		expFile << this->pinNumericName;

		expFile.close();
		this->gpioCoreError->exportFileError = false;
		return true;
	}
}

bool 		BlackCoreGPIO::setDirection()
{
	std::ofstream directionFile;

	directionFile.open(directionPath.c_str(), std::ios::out);
	if(directionFile.fail())
	{
		directionFile.close();
		this->gpioCoreError->directionFileError = true;
		return false;
	}
	else
	{
		if(this->pinNumericType == static_cast<int>(input))
		{
			directionFile << "in";
		}else
		{
			directionFile << "out";
		}

		directionFile.close();
		this->gpioCoreError->directionFileError = false;
		return true;
	}
}

bool 		BlackCoreGPIO::doUnexport()
{
	std::ofstream unExpFile;

	unExpFile.open(this->unExpPath.c_str(), std::ios::out);
	if(unExpFile.fail())
	{
		unExpFile.close();
		return false;
	}
	else
	{
		unExpFile << this->pinNumericName;
		unExpFile.close();
		return true;
	}
}




std::string	BlackCoreGPIO::initialize(gpio_name pin,gpio_type type)
{
	this->isInitializeBefore 	= true;

	this->pinNumericName 		= static_cast<int>(pin);
	this->pinNumericType 		= static_cast<int>(type);
	std::string pinStr 		= tostr(this->pinNumericName);

	this->expPath 			= "/sys/class/gpio/export";
	this->unExpPath 		= "/sys/class/gpio/unexport";
	this->directionPath		= "/sys/class/gpio/gpio" + pinStr + "/direction";


	if(this->doExport())
	{
		std::string ret		= "Pin " + pinStr + " exported successfully.\n";
		if(this->setDirection())
		{
			ret += "Pin " + pinStr + " set direction successfully.\n\n";
			return ret;
		}
		else
		{
			ret +=	"Pin " + pinStr + " setting direction failed.\n\n";
			return ret;
		}

	}
	else
	{
		std::string ret 	= "Pin " + pinStr + " exporting failed.\n" ;
		ret +=	"Pin " + pinStr + " setting direction failed.\n\n";
		return ret;
	}
}

std::string	BlackCoreGPIO::triggerInitialization(gpio_name pin,gpio_type type)
{
	std::string tempDirectionPath = "/sys/class/gpio/gpio"+ tostr(static_cast<int>(pin)) + "/direction";

	std::ifstream checkDirectionFile;
	checkDirectionFile.open(tempDirectionPath.c_str(), std::ios::in|std::ios::binary);

	if(checkDirectionFile.fail() )
	{
		checkDirectionFile.close();
		this->gpioCoreError->initializeError = false;
		return this->initialize(pin,type);
	}
	else
	{
		checkDirectionFile.close();
		if( this->isInitializeBefore )
		{
			this->gpioCoreError->initializeError = true;
			return ("You already initialize pin " + tostr(static_cast<int>(pin)) + "\n");
		}
		else
		{
			this->gpioCoreError->initializeError = false;
			return this->initialize(pin,type);
		}
	}
}

std::string	BlackCoreGPIO::getDirectionFilePath()
{
	return this->directionPath;
}

errorCoreGPIO	*BlackCoreGPIO::getErrorsFromCoreGPIO()
{
	return (this->gpioCoreError);
}

// ########################################## BLACKCOREGPIO DEFINITION ENDS ########################################## //










// ########################################### BLACKGPIO DEFINITION STARTS ########################################### //
BlackGPIO::BlackGPIO(gpio_name pin , gpio_type type)
{
	this->pinName 				= pin;
	this->pinType 				= type;

	this->gpioErrors 			= new errorGPIO;
	this->gpioErrors->gpioCoreErrors 	= this->getErrorsFromCoreGPIO();
	this->gpioErrors->directionError	= false;
	this->gpioErrors->exportError		= false;
	this->gpioErrors->forcingError		= false;
	this->gpioErrors->readError		= false;
	this->gpioErrors->writeError		= false;


	std::cout << this->triggerInitialization(this->pinName,this->pinType);

	this->valuePath 			= "/sys/class/gpio/gpio" + tostr(static_cast<int>(this->pinName)) + "/value";
}

BlackGPIO::~BlackGPIO(){}


bool 		BlackGPIO::isReady()
{
	if( this->isExported() and this->isDirectionSet() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool 		BlackGPIO::isExported()
{
	std::ifstream exportCheck;

	exportCheck.open(valuePath.c_str(),std::ios::in|std::ios::binary);
	if(exportCheck.fail())
	{
		this->gpioErrors->exportError = true;
		return false;
	}
	else
	{
		this->gpioErrors->exportError = false;
		exportCheck.close();
		return true;
	}
}

bool 		BlackGPIO::isDirectionSet()
{
	std::ifstream directionCheck;

	directionCheck.open((this->getDirectionFilePath()).c_str(), std::ios::in|std::ios::binary);
	if(directionCheck.fail())
	{
		directionCheck.close();
		this->gpioErrors->directionError = true;
		return false;
	}
	else
	{
		std::string readValue = "";
		directionCheck >> readValue;

		if( (this->pinType == input and readValue=="in") or (this->pinType == output and readValue=="out") )
		{
			directionCheck.close();
			this->gpioErrors->directionError = false;
			return true;
		}else
		{
			directionCheck.close();
			this->gpioErrors->directionError = true;
			return false;
		}
	}
}


std::string BlackGPIO::getValue()
{
	if(this->isReady())
	{
		std::ifstream valueFile;

		valueFile.open(valuePath.c_str(),std::ios::in);
		if(valueFile.fail())
		{
			std::string ret = "File couldn't open for read.";

			valueFile.close();
			this->gpioErrors->readError = true;
			return ret;
		}
		else
		{
			std::string readValue = "";
			valueFile >> readValue;

			valueFile.close();
			this->gpioErrors->readError = false;
			return readValue;
		}
	}
	else
	{
		std::string ret = "Pin isn't ready for get value.";
		this->gpioErrors->readError = true;
		return ret;
	}
}


gpio_name	BlackGPIO::getName()
{
	return this->pinName;
}

gpio_type	BlackGPIO::getType()
{
	return this->pinType;
}

bool 		BlackGPIO::setValue(gpio_value status)
{
	if ( this->pinType == output )
	{
		this->gpioErrors->forcingError = false;
		if(this->isReady())
		{
			std::ofstream valueFile;
			valueFile.open(valuePath.c_str(),std::ios::out);
			if(valueFile.fail())
			{
				valueFile.close();
				this->gpioErrors->writeError = true;
				return false;
			}
			else
			{
				if(status == high )
				{
					valueFile << "1";
				}else
				{
					valueFile << "0";
				}

				valueFile.close();
				this->gpioErrors->writeError = false;
				return true;
			}
		}
		else
		{
			this->gpioErrors->writeError = true;
			return false;
		}

	}
	else
	{
		this->gpioErrors->writeError = true;
		this->gpioErrors->forcingError = true;
		return false;
	}
}

bool 		BlackGPIO::isHigh()
{
	std::string read = this->getValue();
	if( read == "0")
	{
		return false;
	}
	else
	{
		return true;
	}
}

void 		BlackGPIO::toggleValue()
{
	if( this->pinType == output )
	{
		this->gpioErrors->forcingError = false;
		if(this->isHigh())
		{
			this->setValue(low);
		}
		else
		{
			this->setValue(high);
		}
	}
	else
	{
		this->gpioErrors->forcingError = true;
	}
}

bool 		BlackGPIO::fail()
{
	return (this->gpioErrors->readError or
		this->gpioErrors->writeError or
		this->gpioErrors->exportError or
		this->gpioErrors->forcingError or
		this->gpioErrors->directionError
		);
}

bool 		BlackGPIO::fail(BlackGPIO::flags f)
{
	if(f==readErr)		{ return this->gpioErrors->readError;				}
	if(f==writeErr)		{ return this->gpioErrors->writeError;				}
	if(f==exportErr)	{ return this->gpioErrors->exportError;				}
	if(f==forcingErr)	{ return this->gpioErrors->forcingError;			}
	if(f==directionErr)	{ return this->gpioErrors->directionError;			}
	if(f==exportFileErr)	{ return this->gpioErrors->gpioCoreErrors->exportFileError;	}
	if(f==initializeErr)	{ return this->gpioErrors->gpioCoreErrors->initializeError;	}
	if(f==directionFileErr)	{ return this->gpioErrors->gpioCoreErrors->directionFileError;	}

	return true;
}

// ############################################ BLACKGPIO DECLARATION ENDS ############################################ //


