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



#include "BlackGPIO.h"





namespace BlackLib
{

    // ######################################### BLACKCOREGPIO DEFINITION STARTS ######################################### //
                BlackCoreGPIO::BlackCoreGPIO(gpioName pin, direction dir)
    {
        this->pinNumericName    = static_cast<int>(pin);
        this->pinNumericType    = static_cast<int>(dir);
        this->gpioCoreError     = new errorCoreGPIO( this->getErrorsFromCore() );


        this->expPath           = "/sys/class/gpio/export";
        this->unExpPath         = "/sys/class/gpio/unexport";
        this->directionPath     = "/sys/class/gpio/gpio" + tostr(this->pinNumericName) + "/direction";


        this->doExport();
        this->setDirection();
    }

    BlackCoreGPIO::~BlackCoreGPIO()
    {
        this->doUnexport();
        delete this->gpioCoreError;
    }

    bool        BlackCoreGPIO::loadDeviceTree()
    {
        return false;
    }



    bool        BlackCoreGPIO::doExport()
    {
        std::ofstream expFile;

        expFile.open(this->expPath.c_str(),std::ios::out);
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

    bool        BlackCoreGPIO::setDirection()
    {
        std::ofstream directionFile;

        directionFile.open(this->directionPath.c_str(), std::ios::out);
        if(directionFile.fail())
        {
            directionFile.close();
            this->gpioCoreError->directionFileError = true;
            return false;
        }
        else
        {
            if(this->pinNumericType == static_cast<int>(output))
            {
                directionFile << "out";
            }
            else
            {
                directionFile << "in";
            }

            directionFile.close();
            this->gpioCoreError->directionFileError = false;
            return true;
        }
    }

    bool        BlackCoreGPIO::doUnexport()
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



    std::string BlackCoreGPIO::getDirectionFilePath()
    {
        return this->directionPath;
    }


    std::string BlackCoreGPIO::getValueFilePath()
    {
        return ("/sys/class/gpio/gpio" + tostr(this->pinNumericName) + "/value");
    }


    errorCoreGPIO *BlackCoreGPIO::getErrorsFromCoreGPIO()
    {
        return (this->gpioCoreError);
    }

    // ########################################## BLACKCOREGPIO DEFINITION ENDS ########################################## //










    // ########################################### BLACKGPIO DEFINITION STARTS ########################################### //
    BlackGPIO::BlackGPIO(gpioName pin, direction dir, workingMode wm) : BlackCoreGPIO(pin, dir)
    {
        this->pinName       = pin;
        this->pinDirection  = dir;
        this->workMode      = wm;
        this->gpioErrors    = new errorGPIO( this->getErrorsFromCoreGPIO() );
        this->valuePath     = this->getValueFilePath();
    }

    BlackGPIO::~BlackGPIO()
    {
        delete this->gpioErrors;
    }


    bool        BlackGPIO::isReady()
    {
        return (this->isExported() and this->isDirectionSet());
    }

    bool        BlackGPIO::isExported()
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

    bool        BlackGPIO::isDirectionSet()
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
            std::string readValue;
            directionCheck >> readValue;

            if( (this->pinDirection == input and readValue=="in") or (this->pinDirection == output and readValue=="out") )
            {
                directionCheck.close();
                this->gpioErrors->directionError = false;
                return true;
            }
            else
            {
                directionCheck.close();
                this->gpioErrors->directionError = true;
                return false;
            }
        }
    }


    std::string BlackGPIO::getValue()
    {
        if( this->workMode == SecureMode )
        {
            if( ! this->isReady())
            {
                return GPIO_PIN_NOT_READY_STRING;
            }
        }


        std::ifstream valueFile;

        valueFile.open(valuePath.c_str(),std::ios::in);
        if(valueFile.fail())
        {
            valueFile.close();
            this->gpioErrors->readError = true;
            return FILE_COULD_NOT_OPEN_STRING;
        }
        else
        {
            std::string readValue;
            valueFile >> readValue;

            valueFile.close();
            this->gpioErrors->readError = false;
            return readValue;
        }
    }

    int         BlackGPIO::getNumericValue()
    {
        if( this->workMode == SecureMode )
        {
            if( ! this->isReady())
            {
                return GPIO_PIN_NOT_READY_INT;
            }
        }


        std::ifstream valueFile;

        valueFile.open(valuePath.c_str(),std::ios::in);
        if(valueFile.fail())
        {
            valueFile.close();
            this->gpioErrors->readError = true;
            return FILE_COULD_NOT_OPEN_INT;
        }
        else
        {
            int readValue;
            valueFile >> readValue;

            valueFile.close();
            this->gpioErrors->readError = false;
            return readValue;
        }
    }

    gpioName    BlackGPIO::getName()
    {
        return this->pinName;
    }

    direction   BlackGPIO::getDirection()
    {
        return this->pinDirection;
    }

    bool        BlackGPIO::setValue(digitalValue status)
    {
        if( !(this->pinDirection == output) )
        {
            this->gpioErrors->writeError = true;
            this->gpioErrors->forcingError = true;
            return false;
        }



        this->gpioErrors->forcingError = false;

        if( this->workMode == SecureMode )
        {
            if( ! this->isReady())
            {
                this->gpioErrors->writeError = true;
                return false;
            }
        }



        std::ofstream valueFile;
        valueFile.open(this->valuePath.c_str(), std::ios::out);
        if(valueFile.fail())
        {
            valueFile.close();
            this->gpioErrors->writeError = true;
            return false;
        }
        else
        {
            if( status == high )
            {
                valueFile << "1";
            }
            else
            {
                valueFile << "0";
            }

            valueFile.close();
            this->gpioErrors->writeError = false;
            return true;
        }
    }



    bool        BlackGPIO::isHigh()
    {
        return (this->getNumericValue() == 1);
    }

    void        BlackGPIO::toggleValue()
    {
        if( !(this->pinDirection == output) )
        {
            this->gpioErrors->forcingError = true;
        }
        else
        {
            this->gpioErrors->forcingError = false;
            if( (this->getNumericValue() == 1) )
            {
                this->setValue(low);
            }
            else
            {
                this->setValue(high);
            }
        }
    }


    void        BlackGPIO::setWorkingMode(workingMode newWM)
    {
        this->workMode = newWM;
    }

    workingMode BlackGPIO::getWorkingMode()
    {
        return this->workMode;
    }



    bool        BlackGPIO::fail()
    {
        return (this->gpioErrors->readError or
                this->gpioErrors->writeError or
                this->gpioErrors->exportError or
                this->gpioErrors->forcingError or
                this->gpioErrors->directionError
                );
    }

    bool        BlackGPIO::fail(BlackGPIO::flags f)
    {
        if(f==readErr)          { return this->gpioErrors->readError;                           }
        if(f==writeErr)         { return this->gpioErrors->writeError;                          }
        if(f==exportErr)        { return this->gpioErrors->exportError;                         }
        if(f==forcingErr)       { return this->gpioErrors->forcingError;                        }
        if(f==directionErr)     { return this->gpioErrors->directionError;                      }
        if(f==exportFileErr)    { return this->gpioErrors->gpioCoreErrors->exportFileError;     }
        if(f==directionFileErr) { return this->gpioErrors->gpioCoreErrors->directionFileError;  }

        return true;
    }




    BlackGPIO&  BlackGPIO::operator>>(std::string &readToThis)
    {
        if( this->workMode == SecureMode )
        {
            if( ! this->isReady())
            {
                readToThis = GPIO_PIN_NOT_READY_STRING;
                return *this;
            }
        }


        std::string readValue;
        std::ifstream valueFile;

        valueFile.open(valuePath.c_str(),std::ios::in);
        if(valueFile.fail())
        {
            valueFile.close();
            this->gpioErrors->readError = true;
            readValue = FILE_COULD_NOT_OPEN_STRING;
        }
        else
        {
            valueFile >> readValue;

            valueFile.close();
            this->gpioErrors->readError = false;
        }

        readToThis = readValue;
        return *this;
    }


    BlackGPIO&  BlackGPIO::operator>>(int &readToThis)
    {
        if( this->workMode == SecureMode )
        {
            if( ! this->isReady())
            {
                readToThis = GPIO_PIN_NOT_READY_INT;
                return *this;
            }
        }


        int readValue;
        std::ifstream valueFile;

        valueFile.open(valuePath.c_str(),std::ios::in);
        if(valueFile.fail())
        {
            valueFile.close();
            this->gpioErrors->readError = true;
            readValue = FILE_COULD_NOT_OPEN_INT;
        }
        else
        {
            valueFile >> readValue;

            valueFile.close();
            this->gpioErrors->readError = false;
        }

        readToThis = readValue;
        return *this;
    }


    BlackGPIO&  BlackGPIO::operator<<(digitalValue value)
    {
        if( !(this->pinDirection == output) )
        {
            this->gpioErrors->writeError = true;
            this->gpioErrors->forcingError = true;
            return *this;
        }



        this->gpioErrors->forcingError = false;

        if( this->workMode == SecureMode )
        {
            if( ! this->isReady())
            {
                this->gpioErrors->writeError = true;
                return *this;
            }
        }



        std::ofstream valueFile;
        valueFile.open(this->valuePath.c_str(), std::ios::out);
        if(valueFile.fail())
        {
            valueFile.close();
            this->gpioErrors->writeError = true;
            return *this;
        }
        else
        {
            if( value == high )
            {
                valueFile << "1";
            }
            else
            {
                valueFile << "0";
            }

            valueFile.close();
            this->gpioErrors->writeError = false;
            return *this;
        }
    }


    // ############################################ BLACKGPIO DECLARATION ENDS ############################################ //

} /* namespace BlackLib */
