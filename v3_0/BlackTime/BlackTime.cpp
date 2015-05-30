/*
 * BlackTime.cpp
 *
 *  Created on: 3 May 2015
 *      Author: yigityuce
 */

#include "BlackTime.h"

namespace BlackLib
{

    BlackTime::BlackTime()
    {
        this->hour   = 0;
        this->minute = 0;
        this->second = 0;

    }

    BlackTime::BlackTime(int h,int m,int s)
    {
        if( BlackTime::isValid(h,m,s) )
        {
            this->hour   = h;
            this->minute = m;
            this->second = s;
        }
        else
        {
            this->hour   = 0;
            this->minute = 0;
            this->second = 0;
        }
    }


    BlackTime::~BlackTime()
    {

    }

    bool BlackTime::isValid(int h,int m,int s)
    {
        return ( h >= 0 and h <= 23 and m >=0 and m <= 59 and s >=0 and s <= 59 );
    }


    BlackTime BlackTime::getCurrentTime()
    {
        time_t t = time(0);
        struct tm * now = localtime( &t );

        return BlackTime(now->tm_hour,now->tm_min,now->tm_sec);
    }


    int BlackTime::getHour()
    {
        return this->hour;
    }


    int BlackTime::getMinute()
    {
        return this->minute;
    }


    int BlackTime::getSecond()
    {
        return this->second;
    }


    bool BlackTime::setTime(int h,int m,int s)
    {
        if( BlackTime::isValid(h,m,s) )
        {
            this->hour   = h;
            this->minute = m;
            this->second = s;

            return true;
        }

        return false;
    }

    void BlackTime::start()
    {
        ::gettimeofday(&(this->measureStartTime),NULL);
    }

    BlackTimeElapsed BlackTime::restart()
    {
        BlackTimeElapsed retTemp = this->elapsed();
        this->start();
        return retTemp;
    }

    BlackTimeElapsed BlackTime::elapsed()
    {
        timeval now;
        ::gettimeofday(&now,NULL);

        BlackTimeElapsed temp;

        unsigned long int microDiff = (now.tv_sec*1000000 + now.tv_usec) - (this->measureStartTime.tv_sec*1000000 + this->measureStartTime.tv_usec);
        temp.microSecond            = microDiff%1000;

        unsigned long int miliDiff  = (microDiff - temp.microSecond) / 1000;
        temp.miliSecond             = miliDiff%1000;

        unsigned long int secDiff   = ((miliDiff - temp.miliSecond) / 1000);
        temp.second                 = secDiff%60;

        unsigned long int minDiff   = (secDiff - temp.second)/60;
        temp.minute                 = minDiff%60;

        unsigned long int hour      = (minDiff - temp.minute)/60;
        temp.hour                   = static_cast<unsigned int>(hour);

        return temp;
    }





    BlackTime& BlackTime::addHour(int h)
    {
        this->hour += h;
        this->hour = (((this->hour)%24)+24)%24;

        return *this;
    }


    BlackTime& BlackTime::addMinute(int m)
    {
        int totalMin    = (this->hour * 60) + this->minute;
        int newTotalMin = totalMin + m;
        newTotalMin     = (((newTotalMin)%1440)+1440)%1440;
        this->hour      = static_cast<int>(newTotalMin/60);
        this->minute    = newTotalMin-(this->hour*60);

        return *this;
    }


    BlackTime& BlackTime::addSecond(int s)
    {
        long int newTotalSec = BlackTime::fromTimeToSecond(*this) + static_cast<long int>(s);
        newTotalSec          = (((newTotalSec)%86400)+86400)%86400;
        this->hour           = static_cast<int>(newTotalSec/3600);
        newTotalSec         -= this->hour*3600;
        this->minute         = static_cast<int>(newTotalSec/60);
        newTotalSec         -= this->minute*60;
        this->second         = static_cast<int>(newTotalSec);

        return *this;
    }



    BlackTime BlackTime::fromSecondToTime(long int sec)
    {
        long int temp = (((sec)%86400)+86400)%86400;

        int h   = static_cast<int>(temp/3600);
        temp   -= h*3600;
        int m   = static_cast<int>(temp/60);
        temp   -= m*60;
        int s   = static_cast<int>(temp);

        return BlackTime(h,m,s);
    }


    long int  BlackTime::fromTimeToSecond(BlackTime t)
    {
        return static_cast<long int>((t.getHour() * 60 * 60) + (t.getMinute() * 60) + t.getSecond());
    }



    std::string BlackTime::toString(std::string format)
    {
        std::string retVal  = "";
        int editedHour      = this->hour;

        if( format.find("ap")!= std::string::npos or format.find("AP")!= std::string::npos )
        {
            if( editedHour == 0 )       { editedHour = 12; }
            else if( editedHour > 12 )  { editedHour = editedHour%12; }
        }

        size_t i = 0 ;
        while( i<format.size() )
        {
            if( format[i] == '\'' )
            {
                size_t endQuoteSignPos = format.find_first_of('\'',i+1);
                if( endQuoteSignPos == std::string::npos )
                {
                    retVal = retVal + format.substr(i+1,format.size()-i);
                    return retVal;
                }
                else
                {
                    retVal = retVal + format.substr(i+1,endQuoteSignPos-i-1);
                    i = endQuoteSignPos+1;
                }
            }
            else
            if( format[i] == 'h' or format[i] == 'H' )
            {
                std::string ho = std::to_string(editedHour);
                if( format[i+1] == 'h' or format[i+1] == 'H' )
                {
                    retVal = retVal + ( ho.size()==1 ? "0"+ho : ho );
                    i +=2 ;
                }
                else
                {
                    retVal = retVal + ho;
                    i++;
                }
            }
            else
            if( format[i] == 'm' or format[i] == 'M' )
            {
                std::string mi = std::to_string(this->minute);
                if( format[i+1] == 'm' or format[i+1] == 'M' )
                {
                    retVal = retVal + ( mi.size()==1 ? "0"+mi : mi );
                    i +=2 ;
                }
                else
                {
                    retVal = retVal + mi;
                    i++;
                }
            }
            else
            if( format[i] == 's' or format[i] == 'S' )
            {
                std::string se = std::to_string(this->second);
                if( format[i+1] == 's' or format[i+1] == 'S' )
                {
                    retVal = retVal + ( se.size()==1 ? "0"+se : se );
                    i +=2 ;
                }
                else
                {
                    retVal = retVal + se;
                    i++;
                }
            }
            else
            if( format[i] == ':' or format[i] == '/' or format[i] == '.' or format[i] == '-' or format[i] == ' ')
            {
                retVal = retVal + format[i];
                i++;
            }
            else
            if( format[i] == 'a' or format[i] == 'A')
            {
                if( format[i+1] == 'p' or format[i+1] == 'P' )
                {
                    retVal = retVal + ( this->hour >= 12 ? "pm" : "am" );
                    i +=2 ;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                i++;
            }

        }

        return retVal;
    }







    BlackTime BlackTime::operator- (BlackTime t)
    {
        long int totalSec1  = BlackTime::fromTimeToSecond(*this);
        long int totalSec2  = BlackTime::fromTimeToSecond(t);

        return BlackTime::fromSecondToTime(totalSec1-totalSec2);
    }

    BlackTime BlackTime::operator+ (BlackTime t)
    {
        long int totalSec1  = BlackTime::fromTimeToSecond(*this);
        long int totalSec2  = BlackTime::fromTimeToSecond(t);

        return BlackTime::fromSecondToTime(totalSec1+totalSec2);
    }

    BlackTime& BlackTime::operator= (BlackTime t)
    {
        this->hour   = t.getHour();
        this->minute = t.getMinute();
        this->second = t.getMinute();

        return *this;
    }


    bool BlackTime::operator==(BlackTime t)
    {
        return ( this->hour   == t.getHour()   and
                 this->minute == t.getMinute() and
                 this->second == t.getSecond() );
    }

    bool BlackTime::operator!=(BlackTime t)
    {
        return ( this->hour   != t.getHour()   or
                 this->minute != t.getMinute() or
                 this->second != t.getSecond() );
    }

    bool BlackTime::operator<(BlackTime t)
    {
        return ( BlackTime::fromTimeToSecond(*this) < BlackTime::fromTimeToSecond(t) );
    }

    bool BlackTime::operator>(BlackTime t)
    {
        return ( BlackTime::fromTimeToSecond(*this) > BlackTime::fromTimeToSecond(t) );
    }

    bool BlackTime::operator<=(BlackTime t)
    {
        return ( BlackTime::fromTimeToSecond(*this) <= BlackTime::fromTimeToSecond(t) );
    }

    bool BlackTime::operator>=(BlackTime t)
    {
        return ( BlackTime::fromTimeToSecond(*this) >= BlackTime::fromTimeToSecond(t) );
    }




} /* namespace BlackLib */
