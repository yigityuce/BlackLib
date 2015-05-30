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





#ifndef EXAMPLE_UART_H_
#define EXAMPLE_UART_H_

#include "../BlackUART/BlackUART.h"
#include <string>
#include <iostream>
#include <iomanip>





void example_UART()
{



    /*
     * This part of the example code is about BlackUART class, write/read buffer and write/read
     * string initialization.
     *
     * 1) BlackUART(enum uartName uart);
     * 2) BlackUART(enum uartName uart, struct BlackUartProperties uartProperties);
     * 3) BlackUART(enum uartName uart, enum baudRate uartBaud, enum parity uartParity,
     *                                  enum stopBits uartStopBits, enum characterSize uartCharSize);
     */

    BlackLib::BlackUART uartDemo( BlackLib::UART1,
                                  BlackLib::Baud9600,
                                  BlackLib::ParityEven,
                                  BlackLib::StopOne,
                                  BlackLib::Char8);





    char writeArr[22] = "BlackLib UART EXAMPLE";
    char readArr[22];

    std::string writeStr = "BlackLib UART EXAMPLE";
    std::string readStr;





    /*
     * This part of the example code is about uart device connection openning with
     * BlackLib::openMode enums and getting information about current uart connection.
     */

    bool isOpened = uartDemo.open( BlackLib::ReadWrite | BlackLib::NonBlock );

    if( !isOpened )
    {
        std::cout << "UART DEVICE CAN\'T OPEN.;" << std::endl;
        exit(1);
    }

    std::cout << std::endl;
    std::cout << "Device Path     : " << uartDemo.getPortName() << std::endl;
    std::cout << "Read Buf. Size  : " << uartDemo.getReadBufferSize() << std::endl;
    std::cout << "BaudRate In/Out : " << uartDemo.getBaudRate( BlackLib::input) << "/"
                                      << uartDemo.getBaudRate( BlackLib::output) << std::endl;
    std::cout << "Character Size  : " << uartDemo.getCharacterSize() << std::endl;
    std::cout << "Stop Bit Size   : " << uartDemo.getStopBits() << std::endl;
    std::cout << "Parity          : " << uartDemo.getParity() << std::endl << std::endl;






    /*
     * This part of the example code is about transfering datas from/to arrays with
     * transfer() function and displaying results. Displaying part is unnecessery.
     */

    std::cout << std::setw(43) << "5 TIMES TRANSFER DEMO WITH ARRAYS" << std::endl;
    std::cout << std::setw(15) << "SENT" << std::setw(26) << "RECEIVED" << std::endl;
    std::cout << std::string(50,'-') << std::endl;

    for( int i=0 ; i<5 ; i++)
    {
        memset(readArr, 0, sizeof(readArr) );
        uartDemo.transfer(writeArr, readArr, sizeof readArr, 40000);

        std::cout << "   " << writeArr;
        std::cout << "\t" << readArr << std::endl;
    }
    std::cout << std::endl << std::endl;






    /*
     * This part of the example code is about transfering datas from/to strings with
     * transfer() function and displaying results. Displaying part is unnecessery.
     */

    readStr = uartDemo.transfer(writeStr, 0);

    std::cout << std::setw(43) << "ONESHOT TRANSFER DEMO WITH STRINGS" << std::endl;
    std::cout << std::setw(15) << "SENT" << std::setw(26) << "RECEIVED" << std::endl;
    std::cout << std::string(50,'-');

    std::cout << "\n   " << writeStr;
    std::cout << "\t" << readStr << std::endl << std::endl << std::endl;








    /*
     * This part of the example code is about transfering datas from/to arrays with
     * write()/read() functions and displaying results. Displaying part is unnecessery.
     */

    memset(readArr,0,sizeof(readArr));

    uartDemo.write(writeArr, sizeof writeArr);

    usleep(40000);

    uartDemo.read(readArr, sizeof readArr);

    std::cout << std::setw(44) << "ONESHOT WRITE/READ DEMO WITH ARRAYS" << std::endl;
    std::cout << std::setw(15) << "SENT" << std::setw(26) << "RECEIVED" << std::endl;
    std::cout << std::string(50,'-');

    std::cout << "\n   " << writeArr;
    std::cout << "\t" << readArr << std::endl << std::endl << std::endl;








    /*
     * This part of the example code is about transfering datas from/to strings with
     * write()/read() functions and displaying results. Displaying part is unnecessery.
     */

    uartDemo.write(writeStr);

    usleep(40000);

    readStr = uartDemo.read();

    std::cout << std::setw(44) << "ONESHOT WRITE/READ DEMO WITH STRINGS" << std::endl;
    std::cout << std::setw(15) << "SENT" << std::setw(26) << "RECEIVED" << std::endl;
    std::cout << std::string(50,'-');

    std::cout << "\n   " << writeStr;
    std::cout << "\t" << readStr << std::endl << std::endl << std::endl;







    /*
     * This part of the example code is about transafering datas from/to strings with
     * << and >> overloaded operators and displaying results. Displaying part is unnecessery.
     */

    uartDemo << writeStr;

    usleep(40000);

    uartDemo >> readStr;

    std::cout << std::setw(48) << "ONESHOT TRANSFER DEMO WITH OPERATOR OVERLOAD" << std::endl;
    std::cout << std::setw(15) << "SENT" << std::setw(26) << "RECEIVED" << std::endl;
    std::cout << std::string(50,'-');

    std::cout << "\n   " << writeStr;
    std::cout << "\t" << readStr << std::endl << std::endl << std::endl;







    /*
     * This part of the example code is about changing properties of UART and displaying results.
     * This can be 2 ways. Second method is faster than the first one. Displaying part is unnecessery.
     */

    uartDemo.setCharacterSize( BlackLib::Char7 );
    uartDemo.setParity( BlackLib::ParityNo );
    uartDemo.setStopBits( BlackLib::StopTwo );
    uartDemo.setBaudRate( BlackLib::Baud38400, BlackLib::bothDirection );
    uartDemo.setReadBufferSize(150);

    std::cout << std::setw(42) << "PROPERTIES AFTER FIRST UPDATE" << std::endl;
    std::cout << std::string(50,'-');
    std::cout << "\nRead Buf. Size  : " << uartDemo.getReadBufferSize() << std::endl;
    std::cout << "BaudRate In/Out : " << uartDemo.getBaudRate( BlackLib::input ) << "/"
                                      << uartDemo.getBaudRate( BlackLib::output ) << std::endl;
    std::cout << "Character Size  : " << uartDemo.getCharacterSize() << std::endl;
    std::cout << "Stop Bit Size   : " << uartDemo.getStopBits() << std::endl;
    std::cout << "Parity          : " << uartDemo.getParity() << std::endl << std::endl;



    BlackLib::BlackUartProperties newProperties( BlackLib::Baud50,
                                                 BlackLib::Baud50,
                                                 BlackLib::ParityOdd,
                                                 BlackLib::StopOne,
                                                 BlackLib::Char5 );
    uartDemo.setProperties( newProperties );
    BlackLib::BlackUartProperties updatedProperties = uartDemo.getProperties();

    std::cout << std::setw(42) << "PROPERTIES AFTER SECOND UPDATE" << std::endl;
    std::cout << std::string(50,'-');
    std::cout << "\nRead Buf. Size  : " << uartDemo.getReadBufferSize() << std::endl;
    std::cout << "BaudRate In/Out : " << updatedProperties.uartBaudIn << "/" << updatedProperties.uartBaudOut << std::endl;
    std::cout << "Character Size  : " << updatedProperties.uartCharSize << std::endl;
    std::cout << "Stop Bit Size   : " << updatedProperties.uartStopBits << std::endl;
    std::cout << "Parity          : " << updatedProperties.uartParity << std::endl << std::endl;


}


#endif /* EXAMPLE_UART_H_ */
