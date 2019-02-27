#include "chain-gang-protocol.h"

CGP::CGP(int numStreams, Stream** newStreams, CGPDelegateInterface* newDelegate) {
  this->delegate = newDelegate;

  this->streams = newStreams;
  this->numStreams = numStreams;
  this->lastDatagramIds = (int*)malloc(sizeof(int)*numStreams);
  for (int i = 0; i < numStreams; i++) {
    lastDatagramIds[i] = 0;
  }
  randomSeed(analogRead(0));
}

int CGP::readUntil(int bufferLen, int* buffer, Stream* stream, int terminal, long timeout) {
  int i = 0;
  long startTime = millis();
  while (i < bufferLen && (timeout == 0 || millis() - startTime < timeout)) {
    if (stream->available() > 0) {
      int newByte = stream->read();
      if (newByte != terminal) {
        buffer[i++] = newByte;
      } else {
        return i;
      }
    }
  }
  return 0;
}

void CGP::writeDatagramToStream(Stream* stream, Datagram* datagram) {
  stream->write(datagram->destination);
  stream->write(datagram->command);
  stream->write(datagram->arg);
  stream->write(datagram->id);
  stream->write(END_OF_DATAGRAM);
}

void CGP::sendDatagram(Datagram* datagram) {
  int streamIndex = this->delegate->getStreamIndexForDatagram(datagram);
  if (streamIndex < 0 || streamIndex >= this->numStreams)
    return;

  Stream* stream = this->streams[streamIndex];
  // Fire off the datagram many times. Since they will all have the same datagram ID,
  // after one is successfully received all the rest will be discarded.
  for (int i = 0; i < DATAGRAM_REPEATS; i++)
    writeDatagramToStream(stream, datagram);
}

Datagram* CGP::getDatagramOrEatJunk(Stream* stream, long timeout) {
  int* bytes;
  while (bytes = (int*)malloc(sizeof(int)*128)) {
    int numBytes = readUntil(128, bytes, stream, END_OF_DATAGRAM, timeout);
    // If this happens, then the available data was a false alarm -- it was probably just noise, so return NULL
    if (numBytes == 0) {
      free(bytes);
      return NULL;
    }
    if (numBytes >= 4) {
      // construct a datagram out of the last 4 bytes before the terminal character
      Datagram* newDatagram = Datagram::parse(bytes + numBytes - 4);
      free(bytes);
      return newDatagram;
    }
    free(bytes);
  }
}

Datagram* CGP::getDatagramOnAnyStream(long timeout) {
  int i = 0;
  long startTime = millis();
  while (timeout == 0 || millis() - startTime < timeout) {
    Stream* currStream = this->streams[i];
    i = (i + 1) % numStreams;
    if (currStream->available() > 0) {
      long junkTimeout = timeout > 0 ? timeout : 1000;
      Datagram* datagram = getDatagramOrEatJunk(currStream, junkTimeout);
      if (datagram != NULL && datagram->id != lastDatagramIds[i]) {
        lastDatagramIds[i] = datagram->id;
        return datagram;
      }
      // We had a false alarm so restart the timer
      startTime = millis();
      delete datagram;
    }
  }
  return NULL;
}

void CGP::getAndProcessDatagram() {
  getAndProcessDatagram(0);
}

void CGP::getAndProcessDatagram(long timeout) {
  Datagram* datagram = getDatagramOnAnyStream(timeout);
  if (datagram == NULL)
    return;
  this->delegate->processDatagram(datagram);
  if (this->delegate->shouldForwardDatagram(datagram)) {
    sendDatagram(datagram);
  }
  delete datagram;
}
