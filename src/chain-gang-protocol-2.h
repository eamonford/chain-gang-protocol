#pragma once

#ifdef ARDUINO
    #include <Arduino.h>
#else
  #include "Particle.h"
#endif

#include "Message.h"
#include "Constants.h"

class CGPInterface {
    public:
        virtual bool sendMessage(Message* msg, int identity) = 0;
        virtual bool sendSynAndWaitForAck(Stream* stream) = 0;
        virtual Stream* waitForSynAndSendAck() = 0;

        int* readBytes(Stream* comm, int numBytesToRead);
};
