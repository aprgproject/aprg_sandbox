#include <cstdio>
#include <cstring>
#define DM_ERR_HIGH printf
#define DM_WRN_HIGH printf
#define DM_INF_HIGH printf
#define DM_DBG_LOW printf
#define MTPRINTF printf
#define MTSPRINTF printf
static unsigned int MY_SFN;
unsigned int tcomGetSfn()
{
    return MY_SFN;
}
unsigned int tcomSetSfn(unsigned int sfn)
{
    MY_SFN = sfn;
}



#include <SRLChangeDSPInd.h>
#include <SRLReconfCommitInd.h>
#include <DMeasTimerStack.hpp>
#include <string>

namespace DMeas {

TimerStack::TimerIndex TimerStack::timerTableNbrOfElements = 0 ;

inline int TimerStack::ARRAY_timers_empty(void)
{    return !TimerStack::timerTableNbrOfElements;
}

TimerStack::TimerIndex TimerStack::ARRAY_timers_insert(TimeCounter timeValue, TimerData timerData)
{
    int insertRetry = 0;
    int driveLoop   = 0;
    do // while( !(insertRetry < driveLoop) )
    {
        driveLoop++;

        if( TimerStack::timerTableNbrOfElements < TIMER_TABLE_MAX_NBR_OF_ELEMENTS )
        {
            TimerIndex timerIndex = 0;

            while( timerIndex < TIMER_TABLE_MAX_NBR_OF_ELEMENTS )
            {                if( timers[timerIndex].second.timerType == TimerType::FreeTimer )
                {
                    timers[timerIndex].first  = timeValue;
                    timers[timerIndex].second = timerData;
                    TimerStack::timerTableNbrOfElements++;

                    if( ARRAY_timers_high_mark < timerIndex )
                    {

                        ARRAY_timers_high_mark = timerIndex;

                        ARRAY_timers_max_index = (TIMER_TABLE_MAX_NBR_OF_ELEMENTS < (ARRAY_timers_high_mark+1)
                                                  ?
                                                      TIMER_TABLE_MAX_NBR_OF_ELEMENTS : (ARRAY_timers_high_mark+1));

                        DM_DBG_LOW(
                                    "ARRAY_timers_insert: high mark: %d max index: %d",
                                    ARRAY_timers_high_mark,
                                    ARRAY_timers_max_index);
                    }
                    return timerIndex;
                }

                timerIndex++;
            }
        }
        else
        {
            DM_WRN_HIGH( "Stack full with %d timers, cannot insert new timer", TimerStack::timerTableNbrOfElements );

            u32 freeElemCount = 0;
            for ( int ti = 0; ti < TIMER_TABLE_MAX_NBR_OF_ELEMENTS; ++ti )
            {
                if( TimerType::FreeTimer == timers[ti].second.timerType )
                {
                    ++freeElemCount;
                }
            }

            if ( 0 != freeElemCount )
            {
                TimerStack::timerTableNbrOfElements = TIMER_TABLE_MAX_NBR_OF_ELEMENTS - freeElemCount;

                DM_INF_HIGH( "Found %u free elements in stack, new count of timers %d", freeElemCount,
                             TimerStack::timerTableNbrOfElements );

                if ( 0 == insertRetry )
                {
                    DM_DBG_LOW( "ARRAY_timers_insert: RETRYING");
                    ++insertRetry;
                }
            }
        }
    } while( !(insertRetry < driveLoop) );

    DM_DBG_LOW( "ARRAY_timers_insert: FAILED");

    return ARRAY_timers_end();
}

TimerStack::TimerIndex TimerStack::ARRAY_timers_find( TimeCounter timeToSearch )
{
    for( TNumberOfItems timerIndex = 0;
         (timerIndex < ARRAY_timers_max_index);         timerIndex++ )
    {
        if( timers[timerIndex].first == timeToSearch )
        {            if( timers[timerIndex].second.timerType != TimerType::FreeTimer )
            {
                return timerIndex;
            }
        }
    }
    return ARRAY_timers_end();
}

TimerStack::TimerIndex TimerStack::ARRAY_timers_begin(void)
{
    if( TimerStack::timerTableNbrOfElements > 0 )
    {        return 0;
    }
    else {
        return ARRAY_timers_end();    }
}


inline TimerStack::TimerIndex TimerStack::ARRAY_timers_end(void)
{
    return TIMER_TABLE_MAX_NBR_OF_ELEMENTS;
}

EBoolean
TimerStack::ARRAY_timers_erase( TimerStack::TimerIndex & iter )
{
    EBoolean  retStatus = EBoolean_False;
    if( timers[iter].second.timerType != TimerType::FreeTimer )    {
        if (timers[iter].second.timerType == TimerType::NbccRecovery)
        {
            if (timers[iter].second.value.nbccRecovery.msg)            {
                delete timers[iter].second.value.nbccRecovery.msg;
                timers[iter].second.value.nbccRecovery.msg = 0;
            }
        }

        timers[iter].first = 0;
        timers[iter].second.timerType = TimerType::FreeTimer;
        iter = ARRAY_timers_end();
        TimerStack::timerTableNbrOfElements--;
        retStatus = EBoolean_True;
    }
    else
    {
        DM_WRN_HIGH( "Timer %u with time %d and type %d not reserved, cannot erase", iter, timers[iter].first,
                     timers[iter].second.timerType );
    }

    return retStatus;
}



void
TimerStack::ARRAY_timers_clear(void)
{
    TimerStack::timerTableNbrOfElements = 0;

    ARRAY_timers_high_mark              = 0;

    ARRAY_timers_max_index              = ARRAY_timers_high_mark + 1;

    memset( &timers, 0, sizeof( timers ));

    for( int timerIndex = 0;
         timerIndex < TIMER_TABLE_MAX_NBR_OF_ELEMENTS;
         timerIndex++ )
    {
        timers[timerIndex].second.timerType = TimerType::FreeTimer;
    }
}

TimeCounter
TimerStack::ARRAY_timers_first( TimerStack::TimerIndex iter )
{
    if( !ARRAY_timers_empty() )
    {        if(iter < TIMER_TABLE_MAX_NBR_OF_ELEMENTS )
        {
            return timers[iter].first;
        }        else
        {
            DM_ERR_HIGH( "Iterator %u out of range %u, cannot get first timer", iter, TIMER_TABLE_MAX_NBR_OF_ELEMENTS );
        }
    }
    else
    {
        DM_ERR_HIGH( "Timer stack is empty, cannot get first timer %u", iter );
    }

    return 0;
}


TimerData *
TimerStack::ARRAY_timers_second( TimerStack::TimerIndex iter )
{
    if( !ARRAY_timers_empty() )
    {        if(iter < TIMER_TABLE_MAX_NBR_OF_ELEMENTS )
        {
            return &timers[iter].second;
        }        else
        {
            DM_ERR_HIGH( "Iterator %u out of range %u, cannot get second timer", iter, TIMER_TABLE_MAX_NBR_OF_ELEMENTS );
        }
    }
    else
    {
        DM_ERR_HIGH( "Timer stack is empty, cannot get second timer %u", iter );
    }

    return 0;
}


TimerStack::TimerIndex
TimerStack::ARRAY_timers_next( TimerStack::TimerIndex elem )
{
    if(elem < TIMER_TABLE_MAX_NBR_OF_ELEMENTS )
    {        for( u32 timerIndex = 0;
             timerIndex < TIMER_TABLE_MAX_NBR_OF_ELEMENTS;
             timerIndex++ )
        {            if( timers[timerIndex].first == timers[elem].first )
            {
                if( timers[timerIndex].second.timerType != TimerType::FreeTimer )
                {
                    if( elem != timerIndex )
                    {
                        return timerIndex;
                    }
                }
                else
                {
                    DM_ERR_HIGH( "Timer %u not reserved, cannot get next timer", elem );
                }
            }
        }
    }
    else
    {
        DM_ERR_HIGH( "Iterator %u out of range %u, cannot get next timer", elem, TIMER_TABLE_MAX_NBR_OF_ELEMENTS );
    }

    return ARRAY_timers_end();
}

TSfn        currSfn;

TimerStack::TimerStack()
{
    MTSPRINTF("DMEAS: TimerStack constructed\n");
    DMeas::currSfn  = 0;
    timeCounter     = 0;
    timeOffsetToSFN = 0;
    timeFromStart   = 0;
    nthFib          = 0;
    TimerStack::timerTableNbrOfElements = 0;
    ARRAY_timers_clear();
}

/**
 *
 */
TimerStack::~TimerStack()
{
    MTSPRINTF("DMEAS: TimerStack destructed\n");
}

void
TimerStack::trigExpired( TimerIndex expired )
{
    TimerData* timerData = ARRAY_timers_second( expired );
    if ( NULL == timerData )
    {
        DM_ERR_HIGH( "Cannot trigger expiry for a NULL timerData" );
        return;
    }

    TimerType  timerType = timerData->timerType;

    timerData->timerType = TimerType::ExpiryLock;
    switch( timerType )
    {
    case TimerType::MeasurementPeriod:    case TimerType::MeasurementInit:
    case TimerType::SlaveMeasurementInit:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW("Expired - %u/%u - Measurement: %u / %u (%u) - Sicad: %#X",
                   expired,
                   timeCounter,
                   timerData->value.measurement.measurementId,
                   timerData->value.measurement.userId,
                   timerType,
                   timerData->value.measurement.sicadToWait);
        MTPRINTF("*******************************************\n");
        //g_MeasContainer.timerExpired(timerType, timerData->value.measurement);
        break;
    case TimerType::ReconfCommitInd:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - ReconfCommitInd",
                    expired,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.proceedReconfigCommit( &timerData->value.reconfCommitInd );
        break;
    case TimerType::ChangeDSPInd:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - ChangeDSPInd",
                    expired,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.timeToChangeDSP( &timerData->value.changeDSPInd );
        break;
    case TimerType::PrepareChangeInd:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - PrepareChangeInd",
                    expired,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.userTransferTimer( timerData->value.prepareChangeInd.userId );
        break;
    case TimerType::RlDeletion:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - RlDeletion",
                    expired,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.proceedRlDeletion( &timerData->value.rlDeletion);
        break;
    case TimerType::CommitUserTransfer:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - CommitUserTransfer",
                    expired,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.proceedCommitUserTransfer( &timerData->value.commitUserTransfer);
        break;

    case TimerType::NbccRecovery:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - NbccRecovery. No Reset to RNC",
                    expired,
                    timeCounter);
        MTPRINTF("*******************************************\n");

        //g_RLTable.NbccRecoveryRNCIndFail(timerData->value.nbccRecovery.msg);
        remove(expired);
        break;

    case TimerType::DefinitelyRemoveUser:
        DM_DBG_LOW(
                    "Expired - %u/%u - DefinitelyRemoveUser, nbccId: %u",
                    expired,
                    timeCounter,
                    timerData->value.nbccid);

        //g_RLTable.removeDeletedUser(timerData->value.nbccid);
        break;

    default:
        DM_WRN_HIGH( "Unknown timer type expired: %d", timerType );
        break;
    }

    timerData->timerType = timerType;
}

#define MAX_SFN_CYCLE_LEN 4095

EBoolean
TimerStack::preRefresh( const TSfn newSfn )
{
    TSfn tmpSfn;
    EBoolean retVal = EBoolean_False;

    if ( DMeas::currSfn < newSfn )
    {
        for ( tmpSfn = DMeas::currSfn + 1 ; tmpSfn <= newSfn ; tmpSfn++ )
        {
            retVal = this->refresh(tmpSfn);
        }
    }
    else if ( DMeas::currSfn > newSfn )
    {
        for ( tmpSfn = DMeas::currSfn + 1 ; ((tmpSfn <= newSfn) || (tmpSfn <= MAX_SFN_CYCLE_LEN)) ; tmpSfn++ )
        {
            retVal = this->refresh(tmpSfn);
        }

        if ( (tmpSfn == MAX_SFN_CYCLE_LEN + 1) && (newSfn != MAX_SFN_CYCLE_LEN) )
        {
            retVal = this->refresh(0);

            for ( tmpSfn = DMeas::currSfn + 1 ; tmpSfn <= newSfn ; tmpSfn++ )
            {
                retVal = this->refresh(tmpSfn);
            }
        }
    }
    else
    {

#ifndef MEASURE_DEDICATED_MT_TEST

        (timeFromStart += 20) %= 30000;
        if (EBoolean_True == mayIPrint())
        {
            DM_DBG_LOW("TimerStack.preRefresh: DMeas::currSfn[%u] == newSfn[%u], this should not happen %d.", DMeas::currSfn, newSfn, timeFromStart);
        }
#endif
        retVal = this->refresh(newSfn);
    }

    return (retVal);
}

EBoolean
TimerStack::refresh( const TSfn newSfn )
{
    EBoolean timersTrigged = EBoolean_False;

    if( DMeas::currSfn == newSfn ) {
        return timersTrigged;
    }

    if( DMeas::currSfn > newSfn )
    {
        timeOffsetToSFN += MAX_SFN_CYCLE_LEN + 1;
        //timeOffsetToSFN &= 0x7FFFF;
    }
#ifdef MEASURE_DEDICATED_MT_TEST
    if( timeOffsetToSFN + newSfn < timeCounter ) {
        fprintf( stderr, "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
    }
#endif /* MEASURE_DEDICATED_MT_TEST */

    timeCounter = timeOffsetToSFN + newSfn;

    if( !ARRAY_timers_empty() )
    {
        TimeCounter timeToExpire = timeCounter;

        TimerIndex expiredItem = ARRAY_timers_find( timeToExpire );

        if( expiredItem != ARRAY_timers_end() )
        {            timersTrigged = EBoolean_True;
            MTPRINTF("_____________________________________________________[%u]\n\n",timeToExpire);
            do {
                trigExpired( expiredItem );

                TimerIndex itemToBeDeleted  = expiredItem;

                expiredItem = ARRAY_timers_next( expiredItem );
                remove( itemToBeDeleted );

            }            while( expiredItem != ARRAY_timers_end() );

            MTPRINTF("_________________________________________________________\n\n");
        }
    }
    DMeas::currSfn = newSfn;
    return timersTrigged;
}

EBoolean TimerStack::insert(
        const TSfn             sfn,
        const TimerData      & timerData )
{
    MTPRINTF("DMEAS: TimerStack: insert - start\n");
    TimerIndex   iter;
    TimeCounter     timeValue = timeOffsetToSFN + sfn;

    if( sfn < DMeas::currSfn ) {        timeValue += MAX_SFN_CYCLE_LEN;
    }

    return this->insert( timeValue, timerData, iter );
}

void TimerStack::initIterator(
        TimerIndex                       & iter )
{
    iter = ARRAY_timers_end();
}

EBoolean TimerStack::isValidIterator(
        const TimerIndex                 & iter )
{
    if( ARRAY_timers_end() != iter )
    {        return EBoolean_True;
    }
    else {
        return EBoolean_False;    }
}

EBoolean TimerStack::insertMeasurement(
        const DMeas::TimerType timerType,
        const TimeCounter timeAdvance,
        const TMeasurementID measurementId,
        const TUserId userId,
        TimerIndex & iter,
        TAaSysComSicad const sicadToWait,
        EFaultId const faultId)
{    TimerData timerData;
    timerData.timerType = timerType;
    timerData.value.measurement.measurementId = measurementId;
    timerData.value.measurement.userId = userId;    timerData.value.measurement.sicadToWait = sicadToWait;
    timerData.value.measurement.faultId = faultId;

    DM_DBG_LOW("[%u]InsertMeasurement: %d timeAdvance: %u ( nbccId: %d / type: %u ), sicad: %#X",
               timeCounter, timerData.value.measurement.measurementId, timeAdvance,
               timerData.value.measurement.userId, timerType, timerData.value.measurement.sicadToWait);

    return this->insert(timeCounter + timeAdvance, timerData, iter);
}

const int TimerStack::fibs[6] = {0, 1000, 1000, 2000, 3000, 5000};

EBoolean TimerStack::mayIPrint()
{
    EBoolean ret = EBoolean_False;

    if (!nthFib)
    {
        nthFib = (nthFib + 1) % 6;
        ret = EBoolean_True;
    }
    else
    {
        if (timeFromStart % fibs[nthFib] == 0)
        {
            nthFib = (nthFib + 1) % 6;
            ret = EBoolean_True;
        }
    }
    return ret;
}

EBoolean TimerStack::insert(TimeCounter timeValue, TimerData const& timerData, TimerIndex& iter)
{

    TSfn realSfn = tcomGetSfn(); //provided by HWRel
    MTPRINTF("DMEAS MT environment: realSFN read from MT app by genio_sfn_ctrl_read(): %u \n", realSfn);

    DM_DBG_LOW( "timeValue: %u (before realSfn handling!)", timeValue);
    if( TimerType::ChangeDSPInd    != timerData.timerType
            && TimerType::ReconfCommitInd != timerData.timerType
            && TimerType::CommitUserTransfer != timerData.timerType )
    {
        if( realSfn != DMeas::currSfn )
        {
            //Pending API_SFN_MSG's, timeValue needs fiddling to get the real delay
            if( realSfn > DMeas::currSfn )
            {
                //Amount of pending API_SFN_MSG's in DMeas msg buffer: realSfn - DMeas::currSfn
                //Take the difference into account to get the real timeout
                timeValue += ( realSfn - DMeas::currSfn );
            }
            else
            {
                //realSfn has rolled over but currSfn has not, add MAX_SFN_CYCLE_LEN to realSfn before subtraction
                //-> amount of pending API_SFN_MSG's in DMeas msg buffer: (realSfn+MAX_SFN_CYCLE_LEN) - DMeas::currSfn,
                //Take the difference into account to get the real timeout
                timeValue += ( (realSfn+MAX_SFN_CYCLE_LEN) - DMeas::currSfn );
            }
        }
    }

    if( TimerType::PrepareChangeInd == timerData.timerType )
    {
        timeValue +=  + timeOffsetToSFN;
    }

    DM_DBG_LOW( "timeValue: %u,  DMeas::currSfn: %u, realSfn: %u",
                timeValue, DMeas::currSfn, realSfn);

    iter = ARRAY_timers_insert( timeValue, timerData );

    if( ARRAY_timers_end() != iter )
    {
        MTPRINTF("DMEAS: TimerStack: insert - ready ok ( timeValue = %u )\n",ARRAY_timers_first( iter ));
        return EBoolean_True;
    }
    else
    {
        DM_WRN_HIGH( "Failed to insert timer with value %u", timeValue );

        return EBoolean_False;
    }
}

EBoolean
TimerStack::renewMeasurement(TimerIndex & iter, TimeCounter const timeAdvance)
{
    if( iter != ARRAY_timers_end() )
    {        TimerData *timerDataPtr = ARRAY_timers_second( iter );
        if ( NULL == timerDataPtr )
        {
            DM_ERR_HIGH( "Cannot renew measurement for a NULL timerData" );            return EBoolean_False;
        }

        TimerData timerData = *timerDataPtr;
        if( EBoolean_True == remove( iter ) )
        {
            initIterator( iter );

            DM_DBG_LOW(
                        "[%u]RenewMeasurement: %d timeAdvance: %u ( nbccId: = %d )",
                        timeCounter,
                        timerData.value.measurement.measurementId,
                        timeAdvance,
                        timerData.value.measurement.userId);

            return this->insert( timeCounter + timeAdvance, timerData, iter );
        }
        else
        {
            DM_ERR_HIGH( "RenewMeasurement[%u] counter: %u, advance: %u, unable to remove timer iter: %u for nbccId: %u",
                         timerData.value.measurement.measurementId, timeCounter, timeAdvance, iter,
                         timerData.value.measurement.userId );
        }
    }
    else
    {
        DM_WRN_HIGH( "RenewMeasurement timeCounter: %u, timeAdvance: %u Invalid Iterator", timeCounter, timeAdvance );
    }

    return EBoolean_False;
}


/**
 *
 */
EBoolean
TimerStack::remove(TimerIndex& iter)
{
    EBoolean  retStatus = EBoolean_False;
    if( iter != ARRAY_timers_end() )    {
        TimerData* timerData = ARRAY_timers_second( iter );

        if ( NULL == timerData )        {
            DM_ERR_HIGH( "Cannot remove a NULL timerData" );

            return retStatus;
        }

        if ( TimerType::ExpiryLock != timerData->timerType )
        {
            MTPRINTF("TimerStack::remove(): Timer to be removed by ARRAY_timers_erase, iter: %u\n", iter);
            retStatus = ARRAY_timers_erase(iter);
        }
        else
        {
            DM_DBG_LOW( "Cannot remove timer, which has already expired" );
        }
    }
    else
    {
        /* 22.11.07: Print changed to debug print because of unnecessary warnings in udp log */
        DM_DBG_LOW( "TimerS: No timer to be removed.");
    }

    MTPRINTF("TimerStack::remove(): Timer iterator is reinit, iter:%u\n",iter);
    initIterator( iter );

    return retStatus;
}

EBoolean
TimerStack::trigExpiredAndRemove(TimerIndex &timerIter)
{
    this->trigExpired( timerIter );
    return this->remove( timerIter );
}

void TimerStack::clearUserTimers( const TNodeBCommunicationContextId nBCCId )
{
    if( !ARRAY_timers_empty() )
    {
        for( TimerIndex iter = ARRAY_timers_begin(); iter != ARRAY_timers_end(); ++iter )
        {
            TimerData *data = ARRAY_timers_second( iter );
            if(NULL != data)            {
                if( data->timerType != TimerType::FreeTimer )
                {
                    if( ( data->timerType == TimerType::ChangeDSPInd  &&  data->value.changeDSPInd.userId == nBCCId )                            ||
                            ( data->timerType == TimerType::ReconfCommitInd  &&  data->value.reconfCommitInd.userId == nBCCId )
                            ||
                            ( data->timerType == TimerType::CommitUserTransfer  &&  data->value.commitUserTransfer.userId == nBCCId ))
                    {
                        removeTimerPrint(data->timerType, nBCCId);
                        timers[iter].first = 0;
                        timers[iter].second.timerType = TimerType::FreeTimer;
                        TimerStack::timerTableNbrOfElements--;
                        if( ARRAY_timers_empty() )
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
}


void TimerStack::removeTimerPrint( const TimerType timerType, const TNodeBCommunicationContextId nBCCId )
{
    if ( TimerType::ChangeDSPInd == timerType)
    {        DM_DBG_LOW(
                    "Removed timer for nbccId: %u, timer type: ChangeDSP",
                    nBCCId);
    }    else if ( TimerType::ReconfCommitInd == timerType)
    {
        DM_DBG_LOW(
                    "Removed timer for nbccId: %u, timer type: ReconfCommit",
                    nBCCId);
    }
}

void TimerStack::dump(void)
{
    //MKJ: 18108EO09P   if( !timers.empty() ) {
    if( !ARRAY_timers_empty() ) {
        //MKJ: 18108EO09P     dump( timers.begin(), timers.end() );
        dump( ARRAY_timers_begin(), ARRAY_timers_end() );
    }
    else {
        DM_DBG_LOW(
                    "TimersTable:  -- EMPTY -- ( timeCounter = %u timeOffsetToSFN = %u DMeas::currSfn = %u )",
                    timeCounter,
                    timeOffsetToSFN,
                    DMeas::currSfn);
    }
}

TimerData     *
TimerStack::timersFindNbccRecovery(TNodeBCommunicationContextId nbccId, TimerIndex &iter)
{
    initIterator( iter );
    if( !ARRAY_timers_empty() )
    {
        for( TimerIndex itr = ARRAY_timers_begin(); itr != ARRAY_timers_end(); itr ++ )
        {
            TimerData *data = ARRAY_timers_second( itr );
            if(NULL != data)            {
                if (data->timerType == TimerType::NbccRecovery && data->value.nbccRecovery.nodeBCommunicationContextId == nbccId)
                {
                    MTPRINTF("TimerStack::timersFindNbccRecovery: nbccId: %u  iter=%u",nbccId,iter);                    iter = itr;
                    return data;
                }
            }
        }
    }
    MTPRINTF("TimerStack::timersFindNbccRecovery: nbccId: %u  !!!! iter not found ",nbccId);
    return NULL;
}

void TimerStack::dump(TimerIndex begin, TimerIndex end)
{
    MTPRINTF("TimersTable[id]: timeVal |    type    | value  ( timeCounter = %u timeOffsetToSFN = %u DMeas::currSfn = %u )\n",
             timeCounter, timeOffsetToSFN, DMeas::currSfn);

    TimerIndex iter = begin;
    for (u32 counter = 0; counter < 10; counter++)
    {
        if (EBoolean_True == isValidIterator(iter))        {
            std::string timerTypeStr = "UNKNOWN   ";
            switch(timers[iter].second.timerType)
            {            case DMeas::TimerType::FreeTimer:
                timerTypeStr = "FREE      ";
                break;
            case DMeas::TimerType::MeasurementInit:
                timerTypeStr = "MeasInit  ";
                break;
            case DMeas::TimerType::MeasurementPeriod:
                timerTypeStr = "MeasPeriod";
                break;
            case DMeas::TimerType::ChangeDSPInd:
                timerTypeStr = "ChangeDSP ";
                break;
            case DMeas::TimerType::PrepareChangeInd:
                timerTypeStr = "PrepReconf";
                break;
            case DMeas::TimerType::ReconfCommitInd:
                timerTypeStr = "ReconfComm";
                break;
            case DMeas::TimerType::SlaveMeasurementInit:
                timerTypeStr = "SlaveInit ";
                break;
            case DMeas::TimerType::RlDeletion:
                timerTypeStr = "RlDeletion";
                break;
            case DMeas::TimerType::ExpiryLock:
                timerTypeStr = "ExpiryLock";
                break;
            default:
                break;
            }

            MTPRINTF("TimersTable[%02d]:    %-4u | %s | MId: %d / nbccId: %u\n",
                     iter, timers[iter].first, timerTypeStr.c_str(), timers[iter].second.value.measurement.measurementId,
                     timers[iter].second.value.measurement.userId);
        }

        iter++;
    }
}

#ifdef MEASURE_DEDICATED_MT_TEST

void
TimerStack::clear(
        void )
{
    MTPRINTF("======================== TIMERSTACK - CLEAR =====================\n");

    ARRAY_timers_clear(); // 18108EO09P
}

#endif /* MEASURE_DEDICATED_MT_TEST */

} // namespace DMeas
