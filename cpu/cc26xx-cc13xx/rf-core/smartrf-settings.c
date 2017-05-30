/*
 * Copyright (c) 2015, Texas Instruments Incorporated - http://www.ti.com/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*---------------------------------------------------------------------------*/
#include "rf-core/api/mailbox.h"
#include "rf-core/api/common_cmd.h"
#include "rf-core/api/prop_cmd.h"
/*---------------------------------------------------------------------------*/
/* Overrides for CMD_PROP_RADIO_DIV_SETUP */
uint32_t overrides[] =
{
  /* override_synth.xml */
  HW32_ARRAY_OVERRIDE(0x6088, 1),
  (uint32_t)0x0000001A,
  ADI_HALFREG_OVERRIDE(0, 61, 0xF, 0xD),
  HW32_ARRAY_OVERRIDE(0x4038, 1),
  (uint32_t)0x0000003A,
  HW_REG_OVERRIDE(0x4020, 0x7F00),
  HW_REG_OVERRIDE(0x4064, 0x0040),
  (uint32_t)0x684A3,
  (uint32_t)0xC0040141,
  (uint32_t)0x0533B107,
  (uint32_t)0xA480583,
  (uint32_t)0x7AB80603,
  ADI_REG_OVERRIDE(1, 4, 0x1F),
  ADI_HALFREG_OVERRIDE(1, 7, 0x4, 0x4),
  HW_REG_OVERRIDE(0x6084, 0x35F1),
  (uint32_t)0x00038883,
  (uint32_t)0x00FB88A3,
  /* TX power override */
  ADI_REG_OVERRIDE(0, 12, 0xF9),

  /* Overrides for CRC16 functionality */
  (uint32_t)0x943,
  (uint32_t)0x963,

  (uint32_t)0xFFFFFFFF,
};
/*---------------------------------------------------------------------------*/
/* CMD_PROP_RADIO_DIV_SETUP */
rfc_CMD_PROP_RADIO_DIV_SETUP_t smartrf_settings_cmd_prop_radio_div_setup =
{
    .commandNo = 0x3807,
    .status = 0x0000,
    .pNextOp = 0, /*INSERT APPLICABLE POINTER: (uint8_t*)&xxx */
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .modulation.modType = 0x1,
    .modulation.deviation = 0x64,
    .symbolRate.preScale = 0xf,
    .symbolRate.rateWord = 0x8000,
    .symbolRate.bPdifDecim = 0x0,
    .symbolRate.pdifDecim = 0x0,
    .rxBw = 0x02,
    .preamConf.nPreamBytes = 0x4,
    .preamConf.preamMode = 0x0,
    .formatConf.nSwBits = 0x20,
    .formatConf.bBitReversal = 0x0,
    .formatConf.bMsbFirst = 0x1,
    .formatConf.fecMode = 0x0,
    .formatConf.bDigitalAgc = 0x0,
    
    /*7: .4g mode with dynamic whitening and CRC choice*/
    .formatConf.whitenMode = 0x7,
    .config.frontEndMode = 0x0,
    .config.biasMode = 0x1,
    .config.bNoAdi0Setup = 0x0,
    .config.bNoAdi0Trim = 0x0,
    .config.bNoAdi0Ovr = 0x0,
    .config.bNoAdi1Setup = 0x0,
    .config.bNoAdi1Trim = 0x0,
    .config.bNoAdi1Ovr = 0x0,
    .config.bNoFsPowerUp = 0x0,
    //.config.lnaIbBoost = 0x0,
    //.txPower.IB = 0x3f,
    //.txPower.GC = 0x0,
    //.txPower.boost = 0x0,
    //.txPower.tempCoeff = 0x0,
    .txPower=0xa73f,
    .pRegOverride = overrides,
    .centerFreq = 0x01b1,
    .intFreq = 0x8000,
    .loDivider = 0x0a,
};
/*---------------------------------------------------------------------------*/
/* CMD_FS */
rfc_CMD_FS_t smartrf_settings_cmd_fs =
{
    .commandNo = 0x0803,
    .status = 0x0000,
    .pNextOp = 0, /*INSERT APPLICABLE POINTER: (uint8_t*)&xxx */
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .frequency = 0x01b1,
    .fractFreq = 0x0000,
    .synthConf.bTxMode = 0x0,
    .synthConf.refFreq = 0x0,
    //.calibConf.bOverrideCalib = 0x0,
    //.calibConf.bSkipTdcCalib = 0x0,
    //.calibConf.bSkipCoarseCalib = 0x0,
    //.calibConf.bSkipMidCalib = 0x0,
    //.calibConf.coarsePrecal = 0x0,
    .midPrecal = 0x00,
    .ktPrecal = 0x00,
    .tdcPrecal = 0x0000,
};
/*---------------------------------------------------------------------------*/
/* CMD_PROP_TX_ADV */
rfc_CMD_PROP_TX_ADV_t smartrf_settings_cmd_prop_tx_adv =
{
  .commandNo = 0x3803,
  .status = 0x0000,
  .pNextOp = 0,/*INSERT APPLICABLE POINTER: (uint8_t*)&xxx */
  .startTime = 0x00000000,
  .startTrigger.triggerType = 0x0,
  .startTrigger.bEnaCmd = 0x0,
  .startTrigger.triggerNo = 0x0,
  .startTrigger.pastTrig = 0x0,
  .condition.rule = 0x1,
  .condition.nSkip = 0x0,
  .pktConf.bFsOff = 0x0,
  .pktConf.bUseCrc = 0x1,//
  .pktConf.bCrcIncSw = 0x0, /* .4g mode */
  .pktConf.bCrcIncHdr = 0x0, /* .4g mode */
  .numHdrBits = 0x10 /* 16: .4g mode */,
  .pktLen = 0x0000,
  .startConf.bExtTxTrig = 0x0,
  .startConf.inputMode = 0x0,
  .startConf.source = 0x0,
  .preTrigger.triggerType = TRIG_REL_START,
  .preTrigger.bEnaCmd = 0x0,
  .preTrigger.triggerNo = 0x0,
  .preTrigger.pastTrig = 0x1,//Never (except possibly by CMD_TRIGGER if bEnaCmd = 1)
  .preTime = 0x00000000,
  .syncWord = 0x930b51de,//发送和接收必须相同
  .pPkt = 0,/*INSERT APPLICABLE POINTER: (uint8_t*)&xxx */
};
/*---------------------------------------------------------------------------*/
/* CMD_PROP_RX_ADV */
rfc_CMD_PROP_RX_ADV_t smartrf_settings_cmd_prop_rx_adv =
{
  .commandNo = 0x3804,
  .status = 0x0000,
  .pNextOp = 0,
  .startTime = 0x00000000,
  .startTrigger.triggerType = 0x0,
  .startTrigger.bEnaCmd = 0x0,
  .startTrigger.triggerNo = 0x0,
  .startTrigger.pastTrig = 0x0,
  .condition.rule = 0x1,
  .condition.nSkip = 0x0,
  .pktConf.bFsOff = 0x0,
  .pktConf.bRepeatOk = 0x1,//
  .pktConf.bRepeatNok = 0x1,//
  .pktConf.bUseCrc = 0x1,//发送用了CRC32
  .pktConf.bCrcIncSw = 0x0, /* .4g mode */
  .pktConf.bCrcIncHdr = 0x0, /* .4g mode */
  .pktConf.endType = 0x0,
  .pktConf.filterOp = 0x1,//可以０，也可以是１，默认１
  .rxConf.bAutoFlushIgnored = 0x1,//
  .rxConf.bAutoFlushCrcErr = 0x1,//
  .rxConf.bIncludeHdr = 0x0,
  .rxConf.bIncludeCrc = 0x0,
  .rxConf.bAppendRssi = 0x1,
  .rxConf.bAppendTimestamp = 0x0,
  .rxConf.bAppendStatus = 0x1,
  .syncWord0 = 0x930b51de,//发送和接收必须相同
  .syncWord1 = 0x00000000,
  .maxPktLen = 0x0000, /* To be populated by the driver. */
  .hdrConf.numHdrBits = 0x10, /* 16: .4g mode */
  .hdrConf.lenPos = 0x0, /* .4g mode */
  .hdrConf.numLenBits = 0x0B, /* 11 = 0x0B .4g mode */
  .addrConf.addrType = 0x0,
  .addrConf.addrSize = 0x0,
  .addrConf.addrPos = 0x0,
  .addrConf.numAddr = 0x0,
  .lenOffset = -4, /* .4g mode */
  .endTrigger.triggerType = TRIG_NEVER,
  .endTrigger.bEnaCmd = 0x0,
  .endTrigger.triggerNo = 0x0,
  .endTrigger.pastTrig = 0x0,
  .endTime = 0x00000000,
  .pAddr = 0,/*INSERT APPLICABLE POINTER: (uint8_t*)&xxx */
  .pQueue = 0,/*INSERT APPLICABLE POINTER: (dataQueue_t*)&xxx */
  .pOutput = 0,/*INSERT APPLICABLE POINTER: (uint8_t*)&xxx */
};
/*---------------------------------------------------------------------------*/
