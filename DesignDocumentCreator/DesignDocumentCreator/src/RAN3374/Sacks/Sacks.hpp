#include <Common/Sacks/SupplementarySacks/SupplementarySacks.hpp>
#include <RAN3374/Sacks/SupplementarySacks/SupplementarySacks.hpp>

struct AntennaCarrier_PowerEventInd
{
  TAntennaCarrierAPIDataUnitId                 discriminator;
  TAntennaCarrierAPITransactionId              transaction;
  UAntennaCarrierPowerEventCharacteristics     characteristics;
  TAntennaCarrierMonitoringId                  id;
  TAntennaCarrierOneHundredthOf_dBm            power;
} ;
