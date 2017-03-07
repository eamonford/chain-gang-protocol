#include "chain-gang-protocol.h"

int* CGPInterface::readBytes(Stream* comm, int numBytesToRead) {
  int* datagram = (int*)malloc(sizeof(int)*numBytesToRead);
  int numBytesReceived = 0;
  while (numBytesReceived < numBytesToRead) {
    if (comm->available() > 0) {
      datagram[numBytesReceived++] = comm->read();
    }
  }
  return datagram;
}
