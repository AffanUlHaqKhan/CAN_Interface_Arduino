#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);


void setup() {
  //initializing communication baud rate
  Serial.begin(115200);

  //initilizing can bus at rate of 125 KBPS. Higher speeds dosent seem to work with
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
}

void loop() {
  //if message exists and there is no error then read the data coming in
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID of the can message
    Serial.print(" "); 

    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  
      // print the data for i bytes
      Serial.print(canMsg.data[i]);
      Serial.print(" ");
    }

    Serial.println();      
  }
}
