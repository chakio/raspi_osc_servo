#include "oscListener.hpp"


void ExamplePacketListener::ProcessMessage( const osc::ReceivedMessage& m,
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
                          << val0 << " " << val1 << " " << val2 << " " << val3 << " "
                          << val4 << " " << val5 << " " << val6 << " " << val7 << " "
                          << val8 << " " << val9 << " " << val10 << " " << val11 << " "
                          << val12 << " " << val13 << " " << val14 << " " << val15 << " "
                          << val16 << " " << val17 << " " << val18 << " " << val19 << " "
                          << val20 << " " << val21 << " " << val22 << " " << val23 << " "
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
                          << val0 << " " << val1 << " " << val2 << " " << val3 << " "
                          << val4 << " " << val5 << " " << val6 << " " << val7 << " "
                          << val8 << " " << val9 << " " << val10 << " " << val11 << " "
                          << val12 << " " << val13 << " " << val14 << " " << val15 << " "
                          << val16 << " " << val17 << " " << val18 << " " << val19 << " "
                          << val20 << " " << val21 << " " << val22 << " " << val23 << " "
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
                          << val0 << " " << val1 << " " << val2 << " " << val3 << " "
                          << val4 << " " << val5 << " " << val6 << " " << val7 << " "
                          << val8 << " " << val9 << " " << val10 << " " << val11 << " "
                          << val12 << " " << val13 << " " << val14 << " " << val15 << " "
                          << val16 << " " << val17 << " " << val18 << " " << val19 << " "
                          << val20 << " " << val21 << " " << val22 << " " << val23 << " "
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
                          << val0 << " " << val1 << " " << val2 << " " << val3 << " "
                          << val4 << " " << val5 << " " << val6 << " " << val7 << " "
                          << val8 << " " << val9 << " " << val10 << " " << val11 << " "
                          << val12 << " " << val13 << " " << val14 << " " << val15 << " "
                          << val16 << " " << val17 << " " << val18 << " " << val19 << " "
                          << val20 << " " << val21 << " " << val22 << " " << val23 << " "
                          << "\n";
            }
        } catch( osc::Exception& e ) {
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
            std::cout << "error while parsing message: "
                      << m.AddressPattern() << ": " << e.what() << "\n";
        }
    }
