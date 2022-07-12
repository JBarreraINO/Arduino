/*
 * This file is part of ArduinoIoTBearSSL.
 *
 * Copyright 2019 ARDUINO SA (http://www.arduino.cc/)
 *
 * This software is released under the GNU General Public License version 3,
 * which covers the main part of ArduinoIoTBearSSL.
 * The terms of this license can be found at:
 * https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * You can be released from the requirements of the above licenses by purchasing
 * a commercial license. Buying such a license is mandatory if you want to modify or
 * otherwise use the software for commercial activities involving the Arduino
 * software without disclosing the source code of your own applications. To purchase
 * a commercial license, send an email to license@arduino.cc.
 *
 */

#ifndef _ARDUINO_BEAR_SSL_H_
#define _ARDUINO_BEAR_SSL_H_

#include "BearSSLClient.h"

class ArduinoBearSSLClass {
public:
  ArduinoBearSSLClass();
  virtual ~ArduinoBearSSLClass();

  unsigned long getTime();
  void onGetTime(unsigned long(*)(void));

private:
  unsigned long (*_onGetTimeCallback)(void);
};

extern ArduinoBearSSLClass ArduinoBearSSL;

#endif
