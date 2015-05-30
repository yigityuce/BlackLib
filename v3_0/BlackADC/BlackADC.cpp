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

#include "BlackADC.h"





namespace BlackLib
{

    // ######################################### BLACKCOREADC DEFINITION STARTS ########################################## //
    BlackCoreADC::BlackCoreADC()
    {
        this->adcCoreErrors = new errorCoreADC( this->getErrorsFromCore() );

        this->loadDeviceTree();
        this->findHelperName();
    }

    BlackCoreADC::~BlackCoreADC()
    {
        delete this->adcCoreErrors;
    }


    bool        BlackCoreADC::loadDeviceTree()
    {
        std::string file = this->getSlotsFilePath();
        std::ofstream slotsFile;
        slotsFile.open(file.c_str(), std::ios::out);
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

    bool        BlackCoreADC::findHelperName()
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

    std::string BlackCoreADC::getHelperPath()
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
    BlackADC::BlackADC(adcName adc)
    {
        this->adcErrors                 = new errorADC( this->getErrorsFromCoreADC() );
        this->ainName                   = adc;
        this->ainPath                   = this->getHelperPath() + "/AIN" + tostr(this->ainName);
    }


    BlackADC::~BlackADC()
    {
        delete this->adcErrors;
    }


    std::string BlackADC::getValue()
    {
        std::string returnStr = FILE_COULD_NOT_OPEN_STRING;
        std::ifstream adcValueFile;

        adcValueFile.open(ainPath.c_str(),std::ios::in);
        if(adcValueFile.fail())
        {
            adcValueFile.close();
            this->adcErrors->readError = true;
        }
        else
        {
            returnStr.clear();
            adcValueFile >> returnStr;

            adcValueFile.close();
            this->adcErrors->readError = false;
        }

        return returnStr;
    }

    adcName     BlackADC::getName()
    {
        return this->ainName;
    }


    int         BlackADC::getNumericValue()
    {
        int readValue = FILE_COULD_NOT_OPEN_INT;
        std::ifstream adcValueFile;

        adcValueFile.open(this->ainPath.c_str(),std::ios::in);
        if(adcValueFile.fail())
        {
            adcValueFile.close();
            this->adcErrors->readError=true;
        }
        else
        {
            adcValueFile >> readValue;
            adcValueFile.close();
            this->adcErrors->readError=false;
        }

        return readValue;
    }

    float       BlackADC::getConvertedValue(digitAfterPoint mode)
    {
        int valueInt = 0;

        std::ifstream adcValueFile;

        adcValueFile.open(this->ainPath.c_str(),std::ios::in);
        if(adcValueFile.fail())
        {
            adcValueFile.close();
            this->adcErrors->readError=true;
            return FILE_COULD_NOT_OPEN_FLOAT;
        }
        else
        {
            adcValueFile >> valueInt;
            adcValueFile.close();
            this->adcErrors->readError=false;
        }


        float valueFloat    = static_cast<float>(valueInt);

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

        return FILE_COULD_NOT_OPEN_FLOAT;
    }

    bool        BlackADC::fail()
    {
        return (this->adcErrors->adcCoreErrors->coreErrors->capeMgrError or
                this->adcErrors->adcCoreErrors->coreErrors->ocpError or
                this->adcErrors->adcCoreErrors->helperError or
                this->adcErrors->adcCoreErrors->dtError or
                this->adcErrors->readError);
    }

    bool        BlackADC::fail(BlackADC::flags f)
    {
        if(f==cpmgrErr) { return this->adcErrors->adcCoreErrors->coreErrors->capeMgrError;  }
        if(f==ocpErr)   { return this->adcErrors->adcCoreErrors->coreErrors->ocpError;      }
        if(f==helperErr){ return this->adcErrors->adcCoreErrors->helperError;               }
        if(f==dtErr)    { return this->adcErrors->adcCoreErrors->dtError;                   }
        if(f==readErr)  { return this->adcErrors->readError;                                }

        return true;
    }




    BlackADC&   BlackADC::operator>>(std::string &readToThis)
    {
        std::string readValue = FILE_COULD_NOT_OPEN_STRING;
        std::ifstream adcValueFile;

        adcValueFile.open(ainPath.c_str(),std::ios::in);
        if(adcValueFile.fail())
        {
            adcValueFile.close();
            this->adcErrors->readError = true;
        }
        else
        {
            readValue.clear();
            adcValueFile >> readValue;

            adcValueFile.close();
            this->adcErrors->readError = false;
        }

        readToThis = readValue;
        return *this;
    }


    BlackADC&   BlackADC::operator>>(int &readToThis)
    {
        int readValue = FILE_COULD_NOT_OPEN_INT;
        std::ifstream adcValueFile;

        adcValueFile.open(this->ainPath.c_str(),std::ios::in);
        if(adcValueFile.fail())
        {
            adcValueFile.close();
            this->adcErrors->readError=true;
        }
        else
        {
            adcValueFile >> readValue;
            adcValueFile.close();
            this->adcErrors->readError=false;
        }

        readToThis = readValue;
        return *this;
    }


    BlackADC&   BlackADC::operator>>(float &readToThis)
    {
        readToThis = this->getConvertedValue(dap3);
        return *this;
    }


    // ############################################ BLACKADC DEFINITION ENDS ############################################# //


} /* namespace BlackLib */
