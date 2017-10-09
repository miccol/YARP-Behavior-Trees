// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_BTCmd
#define YARP_THRIFT_GENERATOR_BTCmd

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

class BTCmd;


class BTCmd : public yarp::os::Wire {
public:
  BTCmd();
  virtual int32_t request_tick();
  virtual void request_halt();
  virtual bool read(yarp::os::ConnectionReader& connection) YARP_OVERRIDE;
  virtual std::vector<std::string> help(const std::string& functionName="--all");
};

#endif
