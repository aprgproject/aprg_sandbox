/**
*******************************************************************************
* @file                  $HeadURL: https://svne1.access.nokiasiemensnetworks.com/isource/svnroot/BTS_I_COMMON_APPL/tags/COMMON_APPL_ENV_1602_006_00/I_Interface/Application_Env/Interfaces/AntennaCarrierPower.h $
* @version               $LastChangedRevision: 2420 $
* @date                  $LastChangedDate: 2015-06-23 00:03:53 +0800 (Tue, 23 Jun 2015) $
* @author                $Author: cap015 $
* 
* Original author        <nn>
* 
* Copyright 2010 Nokia. All rights reserved.
******************************************************************************/

#ifndef _ANTENNACARRIERPOWER_H
#define _ANTENNACARRIERPOWER_H

typedef i32 TAntennaCarrierMilliSecond;
typedef i32 TAntennaCarrierOneHundredthOf_dB;
typedef i32 TAntennaCarrierOneHundredthOf_dBm;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* discriminates between power monitoring event types. must be 32-bit. */
typedef enum
{
  EAntennaCarrierPowerEventDiscriminator_Periodic = 1,
  EAntennaCarrierPowerEventDiscriminator_EventA   = 2,
  EAntennaCarrierPowerEventDiscriminator_EventB   = 3,
  EAntennaCarrierPowerEventDiscriminator_EventC   = 4,
  EAntennaCarrierPowerEventDiscriminator_EventD   = 5,
  EAntennaCarrierPowerEventDiscriminator_EventE   = 6,
  EAntennaCarrierPowerEventDiscriminator_EventF   = 7
} EAntennaCarrierPowerEventDiscriminator;

/* discriminates between channel activity measurement power monitoring event types. must be 32-bit. */
typedef enum
{
  EAntennaCarrierCamPowerEventType_SyncOff = 1,
  EAntennaCarrierCamPowerEventType_NonSync = 2
} EAntennaCarrierCamPowerEventType;

typedef struct
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  TAntennaCarrierMilliSecond             period;
}SAntennaCarrierPowerEventPeriodic;

typedef struct
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  TAntennaCarrierMilliSecond             timeHysteresis;
  TAntennaCarrierOneHundredthOf_dBm      upperThreshold;
}SAntennaCarrierPowerEventA;

typedef struct
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  TAntennaCarrierMilliSecond             timeHysteresis;
  TAntennaCarrierOneHundredthOf_dBm      lowerThreshold;
}SAntennaCarrierPowerEventB;

typedef struct
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  TAntennaCarrierMilliSecond             maxRisingTime;
  TAntennaCarrierOneHundredthOf_dB       changeThreshold;
}SAntennaCarrierPowerEventC;

typedef struct
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  TAntennaCarrierMilliSecond             maxFallingTime;
  TAntennaCarrierOneHundredthOf_dB       changeThreshold;
}SAntennaCarrierPowerEventD;

typedef struct
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  TAntennaCarrierMilliSecond             timeHysteresis;
  TAntennaCarrierOneHundredthOf_dBm      upperThreshold;
  TAntennaCarrierOneHundredthOf_dBm      lowerThreshold;
  TAntennaCarrierMilliSecond             timePeriod;
}SAntennaCarrierPowerEventE;

typedef struct
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  TAntennaCarrierMilliSecond             timeHysteresis;
  TAntennaCarrierOneHundredthOf_dBm      upperThreshold;
  TAntennaCarrierOneHundredthOf_dBm      lowerThreshold;
  TAntennaCarrierMilliSecond             timePeriod;
}SAntennaCarrierPowerEventF;

typedef union
{
  EAntennaCarrierPowerEventDiscriminator discriminator;
  SAntennaCarrierPowerEventPeriodic      periodic;
  SAntennaCarrierPowerEventA             eventA;
  SAntennaCarrierPowerEventB             eventB;
  SAntennaCarrierPowerEventC             eventC;
  SAntennaCarrierPowerEventD             eventD;
  SAntennaCarrierPowerEventE             eventE;
  SAntennaCarrierPowerEventF             eventF;
}UAntennaCarrierPowerEventCharacteristics;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ANTENNACARRIERPOWER_H */

/**
*******************************************************************************
* Description         : Power Events in Antenna Carrier API.
*
* Standard Notation   : -
*
* Reference           : RF Related SW Interface Specification.
*
* Parameters          : -
*
* Additional Information : -
*
* Definition Provided by : Platform/Trawler
*
* Remember to put an empty line in the end of each definition file.
* Otherwise the compiler will generate a warning.
******************************************************************************/
