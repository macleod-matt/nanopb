echo compiling protofiles in proto dirctory 

del sensor.pb
del sensor.pb.c
del sensor.pb.h 

generator\protoc -o sensor.pb sensor.proto && py generator\nanopb_generator.py sensor.pb