#ifndef __libdacs1500rcp24__oscListener__
#define __libdacs1500rcp24__oscListener__


#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <string.h>
#include "oscpack/osc/OscReceivedElements.h"
#include "oscpack/osc/OscPacketListener.h"
#include "oscpack/ip/UdpSocket.h"
#include "dacs1500rcp24.hpp"


#define PWM_CHANNEL_NUM 24


class raspiTest : public osc::OscPacketListener {

public:
    void dioStart();
    void dioStop();

protected:
    virtual void ProcessMessage( const osc::ReceivedMessage& m,
                                 const IpEndpointName& remoteEndpoint );

private:
    // dio instance
    std::vector<Dacs1500rcp24> dioList;
    std::string command;
    std::vector<int> values;
};


#endif




/*
#ifndef __libdacs1500rcp24__oscListener__
#define __libdacs1500rcp24__oscListener__


#include <iostream>
#include <string.h>
#include "oscpack/osc/OscReceivedElements.h"
#include "oscpack/osc/OscPacketListener.h"
#include "oscpack/ip/UdpSocket.h"


class ExamplePacketListener : public osc::OscPacketListener {
protected:
    virtual void ProcessMessage( const osc::ReceivedMessage& m,
                                 const IpEndpointName& remoteEndpoint );
};



#endif
*/


