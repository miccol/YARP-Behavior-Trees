// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <BlackBoardCmd.h>
#include <yarp/os/idl/WireTypes.h>



class BlackBoardCmd_SetI16 : public yarp::os::Portable {
public:
  std::string name;
  int16_t data;
  void init(const std::string& name, const int16_t data);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_SetI32 : public yarp::os::Portable {
public:
  std::string name;
  int32_t data;
  void init(const std::string& name, const int32_t data);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_SetI64 : public yarp::os::Portable {
public:
  std::string name;
  YARP_INT64 data;
  void init(const std::string& name, const YARP_INT64 data);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_SetByte : public yarp::os::Portable {
public:
  std::string name;
  int8_t data;
  void init(const std::string& name, const int8_t data);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_SetDouble : public yarp::os::Portable {
public:
  std::string name;
  double data;
  void init(const std::string& name, const double data);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_SetBool : public yarp::os::Portable {
public:
  std::string name;
  double data;
  void init(const std::string& name, const double data);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_SetString : public yarp::os::Portable {
public:
  std::string name;
  std::string data;
  void init(const std::string& name, const std::string& data);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_GetI16 : public yarp::os::Portable {
public:
  std::string name;
  int16_t _return;
  void init(const std::string& name);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_GetI32 : public yarp::os::Portable {
public:
  std::string name;
  int32_t _return;
  void init(const std::string& name);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_GetI64 : public yarp::os::Portable {
public:
  std::string name;
  YARP_INT64 _return;
  void init(const std::string& name);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_GetByte : public yarp::os::Portable {
public:
  std::string name;
  int8_t _return;
  void init(const std::string& name);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_GetDouble : public yarp::os::Portable {
public:
  std::string name;
  double _return;
  void init(const std::string& name);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_GetBool : public yarp::os::Portable {
public:
  std::string name;
  bool _return;
  void init(const std::string& name);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

class BlackBoardCmd_GetString : public yarp::os::Portable {
public:
  std::string name;
  std::string _return;
  void init(const std::string& name);
  virtual bool write(yarp::os::ConnectionWriter& connection) override;
  virtual bool read(yarp::os::ConnectionReader& connection) override;
};

bool BlackBoardCmd_SetI16::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("SetI16",1,1)) return false;
  if (!writer.writeString(name)) return false;
  if (!writer.writeI16(data)) return false;
  return true;
}

bool BlackBoardCmd_SetI16::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void BlackBoardCmd_SetI16::init(const std::string& name, const int16_t data) {
  this->name = name;
  this->data = data;
}

bool BlackBoardCmd_SetI32::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("SetI32",1,1)) return false;
  if (!writer.writeString(name)) return false;
  if (!writer.writeI32(data)) return false;
  return true;
}

bool BlackBoardCmd_SetI32::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void BlackBoardCmd_SetI32::init(const std::string& name, const int32_t data) {
  this->name = name;
  this->data = data;
}

bool BlackBoardCmd_SetI64::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("SetI64",1,1)) return false;
  if (!writer.writeString(name)) return false;
  if (!writer.writeI64(data)) return false;
  return true;
}

bool BlackBoardCmd_SetI64::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void BlackBoardCmd_SetI64::init(const std::string& name, const YARP_INT64 data) {
  this->name = name;
  this->data = data;
}

bool BlackBoardCmd_SetByte::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("SetByte",1,1)) return false;
  if (!writer.writeString(name)) return false;
  if (!writer.writeByte(data)) return false;
  return true;
}

bool BlackBoardCmd_SetByte::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void BlackBoardCmd_SetByte::init(const std::string& name, const int8_t data) {
  this->name = name;
  this->data = data;
}

bool BlackBoardCmd_SetDouble::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("SetDouble",1,1)) return false;
  if (!writer.writeString(name)) return false;
  if (!writer.writeDouble(data)) return false;
  return true;
}

bool BlackBoardCmd_SetDouble::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void BlackBoardCmd_SetDouble::init(const std::string& name, const double data) {
  this->name = name;
  this->data = data;
}

bool BlackBoardCmd_SetBool::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("SetBool",1,1)) return false;
  if (!writer.writeString(name)) return false;
  if (!writer.writeDouble(data)) return false;
  return true;
}

bool BlackBoardCmd_SetBool::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void BlackBoardCmd_SetBool::init(const std::string& name, const double data) {
  this->name = name;
  this->data = data;
}

bool BlackBoardCmd_SetString::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("SetString",1,1)) return false;
  if (!writer.writeString(name)) return false;
  if (!writer.writeString(data)) return false;
  return true;
}

bool BlackBoardCmd_SetString::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void BlackBoardCmd_SetString::init(const std::string& name, const std::string& data) {
  this->name = name;
  this->data = data;
}

bool BlackBoardCmd_GetI16::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("GetI16",1,1)) return false;
  if (!writer.writeString(name)) return false;
  return true;
}

bool BlackBoardCmd_GetI16::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI16(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void BlackBoardCmd_GetI16::init(const std::string& name) {
  _return = 0;
  this->name = name;
}

bool BlackBoardCmd_GetI32::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("GetI32",1,1)) return false;
  if (!writer.writeString(name)) return false;
  return true;
}

bool BlackBoardCmd_GetI32::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void BlackBoardCmd_GetI32::init(const std::string& name) {
  _return = 0;
  this->name = name;
}

bool BlackBoardCmd_GetI64::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("GetI64",1,1)) return false;
  if (!writer.writeString(name)) return false;
  return true;
}

bool BlackBoardCmd_GetI64::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI64(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void BlackBoardCmd_GetI64::init(const std::string& name) {
  _return = 0;
  this->name = name;
}

bool BlackBoardCmd_GetByte::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("GetByte",1,1)) return false;
  if (!writer.writeString(name)) return false;
  return true;
}

bool BlackBoardCmd_GetByte::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readByte(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void BlackBoardCmd_GetByte::init(const std::string& name) {
  _return = 0;
  this->name = name;
}

bool BlackBoardCmd_GetDouble::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("GetDouble",1,1)) return false;
  if (!writer.writeString(name)) return false;
  return true;
}

bool BlackBoardCmd_GetDouble::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void BlackBoardCmd_GetDouble::init(const std::string& name) {
  _return = (double)0;
  this->name = name;
}

bool BlackBoardCmd_GetBool::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("GetBool",1,1)) return false;
  if (!writer.writeString(name)) return false;
  return true;
}

bool BlackBoardCmd_GetBool::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void BlackBoardCmd_GetBool::init(const std::string& name) {
  _return = false;
  this->name = name;
}

bool BlackBoardCmd_GetString::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("GetString",1,1)) return false;
  if (!writer.writeString(name)) return false;
  return true;
}

bool BlackBoardCmd_GetString::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readString(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void BlackBoardCmd_GetString::init(const std::string& name) {
  _return = "";
  this->name = name;
}

BlackBoardCmd::BlackBoardCmd() {
  yarp().setOwner(*this);
}
void BlackBoardCmd::SetI16(const std::string& name, const int16_t data) {
  BlackBoardCmd_SetI16 helper;
  helper.init(name,data);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void BlackBoardCmd::SetI16(const std::string& name, const int16_t data)");
  }
  yarp().write(helper,helper);
}
void BlackBoardCmd::SetI32(const std::string& name, const int32_t data) {
  BlackBoardCmd_SetI32 helper;
  helper.init(name,data);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void BlackBoardCmd::SetI32(const std::string& name, const int32_t data)");
  }
  yarp().write(helper,helper);
}
void BlackBoardCmd::SetI64(const std::string& name, const YARP_INT64 data) {
  BlackBoardCmd_SetI64 helper;
  helper.init(name,data);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void BlackBoardCmd::SetI64(const std::string& name, const YARP_INT64 data)");
  }
  yarp().write(helper,helper);
}
void BlackBoardCmd::SetByte(const std::string& name, const int8_t data) {
  BlackBoardCmd_SetByte helper;
  helper.init(name,data);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void BlackBoardCmd::SetByte(const std::string& name, const int8_t data)");
  }
  yarp().write(helper,helper);
}
void BlackBoardCmd::SetDouble(const std::string& name, const double data) {
  BlackBoardCmd_SetDouble helper;
  helper.init(name,data);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void BlackBoardCmd::SetDouble(const std::string& name, const double data)");
  }
  yarp().write(helper,helper);
}
void BlackBoardCmd::SetBool(const std::string& name, const double data) {
  BlackBoardCmd_SetBool helper;
  helper.init(name,data);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void BlackBoardCmd::SetBool(const std::string& name, const double data)");
  }
  yarp().write(helper,helper);
}
void BlackBoardCmd::SetString(const std::string& name, const std::string& data) {
  BlackBoardCmd_SetString helper;
  helper.init(name,data);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void BlackBoardCmd::SetString(const std::string& name, const std::string& data)");
  }
  yarp().write(helper,helper);
}
int16_t BlackBoardCmd::GetI16(const std::string& name) {
  int16_t _return = 0;
  BlackBoardCmd_GetI16 helper;
  helper.init(name);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int16_t BlackBoardCmd::GetI16(const std::string& name)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t BlackBoardCmd::GetI32(const std::string& name) {
  int32_t _return = 0;
  BlackBoardCmd_GetI32 helper;
  helper.init(name);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t BlackBoardCmd::GetI32(const std::string& name)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
YARP_INT64 BlackBoardCmd::GetI64(const std::string& name) {
  YARP_INT64 _return = 0;
  BlackBoardCmd_GetI64 helper;
  helper.init(name);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","YARP_INT64 BlackBoardCmd::GetI64(const std::string& name)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int8_t BlackBoardCmd::GetByte(const std::string& name) {
  int8_t _return = 0;
  BlackBoardCmd_GetByte helper;
  helper.init(name);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int8_t BlackBoardCmd::GetByte(const std::string& name)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double BlackBoardCmd::GetDouble(const std::string& name) {
  double _return = (double)0;
  BlackBoardCmd_GetDouble helper;
  helper.init(name);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double BlackBoardCmd::GetDouble(const std::string& name)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool BlackBoardCmd::GetBool(const std::string& name) {
  bool _return = false;
  BlackBoardCmd_GetBool helper;
  helper.init(name);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool BlackBoardCmd::GetBool(const std::string& name)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
std::string BlackBoardCmd::GetString(const std::string& name) {
  std::string _return = "";
  BlackBoardCmd_GetString helper;
  helper.init(name);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","std::string BlackBoardCmd::GetString(const std::string& name)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool BlackBoardCmd::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) { reader.fail(); return false; }
  yarp::os::ConstString tag = reader.readTag();
  bool direct = (tag=="__direct__");
  if (direct) tag = reader.readTag();
  while (!reader.isError()) {
    // TODO: use quick lookup, this is just a test
    if (tag == "SetI16") {
      std::string name;
      int16_t data;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      if (!reader.readI16(data)) {
        reader.fail();
        return false;
      }
      SetI16(name,data);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "SetI32") {
      std::string name;
      int32_t data;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      if (!reader.readI32(data)) {
        reader.fail();
        return false;
      }
      SetI32(name,data);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "SetI64") {
      std::string name;
      YARP_INT64 data;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      if (!reader.readI64(data)) {
        reader.fail();
        return false;
      }
      SetI64(name,data);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "SetByte") {
      std::string name;
      int8_t data;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      if (!reader.readByte(data)) {
        reader.fail();
        return false;
      }
      SetByte(name,data);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "SetDouble") {
      std::string name;
      double data;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      if (!reader.readDouble(data)) {
        reader.fail();
        return false;
      }
      SetDouble(name,data);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "SetBool") {
      std::string name;
      double data;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      if (!reader.readDouble(data)) {
        reader.fail();
        return false;
      }
      SetBool(name,data);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "SetString") {
      std::string name;
      std::string data;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      if (!reader.readString(data)) {
        reader.fail();
        return false;
      }
      SetString(name,data);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "GetI16") {
      std::string name;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      int16_t _return;
      _return = GetI16(name);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI16(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "GetI32") {
      std::string name;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      int32_t _return;
      _return = GetI32(name);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "GetI64") {
      std::string name;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      YARP_INT64 _return;
      _return = GetI64(name);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI64(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "GetByte") {
      std::string name;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      int8_t _return;
      _return = GetByte(name);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeByte(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "GetDouble") {
      std::string name;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      double _return;
      _return = GetDouble(name);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "GetBool") {
      std::string name;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = GetBool(name);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "GetString") {
      std::string name;
      if (!reader.readString(name)) {
        reader.fail();
        return false;
      }
      std::string _return;
      _return = GetString(name);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeString(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "help") {
      std::string functionName;
      if (!reader.readString(functionName)) {
        functionName = "--all";
      }
      std::vector<std::string> _return=help(functionName);
      yarp::os::idl::WireWriter writer(reader);
        if (!writer.isNull()) {
          if (!writer.writeListHeader(2)) return false;
          if (!writer.writeTag("many",1, 0)) return false;
          if (!writer.writeListBegin(BOTTLE_TAG_INT, static_cast<uint32_t>(_return.size()))) return false;
          std::vector<std::string> ::iterator _iterHelp;
          for (_iterHelp = _return.begin(); _iterHelp != _return.end(); ++_iterHelp)
          {
            if (!writer.writeString(*_iterHelp)) return false;
           }
          if (!writer.writeListEnd()) return false;
        }
      reader.accept();
      return true;
    }
    if (reader.noMore()) { reader.fail(); return false; }
    yarp::os::ConstString next_tag = reader.readTag();
    if (next_tag=="") break;
    tag = tag + "_" + next_tag;
  }
  return false;
}

std::vector<std::string> BlackBoardCmd::help(const std::string& functionName) {
  bool showAll=(functionName=="--all");
  std::vector<std::string> helpString;
  if(showAll) {
    helpString.push_back("*** Available commands:");
    helpString.push_back("SetI16");
    helpString.push_back("SetI32");
    helpString.push_back("SetI64");
    helpString.push_back("SetByte");
    helpString.push_back("SetDouble");
    helpString.push_back("SetBool");
    helpString.push_back("SetString");
    helpString.push_back("GetI16");
    helpString.push_back("GetI32");
    helpString.push_back("GetI64");
    helpString.push_back("GetByte");
    helpString.push_back("GetDouble");
    helpString.push_back("GetBool");
    helpString.push_back("GetString");
    helpString.push_back("help");
  }
  else {
    if (functionName=="SetI16") {
      helpString.push_back("void SetI16(const std::string& name, const int16_t data) ");
    }
    if (functionName=="SetI32") {
      helpString.push_back("void SetI32(const std::string& name, const int32_t data) ");
    }
    if (functionName=="SetI64") {
      helpString.push_back("void SetI64(const std::string& name, const YARP_INT64 data) ");
    }
    if (functionName=="SetByte") {
      helpString.push_back("void SetByte(const std::string& name, const int8_t data) ");
    }
    if (functionName=="SetDouble") {
      helpString.push_back("void SetDouble(const std::string& name, const double data) ");
    }
    if (functionName=="SetBool") {
      helpString.push_back("void SetBool(const std::string& name, const double data) ");
    }
    if (functionName=="SetString") {
      helpString.push_back("void SetString(const std::string& name, const std::string& data) ");
    }
    if (functionName=="GetI16") {
      helpString.push_back("int16_t GetI16(const std::string& name) ");
    }
    if (functionName=="GetI32") {
      helpString.push_back("int32_t GetI32(const std::string& name) ");
    }
    if (functionName=="GetI64") {
      helpString.push_back("YARP_INT64 GetI64(const std::string& name) ");
    }
    if (functionName=="GetByte") {
      helpString.push_back("int8_t GetByte(const std::string& name) ");
    }
    if (functionName=="GetDouble") {
      helpString.push_back("double GetDouble(const std::string& name) ");
    }
    if (functionName=="GetBool") {
      helpString.push_back("bool GetBool(const std::string& name) ");
    }
    if (functionName=="GetString") {
      helpString.push_back("std::string GetString(const std::string& name) ");
    }
    if (functionName=="help") {
      helpString.push_back("std::vector<std::string> help(const std::string& functionName=\"--all\")");
      helpString.push_back("Return list of available commands, or help message for a specific function");
      helpString.push_back("@param functionName name of command for which to get a detailed description. If none or '--all' is provided, print list of available commands");
      helpString.push_back("@return list of strings (one string per line)");
    }
  }
  if ( helpString.empty()) helpString.push_back("Command not found");
  return helpString;
}


