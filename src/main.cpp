#include <iostream>
#include "oscListener.hpp"


#define PORT 7000


int main(int argc, char* argv[])
{
    raspiTest listener;

    listener.dioStart();

    UdpListeningReceiveSocket s(
                IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
                &listener );
    std::cout << "press ctrl-c to end" << std::endl;
    s.RunUntilSigInt();

    listener.dioStop();

    return 0;
}



/*
int main(int argc, char* argv[])
{
    // dio instance
    std::vector<Dacs1500rcp24> dioList;
    std::string command;
    std::vector<int> values;


    // init dio
    for(int i=0; i<1; i++){
        Dacs1500rcp24 dio(i);
        dioList.push_back(dio);
    }


    // device open
    for(int i=0; i<1; i++) dioList[i].open();


    // lamp on -> off
    for(int i=0; i<1; i++) {
        command = dioList[i].getDigitalOutPutCommand("800000");
      dioList[i].sendCommand(command);
    }
    sleep(2);
    for(int i=0; i<1; i++) {
        command = dioList[i].getDigitalOutPutCommand("000000");
        dioList[i].sendCommand(command);
    }
    sleep(2);


    // pwm init
    for(int i=0; i<1; i++) {
        command = dioList[i].getPWMInitializeCommand(3,20000);
        dioList[i].sendCommand(command);
    }


    // pwm init pos
    for(int i=0; i<1; i++) {
        for(int j=0; j<PWM_CHANNEL_NUM; j++) values.push_back(1450);
        command = dioList[i].getPWMPalseChangeCommand(values);
        dioList[i].sendCommand(command);
    }


    // start
    for(int i=0; i<1; i++) {
        command = dioList[i].getPWMStartCommand();
        dioList[i].sendCommand(command);
    }


    // osc setup
    ExamplePacketListener listener;
    UdpListeningReceiveSocket s(
                IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
                &listener );
    std::cout << "press ctrl-c to end" << std::endl;
    s.RunUntilSigInt();




    // device pwm stop
    for(int i=0; i<1; i++) {
        command = dioList[i].getPWMStopCommand();
        dioList[i].sendCommand(command);
    }


    // device close
    for(int i=0; i<1; i++) dioList[i].close();

    return 0;
}
*/











/*
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



void ctrlc(int aN) {
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
 std::vector<Dacs1500rcp24> dioList;
 //Dacs1500rcp24 dio(0);
 std::string command;
 std::vector<int> values;


    for(int i=0; i<1; i++){
        Dacs1500rcp24 dio(i);
        dioList.push_back(dio);
    }

 // device open
 for(int i=0; i<1; i++) dioList[i].open();
 //dio.open();

 // lamp on -> off
 for(int i=0; i<1; i++) {
     command = dioList[i].getDigitalOutPutCommand("800000");
   dioList[i].sendCommand(command);
 }
 //dio.sendCommand(command);
 sleep(2);
 for(int i=0; i<1; i++) {
     command = dioList[i].getDigitalOutPutCommand("000000");
     dioList[i].sendCommand(command);
 }
 sleep(2);

 // pwm init
 for(int i=0; i<1; i++) {
     command = dioList[i].getPWMInitializeCommand(3,20000);
     dioList[i].sendCommand(command);
 }


 // pwm init pos
 for(int i=0; i<1; i++) {
     for(int j=0; j<PWM_CHANNEL_NUM; j++) values.push_back(1450);
     command = dioList[i].getPWMPalseChangeCommand(values);
     dioList[i].sendCommand(command);
 }


 // start
 for(int i=0; i<1; i++) {
     command = dioList[i].getPWMStartCommand();
     dioList[i].sendCommand(command);
 }




 // program loop
 while(!gShutoff) {
   numrcv = recvfrom(recvSocket, buffer, BUFFER_SIZE, 0, NULL, NULL);
   if(numrcv == -1) { status = close(recvSocket); break; }
   printf("received: %s\n", buffer);

     for(int i=0; i<1; i++) {
         command = buffer;
         dioList[i].sendCommand(command);
     }

 }
 // stop
 for(int i=0; i<1; i++) {
     command = dioList[i].getPWMStopCommand();
     dioList[i].sendCommand(command);
 }


 // device close
 //dio.close();
 for(int i=0; i<1; i++) dioList[i].close();
}
*/










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
