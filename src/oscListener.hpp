#ifndef __libdacs1500rcp24__oscListener__
#define __libdacs1500rcp24__oscListener__


#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <string.h>
#include <oscpack/osc/OscReceivedElements.h>
#include <oscpack/osc/OscPacketListener.h>
#include <oscpack/ip/UdpSocket.h>
#include "dacs1500rcp24.hpp"


#define PWM_CHANNEL_NUM 12
#define PWM_BRANCH_NUM 2
#define DIO_NUM 2


class raspiTest : public osc::OscPacketListener {

public:
    void dioStart();
    void dioStop();

protected:
    virtual void ProcessMessage( const osc::ReceivedMessage& m,
                                 const IpEndpointName& remoteEndpoint );

private:
    std::vector<Dacs1500rcp24> dioList;
    std::string command;
    std::vector<int> values;
    std::vector<osc::int32> oscValues;
};


#endif
