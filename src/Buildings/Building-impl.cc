#include "Building.h"

Building::Building(const std::string &name) : name{name} {}

std::string Building::getName() const { return name; }

void Building::addPiece(char piece) { visiting_pieces.insert(piece); }

void Building::removePiece(char piece) { visiting_pieces.erase(piece); }