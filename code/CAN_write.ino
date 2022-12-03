#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

//Defining pins for ultrasonic sensor
int trigger_pin = 4;
int echo_pin = 3;

long duration;
int distance;


void setup() {
  //initializing the Ultrasonic sensor
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  //initializing baud rate for serial communication
  while (!Serial);
  Serial.begin(115200);

  //initializing CAN-Bus
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() 
{
  //reading and calculating the distance from sensor
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);


  //creating a CAN frame to be sent
  canMsg1.can_id  = 0x0F6; //message id
  canMsg1.can_dlc = 8; //setting data length
  canMsg1.data[0] = distance; //distance data from sensor....rest of the bits are set to 0
  canMsg1.data[1] = 0x00;
  canMsg1.data[2] = 0x00;
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = 0x00;

  //sending CAN message
  mcp2515.sendMessage(&canMsg1);
  Serial.println("Messages sent");
  
  delay(100);
}
