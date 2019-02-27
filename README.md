# Chain Gang Protocol

Chain Gang Protocol (CGP) is a lightweight, serial control protocol designed to run on microcontroller devices
such as Arduino. It is also designed to be robust against noisy or unreliable physical/hardware layers.

The name comes from the idea of a chain gang trying to communicate with each other up and down the line.
Each inmate can only talk directly to the inmate in front of or behind him, so if he wants to say
something to someone further away the message must be passed down the chain by each person in between.

CGP works more like UDP than TCP. There is no SYN/ACK handshake; datagrams are fire-and-forget. Therefore,
there is no guarantee of datagram delivery. However, in order to increase the probability of delivery, each datagram is sent 20 times in rapid succession. Each datagram has a unique ID associated with it, so when the receiver picks up a datagram, it will discard all other datagrams with the same ID.

## Usage

```
#include "chain-gang-protocol.h"

#define SAY_HI 0x20
#define NOOP 0x00

class CGPDelegate : public CGPDelegateInterface {
  Datagram* lastDatagramReceived;

  void processDatagram(Datagram* datagram) {
    lastDatagramReceived = datagram;
    if (datagram->command == SAY_HI) {
      // Do something to say hi!
    } else {
      // Process other commands 
  }

  int getStreamIndexForDatagram(Datagram* datagram) {
    return 0;
  }

  bool shouldForwardDatagram(Datagram* datagram) {
    return datagram->destination == EVERYONE;
  }
};

void setup() {
    Stream* streams[] = {&Serial};
    CGP* cgp = new CGP(1, streams, new CGPDelegate());

    Datagram* datagram = Datagram(EVERYONE, SAY_HI, NOOP, 1);
    cgp.sendDatagram(datagram);
    cgp.getAndProcessDatagram();
}
```
