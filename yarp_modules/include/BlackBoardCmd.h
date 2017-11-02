// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_BlackBoardCmd
#define YARP_THRIFT_GENERATOR_BlackBoardCmd

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

class BlackBoardCmd;


class BlackBoardCmd : public yarp::os::Wire {
public:
  BlackBoardCmd();
  virtual void SetI16(const std::string& name, const int16_t data);
  virtual void SetI32(const std::string& name, const int32_t data);
  virtual void SetI64(const std::string& name, const YARP_INT64 data);
  virtual void SetByte(const std::string& name, const int8_t data);
  virtual void SetDouble(const std::string& name, const double data);
  virtual void SetBool(const std::string& name, const double data);
  virtual void SetString(const std::string& name, const std::string& data);
  virtual int16_t GetI16(const std::string& name);
  virtual int32_t GetI32(const std::string& name);
  virtual YARP_INT64 GetI64(const std::string& name);
  virtual int8_t GetByte(const std::string& name);
  virtual double GetDouble(const std::string& name);
  virtual bool GetBool(const std::string& name);
  virtual std::string GetString(const std::string& name);
  virtual bool read(yarp::os::ConnectionReader& connection) YARP_OVERRIDE;
  virtual std::vector<std::string> help(const std::string& functionName="--all");
};

#endif
