#ifndef MSG_PB_H
#define MSG_PB_H

#include <pb_encode.h>
#include <pb_decode.h>
#include "sensor.pb.h"

#define MAX_PB_SIZE Acceleration_size //set to the max size of protobuf message (in our case Acceleration_size)
/* 
  @brief: Generic PB Serialization Macro 
  @param type:  generic token for input protobuf type  
  @param src: pointer to source (data to be serialized) 
  @param dest: pointer to destination of serialized data 
  @param len: variable to store number of bytes that were encoded  
*/
#define PB_MESSAGE_ENCODE(type, src, dest, len )\
do{ \
  pb_ostream_t stream = pb_ostream_from_buffer(dest, MAX_PB_SIZE);\
  type *message = (type *)src;\
  len = !pb_encode(&stream, type##_fields, message) ? 0 : stream.bytes_written ;\
}while (0)

/* 
  @brief: Generic PB decoding Macro 
  @param type:  generic token for input protobuf type  
  @param src: pointer to source (pb serialized data) 
  @param dest: pointer to destination of de-serialzied data 
  @param len: (in bytes) number of encoded bytes to de-serialize 

*/
#define PB_MESSAGE_DECODE(type, src, dest , len)\
do{ \
  pb_istream_t stream = pb_istream_from_buffer(src, len);\
  type message = type##_init_zero;\
  dest = !pb_decode(&stream, type##_fields, &message) ? NULL : &message;\
}while (0)



#endif 



