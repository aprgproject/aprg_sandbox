#pragma once

#include <EFaultId.h>
#include <SDedMeasInitReq3G.h>
#include <SRLChangeDSPInd_Ver2.h>
#include <SRLCommitChangeInd_Ver2.h>
#include <SRLDeletionInd.h>
#include <SRLPrepareChangeInd.h>
#include <SRLReconfCommitInd.h>
#include <TAaSysComSicad.h>
#include <TMeasurementID.h>
#include <TNbccId.h>
#include <TNodeBCommunicationContextId.h>

#include <map>

namespace DMeas
{

#define TIMER_INVALID_ITERATOR 0xFFFFFFFF

using TimeCounter=u32;
class MeasurementContainer;

extern TSfn currSfn;

enum class TimerType
{
    FreeTimer       = 42,
    MeasurementInit,
    MeasurementPeriod,    ChangeDSPInd,
    PrepareChangeInd,
    ReconfCommitInd,
    SlaveMeasurementInit,    RlDeletion,
    CommitUserTransfer,
    NbccRecovery,
    ExpiryLock,
    DefinitelyRemoveUser,
    Test
} ;

typedef struct
{
    TMeasurementID measurementId; // Measurement Id that this timer was set for
    TUserId userId; // User Id that this timer was set for
    TAaSysComSicad sicadToWait; // Sicad where timer was probably started for
    EFaultId faultId;
} TMeasurementTimer;

struct SNBCCRecovery
{
    SDedMeasInitReq3G*   msg;
    TNbccId 	        nodeBCommunicationContextId;
};

struct TimerData
{
    TimeCounter timerValue;
    TimerType timerType;
    union Value
    {
        TMeasurementTimer  measurement;
        SRLChangeDSPInd_Ver2 changeDSPInd;
        SRLPrepareChangeInd prepareChangeInd;
        SRLReconfCommitInd reconfCommitInd;
        SRLDeletionInd  rlDeletion;
        SRLCommitChangeInd_Ver2       commitUserTransfer;
        SNBCCRecovery      nbccRecovery;
        unsigned int       testNbr;
        TNodeBCommunicationContextId  nbccid;
    } value;
};

class TimerStack
{

public:
    using TimerIndex=u32;
    using TimerTable=std::map<TimerIndex, TimerData>;
    using TimerTablePair=std::pair<TimerIndex const, TimerData>;
    using TimerTableConstIterator=TimerTable::const_iterator;

    static TimeCounter s_timerCounter;

    TimerStack();
    ~TimerStack();

    EBoolean mayIPrint();
    TimeCounter ARRAY_timers_first (TimerIndex timerIndex);
    TimerData* ARRAY_timers_second (TimerIndex timerIndex);
    TimerData* timersFindNbccRecovery(TNodeBCommunicationContextId nbccId, TimerIndex & timerIndex);
    EBoolean trigExpiredAndRemove(TimerIndex & timerIndex);
    EBoolean preRefresh(TSfn const newSfn);
    EBoolean insert(TSfn const expirationTime, TimerData const& timerData);
    EBoolean insert(TimeCounter expirationTime, TimerData const& timerData, TimerIndex& timerIndex);
    EBoolean insertMeasurement(TimerType const timerType,
         TimeCounter const timeAdvance,
         TMeasurementID const measurementId,
         TUserId const userId,
         TimerIndex & timerIndex,
         TAaSysComSicad const timedOutSicad = 0,
         EFaultId const faultId = EFaultId_NoResponseAl);
    EBoolean renewMeasurement(TimerIndex& timerIndex, TimeCounter const timeAdvance);
    EBoolean remove(TimerIndex & timerIndex);
    void initIterator(TimerIndex & timerIndex);
    EBoolean isValidIterator(TimerIndex const& timerIndex);
    void clearUserTimers(TNodeBCommunicationContextId const nBCCId);
    void removeTimerPrint(TimerType const timerType, TNodeBCommunicationContextId const nBCCId);
    void dump(TimerIndex begin, TimerIndex end);
    void dump(void);


private:

    inline int ARRAY_timers_empty(void);
    TimerIndex ARRAY_timers_insert(TimeCounter timerValue, TimerData const& timerData);
    TimerIndex ARRAY_timers_find(TimeCounter);
    TimerIndex ARRAY_timers_begin(void);

    inline TimerIndex ARRAY_timers_end(void);
    EBoolean ARRAY_timers_erase(TimerIndex & timerIndex);
    void ARRAY_timers_clear(void);
    TimerIndex ARRAY_timers_next (TimerIndex timerIndex);
    void trigExpired(TimerIndex timerIndex);
    EBoolean refresh(TSfn const newSFN);

#ifdef MEASURE_DEDICATED_MT_TEST
    void clear (void);
#endif

    TimeCounter timeCounter;
    TimeCounter timeOffsetToSFN;
    TimerTable m_timers;
    TimeCounter     timeFromStart;
    u32  nthFib;
    static const int fibs[6];
};
}