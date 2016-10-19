#include "oscListener.hpp"


void raspiTest::dioStart() {

    // init dio
    for(int i=0; i<DIO_NUM; i++){
        Dacs1500rcp24 dio(i);
        dioList.push_back(dio);
    }

    // device open
    for(int i=0; i<DIO_NUM; i++) dioList[i].open();

    // lamp on -> off
    for(int i=0; i<DIO_NUM; i++) {
        command = dioList[i].getDigitalOutPutCommand("800000");
        dioList[i].sendCommand(command);
        dioList[i].receiveCommand(command.length());
    }
    sleep(2);
    for(int i=0; i<DIO_NUM; i++) {
        command = dioList[i].getDigitalOutPutCommand("000000");
        dioList[i].sendCommand(command);
        dioList[i].receiveCommand(command.length());
    }
    sleep(2);

    // pwm init
    for(int i=0; i<DIO_NUM; i++) {
        command = dioList[i].getPWMInitializeCommand(3,20000);
        dioList[i].sendCommand(command);
        dioList[i].receiveCommand(command.length());
    }

    // pwm init pos
    for(int i=0; i<DIO_NUM; i++) {
		for (int j = 0; j < PWM_BRANCH_NUM; j++)
		{
			for (int k = 0; k < PWM_CHANNEL_NUM; k++) {
				oscValues.push_back(1450);
				values.push_back(1450);
			}
			command = dioList[i].getPWMPalseChangeCommand(values,j);
			dioList[i].sendCommand(command);
			dioList[i].receiveCommand(command.length());
			//dioList[i].receiveCommand(24 * 9);
		}
    }

	for (int i = 0; i<DIO_NUM; i++) {
		command = dioList[i].getDigitalOutPutCommand("800000");
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
	}
    // start
    for(int i=0; i<DIO_NUM; i++) {
        command = dioList[i].getPWMStartCommand();
        dioList[i].sendCommand(command);
        dioList[i].receiveCommand(command.length());
    }
	sleep(2);
	// pwm init pos
	/*for (int i = 0; i<DIO_NUM; i++)//0or1 {
		for (int j = 0; j < PWM_BRANCH_NUM; j++)//0or1
		{
			for (int k = 0; k < PWM_CHANNEL_NUM; k++) //0~12{
				values[j * 12 + k] = 700;
			}
			command = dioList[i].getPWMPalseChangeCommand(values, j);
			dioList[i].sendCommand(command);
			dioList[i].receiveCommand(command.length());
			//dioList[i].receiveCommand(24 * 9);
		}
	}
	for (int i = 0; i<DIO_NUM; i++) {
		command = dioList[i].getDigitalOutPutCommand("000000");
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
	}
	*/


	
	
	for (int k = 0; k < PWM_CHANNEL_NUM*2; k++) //0~12
	{
	values[ k] = 700;
	}
	command = dioList[1].getPWMPalseChangeCommand(values, 0);
	dioList[1].sendCommand(command);
	dioList[1].receiveCommand(command.length());
	command = dioList[1].getPWMPalseChangeCommand(values, 1);
	dioList[1].sendCommand(command);
	dioList[1].receiveCommand(command.length());
	//dioList[i].receiveCommand(24 * 9);
	
	
	for (int i = 0; i<DIO_NUM; i++) {
	command = dioList[i].getDigitalOutPutCommand("(800000");
	dioList[i].sendCommand(command);
	dioList[i].receiveCommand(command.length());
	}

	for (int k = 0; k < PWM_CHANNEL_NUM*2; k++) //0~12
	{
		values[k] = 1000;
	}
	command = dioList[1].getPWMPalseChangeCommand(values, 0);
	dioList[1].sendCommand(command);
	dioList[1].receiveCommand(command.length());
	command = dioList[1].getPWMPalseChangeCommand(values, 1);
	dioList[1].sendCommand(command);
	dioList[1].receiveCommand(command.length());
	//dioList[i].receiveCommand(24 * 9);


	for (int i = 0; i<DIO_NUM; i++) {
		command = dioList[i].getDigitalOutPutCommand("000000");
		dioList[i].sendCommand(command);
		dioList[i].receiveCommand(command.length());
	}
	
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
                for(int j=0; j<PWM_CHANNEL_NUM*PWM_BRANCH_NUM; j++) values[j] = (int)oscValues[j];
				//command.erase(command.begin(), command.begin() + 107);
                command = dioList[0].getPWMPalseChangeCommand(values,0);
                dioList[0].sendCommand(command);
                dioList[0].receiveCommand(command.length());
				std::cout << "/deviceA,value[0]=" << values[0] << std::endl;
				//command.erase(command.begin(), command.begin()+107);
				command = dioList[0].getPWMPalseChangeCommand(values, 1);
				dioList[0].sendCommand(command);
				dioList[0].receiveCommand(command.length());
				std::cout << "/deviceA,value[12]=" << values[12] << std::endl;
				std::cout << command << std::endl;
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
				for (int j = 0; j<PWM_CHANNEL_NUM*PWM_BRANCH_NUM; j++) values[j] = (int)oscValues[j];
				//command.erase(command.begin(), command.begin() + 107);
				command = dioList[1].getPWMPalseChangeCommand(values, 0);
				dioList[1].sendCommand(command);
				dioList[1].receiveCommand(command.length());
				std::cout << "/deviceB,value[0]="<< values[0] << std::endl;
				//command.erase(command.begin(), command.begin() + 107);
				command = dioList[1].getPWMPalseChangeCommand(values, 1);
				dioList[1].sendCommand(command);
				dioList[1].receiveCommand(command.length());
				std::cout << "/deviceB,value[12]=" << values[12] << std::endl;
				std::cout <<command << std::endl;
            }

        } /*else if( strcmp( m.AddressPattern(), "/deviceC" ) == 0 ){
            if(DIO_NUM >= 3) {
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
                        >> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
                        >> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
                        >> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
                        >> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
                        >> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
                        >> osc::EndMessage;
                for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = (int)oscValues[j];
                command = dioList[2].getPWMPalseChangeCommand(values,0);
                dioList[2].sendCommand(command);
                dioList[2].receiveCommand(command.length());
                //dioList[2].receiveCommand(24 * 9);
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

                for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = (int)oscValues[j];
                command = dioList[3].getPWMPalseChangeCommand(values,0);
                dioList[3].sendCommand(command);
                dioList[3].receiveCommand(command.length());
                //dioList[3].receiveCommand(24 * 9);
            }

        }*/
    } catch( osc::Exception& e ) {
        std::cout << "error while parsing message: "
                  << m.AddressPattern() << ": " << e.what() << "\n";
    }
}
