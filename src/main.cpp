#include <iostream>
#include <string.h>

#include "oscpack/osc/OscReceivedElements.h"
#include "oscpack/osc/OscPacketListener.h"
#include "oscpack/ip/UdpSocket.h"


#define PORT 7000

class ExamplePacketListener : public osc::OscPacketListener {
protected:

    virtual void ProcessMessage( const osc::ReceivedMessage& m,
				const IpEndpointName& remoteEndpoint )
    {
        try{
            if( strcmp( m.AddressPattern(), "/deviceA" ) == 0 ){
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                osc::int32 val0, val1, val2, val3, val4, val5,
                           val6, val7, val8, val9, val10, val11,
                           val12, val13, val14, val15, val16, val17,
                           val18, val19, val20, val21, val22, val23;

                args >> val0 >> val1 >> val2 >> val3 >> val4 >> val5
                     >> val6 >> val7 >> val8 >> val9 >> val10 >> val11
                     >> val12 >> val13 >> val14 >> val15 >> val16 >> val17
                     >> val18 >> val19 >> val20 >> val21 >> val22 >> val23
                     >> osc::EndMessage;
                std::cout << "received '/deviceA' message with arguments: "
                    << a0 << " " << a1 << " " << a2 << " " << a3 << " "
                    << a4 << " " << a5 << " " << a6 << " " << a7 << " "
                    << a8 << " " << a9 << " " << a10 << " " << a11 << " "
                    << a12 << " " << a13 << " " << a14 << " " << a15 << " "
                    << a16 << " " << a17 << " " << a18 << " " << a19 << " "
                    << a20 << " " << a21 << " " << a22 << " " << a23 << " "
                    << "\n";

            } else if( strcmp( m.AddressPattern(), "/deviceB" ) == 0 ){
              osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
              osc::int32 val0, val1, val2, val3, val4, val5,
                         val6, val7, val8, val9, val10, val11,
                         val12, val13, val14, val15, val16, val17,
                         val18, val19, val20, val21, val22, val23;

              args >> val0 >> val1 >> val2 >> val3 >> val4 >> val5
                   >> val6 >> val7 >> val8 >> val9 >> val10 >> val11
                   >> val12 >> val13 >> val14 >> val15 >> val16 >> val17
                   >> val18 >> val19 >> val20 >> val21 >> val22 >> val23
                   >> osc::EndMessage;
              std::cout << "received '/deviceB' message with arguments: "
                  << a0 << " " << a1 << " " << a2 << " " << a3 << " "
                  << a4 << " " << a5 << " " << a6 << " " << a7 << " "
                  << a8 << " " << a9 << " " << a10 << " " << a11 << " "
                  << a12 << " " << a13 << " " << a14 << " " << a15 << " "
                  << a16 << " " << a17 << " " << a18 << " " << a19 << " "
                  << a20 << " " << a21 << " " << a22 << " " << a23 << " "
                  << "\n";

            } else if( strcmp( m.AddressPattern(), "/deviceC" ) == 0 ){
              osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
              osc::int32 val0, val1, val2, val3, val4, val5,
                         val6, val7, val8, val9, val10, val11,
                         val12, val13, val14, val15, val16, val17,
                         val18, val19, val20, val21, val22, val23;

              args >> val0 >> val1 >> val2 >> val3 >> val4 >> val5
                   >> val6 >> val7 >> val8 >> val9 >> val10 >> val11
                   >> val12 >> val13 >> val14 >> val15 >> val16 >> val17
                   >> val18 >> val19 >> val20 >> val21 >> val22 >> val23
                   >> osc::EndMessage;
              std::cout << "received '/deviceC' message with arguments: "
                  << a0 << " " << a1 << " " << a2 << " " << a3 << " "
                  << a4 << " " << a5 << " " << a6 << " " << a7 << " "
                  << a8 << " " << a9 << " " << a10 << " " << a11 << " "
                  << a12 << " " << a13 << " " << a14 << " " << a15 << " "
                  << a16 << " " << a17 << " " << a18 << " " << a19 << " "
                  << a20 << " " << a21 << " " << a22 << " " << a23 << " "
                  << "\n";

            }  else if( strcmp( m.AddressPattern(), "/deviceD" ) == 0 ){
              osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
              osc::int32 val0, val1, val2, val3, val4, val5,
                         val6, val7, val8, val9, val10, val11,
                         val12, val13, val14, val15, val16, val17,
                         val18, val19, val20, val21, val22, val23;

              args >> val0 >> val1 >> val2 >> val3 >> val4 >> val5
                   >> val6 >> val7 >> val8 >> val9 >> val10 >> val11
                   >> val12 >> val13 >> val14 >> val15 >> val16 >> val17
                   >> val18 >> val19 >> val20 >> val21 >> val22 >> val23
                   >> osc::EndMessage;
              std::cout << "received '/deviceD' message with arguments: "
                  << a0 << " " << a1 << " " << a2 << " " << a3 << " "
                  << a4 << " " << a5 << " " << a6 << " " << a7 << " "
                  << a8 << " " << a9 << " " << a10 << " " << a11 << " "
                  << a12 << " " << a13 << " " << a14 << " " << a15 << " "
                  << a16 << " " << a17 << " " << a18 << " " << a19 << " "
                  << a20 << " " << a21 << " " << a22 << " " << a23 << " "
                  << "\n";
                }
        } catch( osc::Exception& e ) {
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: "
                << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }
};


int main(int argc, char* argv[])
{
    ExamplePacketListener listener;
    UdpListeningReceiveSocket s(
            IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT ),
            &listener );

    std::cout << "press ctrl-c to end\n";

    s.RunUntilSigInt();

    return 0;
}











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
