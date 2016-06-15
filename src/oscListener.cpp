#include "oscListener.hpp"


void raspiTest::dioStart() {

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
        for(int j=0; j<PWM_CHANNEL_NUM; j++) {
            oscValues.push_back(1450);
            values.push_back(1450);
        }
        command = dioList[i].getPWMPalseChangeCommand(values);
        dioList[i].sendCommand(command);
    }

    // start
    for(int i=0; i<1; i++) {
        command = dioList[i].getPWMStartCommand();
        dioList[i].sendCommand(command);
    }
}


void raspiTest::dioStop() {
    // device pwm stop
    for(int i=0; i<1; i++) {
        command = dioList[i].getPWMStopCommand();
        dioList[i].sendCommand(command);
    }

    // device close
    for(int i=0; i<1; i++) dioList[i].close();
}


void raspiTest::ProcessMessage( const osc::ReceivedMessage& m,
                                const IpEndpointName& remoteEndpoint )
{
    try{
        if( strcmp( m.AddressPattern(), "/deviceA" ) == 0 ){
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();

            args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
                    >> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
                    >> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
                    >> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
                    >> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
                    >> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
                    >> osc::EndMessage;

            for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = (int)oscValues[j];
            command = dioList[0].getPWMPalseChangeCommand(values);
            dioList[0].sendCommand(command);

        } else if( strcmp( m.AddressPattern(), "/deviceB" ) == 0 ){
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();

            args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
                    >> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
                    >> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
                    >> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
                    >> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
                    >> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
                    >> osc::EndMessage;

            for(int i=0; i<1; i++) {
                for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = (int)oscValues[j];
                command = dioList[i].getPWMPalseChangeCommand(values);
                dioList[i].sendCommand(command);
            }

        } else if( strcmp( m.AddressPattern(), "/deviceC" ) == 0 ){
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();

            args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
                    >> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
                    >> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
                    >> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
                    >> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
                    >> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
                    >> osc::EndMessage;

            for(int i=0; i<1; i++) {
                for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = (int)oscValues[j];
                command = dioList[i].getPWMPalseChangeCommand(values);
                dioList[i].sendCommand(command);
            }

        }  else if( strcmp( m.AddressPattern(), "/deviceD" ) == 0 ){
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();

            args >> oscValues[0] >> oscValues[1] >> oscValues[2] >> oscValues[3]
                    >> oscValues[4] >> oscValues[5] >> oscValues[6] >> oscValues[7]
                    >> oscValues[8] >> oscValues[9] >> oscValues[10] >> oscValues[11]
                    >> oscValues[12] >> oscValues[13] >> oscValues[14] >> oscValues[15]
                    >> oscValues[16] >> oscValues[17] >> oscValues[18] >> oscValues[19]
                    >> oscValues[20] >> oscValues[21] >> oscValues[22] >> oscValues[23]
                    >> osc::EndMessage;

            for(int i=0; i<1; i++) {
                for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = (int)oscValues[j];
                command = dioList[i].getPWMPalseChangeCommand(values);
                dioList[i].sendCommand(command);
            }
        }
    } catch( osc::Exception& e ) {
        std::cout << "error while parsing message: "
                  << m.AddressPattern() << ": " << e.what() << "\n";
    }
}
