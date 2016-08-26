#include "oscListener.hpp"


void raspiTest::dioStart() {

    // init dio
    for(int i=0; i<DIO_NUM; i++){
        Dacs1500rcp24 dio(i);
        dioList.push_back(dio);
    }

    // device open
    for(int i=0; i<DIO_NUM; i++) dioList[i].open();

   

    // pwm init
    for(int i=0; i<DIO_NUM; i++) {
        command = dioList[i].getPWMInitializeCommand(3,20000);
        dioList[i].sendCommand(command);
        dioList[i].receiveCommand(command.length());
    }
	// lamp on -> off
	for (int i = 0; i<DIO_NUM; i++) {
		command = dioList[i].getDigitalOutPutCommand("800000");
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
	}
	sleep(2);
	for (int i = 0; i<DIO_NUM; i++) {
		command = dioList[i].getDigitalOutPutCommand("000000");
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
	}
	sleep(2);
	/*
    // pwm init pos
    for(int i=0; i<DIO_NUM; i++) {
       

		for (int j = 0; j<12; j++) values[j] = 1450;
		command = dioList[i].getPWMPalseChangeCommand(1,0, values);
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());

		command = dioList[i].getPWMPalseChangeCommand(1,1, values);
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
    }*/

    // start
    for(int i=0; i<DIO_NUM; i++) {
        command = dioList[i].getPWMStartCommand();
        dioList[i].sendCommand(command);
        dioList[i].receiveCommand(command.length());
    }
	sleep(2);
	/*
	for (int i = 0; i<DIO_NUM; i++) {


		for (int j = 0; j<12; j++) values[j] = 650;
		command = dioList[i].getPWMPalseChangeCommand(1, 0, values);
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());

		
		command = dioList[i].getPWMPalseChangeCommand(1, 1, values);
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
	}
	sleep(2);
	for (int i = 0; i<DIO_NUM; i++) {


		for (int j = 0; j<12; j++) values[j] = 1450;
		command = dioList[i].getPWMPalseChangeCommand(1, 0, values);
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());

		command = dioList[i].getPWMPalseChangeCommand(1, 1, values);
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
	}*/
}


void raspiTest::dioStop() {
    // device pwm stop
    for(int i=0; i<DIO_NUM; i++) {
        command = dioList[i].getPWMStopCommand();
        dioList[i].sendCommand(command);
        dioList[i].receiveCommand(command.length());
    }

    // device close
    for(int i=0; i<DIO_NUM; i++) dioList[i].close();
}


void raspiTest::ProcessMessage( const osc::ReceivedMessage& m,
                                const IpEndpointName& remoteEndpoint )
{
    try{
        if( strcmp( m.AddressPattern(), "/deviceA" ) == 0 ){
            if(DIO_NUM >= 1) {
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
                        >> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
                        >> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
                        >> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
                        >> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
                        >> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
                        >> osc::EndMessage;
                for(int j=0; j<PWM_CHANNEL_NUM/2; j++) values[j] = (int)oscValues[j];
                command = dioList[0].getPWMPalseChangeCommand(1,0,values);
                dioList[0].sendCommand(command);
                dioList[0].receiveCommand(command.length());

				for (int j = PWM_CHANNEL_NUM / 2; j<PWM_CHANNEL_NUM ; j++) values[j- PWM_CHANNEL_NUM / 2] = (int)oscValues[j];
				command = dioList[0].getPWMPalseChangeCommand(1,1, values);
				dioList[0].sendCommand(command);
				dioList[0].receiveCommand(command.length());
                //dioList[0].receiveCommand(24 * 9);
            }

        } else if( strcmp( m.AddressPattern(), "/deviceB" ) == 0 ){
            if(DIO_NUM >= 2) {
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
				args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
					>> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
					>> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
					>> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
					>> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
					>> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
					>> osc::EndMessage;
				for (int j = 0; j<PWM_CHANNEL_NUM / 2; j++) values[j] = (int)oscValues[j];
				command = dioList[1].getPWMPalseChangeCommand(1,0, values);
				dioList[1].sendCommand(command);
				dioList[1].receiveCommand(command.length());

				for (int j = PWM_CHANNEL_NUM / 2; j<PWM_CHANNEL_NUM; j++) values[j - PWM_CHANNEL_NUM / 2] = (int)oscValues[j];
				command = dioList[1].getPWMPalseChangeCommand(1,1, values);
				dioList[1].sendCommand(command);
				dioList[1].receiveCommand(command.length());
				//dioList[0].receiveCommand(24 * 9);
            }

        } else if( strcmp( m.AddressPattern(), "/deviceC" ) == 0 ){
            if(DIO_NUM >= 3) {
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
				args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
					>> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
					>> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
					>> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
					>> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
					>> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
					>> osc::EndMessage;
				for (int j = 0; j<PWM_CHANNEL_NUM / 2; j++) values[j] = (int)oscValues[j];
				command = dioList[2].getPWMPalseChangeCommand(1,0, values);
				dioList[2].sendCommand(command);
				dioList[2].receiveCommand(command.length());

				for (int j = PWM_CHANNEL_NUM / 2; j<PWM_CHANNEL_NUM; j++) values[j - PWM_CHANNEL_NUM / 2] = (int)oscValues[j];
				command = dioList[2].getPWMPalseChangeCommand(1,1, values);
				dioList[2].sendCommand(command);
				dioList[2].receiveCommand(command.length());
				//dioList[0].receiveCommand(24 * 9);
            }

        }  else if( strcmp( m.AddressPattern(), "/deviceD" ) == 0 ){
            if(DIO_NUM >= 4) {
				osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
				args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
					>> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
					>> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
					>> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
					>> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
					>> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
					>> osc::EndMessage;
				for (int j = 0; j<PWM_CHANNEL_NUM / 2; j++) values[j] = (int)oscValues[j];
				command = dioList[3].getPWMPalseChangeCommand(1,0, values);
				dioList[3].sendCommand(command);
				dioList[3].receiveCommand(command.length());

				for (int j = PWM_CHANNEL_NUM / 2; j<PWM_CHANNEL_NUM; j++) values[j - PWM_CHANNEL_NUM / 2] = (int)oscValues[j];
				command = dioList[3].getPWMPalseChangeCommand(1,1, values);
				dioList[3].sendCommand(command);
				dioList[3].receiveCommand(command.length());
				//dioList[0].receiveCommand(24 * 9);
            }

        }
    } catch( osc::Exception& e ) {
        std::cout << "error while parsing message: "
                  << m.AddressPattern() << ": " << e.what() << "\n";
    }
}
