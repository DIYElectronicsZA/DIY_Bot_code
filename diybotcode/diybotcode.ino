#include <LEDMatrixDriver.hpp>
#include <Servo.h>

// This draw a moving sprite on your LED matrix using the hardware SPI driver Library by Bartosz Bielawski.
// Example written 16.06.2017 by Marko Oette, www.oette.info 

// Define the ChipSelect pin for the led matrix (Dont use the SS or MISO pin of your Arduino!)
// Other pins are arduino specific SPI pins (MOSI=DIN of the LEDMatrix and CLK) see https://www.arduino.cc/en/Reference/SPI
int skip = 43
int playpause = 44
int backwards = 45
//Pins for wheels and TB6612
int STBY = 18; //standby

//Motor A
int PWMA = 21; //Speed control
int AIN1 = 20; //Direction
int AIN2 = 19; //Direction

//Motor B
int PWMB = 15; //Speed control
int BIN1 = 16; //Direction
int BIN2 = 17; //Direction

//Pins for Eyes
const uint8_t LEDMATRIX_CS_PIN = 53;

// Define LED Matrix dimensions (0-n) - eg: 32x8 = 31x7
const int LEDMATRIX_WIDTH = 7;  
const int LEDMATRIX_HEIGHT = 7;
const int LEDMATRIX_SEGMENTS = 2;
// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

Servo servoAL;
Servo servoAR;
Servo servoHX;
Servo servoHY;
Servo servoHZ;

void setup() {

  pinMode(skip, OUTPUT);
  pinMode(playpause, OUTPUT);
  pinMode(backwards, OUTPUT);

  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  // init the display
  lmd.setEnabled(true);
  lmd.setIntensity(4);   // 0 = low, 10 = high

  servoAL.attach(9);
  servoAR.attach(7);
  servoHX.attach(10);
  servoHY.attach(11);
  servoHZ.attach(8);
  servoAL.write(90);
  servoAR.write(90);
  servoHX.write(90);
  servoHY.write(90);
  servoHZ.write(90);

  Serial.begin(115200);
}

int x=-1, y=0;   // start top left
bool s = true;  // start with led on

byte a[8]={ B00001100,         // Fully open eye
            B00011110,
            B00110011,
            B00110011,
            B00110011,
            B00110011,
            B00011110,
            B00001110};

byte b[8]={ B00000000,
            B00011110,
            B00110011,
            B00110011,
            B00110011,
            B00110011,
            B00010011,
            B00001110};

byte c[8]={ B00000000,
            B00000000,
            B00011110,
            B00111111,
            B00110011,
            B00110011,
            B00011110,
            B00000000};

byte d[8]={ B00000000,
            B00000000,
            B00000000,
            B00011110,
            B00111111,
            B00110011,
            B00001100,
            B00000000};

byte e[8]={ B00000000,         // Fully closed eye
            B00000000,
            B00000000,
            B00000000,
            B00000000,
            B00111111,
            B00000000,
            B00000000};

byte f[8]={ B00000000,         // Fully closed eye
            B00000000,
            B00000000,
            B00000000,
            B00001100,
            B00010010,
            B00000000,
            B00000000};

byte g[8]={ B00011000,        
            B00111100,
            B01100110,
            B01100110,
            B01100110,
            B01100110,
            B00111100,
            B00011000};

byte h[8]={ B00000000,
            B00011000,
            B01100110,
            B01100110,
            B01100110,
            B01100110,
            B00111100,
            B00011000};
            
byte i[8]={ B00000000,
            B00000000,
            B00111111,
            B00110011,
            B00110011,
            B00110011,
            B00111110,
            B00001100};

byte j[8]={ B00000000,
            B00000000,
            B00011111,
            B00011001,
            B00011001,
            B00011001,
            B00011110,
            B00001100};

byte k[8]={ B00000000,
            B00000110,
            B00011101,
            B00011101,
            B00011101,
            B00011101,
            B00011110,
            B00001100};

byte l[8]={ B00000000,
            B00000111,
            B00011101,
            B00011001,
            B00010011,
            B00011011,
            B00011110,
            B00000000};

byte m[8]={ B00001111,
            B00001011,
            B00001001,
            B00011011,
            B00011111,
            B00001111,
            B00000000,
            B00000000};


byte n[8]={ B00111111,
            B00110011,
            B00010001,
            B00011011,
            B00011111,
            B00000000,
            B00000000,
            B00000000};



const int ANIM_DELAY = 100;
const int ROLL_DELAY = 100;


void loop() {
  move(1, 255, 1); //motor 1, full speed, left
  move(2, 128, 0); //motor 2, half speed, right

 delay(1000);
 stop();
  blink_eyes();
  servoAL.write(90);
  servoAR.write(90);
  servoHX.write(80);
  servoHY.write(80);
  servoHZ.write(80);
  arm_move();
  delay(200);
  roll_eyes();
  servoAL.write(180);
  servoAR.write(-180);
  servoHY.write(110);
  servoHZ.write(110);
  servoHX.write(110);
  delay(200);
  servoAL.write(90);
  move(1, 255, 1); //motor 1, full speed, left
  move(2, 255, 1); //motor 2, full speed, left
  
  delay(1000); //go for 1 second
  stop(); //stop
  delay(250); //hold for 250ms until move again
  
  move(1, 128, 0); //motor 1, half speed, right
  move(2, 128, 0); //motor 2, half speed, right
  
  delay(1000);
  stop();
  delay(250);
  wink();
  arm_move();
  delay(2000);
  servoAL.write(180);
  servoHX.write(90);
  servoHY.write(90);
  servoHZ.write(90);




}// main loop end

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

digitalWrite(STBY, HIGH); //disable standby

boolean inPin1 = LOW;
boolean inPin2 = HIGH;

if(direction == 1){
inPin1 = HIGH;
inPin2 = LOW;
}

if(motor == 1){
digitalWrite(AIN1, inPin1);
digitalWrite(AIN2, inPin2);
analogWrite(PWMA, speed);
}else{
digitalWrite(BIN1, inPin1);
digitalWrite(BIN2, inPin2);
analogWrite(PWMB, speed);
}
}

void stop(){
//enable standby
digitalWrite(STBY, LOW);
}

void arm_move() {
  
  if(Serial.available()){
    char in = Serial.read();
    int pos = Serial.parseInt();
    
    switch(in)
    {
      case 'a':
        servoAL.write(pos);
        Serial.print("AL: ");
        Serial.println(pos);
        break;
      case 'b':
        servoAR.write(pos);
        Serial.print("AR: ");
        Serial.println(pos);
        break;
      case 'c':
        servoHX.write(pos);
        Serial.print("HX: ");
        Serial.println(pos);
        break;
      case 'd':
        servoHY.write(pos);
        Serial.print("HY: ");
        Serial.println(pos);
        break;
      case 'e':
        servoHZ.write(pos);
        Serial.print("HZ: ");
        Serial.println(pos);
        break;
      case 'r':
        servoAL.attach(9);
        servoAR.attach(7);
        servoHX.attach(10);
        servoHY.attach(11);
        servoHZ.attach(8);
        servoAL.write(90);
        servoAR.write(90);
        servoHX.write(90);
        servoHY.write(90);
        servoHZ.write(90);
        Serial.print("Reset");
        break;   
      case 's':
        servoAL.detach();
        servoAR.detach();
        servoHX.detach();
        servoHY.detach();
        servoHZ.detach();
        Serial.print("Stopped");
        break;         
                                
    }
  
  }
}
void wink() {

  drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
  drawSprite( (byte*)&a, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ANIM_DELAY);

 drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
 drawSprite( (byte*)&b, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&c, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&d, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&e, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&f, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&c, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&a, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

}

void roll_eyes(){

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&a, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);
    
    drawSprite( (byte*)&g, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&g, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&h, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&h, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&i, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&i, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&j, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&j, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&k, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&k, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&l, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&l, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&m, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&m, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&n, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&n, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&g, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&g, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&a, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ROLL_DELAY);
}

void blink_eyes(){
  
  for(int cici = 0 ; cici<2; cici++){

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&a, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ANIM_DELAY);
  
    lmd.clear();
    drawSprite( (byte*)&b, x, 0, 8, 8,0 );
    drawSprite( (byte*)&b, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ANIM_DELAY);
  
    lmd.clear();
    drawSprite( (byte*)&c, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&c, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ANIM_DELAY);
  
    lmd.clear();
    drawSprite( (byte*)&d, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&d, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ANIM_DELAY);
  
    lmd.clear();
    drawSprite( (byte*)&e, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&e, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ANIM_DELAY);

    lmd.clear();
    drawSprite( (byte*)&f, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&f, x, 0, 8, 8, 1 );
    lmd.display();
    delay(200);

    drawSprite( (byte*)&a, x, 0, 8, 8, 0 );
    drawSprite( (byte*)&a, x, 0, 8, 8, 1 );
    lmd.display();
    delay(ANIM_DELAY);

  }
}

void drawSprite( byte* sprite, int x, int y, int width, int height, int seg )
{
  byte mask = B10000000;
  for( int iy = 0; iy < height; iy++ )
  {
    for( int ix = 0; ix < width; ix++ )
    {
      lmd.setPixel(x + ix +(8*seg), y + iy, (bool)(sprite[iy] & mask ));
      mask = mask >> 1;
    }
    mask = B10000000;
  }
}


