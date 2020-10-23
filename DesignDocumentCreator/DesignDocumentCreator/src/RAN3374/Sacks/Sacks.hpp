#include <Common/Sacks/SupplementarySacks.hpp>
#include <RAN3374/Sacks/SupplementarySacks.hpp>

typedef u32 TAntennaCarrierAPIDataUnitId;
typedef u32 TAntennaCarrierAPITransactionId;
typedef i32 TAntennaCarrierMonitoringId;
typedef i32 TAntennaCarrierOneHundredthOf_dBm;

struct AntennaCarrier_PowerEventInd
{
    TAntennaCarrierAPIDataUnitId                 discriminator;
    TAntennaCarrierAPITransactionId              transaction;
    UAntennaCarrierPowerEventCharacteristics     characteristics;
    TAntennaCarrierMonitoringId                  id;
    TAntennaCarrierOneHundredthOf_dBm            power;
};

struct BbRakePowerReport
{
    u32 power;
};

struct SHwConfigurationMsg
{
    SMessageAddress         btsomTelecomServiceAddr;
    SWamUnit                wamUnit[MAX_NUM_OF_CONTROL_UNITS];
    SWspUnit                wspUnit[MAX_NUM_OF_DSP_RESOURCES];
    SCarrierResources       carrierResources;
    TNumberOfItems          numOfValidLcr;
    SLocalCellResource      localCellResource[MAX_NUM_OF_LOCAL_CELLS];
    SBsConfigData           bsConfigData;
    TNumberOfItems          btsSwVersionLength;
    TDynamicData            btsSwVersion[1];
};


