#include "dacs1500rcp24.hpp"


Dacs1500rcp24::Dacs1500rcp24() {
  charDeviceID = '0';
  intDeviceID = 0;
}


Dacs1500rcp24::Dacs1500rcp24(int deviceID) {
  intDeviceID = deviceID;

  std::stringstream ss;
  ss << deviceID;
  std::string str = ss.str();
  charDeviceID = str[0];
}


Dacs1500rcp24::~Dacs1500rcp24() {}


void Dacs1500rcp24::open() {
  try {
    if(FT_Open(intDeviceID, &ftHandle) != FT_OK) throw("FT_Open Failed");//例外
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");//例外
    if(FT_SetTimeouts(ftHandle, 1000, 1000) != FT_OK) throw("FT_SetTimeouts Failed");//例外
    std::cout << "open dacs1500rcp24 device." << std::endl;//通常
  }
  catch(char const *str) {
    FT_Close(ftHandle);
    std::cout << "can't open dacs1500rcp24 device." << std::endl;//例外の場合
    std::cout << str << std::endl;
  }
}


void Dacs1500rcp24::close() {
  try {
    if(FT_ResetDevice(ftHandle) != FT_OK) throw("FT_ResetDevice Failed");
    if(FT_Close(ftHandle) != FT_OK) throw("FT_Close Failed");
    std::cout << "close dacs1500rcp24 device." << std::endl;
  }
  catch(char const *str) {
    std::cout << str << std::endl;
    std::cout << "can't close dacs1500rcp24 device normal termination." << std::endl;
  }
}


std::string Dacs1500rcp24::getPWMInitializeCommand(int pwmCountClockID, int pwmPalsePeriod) {
  int data = 0;
  std::string result(18, ' ');

  //ch0~11
  data += 1 << 23;
  data += pwmCountClockID << 20;
  data += 0 << 16;
  data += pwmPalsePeriod;

  result[0] = 'Q';
  result[1] = charDeviceID;
  std::string hexcode = toHex(data);
  for (int i = 0; i < 6; i++) result[2 + i] = hexcode[i];
  result[8] = '&';

  //ch12~23
  data = (data | (1 << 16));

  result[9] = 'Q';
  result[10] = charDeviceID;
  hexcode = toHex(data);
  for (int i = 0; i < 6; i++) result[11 + i] = hexcode[i];
  result[17] = 0x0D;

  return result;
}


std::string Dacs1500rcp24::getPWMStartCommand() {
  std::string result = "Q 00F000&Q 01F000 ";
  result[1] = charDeviceID;
  result[10] = charDeviceID;
  result[17] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getPWMStopCommand() {
  std::string result = "Q 00E000&Q 01E000 ";
  result[1] = charDeviceID;
  result[10] = charDeviceID;
  result[17] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getPWMPalseChangeCommand(int ch, int usec) {
	std::string result(9, ' ');
  int c = 0;
  unsigned int a = 0;
  a += (ch < 12 ? 0 : 1) << 16;
  a += (ch % 12) << 12;
  a += (unsigned int)(usec);
  std::string hex = toHex(a);
  result[c++] = 'Q';
  result[c++] = charDeviceID;
  for (int i = 0; i < 6; i++) result[2 + i] = hex[i];
  result[8] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::getPWMPalseChangeCommand(int o,int ch,std::vector<int> usecList) {
  std::string result(12*9, ' ');
  if (ch == 0)
  {
	  //int c = 0;
	  unsigned int a = 0;
	  for (int i = 0; i < 1; i++) {
		  std::string hex(6, ' ');
		  a = 0;
		  a += 0 << 16;
		  a += (unsigned int)i << 12;
		  a += (unsigned int)usecList[i];
		  std::string hex = toHex(a);
		  result[0+(9*i)] = 'Q';
		  result[1 + (9 * i)] = charDeviceID;
		  result[2 + (9 * i)] = hex[0];
		  result[3 + (9 * i)] = hex[1];
		  result[4 + (9 * i)] = hex[2];
		  result[5 + (9 * i)] = hex[3];
		  result[6 + (9 * i)] = hex[4];
		  result[7 + (9 * i)] = hex[5];
		  result[8 + (9 * i)] = '&';
	  }
	  result[(1 * 9) - 1] = 0x0D;
	  return result;
  }
  /*else
  {
	  int c = 0;
	  unsigned int a = 0;
	  for (int i = 0; i < 12; i++) {
		  a = 0;
		  a += 1 << 16;
		  a += (i % 12) << 12;
		  a += (unsigned int)usecList[i];
		  std::string hex = toHex(a);
		  result[c++] = 'Q';
		  result[c++] = charDeviceID;
		  result[c++] = hex[0];
		  result[c++] = hex[1];
		  result[c++] = hex[2];
		  result[c++] = hex[3];
		  result[c++] = hex[4];
		  result[c++] = hex[5];
		  result[c++] = '&';
	  }
	  result[(12 * 9) - 1] = 0x0D;
	  return result;
  }*/
}


std::string Dacs1500rcp24::getDigitalOutPutCommand(std::string bitStrings) {
  std::string result(9, ' ');
  int c = 0;
  result[c++] = 'W';
  result[c++] = charDeviceID;
  result[c++] = bitStrings[0];
  result[c++] = bitStrings[1];
  result[c++] = bitStrings[2];
  result[c++] = bitStrings[3];
  result[c++] = bitStrings[4];
  result[c++] = bitStrings[5];
  result[c++] = 0x0D;
  return result;
}


std::string Dacs1500rcp24::receiveCommand(int i) {
    std::string bdata(i, ' ');
    DWORD recieve = 0;
    try {
        if (FT_Read(ftHandle, (char*)bdata.c_str(), (DWORD)i, &recieve) != FT_OK) throw("FT_Read Failed");
    }
    catch(char const *str) {
        std::cout << str << std::endl;
        std::cout << "can't connect" << std::endl;
    }
    return bdata;
}


void Dacs1500rcp24::sendCommand(std::string command) {
  DWORD BytesWriten = 0;
  try {
    if (FT_Write(ftHandle, (char*)command.c_str(), command.length(), &BytesWriten) != FT_OK) throw("FT_Write Failed");
    //std::cout << command << std::endl;
  }
  catch(char const *str) {
      std::cout << str << std::endl;
      std::cout << "can't connect" << std::endl;
  }
}


std::string Dacs1500rcp24::toHex(unsigned int x) {
  std::string result(6, ' ');
  for (int i = 0; i < 6; i++) {
    if (x % 16 >= 10) {
      result[5 - i] = (char)((int)'A' + (x % 16 - 10));
    } else {
      result[5 - i] = (char)((int)'0' + x % 16);
    }
    x = x / 16;
  }
  return result;
}
