/*
 * BlackMutex.cpp
 *
 *  Created on: 10 Eki 2014
 *      Author: yigityuce
 */

#include "BlackMutex.h"

namespace BlackLib
{

    BlackMutex::BlackMutex(BlackMutex::mutexMode mm)
    {
        this->lockCount = 0;
        this->mode      = mm;

        pthread_mutexattr_t tempMutexAttr;
        pthread_mutexattr_init(&tempMutexAttr);

        if( mm == BlackMutex::Recursive )
        {
            pthread_mutexattr_settype(&tempMutexAttr, PTHREAD_MUTEX_RECURSIVE);
        }
        else
        {
            pthread_mutexattr_settype(&tempMutexAttr, PTHREAD_MUTEX_ERRORCHECK);
        }

        pthread_mutexattr_setpshared(&tempMutexAttr, PTHREAD_PROCESS_PRIVATE);

        pthread_mutex_init( &(this->mutex), &tempMutexAttr);
        pthread_mutexattr_destroy(&tempMutexAttr);
    }


    BlackMutex::~BlackMutex()
    {
        pthread_mutex_destroy( &(this->mutex) );
    }

    bool BlackMutex::lock()
    {
        bool isSuccess = ( pthread_mutex_lock( &(this->mutex) ) == 0);

        if( isSuccess ){ ++(this->lockCount); }

        return isSuccess;
    }

    bool BlackMutex::timedLock(unsigned int sec)
    {
        timespec until;
        until.tv_sec  = sec;
        until.tv_nsec = 0;

        bool isSuccess = ( pthread_mutex_timedlock( &(this->mutex), &until) == 0);

        if( isSuccess ){ ++(this->lockCount); }

        return isSuccess;
    }

    bool BlackMutex::tryLock()
    {
        bool isSuccess = ( pthread_mutex_trylock( &(this->mutex) ) == 0);

        if( isSuccess ){ ++(this->lockCount); }

        return isSuccess;
    }

    bool BlackMutex::unlock()
    {
        bool isSuccess = ( pthread_mutex_unlock( &(this->mutex) ) == 0);

        if( isSuccess ){ --(this->lockCount); }

        return isSuccess;
    }


    bool BlackMutex::isLocked()
    {
        return (this->lockCount > 0);
    }

    bool BlackMutex::isRecursive()
    {
        return (this->mode == BlackMutex::Recursive );
    }

    unsigned int BlackMutex::getLockedCount()
    {
        return this->lockCount;
    }


} /* namespace BlackLib */
