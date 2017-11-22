/*
 * LmicWrapper.h
 *
 *  Created on: 31.08.2017
 *      Author: nid
 */

#ifndef LIB_LMIC_WRAPPER_LMICWRAPPER_H_
#define LIB_LMIC_WRAPPER_LMICWRAPPER_H_


#include <Arduino.h>
#include <lmic.h>
#include <hal/hal.h>
#include <Timer.h>

class AirTimerAdapter : public TimerAdapter
{
public:
  void timeExpired();
};

static osjob_t sendjob;

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
extern void os_getArtEui (u1_t* buf);
extern void os_getDevEui (u1_t* buf);
extern void os_getDevKey (u1_t* buf);

void onEvent (ev_t ev);
void do_send(osjob_t* j);
void lmicSetup();
void lmicLoop();

#endif /* LIB_LMIC_WRAPPER_LMICWRAPPER_H_ */
