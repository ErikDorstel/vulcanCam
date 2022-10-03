boolean debug=true;

const char* appName="vulcanCam";
const char* appDesc="IR Camera";

#include "MLX90640.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"
#include "WEBSOCKET.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initDNS();
  initHTTP();
  initWEBSOCKET();
  initMLX90640(); }

void loop() { wlanWorker(); httpWorker(); dnsWorker(); websocketWorker(); }
