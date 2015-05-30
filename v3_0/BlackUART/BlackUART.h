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



#ifndef BLACKUART_H_
#define BLACKUART_H_

#include "../BlackCore.h"

#include <string>
#include <fstream>
#include <cstdint>
#include <unistd.h>

#include <fcntl.h>
#include <termios.h>




namespace BlackLib
{

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
     * This enum is used for selecting apply mode of uart property's changes.
     */
    enum uartApplyMode      {   ApplyNow                = 0,
                                ApplyDrain              = 1,
                                ApplyFlush              = 2
                            };




    // ######################################### BLACKUARTPROPERTIES DECLARATION STARTS ######################################### //

    /*! @brief Holds properties of UART.
     *
     *    This struct holds input and output baud rate, parity, stop bits size and character size
     *    properties of UART. Also it has overloaded constructors and overloaded assign operator.
     *    @sa BlackLib::baudRate
     *    @sa BlackLib::parity
     *    @sa BlackLib::stopBits
     *    @sa BlackLib::characterSize
     */
    struct BlackUartProperties
    {
        baudRate        uartBaudIn;     /*!< @brief is used to hold the baud rate of UART RX */
        baudRate        uartBaudOut;    /*!< @brief is used to hold the baud rate of UART TX */
        parity          uartParity;     /*!< @brief is used to hold the parity type of UART */
        stopBits        uartStopBits;   /*!< @brief is used to hold the stop bits size of UART */
        characterSize   uartCharSize;   /*!< @brief is used to hold the character size of UART */

        /*! @brief Default constructor of BlackUartProperties struct.
         *
         *  This function sets default value to variables.
         */
        BlackUartProperties()
        {
            uartBaudIn      = Baud9600;
            uartBaudOut     = Baud9600;
            uartParity      = ParityDefault;
            uartStopBits    = StopDefault;
            uartCharSize    = CharDefault;
        }

        /*! @brief Overloaded constructor of BlackUartProperties struct.
         *
         *  This function sets input arguments to variables.
         * @sa BlackLib::baudRate
         * @sa BlackLib::parity
         * @sa BlackLib::stopBits
         * @sa BlackLib::characterSize
         */
        BlackUartProperties(baudRate S_baudIn, baudRate S_baudOut, parity S_parity, stopBits S_stopBits, characterSize S_charSize)
        {
            uartBaudIn      = S_baudIn;
            uartBaudOut     = S_baudOut;
            uartParity      = S_parity;
            uartStopBits    = S_stopBits;
            uartCharSize    = S_charSize;
        }

        /*! @brief Overloaded constructor of BlackUartProperties struct.
         *
         *  This function gets pointer of BlackUartProperties struct and sets input
         *  struct's variables to own variables.
         */
        BlackUartProperties( BlackUartProperties *S_properties )
        {
            uartBaudIn      = S_properties->uartBaudIn;
            uartBaudOut     = S_properties->uartBaudOut;
            uartParity      = S_properties->uartParity;
            uartStopBits    = S_properties->uartStopBits;
            uartCharSize    = S_properties->uartCharSize;
        }


        /*! @brief Overloaded assign operator of BlackUartProperties struct.
         *
         *  This function assigns input struct's variables to own variables.
         */
        BlackUartProperties& operator=(BlackUartProperties equal)
        {
            uartBaudIn      = equal.uartBaudIn;
            uartBaudOut     = equal.uartBaudOut;
            uartCharSize    = equal.uartCharSize;
            uartParity      = equal.uartParity;
            uartStopBits    = equal.uartStopBits;

            return *this;
        }
    };
    // ########################################## BLACKUARTPROPERTIES DECLARATION ENDS ########################################### //







    // ########################################### BLACKUART DECLARATION STARTS ############################################ //

    /*! @brief Interacts with end user, to use UART.
     *
     *    This class is end node to use uart. End users interact with uart from this class.
     *    It includes public functions to set and get properties of uart's and to read,
     *    write and transfer datas.
     *
     *    @par Example
      @verbatim
      EXAMPLE PROJECT FILE TREE:

         myUartProject
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
             |-> myUartProject.cpp
      @endverbatim
     *  @n@n If BlackLib source files are located in your project like above example project file tree, you have to
     *  include BlackUART.h or another source files with adding this line to your project file (myUartProject.cpp at
     *  the example):
     *  @code{.cpp}
     *      #include "BlackLib/BlackUART/BlackUART.h"
     *  @endcode
     *  @n@n If BlackLib source files are located at same level with your project file (myUartProject.cpp at the
     *  example), you have to include BlackUART.h or another source files with adding this line to your project file:
     *  @code{.cpp}
     *      #include "BlackUART/BlackUART.h"
     *  @endcode
     *  @n @n
     *  @code{.cpp}
     *  // Filename: myUartProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackUART/BlackUART.h"
     *
     *  int main()
     *  {
     *      BlackLib::BlackUART  myUart(BlackLib::UART1,
     *                                  BlackLib::Baud9600,
     *                                  BlackLib::ParityEven,
     *                                  BlackLib::StopOne,
     *                                  BlackLib::Char8 );
     *
     *      myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock);
     *
     *      std::string testMessage = "This is uart test message.";
     *      std::cout << myUart.transfer(testMessage, 40000);
     *
     *      return 0;
     *  }
     * @endcode
     * @n @n
     * You can use "using namespace BlackLib" also. You can get rid of writing "BlackLib::", with using this method.
     * @code{.cpp}
     *  // Filename: myUartProject.cpp
     *  // Author:   Yiğit Yüce - ygtyce@gmail.com
     *
     *  #include <iostream>
     *  #include "BlackLib/BlackUART/BlackUART.h"
     *  using namespace BlackLib;
     *
     *  int main()
     *  {
     *      BlackUART  myUart(UART1,
     *                        Baud9600,
     *                        ParityEven,
     *                        StopOne,
     *                        Char8 );
     *
     *      myUart.open( ReadWrite | NonBlock);
     *
     *      std::string testMessage = "This is uart test message.";
     *      std::cout << myUart.transfer(testMessage, 40000);
     *
     *      return 0;
     *  }
     * @endcode
     *
     */
    class BlackUART : virtual private BlackCore
    {

        private:
            BlackUartProperties defaultUartProperties;      /*!< @brief is used to hold the default properties of uart */
            BlackUartProperties currentUartProperties;      /*!< @brief is used to hold the current properties of uart */
            BlackUartProperties constructorProperties;      /*!< @brief is used to hold the user specified properties of uart */

            errorUART       *uartErrors;                    /*!< @brief is used to hold the errors of BlackUART class */

            std::string     dtUartFilename;                 /*!< @brief is used to hold the uart's device tree overlay name */
            std::string     uartPortPath;                   /*!< @brief is used to hold the uart's tty port path */

            uint32_t        readBufferSize;                 /*!< @brief is used to hold the size of temporary buffer */
            int             uartFD;                         /*!< @brief is used to hold the uart's tty file's file descriptor */
            bool            isOpenFlag;                     /*!< @brief is used to hold the uart's tty file's state */
            bool            isCurrentEqDefault;             /*!< @brief is used to hold the properties of uart is equal to default properties */

            /*! @brief Loads UART overlay to device tree.
            *
            *  This function loads @b BlackUART::dtUartFilename named overlay to device tree.
            *  This file name changes with uartName constructor parameter.
            *  This overlay performs pinmuxing and generates device driver.
            *  @return True if successful, else false.
            */
            bool            loadDeviceTree();


        public:
            /*!
            * This enum is used to define UART debugging flags.
            */
            enum flags      {   dtErr       = 1,    /*!< enumeration for @a errorUART::dtError status */
                                openErr     = 2,    /*!< enumeration for @a errorUART::openError status */
                                closeErr    = 3,    /*!< enumeration for @a errorUART::closeError status */
                                directionErr= 4,    /*!< enumeration for @a errorUART::directionError status */
                                flushErr    = 5,    /*!< enumeration for @a errorUART::flushError status */
                                readErr     = 6,    /*!< enumeration for @a errorUART::readError status */
                                writeErr    = 7,    /*!< enumeration for @a errorUART::writeError status */
                                baudRateErr = 8,    /*!< enumeration for @a errorUART::baudRateError status */
                                parityErr   = 9,    /*!< enumeration for @a errorUART::parityError status */
                                stopBitsErr = 10,   /*!< enumeration for @a errorUART::stopBitsError status */
                                charSizeErr = 11    /*!< enumeration for @a errorUART::charSizeError status */
                            };

            /*! @brief Constructor of BlackUART class.
            *
            * This function initializes errorUART struct, sets value of constructorProperties struct and local variables.
            * Then calls device tree loading function.
            *
            * @param [in] uart          name of uart (enum),(UARTx)
            * @param [in] uartBaud      baud rate of uart (enum)
            * @param [in] uartParity    parity of uart (enum)
            * @param [in] uartStopBits  stop bits of uart (enum)
            * @param [in] uartCharSize  character size of uart (enum)
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   BlackLib::BlackUART  *myUartPtr = new BlackLib::BlackUART(BlackLib::UART4,
            *                                                             BlackLib::Baud9600,
            *                                                             BlackLib::ParityEven,
            *                                                             BlackLib::StopOne,
            *                                                             BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite );
            *   myUartPtr->open( BlackLib::ReadWrite );
            *
            * @endcode
            *
            * @sa loadDeviceTree()
            * @sa uartName
            * @sa baudRate
            * @sa parity
            * @sa stopBits
            * @sa characterSize
            */
            BlackUART(uartName uart, baudRate uartBaud, parity uartParity, stopBits uartStopBits, characterSize uartCharSize);

            /*! @brief Constructor of BlackUART class.
            *
            * This function initializes errorUART struct, sets value of constructorProperties struct and local variables.
            * Then calls device tree loading function.
            *
            * @param [in] uart            name of uart (enum),(UARTx)
            * @param [in] uartProperties  import properties from outside
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUartProperties myUartProps(BlackLib::Baud9600,
            *                                             BlackLib::Baud9600,
            *                                             BlackLib::ParityEven,
            *                                             BlackLib::StopOne,
            *                                             BlackLib::Char8);
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1, myUartProps);
            *   BlackLib::BlackUART  *myUartPtr = new BlackLib::BlackUART(BlackLib::UART4, myUartProps);
            *
            *   myUart.open( BlackLib::ReadWrite );
            *   myUartPtr->open( BlackLib::ReadWrite );
            *
            * @endcode
            *
            * @sa loadDeviceTree()
            * @sa uartName
            * @sa BlackUartProperties
            */
            BlackUART(uartName uart, BlackUartProperties uartProperties);

            /*! @brief Constructor of BlackUART class.
            *
            * This function initializes errorUART struct, sets local variables. Then calls device tree loading function.
            * Objects which are initialized from BlackUART class with this constructor, uses default uart properties.
            *
            * @param [in] uart            name of uart (enum),(UARTx)
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1);
            *   BlackLib::BlackUART  *myUartPtr = new BlackLib::BlackUART(BlackLib::UART4);
            *
            *   myUart.open( BlackLib::ReadWrite );
            *   myUartPtr->open( BlackLib::ReadWrite );
            *
            * @endcode
            * @sa loadDeviceTree()
            * @sa uartName
            */
            BlackUART(uartName uart);

            /*! @brief Destructor of BlackUART class.
            *
            * This function closes TTY file and deletes errorUART struct pointer.
            */
            virtual ~BlackUART();

            /*! @brief Opens TTY file of uart.
            *
            * This function opens uart's TTY file with selected open mode, gets default properties of UART
            * and saves this properties to BlackUART::defaultUartProperties struct. Then sets properties
            * which are specified at class initialization stage. Users can send "or"ed BlackLib::openMode
            * enums as parameter to this function.
            * @warning After initialization of BlackUART class, this function must call. Otherwise users
            * could not use any of data sending or receiving functions.
            *
            * @param [in] openMode          file opening mode
            * @return True if tty file opening successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            * @endcode
            * @sa openMode
            */
            bool            open(uint openMode);

            /*! @brief Closes TTY file of uart.
            *
            * This function closes uart's TTY file and changes BlackUART::isOpenFlag's value.
            * @return True if tty file closing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.close();
            *
            * @endcode
            * @sa BlackUART::isOpenFlag
            */
            bool            close();

            /*! @brief Flushes uart line.
            *
            * This function flushes uart line at specified direction.
            * @param [in] whichDirection flushing direction
            * @return True if flushing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            * @endcode
            * @sa direction
            */
            bool            flush(direction whichDirection);

            /*! @brief Reads values from uart line.
            *
            * This function reads values from uart line and returns read value as string.
            * It creates temporary read buffer with specified size and reads values to this
            * buffer. Then resize buffer to read value size. BlackUART::readBufferSize variable
            * is used to specify temporary buffer size.
            *
            * @return read value if reading successful, else returns BlackLib::UART_READ_FAILED string.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   std::string writeToUart  = "this is test.\n";
            *   myUart.write(writeToUart);
            *
            *   sleep(1);
            *
            *   std::string readFromUart = myUart.read();
            *
            *   std::cout << "Test output on loopback: " << readFromUart;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            * @sa BlackUART::readBufferSize
            */
            std::string     read();

            /*! @brief Reads values from uart line.
            *
            * This function reads values from uart line and saves read value to @a @b readBuffer pointer.
            * It creates temporary read buffer with specified size and reads values to this
            * buffer. Then copies buffer to  @a @b readBuffer pointer.
            *
            * @param [out] readBuffer          buffer pointer
            * @param [in] size                 buffer size
            * @return true if reading successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   std::string writeToUart  = "this is test.\n";
            *   myUart.write(writeToUart);
            *
            *   sleep(1);
            *
            *   char readBuffer[14];
            *   myUart.read(readBuffer, sizeof(readBuffer));
            *
            *   std::cout << "Test output on loopback: " << readBuffer;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            */
            bool            read(char *readBuffer, size_t size);

            /*! @brief Writes values to uart line.
            *
            * This function writes values to uart line. Values sent to this function as string type.
            *
            * @param [in] writeBuffer          values buffer
            * @return true if writing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   std::string writeToUart  = "this is test.\n";
            *   myUart.write(writeToUart);
            *
            *   sleep(1);
            *
            *   std::string readFromUart = myUart.read();
            *
            *   std::cout << "Test output on loopback: " << readFromUart;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            */
            bool            write(std::string writeBuffer);

            /*! @brief Writes values to uart line.
            *
            * This function writes values to uart line. Values sent to this function as c-style string(char array).
            *
            * @param [in] writeBuffer          values buffer
            * @param [in] size                 buffer size
            * @return true if writing successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   char writeBuffer[]  = "this is test.\n";
            *   myUart.write(writeBuffer, sizeof(writeBuffer));
            *
            *   sleep(1);
            *
            *   std::string readFromUart = myUart.read();
            *
            *   std::cout << "Test output on loopback: " << readFromUart;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            */
            bool            write(char *writeBuffer, size_t size);

            /*! @brief Writes and reads values sequentially to/from uart line.
            *
            * This function writes values to uart line firstly and then reads values from uart line and saves read
            * value to @a @b readBuffer pointer. It creates temporary read buffer with specified size and reads
            * values to this buffer. Then it copies buffer to  @a @b readBuffer pointer. This function waits between
            * writing and reading operations.
            *
            * @param [in] writeBuffer          values buffer
            * @param [out] readBuffer          read buffer pointer
            * @param [in] size                 buffer size
            * @param [in] wait_us              sleep time between writing and reading
            * @return true if transfering successful, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   char writeBuffer[]  = "this is test.\n";
            *   char readBuffer[ myUart.getReadBufferSize() ];
            *
            *   myUart.transfer(writeBuffer, readBuffer, sizeof(writeBuffer), 40000);
            *
            *   std::cout << "Test output on loopback: " << readBuffer;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            * @sa BlackUART::readBufferSize
            */
            bool            transfer(char *writeBuffer, char *readBuffer, size_t size, uint32_t wait_us);

            /*! @brief Writes and reads values sequentially to/from uart line.
            *
            * This function writes values to uart line firstly and then reads values from uart line and returns read
            * value as string. It creates temporary read buffer with specified size and reads values to this buffer.
            * Then resize buffer to read value size. BlackUART::readBufferSize variable is used to specify temporary
            * buffer size.
            *
            * @param [in] writeBuffer          write buffer
            * @param [in] wait_us              sleep time between writing and reading
            * @return read value if reading successful, else returns BlackLib::UART_READ_FAILED or
            * BlackLib::UART_WRITE_FAILED string.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   std::string writeToUart = "this is test.\n";
            *   std::string readFromUart;
            *
            *   readFromUart = myUart.transfer(writeToUart, 40000);
            *
            *   std::cout << "Test output on loopback: " << readFromUart;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            * @sa BlackUART::readBufferSize
            */
            std::string     transfer(std::string writeBuffer, uint32_t wait_us);

            /*! @brief Changes internal temporary buffers' sizes.
            *
            * This function changes internal buffers' sizes which are used at read and transfer operations.
            * This buffer size must be maximum possible read value size. Otherwise read value will truncate.
            *
            * @param [in] newBufferSize        new size of the temporary internal buffer
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   std::cout << "Current temporary buffer size: " << myUart.getReadBufferSize() << std::endl;
            *   myUart.setReadBufferSize(2048);
            *   std::cout << "Current temporary buffer size: " << myUart.getReadBufferSize();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current temporary buffer size: 1024
            *   // Current temporary buffer size: 2048
            * @endcode
            * @sa BlackUART::readBufferSize
            */
            void            setReadBufferSize(uint32_t newBufferSize);

            /*! @brief Changes baud rate of uart.
            *
            * This function changes baud rate of uart at specified direction. Also users can select apply
            * condition like ApplyNow, ApplyDrain, ApplyFlush.
            *
            * @param [in] newBaud         new baud rate value
            * @param [in] whichDirection  direction
            * @param [in] applyMode       new value's apply condition
            * @return true if changing operation is successful, else false.
            * @warning Before use this function, users must be called open function. If uart is not open,
            * this function returns false and sets errorUART::baudRateError and errorUART::openError flags.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   // 13 means Baud9600. See the BlackLib::baudRate enums.
            *   std::cout << "Current baud rate: " << myUart.getBaudRate(BlackLib::output) << std::endl;
            *
            *   myUart.setBaudRate(BlackLib::Baud19200, BlackLib::output, BlackLib::ApplyNow);
            *
            *   // 14 means Baud19200. See the BlackLib::baudRate enums.
            *   std::cout << "Current baud rate: " << myUart.getBaudRate(BlackLib::output);
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current baud rate: 13
            *   // Current baud rate: 14
            * @endcode
            *
            * @sa baudRate
            * @sa direction
            * @sa uartApplyMode
            */
            bool            setBaudRate(baudRate newBaud, direction whichDirection, uartApplyMode applyMode = ApplyNow );

            /*! @brief Changes parity of uart.
            *
            * This function changes parity of uart. Also users can select apply condition like ApplyNow,
            * ApplyDrain, ApplyFlush.
            *
            * @param [in] newParity       new parity value
            * @param [in] applyMode       new value's apply condition
            * @return true if changing operation is successful, else false.
            *
            * @warning Before use this function, users must be called open function. If uart is not open,
            * this function returns false and sets errorUART::parityError and errorUART::openError flags.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   // 2 means ParityEven. See the BlackLib::parity enums.
            *   std::cout << "Current parity: " << myUart.getParity() << std::endl;
            *
            *   myUart.setParity(BlackLib::ParityOdd, BlackLib::ApplyNow);
            *
            *   // 1 means ParityOdd. See the BlackLib::parity enums.
            *   std::cout << "Current parity: " << myUart.getParity();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current parity: 2
            *   // Current parity: 1
            * @endcode
            *
            * @sa parity
            * @sa uartApplyMode
            */
            bool            setParity(parity newParity, uartApplyMode applyMode = ApplyNow );

            /*! @brief Changes stop bits size of uart.
            *
            * This function changes stop bits size of uart. Also users can select apply condition like ApplyNow,
            * ApplyDrain, ApplyFlush.
            *
            * @param [in] newStopBits     new stop bits size value
            * @param [in] applyMode       new value's apply condition
            * @return true if changing operation is successful, else false.
            *
            * @warning Before use this function, users must be called open function. If uart is not open,
            * this function returns false and sets errorUART::stopBitsError and errorUART::openError flags.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   // 1 means StopOne. See the BlackLib::stopBits enums.
            *   std::cout << "Current stop bits size: " << myUart.getStopBits() << std::endl;
            *
            *   myUart.setStopBits(BlackLib::StopTwo, BlackLib::ApplyNow);
            *
            *   // 2 means StopTwo. See the BlackLib::stopBits enums.
            *   std::cout << "Current stop bits size: " << myUart.getStopBits();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current stop bits size: 1
            *   // Current stop bits size: 2
            * @endcode
            *
            * @sa stopBits
            * @sa uartApplyMode
            */
            bool            setStopBits(stopBits newStopBits, uartApplyMode applyMode = ApplyNow );

            /*! @brief Changes character size of uart.
            *
            * This function changes character size of uart. Also users can select apply condition like ApplyNow,
            * ApplyDrain, ApplyFlush.
            *
            * @param [in] newCharacterSize  new character size value
            * @param [in] applyMode         new value's apply condition
            * @return true if changing operation is successful, else false.
            *
            * @warning Before use this function, users must be called open function. If uart is not open,
            * this function returns false and sets errorUART::charSizeError and errorUART::openError flags.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   // 8 means Char8. See the BlackLib::characterSize enums.
            *   std::cout << "Current character size: " << myUart.getCharacterSize() << std::endl;
            *
            *   myUart.setCharacterSize(BlackLib::Char7, BlackLib::ApplyNow);
            *
            *   // 7 means Char7. See the BlackLib::characterSize enums.
            *   std::cout << "Current character size: " << myUart.getCharacterSize();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Current character size: 8
            *   // Current character size: 7
            * @endcode
            *
            * @sa characterSize
            * @sa uartApplyMode
            */
            bool            setCharacterSize(characterSize newCharacterSize, uartApplyMode applyMode = ApplyNow );

            /*! @brief Changes properties of uart.
            *
            * This function changes properties of uart. Also users can select apply condition like ApplyNow,
            * ApplyDrain, ApplyFlush. These properties are composed of baud rate, parity, stop bits size and
            * character size.
            *
            * @param [in] &props        new properties
            * @param [in] applyMode     new properties' apply condition
            * @return true if changing operation is successful, else false.
            *
            * @warning Before use this function, users must be called open function. If uart is not open,
            * this function returns false and sets errorUART::baudRateError, errorUART::charSizeError,
            * errorUART::parityError, errorUART::stopBitsError and errorUART::openError flags.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   BlackLib::BlackUartProperties currentProps = myUart.getProperties();
            *
            *   std::cout << "First bauds(in/out) : " << currentProps.uartBaudIn   << "/" << currentProps.uartBaudIn << std::endl
            *             << "First parity        : " << currentProps.uartParity   << std::endl
            *             << "First stop bits size: " << currentProps.uartStopBits << std::endl
            *             << "First character size: " << currentProps.uartCharSize << std::endl;
            *
            *   currentProps = BlackLib::BlackUartProperties(BlackLib::Baud19200, BlackLib::Baud19200,
            *                                                BlackLib::ParityOdd, BlackLib::StopTwo, BlackLib::Char7);
            *
            *   myUart.setProperties(currentProps, BlackLib::ApplyNow);
            *
            *   std::cout << "Second bauds(in/out) : " << currentProps.uartBaudIn   << "/" << currentProps.uartBaudIn << std::endl
            *             << "Second parity        : " << currentProps.uartParity   << std::endl
            *             << "Second stop bits size: " << currentProps.uartStopBits << std::endl
            *             << "Second character size: " << currentProps.uartCharSize << std::endl;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // First bauds(in/out) : 13/13
            *   // First parity        : 2
            *   // First stop bits size: 1
            *   // First character size: 8
            *   // Second bauds(in/out) : 14/14
            *   // Second parity        : 1
            *   // Second stop bits size: 2
            *   // Second character size: 7
            * @endcode
            *
            * @sa BlackUartProperties
            * @sa uartApplyMode
            */
            bool            setProperties(BlackUartProperties &props, uartApplyMode applyMode = ApplyNow );

            /*! @brief Exports properties of uart.
            *
            * This function gets properties of uart. These properties are composed of baud rate, parity, stop bits size and
            * character size.
            *
            * @return BlackUART::currentUartProperties struct with updated values.
            *
            * @par Example
            *   Example usage is shown in BlackUART::setProperties() function's example.
            *
            * @sa BlackUartProperties
            */
            BlackUartProperties getProperties();

            /*! @brief Exports uart's port path.
            *
            * @return uart's port path as string.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Port path: " << myUart.getPortName();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Port path: /dev/ttyO1
            * @endcode
            *
            * @sa uartPortPath
            */
            std::string     getPortName();

            /*! @brief Exports internal temporary buffers' size.
            *
            * @return size of internal temporary buffers.
            *
            * @par Example
            *   Example usage is shown in BlackUART::setReadBufferSize() function's example.
            *
            * @sa readBufferSize
            */
            uint32_t        getReadBufferSize();

            /*! @brief Exports baud rate value of uart.
            *
            * This function Exports baud rate value of uart at specified direction.
            *
            * @param [in] whichDirection  direction
            * @return baud rate value of uart.
            *
            * @par Example
            *   Example usage is shown in BlackUART::setBaudRate() function's example.
            *
            * @sa baudRate
            * @sa direction
            */
            baudRate        getBaudRate(direction whichDirection);

            /*! @brief Exports parity value of uart.
            *
            * @return parity value of uart.
            *
            * @par Example
            *   Example usage is shown in BlackUART::setParity() function's example.
            *
            * @sa parity
            */
            parity          getParity();

            /*! @brief Exports stop bits size value of uart.
            *
            * @return stop bits size value of uart.
            *
            * @par Example
            *   Example usage is shown in BlackUART::setStopBits() function's example.
            *
            * @sa stopBits
            */
            stopBits        getStopBits();

            /*! @brief Exports character size value of uart.
            *
            * @return character size value of uart.
            *
            * @par Example
            *   Example usage is shown in BlackUART::setCharacterSize() function's example.
            *
            * @sa characterSize
            */
            characterSize   getCharacterSize();

            /*! @brief Checks uart's tty file's open state.
            *
            * @return true if tty file is open, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   std::cout << "Is open?: " << std::boolalpha << myUart.isOpen() << std::endl;
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Is open?: " << std::boolalpha << myUart.isOpen();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Is open?: false
            *   // Is open?: true
            * @endcode
            *
            * @sa BlackUART::isOpenFlag
            */
            bool            isOpen();

            /*! @brief Checks uart's tty file's close state.
            *
            * @return true if tty file is close, else false.
            *
            * @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   std::cout << "Is close?: " << std::boolalpha << myUart.isClose() << std::endl;
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *
            *   std::cout << "Is close?: " << std::boolalpha << myUart.isClose();
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Is close?: true
            *   // Is close?: false
            * @endcode
            *
            * @sa BlackUART::isOpenFlag
            */
            bool            isClose();

            /*! @brief Is used for general debugging.
            *
            * @return True if any error occured, else false.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite );
            *
            *   if( myUart.fail() )
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
            bool            fail();

            /*! @brief Is used for specific debugging.
            *
            * You can use this function, after call BlackUART member functions in your code. The
            * input parameter is used for finding out status of selected error.
            * @param [in] f specific error type (enum)
            * @return Value of @a selected error.
            *
            * @par Example
            *  @code{.cpp}
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *
            *   if( myUart.fail(BlackLib::BlackUART::dtErr) )
            *   {
            *       std::cout << "BlackUART INITIALIZATION FAILED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "BlackUART INITIALIZATION IS OK" << std::endl;
            *   }
            *
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock  );
            *
            *   if( myUart.fail(BlackLib::BlackUART::openErr) )
            *   {
            *       std::cout << "OPENNING ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "OPENNING IS OK" << std::endl;
            *   }
            *
            *
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   if( myUart.fail(BlackLib::BlackUART::directionErr) or myUart.fail(BlackLib::BlackUART::flushErr) )
            *   {
            *       std::cout << "FLUSHING ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "FLUSHING IS OK" << std::endl;
            *   }
            *
            *   std::string writeThis = "Loopback test message.";
            *   std::string readThis  = myUart.transfer( writeThis, 40000 );
            *
            *   if( myUart.fail(BlackLib::BlackUART::readErr) or myUart.fail(BlackLib::BlackUART::writeErr) )
            *   {
            *       std::cout << "TRANSFER ERROR OCCURED" << std::endl;
            *   }
            *   else
            *   {
            *       std::cout << "TRANSFER IS OK" << std::endl;
            *   }
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // BlackUART INITIALIZATION IS OK
            *   // OPENNING IS OK
            *   // FLUSHING IS OK
            *   // TRANSFER IS OK
            * @endcode
            *
            * @sa errorUART
            */
            bool            fail(BlackUART::flags f);


            /*! @brief Writes values to uart line with "<<" operator.
            *
            *  This function writes values to uart line. Values sent to this function as string type.
            *  @param [in] &writeFromThis to uart
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   std::string writeToUart  = "this is test.\n";
            *   myUart << writeToUart;
            *
            *   sleep(1);
            *
            *   std::string readFromUart;
            *   myUart >> readFromUart;
            *
            *   std::cout << "Test output on loopback: " << readFromUart;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            */
            BlackUART&      operator<<(std::string &writeFromThis);

            /*! @brief Reads values from uart line with ">>" operator.
            *
            *  This function reads values from uart line with ">>" operator. It creates temporary read
            *  buffer with specified size and reads values to this buffer. Then resize buffer to read
            *  value size. BlackUART::readBufferSize variable is used to specify temporary buffer size.
            *  @param [in] &readToThis from uart. If reading fails, this functions sets
            *  BlackLib::UART_READ_FAILED string to this variable.
            *
            *  @par Example
            *  @code{.cpp}
            *
            *   BlackLib::BlackUART  myUart(BlackLib::UART1,
            *                               BlackLib::Baud9600,
            *                               BlackLib::ParityEven,
            *                               BlackLib::StopOne,
            *                               BlackLib::Char8 );
            *
            *   myUart.open( BlackLib::ReadWrite | BlackLib::NonBlock );
            *   myUart.flush( BlackLib::bothDirection );
            *
            *   std::string writeToUart  = "this is test.\n";
            *   myUart << writeToUart;
            *
            *   sleep(1);
            *
            *   std::string readFromUart;
            *   myUart >> readFromUart;
            *
            *   std::cout << "Test output on loopback: " << readFromUart;
            *
            * @endcode
            * @code{.cpp}
            *   // Possible Output:
            *   // Test output on loopback: this is test.
            * @endcode
            */
            BlackUART&      operator>>(std::string &readToThis);
    };

    // ########################################### BLACKUART DECLARATION ENDS ############################################## //


} /* namespace BlackLib */

#endif /* BLACKUART_H_ */
