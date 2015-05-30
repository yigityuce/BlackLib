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

#ifndef BLACKADC_H_
#define BLACKADC_H_

#include "../BlackCore.h"

#include <cmath>           // need for round() function in BlackADC::getParsedValue()
#include <string>
#include <fstream>







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





    // ######################################### BLACKCOREADC DECLARATION STARTS ########################################## //

    /*! @brief Preparation phase of Beaglebone Black, to use ADC.
     *
     *    This class is core of the BlackADC class. It includes private functions which are doing base processes
     *    for using analog input feature.
     */
    class BlackCoreADC : virtual private BlackCore
    {
        private:
            errorCoreADC    *adcCoreErrors;         /*!< @brief is used to hold the errors of BlackCoreADC class */
            std::string     helperName;             /*!< @brief is used to hold the helper(analog input device driver) name */

            /*! @brief Loads ADC overlay to device tree.
            *
            *  This function loads @b "cape-bone-iio" overlay to device tree.
            *  This overlay performs pinmuxing and generates device driver.
            *  @return True if successful, else false.
            */
            bool            loadDeviceTree();

            /*! @brief Finds full name of helper.
            *
            *  This function searches @b "ocp.X" directory, to find directory which starts with
            *  @b "helper." by using searchDirectoryOcp() protected function at BlackCore class.
            *  @return True if successful, else false.
            *  @sa BlackCore::searchDirectoryOcp()
            */
            bool            findHelperName();



        protected:

            /*! @brief Exports helper path to derived class.
            *
            *  @return Full path of helper.
            */
            std::string     getHelperPath();

            /*! @brief Exports errorCoreADC struct pointer to derived class.
            *
            *  @return errorCoreADC struct pointer.
            */
            errorCoreADC    *getErrorsFromCoreADC();



        public:

            /*! @brief Constructor of BlackCoreADC class.
            *
            * This function initializes errorCoreADC struct and calls device tree loading and
            * helper name finding functions.
            * @sa BlackCoreADC::loadDeviceTree()
            * @sa BlackCoreADC::findHelperName()
            * @sa adcName
            */
                            BlackCoreADC();

            /*! @brief Destructor of BlackCoreADC class.
            *
            * This function deletes errorCoreADC struct pointer.
            */
            virtual         ~BlackCoreADC();


            /*! @brief First declaration of this function.
            */
            virtual std::string getValue() = 0;
    };
    // ########################################## BLACKCOREADC DECLARATION ENDS ########################################### //











    // ########################################### BLACKADC DECLARATION STARTS ############################################ //

    /*! @brief Interacts with end user, to use ADC.
     *
     *    This class is end node to use analog inputs. End users interact with
     *    analog inputs from this class. It includes public functions for reading analog
     *    values.
     *
     * @par Example
      @verbatim
      EXAMPLE PROJECT FILE TREE:

         myAdcProject
         |-> src
             |-> BlackLib
                 |-> BlackDirectory
                     |-> BlackDirectory.cpp
                     |-> BlackDirectory.h
                 |-> BlackThread
                     |-> BlackThread.cpp
                     |-> BlackThread.h
                 |-> BlackMutex
                     |-> BlackMutex.cpp
                     |-> BlackMutex.h
                 |-> BlackTime
                     |-> BlackTime.cpp
                     |-> BlackTime.h
                 |-> BlackADC
                     |-> BlackADC.cpp
                     |-> BlackADC.h
                 |-> BlackGPIO
                     |-> BlackGPIO.cpp
                     |-> BlackGPIO.h
                 |-> BlackI2C
                     |-> BlackI2C.cpp
                     |-> BlackI2C.h
                 |-> BlackPWM
                     |-> BlackPWM.cpp
                     |-> BlackPWM.h
                 |-> BlackSPI
                     |-> BlackSPI.cpp
                     |-> BlackSPI.h
                 |-> BlackUART
                     |-> BlackUART.cpp
                     |-> BlackUART.h
                 |-> BlackCore.cpp
                 |-> BlackCore.h
                 |-> BlackDef.h
                 |-> BlackErr.h
                 |-> BlackLib.h
             |-> myAdcProject.cpp
      @endverbatim
     *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
     *  include BlackADC.h or another source files with adding this line to your project file (myAdcProject.cpp at
     *  the example):
     *  @code{.cpp}
     *      #include "BlackLib/BlackADC/BlackADC.h"
     *  @endcode
     *  @n@n If BlackLib source files are located at same level with your project file (myAdcProject.cpp at the
     *  example), you have to include BlackADC.h or another source files with adding this line to your project file:
     *  @code{.cpp}
     *      #include "BlackADC/BlackADC.h"
     *  @endcode
     *  @n @n
     *  @code{.cpp}
     *  // Filename: myAdcProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackADC/BlackADC.h"
     *
     *  int main()
     *  {
     *      BlackLib::BlackADC  myAdc(BlackLib::AIN0);
     *      std::cout << myAdc.getValue();
     *
     *      return 0;
     *  }
     * @endcode
     * @n @n
     * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
     * @code{.cpp}
     *  // Filename: myAdcProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackADC/BlackADC.h"
     *  using namespace BlackLib;
     *
     *  int main()
     *  {
     *      BlackADC  myAdc(AIN0);
     *      std::cout << myAdc.getValue();
     *
     *      return 0;
     *  }
     * @endcode
     *
     */
    class BlackADC : virtual private BlackCoreADC
    {
        private:
            errorADC        *adcErrors;             /*!< @brief is used to hold the errors of BlackADC class */
            std::string     ainPath;                /*!< @brief is used to hold the AINx file path */
            adcName         ainName;                /*!< @brief is used to hold the selected adc name */


        public:

            /*!
             * This enum is used to define ADC debugging flags.
             */
            enum flags      {   cpmgrErr    = 0,    /*!< enumeration for @a errorCore::capeMgrError status */
                                ocpErr      = 1,    /*!< enumeration for @a errorCore::ocpError status */
                                helperErr   = 2,    /*!< enumeration for @a errorCoreADC::helperError status */
                                dtErr       = 3,    /*!< enumeration for @a errorCoreADC::dtError status */
                                readErr     = 4     /*!< enumeration for @a errorADC::readError status */
                            };

            /*! @brief Constructor of BlackADC class.
            *
            * This function initializes errorADC struct and sets value path for reading analog values.
            *
            * @param [in] adc    name of adc (enum),(AINx)
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC  myAdc(BlackLib::AIN0);
            *   BlackLib::BlackADC *myAdcPtr = new BlackLib::BlackADC(BlackLib::AIN1);
            *
            *   std::cout << myAdc.getValue() << std::endl;
            *   std::cout << myAdcPtr->getValue();
            * @endcode
            *
            * @sa getHelperPath()
            * @sa adcName
            */
                            BlackADC(adcName adc);

            /*! @brief Destructor of BlackADC class.
            *
            * This function deletes errorADC struct pointer.
            */
            virtual         ~BlackADC();

            /*! @brief Reads analog input DC value(mV).
            *
            *  This function reads specified file from path, where defined
            *  at BlackADC::ainPath variable. This file holds analog input voltage at milivolt level.
            *  @return @a String type analog input value. If file opening fails, it returns
            *  BlackLib::FILE_COULD_NOT_OPEN_STRING.
            *
            * @par Example
            * @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   std::string val = myAdc.getValue();
            *   std::cout << "Analog mV Value: " << val << " mV";
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Analog mV Value: 1085 mV
            * @endcode
            */
            std::string     getValue();

            /*! @brief Reads analog input DC value(mV).
            *
            *  This function reads specified file from path, where defined at BlackADC::ainPath
            *  variable. This file holds analog input voltage at milivolt level.
            *  @return @a integer type analog input value. If file opening fails, it returns
            *  BlackLib::FILE_COULD_NOT_OPEN_INT.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   int val = myAdc.getNumericValue();
            *   std::cout << "Analog mV Value: " << val << " mV";
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Analog mV Value: 1085 mV
            * @endcode
            */
            int             getNumericValue();

            /*! @brief Reads converted analog input DC value(Volt).
            *
            * This function reads specified file from path, where defined at BlackADC::ainPath
            * variable. This file holds analog input voltage at milivolt level. Then converts this
            * value to volt level, according to input parameter.
            * @param [in] dap    convertion level (enum),(dapX) @a Expansion: digit after point
            * @return @a converted analog input value as float. If file opening fails, it returns
            *  BlackLib::FILE_COULD_NOT_OPEN_FLOAT.
            *
            * @par Example
            * @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   float converted_dap1 = myAdc.getConvertedValue(BlackLib::dap1);
            *   std::cout << "Analog Volt Value (in a.b form): " << converted_dap1 << " Volt" << std::endl;
            *
            *   usleep(1000);       // give some time to device
            *
            *   float converted_dap3 = myAdc.getConvertedValue(BlackLib::dap3);
            *   std::cout << "Analog Volt Value (in a.bcd form): " << converted_dap3 << " Volt" << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Analog Volt Value (in a.b form): 1.1 Volt
            *   // Analog Volt Value (in a.bcd form): 1.085 Volt
            * @endcode
            *
            * @sa digitAfterPoint
            */
            float           getConvertedValue(digitAfterPoint dap);

            /*! @brief Exports analog input pin name.
            *
            *  @return BlackADC::adcName variable.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   std::cout << "My adc name: AIN" << static_cast<int>(myAdc.getName()) << std::endl;
            *   std::cout << "My adc name: AIN" << (int)myAdc.getName() << std::endl;
            *   std::cout << "My adc name: AIN" << myAdc.getName() << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // My adc name: AIN0
            *   // My adc name: AIN0
            *   // My adc name: AIN0
            * @endcode
            */
            adcName         getName();

            /*! @brief Is used for general debugging.
            *
            * @return True if any error occured, else false.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   myAdc.getNumericValue();
            *
            *   if( myAdc.fail() )
            *   {
            *       std::cout << "ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "EVERYTHING IS OK" << std::endl;
            *   }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // EVERYTHING IS OK
            * @endcode
            *
            * @sa errorADC
            */
            bool            fail();

            /*! @brief Is used for specific debugging.
            *
            * You can use this function, after call BlackADC member functions in your code. The
            * input parameter is used for finding out status of selected error.
            * @param [in] f specific error type (enum)
            * @return Value of @a selected error.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   if( myAdc.fail(BlackLib::BlackADC::helperErr) or
            *       myAdc.fail(BlackLib::BlackADC::cpmgrErr) or
            *       myAdc.fail(BlackLib::BlackADC::ocpErr) or
            *       myAdc.fail(BlackLib::BlackADC::dtErr) )
            *   {
            *       std::cout << "BlackADC INITIALIZATION FAILED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "BlackADC INITIALIZATION IS OK" << std::endl;
            *   }
            *
            *
            *   myAdc.getValue();
            *
            *   if( myAdc.fail(BlackLib::BlackADC::readErr) )
            *   {
            *       std::cout << "READING ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "READING IS OK" << std::endl;
            *   }
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // BlackADC INITIALIZATION IS OK
            *   // READING IS OK
            * @endcode
            *
            * @sa errorADC
            */
            bool            fail(BlackADC::flags f);

            /*! @brief Reads analog input DC value(mV) with ">>" operator.
            *
            *  This function reads specified file from path, where defined at BlackADC::ainPath
            *  variable, with ">>" operator. This file holds analog input voltage at milivolt level.
            *  @param [in] &readToThis read value and save this value to this variable. If file opening
            *  fails, this functions sets BlackLib::FILE_COULD_NOT_OPEN_STRING to variable.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   std::string val;
            *   myAdc >> val;
            *   std::cout << "Analog mV Value: " << val << " mV";
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Analog mV Value: 1085 mV
            * @endcode
            */
            BlackADC&       operator>>(std::string &readToThis);

            /*! @brief Reads analog input DC value(mV) with ">>" operator.
            *
            *  This function reads specified file from path, where defined at BlackADC::ainPath
            *  variable, with ">>" operator. This file holds analog input voltage at milivolt level.
            *  @param [in] &readToThis read value and save this value to this variable. If file opening
            *  fails, this functions sets BlackLib::FILE_COULD_NOT_OPEN_INT to variable.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   int val;
            *   myAdc >> val;
            *   std::cout << "Analog mV Value: " << val << " mV";
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Analog mV Value: 1085 mV
            * @endcode
            */
            BlackADC&       operator>>(int &readToThis);

            /*! @brief Reads converted analog input DC value(volt) with ">>" operator.
            *
            *  This function reads specified file from path, where defined at BlackADC::ainPath
            *  variable, with ">>" operator. This file holds analog input voltage at milivolt level.
            *  Then converts this value to volt level at BlackLib::dap3 mode.
            *  @param [in] &readToThis read value and save this value to this variable. If file opening
            *  fails, this functions sets BlackLib::FILE_COULD_NOT_OPEN_FLOAT to variable.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackADC myAdc(BlackLib::AIN0);
            *
            *   float val;
            *   myAdc >> val;
            *   std::cout << "Analog Volt Value (in a.bcd form): " << val << " Volt" << std::endl;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Analog Volt Value (in a.bcd form): 1.085 Volt
            * @endcode
            *
            *  @sa getConvertedValue()
            */
            BlackADC&       operator>>(float &readToThis);
    };
    // ############################################ BLACKADC DECLARATION ENDS ############################################# //


} /* namespace BlackLib */

#endif /* BLACKADC_H_ */
