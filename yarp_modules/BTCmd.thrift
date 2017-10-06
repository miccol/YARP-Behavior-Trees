#BTCmd.thrift
service BTCmd {
  i32 request_tick();
  void request_halt();
}