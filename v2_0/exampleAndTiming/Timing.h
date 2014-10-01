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


#ifndef TIMING_H_
#define TIMING_H_

#include <sys/time.h>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>


struct elapsedTime
{
    elapsedTime()
    {
        microSecond = 0;
        miliSecond  = 0;
        second      = 0;
    }

    unsigned int microSecond;
    unsigned int miliSecond;
    unsigned int second;
};



class Timing
{
    private:
        std::map<std::string, long int> timeMap;
        template <typename T>
        std::string tostr(const T& t)
        {
            std::ostringstream os;
            os << t;
            return os.str();
        }

    public:
                    Timing(){};
        virtual     ~Timing(){};

        void        startMeasure(std::string ID);
        void        endMeasure(std::string ID);
        elapsedTime getMeasure(std::string ID);

        std::string getAllMeasureTable();

        bool        saveToFile(std::string filename);
};

#endif /* TIMING_H_ */

