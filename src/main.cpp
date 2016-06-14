#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <iostream>

#define BUFFER_SIZE 16

int main() {
 int sock;
 struct sockaddr_in addr;

 char buf[BUFFER_SIZE];

 sock = socket(AF_INET, SOCK_DGRAM, 0);

 addr.sin_family = AF_INET;
 addr.sin_port = htons(12345);
 addr.sin_addr.s_addr = INADDR_ANY;
 addr.sin_len = sizeof(addr);

 bind(sock, (struct sockaddr *)&addr, sizeof(addr));

 memset(buf, 0, sizeof(buf));

 int i = 0;
 while(i<10){
  recv(sock, buf, sizeof(buf), 0);
  std::string str(BUFFER_SIZE/4, ' ');

  for(int j=0; j<BUFFER_SIZE/4; j++) str[j-0] = buf[j];
  std::cout << "A : " << str << std::endl;
  for(int j=BUFFER_SIZE/4; j<BUFFER_SIZE/3; j++) str[j-(BUFFER_SIZE/4)] = buf[j];
  std::cout << "B : " << str << std::endl;
  for(int j=BUFFER_SIZE/3; j<BUFFER_SIZE/2; j++) str[j-(BUFFER_SIZE/3)] = buf[j];
  std::cout << "C : " << str << std::endl;
  for(int j=BUFFER_SIZE/2; j<BUFFER_SIZE/1; j++) str[j-(BUFFER_SIZE/2)] = buf[j];
  std::cout << "D : " << str << std::endl;
  i++;
 }
 close(sock);

 return 0;
}




/*
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "dacs1500rcp24.hpp"

#define PWM_CHANNEL_NUM 2

int main(void)
{
	Dacs1500rcp24 dio(0);
	std::string command;
	std::vector<int> values;

	// device open
	dio.open();

	// lamp on -> off
	command = dio.getDigitalOutPutCommand("800000");
	dio.sendCommand(command);
	sleep(2);
	command = dio.getDigitalOutPutCommand("000000");
	dio.sendCommand(command);
	sleep(2);

	// pwm init
	command = dio.getPWMInitializeCommand(3,20000);
	dio.sendCommand(command);

	// pwm init pos
	for(int i=0; i<PWM_CHANNEL_NUM; i++) values.push_back(1450);
	command = dio.getPWMPalseChangeCommand(values);
	dio.sendCommand(command);

	// start
	command = dio.getPWMStartCommand();
	dio.sendCommand(command);

	// changePWM
	for (int i=0; i<10; i++) {
    sleep(1);
    if(i%2==0) {
			for(int i=0; i<PWM_CHANNEL_NUM; i++) values[i] = 2400;
			command = dio.getPWMPalseChangeCommand(values);
			dio.sendCommand(command);
		}
    else {
			for(int i=0; i<PWM_CHANNEL_NUM; i++) values[i] = 500;
			command = dio.getPWMPalseChangeCommand(values);
			dio.sendCommand(command);
		}
	}

	// stop
	command = dio.getPWMStopCommand();
	dio.sendCommand(command);

	// device close
	dio.close();

	return 0;
}
*/
