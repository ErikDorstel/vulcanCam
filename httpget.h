String httpget(String request) {
  String response="";

  // vulcanCam specific pages

  if (request.indexOf("/getFrame")>=0) { getFrame(); float maxTemp=0; float minTemp=1000;
    for (int x=0;x<32*24;x++) { response+=String(frameBuffer[x]) + ",";
      if (frameBuffer[x]<minTemp) { minTemp=frameBuffer[x]; }
      else if (frameBuffer[x]>maxTemp) { maxTemp=frameBuffer[x]; } }
    response+=String(minTemp) + "," + String(maxTemp) + ","; }

  // WLAN Choose specific pages

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (statusStation==true) { response="<div class=\"x1\">WLAN AP " + ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) { response=a2h(ssidStation) + "," + a2h(passwordStation) + ","; }

  else if (request.indexOf("/scanAP")>=0) {
    int indexes=WiFi.scanNetworks(); for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<div class=\"x1\" onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</div>"; } } }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    ssidStation=h2a(request.substring(a,b-1)); passwordStation=h2a(request.substring(b));
    reconnectWLAN(); }

  // Default page

  else { response=index_html; }

  return response; }
