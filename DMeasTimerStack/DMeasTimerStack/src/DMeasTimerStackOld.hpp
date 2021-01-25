
#ifndef DMEASTIMERSTACK_HPP
#define DMEASTIMERSTACK_HPP

#include <TMeasurementID.h>
#include <TAaSysComSicad.h>
#include <EFaultId.h>
#include <SDedMeasInitReq3G.h>
#include <TNbccId.h>
#include <SRLChangeDSPInd_Ver2.h>
#include <SRLPrepareChangeInd.h>
#include <SRLDeletionInd.h>
#include <SRLCommitChangeInd_Ver2.h>
#include <SRLReconfCommitInd.h>
#include <TNodeBCommunicationContextId.h>

//----------------------- INCLUDED FILES --------------------------------------
//----------------------- EXTERNAL DEFINITIONS --------------------------------

extern const char* DMEASTIMERSTACK_VERSION;

typedef u32 TimeCounter;

//----------------------- COMMON DEFINITIONS ----------------------------------


namespace DMeas {


extern TSfn currSfn;

typedef struct
{
    TMeasurementID measurementId; // Measurement Id that this timer was set for
    TUserId userId; // User Id that this timer was set for
    TAaSysComSicad sicadToWait; // Sicad where timer was probably started for
    EFaultId faultId;
} TMeasurementTimer;


namespace TimerType
{
typedef enum
{
    FreeTimer       = 42,
    MeasurementInit,
    MeasurementPeriod,
    ChangeDSPInd,
    PrepareChangeInd,
    ReconfCommitInd,
    SlaveMeasurementInit,
    RlDeletion,
    CommitUserTransfer,
    NbccRecovery,
    ExpiryLock,
    DefinitelyRemoveUser,
    Test
} Value;
}


class MeasurementContainer;
typedef struct SNBCCRecovery
{
    SDedMeasInitReq3G*   msg;
    TNbccId 	        nodeBCommunicationContextId;
}SNBCCRecovery;



typedef struct
{
    TimerType timerType;
    union Value
    {
        TMeasurementTimer  measurement;        SRLChangeDSPInd_Ver2          changeDSPInd;
        SRLPrepareChangeInd           prepareChangeInd;
        SRLReconfCommitInd reconfCommitInd;
        SRLDeletionInd     rlDeletion;        SRLCommitChangeInd_Ver2       commitUserTransfer;
        SNBCCRecovery      nbccRecovery;
        unsigned int       testNbr;
        TNodeBCommunicationContextId  nbccid;
    } value;

} TimerData;

#define MAX_NBR_OF_NBCC_IN_WAM 10//remove this

#ifdef REL4
#define TIMER_TABLE_MAX_NBR_OF_ELEMENTS 7*10*MAX_NBR_OF_NBCC_IN_WAM
#else
#define TIMER_TABLE_MAX_NBR_OF_ELEMENTS 10*MAX_NBR_OF_NBCC_IN_WAM // PR 30590ES09P: increased value
#endif

class TimerStack
{
private:

    TimeCounter timeCounter;
    TimeCounter timeOffsetToSFN;
    typedef struct
    {
        TimeCounter first;
        TimerData   second;
    } TimerTable;

    TimerTable  timers[ TIMER_TABLE_MAX_NBR_OF_ELEMENTS ];

    u32 ARRAY_timers_high_mark;

    u32 ARRAY_timers_max_index;

public: // datatypes and variables

    typedef u32   TimerIterator;
    
    EBoolean      mayIPrint();
    static TimerIterator timerTableNbrOfElements;

    TimeCounter     ARRAY_timers_first    ( TimerIterator iter);
    TimerData     * ARRAY_timers_second   ( TimerIterator iter);
    TimerData     * timersFindNbccRecovery( TNodeBCommunicationContextId nbccId, TimerIterator &iter);

private: // methods

    TimeCounter     timeFromStart;
    u32  nthFib;

    static const int fibs[6];

    inline
    int  ARRAY_timers_empty    ( void );
    TimerIterator   ARRAY_timers_insert   ( TimeCounter timeValue,
           TimerData timerData );
    TimerIterator   ARRAY_timers_find     ( TimeCounter );
    TimerIterator   ARRAY_timers_begin    ( void );

    inline
    TimerIterator   ARRAY_timers_end      ( void );

    EBoolean        ARRAY_timers_erase    ( TimerIterator & iter );
    void ARRAY_timers_clear    ( void );
    TimerIterator   ARRAY_timers_next     ( TimerIterator elem );
    void trigExpired ( TimerIterator expired );
    EBoolean        refresh ( const TSfn            newSFN );

public: // methods

    TimerStack();

    ~TimerStack();
    EBoolean trigExpiredAndRemove(TimerIterator &timerIter);

    EBoolean        preRefresh( const TSfn newSfn );
    EBoolean        insert  ( const TSfn     expirationTime,
        const TimerData         & timerData );
    EBoolean        insert      ( TimeCounter           expirationTime,
            const TimerData     & timerData,
            TimerIterator       & timerIterator );
    EBoolean insertMeasurement(DMeas::TimerType const timerType,
         TimeCounter const timeAdvance,
         TMeasurementID const measurementId,
         TUserId const userId,         TimerIterator & itr,
         TAaSysComSicad const timedOutSicad = 0,
         EFaultId const faultId = EFaultId_NoResponseAl);
    EBoolean renewMeasurement(TimerIterator& timerIter, TimeCounter const timeAdvance);    EBoolean remove(TimerIterator & timerIter);
    void initIterator(TimerIterator & iter);
    EBoolean isValidIterator(TimerIterator const& iter);
    void clearUserTimers(TNodeBCommunicationContextId const nBCCId);

    void removeTimerPrint(TimerType const timerType, TNodeBCommunicationContextId const nBCCId);

    void dump (TimerIterator begin, TimerIterator end);
    void dump (void);

#ifdef MEASURE_DEDICATED_MT_TEST
    void clear (void);

#endif /* MEASURE_DEDICATED_MT_TEST */

};
} // namespace DMeas
/*****************************************************************************/
#endif /* DMEASTIMERSTACK_HPP */
