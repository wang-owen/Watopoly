#include <iostream>

#include "Board.h"
#include "Buildings/AcademicBuilding.h"
#include "Buildings/Building.h"
#include "Buildings/CollectOSAP.h"
#include "Buildings/CoopFee.h"
#include "Buildings/DCTimsLine.h"
#include "Buildings/GoToTims.h"
#include "Buildings/GooseNesting.h"
#include "Buildings/GymBuilding.h"
#include "Buildings/NeedlesHall.h"
#include "Buildings/ResidenceBuilding.h"
#include "Buildings/RollUpTheRimDecorator.h"
#include "Buildings/SLC.h"
#include "Buildings/Tuition.h"

Board::Board() : active_cups{std::make_shared<int>(0)} {
  buildings.reserve(40);
  auto slc = std::make_shared<RollUpTheRimDecorator>(
      std::make_unique<SLC>(buildings), active_cups);
  auto needles_hall = std::make_shared<RollUpTheRimDecorator>(
      std::make_unique<NeedlesHall>(), active_cups);

  buildings.reserve(40);
  buildings.emplace_back(std::make_shared<CollectOSAP>());
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "AL", MonopolyBlock::Arts1, 40, 50,
      std::array<int, 6>{2, 10, 30, 90, 160, 250}));
  buildings.emplace_back(slc);
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "ML", MonopolyBlock::Arts1, 60, 50,
      std::array<int, 6>{4, 20, 60, 180, 320, 450}));
  buildings.emplace_back(std::make_shared<Tuition>());
  buildings.emplace_back(std::make_shared<ResidenceBuilding>("MKV"));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "ECH", MonopolyBlock::Arts2, 100, 50,
      std::array<int, 6>{6, 30, 90, 270, 400, 550}));
  buildings.emplace_back(needles_hall);
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "PAS", MonopolyBlock::Arts2, 100, 50,
      std::array<int, 6>{6, 30, 90, 270, 400, 550}));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "HH", MonopolyBlock::Arts2, 120, 50,
      std::array<int, 6>{8, 40, 100, 300, 450, 600}));
  buildings.emplace_back(std::make_shared<DCTimsLine>());
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "RCH", MonopolyBlock::Eng, 140, 100,
      std::array<int, 6>{10, 50, 150, 450, 625, 750}));
  buildings.emplace_back(std::make_shared<GymBuilding>("PAC"));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "DWE", MonopolyBlock::Eng, 140, 100,
      std::array<int, 6>{10, 50, 150, 450, 625, 750}));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "CPH", MonopolyBlock::Eng, 160, 100,
      std::array<int, 6>{12, 60, 180, 500, 700, 900}));
  buildings.emplace_back(std::make_shared<ResidenceBuilding>("UWP"));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "LHI", MonopolyBlock::Health, 180, 100,
      std::array<int, 6>{14, 70, 200, 550, 750, 950}));
  buildings.emplace_back(slc);
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "BMH", MonopolyBlock::Health, 180, 100,
      std::array<int, 6>{14, 70, 200, 550, 750, 950}));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "OPT", MonopolyBlock::Health, 200, 100,
      std::array<int, 6>{16, 80, 220, 600, 800, 1000}));
  buildings.emplace_back(std::make_shared<GooseNesting>());
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "EV1", MonopolyBlock::Env, 220, 150,
      std::array<int, 6>{18, 90, 250, 700, 875, 1050}));
  buildings.emplace_back(needles_hall);
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "EV2", MonopolyBlock::Env, 220, 150,
      std::array<int, 6>{18, 90, 250, 700, 875, 1050}));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "EV3", MonopolyBlock::Env, 240, 150,
      std::array<int, 6>{20, 100, 300, 750, 925, 1100}));
  buildings.emplace_back(std::make_shared<ResidenceBuilding>("V1"));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "PHYS", MonopolyBlock::Sci1, 260, 150,
      std::array<int, 6>{22, 110, 330, 800, 975, 1150}));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "B1", MonopolyBlock::Sci1, 260, 150,
      std::array<int, 6>{22, 110, 330, 800, 975, 1150}));
  buildings.emplace_back(std::make_shared<GymBuilding>("CIF"));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "B2", MonopolyBlock::Sci1, 280, 150,
      std::array<int, 6>{24, 120, 360, 850, 1025, 1200}));
  buildings.emplace_back(std::make_shared<GoToTims>(buildings));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "EIT", MonopolyBlock::Sci2, 300, 200,
      std::array<int, 6>{26, 130, 390, 900, 1100, 1275}));
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "ESC", MonopolyBlock::Sci2, 300, 200,
      std::array<int, 6>{26, 130, 390, 900, 1100, 1275}));
  buildings.emplace_back(slc);
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "C2", MonopolyBlock::Sci2, 320, 200,
      std::array<int, 6>{28, 150, 450, 1000, 1200, 1400}));
  buildings.emplace_back(std::make_shared<ResidenceBuilding>("REV"));
  buildings.emplace_back(needles_hall);
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "MC", MonopolyBlock::Math, 350, 200,
      std::array<int, 6>{35, 175, 500, 1100, 1300, 1500}));
  buildings.emplace_back(std::make_shared<CoopFee>());
  buildings.emplace_back(std::make_shared<AcademicBuilding>(
      "DC", MonopolyBlock::Math, 400, 200,
      std::array<int, 6>{50, 200, 600, 1400, 1700, 2000}));
}

void Board::displayBoard() const {
    std::cout << "_________________________________________________________________________________________\n";
    std::cout << "|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |\n";
  std::cout << "|Nesting|"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[21]))
        << "|HALL   |" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[23])) << "|"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[24])) << "|       |"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[26])) << "|"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[27])) << "|       |"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[29])) << "|TIMS   |\n";
    std::cout << "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[20]) << "|" << printEmptySquareWithPieces(buildings[21]) << "|" 
        << printEmptySquareWithPieces(buildings[22]) << "|" << printEmptySquareWithPieces(buildings[23]) 
        << "|" << printEmptySquareWithPieces(buildings[24]) << "|" << printEmptySquareWithPieces(buildings[25]) 
        << "|" << printEmptySquareWithPieces(buildings[26]) << "|" << printEmptySquareWithPieces(buildings[27]) 
        << "|" << printEmptySquareWithPieces(buildings[28]) << "|" << printEmptySquareWithPieces(buildings[29]) 
        << "|" << printEmptySquareWithPieces(buildings[30]) << "|\n";
    std::cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[19])) << "|" << std::string(71, ' ') 
        << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[31])) << "|\n";
  std::cout << "|OPT    |" << std::string(71, ' ') << "|EIT    |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[19]) << "|" << std::string(71, ' ') 
        << "|" << printEmptySquareWithPieces(buildings[31]) << "|\n";
  std::cout << "|_______|" << std::string(71, ' ') << "|_______|\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[18])) << "|" << std::string(71, ' ') 
        << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[32])) << "|\n";
  std::cout << "|BMH    |" << std::string(71, ' ') << "|ESC    |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[18]) << "|" << std::string(71, ' ') 
        << "|" << printEmptySquareWithPieces(buildings[32]) << "|\n";
  std::cout << "|_______|" << std::string(71, ' ') << "|_______|\n";
  std::cout << "|SLC    |" << std::string(71, ' ') << "|SLC    |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[17]) << "|" << std::string(71, ' ') 
        << "|" << printEmptySquareWithPieces(buildings[33]) << "|\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
  std::cout << "|_______|" << std::string(71, ' ') << "|_______|\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[16])) << "|" << std::string(71, ' ') 
        << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[34])) << "|\n";
  std::cout << "|LHI    |" << std::string(71, ' ') << "|C2     |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[16]) << "|" << std::string(13, ' ') << std::string(45, '_') << std::string(13, ' ') 
        << "|" << printEmptySquareWithPieces(buildings[34]) << "|\n";
    std::cout << "|_______|" << std::string(12, ' ') << "|" << std::string(45, ' ') << "|" << std::string(12, ' ') << "|_______|\n";
    std::cout << "|UWP    |" << std::string(12, ' ') << "| #   #  ##  #####  ###  ###   ###  #   #   # |" << std::string(12, ' ') << "|REV    |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[15]) << "|" << std::string(12, ' ') << "| #   # #  #   #   #   # #  # #   # #   #   # |" << std::string(12, ' ') 
        << "|" << printEmptySquareWithPieces(buildings[35]) << "|\n";
    std::cout << "|       |" << std::string(12, ' ') << "| # # # ####   #   #   # ###  #   # #    # #  |" << std::string(12, ' ') << "|       |\n";
    std::cout << "|       |" << std::string(12, ' ') << "| # # # #  #   #   #   # #    #   # #     #   |" << std::string(12, ' ') << "|       |\n";
    std::cout << "|_______|" << std::string(12, ' ') << "| ##### #  #   #    ###  #     ###  ## #  #   |" << std::string(12, ' ') << "|_______|\n";
    std::cout << "|       |" << std::string(12, ' ') << "|" << std::string(45, '_') << "|" << std::string(12, ' ') <<"|NEEDLES|\n";
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[14])) << "|" << std::string(71, ' ') << "|HALL   |\n";
  std::cout << "|CPH    |" << std::string(71, ' ') << "|       |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[14]) << "|" << std::string(71, ' ') << "|" << printEmptySquareWithPieces(buildings[36]) << "|\n";
  std::cout << "|_______|" << std::string(71, ' ') << "|_______|\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[13])) << "|" << std::string(71, ' ') << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[37])) << "|\n";
  std::cout << "|DWE    |" << std::string(71, ' ') << "|MC     |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[13]) << "|" << std::string(71, ' ') << "|" << printEmptySquareWithPieces(buildings[37]) << "|\n";
  std::cout << "|_______|" << std::string(71, ' ') << "|_______|\n";
  std::cout << "|PAC    |" << std::string(71, ' ') << "|COOP   |\n";
  std::cout << "|       |" << std::string(71, ' ') << "|FEE    |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[12]) << "|" << std::string(71, ' ') << "|" << printEmptySquareWithPieces(buildings[38]) << "|\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
  std::cout << "|_______|" << std::string(71, ' ') << "|_______|\n";
  std::cout << "|       |" << std::string(71, ' ') << "|       |\n";
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[11])) << "|" << std::string(71, ' ') << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[39])) << "|\n";
  std::cout << "|RCH    |" << std::string(71, ' ') << "|DC     |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[11]) << "|" << std::string(71, ' ') << "|" << printEmptySquareWithPieces(buildings[39]) << "|\n";
  std::cout << "|_______|" << std::string(71, '_') << "|_______|\n";
    std::cout << "|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|\n";
    std::cout << "|Line   |" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[9])) << "|"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[8])) << "|HALL   |"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[6])) << "|       |       |"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[3])) << "|       |"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[1])) << "|OSAP   |\n";
    std::cout << "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |\n";
    std::cout << "|" << printEmptySquareWithPieces(buildings[10]) << "|" << printEmptySquareWithPieces(buildings[9]) << "|"
        << printEmptySquareWithPieces(buildings[8]) << "|" << printEmptySquareWithPieces(buildings[7]) << "|"
        << printEmptySquareWithPieces(buildings[6]) << "|" << printEmptySquareWithPieces(buildings[5]) << "|"
        << printEmptySquareWithPieces(buildings[4]) << "|" << printEmptySquareWithPieces(buildings[3]) << "|"
        << printEmptySquareWithPieces(buildings[2]) << "|" << printEmptySquareWithPieces(buildings[1]) << "|"
            << printEmptySquareWithPieces(buildings[0]) << "|\n";
    std::cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|\n";
}

std::string
Board::printImprovements(std::shared_ptr<AcademicBuilding> building) const {
  int numImprovements = building->getNumImprovements();
  std::string result = "";
  for (int i = 0; i < AcademicBuilding::MAX_IMPROVEMENTS; i++) {
    if (numImprovements <= 0) {
      result += "_";
    } else {
      result += "I";
      numImprovements--;
    }
  }
  result += "  ";
  return result;
}

std::string
Board::printEmptySquareWithPieces(std::shared_ptr<Building> building) const {
  std::string result = "";
  for (auto &piece : building->getVisitingPieces()) {
    result += piece;
  }
  while (result.size() < 7) {
    result += " ";
  }
  return result;
}

const std::vector<std::shared_ptr<Building>> &Board::getBuildings() const {
  return buildings;
}
