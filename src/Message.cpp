#include "Message.h"
#include "Constants.h"

Message::Message(int destination, int command, int arg) {
  this->destination = destination;
  this->command = command;
  this->arg = arg;
}

bool Message::isForId(int id) {
  return (id == EVERYONE && this->destination == FIRST_UNIDENTIFIED) ||
         this->destination == id ||
         this->destination == EVERYONE;
}

bool Message::isForIdOtherThan(int id) {
  return (this->destination == EVERYONE || this->destination == MASTER ||
            this->destination != id) &&
         !(id == EVERYONE && this->destination == FIRST_UNIDENTIFIED);
}
