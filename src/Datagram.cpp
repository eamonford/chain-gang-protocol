#include "Datagram.h"
#include "Constants.h"

Datagram::Datagram(int newDestination, int newCommand, int newArg) : Datagram(newDestination, newCommand, newArg, random(1, 254)) {}

Datagram::Datagram(int newDestination, int newCommand, int newArg, int newId) {
  this->destination = newDestination;
  this->command = newCommand;
  this->arg = newArg;
  this->id = newId;
}

bool Datagram::isForId(int id) {
  return (id == EVERYONE && this->destination == FIRST_UNIDENTIFIED) ||
         this->destination == id ||
         this->destination == EVERYONE;
}

bool Datagram::isForIdOtherThan(int id) {
  return (this->destination == EVERYONE || this->destination == MASTER ||
            this->destination != id) &&
         !(id == EVERYONE && this->destination == FIRST_UNIDENTIFIED);
}
