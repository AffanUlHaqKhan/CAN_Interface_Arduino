# Embedded_lab_CAN

Task is to develop a small CAN-Network using two arduino controllers. One arduino will abe acting as a master and ultrasonic sensor data over the can network to the slave arduino. slave arduino will be displaying it on a 16x2 lcd display


## Hardware Components

Arduino x2
16x2 LCD Display
Can controller(MCP2515) x2
Ultrasonic sensor

Main goal is to acquuire some data from the sensor, send it through the master arduino on using the can controller(MCP2515), receive it on the other end on slave arduino, finally display it on the lcd display.

Circuit diagram for how the whole mechanism will look is drawn on proteus.
Proteus template for arduino, lcd and mcp2515 are gathered through online resources.
Link for arduino proteus library: https://github.com/Proteus-LIBRARY/Arduino-Library
Link for lcd proteus library: https://www.theengineeringprojects.com/2016/05/new-lcd-library-proteus.html
Link for mcp2515 proteus library: https://www.snapeda.com/parts/MCP2515-E/P/Microchip/view-part/

Connection reference for CAN Controller: https://cdn.shopify.com/s/files/1/1509/1638/files/CAN_Bus_Modul_Datenblatt_AZ-Delivery_Vertriebs_GmbH.pdf?v=1608048722

## Implentation Idea

One arduino acts as a transmitter and the second one as a receiver. Transmitter sends data of ultrasonic sensor in a can frame with a user specified ID. Receiver receives the CAN frame and decodes the data. Decoded data can be seen on serial monitor.
Sample code provided with the autowp/arduino-mcp2515[1] for read and write of can frame were modified to acheice the results.

While implementing can bitrate needs to be properly set, from our implementation, MCP2515 works good with 125kbps bit rate but receiver stops receiving anything at 500kbps bitrate. Most probable reason is due to the crystal present on MCP2515 module

For detailed explanation of library usage and samples, refer to[1]

## CAN Frame [2]

![CAN Frame](/assets/images/can_frame.png)
-SOF: The Start of Frame is a 'dominant 0' to tell the other nodes that a CAN node intends to talk.
-ID: The ID is the frame identifier - lower values have higher priority.
-RTR: The Remote Transmission Request indicates whether a node sends data or requests dedicated data from another node.
-Control: The Control contains the Identifier Extension Bit (IDE) which is a 'dominant 0' for 11-bit. It also contains the 4 bit Data Length Code (DLC) that specifies the length of the data bytes to be transmitted (0 to 8 bytes).
-Data: The Data contains the data bytes aka payload, which includes CAN signals that can be extracted and decoded for information.
-CRC: The Cyclic Redundancy Check is used to ensure data integrity.
-ACK: The ACK slot indicates if the node has acknowledged and received the data correctly.
-EOF: The EOF marks the end of the CAN frame.

## Code Explanation

-CAN-bus initialized at rate of 125kbps for both the receiver and transmitter.

-On transmitter side first the sensor gets some data which is the converted into distance using the formula  **"duration*0.034/2"**.
-Then we set the can msg id and the data length
-The calculated distance is then transferred into a can frame to be sent. 

-On receiver end it is first checked if a message os received and there is no error.
-Msg id is decoded. Data is decoded byte by byte.

## References

 [1]https://github.com/autowp/arduino-mcp2515 .
 [2]https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial .
 
