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




#include "BlackI2C.h"

namespace BlackLib
{

    BlackI2C::BlackI2C(i2cName i2c, unsigned int i2cDeviceAddress)
    {
        this->i2cPortPath   = "/dev/i2c-" + tostr(static_cast<int>(i2c));
        this->i2cDevAddress = i2cDeviceAddress;
        this->i2cFD         = -1;
        this->isOpenFlag    = false;

        this->i2cErrors     = new errorI2C( this->getErrorsFromCore() );
    }


    BlackI2C::~BlackI2C()
    {
        this->close();
        delete this->i2cErrors;
    }


    inline bool BlackI2C::useSmbusIOCTL(direction rwMode, uint8_t registerAddr, transactionType smbusTransaction, i2c_smbus_data &data)
    {
        if( rwMode == bothDirection ) { return false; }

        i2c_smbus_ioctl_data smbusPackage;

        smbusPackage.read_write = (rwMode == input ) ? I2C_SMBUS_READ : I2C_SMBUS_WRITE;
        smbusPackage.command    = registerAddr;
        smbusPackage.size       = smbusTransaction;
        smbusPackage.data       = &data;


        if( ::ioctl(this->i2cFD, I2C_SMBUS, &smbusPackage) < 0 )
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool    BlackI2C::setSlave()
    {
        if( ::ioctl(this->i2cFD, I2C_SLAVE, this->i2cDevAddress) < 0)
        {
            this->i2cErrors->setSlaveError = true;
            return false;
        }
        else
        {
            this->i2cErrors->setSlaveError = false;
            return true;
        }
    }

    bool    BlackI2C::loadDeviceTree()
    {
        return false;
    }





    bool    BlackI2C::open(uint openMode)
    {
        uint flags = 0;

        if( (openMode & ReadOnly)   == ReadOnly     ){  flags |= O_RDONLY;  }
        if( (openMode & WriteOnly)  == WriteOnly    ){  flags |= O_WRONLY;  }
        if( (openMode & ReadWrite)  == ReadWrite    ){  flags |= O_RDWR;    }
        if( (openMode & Append)     == Append       ){  flags |= O_APPEND;  }
        if( (openMode & Truncate)   == Truncate     ){  flags |= O_TRUNC;   }
        if( (openMode & NonBlock)   == NonBlock     ){  flags |= O_NONBLOCK;}


        this->i2cFD = ::open(this->i2cPortPath.c_str(), flags);


        if( this->i2cFD < 0 )
        {
            this->isOpenFlag = false;
            this->i2cErrors->openError = true;
            return false;
        }
        else
        {
            this->isOpenFlag = true;
            this->i2cErrors->openError = false;
            this->setSlave();
            return true;
        }
    }

    bool    BlackI2C::close()
    {
        if( ::close(this->i2cFD) < 0 )
        {
            this->i2cErrors->closeError = true;
            return false;
        }
        else
        {
            this->i2cErrors->closeError = false;
            this->isOpenFlag = false;
            return true;
        }
    }






    bool    BlackI2C::writeByte(uint8_t registerAddr, uint8_t value)
    {
        this->setSlave();

        i2c_smbus_data writeFromThis;
        writeFromThis.byte = value;

        if( this->useSmbusIOCTL(output, registerAddr, SMBUS_BYTE_DATA, writeFromThis) )
        {
            this->i2cErrors->writeError = false;
            return true;
        }
        else
        {
            this->i2cErrors->writeError = true;
            return false;
        }
    }

    uint8_t BlackI2C::readByte(uint8_t registerAddr)
    {
        this->setSlave();

        i2c_smbus_data readToThis;
        if( this->useSmbusIOCTL(input, registerAddr, SMBUS_BYTE_DATA, readToThis) )
        {
            this->i2cErrors->readError = false;
            return readToThis.byte;
        }
        else
        {
            this->i2cErrors->readError = true;
            return 0x00;
        }
    }



    bool    BlackI2C::writeWord(uint8_t registerAddr, uint16_t value)
    {
        this->setSlave();

        i2c_smbus_data writeFromThis;
        writeFromThis.word = value;

        if( this->useSmbusIOCTL(output, registerAddr, SMBUS_WORD_DATA, writeFromThis) )
        {
            this->i2cErrors->writeError = false;
            return true;
        }
        else
        {
            this->i2cErrors->writeError = true;
            return false;
        }
    }

    uint16_t BlackI2C::readWord(uint8_t registerAddr)
    {
        this->setSlave();

        i2c_smbus_data readToThis;

        if( this->useSmbusIOCTL(input, registerAddr, SMBUS_WORD_DATA, readToThis) )
        {
            this->i2cErrors->readError = false;
            return readToThis.word;
        }
        else
        {
            this->i2cErrors->readError = true;
            return 0x0000;
        }

    }



    bool    BlackI2C::writeBlock(uint8_t registerAddr, uint8_t *writeBuffer, size_t bufferSize)
    {
        this->setSlave();

        if( bufferSize > 32 )
        {
            bufferSize = 32;
        }


        i2c_smbus_data writeFromThis;

        memset(writeFromThis.block, 0, bufferSize+1);
        memcpy( &(writeFromThis.block[1]), writeBuffer, bufferSize);
        writeFromThis.block[0] = bufferSize;

        if( this->useSmbusIOCTL(output, registerAddr, SMBUS_I2C_BLOCK_DATA, writeFromThis) )
        {
            this->i2cErrors->writeError = false;
            return true;
        }
        else
        {
            this->i2cErrors->writeError = true;
            return false;
        }
    }

    uint8_t BlackI2C::readBlock(uint8_t registerAddr, uint8_t *readBuffer, size_t bufferSize)
    {
        this->setSlave();
        if( bufferSize > 32 )
        {
            bufferSize = 32;
        }

        i2c_smbus_data readToThis;
        readToThis.block[0] = bufferSize;

        if( this->useSmbusIOCTL(input, registerAddr, SMBUS_I2C_BLOCK_DATA, readToThis) )
        {
            this->i2cErrors->readError = false;
            memcpy(readBuffer, &(readToThis.block[1]), bufferSize);
            return readToThis.block[0];
        }
        else
        {
            this->i2cErrors->readError = true;
            return 0x00;
        }

    }



    bool    BlackI2C::writeLine(uint8_t *writeBuffer, size_t bufferSize)
    {
        this->setSlave();
        if( ::write(this->i2cFD, writeBuffer, bufferSize) < 0 )
        {
            this->i2cErrors->writeError = true;
            return false;
        }
        else
        {
            this->i2cErrors->writeError = false;
            return true;
        }
    }

    bool    BlackI2C::readLine(uint8_t *readBuffer, size_t bufferSize)
    {
        this->setSlave();
        if( ::read(this->i2cFD, readBuffer, bufferSize) < 0 )
        {
            this->i2cErrors->readError = true;
            return false;
        }
        else
        {
            this->i2cErrors->readError = false;
            return true;
        }
    }



    void    BlackI2C::setDeviceAddress(unsigned int newDeviceAddr)
    {
        this->i2cDevAddress = newDeviceAddr;
        this->setSlave();
    }

    int     BlackI2C::getDeviceAddress()
    {
        return this->i2cDevAddress;
    }





    std::string BlackI2C::getPortName()
    {
        return this->i2cPortPath;
    }

    bool        BlackI2C::isOpen()
    {
        return this->isOpenFlag;
    }

    bool        BlackI2C::isClose()
    {
        return !(this->isOpenFlag);
    }


    bool        BlackI2C::fail()
    {
        return (this->i2cErrors->openError or
                this->i2cErrors->closeError or
                this->i2cErrors->setSlaveError or
                this->i2cErrors->readError or
                this->i2cErrors->writeError
                );
    }

    bool        BlackI2C::fail(BlackI2C::flags f)
    {
        if(f==openErr)          { return this->i2cErrors->openError;        }
        if(f==closeErr)         { return this->i2cErrors->closeError;       }
        if(f==setSlaveErr)      { return this->i2cErrors->setSlaveError;    }
        if(f==readErr)          { return this->i2cErrors->readError;        }
        if(f==writeErr)         { return this->i2cErrors->writeError;       }

        return true;
    }






} /* namespace BlackLib */
