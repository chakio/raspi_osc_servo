#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256



#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "dacs1500rcp24.hpp"

#define PWM_CHANNEL_NUM 2



#include <signal.h>
int gShutoff;



void ctlc(int aN) {
	gShutoff = 1;
	signal( SIGINT, NULL );
}



int main() {
	gShutoff = 0;
  signal( SIGINT, ctrlc );


 unsigned short port = 9876;
 int recvSocket;

 struct sockaddr_in recvSockAddr;

 int status;
 int numrcv;
 char buffer[BUFFER_SIZE];
 unsigned long on = 1;

 memset(&recvSockAddr, 0, sizeof(recvSockAddr));
 recvSockAddr.sin_port = htons(port);
 recvSockAddr.sin_family = AF_INET;
 recvSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

 recvSocket = socket(AF_INET, SOCK_DGRAM, 0);

 status = bind(recvSocket, (const struct sockaddr *) &recvSockAddr, sizeof(recvSockAddr));





 // dio instance
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

 // stop
 command = dio.getPWMStopCommand();
 dio.sendCommand(command);

 // device close
 dio.close();



 // program loop
 while(!gShutoff) {
   numrcv = recvfrom(recvSocket, buffer, BUFFER_SIZE, 0, NULL, NULL);
   if(numrcv == -1) { status = close(recvSocket); break; }
   printf("received: %s\n", buffer);
 }
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
