#include "msg_npb.h"
#include "stdint.h"
/* 
    In this example, we will demonstrate the encoding and decoding of some simple message structures imported from a previous project within sensor.proto
*/


int main(){ 
  MftmStatus msg_status; //custom status message for embedded device (see sensor.proto)
  Temperature msg_temp;  //custom message for multi channel temperature sensor (see sensor.proto) 
  MftmStatus * pmsg_status; //custom status message for embedded device (see sensor.proto)
  Temperature * pmsg_temp;  //custom message for multi channel temperature sensor (see sensor.proto) 


  uint8_t temp_encode_buff[Temperature_size]; 
  uint8_t status_encode_buff[MftmStatus_size]; 
  uint8_t temp_bytes =0; 
  uint8_t status_bytes =0; 

  msg_status.firwmare_version = 1.0; 
  msg_status.peripheral_ready = true; 
  msg_status.accel_connected = true; 
  msg_status.temp_connected = 2; 
  msg_status.force_connected = 3;
  msg_status.mic_connected = 0;

  msg_temp.voltage_internal;
  msg_temp.voltage_channel1;
  msg_temp.voltage_channel2;

  // encode the data 
  PB_MESSAGE_ENCODE(MftmStatus, &msg_status, &status_encode_buff,status_bytes ); 
  PB_MESSAGE_ENCODE(Temperature, &msg_temp, &temp_encode_buff,temp_bytes ); 
  //do somehting: e.g.) transmit data over micro service/grpc stream 

  if(status_bytes > 0  && temp_bytes > 0){ 
    PB_MESSAGE_DECODE(MftmStatus, &status_encode_buff, pmsg_status,status_bytes ); 
    PB_MESSAGE_DECODE(Temperature, &temp_encode_buff, pmsg_temp,temp_bytes ); 
  }

  if(pmsg_status != NULL && pmsg_temp != NULL){ 
    //do something with pointers to decoded data pmsg_status, pmsg_temp

  }

}