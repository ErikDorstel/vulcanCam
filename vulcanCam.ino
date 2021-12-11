boolean debug=false;

#include "MLX90640.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initMLX90640(); }

void loop() { httpWorker(); dnsWorker(); }
