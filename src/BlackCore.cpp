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

#include "BlackCore.h"







namespace BlackLib
{

    // ########################################### BLACKCORE DEFINITION STARTS ########################################### //
    BlackCore::BlackCore()
    {
        this->coreErrors = new errorCore();

        this->findCapeMgrName();
        this->findOcpName();
        this->slotsFilePath = "/sys/devices/" + this->capeMgrName + "/slots";
    }

    BlackCore::~BlackCore()
    {
        delete this->coreErrors;
    }

    std::string BlackCore::executeCommand(std::string command)
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

    std::string BlackCore::searchDirectory(std::string seachIn, std::string searchThis)
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

    bool        BlackCore::findCapeMgrName()
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

    bool        BlackCore::findOcpName()
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




    std::string BlackCore::searchDirectoryOcp(BlackCore::ocpSearch searchThis)
    {
        std::string searchResult;
        std::string searchPath = "/sys/devices/" + this->getOcpName() + "/";

        if( searchThis == this->SPI0 )
        {
            searchPath += DEFAULT_SPI0_PINMUX + ".spi/spi_master/";
        }
        else if( searchThis == this->SPI1 )
        {
            searchPath += DEFAULT_SPI1_PINMUX + ".spi/spi_master/";
        }


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

            case SPI0:
            {
                searchResult = this->searchDirectory(searchPath,"spi");
                break;
            }

            case SPI1:
            {
                searchResult = this->searchDirectory(searchPath,"spi");
                break;
            }
        }


        return searchResult;
    }

    errorCore   *BlackCore::getErrorsFromCore()
    {
        return (this->coreErrors);
    }



    std::string BlackCore::getCapeMgrName()
    {
        return this->capeMgrName;
    }

    std::string BlackCore::getOcpName()
    {
        return this->ocpName;
    }

    std::string BlackCore::getSlotsFilePath()
    {
        return this->slotsFilePath;
    }

    // ############################################ BLACKCORE DEFINITION ENDS ############################################ //



} /* namespace BlackLib */
