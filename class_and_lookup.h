//encode abcdefg to gafbdec
byte encodeOredred(byte in)
{
    byte a = bitRead(in, 6) << 5;
    byte b = bitRead(in, 5) << 3;
    byte c = bitRead(in, 4) << 0;
    byte d = bitRead(in, 3) << 2;
    byte e = bitRead(in, 2) << 1;
    byte f = bitRead(in, 1) << 4;
    byte g = bitRead(in, 0) << 6;
    byte out = 0;
    out |= a;
    out |= b;
    out |= c;
    out |= d;
    out |= e;
    out |= f;
    out |= g;
    // byte out = a || b || c || d || e || f || g;
    return out;
}

class display
{
public:
    byte digits;  //the amount of digits fo the display
    byte address; //i2c address of the device
    display(byte digitsIn, byte addressIn, byte currentIn)
    {
        address = addressIn;
        digits = digitsIn;
        current = currentIn;
        byte currentBits;
        //encode current to bits
        if (current >= 12)
        {
            currentBits |= B100;
            current -= 12;
        }
        if (current >= 6)
        {
            currentBits |= B010;
            current -= 6;
        }
        if (current >= 3)
        {
            currentBits |= B001;
            current -= 3;
        }
        current = currentBits;
    }
    void initDisplay()
    {
        //send control byte to display
        byte controlData = B00000111 | (current << 4); //insert current in it's place
        Wire.beginTransmission(address);
        Wire.write(0x00);
        Wire.write(controlData);
        Wire.endTransmission();
    }
    void clearDisplay()
    {
        Wire.beginTransmission(address);
        Wire.write(0x01); //start at 1st digits
        for (int i = 0; i < digits; i++)
        {
            Wire.write(0x00);
        }
        Wire.endTransmission();
    }
    void sendData(byte *dataIn, int startDigit, int endDigit)
    {
        Wire.beginTransmission(address);
        Wire.write(byte(startDigit + 1)); //digit's commands are 1init
        for (int i = 0, len = endDigit - startDigit; i <= len; i++)
        {
            Wire.write(encodeOredred(dataIn[i]));
        }
        Wire.endTransmission();
    }

private:
    byte current; //the drive current; bits are (right to left): 12mA, 6mA, 3mA
};
//lookup for segments in format -gafbaec
const byte segments[128] = {B00000000,  //0
                            B00000000,  //1
                            B00000000,  //2
                            B00000000,  //3
                            B00000000,  //4
                            B00000000,  //5
                            B00000000,  //6
                            B00000000,  //7
                            B00000000,  //8
                            B00000000,  //9
                            B00000000,  //10
                            B00000000,  //11
                            B00000000,  //12
                            B00000000,  //13
                            B00000000,  //14
                            B00000000,  //15
                            B00000000,  //16
                            B00000000,  //17
                            B00000000,  //18
                            B00000000,  //19
                            B00000000,  //20
                            B00000000,  //21
                            B00000000,  //22
                            B00000000,  //23
                            B00000000,  //24
                            B00000000,  //25
                            B00000000,  //26
                            B00000000,  //27
                            B00000000,  //28
                            B00000000,  //29
                            B00000000,  //30
                            B00000000,  //31
                            B00000000,  //32  ' '
                            B00000000,  //33   !
                            B00000000,  //34   "
                            B00000000,  //35   #
                            B00000000,  //36   $
                            B00000000,  //37   %
                            B00000000,  //38   &
                            B00000000,  //39   '
                            B00000000,  //40   (
                            B00000000,  //41   )
                            B00000000,  //42   *
                            B00000000,  //43   +
                            B00000000,  //44   ,
                            B00000000,  //45   -
                            B00000000,  //46   .
                            B00000000,  //47   /
                            B01111110,  //48   0
                            B00110000,  //49   1
                            B01101101,  //50   2
                            B01111001,  //51   3
                            B00110011,  //52   4
                            B01011011,  //53   5
                            B01011111,  //54   6
                            B01110000,  //55   7
                            B01111111,  //56   8
                            B01111011,  //57   9
                            B00000000,  //58   :
                            B00000000,  //59   ;
                            B00000000,  //60   <
                            B00000000,  //61   =
                            B00000000,  //62   >
                            B00000000,  //63   ?
                            B00000000,  //64   @
                            B00000000,  //65   A
                            B00000000,  //66   B
                            B00000000,  //67   C
                            B00000000,  //68   D
                            B00000000,  //69   E
                            B00000000,  //70   F
                            B00000000,  //71   G
                            B00000000,  //72   H
                            B00000000,  //73   I
                            B00000000,  //74   J
                            B00000000,  //75   K
                            B00000000,  //76   L
                            B00000000,  //77   M
                            B00000000,  //78   N
                            B00000000,  //79   O
                            B00000000,  //80   P
                            B00000000,  //81   Q
                            B00000000,  //82   R
                            B00000000,  //83   S
                            B00000000,  //84   T
                            B00000000,  //85   U
                            B00000000,  //86   V
                            B00000000,  //87   W
                            B00000000,  //88   X
                            B00000000,  //89   Y
                            B00000000,  //90   Z
                            B00000000,  //91   [
                            B00000000,  //92   backslash
                            B00000000,  //93   ]
                            B00000000,  //94   ^
                            B00000000,  //95   _
                            B00000000,  //96   `
                            B00000000,  //97   a
                            B00000000,  //98   b
                            B00000000,  //99   c
                            B00000000,  //100  d
                            B00000000,  //101  e
                            B00000000,  //102  f
                            B00000000,  //103  g
                            B00000000,  //104  h
                            B00000000,  //105  i
                            B00000000,  //106  j
                            B00000000,  //107  k
                            B00000000,  //108  l
                            B00000000,  //109  m
                            B00000000,  //110  n
                            B00000000,  //111  o
                            B00000000,  //112  p
                            B00000000,  //113  q
                            B00000000,  //114  r
                            B00000000,  //115  s
                            B00000000,  //116  t
                            B00000000,  //117  u
                            B00000000,  //118  v
                            B00000000,  //119  w
                            B00000000,  //120  x
                            B00000000,  //121  y
                            B00000000,  //122  z
                            B00000000,  //123  {
                            B00000000,  //124  |
                            B00000000,  //125  }
                            B00000000,  //126  ~
                            B00000000}; //127

char intToChar(int input)
{
    return (char)(input + 48);
}

char digit(int input, int digit)
{
    int value = floor(input / pow(10, digit)) - 10 * floor(input / pow(10, digit + 1));
    return intToChar(value);
}
