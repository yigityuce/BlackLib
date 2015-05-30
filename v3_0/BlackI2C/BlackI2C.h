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





#ifndef BLACKI2C_H_
#define BLACKI2C_H_


#include "../BlackCore.h"
#include <iostream>

#include <cstring>
#include <string>
#include <fstream>
#include <cstdint>
#include <unistd.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


namespace BlackLib
{

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







    // ########################################### BLACKI2C DECLARATION STARTS ############################################ //

    /*! @brief Interacts with end user, to use I2C.
     *
     *    This class is end node to use i2c. End users interact with i2c from this class.
     *    It includes public functions to read and write byte, word or block datas.
     *
     *    @warning BlackI2C uses SMBUS. Device and register addresses vary by slave device.
     *
     *    @par Example
      @verbatim
      EXAMPLE PROJECT FILE TREE:

         myI2cProject
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
             |-> myI2cProject.cpp
      @endverbatim
     *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
     *  include BlackI2C.h or another source files with adding this line to your project file (myI2cProject.cpp at
     *  the example):
     *  @code{.cpp}
     *      #include "BlackLib/BlackI2C/BlackI2C.h"
     *  @endcode
     *  @n@n If BlackLib source files are located at same level with your project file (myI2cProject.cpp at the
     *  example), you have to include BlackI2C.h or another source files with adding this line to your project file:
     *  @code{.cpp}
     *      #include "BlackI2C/BlackI2C.h"
     *  @endcode
     *  @n @n
     *  @code{.cpp}
     *  // Filename: myI2cProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackI2C/BlackI2C.h"
     *
     *  int main()
     *  {
     *      BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
     *
     *      myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock);
     *
     *      uint8_t who_am_i = myI2c.readByte(0x28);
     *      std::cout << "0x28: " << std::hex << (int)who_am_i << std::endl;
     *
     *      return 0;
     *  }
     * @endcode
     * @n @n
     * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
     * @code{.cpp}
     *  // Filename: myI2cProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackI2C/BlackI2C.h"
     *  using namespace BlackLib;
     *
     *  int main()
     *  {
     *      BlackI2C  myI2c(I2C_1, 0x53);
     *
     *      myI2c.open( ReadWrite|NonBlock );
     *
     *      uint8_t who_am_i = myI2c.readByte(0x28);
     *      std::cout << "0x28: " << std::hex << (int)who_am_i << std::endl;
     *
     *      return 0;
     *  }
     * @endcode
     */
    class BlackI2C : virtual private BlackCore
    {
        private:
            errorI2C        *i2cErrors;                 /*!< @brief is used to hold the errors of BlackI2C class */

            unsigned int    i2cDevAddress;              /*!< @brief is used to hold the i2c's device address */
            int             i2cFD;                      /*!< @brief is used to hold the i2c's tty file's file descriptor */
            std::string     i2cPortPath;                /*!< @brief is used to hold the i2c's tty port path */
            bool            isOpenFlag;                 /*!< @brief is used to hold the i2c's tty file's state */



            /*! @brief Device tree loading is not necessary for using I2C feature.
            *
            *  But this function have to declare in this class again. Because it is a pure virtual
            *  function. It does nothing.
            *  @return false all time.
            */
            bool        loadDeviceTree();

            /*! @brief Does SMBUS kernel requests.
            *
            * This function generates <i><b>I2C SMBUS IOCTL DATA PACKAGE</b></i> with read/write mode selection, register
            * address, transaction type and <i><b>I2C SMBUS DATA</b></i>. Then this function does ioctl kernel request with
            * using this smbus package.
            *
            * @param [in] rwMode            write or read mode selection (enum)
            * @param [in] registerAddr      register address which will access
            * @param [in] smbusTransaction  transaction type (enum)
            * @param [in] data              data
            * @return If kernel request is finished successfully, this function returns true, else false.
            *
            */
            inline bool useSmbusIOCTL(direction rwMode, uint8_t registerAddr, transactionType smbusTransaction, i2c_smbus_data &data);

            /*! @brief Sets slave to device.
            *
            * This function does ioctl kernel request with "I2C_SLAVE" command.
            *
            * @return If kernel request is finished successfully, this function returns true, else false.
            */
            inline bool setSlave();



        public:
            /*!
            * This enum is used to define I2C debugging flags.
            */
            enum flags      {   openErr     = 0,    /*!< enumeration for @a errorI2C::openError status */
                                closeErr    = 1,    /*!< enumeration for @a errorI2C::closeError status */
                                setSlaveErr = 2,    /*!< enumeration for @a errorI2C::setSlaveError status */
                                readErr     = 3,    /*!< enumeration for @a errorI2C::readError status */
                                writeErr    = 4     /*!< enumeration for @a errorI2C::writeError status */
                            };

            /*! @brief Constructor of BlackI2C class.
            *
            * This function initializes errorI2C struct and sets local variables.
            *
            * @param [in] i2c               name of i2c (enum),(I2C_x)
            * @param [in] i2cDeviceAddress  address of device
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *   BlackLib::BlackI2C  *myI2cPtr(BlackLib::I2C_1, 0x69);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock);
            *   myI2cPtr->open( BlackLib::ReadWrite | BlackLib::NonBlock);
            *
            * @endcode
            *
            * @sa i2cName
            */
            BlackI2C(i2cName i2c, unsigned int i2cDeviceAddress);

            /*! @brief Destructor of BlackI2C class.
            *
            * This function closes TTY file and deletes errorI2C struct pointer.
            */
            virtual ~BlackI2C();


            /*! @brief Opens TTY file of i2c.
            *
            * This function opens i2c's TTY file with selected open mode. Users can send "or"ed
            * BlackLib::openMode enums as parameter to this function.
            * @warning After initialization of BlackI2C class, this function must call. Otherwise users
            * could not use any of data transfering functions.
            *
            * @param [in] openMode          file opening mode
            * @return True if tty file opening successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            * @endcode
            *
            * @sa openMode
            */
            bool        open(uint openMode);

            /*! @brief Closes TTY file of i2c.
            *
            * This function closes i2c's TTY file and changes isOpenFlag's value.
            * @return True if tty file closing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myI2c.close();
            *
            * @endcode
            *
            * @sa BlackSPI::isOpenFlag
            */
            bool        close();

            /*! @brief Writes byte value to i2c smbus.
            *
            * This function writes byte value to i2c smbus. Register address of device and values sent
            * to this function as uint8_t type.
            *
            * @param [in] registerAddr      register address
            * @param [in] value             byte data
            * @return true if writing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *                                       //  ___ ___ ___ ___|___ ___ ___ ___
            *   uint8_t powerCtl_Addr       = 0x2D; // |_0_|_0_|_1_|_0_|_1_|_1_|_0_|_1_|
            *   uint8_t measureMode         = 0x08; // |_0_|_0_|_0_|_0_|_1_|_0_|_0_|_0_|
            *
            *   uint8_t powerCtlReg         = myI2c.readByte(powerCtl_Addr);
            *   std::cout << "Power Ctrl's current value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;
            *
            *   powerCtlReg |= (measureMode);       //                      ___ ___ ___ ___|___ ___ ___ ___
            *                                       // powerCtlReg:        |_x_|_x_|_x_|_x_|_x_|_x_|_x_|_x_|
            *                                       // measureMode:        |_0_|_0_|_0_|_0_|_1_|_0_|_0_|_0_|
            *                                       //                      ___ ___ ___ ___|___ ___ ___ ___ or these
            *                                       // result:             |_x_|_x_|_x_|_x_|_1_|_x_|_x_|_x_|
            *
            *   bool resultOfWrite          = myI2c.writeByte(powerCtl_Addr, powerCtlReg);
            *   std::cout << "Power Ctrl's new value is wrote?: " << std::boolalpha << resultOfWrite << std::dec << std::endl;
            *
            *   powerCtlReg                 = myI2c.readByte(powerCtl_Addr);
            *   std::cout << "Power Ctrl's new value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;
            *
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Power Ctrl's current value: 00
            *   // Power Ctrl's new value is wrote?: true
            *   // Power Ctrl's new value: 08
            * @endcode
            */
            bool        writeByte(uint8_t registerAddr, uint8_t value);

            /*! @brief Writes word value to i2c smbus.
            *
            * This function writes word value to i2c smbus. Values sent to this function as uint16_t type.
            *
            * @param [in] registerAddr      register address
            * @param [in] value             word data
            *
            * @warning Word data operations use little-endian system. This means, it stores the most significant byte
            * of a word in the largest address and the least significant byte is stored in the smallest address.
            *
            * @return true if writing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *                                       //  ___ ___ ___ ___|___ ___ ___ ___
            *   uint8_t offsetX_Addr        = 0x1E; // |_0_|_0_|_0_|_1_|_1_|_1_|_1_|_0_|
            *   uint8_t offsetY_Addr        = 0x1F; // |_0_|_0_|_0_|_1_|_1_|_1_|_1_|_1_|
            *
            *   // Example: Register Map of slave device(0x53), Little-Endian System
            *   // ----------------------------------
            *   // |   | 0 | 1 | .......... | e | f |
            *   // ----------------------------------
            *   // |00 |...|...| .......... |...|...|
            *   // ----------------------------------
            *   // |10 |...|...| .......... | 1 | 4 |   ==> 0x1E = 0x01 , 0x1F = 0x04
            *   // ----------------------------------
            *   // | : | : | : | .......... | : | : |
            *   // | : | : | : | .......... | : | : |
            *   // | : | : | : | .......... | : | : |
            *   // ----------------------------------
            *   // |f0 |...|...| .......... |...|...|
            *   // ----------------------------------
            *   //
            *   // When users read word data from 0x1E address, word value is 0x0401.
            *   // This means smallest address(0x1E) will be least significant byte(LSB, 0x01)
            *   // and largest address(0x1F) will be most significant byte(MSB, 0x04)
            *
            *
            *   uint16_t tempRead           = myI2c.readWord(offsetX_Addr);
            *   uint8_t offsetX             = static_cast<uint8_t>(tempRead & 0xFF);
            *   uint8_t offsetY             = static_cast<uint8_t>(tempRead >> 8);
            *   std::cout << "Offset X's current value: " << std::hex << (int)offsetX << std::dec << std::endl;
            *   std::cout << "Offset Y's current value: " << std::hex << (int)offsetY << std::dec << std::endl;
            *
            *   offsetX                     = 0xA0;
            *   offsetY                     = 0x0B;
            *   uint16_t tempWrite          = ((static_cast<uint16_t>(offsetY) << 8) | static_cast<uint16_t>(offsetX));
            *
            *   bool resultOfWrite          = myI2c.writeWord(offsetX_Addr, tempWrite);
            *   std::cout << "Offset X&Y's new value is wrote?: " << std::boolalpha << resultOfWrite << std::dec << std::endl;
            *
            *   tempRead                    = myI2c.readWord(offsetX_Addr);
            *   offsetX                     = static_cast<uint8_t>(tempRead & 0xFF);
            *   offsetY                     = static_cast<uint8_t>(tempRead >> 8);
            *   std::cout << "Offset X's new value: " << std::hex << (int)offsetX << std::dec << std::endl;
            *   std::cout << "Offset Y's new value: " << std::hex << (int)offsetY << std::dec << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Offset X's current value: 00
            *   // Offset Y's current value: 00
            *   // Offset X&Y's new value is wrote?: true
            *   // Offset X's new value: A0
            *   // Offset Y's new value: 0B
            * @endcode
            */
            bool        writeWord(uint8_t registerAddr, uint16_t value);

            /*! @brief Writes block of data to i2c smbus.
            *
            * This function writes block of data to i2c smbus. Data block sent to this function as pointer
            * of uint8_t type.
            *
            * @param [in] registerAddr      register address
            * @param [in] writeBuffer       buffer pointer
            * @param [in] bufferSize        buffer size
            *
            * @warning Maximum block size is 32.
            *
            * @return true if writing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *                                       //  ___ ___ ___ ___|___ ___ ___ ___
            *   uint8_t offsetX_Addr        = 0x1E; // |_0_|_0_|_0_|_1_|_1_|_1_|_1_|_0_|
            *   uint8_t offsetY_Addr        = 0x1F; // |_0_|_0_|_0_|_1_|_1_|_1_|_1_|_1_|
            *   uint8_t offsetZ_Addr        = 0x20; // |_0_|_0_|_1_|_0_|_0_|_0_|_0_|_0_|
            *
            *   uint8_t offsetValues[3]     = { 0x00, 0x00, 0x00 };
            *   uint8_t readBlockSize       = myI2c.readBlock(offsetX_Addr, offsetValues, sizeof(offsetValues) );
            *
            *   std::cout << "Total read block size: " << (int)readBlockSize << std::endl;
            *   std::cout << "Offset X's current value: " << std::hex << (int)offsetValues[0] << std::dec << std::endl;
            *   std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues[1] << std::dec << std::endl;
            *   std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues[2] << std::dec << std::endl;
            *
            *
            *   offsetValues[0]             = 0x1A;
            *   offsetValues[1]             = 0x2B;
            *   offsetValues[2]             = 0x3C;
            *
            *   bool resultOfWrite          = myI2c.writeBlock(offsetX_Addr, offsetValues, sizeof(offsetValues) );
            *   std::cout << "Offsets' new values are wrote?: " << std::boolalpha << resultOfWrite << std::dec << std::endl;
            *
            *   memset(offsetValues, 0, sizeof(offsetValues));      // clear buffer
            *
            *   readBlockSize               = myI2c.readBlock(offsetX_Addr, offsetValues, sizeof(offsetValues) );
            *
            *   std::cout << "Total read block size: " << (int)readBlockSize << std::endl;
            *   std::cout << "Offset X's current value: " << std::hex << (int)offsetValues[0] << std::dec << std::endl;
            *   std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues[1] << std::dec << std::endl;
            *   std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues[2] << std::dec << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Total read block size: 3
            *   // Offset X's current value: 00
            *   // Offset Y's current value: 00
            *   // Offset Z's current value: 00
            *   // Offsets' new values are wrote?: true
            *   // Total read block size: 3
            *   // Offset X's current value: 1A
            *   // Offset Y's current value: 2B
            *   // Offset Z's current value: 3C
            * @endcode
            */
            bool        writeBlock(uint8_t registerAddr, uint8_t *writeBuffer, size_t bufferSize);

            /*! @brief Writes data block to i2c line.
            *
            * This function writes data block to i2c line directly. Data block sent to this function as pointer
            * of uint8_t type.
            *
            * @param [in] writeBuffer       buffer pointer
            * @param [in] bufferSize        buffer size
            *
            * @warning Data block's first element must be the address of register which will write datas.
            *
            * @return true if writing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *                                       //  ___ ___ ___ ___|___ ___ ___ ___
            *   uint8_t offsetX_Addr        = 0x1E; // |_0_|_0_|_0_|_1_|_1_|_1_|_1_|_0_|
            *   uint8_t offsetY_Addr        = 0x1F; // |_0_|_0_|_0_|_1_|_1_|_1_|_1_|_1_|
            *   uint8_t offsetZ_Addr        = 0x20; // |_0_|_0_|_1_|_0_|_0_|_0_|_0_|_0_|
            *
            *   uint8_t offsetValues[3]     = { 0x00, 0x00, 0x00 };
            *   myI2c.writeLine(&offsetX_Addr, 1);                      // address of register which will read datas
            *   myI2c.readLine( offsetValues, sizeof(offsetValues) );   // read three data from "offsetX_Addr"
            *
            *   std::cout << "Offset X's current value: " << std::hex << (int)offsetValues[0] << std::dec << std::endl;
            *   std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues[1] << std::dec << std::endl;
            *   std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues[2] << std::dec << std::endl;
            *
            *
            *   offsetValues[0]             = 0xD4;
            *   offsetValues[1]             = 0xE5;
            *   offsetValues[2]             = 0xF6;
            *   uint8_t tempBufWithAddr[4]  = { offsetX_Addr, offsetValues[0], offsetValues[1], offsetValues[2] };
            *
            *   bool resultOfWrite          = myI2c.writeLine(tempBufWithAddr, sizeof(tempBufWithAddr) );
            *   std::cout << "Offsets' new values are wrote?: " << std::boolalpha << resultOfWrite << std::dec << std::endl;
            *
            *   memset(offsetValues, 0, sizeof(offsetValues));          // clear buffer
            *   myI2c.writeLine(&offsetX_Addr, 1);                      // address of register which will read datas
            *   myI2c.readLine( offsetValues, sizeof(offsetValues) );   // read three data from "offsetX_Addr"
            *
            *   std::cout << "Offset X's current value: " << std::hex << (int)offsetValues[0] << std::dec << std::endl;
            *   std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues[1] << std::dec << std::endl;
            *   std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues[2] << std::dec << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Offset X's current value: 00
            *   // Offset Y's current value: 00
            *   // Offset Z's current value: 00
            *   // Offsets' new values are wrote?: true
            *   // Offset X's current value: D4
            *   // Offset Y's current value: E5
            *   // Offset Z's current value: F6
            * @endcode
            */
            bool        writeLine(uint8_t *writeBuffer, size_t bufferSize);

            /*! @brief Read byte value from i2c smbus.
            *
            * This function reads byte value from i2c smbus. Register address of device sent
            * to this function as uint8_t type.
            *
            * @param [in] registerAddr      register address
            * @return read value if reading successfull, else 0x00.
            *
            * @par Example
            *   Example usage is shown in BlackI2C::writeByte() function's example.
            */
            uint8_t     readByte(uint8_t registerAddr);

            /*! @brief Read word value from i2c smbus.
            *
            * This function reads word value from i2c smbus. Register address of device sent
            * to this function as uint8_t type.
            *
            * @param [in] registerAddr      register address
            * @return read value if reading successfull, else 0x0000.
            *
            * @par Example
            *   Example usage is shown in BlackI2C::writeWord() function's example.
            */
            uint16_t    readWord(uint8_t registerAddr);

            /*! @brief Read data block from i2c smbus.
            *
            * This function reads data block from i2c smbus. Register address of device sent
            * to this function as uint8_t type.
            *
            * @param [in] registerAddr      register address
            * @param [out] readBuffer       buffer pointer
            * @param [in] bufferSize        buffer size
            * @return size of read data block if reading successfull, else 0x00.
            *
            * @par Example
            *   Example usage is shown in BlackI2C::writeBlock() function's example.
            */
            uint8_t     readBlock(uint8_t registerAddr, uint8_t *readBuffer, size_t bufferSize);

            /*! @brief Read data block from i2c line.
            *
            * This function reads data block from i2c line directly.
            *
            * @param [out] readBuffer       buffer pointer
            * @param [in] bufferSize        buffer size
            *
            * @warning For reading something from i2c line, firstly users must write register address
            * data to line.
            * @return true reading successfull, else false.
            *
            * @par Example
            *   Example usage is shown in BlackI2C::writeLine() function's example.
            */
            bool        readLine(uint8_t *readBuffer, size_t bufferSize);

            /*! @brief Changes device address of slave device.
            *
            * This function changes device address of slave device and sets this device to slave.
            *
            * @param [in] newDeviceAddr  new slave device address
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Current slave address: " << std::hex << myI2c.getDeviceAddress() << std::endl;
            *
            *   myI2c.setDeviceAddress(0x69);
            *   std::cout << "Current slave address: " << std::hex << myI2c.getDeviceAddress() << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current slave address: 53
            *   // Current slave address: 69
            * @endcode
            *
            */
            void        setDeviceAddress(unsigned int newDeviceAddr);

            /*! @brief Exports device address of slave device.
            *
            * @return address of current slave device.
            *
            * @par Example
            *   Example usage is shown in BlackI2C::setDeviceAddress() function's example.
            *
            */
            int         getDeviceAddress();

            /*! @brief Exports i2c's port path.
            *
            * @return i2c's port path as string.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Port path: " << myI2c.getPortName();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Port path: /dev/i2c-1
            * @endcode
            *
            * @sa i2cPortPath
            */
            std::string getPortName();

            /*! @brief Checks i2c's tty file's open state.
            *
            * @return true if tty file is open, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   std::cout << "Is open?: " << std::boolalpha << myI2c.isOpen() << std::endl;
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Is open?: " << std::boolalpha << myI2c.isOpen();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Is open?: false
            *   // Is open?: true
            * @endcode
            *
            * @sa BlackI2C::isOpenFlag
            */
            bool        isOpen();

            /*! @brief Checks i2c's tty file's close state.
            *
            * @return true if tty file is close, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   std::cout << "Is close?: " << std::boolalpha << myI2c.isClose() << std::endl;
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Is close?: " << std::boolalpha << myI2c.isClose();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Is close?: true
            *   // Is close?: false
            * @endcode
            *
            * @sa BlackI2C::isOpenFlag
            */
            bool        isClose();

            /*! @brief Is used for general debugging.
            *
            * @return True if any error occured, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   if( myI2c.fail() )
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
            * @sa errorUART
            */
            bool        fail();

            /*! @brief Is used for specific debugging.
            *
            * You can use this function, after call BlackI2C member functions in your code. The
            * input parameter is used for finding out status of selected error.
            * @param [in] f specific error type (enum)
            * @return Value of @a selected error.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);
            *
            *   myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   if( myI2c.fail(BlackLib::BlackI2C::openErr) )
            *   {
            *       std::cout << "OPENNING ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "OPENNING IS OK" << std::endl;
            *
            *       if( myI2c.fail(BlackLib::BlackI2C::setSlaveErr) )
            *       {
            *           std::cout << "SETTING SLAVE ERROR OCCURED" << std::endl;
            *       }
            *       else
            *       {
            *           std::cout << "SETTING SLAVE IS OK" << std::endl;
            *       }
            *   }
            *
            *
            *   uint8_t powerCtl_Addr       = 0x2D;
            *   uint8_t measureMode         = 0x08;
            *   uint8_t powerCtlReg         = myI2c.readByte(powerCtl_Addr);
            *
            *   if( myI2c.fail(BlackLib::BlackI2C::readErr) )
            *   {
            *       std::cout << "READ DATA ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "READ DATA IS OK" << std::endl;
            *   }
            *
            *
            *   powerCtlReg |= (measureMode);
            *   bool resultOfWrite          = myI2c.writeByte(powerCtl_Addr, powerCtlReg);
            *
            *   if( myI2c.fail(BlackLib::BlackI2C::writeErr) )
            *   {
            *       std::cout << "WRITE DATA ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "WRITE DATA IS OK" << std::endl;
            *   }
            *
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // OPENNING IS OK
            *   // SETTING SLAVE IS OK
            *   // READ DATA IS OK
            *   // WRITE DATA IS OK
            * @endcode
            *
            * @sa errorI2C
            */
            bool        fail(BlackI2C::flags f);
    };

    // ########################################### BLACKI2C DECLARATION ENDS ############################################## //


} /* namespace BlackLib */

#endif /* BLACKI2C_H_ */
