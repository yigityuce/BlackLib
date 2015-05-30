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



#include "BlackPWM.h"





namespace BlackLib
{

    // ######################################### BLACKCOREPWM DEFINITION STARTS ########################################## //
    BlackCorePWM::BlackCorePWM(pwmName pwm)
    {
        this->pwmPinName    = pwm;
        this->pwmCoreErrors = new errorCorePWM( this->getErrorsFromCore() );

        this->loadDeviceTree();

        this->pwmTestPath   = "/sys/devices/" + this->getOcpName() + "/" + this->findPwmTestName( this->pwmPinName );
    }


    BlackCorePWM::~BlackCorePWM()
    {
        delete this->pwmCoreErrors;
    }


    bool        BlackCorePWM::loadDeviceTree()
    {
        std::string file    = this->getSlotsFilePath();
        std::ofstream slotsFile;

        slotsFile.open(file.c_str(), std::ios::out);
        if(slotsFile.fail())
        {
            slotsFile.close();
            this->pwmCoreErrors->dtSsError  = true;
            this->pwmCoreErrors->dtError    = true;
            return false;
        }
        else
        {
            slotsFile << "am33xx_pwm";
            slotsFile.close();
            this->pwmCoreErrors->dtSsError  = false;
        }


        slotsFile.open(file.c_str(), std::ios::out);
        if(slotsFile.fail())
        {
            slotsFile.close();
            this->pwmCoreErrors->dtError    = true;
            return false;
        }
        else
        {
            slotsFile << ("bone_pwm_" + pwmNameMap[this->pwmPinName]);
            slotsFile.close();
            this->pwmCoreErrors->dtError    = false;
            return true;
        }
    }

    std::string BlackCorePWM::findPwmTestName(pwmName pwm)
    {
        std::string searchResult = SEARCH_DIR_NOT_FOUND;
        switch (pwm)
        {
            case P8_13:
            {
                searchResult = this->searchDirectoryOcp(BlackCore::PWM_P8_13);
                break;
            }

            case P8_19:
            {
                searchResult = this->searchDirectoryOcp(BlackCore::PWM_P8_19);
                break;
            }

            case P9_14:
            {
                searchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_14);
                break;
            }

            case P9_16:
            {
                searchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_16);
                break;
            }

            case P9_21:
            {
                searchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_21);
                break;
            }

            case P9_22:
            {
                searchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_22);
                break;
            }

            case P9_42:
            {
                searchResult = this->searchDirectoryOcp(BlackCore::PWM_P9_42);
                break;
            }
        };


        if( searchResult == SEARCH_DIR_NOT_FOUND )
        {
            this->pwmCoreErrors->pwmTestError = true;
            return PWM_TEST_NAME_NOT_FOUND;
        }
        else
        {
            this->pwmCoreErrors->pwmTestError = false;
            return searchResult;
        }
    }



    std::string BlackCorePWM::getPeriodFilePath()
    {
        return (this->pwmTestPath + "/period");
    }

    std::string BlackCorePWM::getDutyFilePath()
    {
        return (this->pwmTestPath + "/duty");
    }

    std::string BlackCorePWM::getRunFilePath()
    {
        return (this->pwmTestPath + "/run");
    }

    std::string BlackCorePWM::getPolarityFilePath()
    {
        return (this->pwmTestPath + "/polarity");
    }

    errorCorePWM *BlackCorePWM::getErrorsFromCorePWM()
    {
        return (this->pwmCoreErrors);
    }
    // ########################################## BLACKCOREPWM DEFINITION ENDS ########################################### //












    // ########################################### BLACKPWM DEFINITION STARTS ############################################ //
    BlackPWM::BlackPWM(pwmName pwm) : BlackCorePWM(pwm)
    {
        this->pwmErrors     = new errorPWM( this->getErrorsFromCorePWM() );

        this->periodPath    = this->getPeriodFilePath();
        this->dutyPath      = this->getDutyFilePath();
        this->runPath       = this->getRunFilePath();
        this->polarityPath  = this->getPolarityFilePath();
    }

    BlackPWM::~BlackPWM()
    {
        delete this->pwmErrors;
    }

    std::string BlackPWM::getValue()
    {
        double period   = static_cast<long double>( this->getNumericPeriodValue() );
        double duty     = static_cast<long double>( this->getNumericDutyValue() );

        return tostr(static_cast<float>( (1.0 - (duty / period )) * 100 ));
    }

    std::string BlackPWM::getPeriodValue()
    {
        std::ifstream periodValueFile;

        periodValueFile.open(this->periodPath.c_str(),std::ios::in);
        if(periodValueFile.fail())
        {
            periodValueFile.close();
            this->pwmErrors->periodFileError = true;
            return FILE_COULD_NOT_OPEN_STRING;
        }
        else
        {
            std::string readValue;
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
            dutyValueFile.close();
            this->pwmErrors->dutyFileError = true;
            return FILE_COULD_NOT_OPEN_STRING;
        }
        else
        {
            std::string readValue;
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
            runValueFile.close();
            this->pwmErrors->runFileError = true;
            return FILE_COULD_NOT_OPEN_STRING;
        }
        else
        {
            std::string readValue;
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
            polarityValueFile.close();
            this->pwmErrors->polarityFileError = true;
            return FILE_COULD_NOT_OPEN_STRING;
        }
        else
        {
            std::string readValue;
            polarityValueFile >> readValue;

            polarityValueFile.close();
            this->pwmErrors->polarityFileError = false;
            return readValue;
        }
    }

    float       BlackPWM::getNumericValue()
    {
        double period   = static_cast<long double>( this->getNumericPeriodValue() );
        double duty     = static_cast<long double>( this->getNumericDutyValue() );

        return static_cast<float>( (1.0 - (duty / period )) * 100 );
    }

    inline int64_t    BlackPWM::getNumericPeriodValue()
    {
        int64_t readValue = FILE_COULD_NOT_OPEN_INT;

        std::ifstream periodValueFile;

        periodValueFile.open(this->periodPath.c_str(),std::ios::in);
        if(periodValueFile.fail())
        {
            periodValueFile.close();
            this->pwmErrors->periodFileError = true;
        }
        else
        {
            periodValueFile >> readValue;

            periodValueFile.close();
            this->pwmErrors->periodFileError = false;
        }
        return readValue;
    }

    inline int64_t    BlackPWM::getNumericDutyValue()
    {
        int64_t readValue = FILE_COULD_NOT_OPEN_INT;
        std::ifstream dutyValueFile;

        dutyValueFile.open(this->dutyPath.c_str(),std::ios::in);
        if(dutyValueFile.fail())
        {
            dutyValueFile.close();
            this->pwmErrors->dutyFileError = true;
        }
        else
        {
            dutyValueFile >> readValue;

            dutyValueFile.close();
            this->pwmErrors->dutyFileError = false;
        }
        return readValue;
    }


    bool        BlackPWM::setDutyPercent(float percantage)
    {
        if( percantage > 100.0 or percantage < 0.0 )
        {
            this->pwmErrors->outOfRange      = true;
            this->pwmErrors->dutyFileError   = true;
            this->pwmErrors->periodFileError = true;
            return false;
        }

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
            dutyFile << static_cast<int64_t>(std::round((this->getNumericPeriodValue()) * (1.0 - (percantage/100))));
            dutyFile.close();
            this->pwmErrors->dutyFileError = false;
            return true;
        }

    }

    bool        BlackPWM::setPeriodTime(uint64_t period, timeType tType)
    {
        uint64_t writeThis = static_cast<uint64_t>(period * static_cast<double>(pow( 10, static_cast<int>(tType)+9) ));

        if( writeThis > 1000000000)
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

    bool        BlackPWM::setSpaceRatioTime(uint64_t space, timeType tType)
    {
        uint64_t writeThis = static_cast<int64_t>(space * static_cast<double>(pow( 10, static_cast<int>(tType)+9) ));

        if( writeThis > 1000000000)
        {
            this->pwmErrors->outOfRange = true;
            return false;
        }
        else
        {
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

    bool        BlackPWM::setLoadRatioTime(uint64_t load, timeType tType)
    {
        uint64_t writeThis = (this->getNumericPeriodValue() - static_cast<int64_t>(load * static_cast<double>(pow( 10, static_cast<int>(tType)+9) )));

        if( writeThis > 1000000000)
        {
            this->pwmErrors->outOfRange = true;
            return false;
        }
        else
        {
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

    bool        BlackPWM::setPolarity(polarityType polarity)
    {
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
            polarityFile << static_cast<int>(polarity);
            polarityFile.close();
            this->pwmErrors->polarityFileError = false;
            return true;
        }
    }

    bool        BlackPWM::setRunState(runValue state)
    {
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
            runFile << static_cast<int>(state);
            runFile.close();
            this->pwmErrors->runFileError = false;
            return true;
        }
    }



    bool        BlackPWM::isRunning()
    {
        return (this->getRunValue() == "1");
    }

    bool        BlackPWM::isPolarityStraight()
    {
        return !(this->getPolarityValue() == "1");
    }

    bool        BlackPWM::isPolarityReverse()
    {
        return (this->getPolarityValue() == "1");
    }



    void        BlackPWM::toggleRunState()
    {
        if( this->getRunValue() == "1" )
        {
            this->setRunState(stop);
        }
        else
        {
            this->setRunState(run);
        }
    }

    void        BlackPWM::tooglePolarity()
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

    bool        BlackPWM::fail()
    {
        return (this->pwmErrors->outOfRange or
                this->pwmErrors->runFileError or
                this->pwmErrors->dutyFileError or
                this->pwmErrors->periodFileError or
                this->pwmErrors->polarityFileError or
                this->pwmErrors->pwmCoreErrors->dtError or
                this->pwmErrors->pwmCoreErrors->dtSsError or
                this->pwmErrors->pwmCoreErrors->pwmTestError or
                this->pwmErrors->pwmCoreErrors->coreErrors->ocpError or
                this->pwmErrors->pwmCoreErrors->coreErrors->capeMgrError
                );
    }

    bool        BlackPWM::fail(BlackPWM::flags f)
    {
        if(f==outOfRangeErr)    { return this->pwmErrors->outOfRange;                               }
        if(f==runFileErr)       { return this->pwmErrors->runFileError;                             }
        if(f==dutyFileErr)      { return this->pwmErrors->dutyFileError;                            }
        if(f==periodFileErr)    { return this->pwmErrors->periodFileError;                          }
        if(f==polarityFileErr)  { return this->pwmErrors->polarityFileError;                        }
        if(f==dtErr)            { return this->pwmErrors->pwmCoreErrors->dtError;                   }
        if(f==dtSubSystemErr)   { return this->pwmErrors->pwmCoreErrors->dtSsError;                 }
        if(f==pwmTestErr)       { return this->pwmErrors->pwmCoreErrors->pwmTestError;              }
        if(f==ocpErr)           { return this->pwmErrors->pwmCoreErrors->coreErrors->ocpError;      }
        if(f==cpmgrErr)         { return this->pwmErrors->pwmCoreErrors->coreErrors->capeMgrError;  }

        return true;
    }

    // ########################################### BLACKPWM DEFINITION STARTS ############################################ //


} /* namespace BlackLib */
