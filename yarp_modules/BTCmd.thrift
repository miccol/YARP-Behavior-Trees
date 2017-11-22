#BTCmd.thrift
service BTCmd {
  i32 request_tick();
  i32 request_status();
  void request_halt();
}