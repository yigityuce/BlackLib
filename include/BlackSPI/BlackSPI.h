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





#ifndef BLACKSPI_H_
#define BLACKSPI_H_


#include "../BlackCore.h"

#include <cstring>
#include <string>
#include <fstream>
#include <cstdint>
#include <unistd.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


using std::string;

namespace BlackLib
{

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









    // ######################################### BLACKSPIPROPERTIES DECLARATION STARTS ######################################### //

    /*! @brief Holds properties of SPI.
     *
     *    This struct holds bits per word, mode and speed properties of SPI. Also it has overloaded
     *    constructors and overloaded assign operator.
     */
    struct BlackSpiProperties
    {
        uint8_t     spiBitsPerWord;     /*!< @brief is used to hold the bits per word size of SPI */
        uint8_t     spiMode;            /*!< @brief is used to hold the mode of SPI */
        uint32_t    spiSpeed;           /*!< @brief is used to hold the speed of SPI */

        /*! @brief Default constructor of BlackSpiProperties struct.
         *
         *  This function sets default value to variables.
         */
        BlackSpiProperties()
        {
            spiBitsPerWord  = 0;
            spiMode         = 0;
            spiSpeed        = 0;
        }

        /*! @brief Overloaded constructor of BlackSpiProperties struct.
         *
         *  This function sets entered parameters to variables.
         */
        BlackSpiProperties(uint8_t bits, uint8_t mode, uint32_t speed)
        {
            spiBitsPerWord  = bits;
            spiMode         = mode;
            spiSpeed        = speed;
        }

        /*! @brief Overloaded constructor of BlackSpiProperties struct.
         *
         *  This function gets pointer of BlackSpiProperties struct and sets this pointed
         *  struct's variables to own variables.
         */
        BlackSpiProperties( BlackSpiProperties *self )
        {
            spiBitsPerWord  = self->spiBitsPerWord;
            spiMode         = self->spiMode;
            spiSpeed        = self->spiSpeed;
        }

        /*! @brief Overloaded assign operator of BlackSpiProperties struct.
         *
         *  This function assigns input struct's variables to own variables.
         */
        BlackSpiProperties& operator=(BlackSpiProperties equal)
        {
            spiBitsPerWord  = equal.spiBitsPerWord;
            spiMode         = equal.spiMode;
            spiSpeed        = equal.spiSpeed;
            return *this;
        }
    };
    // ########################################## BLACKSPIPROPERTIES DECLARATION ENDS ########################################### //





    // ########################################### BLACKSPI DECLARATION STARTS ############################################ //

    /*! @brief Interacts with end user, to use SPI.
     *
     *    This class is end node to use spi. End users interact with spi from this class.
     *    It includes public functions to set and get properties of spi's and to transfer datas.
     *    Spi has not capable of only read operation. For reading something from spi, user's
     *    must send dummy data.
     *
     *    @warning Users have to execute setup script before use spi. This is required for compiling
     *    and setting device tree overlays about spi.
     *
     *    @warning Spi speed can be 24000000 Hz(24 MHz) maximum.
     *
     *    @par Example
      @verbatim
      EXAMPLE PROJECT FILE TREE:

         mySpiProject
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
             |-> mySpiProject.cpp
      @endverbatim
     *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
     *  include BlackSPI.h or another source files with adding this line to your project file (mySpiProject.cpp at
     *  the example):
     *  @code{.cpp}
     *      #include "BlackLib/BlackSPI/BlackSPI.h"
     *  @endcode
     *  @n@n If BlackLib source files are located at same level with your project file (mySpiProject.cpp at the
     *  example), you have to include BlackSPI.h or another source files with adding this line to your project file:
     *  @code{.cpp}
     *      #include "BlackSPI/BlackSPI.h"
     *  @endcode
     *  @n @n
     *  @code{.cpp}
     *  // Filename: mySpiProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackSPI/BlackSPI.h"
     *
     *  int main()
     *  {
     *      BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
     *
     *      mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock);
     *
     *      uint8_t writeArr[4] = { 0x55, 0xaa, 0xf0, 0x0c };
     *      uint8_t readArr[4];
     *
     *      mySpi.transfer(writeArr, readArr, sizeof(writeArr), 100);
     *
     *      return 0;
     *  }
     * @endcode
     * @n @n
     * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
     * @code{.cpp}
     *  // Filename: mySpiProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackSPI/BlackSPI.h"
     *  using namespace BlackLib;
     *
     *  int main()
     *  {
     *      BlackSPI  mySpi(SPI0_0, 8, SpiDefault, 2400000);
     *
     *      mySpi.open( ReadWrite|NonBlock );
     *
     *      uint8_t writeArr[4] = { 0x55, 0xaa, 0xf0, 0x0c };
     *      uint8_t readArr[4];
     *
     *      mySpi.transfer(writeArr, readArr, sizeof(writeArr), 100);
     *
     *      return 0;
     *  }
     * @endcode
     */
    class BlackSPI : virtual private BlackCore
    {
        private:
            BlackSpiProperties constructorProperties;   /*!< @brief is used to hold the user specified properties of spi */
            BlackSpiProperties defaultProperties;       /*!< @brief is used to hold the default properties of spi */
            BlackSpiProperties currentProperties;       /*!< @brief is used to hold the current properties of spi */

            errorSPI        *spiErrors;                 /*!< @brief is used to hold the errors of BlackSPI class */

            std::string     spiPortPath;                /*!< @brief is used to hold the spi's tty port path */
            std::string     dtSpiFilename;              /*!< @brief is used to hold the spi's device tree overlay name */

            int             spiFD;                      /*!< @brief is used to hold the spi's tty file's file descriptor */
            int             spiBusNumber;               /*!< @brief is used to hold the spi's bus number */
            int             spiChipNumber;              /*!< @brief is used to hold the spi's chip number */
            bool            isCurrentEqDefault;         /*!< @brief is used to hold the properties of spi is equal to default properties */
            bool            isOpenFlag;                 /*!< @brief is used to hold the spi's tty file's state */

            /*! @brief Loads SPI overlay to device tree.
            *
            *  This function loads @b BlackSPI::dtSpiFilename overlay to device tree. This file name changes with
            *  spiName constructor parameter. This overlay performs pinmuxing and generates device driver.
            *  @warning BlackSPI class uses custom device tree overlays. Users must install these overlays firstly
            *  by executing setup script.
            *  @return True if successful, else false.
            */
            bool            loadDeviceTree();

            /*! @brief Finds SPI's port path and bus number.
            *
            *  The spi's TTY file name which located at "/dev/" directory, is differed to device tree overlay loading order.
            *  For example if users want to use both of spi bus and loads spi1 and then spi0 overlay to device tree, Beaglebone
            *  generates TTY file "spidev1.x" for spi1 and "spidev2.x" for spi0. But if users loads first spi0 and then spi1
            *  overlay to device tree, this time Beaglebone generates TTY file "spidev1.x" for spi0 and "spidev2.x" for spi1.
            *  For this reason which file associated with which spi, must find. This function does these operations exactly.
            *  @return True if successful, else false.
            */
            bool            findPortPath();


        public:
            /*!
            * This enum is used to define SPI debugging flags.
            */
            enum flags      {   dtErr       = 1,    /*!< enumeration for @a errorSPI::dtError status */
                                openErr     = 2,    /*!< enumeration for @a errorSPI::openError status */
                                closeErr    = 3,    /*!< enumeration for @a errorSPI::closeError status */
                                portPathErr = 4,    /*!< enumeration for @a errorSPI::portPathError status */
                                transferErr = 5,    /*!< enumeration for @a errorSPI::transferError status */
                                modeErr     = 6,    /*!< enumeration for @a errorSPI::modeError status */
                                speedErr    = 7,    /*!< enumeration for @a errorSPI::speedError status */
                                bitSizeErr  = 8     /*!< enumeration for @a errorSPI::bitSizeError status */
                            };

            /*! @brief Constructor of BlackSPI class.
            *
            * This function initializes errorSPI struct, sets local variables. Then calls device tree loading function
            * and port path finding function. Objects which are initialized from BlackSPI class with this constructor,
            * uses default line properties.
            *
            * @param [in] spi            name of spi (enum),(SPIx_y)
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0);
            *   BlackLib::BlackSPI  *mySpiPtr = new BlackLib::BlackSPI(BlackLib::SPI0_1);
            *
            *   mySpi.open( BlackLib::ReadWrite );
            *   mySpiPtr->open( BlackLib::ReadWrite );
            *
            * @endcode
            * @sa loadDeviceTree()
            * @sa findPortPath()
            * @sa spiName
            */
            BlackSPI(spiName spi);

            /*! @brief Constructor of BlackSPI class.
            *
            * This function initializes errorSPI struct, sets value of constructorProperties struct and local variables.
            * Then calls device tree loading function and port path finding function.
            *
            * @param [in] spi            name of spi (enum),(SPIx_y)
            * @param [in] spiProperties  import properties from outside
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSpiProperties mySpiProps(8, BlackLib::SpiDefault, 2400000);
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, mySpiProps);
            *   BlackLib::BlackSPI  *mySpiPtr = new BlackLib::BlackSPI(BlackLib::SPI0_1, mySpiProps);
            *
            *   mySpi.open( BlackLib::ReadWrite );
            *   mySpiPtr->open( BlackLib::ReadWrite );
            *
            * @endcode
            *
            * @sa loadDeviceTree()
            * @sa findPortPath()
            * @sa spiName
            * @sa BlackSpiProperties
            */
            BlackSPI(spiName spi, BlackSpiProperties spiProperties);

            /*! @brief Constructor of BlackSPI class.
            *
            * This function initializes errorSPI struct, sets value of constructorProperties struct and local variables.
            * Then calls device tree loading function and port path finding function.
            *
            * @param [in] spi               name of spi (enum),(SPIx_y)
            * @param [in] spiBitsPerWord    word size of spi
            * @param [in] spiMode           mode of spi
            * @param [in] spiSpeed          transfer speed of spi
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *   BlackLib::BlackSPI  *mySpiPtr = new BlackLib::BlackSPI(BlackLib::SPI0_1, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite );
            *   mySpiPtr->open( BlackLib::ReadWrite );
            *
            * @endcode
            *
            * @sa loadDeviceTree()
            * @sa findPortPath()
            * @sa spiName
            * @sa BlackSpiProperties::spiBitsPerWord
            * @sa BlackSpiProperties::spiMode
            * @sa BlackSpiProperties::spiSpeed
            */
            BlackSPI(spiName spi, uint8_t spiBitsPerWord, uint8_t spiMode, uint32_t spiSpeed);

            /*! @brief Destructor of BlackSPI class.
            *
            * This function closes TTY file and deletes errorSPI struct pointer.
            */
            virtual ~BlackSPI();

            /*! @brief Opens TTY file of spi.
            *
            * This function opens spi's TTY file with selected open mode, gets default properties of SPI
            * and saves this properties to BlackSPI::defaultProperties struct. Then sets properties
            * which are specified at class initialization stage. Users can send "or"ed BlackLib::openMode
            * enums as parameter to this function.
            * @warning After initialization of BlackSPI class, this function must call. Otherwise users
            * could not use any of data transfering functions.
            *
            * @param [in] openMode          file opening mode
            * @return True if tty file opening successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            * @endcode
            *
            * @sa openMode
            */
            bool            open(uint openMode);

            /*! @brief Closes TTY file of spi.
            *
            * This function closes spi's TTY file and changes isOpenFlag's value.
            * @return True if tty file closing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   mySpi.close();
            *
            * @endcode
            *
            * @sa BlackSPI::isOpenFlag
            */
            bool            close();

            /*! @brief Transfers byte to/from slave.
            *
            * This function creates temporary read variable and then generates <i><b> SPI IOCTL
            * TRANSFER PACKAGE </b></i> with write byte's address, temporary read variable's address,
            * delay time, spi word's size and spi speed parameters. After doing ioctl kernel request, if request is
            * finished successfully, data which is held in temporary read variable, is returned from this function.
            *
            * @param [in] writeByte            one byte data
            * @param [in] wait_us              delay time
            * @return If transfer operation is successful this function returns received byte data, else returns 0.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   uint8_t sendByte = 0x87;
            *   uint8_t recvByte = mySpi.transfer(sendByte, 100);
            *
            *   std::cout << "Loopback spi test result: 0x" << std::hex << (int)recvByte;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Loopback spi test result: 0x87
            * @endcode
            */
            uint8_t         transfer(uint8_t writeByte, uint16_t wait_us = 10);

            /*! @brief Transfers datas to/from slave.
            *
            * This function creates temporary read buffer with specified size and then generates <i><b> SPI IOCTL
            * TRANSFER PACKAGE </b></i> with write buffer pointer, temporary read buffer pointer, buffer size,
            * delay time, spi word's size and spi speed parameters. After doing ioctl kernel request if request is
            * finished successfully, datas which are held in temporary read buffer are copied to @a @b readBuffer
            * pointer.
            *
            * @param [in] writeBuffer          data buffer pointer
            * @param [out] readBuffer          read buffer pointer
            * @param [in] bufferSize           buffer size
            * @param [in] wait_us              delay time
            * @return true if transfer operation successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   uint8_t sendBytes[4] = { 0x87, 0x41, 0xF1, 0x5A };
            *   uint8_t recvBytes[4];
            *   mySpi.transfer(sendBytes, recvBytes, sizeof(sendBytes), 100);
            *
            *   std::cout << "Loopback spi test result 0: 0x" << std::hex << (int)recvBytes[0] << std::endl
            *             << "Loopback spi test result 1: 0x" << std::hex << (int)recvBytes[1] << std::endl
            *             << "Loopback spi test result 2: 0x" << std::hex << (int)recvBytes[2] << std::endl
            *             << "Loopback spi test result 3: 0x" << std::hex << (int)recvBytes[3] << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Loopback spi test result 0: 0x87
            *   // Loopback spi test result 1: 0x41
            *   // Loopback spi test result 2: 0xF1
            *   // Loopback spi test result 3: 0x5A
            * @endcode
            */
            bool            transfer(uint8_t *writeBuffer, uint8_t *readBuffer, size_t bufferSize, uint16_t wait_us = 10);


            /*! @brief Changes word size of spi.
            *
            * This function changes bits per word size of spi on fly.
            *
            * @param [in] newBitSize         new word size
            * @return true if changing operation is successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Current bits per word size: " << (int)mySpi.getBitsPerWord() << std::endl;
            *   mySpi.setBitsPerWord(10);
            *   std::cout << "Current bits per word size: " << (int)mySpi.getBitsPerWord();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current bits per word size: 8
            *   // Current bits per word size: 10
            * @endcode
            *
            * @sa BlackSpiProperties::spiBitsPerWord
            */
            bool            setBitsPerWord(uint8_t newBitSize);

            /*! @brief Changes maximum speed of spi.
            *
            * This function changes maximum speed of spi on fly.
            *
            * @param [in] newSpeed         new speed value
            * @return true if changing operation is successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Current speed: " << mySpi.getMaximumSpeed() << " Hz\n";
            *   mySpi.setMaximumSpeed(18000000);
            *   std::cout << "Current speed: " << mySpi.getMaximumSpeed() << " Hz";
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current speed: 2400000 Hz
            *   // Current speed: 18000000 Hz
            * @endcode
            *
            * @sa BlackSpiProperties::spiSpeed
            */
            bool            setMaximumSpeed(uint32_t newSpeed);

            /*! @brief Changes mode of spi.
            *
            * This function changes mode of spi on fly. Users can send "or"ed BlackLib::spiMode
            * enums as parameter to this function.
            *
            * @param [in] newMode         new mode value
            * @return true if changing operation is successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   // 0 means SpiDefault. See the BlackLib::spiMode enums.
            *   std::cout << "Current mode: " << (int)mySpi.getMode() << std::endl;
            *
            *   mySpi.setMode( BlackLib::SpiPolarity | BlackLib::SpiPhase );
            *
            *   // 3 means SpiPolarity and SpiPhase. See the BlackLib::spiMode enums.
            *   std::cout << "Current mode: " << (int)mySpi.getMode();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current mode: 0
            *   // Current mode: 3
            * @endcode
            *
            * @sa BlackSpiProperties::spiMode
            * @sa spiMode
            */
            bool            setMode(uint8_t newMode);

            /*! @brief Changes properties of spi.
            *
            * This function changes properties of spi. These properties are composed of word size,
            * speed and mode.
            *
            * @param [in] &newProperties        new properties of spi
            * @return true if changing operation is successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   BlackLib::BlackSpiProperties currentProps = mySpi.getProperties();
            *
            *   std::cout << "First bits per word size: " << (int)currentProps.spiBitsPerWord << std::endl
            *             << "First mode              : " << (int)currentProps.spiMode        << std::endl
            *             << "First speed             : " << currentProps.spiSpeed       << std::endl;
            *
            *   currentProps = BlackLib::BlackSpiProperties(10, BlackLib::SpiPolarity | BlackLib::SpiPhase, 18000000);
            *
            *   mySpi.setProperties(currentProps);
            *
            *   std::cout << "Second bits per word size: " << (int)currentProps.spiBitsPerWord << std::endl
            *             << "Second mode              : " << (int)currentProps.spiMode        << std::endl
            *             << "Second speed             : " << currentProps.spiSpeed       << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // First bits per word size: 8
            *   // First mode              : 0
            *   // First speed             : 2400000
            *   // Second bits per word size: 10
            *   // Second mode              : 3
            *   // Second speed             : 18000000
            * @endcode
            *
            * @sa BlackSpiProperties
            */
            bool            setProperties(BlackSpiProperties &newProperties);

            /*! @brief Exports spi's port path.
            *
            * @return spi's port path as string.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Port path: " << mySpi.getPortName();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Port path: /dev/spidev1.0
            * @endcode
            *
            * @sa spiPortPath
            */
            string          getPortName();

            /*! @brief Exports word size of spi.
            *
            * @return bits per word size of spi
            *
            * @par Example
            *   Example usage is shown in BlackSPI::setBitsPerWord() function's example.
            *
            * @sa BlackSpiProperties::spiBitsPerWord
            */
            uint8_t         getBitsPerWord();

            /*! @brief Exports maximum speed of spi.
            *
            * @return maximum speed of spi
            *
            * @par Example
            *   Example usage is shown in BlackSPI::setMaximumSpeed() function's example.
            *
            * @sa BlackSpiProperties::spiSpeed
            */
            uint32_t        getMaximumSpeed();

            /*! @brief Exports mode of spi.
            *
            * @return mode of spi
            *
            * @par Example
            *   Example usage is shown in BlackSPI::setMode() function's example.
            *
            * @sa BlackSpiProperties::spiMode
            * @sa BlackLib::spiMode
            */
            uint8_t         getMode();

            /*! @brief Exports properties of spi.
            *
            * This function gets properties of spi. These properties are composed of word size,
            * speed and mode.
            *
            * @return BlackSPI::currentProperties struct with updated values.
            *
            * @par Example
            *   Example usage is shown in BlackSPI::setProperties() function's example.
            *
            * @sa BlackSpiProperties
            */
            BlackSpiProperties getProperties();

            /*! @brief Checks spi's tty file's open state.
            *
            * @return true if tty file is open, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *
            *   std::cout << "Is open?: " << std::boolalpha << mySpi.isOpen() << std::endl;
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Is open?: " << std::boolalpha << mySpi.isOpen();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Is open?: false
            *   // Is open?: true
            * @endcode
            *
            * @sa BlackSPI::isOpenFlag
            */
            bool            isOpen();

            /*! @brief Checks spi's tty file's close state.
            *
            * @return true if tty file is close, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *
            *   std::cout << "Is close?: " << std::boolalpha << mySpi.isClose() << std::endl;
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Is close?: " << std::boolalpha << mySpi.isClose();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Is close?: true
            *   // Is close?: false
            * @endcode
            *
            * @sa BlackSPI::isOpenFlag
            */
            bool            isClose();

            /*! @brief Is used for general debugging.
            *
            * @return True if any error occured, else false.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   if( mySpi.fail() )
            *   {
            *       std::cout << "ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "EVERYTHING IS OK" << std::endl;
            *   }
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // EVERYTHING IS OK
            * @endcode
            *
            * @sa errorSPI
            */
            bool            fail();

            /*! @brief Is used for specific debugging.
            *
            * You can use this function, after call BlackSPI member functions in your code. The
            * input parameter is used for finding out status of selected error.
            * @param [in] f specific error type (enum)
            * @return Value of @a selected error.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackSPI  mySpi(BlackLib::SPI0_0, 8, BlackLib::SpiDefault, 2400000);
            *
            *
            *   if( mySpi.fail(BlackLib::BlackSPI::dtErr) or mySpi.fail(BlackLib::BlackSPI::portPathErr) )
            *   {
            *       std::cout << "BlackSPI INITIALIZATION FAILED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "BlackSPI INITIALIZATION IS OK" << std::endl;
            *   }
            *
            *
            *   mySpi.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   if( mySpi.fail(BlackLib::BlackSPI::openErr) )
            *   {
            *       std::cout << "OPENNING ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "OPENNING IS OK" << std::endl;
            *   }
            *
            *
            *   uint8_t sendBytes[4] = { 0x87, 0x41, 0xF1, 0x5A };
            *   uint8_t recvBytes[4];
            *   mySpi.transfer(sendBytes, recvBytes, sizeof(sendBytes), 100);
            *
            *   if( mySpi.fail(BlackLib::BlackSPI::transferErr) )
            *   {
            *       if( mySpi.fail(BlackLib::BlackSPI::openErr) )
            *       {
            *           std::cout << "TRANSFER ERROR OCCURED BECAUSE SPI TTY IS NOT OPEN" << std::endl;
            *       }
            *       else
            *       {
            *           std::cout << "TRANSFER ERROR OCCURED" << std::endl;
            *       }
            *   }
            *   else
            *   {
            *       std::cout << "TRANSFER IS OK" << std::endl;
            *   }
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // BlackSPI INITIALIZATION IS OK
            *   // OPENNING IS OK
            *   // TRANSFER IS OK
            * @endcode
            *
            * @sa errorSPI
            */
            bool            fail(BlackSPI::flags f);

    };
    // ########################################### BLACKSPI DECLARATION ENDS ############################################## //


} /* namespace BlackLib */

#endif /* BLACKSPI_H_ */
