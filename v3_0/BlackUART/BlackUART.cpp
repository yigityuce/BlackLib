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



#include "BlackUART.h"


namespace BlackLib
{

    BlackUART::BlackUART(uartName uart, baudRate uartBaud, parity uartParity, stopBits uartStopBits, characterSize uartCharSize)
    {
        this->dtUartFilename            = "BB-UART" + tostr(static_cast<int>(uart));
        this->uartPortPath              = "/dev/ttyO" + tostr(static_cast<int>(uart));

        this->readBufferSize            = 1024;
        this->uartFD                    = -1;
        this->isOpenFlag                = false;
        this->isCurrentEqDefault        = false;

        this->uartErrors                = new errorUART( this->getErrorsFromCore() );
        this->constructorProperties     = BlackUartProperties(uartBaud, uartBaud, uartParity, uartStopBits, uartCharSize);

        this->loadDeviceTree();
    }


    BlackUART::BlackUART(uartName uart, BlackUartProperties uartProperties)
    {
        this->dtUartFilename            = "BB-UART" + tostr(static_cast<int>(uart));
        this->uartPortPath              = "/dev/ttyO" + tostr(static_cast<int>(uart));

        this->readBufferSize            = 1024;
        this->uartFD                    = -1;
        this->isOpenFlag                = false;
        this->isCurrentEqDefault        = false;

        this->uartErrors                = new errorUART( this->getErrorsFromCore() );
        this->constructorProperties     = uartProperties;

        this->loadDeviceTree();
    }


    BlackUART::BlackUART(uartName uart)
    {
        this->dtUartFilename            = "BB-UART" + tostr(static_cast<int>(uart));
        this->uartPortPath              = "/dev/ttyO" + tostr(static_cast<int>(uart));

        this->readBufferSize            = 1024;
        this->uartFD                    = -1;
        this->isOpenFlag                = false;
        this->isCurrentEqDefault        = true;

        this->uartErrors                = new errorUART( this->getErrorsFromCore() );

        this->loadDeviceTree();
    }


    BlackUART::~BlackUART()
    {
        this->close();
        delete this->uartErrors;
    }



    bool        BlackUART::loadDeviceTree()
    {
        std::string file = this->getSlotsFilePath();

        std::ofstream slotsFile;
        slotsFile.open(file.c_str(),std::ios::out);
        if(slotsFile.fail())
        {
            this->uartErrors->dtError = true;
            slotsFile.close();
            return false;
        }
        else
        {
            this->uartErrors->dtError = false;
            slotsFile << this->dtUartFilename;
            slotsFile.close();
            return true;
        }
    }


    bool        BlackUART::open(uint openMode)
    {
        int flags = 0;

        if( (openMode & ReadOnly)   == ReadOnly     ){  flags |= O_RDONLY;  }
        if( (openMode & WriteOnly)  == WriteOnly    ){  flags |= O_WRONLY;  }
        if( (openMode & ReadWrite)  == ReadWrite    ){  flags |= O_RDWR;    }
        if( (openMode & Append)     == Append       ){  flags |= O_APPEND;  }
        if( (openMode & Truncate)   == Truncate     ){  flags |= O_TRUNC;   }
        if( (openMode & NonBlock)   == NonBlock     ){  flags |= O_NONBLOCK;}

        this->uartFD = ::open(this->uartPortPath.c_str(), flags | O_NOCTTY);


        if( this->uartFD < 0 )
        {
            this->uartErrors->openError = true;
            this->isOpenFlag            = false;
            return false;
        }



        this->uartErrors->openError     = false;
        this->isOpenFlag                = true;
        this->defaultUartProperties     = this->getProperties();

        if( this->isCurrentEqDefault )
        {
            this->currentUartProperties = this->defaultUartProperties;
            return true;
        }
        else
        {
            if( this->setProperties(this->constructorProperties , ApplyNow) )
            {
                this->currentUartProperties = this->constructorProperties;
            }
            else
            {
                this->currentUartProperties = this->defaultUartProperties;
            }
        }
        return true;
    }

    bool        BlackUART::close()
    {
        if( ::close(this->uartFD) < 0 )
        {
            this->uartErrors->closeError    = true;
            return false;
        }
        else
        {
            this->uartErrors->closeError    = false;
            this->isOpenFlag                = false;
            return true;
        }
    }



    bool        BlackUART::flush(direction whichDirection)
    {
        int isFlushed = -1;


        if( whichDirection == input )
        {
            this->uartErrors->directionError = false;
            isFlushed = tcflush(this->uartFD, TCIFLUSH);
        }
        else if( whichDirection == output )
        {
            this->uartErrors->directionError = false;
            isFlushed = tcflush(this->uartFD, TCOFLUSH);
        }
        else if( whichDirection == bothDirection )
        {
            this->uartErrors->directionError = false;
            isFlushed = tcflush(this->uartFD, TCIOFLUSH);
        }
        else
        {
            this->uartErrors->directionError = true;
        }


        if( isFlushed == 0 )
        {
            this->uartErrors->flushError = false;
            return true;
        }
        else
        {
            this->uartErrors->flushError = true;
            return false;
        }
    }



    bool        BlackUART::read(char *readBuffer, size_t size)
    {
        char tempReadBuffer[size];
        memset(&tempReadBuffer, 0, size);

        if(::read(this->uartFD, tempReadBuffer, sizeof(tempReadBuffer)) > 0)
        {
            memcpy(readBuffer, tempReadBuffer, sizeof(tempReadBuffer));
            this->uartErrors->readError = false;
            return true;
        }
        else
        {
            this->uartErrors->readError = true;
            return false;
        }
    }

    std::string BlackUART::read()
    {
        std::string tempReadBuffer;
        tempReadBuffer.resize(this->readBufferSize);

        int readSize = ::read(this->uartFD, &tempReadBuffer[0], tempReadBuffer.size() );
        if( readSize > 0)
        {
            this->uartErrors->readError = false;
            tempReadBuffer.resize(readSize);
            return tempReadBuffer;
        }
        else
        {
            this->uartErrors->readError = true;
            return UART_READ_FAILED;
        }
    }



    bool        BlackUART::write(char *writeBuffer, size_t size)
    {
        if(::write(this->uartFD, writeBuffer, size) > 0)
        {
            this->uartErrors->writeError = false;
            return true;
        }
        else
        {
            this->uartErrors->writeError = true;
            return false;
        }
    }

    bool        BlackUART::write(std::string writeBuffer)
    {
        if(::write(this->uartFD, writeBuffer.c_str(), writeBuffer.size() ) > 0)
        {
            this->uartErrors->writeError = false;
            return true;
        }
        else
        {
            this->uartErrors->writeError = true;
            return false;
        }
    }




    bool        BlackUART::transfer(char *writeBuffer, char *readBuffer, size_t size, uint32_t wait_us)
    {
        if(::write(this->uartFD, writeBuffer, size ) > 0)
        {
            this->uartErrors->writeError = false;
        }
        else
        {
            this->uartErrors->writeError = true;
            return false;
        }

        usleep(wait_us);


        char tempReadBuffer[ size ];
        memset(&tempReadBuffer, 0, size);

        if(::read(this->uartFD, tempReadBuffer, sizeof(tempReadBuffer)) > 0)
        {
            memcpy(readBuffer,tempReadBuffer,sizeof(tempReadBuffer));
            this->uartErrors->readError = false;
            return true;
        }
        else
        {
            this->uartErrors->readError = true;
            return false;
        }
    }

    std::string BlackUART::transfer(std::string writeBuffer, uint32_t wait_us)
    {
        if(::write(this->uartFD,writeBuffer.c_str(),writeBuffer.size() ) > 0)
        {
            this->uartErrors->writeError = false;
        }
        else
        {
            this->uartErrors->writeError = true;
            return UART_WRITE_FAILED;
        }

        usleep(wait_us);

        std::string tempReadBuffer;
        tempReadBuffer.resize(this->readBufferSize);

        int readSize = ::read(this->uartFD, &tempReadBuffer[0], tempReadBuffer.size() );
        if( readSize > 0 )
        {
            this->uartErrors->readError = false;
            tempReadBuffer.resize(readSize);
            return tempReadBuffer;
        }
        else
        {
            this->uartErrors->readError = true;
            return UART_READ_FAILED;
        }



    }



    uint32_t    BlackUART::getReadBufferSize()
    {
        return this->readBufferSize;
    }

    void        BlackUART::setReadBufferSize(uint32_t newBufferSize)
    {
        this->readBufferSize = newBufferSize;
    }



    std::string BlackUART::getPortName()
    {
        return this->uartPortPath;
    }



    baudRate    BlackUART::getBaudRate(direction whichDirection)
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->baudRateError = true;
            this->uartErrors->openError     = true;
            return Baud0;
        }

        termios tempProperties;
        if( tcgetattr(this->uartFD, &tempProperties) != 0 )
        {
            this->uartErrors->baudRateError = true;
            return Baud0;
        }
        else
        {
            this->uartErrors->baudRateError = false;
        }



        if( whichDirection == input )
        {
            this->currentUartProperties.uartBaudIn = static_cast<baudRate>(cfgetispeed(&tempProperties));
            return this->currentUartProperties.uartBaudIn;
        }

        if( whichDirection == output )
        {
            this->currentUartProperties.uartBaudOut = static_cast<baudRate>(cfgetospeed(&tempProperties));
            return this->currentUartProperties.uartBaudOut;
        }
        else
        {
            return Baud0;
        }
    }

    bool        BlackUART::setBaudRate(baudRate newBaud, direction whichDirection, uartApplyMode applyMode )
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->baudRateError = true;
            this->uartErrors->openError     = true;
            return false;
        }

        termios tempProperties;
        tcgetattr(this->uartFD, &tempProperties);

        if( whichDirection == input)
        {
            cfsetispeed(&tempProperties, newBaud);
        }
        else
        if( whichDirection == output )
        {
            cfsetospeed(&tempProperties, newBaud);
        }
        else
        if( whichDirection == bothDirection )
        {
            cfsetispeed(&tempProperties, newBaud);
            cfsetospeed(&tempProperties, newBaud);
        }
        else
        {
            this->uartErrors->directionError    = true;
            this->uartErrors->baudRateError     = true;
            return false;
        }

        this->uartErrors->directionError        = false;

        if( tcsetattr(this->uartFD, applyMode, &tempProperties) == 0 )
        {
            if( whichDirection == input)
            {
                this->currentUartProperties.uartBaudIn = newBaud;
            }
            else
            if( whichDirection == output )
            {
                this->currentUartProperties.uartBaudOut = newBaud;
            }
            else
            if( whichDirection == bothDirection )
            {
                this->currentUartProperties.uartBaudIn = newBaud;
                this->currentUartProperties.uartBaudOut = newBaud;
            }

            this->uartErrors->baudRateError = false;
            return true;
        }
        else
        {
            this->uartErrors->baudRateError = true;
            return false;
        }
    }



    parity      BlackUART::getParity()
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->parityError   = true;
            this->uartErrors->openError     = true;
            return ParityDefault;
        }

        termios tempProperties;
        if( tcgetattr(this->uartFD, &tempProperties) != 0 )
        {
            this->uartErrors->parityError = true;
            return ParityDefault;
        }
        else
        {
            this->uartErrors->parityError = false;
        }

        tcflag_t controlFlag = tempProperties.c_cflag;

        if( (controlFlag & PARENB)      == PARENB )
        {
            if( (controlFlag & PARODD)  == PARODD )
            {
                this->currentUartProperties.uartParity = ParityOdd;
                return ParityOdd;
            }
            else
            {
                this->currentUartProperties.uartParity = ParityEven;
                return ParityEven;
            }
        }
        else
        {
            this->currentUartProperties.uartParity = ParityNo;
            return ParityNo;
        }
    }

    bool        BlackUART::setParity(parity newParity, uartApplyMode applyMode )
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->parityError   = true;
            this->uartErrors->openError     = true;
            return false;
        }

        termios tempProperties;
        tcgetattr(this->uartFD, &tempProperties);

        if( (newParity == ParityOdd) or (newParity == ParityEven) )
        {
            tempProperties.c_cflag |= PARENB;

            if( newParity == ParityOdd )
            {
                tempProperties.c_cflag |= PARODD;
            }
            else
            {
                tempProperties.c_cflag &= ~(PARODD);
            }
        }
        else
        {
            tempProperties.c_cflag &= ~(PARENB);
        }



        if( tcsetattr(this->uartFD, applyMode, &tempProperties) == 0 )
        {
            this->uartErrors->parityError = false;
            this->currentUartProperties.uartParity = (newParity == ParityDefault) ? ParityNo : newParity;;
            return true;
        }
        else
        {
            this->uartErrors->parityError = true;
            return false;
        }
    }



    stopBits    BlackUART::getStopBits()
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->stopBitsError = true;
            this->uartErrors->openError     = true;
            return StopDefault;
        }

        termios tempProperties;
        if( tcgetattr(this->uartFD, &tempProperties) != 0 )
        {
            this->uartErrors->stopBitsError = true;
            return StopDefault;
        }
        else
        {
            this->uartErrors->stopBitsError = false;
        }


        if( (tempProperties.c_cflag & CSTOPB) == CSTOPB )
        {
            this->currentUartProperties.uartStopBits = StopTwo;
            return StopTwo;
        }
        else
        {
            this->currentUartProperties.uartStopBits = StopOne;
            return StopOne;
        }

    }

    bool        BlackUART::setStopBits(stopBits newStopBits, uartApplyMode applyMode )
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->stopBitsError = true;
            this->uartErrors->openError     = true;
            return false;
        }

        termios tempProperties;
        tcgetattr(this->uartFD, &tempProperties);

        if( newStopBits == StopTwo)
        {
            tempProperties.c_cflag |= CSTOPB;
        }
        else
        {
            tempProperties.c_cflag &= ~(CSTOPB);
        }


        if( tcsetattr(this->uartFD, applyMode, &tempProperties) == 0 )
        {
            this->uartErrors->stopBitsError = false;
            this->currentUartProperties.uartStopBits = (newStopBits == StopDefault) ? StopOne : newStopBits;
            return true;
        }
        else
        {
            this->uartErrors->stopBitsError = true;
            return false;
        }
    }



    characterSize BlackUART::getCharacterSize()
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->charSizeError = true;
            this->uartErrors->openError     = true;
            return CharDefault;
        }

        termios tempProperties;
        if( tcgetattr(this->uartFD, &tempProperties) != 0 )
        {
            this->uartErrors->charSizeError = true;
            return CharDefault;
        }
        else
        {
            this->uartErrors->charSizeError = false;
        }

        tcflag_t controlFlag = tempProperties.c_cflag;

        if( (controlFlag & CS8) == CS8  ){ this->currentUartProperties.uartCharSize = Char8; return Char8; }
        if( (controlFlag & CS6) == CS6  ){ this->currentUartProperties.uartCharSize = Char6; return Char6; }
        if( (controlFlag & CS7) == CS7  ){ this->currentUartProperties.uartCharSize = Char7; return Char7; }
        else                             { this->currentUartProperties.uartCharSize = Char5; return Char5; }
    }

    bool        BlackUART::setCharacterSize(characterSize newCharacterSize, uartApplyMode applyMode )
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->charSizeError = true;
            this->uartErrors->openError     = true;
            return false;
        }

        termios tempProperties;
        tcgetattr(this->uartFD, &tempProperties);

        switch (newCharacterSize)
        {
            case Char5:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS5;
                break;
            }
            case Char6:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS6;
                break;
            }
            case Char7:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS7;
                break;
            }
            case Char8:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS8;
                break;
            }
            case CharDefault:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS8;
                break;
            }
            default:
                break;
        }



        if( tcsetattr(this->uartFD, applyMode, &tempProperties) == 0 )
        {
            this->currentUartProperties.uartCharSize = (newCharacterSize == CharDefault) ? Char8 : newCharacterSize;
            this->uartErrors->charSizeError = false;
            return true;
        }
        else
        {
            this->uartErrors->charSizeError = true;
            return false;
        }

    }




    BlackUartProperties BlackUART::getProperties()
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->baudRateError = true;
            this->uartErrors->charSizeError = true;
            this->uartErrors->parityError   = true;
            this->uartErrors->stopBitsError = true;
            this->uartErrors->openError     = true;
            return BlackUartProperties();
        }

        termios tempProperties;
        if( tcgetattr(this->uartFD, &tempProperties) != 0 )
        {
            this->uartErrors->baudRateError = true;
            this->uartErrors->charSizeError = true;
            this->uartErrors->parityError   = true;
            this->uartErrors->stopBitsError = true;
        }
        else
        {
            this->uartErrors->baudRateError = false;
            this->uartErrors->charSizeError = false;
            this->uartErrors->parityError   = false;
            this->uartErrors->stopBitsError = false;
        }

        tcflag_t controlFlag = tempProperties.c_cflag;

        baudRate        currentBaudIn   = static_cast<baudRate>(cfgetispeed(&tempProperties));
        baudRate        currentBaudOut  = static_cast<baudRate>(cfgetospeed(&tempProperties));
        stopBits        currentStopBits = ((controlFlag & CSTOPB)==CSTOPB) ? StopTwo : StopOne;
        parity          currentParity   = ((controlFlag & PARENB)==PARENB) ? ( ((controlFlag & PARODD)==PARODD) ? ParityOdd : ParityEven ) : ParityNo;
        characterSize   currentCharSize;

        if     ( (controlFlag & CS8) == CS8  ){ currentCharSize = Char8; }
        else if( (controlFlag & CS6) == CS6  ){ currentCharSize = Char6; }
        else if( (controlFlag & CS7) == CS7  ){ currentCharSize = Char7; }
        else                                  { currentCharSize = Char5; }

        this->currentUartProperties = BlackUartProperties(currentBaudIn, currentBaudOut, currentParity, currentStopBits, currentCharSize);
        return this->currentUartProperties;
    }

    bool        BlackUART::setProperties(BlackUartProperties &props, uartApplyMode applyMode)
    {
        if( !(this->isOpenFlag) )
        {
            this->uartErrors->baudRateError = true;
            this->uartErrors->charSizeError = true;
            this->uartErrors->parityError   = true;
            this->uartErrors->stopBitsError = true;
            this->uartErrors->openError     = true;
            return false;
        }

        termios tempProperties;
        tcgetattr(this->uartFD, &tempProperties);

        cfsetispeed(&tempProperties, props.uartBaudIn);
        cfsetospeed(&tempProperties, props.uartBaudOut);


        if( (props.uartParity == ParityOdd) or (props.uartParity == ParityEven) )
        {
            tempProperties.c_cflag |= PARENB;

            if( props.uartParity == ParityOdd )
            {
                tempProperties.c_cflag |= PARODD;
            }
            else
            {
                tempProperties.c_cflag &= ~(PARODD);
            }
        }
        else
        {
            tempProperties.c_cflag &= ~(PARENB);
        }


        if( props.uartStopBits == StopTwo)
        {
            tempProperties.c_cflag |= CSTOPB;
        }
        else
        {
            tempProperties.c_cflag &= ~(CSTOPB);
        }


        switch (props.uartCharSize)
        {
            case Char5:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS5;
                break;
            }
            case Char6:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS6;
                break;
            }
            case Char7:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS7;
                break;
            }
            case Char8:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS8;
                break;
            }
            case CharDefault:
            {
                tempProperties.c_cflag &= ~(CSIZE);
                tempProperties.c_cflag |= CS8;
                break;
            }
            default:
                break;
        }


        tempProperties.c_cflag |= CLOCAL;
        tempProperties.c_cflag |= CREAD;

        tempProperties.c_iflag |= ICRNL;
        tempProperties.c_oflag = 0;
        tempProperties.c_lflag = 0;

        tempProperties.c_cc[VTIME] = 0;
        tempProperties.c_cc[VMIN]  = 1;



        if( tcsetattr(this->uartFD, applyMode, &tempProperties) == 0 )
        {
            this->uartErrors->baudRateError = false;
            this->uartErrors->charSizeError = false;
            this->uartErrors->parityError   = false;
            this->uartErrors->stopBitsError = false;

            this->currentUartProperties.uartBaudIn   = props.uartBaudIn;
            this->currentUartProperties.uartBaudOut  = props.uartBaudOut;
            this->currentUartProperties.uartCharSize = (props.uartCharSize == CharDefault)   ? Char8    : props.uartCharSize;
            this->currentUartProperties.uartParity   = (props.uartParity   == ParityDefault) ? ParityNo : props.uartParity;
            this->currentUartProperties.uartStopBits = (props.uartStopBits == StopDefault)   ? StopOne  : props.uartStopBits;
            return true;
        }
        else
        {
            this->uartErrors->baudRateError = true;
            this->uartErrors->charSizeError = true;
            this->uartErrors->parityError   = true;
            this->uartErrors->stopBitsError = true;
            return false;
        }


    }





    bool        BlackUART::isOpen()
    {
        return this->isOpenFlag;
    }

    bool        BlackUART::isClose()
    {
        return !(this->isOpenFlag);
    }




    bool        BlackUART::fail()
    {
        return (this->uartErrors->dtError or
                this->uartErrors->readError or
                this->uartErrors->writeError or
                this->uartErrors->flushError or
                this->uartErrors->openError or
                this->uartErrors->closeError or
                this->uartErrors->directionError or
                this->uartErrors->baudRateError or
                this->uartErrors->charSizeError or
                this->uartErrors->stopBitsError or
                this->uartErrors->parityError
                );
    }

    bool        BlackUART::fail(BlackUART::flags f)
    {
        if(f==dtErr)            { return this->uartErrors->dtError;         }
        if(f==readErr)          { return this->uartErrors->readError;       }
        if(f==writeErr)         { return this->uartErrors->writeError;      }
        if(f==flushErr)         { return this->uartErrors->flushError;      }
        if(f==closeErr)         { return this->uartErrors->closeError;      }
        if(f==openErr)          { return this->uartErrors->openError;       }
        if(f==directionErr)     { return this->uartErrors->directionError;  }
        if(f==parityErr)        { return this->uartErrors->parityError;     }
        if(f==baudRateErr)      { return this->uartErrors->baudRateError;   }
        if(f==charSizeErr)      { return this->uartErrors->charSizeError;   }
        if(f==stopBitsErr)      { return this->uartErrors->stopBitsError;   }

        return true;
    }




    BlackUART&      BlackUART::operator<<(std::string &writeFromThis)
    {
        if(::write(this->uartFD,writeFromThis.c_str(),writeFromThis.size() ) > 0)
        {
            this->uartErrors->writeError = false;
        }
        else
        {
            this->uartErrors->writeError = true;
        }

        return *this;
    }

    BlackUART&      BlackUART::operator>>(std::string &readToThis)
    {
        std::string tempReadBuffer;
        tempReadBuffer.resize(this->readBufferSize);

        int readSize = ::read(this->uartFD, &tempReadBuffer[0], tempReadBuffer.size() );
        if( readSize > 0)
        {
            this->uartErrors->readError = false;
            tempReadBuffer.resize(readSize);
            readToThis = tempReadBuffer;
        }
        else
        {
            this->uartErrors->readError = true;
            readToThis = UART_READ_FAILED;
        }

        return *this;
    }


} /* namespace BlackLib */
