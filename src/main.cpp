#include <iostream>
#include <string.h>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"


#define PORT 7000

class ExamplePacketListener : public osc::OscPacketListener {
protected:

    virtual void ProcessMessage( const osc::ReceivedMessage& m,
				const IpEndpointName& remoteEndpoint )
    {
        try{
            // example of parsing single messages. osc::OsckPacketListener
            // handles the bundle traversal.

            if( strcmp( m.AddressPattern(), "/test1" ) == 0 ){
                // example #1 -- argument stream interface
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                bool a1;
                osc::int32 a2;
                float a3;
                const char *a4;
                args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;

                std::cout << "received '/test1' message with arguments: "
                    << a1 << " " << a2 << " " << a3 << " " << a4 << "\n";

            }else if( strcmp( m.AddressPattern(), "/test2" ) == 0 ){
                // example #2 -- argument iterator interface, supports
                // reflection for overloaded messages (eg you can call
                // (*arg)->IsBool() to check if a bool was passed etc).
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bool a1 = (arg++)->AsBool();
                int a2 = (arg++)->AsInt32();
                float a3 = (arg++)->AsFloat();
                const char *a4 = (arg++)->AsString();
                if( arg != m.ArgumentsEnd() )
                    throw osc::ExcessArgumentException();

                std::cout << "received '/test2' message with arguments: "
                    << a1 << " " << a2 << " " << a3 << " " << a4 << "\n";
            }
        }catch( osc::Exception& e ){
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
