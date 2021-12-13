char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>vulcanCam - IR Camera</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/vulcanCam">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html      { font-family:Arial; }
div       { background-color:#888888; color:#ffffff; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
.x0a      { background-color:#C0A0A0; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b      { background-color:#C0A0A0; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0       { background-color:#C0A0A0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1       { background-color:#A0B0C0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2       { background-color:#888888; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3       { background-color:#888888; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4       { background-color:#888888; padding:0.3em 0em; width:24%; font-size:1.4em; }
#camFrame { display:none; }
</style>
<script>

function vulcanCaminit() { ajaxObj=[]; doPrepareLegend(); shot=0; openStream(); }

function doDisplay() { }

function scaleSmooth() { document.getElementById('scaleFrame').style="image-rendering:auto;"; }
function scalePixelated() { document.getElementById('scaleFrame').style="image-rendering:pixelated;"; }
function doShot(count) { closeStream(); shot=count; shotCount=0; openStream(); }
function openStream() { stream=new WebSocket("ws://"+window.location.hostname+":81"); stream.binaryType="arraybuffer"; stream.onmessage=streamMessage; }
function reopenStream() { shot=0; if (stream.readyState==3) { openStream(); } }
function closeStream() { stream.close(); }

function doRange(doSet) { }

function streamMessage(event) {
  if (shot==0) { temps=new Float32Array(event.data); doDisplayFrame(); doDisplayLegend(); } else {
    if (shotCount==0) { temps=new Float32Array(event.data); shotCount++; } else {
      tempsNew=new Float32Array(event.data); for (x=0;x<32*24;x++) { temps[x]+=tempsNew[x]; } shotCount++;
      if (shotCount==shot) { for (x=0;x<32*24;x++) { temps[x]/=shot; } closeStream(); doDisplayFrame(); doDisplayLegend(); } } } }

function doDisplayFrame() {
  minTemp=1000; maxTemp=0;
  for (x=0;x<32*24;x++) { if (temps[x]<minTemp) { minTemp=temps[x]; } else if (temps[x]>maxTemp) { maxTemp=temps[x]; } }
  camFrame=document.getElementById('camFrame').getContext('2d');
  for (y=0;y<24;y++) { for (x=0;x<32;x++) {
    temp=temps[y*32+(31-x)]*1;
    hue=mapValue(temp,minTemp,maxTemp,240,420);
    light=mapValue(temp,minTemp,maxTemp,30,60);
    camFrame.fillStyle='hsl('+hue+',70%,'+light+'%)';
    camFrame.fillRect(x,y,1,1); } }
  document.getElementById('scaleFrame').src=document.getElementById('camFrame').toDataURL("image/png"); }

function doPrepareLegend() {
  scaleLegend=document.getElementById('scaleLegend').getContext('2d');
  for (y=0;y<480;y++) {
    hue=mapValue(y,0,479,240,420);
    light=mapValue(y,0,479,30,60);
    scaleLegend.fillStyle='hsl('+hue+',70%,'+light+'%)';
    scaleLegend.fillRect(0,y,30,1); } }

function doDisplayLegend() {
  scaleLegend=document.getElementById('scaleLegend').getContext('2d');
  scaleLegend.clearRect(30,0,60,480);
  diff=Math.floor(maxTemp)-Math.ceil(minTemp); step=1; while (diff/step>10) { step++; }
  for (value=Math.ceil(minTemp);value<=Math.floor(maxTemp);value+=step) {
    y=mapValue(value,minTemp,maxTemp,0,479);
    scaleLegend.fillStyle='rgb(0,0,0)';
    scaleLegend.font="20px Arial";
    scaleLegend.fillRect(30,y,10,1);
    scaleLegend.fillText(value+"\u00b0",45,y+7); } }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="xxxx") { } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }

</script></head><body onload="vulcanCaminit();">

<div><div class="x0a">vulcanCam</div></div>
<div><div class="x0b">IR Camera</div></div>

<div class="x1" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x1"><img id="scaleFrame" width="640px" height="480px"></img><canvas id="scaleLegend" width="90px" height="480px"></canvas></div></div>
<div><div class="x2" onclick="scaleSmooth();">Smooth</div>
     <div class="x2" onclick="scalePixelated();">Pixelated</div></div>
<div><div class="x3" onclick="closeStream();">Stop</div>
     <div class="x3" onclick="reopenStream();">Start</div>
     <div class="x3" onclick="doShot(20);">Shot</div></div>
</div>

<canvas id="camFrame" width="32px" height="24px"></canvas>

</body></html>

)";
