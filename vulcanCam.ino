boolean debug=false;

#include "MLX90640.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"
#include "WEBSOCKET.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initWEBSOCKET();
  initMLX90640(); }

void loop() { httpWorker(); dnsWorker(); websocketWorker(); }
