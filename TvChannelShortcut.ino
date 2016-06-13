#include <IRLib.h>
#include <avr/pgmspace.h>

#define IR_RECV_PIN 11
#define IR_TX_PIN 9
#define IrRemoteCols 3
#define IrRemoteRows 7
#define _DELAY_IR       10
#define _DELAY_CHANNEL  7000

IRrecv My_Receiver(IR_RECV_PIN);
IRsend My_Sender;
IRdecode My_Decoder;
IRdecodeHash My_Hash_Decoder;

int buttonCode = 0;

/* Standard Arduino remote for hobbist             */
const unsigned long IrHashValue[IrRemoteRows][IrRemoteCols] = {
  {0xE318261B, 0x511DBB, 0xEE886D7F},
  {0x52A3D41F, 0xD7E84B1B, 0x20FE4DBB},
  {0xF076C13B, 0xA3C8EDDB, 0xE5CFBD7F},
  {0xC101E57B, 0x97483BFB, 0xF0C41643},
  {0x9716BE3F, 0x3D9AE3F7, 0x6182021B},
  {0x8C22657B, 0x488F3CBB, 0x449E79F},
  {0x32C6FDF7, 0x1BC0157B, 0x3EC3FC1B}
};

const int IrButtonCode[IrRemoteRows][IrRemoteCols] = {
  {11, 21, 31},
  {12, 22, 32},
  {13, 23, 33},
  {14, 24, 34},
  {15, 25, 35},
  {16, 26, 36},
  {17, 27, 37}
};

const String IrChannelName[IrRemoteRows][IrRemoteCols] = {
  {"Discovery","332","81"},
  {"SCI","83","82"},
  {"TLC","31","83"},
  {" ","99","84"},
  {" "," ","85"},
  {" "," "," "},
  {" "," "," "}
};

/* NOW TV BOX CONTROL */
#define BLINKLED 13
#define NOWTV_NUM0 NEC,0x20200FF,32
#define NOWTV_NUM1 NEC,0x202807F,32
#define NOWTV_NUM2 NEC,0x20240BF,32
#define NOWTV_NUM3 NEC,0x202C03F,32
#define NOWTV_NUM4 NEC,0x20220DF,32
#define NOWTV_NUM5 NEC,0x202A05F,32
#define NOWTV_NUM6 NEC,0x202609F,32
#define NOWTV_NUM7 NEC,0x202E01F,32
#define NOWTV_NUM8 NEC,0x20210EF,32
#define NOWTV_NUM9 NEC,0x202906F,32
/* #define NOWTV_SPACER NEC,0XFFFFFFFF,0 */
#define NOWTV_SPACER NEC,REPEAT,0

enum IrRemoteDigits {N0, N1, N2, N3, N4, N5, N6, N7, N8, N9};

void setChannelNowTv(int chNum) {
  switch(chNum) {
    // delay(500) to prevent IR signal jam between Arduino remote & NowTV IR
    case 209: delay(500); sendDigitNowTv(N2); sendDigitNowTv(N0); sendDigitNowTv(N9); break;
    case 211: delay(500); sendDigitNowTv(N2); sendDigitNowTv(N1); sendDigitNowTv(N1); break;
    case 212: delay(500); sendDigitNowTv(N2); sendDigitNowTv(N1); sendDigitNowTv(N2); break;
    case 213: delay(500); sendDigitNowTv(N2); sendDigitNowTv(N1); sendDigitNowTv(N3); break;
    case 332: delay(500); sendDigitNowTv(N3); sendDigitNowTv(N3); sendDigitNowTv(N2); break;
    case 333: delay(500); sendDigitNowTv(N3); sendDigitNowTv(N3); sendDigitNowTv(N2); break;
  }
}

void sendDigitNowTv(enum IrRemoteDigits dig) {
  switch (dig) {
    case N0: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM0); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N1: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM1); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N2: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM2); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N3: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM3); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N4: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM4); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N5: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM5); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N6: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM6); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N7: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM7); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N8: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM8); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;
    case N9: My_Sender.send(NOWTV_SPACER); My_Sender.send(NOWTV_NUM9); delay(_DELAY_IR); My_Sender.send(NOWTV_SPACER); delay(_DELAY_IR); My_Receiver.enableIRIn(); break;

  }
}

/* SHARP TV CONTROL */
void sendSharpTv(String msg) {
  Serial1.print(msg);
  Serial1.print((char)13);
}

void readTv() {
#ifdef DEBUG
  bool gotMsg = false;
  while (Serial1.available()) {
    Serial.write(Serial1.read());
    gotMsg = true;
  }
  if (gotMsg) Serial.println();
#endif
}

void setChannelSharpTv(int chNum) {
  switch (chNum) {
    case -1: sendSharpTv("IAVD1   "); break;  // HDMI1
    case -2: sendSharpTv("IAVD2   "); break;  // HDMI2
    case 31: sendSharpTv("DTVD031 "); break;
    case 81: sendSharpTv("DTVD081 "); break;
    case 82: sendSharpTv("DTVD082 "); break;
    case 83: sendSharpTv("DTVD083 "); break;
    case 84: sendSharpTv("DTVD084 "); break;
    case 85: sendSharpTv("DTVD085 "); break;
    case 99: sendSharpTv("DTVD099 "); break;
  }
}

/* IR REMOTE CONTROLLER (ARDUINO) */
int getButtonCode(unsigned long hash) {
  for (byte _r = 0; _r < IrRemoteRows; _r++)
    for (byte _c = 0; _c < IrRemoteCols; _c++) {
      if (hash == IrHashValue[_r][_c])
        return IrButtonCode[_r][_c];
    }
  return 0;
}

/* ARDUINO BASE FUNCTIONS */
void setup()
{
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(IR_TX_PIN, OUTPUT);
  My_Receiver.enableIRIn(); // Start the receiver
#ifdef DEBUG
  Serial.begin(115200);   // Computer console message exchange
#endif
  Serial1.begin(9600);    // pin0(RX) & pin1(TX), RS232C to Sharp TV
  delay(1000);
}

void loop() {

  buttonCode = 0;
  if (My_Receiver.GetResults(&My_Decoder)) {    //Puts results in My_Decoder
    My_Hash_Decoder.copyBuf(&My_Decoder);       //copy the results to the hash decoder
//    My_Decoder.decode();

    My_Hash_Decoder.decode();
    buttonCode = getButtonCode(My_Hash_Decoder.hash);
  
#ifdef DEBUG
    Serial.print(", hash decode: 0x");
    Serial.println(My_Hash_Decoder.hash, HEX); // Do something interesting with this value
    Serial.print("Button pressed (code):");
    Serial.println(buttonCode);
#endif
    switch(buttonCode) {
      case 11: setChannelNowTv(209); setChannelSharpTv(-1); break;
      case 12: setChannelNowTv(211); setChannelSharpTv(-1); break;
      case 13: setChannelNowTv(213); setChannelSharpTv(-1); break;
      case 16: sendSharpTv("WIDE1   "); break;
      case 17: sendSharpTv("WIDE10  "); break;
      
      case 21: setChannelNowTv(332); setChannelSharpTv(-1); break;
      case 22: setChannelSharpTv(83); break;
      case 23: setChannelSharpTv(31); break;
      case 24: setChannelSharpTv(99); break;
      
      case 31: setChannelSharpTv(81); break;
      case 32: setChannelSharpTv(82); break;
      case 33: setChannelSharpTv(83); break;
      case 34: setChannelSharpTv(84); break;
      case 35: setChannelSharpTv(85); break;

      case 17: 
        Serial1.print("VOLM????"); Serial1.print((char)13); delay(50); readTv();
        Serial1.print("VOLM????"); Serial1.print((char)13); delay(50); readTv();
        Serial1.print("VOLM????"); Serial1.print((char)13); delay(50); readTv();
      break;
    }
    delay(500);
    My_Receiver.resume();
  }
}
