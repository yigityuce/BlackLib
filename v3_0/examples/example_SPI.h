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




#ifndef EXAMPLE_SPI_H_
#define EXAMPLE_SPI_H_


#include "../BlackSPI/BlackSPI.h"
#include <string>
#include <iostream>
#include <iomanip>




void example_SPI()
{

    /*
     * This part of the example code is about BlackSPI class, write/read buffer and write/read
     * byte initialization.
     *
     * BlackSPI class also can be use like below:
     * 1) BlackSPI(enum spiName spi);
     * 2) BlackSPI(enum spiName spi, struct BlackSpiProperties spiProperties);
     * 3) BlackSPI(enum spiName spi, uint8_t spiBitsPerWord, uint8_t spiMode, uint32_t spiSpeed);
     */

    BlackLib::BlackSPI spiDemo(BlackLib::SPI0_0, 8, BlackLib::SpiDefault , 2400000);

    uint8_t writeByte   = 0xb1;
    uint8_t readByte;

    uint8_t writeArr[4] = { 0x55, 0xaa, 0xf0, 0x0c } ;
    uint8_t readArr[4];






    /*
     * This part of the example code is about spi device connection openning with
     * BlackLib::openMode enums and getting information about current spi connection.
     */

    bool isOpened = spiDemo.open(BlackLib::ReadWrite|BlackLib::NonBlock);

    if( !isOpened )
    {
        std::cout << "SPI DEVICE CAN\'T OPEN.;" << std::endl;
        exit(1);
    }

    std::cout << std::endl;
    std::cout << "Device Path   : " << spiDemo.getPortName() << std::endl;
    std::cout << "Max Speed(Hz) : " << spiDemo.getMaximumSpeed() << std::endl;
    std::cout << "Bits Per Word : " << (int)spiDemo.getBitsPerWord() << std::endl;
    std::cout << "Mode          : " << (int)spiDemo.getMode() << std::endl << std::endl ;







    /*
     * This part of the example code is about transfering data from/to uint8_t byte with
     * transfer() function and displaying result. Displaying part is unnecessery.
     */

    readByte = spiDemo.transfer(writeByte,0);

    std::cout << std::setw(43) << "ONESHOT TRANSFER DEMO WITH ONE BYTE" << std::endl;
    std::cout << std::setw(15) << "SENT" << std::setw(26) << "RECEIVED" << std::endl;
    std::cout << std::string(50,'-');

    std::cout << "\n\t    " << std::hex << (int)writeByte;
    std::cout << "\t\t\t    " << std::hex << (int)readByte << std::endl << std::endl << std::endl;







    /*
     * This part of the example code is about transfering datas from/to arrays with
     * transfer() function and displaying results. Displaying part is unnecessery.
     */

    std::cout << std::setw(43) << "ONESHOT TRANSFER DEMO WITH ARRAYS" << std::endl;
    std::cout << std::setw(15) << "SENT" << std::setw(26) << "RECEIVED" << std::endl;
    std::cout << std::string(50,'-');

    memset(readArr,0,sizeof(readArr));

    spiDemo.transfer(writeArr, readArr, sizeof readArr);

    std::cout << "\n\t" << std::hex << (int)writeArr[0] << " " << (int)writeArr[1]
                            <<  " " << (int)writeArr[2] << " " << (int)writeArr[3];

    std::cout << "\t\t" << std::hex << (int)readArr[0] << " " << (int)readArr[1]
                            <<  " " << (int)readArr[2] << " " << (int)readArr[3] << std::endl << std::endl << std::endl;












    /*
     * This part of the example code is about changing properties of SPI and displaying results.
     * This can be 2 ways. Second method is faster than the first one. Displaying part is unnecessery.
     */

    spiDemo.setBitsPerWord(16);
    spiDemo.setMaximumSpeed(2000000);
    spiDemo.setMode(BlackLib::SpiMode2);

    std::cout << std::setw(42) << "PROPERTIES AFTER FIRST UPDATE" << std::endl;
    std::cout << std::string(50,'-');
    std::cout << "\nMax Speed(Hz) : " << std::dec << spiDemo.getMaximumSpeed() << std::endl;
    std::cout << "Bits Per Word : "   << std::dec << (int)spiDemo.getBitsPerWord() << std::endl;
    std::cout << "Mode          : "   << std::dec << (int)spiDemo.getMode() << std::endl << std::endl ;



    BlackLib::BlackSpiProperties newProperties(14, (BlackLib::SpiPhase|BlackLib::SpiPolarity) , 24000000);
    spiDemo.setProperties( newProperties );
    BlackLib::BlackSpiProperties updatedProperties = spiDemo.getProperties();

    std::cout << std::setw(42) << "PROPERTIES AFTER SECOND UPDATE" << std::endl;
    std::cout << std::string(50,'-');
    std::cout << "\nMax Speed(Hz) : " << std::dec << updatedProperties.spiSpeed << std::endl;
    std::cout << "Bits Per Word : "   << std::dec << (int)updatedProperties.spiBitsPerWord << std::endl;
    std::cout << "Mode          : "   << std::dec << (int)updatedProperties.spiMode << std::endl << std::endl ;


}

#endif /* EXAMPLE_SPI_H_ */
