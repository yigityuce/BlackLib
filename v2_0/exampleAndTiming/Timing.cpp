 /*

 ####################################################################################
 #  BlackLib Library controls Beaglebone Black's inputs and outputs.                #
 #  Copyright (C) 2013-2014 by Yigit YUCE                                           #
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

#include "Timing.h"

void        Timing::startMeasure(std::string ID)
{
    timeval startTm;
    gettimeofday(&startTm,NULL);
    this->timeMap[ID] = (long int)startTm.tv_usec;
}

void        Timing::endMeasure(std::string ID)
{
    timeval stopTm;
    gettimeofday(&stopTm,NULL);
    this->timeMap[ID] = (long int)stopTm.tv_usec - this->timeMap[ID];
}

elapsedTime Timing::getMeasure(std::string ID)
{
    long int elapsed = this->timeMap[ID];
    elapsedTime elapsedStruct;


    if( elapsed < 1000 )                        // 0-999 us
    {
        elapsedStruct.microSecond = elapsed;
        elapsedStruct.miliSecond  = 0;
        elapsedStruct.second      = 0;
    }
    else
    if( elapsed < 1000*1000 )                   // 0.999 ms - 999 ms
    {
        elapsedStruct.microSecond = (elapsed % 1000);
        elapsedStruct.miliSecond  = (elapsed - (elapsed % 1000)) / 1000;
        elapsedStruct.second      = 0;
    }
    else                                        // 0.999 sec - infinite sec
    {
        elapsedStruct.microSecond = (elapsed % 1000);
        elapsedStruct.miliSecond  = (elapsed - (elapsed % 1000)) / 1000;
        elapsedStruct.second      = (elapsed - (elapsed % 1000000)) / 1000000;
    }

    return elapsedStruct;
}

std::string Timing::getAllMeasureTable()
{
    unsigned int maxStringSize = 5;
    std::string table;

    std::map<std::string, long int>::iterator iter = this->timeMap.begin();
    for( ; iter != this->timeMap.end() ; ++iter )
    {
        if( (*iter).first.size() > maxStringSize )
        {
            maxStringSize = (*iter).first.size();
        }
    }

    std::string lineString( maxStringSize+25 , '-');
    table += lineString;
    table += "\n| ";
    table += ( (maxStringSize>5) ? std::string(maxStringSize-5, ' ') + std::string("LABEL") : std::string("LABEL") );
    table += " |  SEC | mSEC | uSEC |\n";
    table += lineString;

    iter = this->timeMap.begin();
    for( ; iter != this->timeMap.end() ; ++iter )
    {
        std::string id = (*iter).first;
        elapsedTime et = this->getMeasure(id);
        std::string et_usec = this->tostr(et.microSecond);
        std::string et_msec = this->tostr(et.miliSecond);
        std::string et_sec  = this->tostr(et.second);
        table += "\n| ";
        table += ( (id.size() < maxStringSize) ? std::string(maxStringSize-id.size(), ' ') + id : id );
        table += " | ";
        table += ( (et_sec.size() < 4) ? std::string(4-et_sec.size(), ' ') + et_sec : et_sec );
        table += " | ";
        table += ( (et_msec.size() < 4) ? std::string(4-et_msec.size(), ' ') + et_msec : et_msec );
        table += " | ";
        table += ( (et_usec.size() < 4) ? std::string(4-et_usec.size(), ' ') + et_usec : et_usec );
        table += " |\n";
        table += lineString;
    }

    table += "\n";

    return table;

}

bool        Timing::saveToFile(std::string filename)
{
    std::ofstream out;
    out.open(filename.c_str(), std::ios::out );

    if(out.fail())
    {
        out.close();
        return false;
    }
    else
    {
        std::string writeThis = "\nFilename: ";
        writeThis += filename;
        writeThis += "\n\n";
        writeThis += this->getAllMeasureTable();

        out << writeThis;
        out.close();
        return true;
    }
}
