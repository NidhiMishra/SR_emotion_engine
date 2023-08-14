// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.
#ifndef INITMOOD_H
#define INITMOOD_H

#include "InitMoodService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include "control_interface.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::imi;

class InitMoodServiceHandler : virtual public InitMoodServiceIf {
 public:
  InitMoodServiceHandler() {
    // Your initialization goes here
  }

  void initMood(const  ::imi::Vec3& mood) {
    // Your implementation goes here
    printf("initMood\n");
	for(int i=0;i!=3;++i){
	   aff_sys.mood_state[i]=mood[i];
	}
  }

};

#endif