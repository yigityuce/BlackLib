 /*

 ####################################################################################
 #  BlackLib Library controls Beaglebone Black's inputs and outputs.                #
 #  Copyright (C) 2013-2014 by Yigit YUCE                                           #
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
     * This enum is used for selecting ADC input.
     */
    enum adcName            {   AIN0                    = 0,
                                AIN1                    = 1,
                                AIN2                    = 2,
                                AIN3                    = 3,
                                AIN4                    = 4,
                                AIN5                    = 5,
                                AIN6                    = 6
                            };



    /*!
     * This enum is used for selecting convert level of ADC value.
     */
    enum digitAfterPoint    {   dap1                    = 1,
                                dap2                    = 2,
                                dap3                    = 3
                            };




    /*!
     *  This enum is used for selecting direction.
     */
    enum direction          {   input                   = 1,
                                output                  = 2,
                                bothDirection           = (input|output)
                            };



    /*!
     * This enum is used for setting digital output value.
     */
    enum digitalValue       {   low                     = 0,
                                high                    = 1
                            };




    /*!
     * This enum is used for selecting GPIO number.
     */
    enum gpioName           {   GPIO_125=125,   GPIO_123=123,
                                GPIO_122=122,   GPIO_121=121,
                                GPIO_120=120,   GPIO_117=117,
                                GPIO_49=49,     GPIO_15=15,
                                GPIO_48=48,     GPIO_51=51,
                                GPIO_20=20,     GPIO_38=38,
                                GPIO_30=30,     GPIO_60=60,
                                GPIO_31=31,     GPIO_40=40,
                                GPIO_39=39,     GPIO_34=34,
                                GPIO_35=35,     GPIO_66=66,
                                GPIO_67=67,     GPIO_69=69,
                                GPIO_68=68,     GPIO_45=45,
                                GPIO_44=44,     GPIO_23=23,
                                GPIO_26=26,     GPIO_47=47,
                                GPIO_46=46,     GPIO_27=27,
                                GPIO_65=65,     GPIO_22=22,
                                GPIO_63=63,     GPIO_62=62,
                                GPIO_37=37,     GPIO_36=36,
                                GPIO_33=33,     GPIO_32=32,
                                GPIO_61=61,     GPIO_86=86,
                                GPIO_88=88,     GPIO_87=87,
                                GPIO_89=89,     GPIO_10=10,
                                GPIO_11=11,     GPIO_81=81,
                                GPIO_80=80,     GPIO_78=78,
                                GPIO_79=79,     GPIO_76=76,
                                GPIO_77=77,     GPIO_74=74,
                                GPIO_75=75,     GPIO_72=72,
                                GPIO_73=73,     GPIO_70=70,
                                GPIO_71=71,     GPIO_14=14,
                                GPIO_9=9,       GPIO_8=8,
                                GPIO_7=7,       GPIO_5=5,
                                GPIO_4=4,       GPIO_3=3,
                                GPIO_2=2
                            };


    /*!
     * This enum is used for selecting working mode.
     */
    enum workingMode        {   SecureMode              = 0,
                                FastMode                = 1
                            };



    /*!
     * This enum is used for selecting PWM name.
     */
    enum pwmName            {   P8_13                   = 0,
                                P8_19                   = 1,
                                P9_14                   = 2,
                                P9_16                   = 3,
                                P9_21                   = 4,
                                P9_22                   = 5,
                                P9_42                   = 6,

                                EHRPWM2B                = P8_13,
                                EHRPWM2A                = P8_19,
                                EHRPWM1A                = P9_14,
                                EHRPWM1B                = P9_16,
                                EHRPWM0B                = P9_21,
                                EHRPWM0A                = P9_22,
                                ECAP0                   = P9_42
                            };

    /*!
     * This string array is used for mapping pwm name.
     */
    const std::string pwmNameMap[7] = { "P8_13",
                                        "P8_19",
                                        "P9_14",
                                        "P9_16",
                                        "P9_21",
                                        "P9_22",
                                        "P9_42",
                                      };



    /*!
     * This enum is used for setting run state (like PWM).
     */
    enum runValue           {   stop                    = 0,
                                run                     = 1
                            };




    /*!
     * This enum is used for setting PWM polarity.
     */
    enum polarityType       {   straight                = 0,
                                reverse                 = 1
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
     * This enum is used for selecting UART name.
     */
    enum uartName           {   UART1                   = 1,
                                UART2                   = 2,
                                UART4                   = 4,
                                UART5                   = 5
                            };


    /*!
     * This enum is used for setting baud rate.
     */
    enum baudRate           {   Baud0                   = 0,
                                Baud50                  = 1,
                                Baud75                  = 2,
                                Baud110                 = 3,
                                Baud134                 = 4,
                                Baud150                 = 5,
                                Baud200                 = 6,
                                Baud300                 = 7,
                                Baud600                 = 8,
                                Baud1200                = 9,
                                Baud1800                = 10,
                                Baud2400                = 11,
                                Baud4800                = 12,
                                Baud9600                = 13,
                                Baud19200               = 14,
                                Baud38400               = 15
                            };


    /*!
     * This enum is used for setting parity.
     */
    enum parity             {   ParityNo                = 0,
                                ParityOdd               = 1,
                                ParityEven              = 2,
                                ParityDefault           = -1
                            };


    /*!
     * This enum is used for setting character size.
     */
    enum characterSize      {   Char5                   = 5,
                                Char6                   = 6,
                                Char7                   = 7,
                                Char8                   = 8,
                                CharDefault             = 0
                            };


    /*!
     * This enum is used for setting stop bit(s) size.
     */
    enum stopBits           {   StopOne                 = 1,
                                StopTwo                 = 2,
                                StopDefault             = -1
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


    /*!
     * This enum is used for selecting apply mode of uart property's changes.
     */
    enum uartApplyMode      {   ApplyNow                = 0,
                                ApplyDrain              = 1,
                                ApplyFlush              = 2
                            };


    /*!
     * This enum is used for setting spi name.
     */
    enum spiName            {   SPI0_0                  = 0,
                                SPI0_1                  = 1,
                                SPI1_0                  = 2,
                                SPI1_1                  = 3
                            };

    /*!
     * This enum is used for setting spi mode.
     */
    enum spiMode            {   SpiDefault              = 0x00,
                                SpiPhase                = 0x01,
                                SpiPolarity             = 0x02,
                                SpiChipSelectHigh       = 0x04,
                                SpiLsbFirst             = 0x08,
                                Spi3Wire                = 0x10,
                                SpiLoop                 = 0x20,
                                SpiNoChipSelect         = 0x40,
                                SpiReady                = 0x80,

                                SpiMode0                = (0|0),
                                SpiMode1                = (0|SpiPhase),
                                SpiMode2                = (SpiPolarity|0),
                                SpiMode3                = (SpiPolarity|SpiPhase)
                            };






    /*!
     * This enum is used for setting i2c name.
     */
    enum i2cName            {   I2C_0                   = 0,
                                I2C_1                   = 1
                            };

    /*!
     * This enum is used for selecting i2c bus transaction type.
     */
    enum transactionType    {   SMBUS_QUICK             = 0,
                                SMBUS_BYTE              = 1,
                                SMBUS_BYTE_DATA         = 2,
                                SMBUS_WORD_DATA         = 3,
                                SMBUS_PROC_CALL         = 4,
                                SMBUS_BLOCK_DATA        = 5,
                                SMBUS_I2C_BLOCK_BROKEN  = 6,
                                SMBUS_BLOCK_PROC_CALL   = 7,
                                SMBUS_I2C_BLOCK_DATA    = 8
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
