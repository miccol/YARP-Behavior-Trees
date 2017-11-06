#BlackBoardCmd.thrift
service BlackBoardCmd {
  void SetI16(1: string name, 2: i16 data);
  void SetI32(1: string name, 2: i32 data);
  void SetI64(1: string name, 2: i64 data);
  void SetByte(1: string name, 2: byte data);
  void SetDouble(1: string name, 2: double data);
  void SetBool(1: string name, 2: double data);
  void SetString(1: string name, 2: string data);
  i16 GetI16(1: string name);
  i32 GetI32(1: string name);
  i64 GetI64(1: string name);
  byte GetByte(1: string name);
  double GetDouble(1: string name);
  bool GetBool(1: string name);
  string GetString(1: string name);
}