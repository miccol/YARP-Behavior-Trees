#BTCmd.thrift
service BTCmd {
  void request_tick();
  i32 request_status();
  void request_halt();
}