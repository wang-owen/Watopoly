module PieceManager;
import <iostream>;

const std::vector<std::pair<char, std::string>> PieceManager::PIECES = {
    {'G', "Goose"},     {'B', "GRT Bus"}, {'D', "Tim Hortons Doughnut"},
    {'P', "Professor"}, {'S', "Student"}, {'$', "Money"},
    {'L', "Laptop"},    {'T', "Pink Tie"}};

const std::vector<PieceType> PieceManager::PIECE_TYPES = {
    PieceType::Goose,     PieceType::GRTBus,  PieceType::TimHortonsDoughnut,
    PieceType::Professor, PieceType::Student, PieceType::Money,
    PieceType::Laptop,    PieceType::PinkTie};

PieceManager::PieceManager()
    : available_pieces{PIECE_TYPES.begin(), PIECE_TYPES.end()} {}

void PieceManager::displayPieces() {
  std::cout << "Available pieces:\n";
  std::cout << "-----------------\n";
  for (size_t i = 1; i <= PIECE_TYPES.size(); i++) {
    std::cout << (isAvailable(i) ? std::to_string(i) : "X") << " - "
              << PIECES[i - 1].second << " (" << PIECES[i - 1].first << ")\n";
  }
}

int PieceManager::getNumPieces() const {
  return static_cast<int>(PIECE_TYPES.size());
}

bool PieceManager::isAvailable(int n) const {
  return available_pieces.contains(PIECE_TYPES[n - 1]);
}

char PieceManager::selectPiece(int n) {
  if (isAvailable(n)) {
    available_pieces.erase(PIECE_TYPES[n - 1]);
    return PIECES[n - 1].first;
  }
  throw("Piece not available!");
}
