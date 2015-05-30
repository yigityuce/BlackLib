/*
 * BlackThread.cpp
 *
 *  Created on: 6 Eki 2014
 *      Author: yigityuce
 */

#include "BlackThread.h"

namespace BlackLib
{

    BlackThread::BlackThread()
    {
        this->nativeThread      = 0;
        this->threadState       = BlackThread::Stateless;
        this->threadPriority    = BlackThread::PriorityDEFAULT;
        this->isCreated         = false;

        this->calculatePriorities();
    }

    BlackThread::~BlackThread()
    {
    }

    void BlackThread::calculatePriorities()
    {
        int maxPriority = sched_get_priority_max( SCHED_RR );   // max: 99
        int minPriority = sched_get_priority_min( SCHED_RR );   // min: 1

        maxPriority     = maxPriority - 18;                     // max: 81
        int midPriority = (int)((maxPriority + minPriority)/2); // mid: 41

        this->priorities.resize(5,0);

        this->priorities[BlackThread::PriorityLOWEST ] = minPriority;                           // lowest : 1
        this->priorities[BlackThread::PriorityLOW    ] = (int)((minPriority + midPriority)/2);  // low    : 21
        this->priorities[BlackThread::PriorityNORMAL ] = midPriority;                           // normal : 41
        this->priorities[BlackThread::PriorityHIGH   ] = (int)((midPriority + maxPriority)/2);  // high   : 61
        this->priorities[BlackThread::PriorityHIGHEST] = maxPriority;                           // highest: 81
    }




    bool BlackThread::setAttribute(pthread_attr_t *attr, BlackThread::priority tp)
    {
        bool isSet = false;

        #ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
            if( !( (this->threadState == BlackThread::Running)or(this->threadState == BlackThread::Paused) ) )
            {
                BlackThread::priority tempThreadPriority  = tp;

                if( tempThreadPriority == BlackThread::PriorityDEFAULT )
                {
                    isSet = ( (pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED) == 0) and
                              (pthread_attr_setschedpolicy( attr, SCHED_OTHER)            == 0)
                            );
                }
                else
                if( tempThreadPriority == BlackThread::PriorityIDLE )
                {
                    #ifdef SCHED_IDLE
                        isSet = ( (pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED) == 0) and
                                  (pthread_attr_setschedpolicy( attr, SCHED_IDLE)             == 0)
                                );
                    #endif

                    #ifndef SCHED_IDLE
                        sched_param priority;
                        priority.__sched_priority = this->threadClass->priorities[BlackThread::PriorityLOWEST];

                        isSet = ( (pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED) == 0) and
                                  (pthread_attr_setschedpolicy( attr, SCHED_RR              ) == 0) and
                                  (pthread_attr_setschedparam(  attr, &priority             ) == 0)
                                );

                        if( isSet ){ tempThreadPriority = BlackThread::PriorityLOWEST; }
                    #endif
                }
                else
                {
                    sched_param priority;
                    priority.__sched_priority = this->priorities[tempThreadPriority];

                    isSet = ( (pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED) == 0) and
                              (pthread_attr_setschedpolicy( attr, SCHED_RR              ) == 0) and
                              (pthread_attr_setschedparam(  attr, &priority             ) == 0)
                            );
                }

                if( isSet ){ this->threadPriority = tempThreadPriority; }
            }
        #endif

        return isSet;
    }

    BlackThread::priority BlackThread::setPriority(BlackThread::priority tp)
    {
        #ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
            if( (this->threadState == BlackThread::Running) or (this->threadState == BlackThread::Paused))
            {
                int         policy;
                sched_param priority;

                if( tp == BlackThread::PriorityDEFAULT )
                {
                    policy                          = SCHED_OTHER;
                    priority.__sched_priority       = sched_get_priority_min(policy);
                }
                else
                if( tp == BlackThread::PriorityIDLE )
                {
                    #ifdef SCHED_IDLE
                        policy                      = SCHED_IDLE;
                        priority.__sched_priority   = sched_get_priority_min(policy);
                    #endif

                    #ifndef SCHED_IDLE
                        policy                      = SCHED_RR;
                        priority.__sched_priority   = sched_get_priority_min(policy);
                    #endif
                }
                else
                {
                    policy                          = SCHED_RR;
                    priority.__sched_priority       = this->priorities[tp];
                }

                if( pthread_setschedparam(this->nativeThread, policy, &priority) == 0 )
                {
                    this->threadPriority            = tp;
                }
            }
            else
            {
                this->threadPriority                = tp;
            }
        #endif


        return this->threadPriority;
    }

    BlackThread::priority BlackThread::getPriority()
    {
        if( (this->threadState == BlackThread::Running) or (this->threadState == BlackThread::Paused))
        {
            #ifdef _POSIX_THREAD_PRIORITY_SCHEDULING

                BlackThread::priority tempReturn = BlackThread::PriorityDEFAULT;
                int         policy;
                sched_param priority;

                pthread_getschedparam( this->nativeThread, &policy, &priority);

                switch(policy)
                {
                    case SCHED_OTHER:
                    {
                        tempReturn = BlackThread::PriorityDEFAULT;
                        break;
                    }

                    #ifdef SCHED_IDLE
                        case SCHED_IDLE:
                        {
                            tempReturn = BlackThread::PriorityIDLE;
                            break;
                        }
                    #endif

                    case SCHED_RR:
                    {
                        if( priority.__sched_priority <= this->priorities[BlackThread::PriorityLOWEST] )
                        {
                            tempReturn = BlackThread::PriorityLOWEST;
                        }
                        else
                        if( priority.__sched_priority <= this->priorities[BlackThread::PriorityLOW] )
                        {
                            tempReturn = BlackThread::PriorityLOW;
                        }
                        else
                        if( priority.__sched_priority <= this->priorities[BlackThread::PriorityNORMAL] )
                        {
                            tempReturn = BlackThread::PriorityNORMAL;
                        }
                        else
                        if( priority.__sched_priority <= this->priorities[BlackThread::PriorityHIGH] )
                        {
                            tempReturn = BlackThread::PriorityHIGH;
                        }
                        else
                        {
                            tempReturn = BlackThread::PriorityHIGHEST;
                        }
                        break;
                    }
                };

                this->threadPriority = tempReturn;
            #endif
        }


        return this->threadPriority;
    }





    void BlackThread::run()
    {
        if( (this->threadState == BlackThread::Stateless) or (this->threadState == BlackThread::Stopped))
        {
            pthread_attr_t      threadConstructorAttrs;
            pthread_attr_init(&(threadConstructorAttrs));

            this->setAttribute(&(threadConstructorAttrs), this->threadPriority);


            this->isCreated = (pthread_create( &(this->nativeThread),
                                               &(threadConstructorAttrs),
                                               &BlackThread::threadFunction,
                                               (void*)(this)
                                             ) == 0
                              );

            if(this->isCreated)
            {
                this->threadState = BlackThread::Running;
            }
        }

    }

    void* BlackThread::threadFunction(void *thread)
    {
        pthread_cleanup_push(&BlackThread::cleanUp, thread );

        ((BlackLib::BlackThread*)thread)->onStartHandler();

        pthread_cleanup_pop(1);
        return NULL;
    }

    void BlackThread::stop()
    {
        pthread_exit(NULL);
    }

    void BlackThread::pause()
    {
        if(this->threadState == BlackThread::Running)
        {
            this->threadState = BlackThread::Paused;
            this->onPauseHandler();

            this->threadState = BlackThread::Running;
            this->onResumeHandler();
        }
    }



    void BlackThread::onStopHandler()  {}
    void BlackThread::onPauseHandler() {}
    void BlackThread::onResumeHandler(){}


    void BlackThread::waitUntilFinish()
    {
        if( (this->threadState == BlackThread::Running) or (this->threadState == BlackThread::Paused))
        {
            pthread_join(this->nativeThread,NULL);
        }
    }

    void  BlackThread::cleanUp(void *thread)
    {
        ((BlackLib::BlackThread*)thread)->onStopHandler();
        ((BlackLib::BlackThread*)thread)->threadState  = BlackThread::Stopped;
    }



    const pthread_t BlackThread::getThreadId()
    {
        return pthread_self();
    }


    void BlackThread::sleep(unsigned int sec)
    {
        ::sleep(sec);
    }

    void BlackThread::msleep(unsigned int msec)
    {
        ::usleep( msec*1000 );
    }

    void BlackThread::usleep(unsigned int usec)
    {
        ::usleep(usec);
    }

    void BlackThread::yield()
    {
        ::sched_yield();
    }


    bool BlackThread::isRunning()
    {
        return ( (this->threadState == BlackThread::Running) or
                 (this->threadState == BlackThread::Paused)
               );
    }

    bool BlackThread::isFinished()
    {
        return ( this->threadState == BlackThread::Stopped );
    }




















} /* namespace BlackLib */
