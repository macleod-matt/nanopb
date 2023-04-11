

# Repository to Maintain Latest Rainhouse NanoPB Library #
- Author Matt MacLeod
- Last Updated 2023/04/10
********

## Summary
********
Fast, light weight, generic protobuf serialization library for embedded applications 

The proto instances are copied over from a previous project that required the serialization of multiple sensors instances (see sensor.proto)

 
## API: 
********

Instead of requiring a specific test case for every proto instance, the serialize/deserialization apis from NanoPB have been extrapolated into the following macros for 

>**PB_MESSAGE_ENCODE(type, src, dest, len )**

Agnostic pb message encoding macro. As long as the pb type is defined within the imported .proto file, this macro can be used to encode the data as that type.


Parameter        | Description |
------------- | -------------
|**Type** | Generic Token representing typedef of PB Serialization structure
|**src** |address of source of serialzied message
|**dest** | address of destination of serialzied message
|**len** | variable representing number of encodeded bytes 

Example: 
```
MftmStatus mftm_stats; 
msg_mftm.msg_id = MessageID_MFTMSTATUS;
msg_mftm.firwmare_version = 1.0; 
msg_mftm.peripheral_ready = true; 
msg_mftm.accel_connected = true; 
msg_mftm.temp_connected = 2; 
msg_mftm.force_connected = 3;
msg_mftm.mic_connected = 0;

uint8_t buffer[240];  
uint8_t encoded_bytes = 0; 
PB_MESSAGE_ENCODE(MftmStatus, &mftm_stats, &buffer, encoded_bytes); 

if(encoded_bytes > 0){ 

  printf("Successfully encoded %d bytes\n", encoded_bytes); 

}

//OUTPUT FROM CONSOLE
Successfully encoded 17 bytes

```
********

>**PB_MESSAGE_DECODE(type, src, dest, len )**

Agnostic pb message encdecoding macro. As long as the pb type is defined within the imported .proto file, this macro can be used to decode the data in that type.


Parameter        | Description |
------------- | -------------
|**Type** | Generic Token representing typedef of PB Serialization structure
|**src** |address og source of serialzied message
|**dest** | address of destination of serialzied message
|**len** | length (in bytes) of the message to decode   

Example: 
```

MftmStatus * pdecoded_message; 
//see serialized buffer encoding above for buffer definition
PB_MESSAGE_DECODE(MftmStatus, pdecoded_message, &buffer, encoded_bytes); 


  LOG_INF("Firmware Version = v.%d, Peripheral Ready = %d , accel_ready = %d, temp_con 
                %d, force_con = %d, mic_con = %d", 
                decoded_message->firmware_version,  decoded_message->peripheral_ready,   
                decoded_message->accel_connected, decoded_message->temp_connected,
                decoded_message->force_connected,decoded_message->mic_connected); 



//output (from RTT Log viewer, can replace with printf): 
Firmware Version = 1.0, Peripheral Ready = true, accel_ready = true, temp_con = 2, force_con = 3, mic_con = 0


```
********




## Background: 
********

- Protobufers are intended for fast and light weight data serialization for micro services across comminication networks 


## Steps to integrate protobuf library into your project: 

********

1. Make any changes to the proto/sensor.proto file you wish 
2. run compile-nanopb.bat 
    - Confirm that sensor.pb, sensor.pb.c, sensor.pb.h are in the proto folder 
3. IF the compiler yields and error about the proto/sensor.pb.c path, change the following line in sensor.pb.c from:
 
 ```
  #include "proto/sensor.pb.h" 
```  
to  

```
 #include "sensor.pb.h
```

4. Enable: CONFIG_NANOPB in proj.conf (zephyr RTOS Only)
5. Compile program