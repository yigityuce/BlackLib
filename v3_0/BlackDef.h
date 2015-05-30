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



#ifndef BLACKDEF_H_
#define BLACKDEF_H_


#include <string>

namespace BlackLib
{

    /*!
    *  This enum is used for selecting direction.
    */
    enum direction          {   input                   = 1,
                                output                  = 2,
                                bothDirection           = (input|output)
                            };


    /*!
     * This enum is used for setting run state (like PWM).
     */
    enum runValue           {   stop                    = 0,
                                run                     = 1
                            };


    /*!
     * This enum is used for selecting time type (like BlackPWM::setPeriodTime() function).
     */
    enum timeType           {   picosecond              = -12,
                                nanosecond              = -9,
                                microsecond             = -6,
                                milisecond              = -3,
                                second                  = 1
                            };


    /*!
     * This enum is used for selecting file open mode.
     */
    enum openMode           {   ReadOnly                = 0,
                                WriteOnly               = 1,
                                ReadWrite               = 2,
                                Append                  = 4,
                                Truncate                = 8,
                                NonBlock                = 16
                            };





    const std::string       DEFAULT_CAPE_MGR_NUMBER     = "8";                      //!< If @b capemgr finding fails, it uses this number
    const std::string       DEFAULT_OCP_NUMBER          = "2";                      //!< If @b ocp finding fails, it uses this number
    const std::string       DEFAULT_HELPER_NUMBER       = "14";                     //!< If @b helper finding fails, it uses this number
    const std::string       DEFAULT_PWM_TEST_NUMBER     = "15";                     //!< If @b pwm_test finding fails, it uses this number
    const std::string       DEFAULT_SPI0_PINMUX         = "48030000";               //!< SPI0 pinmux number
    const std::string       DEFAULT_SPI1_PINMUX         = "481a0000";               //!< SPI1 pinmux number
    const unsigned int      DEFAULT_OPEN_MODE           = (ReadWrite);              //!< Default open mode
    const std::string       PWM_TEST_NAME_NOT_FOUND     = "PwmTestNameError";       //!< If pwm test name could not find, function returns this string
    const std::string       GPIO_PIN_NOT_READY_STRING   = "Gpio Pin Isn\'t Ready";  //!< If gpio pin is not ready, function returns this string
    const int               GPIO_PIN_NOT_READY_INT      = -2;                       //!< If gpio pin is not ready, function returns this integer
    const std::string       UART_READ_FAILED            = "UartReadError";          //!< If uart read is failed, function returns this string
    const std::string       UART_WRITE_FAILED           = "UartWriteError";         //!< If uart write is failed, function returns this string
    const std::string       SEARCH_DIR_NOT_FOUND        = "Not Found";              //!< If directory searching fails, function returns this string
    const std::string       FILE_COULD_NOT_OPEN_STRING  = "File Couldn\'t Open";    //!< If file could not open, function returns this string
    const int               FILE_COULD_NOT_OPEN_INT     = -1;                       //!< If file could not open, function returns this integer
    const float             FILE_COULD_NOT_OPEN_FLOAT   = -1.0;                     //!< If file could not open, function returns this float value

} /* namespace BlackLib */

#endif /* BLACKDEF_H_ */
