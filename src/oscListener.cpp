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
            osc::int32 val0, val1, val2, val3, val4, val5,
                    val6, val7, val8, val9, val10, val11,
                    val12, val13, val14, val15, val16, val17,
                    val18, val19, val20, val21, val22, val23;

            args >> val0 >> val1 >> val2 >> val3 >> val4 >> val5
                    >> val6 >> val7 >> val8 >> val9 >> val10 >> val11
                    >> val12 >> val13 >> val14 >> val15 >> val16 >> val17
                    >> val18 >> val19 >> val20 >> val21 >> val22 >> val23
                    >> osc::EndMessage;

            values[0] = (int)val0;
            values[1] = (int)val1;
            values[2] = (int)val2;
            values[3] = (int)val3;
            values[4] = (int)val4;
            values[5] = (int)val5;
            values[6] = (int)val6;
            values[7] = (int)val7;
            values[8] = (int)val8;
            values[9] = (int)val9;
            values[10] = (int)val10;
            values[11] = (int)val11;
            values[12] = (int)val12;
            values[13] = (int)val13;
            values[14] = (int)val14;
            values[15] = (int)val15;
            values[16] = (int)val16;
            values[17] = (int)val17;
            values[18] = (int)val18;
            values[19] = (int)val19;
            values[20] = (int)val20;
            values[21] = (int)val21;
            values[22] = (int)val22;
            values[23] = (int)val23;


            std::cout << "received '/deviceA' message with arguments: "
                      << val0 << " " << val1 << " " << val2 << " " << val3 << " "
                      << val4 << " " << val5 << " " << val6 << " " << val7 << " "
                      << val8 << " " << val9 << " " << val10 << " " << val11 << " "
                      << val12 << " " << val13 << " " << val14 << " " << val15 << " "
                      << val16 << " " << val17 << " " << val18 << " " << val19 << " "
                      << val20 << " " << val21 << " " << val22 << " " << val23 << " "
                      << "\n";

            for(int i=0; i<1; i++) {
                command = dioList[i].getPWMPalseChangeCommand(values);
                dioList[i].sendCommand(command);
                //valList.clear();
            }


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
                      << val0 << " " << val1 << " " << val2 << " " << val3 << " "
                      << val4 << " " << val5 << " " << val6 << " " << val7 << " "
                      << val8 << " " << val9 << " " << val10 << " " << val11 << " "
                      << val12 << " " << val13 << " " << val14 << " " << val15 << " "
                      << val16 << " " << val17 << " " << val18 << " " << val19 << " "
                      << val20 << " " << val21 << " " << val22 << " " << val23 << " "
                      << "\n";

            for(int i=0; i<1; i++) {
                for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = 500;
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
                      << val0 << " " << val1 << " " << val2 << " " << val3 << " "
                      << val4 << " " << val5 << " " << val6 << " " << val7 << " "
                      << val8 << " " << val9 << " " << val10 << " " << val11 << " "
                      << val12 << " " << val13 << " " << val14 << " " << val15 << " "
                      << val16 << " " << val17 << " " << val18 << " " << val19 << " "
                      << val20 << " " << val21 << " " << val22 << " " << val23 << " "
                      << "\n";

            for(int i=0; i<1; i++) {
                for(int j=0; j<PWM_CHANNEL_NUM; j++) values[j] = 500;
                command = dioList[i].getPWMPalseChangeCommand(values);
                dioList[i].sendCommand(command);
            }
        }
    } catch( osc::Exception& e ) {
        std::cout << "error while parsing message: "
                  << m.AddressPattern() << ": " << e.what() << "\n";
    }
}
