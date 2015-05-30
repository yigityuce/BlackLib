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



#ifndef EXAMPLE_I2C_H_
#define EXAMPLE_I2C_H_


#pragma GCC diagnostic ignored "-Wunused-variable"



#include "../BlackI2C/BlackI2C.h"
#include <string>
#include <iostream>







void example_I2C()
{

    BlackLib::BlackI2C  myI2c(BlackLib::I2C_1, 0x53);


    bool isOpened = myI2c.open( BlackLib::ReadWrite | BlackLib::NonBlock );

    if( !isOpened )
    {
        std::cout << "I2C DEVICE CAN\'T OPEN.;" << std::endl;
        exit(1);
    }



    // read-write register
    uint8_t powerCtl_Addr   = 0x2D;
    uint8_t offsetX_Addr    = 0x1E;
    uint8_t offsetY_Addr    = 0x1F;
    uint8_t offsetZ_Addr    = 0x20;

    // read only register
    uint8_t axisX0_Addr     = 0x32;
    uint8_t axisX1_Addr     = 0x33;
    uint8_t axisY0_Addr     = 0x34;
    uint8_t axisY1_Addr     = 0x35;
    uint8_t axisZ0_Addr     = 0x36;
    uint8_t axisZ1_Addr     = 0x37;

    // set bit
    uint8_t measureMode     = 0x08;














    uint8_t powerCtlReg     = myI2c.readByte(powerCtl_Addr);


    std::cout << "Power Ctrl's current value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;

    powerCtlReg |= (measureMode);      //                      ___ ___ ___ ___|___ ___ ___ ___
                                       // powerCtlReg:        |_x_|_x_|_x_|_x_|_x_|_x_|_x_|_x_|
                                       // measureMode:        |_0_|_0_|_0_|_0_|_1_|_0_|_0_|_0_|
                                       //                      ___ ___ ___ ___|___ ___ ___ ___ or these
                                       // result:             |_x_|_x_|_x_|_x_|_1_|_x_|_x_|_x_|

    bool resultOfWrite      = myI2c.writeByte(powerCtl_Addr, powerCtlReg);


    powerCtlReg             = myI2c.readByte(powerCtl_Addr);
    std::cout << "Power Ctrl's new value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;














    // Example: Register Map of slave device(0x53), Little-Endian System
    // ----------------------------------
    // |   | 0 | 1 | .......... | e | f |
    // ----------------------------------
    // |00 |...|...| .......... |...|...|
    // ----------------------------------
    // |10 |...|...| .......... | 1 | 4 |   ==> 0x1E = 0x01 , 0x1F = 0x04
    // ----------------------------------
    // | : | : | : | .......... | : | : |
    // | : | : | : | .......... | : | : |
    // | : | : | : | .......... | : | : |
    // ----------------------------------
    // |f0 |...|...| .......... |...|...|
    // ----------------------------------
    //
    // When users read word data from 0x1E address, word value is 0x0401.
    // This means smallest address(0x1E) will be least significant byte(LSB, 0x01)
    // and largest address(0x1F) will be most significant byte(MSB, 0x04)

    int16_t tempRead        = myI2c.readWord(offsetX_Addr);


    uint8_t offsetX         = static_cast<uint8_t>(tempRead & 0xFF);
    uint8_t offsetY         = static_cast<uint8_t>(tempRead >> 8);
    std::cout << "\nOffset X's current value: " << std::hex << (int)offsetX << std::dec << std::endl;
    std::cout << "Offset Y's current value: " << std::hex << (int)offsetY << std::dec << std::endl;

    offsetX                 = 0xA0;
    offsetY                 = 0x0B;
    uint16_t tempWrite      = ((static_cast<uint16_t>(offsetY) << 8) | static_cast<uint16_t>(offsetX));

    resultOfWrite           = myI2c.writeWord(offsetX_Addr, tempWrite);


    std::cout << "Offset X&Y's new value is wrote?: " << std::boolalpha << resultOfWrite << std::dec << std::endl;

    tempRead                = myI2c.readWord(offsetX_Addr);
    offsetX                 = static_cast<uint8_t>(tempRead & 0xFF);
    offsetY                 = static_cast<uint8_t>(tempRead >> 8);
    std::cout << "Offset X's new value: " << std::hex << (int)offsetX << std::dec << std::endl;
    std::cout << "Offset Y's new value: " << std::hex << (int)offsetY << std::dec << std::endl;











    // Block read/write data from SMBUS.

    uint8_t offsetValues[3]     = { 0x00, 0x00, 0x00 };

    uint8_t readBlockSize       = myI2c.readBlock(offsetX_Addr, offsetValues, sizeof(offsetValues) );

    std::cout << "\nTotal read block size: "  << (int)readBlockSize << std::endl;
    std::cout << "Offset X's current value: " << std::hex << (int)offsetValues[0] << std::dec << std::endl;
    std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues[1] << std::dec << std::endl;
    std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues[2] << std::dec << std::endl;

    offsetValues[0]             = 0x1A;
    offsetValues[1]             = 0x2B;
    offsetValues[2]             = 0x3C;

    resultOfWrite               = myI2c.writeBlock(offsetX_Addr, offsetValues, sizeof(offsetValues) );


    std::cout << "Offsets' new values are wrote?: " << std::boolalpha << resultOfWrite << std::dec << std::endl;
    memset(offsetValues, 0, sizeof(offsetValues));      // clear buffer

    readBlockSize               = myI2c.readBlock(offsetX_Addr, offsetValues, sizeof(offsetValues) );
    std::cout << "Total read block size: " << (int)readBlockSize << std::endl;
    std::cout << "Offset X's current value: " << std::hex << (int)offsetValues[0] << std::dec << std::endl;
    std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues[1] << std::dec << std::endl;
    std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues[2] << std::dec << std::endl;












    // Pure read/write data from i2c line directly.

    uint8_t offsetValues2[3]    = { 0x00, 0x00, 0x00 };
    myI2c.writeLine(&offsetX_Addr, 1);                        // address of register which will read datas

    myI2c.readLine( offsetValues2, sizeof(offsetValues2) );   // read three data from "offsetX_Addr"

    std::cout << "\nOffset X's current value: " << std::hex << (int)offsetValues2[0] << std::dec << std::endl;
    std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues2[1] << std::dec << std::endl;
    std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues2[2] << std::dec << std::endl;


    offsetValues2[0]            = 0xD4;
    offsetValues2[1]            = 0xE5;
    offsetValues2[2]            = 0xF6;
    uint8_t tempBufWithAddr[4]  = { offsetX_Addr, offsetValues2[0], offsetValues2[1], offsetValues2[2] };

    resultOfWrite               = myI2c.writeLine(tempBufWithAddr, sizeof(tempBufWithAddr) );

    std::cout << "Offsets' new values are wrote?: " << std::boolalpha << resultOfWrite << std::dec << std::endl;

    memset(offsetValues2, 0, sizeof(offsetValues2));          // clear buffer
    myI2c.writeLine(&offsetX_Addr, 1);                        // address of register which will read datas
    myI2c.readLine( offsetValues2, sizeof(offsetValues2) );   // read three data from "offsetX_Addr"

    std::cout << "Offset X's current value: " << std::hex << (int)offsetValues2[0] << std::dec << std::endl;
    std::cout << "Offset Y's current value: " << std::hex << (int)offsetValues2[1] << std::dec << std::endl;
    std::cout << "Offset Z's current value: " << std::hex << (int)offsetValues2[2] << std::dec << std::endl;



}




#endif /* EXAMPLE_I2C_H_ */
