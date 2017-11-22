/*
 * LmicWrapper.cpp
 *
 *  Created on: 31.08.2017
 *      Author: nid
 */

#include <LoRaTxData.h>
#include <LmicWrapper.h>

void AirTimerAdapter::timeExpired()
{
  lmicLoop();
}

// MIT License
// https://github.com/gonzalocasas/arduino-uno-dragino-lorawan/blob/master/LICENSE
// Based on examples from https://github.com/matthijskooijman/arduino-lmic
// Copyright (c) 2015 Thomas Telkamp and Matthijs Kooijman

// Mixed with code from https://github.com/waagsociety/air_quality_sensor_kit
// Adaptions: Andreas Spiess, Dieter Niklaus

uint8_t NWKSKEY[] = { 0x0A, 0x50, 0x2A, 0x05, 0x2B, 0x05, 0x5D, 0x6E, 0x16, 0x76, 0x3B, 0xA8, 0x07, 0xC9, 0xEC, 0x5B };
uint8_t APPSKEY[] = { 0x14, 0x51, 0x6D, 0xA8, 0x09, 0x31, 0xC6, 0x2A, 0x44, 0x26, 0x28, 0x02, 0x1E, 0x4A, 0xDC, 0xC5 };
const long int DEVADDR = 0x2601103C;

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned int TX_INTERVAL = 60; // 1 min

// Payload to send (uplink)
const int cMsgSize = LoRaTxData::c_LoRaTxDataSize;
unsigned char* message;

// Pin mapping
#if defined (ARDUINO_ARCH_SAMD) && defined (__SAMD21G18A__) // Adafruit Feather M0 (LoRa)
const lmic_pinmap lmic_pins = {
  .nss = 8,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 4,
  .dio = {3, 6, LMIC_UNUSED_PIN},
};
#else
// Pin mapping Dragino Shield
const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 9,
  .dio = {2, 6, 7},
};
#endif

void onEvent (ev_t ev)
{
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      break;
    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      break;
    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      break;
    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      break;
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      break;
    case EV_RFU1:
      Serial.println(F("EV_RFU1"));
      break;
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      break;
    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      if (LMIC.dataLen)
	    {
        // data received in rx slot after tx
        Serial.print("Data Received: ");
        Serial.write(LMIC.frame + LMIC.dataBeg, LMIC.dataLen);
        Serial.println();
      }
      // Schedule next transmission
      os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
      break;
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      break;
    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      break;
    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      break;
    default:
      Serial.println(F("Unknown event"));
      break;
  }
}

void do_send(osjob_t* j)
{
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND)
  {
    Serial.println("OP_TXRXPEND, not sending");
  } 
  else
  {
    LoRaTxData::Instance()->updateTxData(message, cMsgSize);

    LMIC_setTxData2(1, message, cMsgSize, 0);

    Serial.println("Sending uplink packet...");

    Serial.print("Size of the message: ");
    Serial.println(cMsgSize);
    for (unsigned int i = 0; i < cMsgSize; i++)
    {
      Serial.print("message[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.println(message[i]);
    }
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

void lmicSetup()
{
  new Timer(new AirTimerAdapter(), Timer::IS_RECURRING, 1000);

  // LMIC init
  os_init();

  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();

  // Set static session parameters.
  LMIC_setSession(0x1, DEVADDR, NWKSKEY, APPSKEY);

  // Set up the channels used by the Things Network, which corresponds
  // to the defaults of most gateways. Without this, only three base
  // channels from the LoRaWAN specification are used, which certainly
  // works, so it is good for debugging, but can overload those
  // frequencies, so be sure to configure the full frequency range of
  // your network here (unless your network autoconfigures them).
  // Setting up channels should happen after LMIC_setSession, as that
  // configures the minimal channel set.
  LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
  LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
  // TTN defines an additional channel at 869.525Mhz using SF9 for class B
  // devices' ping slots. LMIC does not have an easy way to define set this
  // frequency and support for class B is spotty and untested, so this
  // frequency is not configured here.

  // Disable link check validation
  LMIC_setLinkCheckMode(0);

  // TTN uses SF9 for its RX2 window.
  LMIC.dn2Dr = DR_SF9;

  // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
  LMIC_setDrTxpow(DR_SF7, 14);

#if 0
  for (int i=1; i<=8; i++)
  {
    LMIC_disableChannel(i);
  }
#endif

  // Start job
  do_send(&sendjob);
}

void lmicLoop()
{
  os_runloop_once();
}
