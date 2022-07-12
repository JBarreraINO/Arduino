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

#ifndef _BEAR_SSL_CLIENT_H_
#define _BEAR_SSL_CLIENT_H_

#include <Arduino.h>
#include <Client.h>

#include "bearssl/bearssl.h"

class BearSSLClient : public Client {

public:
  BearSSLClient(Client& client);
  virtual ~BearSSLClient();

  virtual int connect(IPAddress ip, uint16_t port);
  virtual int connect(const char* host, uint16_t port);
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  virtual int available();
  virtual int read();
  virtual int read(uint8_t *buf, size_t size);
  virtual int peek();
  virtual void flush();
  virtual void stop();
  virtual uint8_t connected();
  virtual operator bool();

  using Print::write;

  void setEccSlot(int ecc508KeySlot, const byte cert[], int certLength);

private:
  int connectSSL(const char* host);
  static int clientRead(void *ctx, unsigned char *buf, size_t len);
  static int clientWrite(void *ctx, const unsigned char *buf, size_t len);

private:
  Client* _client;
  br_ec_private_key _ecKey;
  br_x509_certificate _ecCert;

  br_ssl_client_context _sc;
  br_x509_minimal_context _xc;
  unsigned char _iobuf[8192 + 85 + 325];
  br_sslio_context _ioc;
};

#endif
