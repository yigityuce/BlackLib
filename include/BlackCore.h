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


#ifndef BLACKCORE_H_
#define BLACKCORE_H_


#include "BlackErr.h"       // Black Errors header file
#include "BlackDef.h"       // Black Definitions header file


#include <cstring>
#include <string>
#include <sstream>          // need for tostr() function
#include <cstdio>           // need for popen() function in BlackCore::executeShellCmd()
#include <dirent.h>         // need for dirent struct in BlackCore::searchDirectory()








namespace BlackLib
{

    /*! @brief Uses for converting the different types variable to string type.
    *
    * @tparam T variable which will convert.
    * @return String type value of T type variable.
    */
    template <typename T>
    inline std::string tostr(const T& t)
    {
        std::ostringstream os;
        os << t;
        return os.str();
    }





    // ########################################### BLACKCORE DECLARATION STARTS ########################################### //

    /*! @brief Base class of the other classes.
     *
     *    This class is core of the @b BlackLib Library.
     *    It includes private functions like communicating with operating system and their limited versions for
     *    using from derived class.
     */
    class BlackCore
    {
        private:
            errorCore       *coreErrors;            /*!< @brief is used to hold the errors of BlackCore class */
            std::string     capeMgrName;            /*!< @brief is used to hold the capemgr name */
            std::string     ocpName;                /*!< @brief is used to hold the ocp name */
            std::string     slotsFilePath;          /*!< @brief is used to hold the slots file path */

            /*! @brief Finds full name of capemgr directory.
            *
            *  This function searches @b "/sys/devices/" directory,
            *  to find directory which starts with @b "bone_capemgr."
            *  @return True if successful, else false.
            *  @sa BlackCore::searchDirectory()
            */
            bool            findCapeMgrName();

            /*! @brief Finds full name of ocp directory.
            *
            *  This function searches @b "/sys/devices/" directory,
            *  to find directory which starts with @b "ocp."
            *  @return True if successful, else false.
            *  @sa BlackCore::searchDirectory()
            */
            bool            findOcpName();

            /*! @brief Executes system call.
            *
            *  This function executes system commands with using popen() function.
            *  This example executes "ls" command with argument "la" and saves
            *  output to returnValue variable. @n @n
            *  <b> string returnValue = executeCommand("ls -la"); </b>
            */
            std::string     executeCommand(std::string command);

            /*! @brief Searches specified directory to find specified file/directory.
            *
            *  @param[in] searchIn searching directory
            *  @param[in] searchThis search file/directory
            *  @return Full name of searching file/directory.
            */
            std::string     searchDirectory(std::string searchIn, std::string searchThis);

            /*! @brief First declaration of this function.
            */
            virtual bool    loadDeviceTree() = 0;



        protected:

            /*!
             * This enum is used for defining ADC, PWM and SPI device driver names.
             */
            enum ocpSearch  {   ADC_helper  =   0,         /*!< enumeration for @a adc device driver name for using at BlackCore::searchDirectoryOcp() function parameter*/
                                PWM_P8_13   =   1,         /*!< enumeration for @a P8_13 pwm device driver name */
                                PWM_P8_19   =   2,         /*!< enumeration for @a P8_19 pwm device driver name */
                                PWM_P9_14   =   3,         /*!< enumeration for @a P9_14 pwm device driver name */
                                PWM_P9_16   =   4,         /*!< enumeration for @a P9_16 pwm device driver name */
                                PWM_P9_21   =   5,         /*!< enumeration for @a P9_21 pwm device driver name */
                                PWM_P9_22   =   6,         /*!< enumeration for @a P9_22 pwm device driver name */
                                PWM_P9_42   =   7,         /*!< enumeration for @a P9_42 pwm device driver name */
                                SPI0        =   8,         /*!< enumeration for @a SPI0 spi device driver name */
                                SPI1        =   9          /*!< enumeration for @a SPI1 spi device driver name */
                            };

            /*! @brief Searches ocp directory to find specified file/directory.
            *
            * This function searches ocp directory only. It can be used from derived class.
            *  @param[in] searchThis takes BlackCore::ocpSearch type variable(enum)
            *  @return Full name of searching file/directory.
            */
            std::string     searchDirectoryOcp(BlackCore::ocpSearch searchThis);

            /*! @brief Exports errorCore struct to derived class.
            *
            *  @return errorCore struct pointer.
            */
            errorCore       *getErrorsFromCore();

            /*! @brief Exports capemgr name to derived class.
            *
            *  @return BlackCore::capeMgrName variable.
            */
            std::string     getCapeMgrName();

            /*! @brief Exports ocp name to derived class.
            *
            *  @return BlackCore::ocpName variable.
            */
            std::string     getOcpName();

            /*! @brief Exports slots file path to derived class.
            *
            *  @return BlackCore::slotsFilePath variable.
            */
            std::string     getSlotsFilePath();



        public:
            /*! @brief Constructor of BlackCore class.
            *
            * This function initializes errorCore struct and runs these functions:
            * @li findCapeMgrName()
            * @li findOcpName()
            */
            BlackCore();

            /*! @brief Destructor of BlackCore class.
            *
            * This function deletes errorCore struct pointer.
            */
            virtual ~BlackCore();

    };
    // ############################################ BLACKCORE DECLARATION ENDS ############################################ //


} /* namespace BlackLib */

#endif /* BLACKCORE_H_ */
