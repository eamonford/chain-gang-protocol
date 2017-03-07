#include "chain-gang-protocol-2.h"

int* CGPInterface::readBytes(Stream* comm, int numBytesToRead) {
  int* message = (int*)malloc(sizeof(int)*numBytesToRead);
  int numBytesReceived = 0;
  while (numBytesReceived < numBytesToRead) {
    if (comm->available() > 0) {
      message[numBytesReceived++] = comm->read();
    }
  }
  return message;
}
