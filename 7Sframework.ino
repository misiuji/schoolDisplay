#include "Wire.h"
#include "class_and_lookup.h"

int x;
display dis(4, 0x38, 12);

void setup()
{
    Wire.begin();
    dis.initDisplay();
}
void loop()
{
    byte data[4] = {segments[digit(x, 3)], segments[digit(x, 2)], segments[digit(x, 1)], segments[digit(x, 0)]};
    dis.sendData(data, 0, 3);
    x++;
    delay(50);
}
//test