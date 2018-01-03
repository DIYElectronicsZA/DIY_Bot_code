#include <GPD2846.h>

GPD2846 mp3(43, 44, 45); // Arduino pins D2 = S1, D3 = S2, D4 = S3 on MP3 player

void setup() {
  Serial.begin(115200);
}

void loop() {
  checkForSerialCommand();
}

void checkForSerialCommand() {
  char serialCommand=' ';
  if(Serial.available()>0) {
    serialCommand=Serial.read();
    Serial.flush();
  }
  switch(serialCommand) {
    case 'f': // skip forward
      mp3.next();  
      break;
    case 'd': // volume down
      mp3.volumeDown();
      break;
    case 'p': // pause on or off
      mp3.pause();  // could use mp3.play();
      break;
    case 'b': // skip back
      mp3.previous();
      break;
    case 'u': // volume up
      mp3.volumeUp();
      break;
    default:
      break;    
  }
}
