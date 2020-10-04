#include "Wire.h"
#include "class_and_lookup.h"

int x;
display dis(4, 0x38, 9);

void setup()
{
    Wire.begin();
    dis.initDisplay();
}
void loop()
{
    byte data[4] = {segments[digit(x, 3)], segments[digit(x, 2)], segments[digit(x, 1)], segments[digit(x, 0)]};
    // byte data[4] = {B00000001, B00000010, B00000100, B00001000};
    dis.sendData(data, 0, 3);
    x++;
    delay(50);
}