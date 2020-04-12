#include <Arduino.h>

typedef struct CMD {
    int cmd;
    void* data; //usually arguments
    bool cmd_started;
    bool cmd_processed;
    bool endline_reached;
} CMD;

void new_cmd();
int commandReader();
int processCmd(const char c);
int lightControl(int lightId, int lightAmount);