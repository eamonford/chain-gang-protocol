// Example usage for chain-gang-protocol library by Eamon Ford.

#include "chain-gang-protocol.h"

class CGPDelegate : public CGPDelegateInterface {
  void processDatagram(Datagram* datagram) {}

  int getStreamIndexForDatagram(Datagram* datagram) {
    return 0;
  }

  bool shouldForwardDatagram(Datagram* datagram) {
    if (datagram->destination == EVERYONE)
      return true;
    else
      return false;
  }
};


void setup() {
    Stream* testStream = &Serial;
    Stream* streams[] = {testStream};
    CGP* cgp = new CGP(1, streams, new CGPDelegate());
}
