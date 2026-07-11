<p style="font-family: 'Courier New', Courier, monospace;">Simple arduino library for implementing basic aliexpress/amazon encoders.<br><br>
To use, place the dorianEncoderSimple2 folder into your arduino folder<br><br>
10nf or similar capacitors are required on both encoder pins.<br><br>
hardwaredebounce>softwaredebounce I will fight you on this.<br><br>
Built and tested on esp32-s3<br><br>

/* ENCODER PHASE DIAGRAM<br>
  _v__  _v__<br>
  |' |  |' |<br>
__|' |__|' |__        v<br>
 __'_  __'_       (stop detent)<br>
 | '|  | '|           ^<br>
_| '|__| '|__       the encoder this was written for returns back to the same position each time.<br>
   ^     ^           in other words it steps through all 4 points (phase combinations?) in one rotation step.<br>
<br>*/</p>
