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

#ifndef BLACKGPIO_H_
#define BLACKGPIO_H_

#include "../BlackCore.h"

#include <fstream>
#include <string>





namespace BlackLib
{

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



    // ######################################### BLACKCOREGPIO DECLARATION STARTS ######################################### //

    /*! @brief Preparation phase of Beaglebone Black, to use GPIO.
     *
     *    This class is core of the BlackGPIO class. It includes private functions which are doing base processes
     *    for using gpio pins, and protected functions which are using for exporting private variables to
     *    derived class(es).
     */
    class BlackCoreGPIO : virtual private BlackCore
    {
        private:
            errorCoreGPIO   *gpioCoreError;         /*!< @brief is used to hold the errors of BlackCoreGPIO class */
            int             pinNumericName;         /*!< @brief is used to hold the selected pin number */
            int             pinNumericType;         /*!< @brief is used to hold the selected pin direction */
            std::string     expPath;                /*!< @brief is used to hold the @a export file path */
            std::string     directionPath;          /*!< @brief is used to hold the @a direction file path */
            std::string     unExpPath;              /*!< @brief is used to hold the @a unexport file path */


            /*! @brief Device tree loading is not necessary for using GPIO feature.
            *
            *  But this function have to declare in this class again. Because it is a pure virtual
            *  function. It does nothing.
            *  @return false all time.
            */
            bool            loadDeviceTree();

            /*! @brief Exports pin.
            *
            *  This function exports pin. This step is necessary.
            *  @return True if exporting is successful, else false.
            */
            bool            doExport();

            /*! @brief Sets pin direction.
            *
            *  This function sets pin direction to input or output. Pin directions are input at default.
            *  @return True if setting direction is successful, else false.
            */
            bool            setDirection();

            /*! @brief Unexports pin to release it.
            *
            *  This function is reverse of pin exporting. But this step is not necessary.
            *  @return True if unexporting is successful, else false.
            */
            bool            doUnexport();

        protected:

            /*! @brief Exports direction file path to derived class.
            *
            *  @return BlackCoreGPIO::directionPath variable.
            */
            std::string     getDirectionFilePath();

            /*! @brief Exports value file path to derived class.
            *
            *  @return BlackCoreGPIO::valuePath variable.
            */
            std::string     getValueFilePath();

            /*! @brief Exports errorCoreGPIO struct to derived class.
            *
            *  @return errorCoreGPIO struct pointer.
            */
            errorCoreGPIO   *getErrorsFromCoreGPIO();

        public:

            /*! @brief Constructor of BlackCoreGPIO class.
            *
            * This function initializes errorCoreGPIO struct, sets file path variables
            * and calls exporting and setting direction functions.
            *
            * @sa BlackCoreGPIO::doExport()
            * @sa BlackCoreGPIO::setDirection()
            * @sa gpioName
            * @sa direction
            */
                            BlackCoreGPIO(gpioName pin, direction dir);


            /*! @brief Destructor of BlackCoreGPIO class.
            *
            * This function unexports pin and deletes errorCoreGPIO struct pointer.
            */
            virtual         ~BlackCoreGPIO();

            /*! @brief First declaration of this function.
            */
            virtual std::string getValue() = 0;

    };
    // ########################################## BLACKCOREGPIO DECLARATION ENDS ########################################## //










    // ########################################### BLACKGPIO DECLARATION STARTS ########################################### //

    /*! @brief Interacts with end user, to use GPIO.
     *
     *    This class is end node to use GPIO. End users interact with gpio pins from this class.
     *    It includes public functions to set and get properties of GPIO.
     * @par Example
      @verbatim
      EXAMPLE PROJECT FILE TREE:

         myGpioProject
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
             |-> myGpioProject.cpp
      @endverbatim
     *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
     *  include BlackGPIO.h or another source files with adding this line to your project file (myGpioProject.cpp at
     *  the example):
     *  @code{.cpp}
     *      #include "BlackLib/BlackGPIO/BlackGPIO.h"
     *  @endcode
     *  @n@n If BlackLib source files are located at same level with your project file (myGpioProject.cpp at the
     *  example), you have to include BlackGPIO.h or another source files with adding this line to your project file:
     *  @code{.cpp}
     *      #include "BlackGPIO/BlackGPIO.h"
     *  @endcode
     *  @n @n
     *  @code{.cpp}
     *  // Filename: myGpioProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackGPIO/BlackGPIO.h"
     *
     *  int main()
     *  {
     *      BlackLib::BlackGPIO  myGpio(BlackLib::GPIO_30, BlackLib::input);
     *      std::cout << myGpio.getValue();
     *
     *      return 0;
     *  }
     * @endcode
     * @n @n
     * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
     * @code{.cpp}
     *  // Filename: myGpioProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackGPIO/BlackGPIO.h"
     *  using namespace BlackLib;
     *
     *  int main()
     *  {
     *      BlackGPIO  myGpio(GPIO_30, input);
     *      std::cout << myGpio.getValue();
     *
     *      return 0;
     *  }
     * @endcode
     *
     */
    class BlackGPIO : virtual private BlackCoreGPIO
    {
        private:
            errorGPIO       *gpioErrors;                    /*!< @brief is used to hold the errors of BlackGPIO class */
            gpioName        pinName;                        /*!< @brief is used to hold the selected GPIO pin name */
            direction       pinDirection;                   /*!< @brief is used to hold the selected GPIO pin direction */
            workingMode     workMode;                       /*!< @brief is used to hold the selected working mode */
            std::string     valuePath;                      /*!< @brief is used to hold the value file path */

            /*! @brief Checks the export state of GPIO pin.
            *
            * This function reads specified file from path, where defined at BlackGPIO::valuePath variable.
            * If this file could open successfully, this means pin is exported successfully.
            * @return False if file opening fails, else true.
            */
            bool            isExported();

            /*! @brief Checks direction of GPIO pin.
            *
            * This function reads specified file from path, where defined at BlackGPIO::directionPath variable.
            * @return True if direction file can open successfully and its value is equal to defined direction when
            * class initialization, else false.
            */
            bool            isDirectionSet();

            /*! @brief Checks ready state of GPIO pin.
            *
            * This function calls isExported() and isDirectionSet() functions and then evaluates return
            * values of these functions.
            * @return True if both functions return true, else false.
            * @sa isExported()
            * @sa isDirectionSet()
            */
            bool            isReady();


        public:

            /*!
            * This enum is used to define GPIO debugging flags.
            */
            enum flags      {   exportFileErr       = 0,    /*!< enumeration for @a errorCoreGPIO::exportFileError status */
                                exportErr           = 1,    /*!< enumeration for @a errorGPIO::exportError status */
                                directionFileErr    = 2,    /*!< enumeration for @a errorCoreGPIO::directionFileError status */
                                directionErr        = 3,    /*!< enumeration for @a errorGPIO::directionError status */
                                readErr             = 4,    /*!< enumeration for @a errorGPIO::readError status */
                                writeErr            = 5,    /*!< enumeration for @a errorGPIO::writeError status */
                                forcingErr          = 6,    /*!< enumeration for @a errorGPIO::forcingError status */
                            };

            /*! @brief Constructor of BlackGPIO class.
            *
            * This function initializes BlackCoreGPIO class with entered parameters and errorGPIO struct.
            * Then it sets value file path variable.
            * @param [in] pn        gpio pin name(enum)
            * @param [in] pd        gpio pin direction(enum)
            * @param [in] wm        working mode(enum), default value is SecureMode
            *
            * @par Example
            *  @code{.cpp}
            *   // Pin:30 - Direction:Out - Working Mode:SecureMode
            *   BlackLib::BlackGPIO  myGpio(BlackLib::GPIO_30, BlackLib::output);
            *
            *   // Pin:60 - Direction:Out - Working Mode:FastMode
            *   BlackLib::BlackGPIO  myGpio2(BlackLib::GPIO_60, BlackLib::output, BlackLib::FastMode);
            *
            *   // Pin:40 - Direction:In - Working Mode:SecureMode
            *   BlackLib::BlackGPIO *myGpioPtr = new BlackLib::BlackGPIO(BlackLib::GPIO_40, BlackLib::input);
            *
            *   myGpio.getValue();
            *   myGpio2.getValue();
            *   myGpioPtr->getValue();
            *
            * @endcode
            *
            * @sa gpioName
            * @sa direction
            * @sa workingMode
            */
                            BlackGPIO(gpioName pn, direction pd, workingMode wm = SecureMode);

            /*! @brief Destructor of BlackGPIO class.
            *
            * This function deletes errorGPIO struct pointer.
            */
            virtual         ~BlackGPIO();

            /*! @brief Reads value of gpio pin as string type.
            *
            * If working mode is selected SecureMode, this function checks pin ready state by calling isReady() function.
            * If pin is not ready, function returns with BlackLib::GPIO_PIN_NOT_READY_STRING value. If working mode is
            * selected FastMode, ready state checking will skip. Then it reads specified file from path, where defined at
            * BlackGPIO::valuePath variable. This file holds gpio pin value.
            * @return @a string type GPIO pin value. If file opening fails, it returns BlackLib::FILE_COULD_NOT_OPEN_STRING
            * or if pin isn't ready, it returns BlackLib::GPIO_PIN_NOT_READY_STRING.
            *
            * @par Example
            * @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   std::string val = myGpio.getValue();
            *   std::cout << "Gpio30 Value: " << val;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Gpio30 Value: 1
            * @endcode
            */
            std::string     getValue();

            /*! @brief Reads value of gpio pin as int type.
            *
            * If working mode is selected SecureMode, this function checks pin ready state by calling isReady() function.
            * If pin is not ready, function returns with BlackLib::GPIO_PIN_NOT_READY_INT value. If working mode is
            * selected FastMode, ready state checking will skip. Then it reads specified file from path, where defined at
            * BlackGPIO::valuePath variable. This file holds gpio pin value.
            * @return @a int type GPIO pin value. If file opening fails, it returns BlackLib::FILE_COULD_NOT_OPEN_INT
            * or if pin isn't ready, it returns BlackLib::GPIO_PIN_NOT_READY_INT.
            *
            * @par Example
            * @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   int val = myGpio.getNumericValue();
            *   std::cout << "Gpio30 Value: " << val;
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Gpio30 Value: 1
            * @endcode
            */
            int             getNumericValue();

            /*! @brief Exports name of gpio pin.
            *
            *  @return BlackGPIO::pinName variable.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   std::cout << "My gpio name: GPIO_" << static_cast<int>(myGpio.getName()) << std::endl;
            *   std::cout << "My gpio name: GPIO_" << (int)myGpio.getName() << std::endl;
            *   std::cout << "My gpio name: GPIO_" << myGpio.getName() << std::endl;
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // My gpio name: GPIO_30
            *   // My gpio name: GPIO_30
            *   // My gpio name: GPIO_30
            *  @endcode
            */
            gpioName        getName();

            /*! @brief Exports direction of gpio pin.
            *
            *  @return BlackGPIO::pinDirection variable.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   std::cout << "Values: input=1, output=2, bothDirection=3" << std::endl << std::endl;
            *
            *   std::cout << "My gpio direction: " << static_cast<int>(myGpio.getDirection()) << std::endl;
            *   std::cout << "My gpio direction: " << (int)myGpio.getDirection() << std::endl;
            *   std::cout << "My gpio direction: " << myGpio.getDirection() << std::endl;
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // Values: input=1, output=2, bothDirection=3
            *   //
            *   // My gpio direction: 2
            *   // My gpio direction: 2
            *   // My gpio direction: 2
            *  @endcode
            */
            direction       getDirection();

            /*! @brief Sets value of GPIO pin.
            *
            * If pin direction is not output, function returns with false value. If working mode is selected SecureMode,
            * this function checks pin ready state by calling isReady() function. If pin is not ready, function returns
            * with false value. If working mode is selected FastMode, ready state checking will skip. Then the input
            * parameter is converted to 1 or 0 and this value is saved to value file.
            * @param [in] v new pin value(enum)
            * @return True if setting new value is successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *   BlackLib::BlackGPIO myGpio2(BlackLib::GPIO_60, BlackLib::input, BlackLib::SecureMode);
            *
            *   if( myGpio.setValue(BlackLib::high) )
            *   {
            *       std::cout << "Gpio 30 set high successfully." << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "Gpio 30 couldn't set." << std::endl;
            *   }
            *
            *   if( myGpio2.setValue(BlackLib::low) )
            *   {
            *       std::cout << "Gpio 60 set low successfully (This is not possible)." << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << std::endl << "Gpio 60 couldn't set. Because this pin's direction is input."
            *                 << std::endl << "You can't write anything to input type pin." << std::endl;
            *   }
            *
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // Gpio 30 set high successfully.
            *   //
            *   // Gpio 60 couldn't set. Because this pin's direction is input.
            *   // You can't write anything to input type pin.
            *  @endcode
            *
            * @sa digitalValue
            */
            bool            setValue(digitalValue v);

            /*! @brief Checks value of GPIO pin.
            *
            * This function calls getNumericValue() function and evaluates return value.
            * @return True if return value equals 1, else false.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   myGpio.setValue(BlackLib::high);
            *   std::cout << std::boolalpha << myGpio.isHigh() << std::endl;
            *
            *   if( myGpio.isHigh() )
            *   {
            *       std::cout << "Do something with me, i am high." << std::endl;
            *   }
            *
            *   myGpio.setValue(BlackLib::low);
            *   std::cout << ( myGpio.isHigh() ? "yeap" : "nope") << std::endl;
            *
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // true
            *   // Do something with me, i am high.
            *   // nope
            *  @endcode
            *
            * @sa getNumericValue()
            */
            bool            isHigh();

            /*! @brief Toggles value of GPIO pin.
            *
            * If pin direction is output, this function sets pin value to 1 or 0, by value of current state.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   myGpio.setValue(BlackLib::high);
            *   std::cout << "Before toggle: " << std::boolalpha << myGpio.isHigh() << std::endl;
            *
            *   myGpio.toggleValue();
            *   std::cout << "After toggle: " << std::boolalpha << myGpio.isHigh() << std::endl;
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // Before toggle: true
            *   // After toggle: false
            *  @endcode
            */
            void            toggleValue();

            /*! @brief Changes working mode.
            *
            * This function sets new working mode value to BlackGPIO::workingMode variable.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   myGpio.setWorkingMode(BlackLib::FastMode);
            *   std::cout << "Now you can be more faster than the previous one, but MAYBE." << std::endl;
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // Now you can be more faster than the previous one, but MAYBE.
            *  @endcode
            */
            void            setWorkingMode(workingMode newWM);

            /*! @brief Exports working mode value.
            *
            *  @return BlackLib::workingMode variable.
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   std::cout << "Your current working mode is "
            *             << ( (myGpio.getWorkingMode() == BlackLib::SecureMode) ? "Secure Mode" : "Fast Mode" ) << std::endl;
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // Your current working mode is Secure Mode
            *  @endcode
            */
            workingMode     getWorkingMode();


            /*! @brief Is used for general debugging.
            *
            * @return True if any error occured, else false.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   myGpio.getNumericValue();
            *
            *   if( myGpio.fail() )
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
            * @sa errorGPIO
            */
            bool            fail();

            /*! @brief Is used for specific debugging.
            *
            * You can use this function, after call BlackGPIO member functions in your code. The
            * input parameter is used for finding out status of selected error.
            * @param [in] f specific error type (enum)
            * @return Value of @a selected error.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   if( myGpio.fail(BlackLib::BlackGPIO::directionFileErr) or
            *       myGpio.fail(BlackLib::BlackGPIO::exportFileErr) )
            *   {
            *        std::cout << "GPIO30: BlackGPIO INITIALIZATION FAILED" << std::endl;
            *   }
            *
            *   myGpio.setValue(BlackLib::high);
            *   if( myGpio.fail(BlackLib::BlackGPIO::directionErr) or
            *       myGpio.fail(BlackLib::BlackGPIO::exportErr) )
            *   {
            *        std::cout << "GPIO30: You are in secure mode and isReady() function failed." << std::endl;
            *   }
            *
            *   if( myGpio.fail(BlackLib::BlackGPIO::forcingErr) )
            *   {
            *        std::cout << "GPIO30: You are tried to set some value to input type pin."
            *                  << " This operation is not valid." << std::endl;
            *   }
            *
            *   if( myGpio.fail(BlackLib::BlackGPIO::writeErr) )
            *   {
            *        std::cout << "GPIO30: You could not write anything." << std::endl;
            *   }
            *
            *
            *
            *   BlackLib::BlackGPIO myGpio2(BlackLib::GPIO_60, BlackLib::input, BlackLib::FastMode);
            *
            *   if( myGpio2.fail(BlackLib::BlackGPIO::directionFileErr) or
            *       myGpio2.fail(BlackLib::BlackGPIO::exportFileErr) )
            *   {
            *        std::cout << "GPIO60: BlackGPIO INITIALIZATION FAILED" << std::endl;
            *   }
            *
            *   myGpio2.setValue(BlackLib::high);
            *   if( myGpio2.fail(BlackLib::BlackGPIO::directionErr) or
            *       myGpio2.fail(BlackLib::BlackGPIO::exportErr) )
            *   {
            *        std::cout << "GPIO60: This is not meaningful. Because you are in fast mode and these flags" << std::endl
            *                  << "could not change in fast mode." << std::endl;
            *   }
            *
            *   if( myGpio2.fail(BlackLib::BlackGPIO::forcingErr) )
            *   {
            *       std::cout << "GPIO60: You are tried to set some value to input type pin."
            *                 << " This operation is not valid." << std::endl;
            *   }
            *
            *   if( myGpio2.fail(BlackLib::BlackGPIO::writeErr) )
            *   {
            *        std::cout << "GPIO60: You could not write anything." << std::endl;
            *   }
            *
            *   myGpio2.getValue();
            *   if( ! myGpio2.fail(BlackLib::BlackGPIO::readErr) )
            *   {
            *        std::cout << "GPIO60: You are read some value from GPIO60 successfully." << std::endl;
            *   }
            *
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // GPIO60: You are tried to set some value to input type pin. This operation is not valid.
            *   // GPIO60: You could not write anything.
            *   // GPIO60: You are read some value from GPIO60 successfully.
            *  @endcode
            *
            * @sa errorGPIO
            */
            bool            fail(BlackGPIO::flags f);

            /*! @brief Reads value of gpio pin as string type with ">>" operator.
            *
            * If working mode is selected SecureMode, this function checks pin ready state by calling isReady() function.
            * If working mode is selected FastMode, ready state checking will skip. Then it reads specified file from path,
            * where defined at BlackGPIO::valuePath variable, with ">>" operator. This file holds gpio pin value.
            * @param [in] &readToThis read value and save this value to this variable. If file opening fails, this
            * functions sets BlackLib::FILE_COULD_NOT_OPEN_STRING to variable or if pin isn't ready, it sets
            * BlackLib::GPIO_PIN_NOT_READY_STRING.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   myGpio << BlackLib::high;
            *
            *   std::string val;
            *   myGpio >> val;
            *
            *   std::cout << "Current value: " << val << std::endl;
            *
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // Current value: 1
            *  @endcode
            */
            BlackGPIO&      operator>>(std::string &readToThis);

            /*! @brief Reads value of gpio pin as int type with ">>" operator.
            *
            * If working mode is selected SecureMode, this function checks pin ready state by calling isReady() function.
            * If working mode is selected FastMode, ready state checking will skip. Then it reads specified file from path,
            * where defined at BlackGPIO::valuePath variable, with ">>" operator. This file holds gpio pin value.
            * @param [in] &readToThis read value and save this value to this variable. If file opening fails, this
            * functions sets BlackLib::FILE_COULD_NOT_OPEN_INT to variable or if pin isn't ready, it sets
            * BlackLib::GPIO_PIN_NOT_READY_INT.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   myGpio << BlackLib::high;
            *
            *   int val;
            *   myGpio >> val;
            *
            *   std::cout << "Current value: " << val << std::endl;
            *
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // Current value: 1
            *  @endcode
            */
            BlackGPIO&      operator>>(int &readToThis);

            /*! @brief Sets value of GPIO pin with "<<" operator.
            *
            *  If pin direction is not output, function does nothing. If working mode is selected SecureMode, this function
            *  checks pin ready state by calling isReady() function. If pin is not ready, function does nothing. If working
            *  mode is selected FastMode, ready state checking will skip. Then the input parameter is saved to value file.
            *  @param [in] &value new pin value(enum)
            *
            *  @par Example
            *  @code{.cpp}
            *   BlackLib::BlackGPIO myGpio(BlackLib::GPIO_30, BlackLib::output, BlackLib::SecureMode);
            *
            *   myGpio << BlackLib::high ;
            *   std::cout << std::boolalpha << myGpio.isHigh() << std::endl;
            *
            *   myGpio << BlackLib::low ;
            *   std::cout << std::boolalpha << myGpio.isHigh() << std::endl;
            *
            *  @endcode
            *  @code{.cpp}
            *   // Possible Output:
            *   // true
            *   // false
            *  @endcode
            *
            *  @sa digitalValue
            */
            BlackGPIO&      operator<<(digitalValue value);
    };
    // ############################################ BLACKGPIO DECLARATION ENDS ############################################ //


} /* namespace BlackLib */

#endif /* BLACKGPIO_H_ */
