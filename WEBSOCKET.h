#include <WebSocketsServer.h>

WebSocketsServer stream=WebSocketsServer(81);

unsigned long timeMark=millis()+100;

void streamEvent(uint8_t num,WStype_t type,uint8_t * payload,size_t length) {
  switch(type) {
    case WStype_CONNECTED: { if (debug) { Serial.println(String(stream.connectedClients()) + " Websocket clients connected."); } }
    case WStype_DISCONNECTED: { if (debug) { Serial.println(String(stream.connectedClients()) + " Websocket clients connected."); } }
    case WStype_TEXT: { }
    case WStype_BIN: { }
    case WStype_ERROR: { } } }

void initWEBSOCKET() {
  stream.begin();
  stream.onEvent(streamEvent); }

void websocketWorker() {
  stream.loop(); if (millis()>=timeMark) { timeMark=millis()+200;
    if (stream.connectedClients()>0) { getFrame(); stream.broadcastBIN((byte*)frameBuffer,32*24*4); } } }
