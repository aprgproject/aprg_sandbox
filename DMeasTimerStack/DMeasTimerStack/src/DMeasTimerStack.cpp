#include <cstdio>
#include <cstring>

#define DM_ERR_HIGH printf
#define DM_WRN_HIGH printf
#define DM_INF_HIGH printf
#define DM_DBG_LOW printf
#define MTPRINTF printf
#define MTSPRINTF printf
static unsigned int MY_SFN;

//sample impl
unsigned int tcomGetSfn()
{
    return MY_SFN;
}

void tcomSetSfn(unsigned int sfn)
{
    MY_SFN = sfn;
}

#include <SRLChangeDSPInd.h>
#include <SRLReconfCommitInd.h>
#include <DMeasTimerStack.hpp>

#include <algorithm>
#include <string>

using namespace std;
using namespace alba;

namespace DMeas 
{

TimerStack::TimerIndex TimerStack::s_timerCounter = 0;
int const TimerStack::fibs[6] = {0, 1000, 1000, 2000, 3000, 5000};

inline int TimerStack::ARRAY_timers_empty(void)
{
    return m_timers.empty();
}

TimerStack::TimerIndex TimerStack::ARRAY_timers_insert(TimeCounter timerValue, TimerData const& timerData)
{
    TimerData timerDataToBeSaved=timerData;
    timerDataToBeSaved.timerValue = timerValue;
    TimerIndex timerIndex = 0;
    TimerTableConstIterator notConsecutiveTimerIndexIterator = adjacent_find(m_timers.begin(), m_timers.end(), [](TimerTablePair const& timerDataPair1, TimerTablePair const& timerDataPair2)
    {
            return timerDataPair1.first+1!=timerDataPair2.first;
    });
    if(notConsecutiveTimerIndexIterator==m_timers.end())
    {
        timerIndex = (timerIndex==TIMER_INVALID_ITERATOR) ? 0 : s_timerCounter++;
    }
    else
    {
        timerIndex=(notConsecutiveTimerIndexIterator->first)+1;
    }
    m_timers[timerIndex] = timerDataToBeSaved;
    return timerIndex;
}

TimerStack::TimerIndex TimerStack::ARRAY_timers_find(TimeCounter timeToSearch)
{
    TimerIndex timerIndex = 0;
    TimerTableConstIterator iteratorWithSameTimerValue = find_if(m_timers.begin(), m_timers.end(), [&timeToSearch](TimerTablePair const& timerDataPair)
    {
        return timerDataPair.second.timerValue==timeToSearch;
    });
    if(iteratorWithSameTimerValue==m_timers.end())
    {
        timerIndex=TIMER_INVALID_ITERATOR;
    }
    else
    {
        timerIndex=iteratorWithSameTimerValue->first;
    }
    return timerIndex;
}

TimerStack::TimerIndex TimerStack::ARRAY_timers_begin(void)
{
    TimerIndex timerIndex = TIMER_INVALID_ITERATOR;
    if(!m_timers.empty())
    {
        timerIndex = 0;
    }
    return timerIndex;
}

inline TimerStack::TimerIndex TimerStack::ARRAY_timers_end(void)
{
    TimerIndex timerIndex = TIMER_INVALID_ITERATOR;
    if(!m_timers.empty())
    {
        TimerTableConstIterator endIterator = m_timers.end();
        endIterator--;
        timerIndex = (endIterator->first)+1;
    }
    return timerIndex;
}

EBoolean TimerStack::ARRAY_timers_erase(TimerStack::TimerIndex & timerIndex)
{
    EBoolean retStatus = EBoolean_False;
    TimerData & timerData(m_timers[timerIndex]);
    if(timerData.timerType != TimerType::FreeTimer)
    {
        if(timerData.timerType == TimerType::NbccRecovery)
        {
            if (timerData.value.nbccRecovery.msg)
            {
                delete timerData.value.nbccRecovery.msg;
                timerData.value.nbccRecovery.msg = 0;
            }
        }

        timerData.timerValue = 0;
        timerData.timerType = TimerType::FreeTimer;
        timerIndex = TIMER_INVALID_ITERATOR;
        retStatus = EBoolean_True;
        m_timers.erase(timerIndex);
    }
    else
    {
        DM_WRN_HIGH("Timer %u with time %d and type %d not reserved, cannot erase", timerIndex, timerData.timerValue, timerData.timerType);
    }
    return retStatus;
}

void TimerStack::ARRAY_timers_clear(void)
{
    m_timers.clear();
}

TimeCounter TimerStack::ARRAY_timers_first(TimerStack::TimerIndex timerIndex)
{
    TimeCounter timeCounter = TIMER_INVALID_ITERATOR;
    if( !ARRAY_timers_empty() )
    {
        timeCounter = m_timers[timerIndex].timerValue;
    }
    else
    {
        DM_ERR_HIGH( "Timer stack is empty, cannot get first timer %u", timerIndex );
    }
    return timeCounter;
}

TimerData* TimerStack::ARRAY_timers_second(TimerStack::TimerIndex timerIndex)
{
    TimerData* timeDataPtr = nullptr;
    if( !ARRAY_timers_empty() )
    {
        timeDataPtr = &m_timers[timerIndex];
    }
    else
    {
        DM_ERR_HIGH( "Timer stack is empty, cannot get second timer %u", timerIndex );
    }
    return timeDataPtr;
}


TimerStack::TimerIndex TimerStack::ARRAY_timers_next(TimerStack::TimerIndex timerIndex)
{
    TimerData const& currentTimerData(m_timers[timerIndex]);

    for(TimerTablePair const& timerTablePair : m_timers) //optimize this
    {
        if( timerTablePair.second.timerValue == currentTimerData.timerValue )
        {
            if( timerTablePair.second.timerType != TimerType::FreeTimer )
            {
                if(timerIndex != timerTablePair.first)
                {
                    return timerTablePair.first;
                }
            }
            else
            {
                DM_ERR_HIGH( "Timer %u not reserved, cannot get next timer", timerIndex );
            }
        }
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
    ARRAY_timers_clear();
}

TimerStack::~TimerStack()
{
    MTSPRINTF("DMEAS: TimerStack destructed\n");
}

void TimerStack::trigExpired(TimerIndex timerIndex)
{
    TimerData* timerData = ARRAY_timers_second(timerIndex);

    if ( nullptr == timerData )
    {
        DM_ERR_HIGH( "Cannot trigger expiry for a nullptr timerData" );
        return;
    }

    TimerType timerType = timerData->timerType;
    timerData->timerType = TimerType::ExpiryLock;

    switch( timerType )
    {
    case TimerType::MeasurementPeriod:
    case TimerType::MeasurementInit:
    case TimerType::SlaveMeasurementInit:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW("Expired - %u/%u - Measurement: %u / %u (%u) - Sicad: %#X",
                   timerIndex,
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
                    timerIndex,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.proceedReconfigCommit( &timerData->value.reconfCommitInd );
        break;
    case TimerType::ChangeDSPInd:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - ChangeDSPInd",
                    timerIndex,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.timeToChangeDSP( &timerData->value.changeDSPInd );
        break;
    case TimerType::PrepareChangeInd:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - PrepareChangeInd",
                    timerIndex,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.userTransferTimer( timerData->value.prepareChangeInd.userId );
        break;
    case TimerType::RlDeletion:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - RlDeletion",
                    timerIndex,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.proceedRlDeletion( &timerData->value.rlDeletion);
        break;
    case TimerType::CommitUserTransfer:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - CommitUserTransfer",
                    timerIndex,
                    timeCounter);
        MTPRINTF("*******************************************\n");
        //g_RLTable.proceedCommitUserTransfer( &timerData->value.commitUserTransfer);
        break;

    case TimerType::NbccRecovery:
        MTPRINTF("*******************************************\n");
        DM_DBG_LOW(
                    "Expired - %u/%u - NbccRecovery. No Reset to RNC",
                    timerIndex,
                    timeCounter);
        MTPRINTF("*******************************************\n");

        //g_RLTable.NbccRecoveryRNCIndFail(timerData->value.nbccRecovery.msg);
        remove(timerIndex);
        break;

    case TimerType::DefinitelyRemoveUser:
        DM_DBG_LOW(
                    "Expired - %u/%u - DefinitelyRemoveUser, nbccId: %u",
                    timerIndex,
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

EBoolean TimerStack::preRefresh(TSfn const newSfn)
{
    TSfn tmpSfn;
    EBoolean retVal = EBoolean_False;

    if ( DMeas::currSfn < newSfn )
    {
        for ( tmpSfn = DMeas::currSfn + 1 ; tmpSfn <= newSfn ; tmpSfn++ )
        {
            retVal = refresh(tmpSfn);
        }
    }
    else if ( DMeas::currSfn > newSfn )
    {
        for ( tmpSfn = DMeas::currSfn + 1 ; ((tmpSfn <= newSfn) || (tmpSfn <= MAX_SFN_CYCLE_LEN)) ; tmpSfn++ )
        {
            retVal = refresh(tmpSfn);
        }

        if ( (tmpSfn == MAX_SFN_CYCLE_LEN + 1) && (newSfn != MAX_SFN_CYCLE_LEN) )
        {
            retVal = refresh(0);

            for ( tmpSfn = DMeas::currSfn + 1 ; tmpSfn <= newSfn ; tmpSfn++ )
            {
                retVal = refresh(tmpSfn);
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
        retVal = refresh(newSfn);
    }

    return (retVal);
}

EBoolean TimerStack::refresh( const TSfn newSfn )
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

    if(!ARRAY_timers_empty())
    {
        TimeCounter timeToExpire = timeCounter;

        TimerIndex expiredItem = ARRAY_timers_find( timeToExpire );

        if( expiredItem != ARRAY_timers_end() )
        {
            timersTrigged = EBoolean_True;
            MTPRINTF("_____________________________________________________[%u]\n\n",timeToExpire);
            do {
                trigExpired( expiredItem );

                TimerIndex itemToBeDeleted  = expiredItem;

                expiredItem = ARRAY_timers_next( expiredItem );

                remove( itemToBeDeleted );

            }
            while( expiredItem != ARRAY_timers_end() );

            MTPRINTF("_________________________________________________________\n\n");
        }
    }
    DMeas::currSfn = newSfn;
    return timersTrigged;
}

EBoolean TimerStack::insert(TSfn const sfn, TimerData const& timerData)
{
    MTPRINTF("DMEAS: TimerStack: insert - start\n");
    TimerIndex  timerIndex;
    TimeCounter timerValue = timeOffsetToSFN + sfn;

    if( sfn < DMeas::currSfn )
    {
        timerValue += MAX_SFN_CYCLE_LEN;
    }
    return insert(timerValue, timerData, timerIndex);
}

void TimerStack::initIterator(TimerIndex& timerIndex)
{
    timerIndex = ARRAY_timers_end();
}

EBoolean TimerStack::isValidIterator(TimerIndex const& timerIndex)
{
    if(m_timers.find(timerIndex) != m_timers.cend())
    {
        return EBoolean_True;
    }
    else
    {
        return EBoolean_False;
    }
}

EBoolean TimerStack::insertMeasurement(
        const DMeas::TimerType timerType,
        const TimeCounter timeAdvance,
        const TMeasurementID measurementId,
        const TUserId userId,
        TimerIndex & timerIndex,
        TAaSysComSicad const sicadToWait,
        EFaultId const faultId)
{
    TimerData timerData;
    timerData.timerType = timerType;
    timerData.value.measurement.measurementId = measurementId;
    timerData.value.measurement.userId = userId;
    timerData.value.measurement.sicadToWait = sicadToWait;
    timerData.value.measurement.faultId = faultId;

    DM_DBG_LOW("[%u]InsertMeasurement: %d timeAdvance: %u ( nbccId: %d / type: %u ), sicad: %#X",
               timeCounter, timerData.value.measurement.measurementId, timeAdvance,
               timerData.value.measurement.userId, timerType, timerData.value.measurement.sicadToWait);

    return insert(timeCounter + timeAdvance, timerData, timerIndex);
}

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

EBoolean TimerStack::insert(TimeCounter timerValue, TimerData const& timerData, TimerIndex& timerIndex)
{
    TSfn realSfn = tcomGetSfn(); //provided by HWRel

    MTPRINTF("DMEAS MT environment: realSFN read from MT app by genio_sfn_ctrl_read(): %u \n", realSfn);

    DM_DBG_LOW( "timerValue: %u (before realSfn handling!)", timerValue);

    if( TimerType::ChangeDSPInd    != timerData.timerType
            && TimerType::ReconfCommitInd != timerData.timerType
            && TimerType::CommitUserTransfer != timerData.timerType )
    {
        if( realSfn != DMeas::currSfn )
        {
            //Pending API_SFN_MSG's, timerValue needs fiddling to get the real delay
            if( realSfn > DMeas::currSfn )
            {
                //Amount of pending API_SFN_MSG's in DMeas msg buffer: realSfn - DMeas::currSfn
                //Take the difference into account to get the real timeout
                timerValue += ( realSfn - DMeas::currSfn );
            }
            else
            {
                //realSfn has rolled over but currSfn has not, add MAX_SFN_CYCLE_LEN to realSfn before subtraction
                //-> amount of pending API_SFN_MSG's in DMeas msg buffer: (realSfn+MAX_SFN_CYCLE_LEN) - DMeas::currSfn,
                //Take the difference into account to get the real timeout
                timerValue += ( (realSfn+MAX_SFN_CYCLE_LEN) - DMeas::currSfn );
            }
        }
    }

    if( TimerType::PrepareChangeInd == timerData.timerType )
    {
        timerValue +=  + timeOffsetToSFN;
    }

    DM_DBG_LOW( "timerValue: %u,  DMeas::currSfn: %u, realSfn: %u",
                timerValue, DMeas::currSfn, realSfn);

    timerIndex = ARRAY_timers_insert( timerValue, timerData );

    if( ARRAY_timers_end() != timerIndex )
    {
        MTPRINTF("DMEAS: TimerStack: insert - ready ok ( timerValue = %u )\n", ARRAY_timers_first( timerIndex ));
        return EBoolean_True;
    }
    else
    {
        DM_WRN_HIGH("Failed to insert timer with value %u", timerValue);
        return EBoolean_False;
    }
}

EBoolean TimerStack::renewMeasurement(TimerIndex & timerIndex, TimeCounter const timeAdvance)
{
    if(timerIndex != ARRAY_timers_end())
    {
        TimerData *timerDataPtr = ARRAY_timers_second(timerIndex);
        if ( nullptr == timerDataPtr )
        {
            DM_ERR_HIGH( "Cannot renew measurement for a nullptr timerData" );
            return EBoolean_False;
        }

        TimerData timerData = *timerDataPtr;
        if(EBoolean_True == remove( timerIndex))
        {
            initIterator(timerIndex);

            DM_DBG_LOW(
                        "[%u]RenewMeasurement: %d timeAdvance: %u ( nbccId: = %d )",
                        timeCounter,
                        timerData.value.measurement.measurementId,
                        timeAdvance,
                        timerData.value.measurement.userId);

            return insert( timeCounter + timeAdvance, timerData, timerIndex );
        }
        else
        {
            DM_ERR_HIGH( "RenewMeasurement[%u] counter: %u, advance: %u, unable to remove timer iter: %u for nbccId: %u",
                         timerData.value.measurement.measurementId, timeCounter, timeAdvance, timerIndex,
                         timerData.value.measurement.userId );
        }
    }
    else
    {
        DM_WRN_HIGH( "RenewMeasurement timeCounter: %u, timeAdvance: %u Invalid Iterator", timeCounter, timeAdvance );
    }

    return EBoolean_False;
}

EBoolean TimerStack::remove(TimerIndex& timerIndex)
{
    EBoolean  retStatus = EBoolean_False;
    if(timerIndex != ARRAY_timers_end())
    {
        TimerData* timerData = ARRAY_timers_second(timerIndex);

        if ( nullptr == timerData )
        {
            DM_ERR_HIGH( "Cannot remove a nullptr timerData" );

            return retStatus;
        }

        if ( TimerType::ExpiryLock != timerData->timerType )
        {
            MTPRINTF("TimerStack::remove(): Timer to be removed by ARRAY_timers_erase, iter: %u\n", timerIndex);
            retStatus = ARRAY_timers_erase(timerIndex);
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

    MTPRINTF("TimerStack::remove(): Timer iterator is reinit, iter:%u\n",timerIndex);
    initIterator( timerIndex );

    return retStatus;
}

EBoolean TimerStack::trigExpiredAndRemove(TimerIndex &timerIndex)
{
    trigExpired(timerIndex);
    return remove(timerIndex);
}

void TimerStack::clearUserTimers(TNodeBCommunicationContextId const nBCCId)
{
    if( !ARRAY_timers_empty() )
    {
        for(TimerTablePair const& timerTablePair : m_timers)
        {
            TimerData *data = ARRAY_timers_second( timerTablePair.first );
            if(nullptr != data)
            {
                if( data->timerType != TimerType::FreeTimer )
                {
                    if( ( data->timerType == TimerType::ChangeDSPInd  &&  data->value.changeDSPInd.userId == nBCCId )
                            ||
                            ( data->timerType == TimerType::ReconfCommitInd  &&  data->value.reconfCommitInd.userId == nBCCId )
                            ||
                            ( data->timerType == TimerType::CommitUserTransfer  &&  data->value.commitUserTransfer.userId == nBCCId ))
                    {
                        removeTimerPrint(data->timerType, nBCCId);
                        data->timerValue=0;
                        data->timerType=TimerType::FreeTimer;
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


void TimerStack::removeTimerPrint(TimerType const timerType, TNodeBCommunicationContextId const nBCCId)
{
    if ( TimerType::ChangeDSPInd == timerType)
    {
        DM_DBG_LOW(
                    "Removed timer for nbccId: %u, timer type: ChangeDSP",
                    nBCCId);
    }
    else if ( TimerType::ReconfCommitInd == timerType)
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

TimerData* TimerStack::timersFindNbccRecovery(TNodeBCommunicationContextId nbccId, TimerIndex &timerIndex)
{
    initIterator( timerIndex );
    if( !ARRAY_timers_empty() )
    {
        for( TimerIndex traversingIndex = ARRAY_timers_begin(); traversingIndex != ARRAY_timers_end(); traversingIndex ++ ) //std::find_if
        {
            TimerData *data = ARRAY_timers_second( traversingIndex );
            if(nullptr != data)
            {
                if (data->timerType == TimerType::NbccRecovery && data->value.nbccRecovery.nodeBCommunicationContextId == nbccId)
                {
                    MTPRINTF("TimerStack::timersFindNbccRecovery: nbccId: %u  iter=%u",nbccId,timerIndex);
                    timerIndex = traversingIndex;
                    return data;
                }
            }
        }
    }
    MTPRINTF("TimerStack::timersFindNbccRecovery: nbccId: %u  !!!! iter not found ",nbccId);
    return nullptr;
}

void TimerStack::dump(TimerIndex begin, TimerIndex end)
{
    MTPRINTF("TimersTable[id]: timeVal |    type    | value  ( timeCounter = %u timeOffsetToSFN = %u DMeas::currSfn = %u )\n",
             timeCounter, timeOffsetToSFN, DMeas::currSfn);

    TimerIndex timerIndex = begin;
    for (u32 counter = 0; counter < 10; counter++)
    {
        if (EBoolean_True == isValidIterator(timerIndex))
        {
            string timerTypeStr = "UNKNOWN   ";
            TimerData* timerData = ARRAY_timers_second(timerIndex);
            switch(timerData->timerType)
            {
            case DMeas::TimerType::FreeTimer:
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

            MTPRINTF("TimersTable[%02d]:    %-4U | %s | MId: %d / nbccId: %u\n",
                     timerIndex,
                     timerData->timerValue,
                     timerTypeStr.c_str(),
                     timerData->value.measurement.measurementId,
                     timerData->value.measurement.userId);
        }

        timerIndex++;
    }
}

#ifdef MEASURE_DEDICATED_MT_TEST

void TimerStack::clear(
        void )
{
    MTPRINTF("======================== TIMERSTACK - CLEAR =====================\n");

    ARRAY_timers_clear(); // 18108EO09P
}

#endif /* MEASURE_DEDICATED_MT_TEST */

} // namespace DMeas
