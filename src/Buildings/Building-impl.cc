#include "Building.h"

void Building::addPiece(char piece) { visiting_pieces.insert(piece); }
void Building::removePiece(char piece) { visiting_pieces.erase(piece); }