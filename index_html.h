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
html   { font-family:Arial; }
div    { background-color:#888888; color:#ffffff; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
.x0a   { background-color:#C0A0A0; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#C0A0A0; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#C0A0A0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1    { background-color:#A0B0C0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#888888; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#888888; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#888888; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function vulcanCaminit() {
  ajaxObj=[]; blur=10; setBlur(); openStream();
  doDisplay(); }
  
function doDisplay() {
  document.getElementById('blurBtn').innerHTML="Blur: "+blur+" Pixel"; }

function decBlur() { blur-=5; doRange(true); }
function incBlur() { blur+=5; doRange(true); }
function setBlur() { document.getElementById('camFrame').style="filter:blur("+blur+"px);"; }
function openStream() { stream=new WebSocket("ws://"+window.location.hostname+":81"); stream.binaryType="arraybuffer"; stream.onmessage=streamMessage; }
function reopenStream() { if (stream.readyState==3) { openStream(); } }
function closeStream() { stream.close(); }

function doRange(doSet) {
  if (blur<0) {blur=0; }
  if (blur>30) {blur=30; }
  if (doSet) { setBlur(); }
  doDisplay(); }

function streamMessage(event) {
  temps=new Float32Array(event.data); minTemp=1000; maxTemp=0;
  for (x=0;x<32*24;x++) { if (temps[x]<minTemp) { minTemp=temps[x]; } else if (temps[x]>maxTemp) { maxTemp=temps[x]; } }
  document.getElementById('minTemp').innerHTML="Min: "+Math.round(minTemp*100)/100+" &#176;";
  document.getElementById('maxTemp').innerHTML="Max: "+Math.round(maxTemp*100)/100+" &#176;";
  camFrame=document.getElementById('camFrame').getContext('2d');
  for (y=0;y<24;y++) { for (x=0;x<32;x++) {
    temp=temps[y*32+(31-x)]*1;
    hue=mapValue(temp,minTemp,maxTemp,240,420);
    light=mapValue(temp,minTemp,maxTemp,30,60);
    camFrame.fillStyle='hsl('+hue+',70%,'+light+'%)';
    camFrame.fillRect(x*20,y*20,20,20); } } }

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
<div><div class="x1"><canvas id="camFrame" width="640px" height="480px"></canvas></div></div>
<div><div class="x3" id="blurBtn"></div>
     <div class="x3" onclick="decBlur();">&#8722;</div>
     <div class="x3" onclick="incBlur();">+</div></div>
<div><div class="x2" onclick="closeStream();">Stop</div>
     <div class="x2" onclick="reopenStream();">Start</div></div>
<div><div class="x2" id="minTemp"></div>
     <div class="x2" id="maxTemp"></div></div>
</div>

</body></html>

)";
