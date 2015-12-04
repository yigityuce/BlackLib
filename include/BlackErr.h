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



#ifndef BLACKERR_H_
#define BLACKERR_H_





namespace BlackLib
{

    /*! @brief Holds BlackCore errors.
     *
     *    This struct is base of the ERROR DATA STRUCT.
     *    The rest of error data structs include this.
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

        /*! @brief errorCore struct's constructor.
         *
         *  This function clears all flags.
         */
        errorCore()
        {
            capeMgrError    = false;
            ocpError        = false;
        }
    };




    /*! @brief Holds BlackCoreADC errors.
     *
     *    This struct holds ADC core errors and includes pointer of errorCore struct.
     */
    struct errorCoreADC
    {
        /*! @brief Pointer of errorCore struct which stores errors of BlackCore class.
         *
         *  This struct initializes at constructor of BlackCoreADC class.
         *  Its value can set with @n
         *  @li getErrorsFromCore()
         *
         *  function in BlackCore class.
         *  @sa BlackCoreADC::BlackCoreADC()
         *  @sa BlackCore::getErrorsFromCore()
         */
        errorCore *coreErrors;


        /*! @brief @b helper directory finding error.
        *
        *  Its value can change, when finding @a helper.X name, at@n
        *  @li findHelperName()
        *
        *  function in BlackCoreADC class.
        *  @sa BlackCoreADC::findHelperName()
        */
        bool helperError;


        /*! @brief <b> Device tree</b> loading error.
        *
        *  Its value can change, when loading adc overlay to device tree, at@n
        *  @li loadDeviceTree()
        *
        *  function in BlackCoreADC class.
        *  @sa BlackCoreADC::loadDeviceTree()
        */
        bool dtError;


        /*! @brief errorCoreADC struct's constructor.
         *
         *  This function clears all flags and initializes errorCore struct.
         */
        errorCoreADC()
        {
            dtError         = false;
            helperError     = false;
            coreErrors      = new errorCore();
        }


        /*! @brief errorCoreADC struct's constructor with errorCore pointer parameter.
         *
         * @param [in] *base    pointer of errorCore struct.
         *
         *  This function clears all flags and assigns input parameter to coreErrors variable.
         */
        errorCoreADC(errorCore *base)
        {
            dtError         = false;
            helperError     = false;
            coreErrors      = base;
        }
    };





    /*! @brief Holds BlackADC errors.
     *
     *    This struct holds ADC errors and includes pointer of errorCoreADC struct.
     */
    struct errorADC
    {
        /*! @brief Pointer of errorCoreADC struct which stores errors of BlackCoreADC class.
        *
        *  This struct initializes at constructor of BlackADC class.@n
        *  Its value can set with @n
        *  @li getErrorsFromCoreADC()
        *
        *  function in BlackCoreADC class.
        *  @sa BlackADC::BlackADC()
        *  @sa BlackCoreADC::getErrorsFromCoreADC()
        */
        errorCoreADC *adcCoreErrors;


        /*! @brief <b> Value file</b> reading error.
        *
        *  Its value can change, when opening analog input's value file, at@n
        *  @li getValue()
        *  @li getNumericValue()
        *  @li getConvertedValue()
        *
        *  functions in BlackADC class.
        *  @sa BlackADC::getValue()
        *  @sa BlackADC::getNumericValue()
        *  @sa BlackADC::getConvertedValue()
        */
        bool readError;


        /*! @brief errorADC struct's constructor.
         *
         *  This function clears all flags and initializes errorCoreADC struct.
         */
        errorADC()
        {
            readError       = false;
            adcCoreErrors   = new errorCoreADC();
        }


        /*! @brief errorADC struct's constructor with errorCoreADC pointer parameter.
         *
         * @param [in] *base    pointer of errorCoreADC struct.
         *
         *  This function clears all flags and assigns input parameter to adcCoreErrors variable.
         */
        errorADC(errorCoreADC *base)
        {
            readError       = false;
            adcCoreErrors   = base;
        }
    };




    /*! @brief Holds BlackCorePWM errors.
     *
     *    This struct holds PWM core errors and includes pointer of errorCore struct.
     */
    struct errorCorePWM
    {
        /*! @brief Pointer of errorCore struct which stores errors of BlackCore class.
         *
         *  This struct initializes at constructor in BlackCorePWM class.@n
         *  Its value can set with @n
         *  @li getErrorsFromCore()
         *
         *  function in BlackCore class.
         *  @sa BlackCorePWM::BlackCorePWM()
         *  @sa BlackCore::getErrorsFromCore()
         */
        errorCore *coreErrors;


        /*! @brief @b Device @b tree loading error.
        *
        *  Its value can change, when loading subsystem pwm overlay to device tree, at@n
        *  @li loadDeviceTree()
        *
        *  function in BlackCorePWM class.
        *  @sa BlackCorePWM::loadDeviceTree()
        */
        bool dtSsError;


        /*! @brief @b Device @b tree loading error.
        *
        *  Its value can change, when loading pwm overlay to device tree, at@n
        *  @li loadDeviceTree()
        *
        *  function in BlackCorePWM class.
        *  @sa BlackCorePWM::loadDeviceTree()
        */
        bool dtError;


        /*! @brief @b pwm_test directory finding error.
        *
        *  Its value can change, when finding @a pwm_test_X.Y name, at@n
        *  @li findPwmTestName()
        *
        *  function in BlackCorePWM class.
        *  @sa BlackCorePWM::findPwmTestName()
        */
        bool pwmTestError;


        /*! @brief errorCorePWM struct's constructor.
         *
         *  This function clears all flags and initializes errorCore struct.
         */
        errorCorePWM()
        {
            dtSsError       = false;
            dtError         = false;
            pwmTestError    = false;
            coreErrors      = new errorCore();
        }


        /*! @brief errorCorePWM struct's constructor with errorCore pointer parameter.
         *
         * @param [in] *base    pointer of errorCore struct.
         *
         *  This function clears all flags and assigns input parameter to coreErrors variable.
         */
        errorCorePWM(errorCore *base)
        {
            dtSsError       = false;
            dtError         = false;
            pwmTestError    = false;
            coreErrors      = base;
        }
    };




    /*! @brief Holds BlackPWM errors.
     *
     *    This struct holds PWM errors and includes pointer of errorCorePWM struct.
     */
    struct errorPWM
    {
        /*! @brief Pointer of errorCorePWM struct, which stores errors of BlackCorePWM class.
        *
        *  This struct initializes at constructor in BlackPWM class.@n
        *  Its value can set with @n
        *  @li getErrorsFromCorePWM()
        *
        *  function in BlackCorePWM class.
        *  @sa BlackPWM::BlackPWM()
        *  @sa BlackCorePWM::getErrorsFromCorePWM()
        */
        errorCorePWM *pwmCoreErrors;


        /*! @brief @b Period @b file reading error.
        *
        *  Its value can change, when opening pwm's period value file, at@n
        *  @li getValue()
        *  @li getNumericValue()
        *  @li getPeriodValue()
        *  @li getNumericPeriodValue()
        *  @li setPeriodTime()
        *  @li setSpaceRatioTime()
        *  @li setLoadRatioTime()
        *
        *  functions in BlackPWM class.
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
        *  Its value can change, when opening pwm's duty value file, at@n
        *  @li getValue()
        *  @li getNumericValue()
        *  @li getDutyValue()
        *  @li getNumericDutyValue()
        *  @li setDutyPercent()
        *  @li setPeriodTime()
        *  @li setSpaceRatioTime()
        *  @li setLoadRatioTime()
        *
        *  functions in BlackPWM class.
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
        *  Its value can change, when opening pwm's run value file, at@n
        *  @li getRunValue()
        *  @li isRunning()
        *  @li setRunState()
        *  @li toggleRunState()
        *
        *  functions in BlackPWM class.
        *  @sa BlackPWM::getRunValue()
        *  @sa BlackPWM::isRunning()
        *  @sa BlackPWM::setRunState()
        *  @sa BlackPWM::toggleRunState()
        */
        bool runFileError;


        /*! @brief @b Polarity @b file reading error.
        *
        *  Its value can change, when opening pwm's polarity value file, at@n
        *  @li getPolarityValue()
        *  @li isPolarityStraight()
        *  @li isPolarityReverse()
        *  @li setPolarity()
        *  @li tooglePolarity()
        *
        *  functions in BlackPWM class.
        *  @sa BlackPWM::getPolarityValue()
        *  @sa BlackPWM::isPolarityStraight()
        *  @sa BlackPWM::isPolarityReverse()
        *  @sa BlackPWM::setPolarity()
        *  @sa BlackPWM::tooglePolarity()
        */
        bool polarityFileError;


        /*! @brief Out of range value error.
        *
        *  Its value can change, when setting some variables of pwm, at@n
        *  @li setDutyPercent()
        *  @li setPeriodTime()
        *  @li setSpaceRatioTime()
        *  @li setLoadRatioTime()
        *
        *  functions in BlackPWM class.
        *  @sa BlackPWM::setDutyPercent()
        *  @sa BlackPWM::setPeriodTime()
        *  @sa BlackPWM::setSpaceRatioTime()
        *  @sa BlackPWM::setLoadRatioTime()
        */
        bool outOfRange;


        /*! @brief errorPWM struct's constructor.
         *
         *  This function clears all flags and initializes errorCorePWM struct.
         */
        errorPWM()
        {
            periodFileError     = false;
            dutyFileError       = false;
            runFileError        = false;
            polarityFileError   = false;
            outOfRange          = false;
            pwmCoreErrors       = new errorCorePWM();
        }


        /*! @brief errorPWM struct's constructor with errorCorePWM pointer parameter.
         *
         * @param [in] *base    pointer of errorCorePWM struct.
         *
         *  This function clears all flags and assigns input parameter to pwmCoreErrors variable.
         */
        errorPWM(errorCorePWM* base)
        {
            periodFileError     = false;
            dutyFileError       = false;
            runFileError        = false;
            polarityFileError   = false;
            outOfRange          = false;
            pwmCoreErrors       = base;
        }
    };




    /*! @brief Holds BlackCoreGPIO errors.
     *
     *    This struct holds GPIO core errors and includes pointer of errorCore struct.
     */
    struct errorCoreGPIO
    {
        /*! @brief Pointer of errorCore struct, which stores errors of BlackCore class.
         *
         *  This struct initializes at constructor in BlackCoreGPIO class.@n
         *  Its value can set with @n
         *  @li getErrorsFromCore()
         *
         *  function in BlackCore class.
         *  @sa BlackCoreGPIO::BlackCoreGPIO()
         *  @sa BlackCore::getErrorsFromCore()
         */
        errorCore *coreErrors;


        /*! @brief @b Export @b file opening error.
        *
        *  Its value can change, when exporting pin, at@n
        *  @li doExport()
        *
        *  function in BlackCoreGPIO class.
        *  @sa BlackCoreGPIO::doExport()
        */
        bool exportFileError;


        /*! @brief @b Direction @b file opening error.
        *
        *  Its value can change, when setting direction of pin, at@n
        *  @li setDirection()
        *
        *  function in BlackCoreGPIO class.
        *  @sa BlackCoreGPIO::setDirection()
        */
        bool directionFileError;


        /*! @brief errorCoreGPIO struct's constructor.
         *
         *  This function clears all flags and initializes errorCore struct.
         */
        errorCoreGPIO()
        {
            exportFileError     = false;
            directionFileError  = false;
            coreErrors          = new errorCore();
        }


        /*! @brief errorCoreGPIO struct's constructor with errorCore pointer parameter.
         *
         * @param [in] *base    pointer of errorCore struct.
         *
         *  This function clears all flags and assigns input parameter to coreErrors variable.
         */
        errorCoreGPIO(errorCore *base)
        {
            exportFileError     = false;
            directionFileError  = false;
            coreErrors          = base;
        }
    };




    /*! @brief Holds BlackGPIO errors.
     *
     *    This struct holds GPIO errors and includes pointer of errorCoreGPIO struct.
     */
    struct errorGPIO
    {
        /*! @brief Pointer of errorCoreGPIO struct, which stores errors of BlackCoreGPIO class.
        *
        *  This struct initializes at constructor in BlackGPIO class.@n
        *  Its value can set with @n
        *  @li getErrorsFromCoreGPIO()
        *
        *  function in BlackCoreGPIO class.
        *  @sa BlackGPIO::BlackGPIO()
        *  @sa BlackCoreGPIO::getErrorsFromCoreGPIO()
        */
        errorCoreGPIO *gpioCoreErrors;


        /*! @brief Pin @b couldn't @b export error.
        *
        *  Its value can change, when checking GPIO pin's export status, at@n
        *  @li isExported()
        *  @li isReady()
        *  @li getValue()
        *  @li isHigh()
        *  @li toggleValue()
        *  @li setValue()
        *  @li operator>>()
        *  @li operator<<()
        *
        *  functions in BlackGPIO class, if working mode is secureMode.
        *  @sa BlackGPIO::isExported()
        *  @sa BlackGPIO::isReady()
        *  @sa BlackGPIO::getValue()
        *  @sa BlackGPIO::isHigh()
        *  @sa BlackGPIO::toggleValue()
        *  @sa BlackGPIO::setValue()
        *  @sa BlackGPIO::operator>>(std::string &)
        *  @sa BlackGPIO::operator>>(int &)
        *  @sa BlackGPIO::operator<<(BlackLib::digitalValue)
        */
        bool exportError;


        /*! @brief Pin direction @b couldn't @b set error.
        *
        *  Its value can change, when checking GPIO pin's direction, at@n
        *  @li isDirectionSet()
        *  @li isReady()
        *  @li getValue()
        *  @li isHigh()
        *  @li toggleValue()
        *  @li setValue()
        *  @li operator>>()
        *  @li operator<<()
        *
        *  functions in BlackGPIO class, if working mode is secureMode.
        *  @sa BlackGPIO::isDirectionSet()
        *  @sa BlackGPIO::isReady()
        *  @sa BlackGPIO::getValue()
        *  @sa BlackGPIO::isHigh()
        *  @sa BlackGPIO::toggleValue()
        *  @sa BlackGPIO::setValue()
        *  @sa BlackGPIO::operator>>(std::string &)
        *  @sa BlackGPIO::operator>>(int &)
        *  @sa BlackGPIO::operator<<(BlackLib::digitalValue)
        */
        bool directionError;


        /*! @brief @b Value @b file reading error.
        *
        *  Its value can change, when opening gpio pin's value file, at@n
        *  @li getValue()
        *  @li getNumericValue()
        *  @li isHigh()
        *  @li toggleValue()
        *  @li operator>>()
        *
        *  functions in BlackGPIO class.
        *  @sa BlackGPIO::getValue()
        *  @sa BlackGPIO::getNumericValue()
        *  @sa BlackGPIO::isHigh()
        *  @sa BlackGPIO::toggleValue()
        *  @sa BlackGPIO::operator>>(std::string &)
        *  @sa BlackGPIO::operator>>(int &)
        */
        bool readError;


        /*! @brief @b Value @b file writing error.
        *
        *  Its value can change, when opening gpio pin's value file, at@n
        *  @li setValue()
        *  @li operator<<()
        *
        *  function in BlackGPIO class.
        *  @sa BlackGPIO::setValue()
        *  @sa BlackGPIO::operator<<(BlackLib::digitalValue)
        */
        bool writeError;


        /*! @brief Pin @b write forcing error.
        *
        *  Its value can change, when trying to write something to input type gpio pin, at@n
        *  @li setValue()
        *
        *  function in BlackGPIO class.
        *  @sa BlackGPIO::setValue()
        *  @sa BlackGPIO::operator<<(BlackLib::digitalValue)
        */
        bool forcingError;


        /*! @brief errorGPIO struct's constructor.
         *
         *  This function clears all flags and initializes errorCoreGPIO struct.
         */
        errorGPIO()
        {
            exportError     = false;
            directionError  = false;
            readError       = false;
            writeError      = false;
            forcingError    = false;
            gpioCoreErrors  = new errorCoreGPIO();
        }


        /*! @brief errorGPIO struct's constructor with errorCoreGPIO pointer parameter.
         *
         *  @param [in] *base    pointer of errorCoreGPIO struct.
         *
         *  This function clears all flags and assigns input parameter to gpioCoreErrors variable.
         */
        errorGPIO(errorCoreGPIO *base)
        {
            exportError     = false;
            directionError  = false;
            readError       = false;
            writeError      = false;
            forcingError    = false;
            gpioCoreErrors  = base;
        }
    };




    /*! @brief Holds BlackUART errors.
     *
     *    This struct holds UART errors and includes pointer of errorCore struct.
     */
    struct errorUART
    {
        /*! @brief Pointer of errorCore struct, which stores errors of BlackCore class.
         *
         *  This struct initializes at constructor in BlackUART class.@n
         *  Its value can set with @n
         *  @li getErrorsFromCore()
         *
         *  function in BlackUART class.
         *  @sa BlackUART::BlackUART()
         *  @sa BlackCore::getErrorsFromCore()
         */
        errorCore *coreErrors;


        /*! @brief @b Device @b tree loading error.
        *
        *  Its value can change, when loading uart overlay to device tree, at@n
        *  @li loadDeviceTree()
        *
        *  function in BlackUART class.
        *  @sa BlackUART::loadDeviceTree()
        */
        bool dtError;


        /*! @brief TTY file @b opening error.
        *
        *  Its value can change, when opening uart's tty file, at@n
        *  @li open()
        *
        *  function in BlackUART class.
        *  @sa BlackUART::open()
        */
        bool openError;

        /*! @brief TTY file @b closing error.
        *
        *  Its value can change, when closing uart's tty file, at@n
        *  @li close()
        *
        *  function in BlackUART class.
        *  @sa BlackUART::close()
        */
        bool closeError;


        /*! @brief Some uart operation's direction error.
        *
        *  Its value can change, when doing some operations to UART, at@n
        *  @li setBaudRate()
        *  @li flush()
        *
        *  functions in BlackUART class.
        *  @sa BlackUART::setBaudRate()
        *  @sa BlackUART::flush()
        */
        bool directionError;


        /*! @brief UART line flushing error.
        *
        *  Its value can change, when flushing line, at@n
        *  @li flush()
        *
        *  function in BlackUART class.
        *  @sa BlackUART::flush()
        */
        bool flushError;


        /*! @brief TTY file @b reading error.
        *
        *  Its value can change, when reading uart's tty file, at@n
        *  @li read()
        *  @li transfer()
        *  @li operator>>()
        *
        *  functions in BlackUART class.
        *  @sa BlackUART::read(char*, size_t)
        *  @sa BlackUART::read()
        *  @sa BlackUART::transfer(char*, char*, size_t, uint32_t)
        *  @sa BlackUART::transfer(std::string, uint32_t)
        *  @sa BlackUART::operator>>(std::string &)
        */
        bool readError;


        /*! @brief TTY file @b writing error.
        *
        *  Its value can change, when writing uart's tty file, at@n
        *  @li write()
        *  @li transfer()
        *  @li operator<<()
        *
        *  functions in BlackUART class.
        *  @sa BlackUART::write(char*, size_t)
        *  @sa BlackUART::write(std::string)
        *  @sa BlackUART::transfer(char*, char*, size_t, uint32_t)
        *  @sa BlackUART::transfer(std::string, uint32_t)
        *  @sa BlackUART::operator<<(std::string &)
        */
        bool writeError;


        /*! @brief UART's @b baud property setting error.
        *
        *  Its value can change, when setting uart's baud property, at@n
        *  @li getBaudRate()
        *  @li setBaudRate()
        *  @li getProperties()
        *  @li setProperties()
        *
        *  functions in BlackUART class.
        *  @sa BlackUART::getBaudRate()
        *  @sa BlackUART::setBaudRate()
        *  @sa BlackUART::getProperties()
        *  @sa BlackUART::setProperties()
        */
        bool baudRateError;


        /*! @brief UART's @b parity property setting error.
        *
        *  Its value can change, when setting uart's parity property, at@n
        *  @li getParity()
        *  @li setParity()
        *  @li getProperties()
        *  @li setProperties()
        *
        *  functions in BlackUART class.
        *  @sa BlackUART::getParity()
        *  @sa BlackUART::setParity()
        *  @sa BlackUART::getProperties()
        *  @sa BlackUART::setProperties()
        */
        bool parityError;


        /*! @brief UART's @b stop @b bits property setting error.
        *
        *  Its value can change, when setting uart's stop bits property, at@n
        *  @li getStopBits()
        *  @li setParity()
        *  @li getProperties()
        *  @li setProperties()
        *
        *  functions in BlackUART class.
        *  @sa BlackUART::getStopBits()
        *  @sa BlackUART::setStopBits()
        *  @sa BlackUART::getProperties()
        *  @sa BlackUART::setProperties()
        */
        bool stopBitsError;


        /*! @brief UART's @b character @b size property setting error.
        *
        *  Its value can change, when setting uart's character size property, at@n
        *  @li getCharacterSize()
        *  @li setCharacterSize()
        *  @li getProperties()
        *  @li setProperties()
        *
        *  functions in BlackUART class.
        *  @sa BlackUART::getCharacterSize()
        *  @sa BlackUART::setCharacterSize()
        *  @sa BlackUART::getProperties()
        *  @sa BlackUART::setProperties()
        */
        bool charSizeError;


        /*! @brief errorUART struct's constructor.
         *
         *  This function clears all flags and initializes errorCore struct.
         */
        errorUART()
        {
            dtError         = false;
            openError       = false;
            closeError      = false;
            directionError  = false;
            flushError      = false;
            readError       = false;
            writeError      = false;
            baudRateError   = false;
            parityError     = false;
            stopBitsError   = false;
            charSizeError   = false;
            coreErrors      = new errorCore();
        }


        /*! @brief errorUART struct's constructor with errorCore pointer parameter.
         *
         *  @param [in] *base    pointer of errorCore struct.
         *
         *  This function clears all flags and assigns input parameter to coreErrors variable.
         */
        errorUART(errorCore *base)
        {
            dtError         = false;
            openError       = false;
            closeError      = false;
            directionError  = false;
            flushError      = false;
            readError       = false;
            writeError      = false;
            baudRateError   = false;
            parityError     = false;
            stopBitsError   = false;
            charSizeError   = false;
            coreErrors      = base;
        }
    };




    /*! @brief Holds BlackSPI errors.
     *
     *    This struct holds SPI errors and includes pointer of errorCore struct.
     */
    struct errorSPI
    {
        /*! @brief Pointer of errorCore struct, which stores errors of BlackCore class.
         *
         *  This struct initializes at constructor in BlackSPI class.@n
         *  Its value can set with @n
         *  @li getErrorsFromCore()
         *
         *  function in BlackSPI class.
         *  @sa BlackSPI::BlackSPI()
         *  @sa BlackCore::getErrorsFromCore()
         */
        errorCore *coreErrors;


        /*! @brief @b Device @b tree loading error.
        *
        *  Its value can change, when loading spi overlay to device tree, at@n
        *  @li loadDeviceTree()
        *
        *  function in BlackSPI class.
        *  @sa BlackSPI::loadDeviceTree()
        */
        bool dtError;


        /*! @brief TTY file @b opening error.
        *
        *  Its value can change, when opening spi's tty file, at@n
        *  @li open()
        *
        *  function in BlackSPI class.
        *  @sa BlackSPI::open()
        */
        bool openError;


        /*! @brief TTY file @b closing error.
        *
        *  Its value can change, when closing spi's tty file, at@n
        *  @li close()
        *
        *  function in BlackSPI class.
        *  @sa BlackSPI::close()
        */
        bool closeError;


        /*! @brief TTY file path finding error.
        *
        *  Its value can change, when finding spi's tty file path, at@n
        *  @li findPortPath()
        *
        *  function in BlackSPI class.
        *  @sa BlackSPI::findPortPath()
        */
        bool portPathError;


        /*! @brief SPI data transfer error.
        *
        *  Its value can change, when transfering data between master and slave, at@n
        *  @li transfer()
        *  @li operator<<()
        *
        *  function in BlackSPI class.
        *  @sa BlackSPI::transfer(uint8_t, uint16_t)
        *  @sa BlackSPI::transfer(uint8_t*, uint8_t*, size_t, uint16_t)
        */
        bool transferError;


        /*! @brief SPI's @b mode property setting error.
        *
        *  Its value can change, when setting spi's mode property, at@n
        *  @li setMode()
        *  @li getMode()
        *  @li setProperties()
        *  @li getProperties()
        *
        *  functions in BlackSPI class.
        *  @sa BlackSPI::setMode()
        *  @sa BlackSPI::getMode()
        *  @sa BlackSPI::setProperties()
        *  @sa BlackSPI::getProperties()
        */
        bool modeError;


        /*! @brief SPI's @b speed property setting error.
        *
        *  Its value can change, when setting spi's speed property, at@n
        *  @li setMaximumSpeed()
        *  @li getMaximumSpeed()
        *  @li setProperties()
        *  @li getProperties()
        *
        *  functions in BlackSPI class.
        *  @sa BlackSPI::setMaximumSpeed()
        *  @sa BlackSPI::getMaximumSpeed()
        *  @sa BlackSPI::setProperties()
        *  @sa BlackSPI::getProperties()
        */
        bool speedError;


        /*! @brief SPI's @b bit @b size property setting error.
        *
        *  Its value can change, when setting spi's bit size property, at@n
        *  @li setBitsPerWord()
        *  @li getBitsPerWord()
        *  @li setProperties()
        *  @li getProperties()
        *
        *  functions in BlackSPI class.
        *  @sa BlackSPI::setBitsPerWord()
        *  @sa BlackSPI::getBitsPerWord()
        *  @sa BlackSPI::setProperties()
        *  @sa BlackSPI::getProperties()
        */
        bool bitSizeError;


        /*! @brief errorSPI struct's constructor.
         *
         *  This function clears all flags and initializes errorCore struct.
         */
        errorSPI()
        {
            dtError         = false;
            openError       = false;
            closeError      = false;
            portPathError   = false;
            transferError   = false;
            modeError       = false;
            speedError      = false;
            bitSizeError    = false;
            coreErrors      = new errorCore();
        }


        /*! @brief errorSPI struct's constructor with errorCore pointer parameter.
         *
         *  @param [in] *base    pointer of errorCore struct.
         *
         *  This function clears all flags and assigns input parameter to coreErrors variable.
         */
        errorSPI(errorCore *base)
        {
            dtError         = false;
            openError       = false;
            closeError      = false;
            portPathError   = false;
            transferError   = false;
            modeError       = false;
            speedError      = false;
            bitSizeError    = false;
            coreErrors      = base;
        }
    };




    /*! @brief Holds BlackI2C errors.
     *
     *    This struct holds I2C errors and includes pointer of errorCore struct.
     */
    struct errorI2C
    {
        /*! @brief Pointer of errorCore struct, which stores errors of BlackCore class.
         *
         *  This struct initializes at constructor in BlackI2C class.@n
         *  Its value can set with @n
         *  @li getErrorsFromCore()
         *
         *  function in BlackI2C class.
         *  @sa BlackI2C::BlackI2C()
         *  @sa BlackCore::getErrorsFromCore()
         */
        errorCore *coreErrors;


        /*! @brief TTY file @b opening error.
        *
        *  Its value can change, when opening i2c's tty file, at@n
        *  @li open()
        *
        *  function in BlackI2C class.
        *  @sa BlackI2C::open()
        */
        bool openError;


        /*! @brief TTY file @b closing error.
        *
        *  Its value can change, when closing i2c's tty file, at@n
        *  @li close()
        *
        *  function in BlackI2C class.
        *  @sa BlackI2C::close()
        */
        bool closeError;


        /*! @brief Slave setting error.
        *
        *  Its value can change, when opening TTY file, doing i2c write/read operations and
        *  assigning new device address value at@n
        *  @li open()
        *  @li writeByte()
        *  @li writeWord()
        *  @li writeBlock()
        *  @li writeLine()
        *  @li readByte()
        *  @li readWord()
        *  @li readBlock()
        *  @li readLine()
        *  @li setDeviceAddress()
        *
        *  functions in BlackI2C class.
        *  @sa BlackI2C::open()
        *  @sa BlackI2C::writeByte()
        *  @sa BlackI2C::writeWord()
        *  @sa BlackI2C::writeBlock()
        *  @sa BlackI2C::writeLine()
        *  @sa BlackI2C::readByte()
        *  @sa BlackI2C::readWord()
        *  @sa BlackI2C::readBlock()
        *  @sa BlackI2C::readLine()
        *  @sa BlackI2C::setDeviceAddress()
        */
        bool setSlaveError;


        /*! @brief I2C @b reading error.
        *
        *  Its value can change, when reading i2c data, at@n
        *  @li readByte()
        *  @li readWord()
        *  @li readBlock()
        *  @li readLine()
        *
        *  functions in BlackI2C class.
        *  @sa BlackI2C::readByte()
        *  @sa BlackI2C::readWord()
        *  @sa BlackI2C::readBlock()
        *  @sa BlackI2C::readLine()
        */
        bool readError;

        /*! @brief I2C @b writing error.
        *
        *  Its value can change, when writing i2c data, at@n
        *  @li writeByte()
        *  @li writeWord()
        *  @li writeBlock()
        *  @li writeLine()
        *
        *  functions in BlackI2C class.
        *  @sa BlackI2C::writeByte()
        *  @sa BlackI2C::writeWord()
        *  @sa BlackI2C::writeBlock()
        *  @sa BlackI2C::writeLine()
        */
        bool writeError;


        /*! @brief BlackI2C struct's constructor.
         *
         *  This function clears all flags and initializes errorCore struct.
         */
        errorI2C()
        {
            openError       = false;
            closeError      = false;
            setSlaveError   = false;
            readError       = false;
            writeError      = false;
            coreErrors      = new errorCore();
        }


        /*! @brief BlackI2C struct's constructor with errorCore pointer parameter.
         *
         *  @param [in] *base    pointer of errorCore struct.
         *
         *  This function clears all flags and assigns input parameter to coreErrors variable.
         */
        errorI2C(errorCore *base)
        {
            openError       = false;
            closeError      = false;
            setSlaveError   = false;
            readError       = false;
            writeError      = false;
            coreErrors      = base;
        }
    };



} /* namespace BlackLib */

#endif /* BLACKERR_H_ */
