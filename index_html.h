const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>vulcanCam - IR Camera</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/vulcanCam">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html    { font-family:Arial; }
div     { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
.x0a    { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b    { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0     { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1     { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a    { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2     { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3     { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4     { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
.hidden { display:none; }
</style>
<script>

function vulcanCaminit() {
  ajaxObj=[]; appName="&nbsp;"; appDesc="&nbsp;"; requestAJAX('appName');
  setSmooth(); openStream(0); window.setInterval("checkStream();",5000); }

function doDisplay() { }

function openStream(count) { shot=count; shotCount=0;
  doPrepareLegend(); stream=new WebSocket("ws://"+window.location.hostname+":81");
  stream.binaryType="arraybuffer"; stream.onmessage=streamMessage; stream.heartbeat=0; id("stopBtn").style.color="#f0f0f0";
  if (shot==0) { id("runBtn").style.color="#000000"; id("shotBtn").style.color="#f0f0f0"; } else { id("shotBtn").style.color="#000000"; } }

function reopenStream(count) { closeStream(); openStream(count); }

function closeStream() { stream.close(); shot=-1;
  id("stopBtn").style.color="black"; id("runBtn").style.color="#f0f0f0"; id("shotBtn").style.color="#f0f0f0"; }

function checkStream() { if (shot>=0 && stream.heartbeat==0) { stream.close(); openStream(shot); } else { stream.heartbeat=0; } }

function setSmooth() { id("scaledFrame").style="image-rendering:auto;";
  id("smoothBtn").style.color="#000000"; id("pixelatedBtn").style.color="#f0f0f0"; }

function setPixelated() { id("scaledFrame").style="image-rendering:pixelated;";
  id("smoothBtn").style.color="#f0f0f0"; id("pixelatedBtn").style.color="#000000"; }

function doRange(doSet) { }

function streamMessage(event) { stream.heartbeat++;
  if (shot==0) { temps=new Float32Array(event.data); doDisplayFrame(); doDisplayLegend(); }
  else { if (shotCount==0) { temps=new Float32Array(event.data); shotCount++; }
    else { tempsNew=new Float32Array(event.data); for (x=0;x<32*24;x++) { temps[x]+=tempsNew[x]; } shotCount++;
      if (shotCount==shot) { for (x=0;x<32*24;x++) { temps[x]/=shot; } closeStream(); doDisplayFrame(); doDisplayLegend(); } } } }

function doPrepareLegend() {
  scaledLegend=id('scaledLegend').getContext('2d');
  for (y=0;y<480;y++) {
    hue=mapValue(y,0,479,240,420);
    light=mapValue(y,0,479,30,60);
    scaledLegend.fillStyle='hsl('+hue+',70%,'+light+'%)';
    scaledLegend.fillRect(0,y,30,1); } }

function doDisplayFrame() {
  minTemp=1000; maxTemp=0;
  for (x=0;x<32*24;x++) { if (temps[x]<minTemp) { minTemp=temps[x]; } else if (temps[x]>maxTemp) { maxTemp=temps[x]; } }
  camFrame=id('camFrame').getContext('2d');
  for (y=0;y<24;y++) { for (x=0;x<32;x++) {
    temp=temps[y*32+(31-x)];
    hue=mapValue(temp,minTemp,maxTemp,240,420);
    light=mapValue(temp,minTemp,maxTemp,30,60);
    camFrame.fillStyle='hsl('+hue+',70%,'+light+'%)';
    camFrame.fillRect(x,y,1,1); } }
  id('scaledFrame').src=id('camFrame').toDataURL("image/png"); }

function doDisplayLegend() {
  scaledLegend=id('scaledLegend').getContext('2d');
  scaledLegend.clearRect(30,0,60,480);
  diff=Math.floor(maxTemp)-Math.ceil(minTemp); step=1; while (diff/step>10) { step++; }
  for (value=Math.ceil(minTemp);value<=Math.floor(maxTemp);value+=step) {
    y=mapValue(value,minTemp,maxTemp,0,479);
    scaledLegend.fillStyle='rgb(0,0,0)';
    scaledLegend.font="20px Arial";
    scaledLegend.fillRect(30,y,10,1);
    scaledLegend.fillText(value+"\u00b0",45,y+7); } }

function doDisplayTemp(event) { if (stream.readyState==3) {
  doPrepareLegend(); scaledFrame=id('scaledFrame');
  x=Math.floor((event.clientX-scaledFrame.getBoundingClientRect().left)/20);
  y=Math.floor((event.clientY-scaledFrame.getBoundingClientRect().top)/20);
  temp=temps[y*32+(31-x)]; y=mapValue(temp,minTemp,maxTemp,0,479);
  scaledLegend=id('scaledLegend').getContext('2d');
  scaledLegend.fillStyle='rgb(200,200,200)';
  scaledLegend.fillRect(0,y-5,30,11);
  scaledLegend.fillStyle='rgb(0,0,0)';
  scaledLegend.fillRect(0,y,30,1); } }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="foo") { } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="vulcanCaminit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1a" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x1"><img id="scaledFrame" onclick="doDisplayTemp(event);" width="640px" height="480px"></img><canvas id="scaledLegend" width="90px" height="480px"></canvas></div></div>
<div><div class="x2" id="smoothBtn" onclick="setSmooth();">Smooth</div>
     <div class="x2" id="pixelatedBtn" onclick="setPixelated();">Pixelated</div></div>
<div><div class="x3" id="stopBtn" onclick="closeStream();">Stop</div>
     <div class="x3" id="runBtn" onclick="reopenStream(0);">Run</div>
     <div class="x3" id="shotBtn" onclick="reopenStream(20);">Shot</div></div>
</div>

<canvas class="hidden" id="camFrame" width="32px" height="24px"></canvas>

</body></html>

)";
