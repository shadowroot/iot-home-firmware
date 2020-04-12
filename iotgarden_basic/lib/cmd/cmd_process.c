#include "cmd_process.h"
#include <Arduino.h>

const char CMD_END = '\n';
static CMD current_cmd;

void new_cmd(){
  current_cmd.cmd = -1;
  current_cmd.endline_reached = false;
  current_cmd.data = NULL;
  current_cmd.cmd_processed = false;
  current_cmd.cmd_started = false;
}

int commandReader(HardwareSerial& s){
  int recvByte = 0;
  while (s.available() > 0) {
    recvByte = s.read();
    const char c = recvByte;
    processCmd(c);
  }
  return 0;
}

int processCmd(const char c){
  bool endReached = false;

  return 0;
}

int lightControl(int lightId, int lightAmount){
  return 0;
}