#include "iostream"
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

Board::Board() {
  buildings.reserve(40);
  auto slc = std::make_shared<RollUpTheRimDecorator>(std::make_shared<SLC>());
  auto needles_hall =
      std::make_shared<RollUpTheRimDecorator>(std::make_shared<NeedlesHall>());

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
  buildings.emplace_back(std::make_shared<GoToTims>());
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
    std::cout << "_________________________________________________________________________________________" << std::endl;
    std::cout << "|Goose |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |" << std::endl;
    std::cout << "|Nesting|" 
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[21]))
        << "|HALL   |" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[23])) << "|"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[24])) << "|       |"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[26])) << "|"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[27])) << "|       |"
        << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[29])) << "|TIMS   |" << std::endl;
    std::cout << "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |" << std::endl;
    std::cout << "|" << printEmptySquareWithPieces(buildings[20]) << "|" << printEmptySquareWithPieces(buildings[21]) << "|" 
        << printEmptySquareWithPieces(buildings[22]) << "|" << printEmptySquareWithPieces(buildings[23]) 
        << "|" << printEmptySquareWithPieces(buildings[24]) << "|" << printEmptySquareWithPieces(buildings[25]) 
        << "|" << printEmptySquareWithPieces(buildings[26]) << "|" << printEmptySquareWithPieces(buildings[27]) 
        << "|" << printEmptySquareWithPieces(buildings[28]) << "|" << printEmptySquareWithPieces(buildings[29]) 
        << "|" << printEmptySquareWithPieces(buildings[30]) << "|" << std::endl;
    std::cout << "|       |" << "|       |" << "|       |" << "|       |" << "|       |" << "|       |" << "|       |" << "|       |" << "|       |"  << "|       |" << "|       |" << std::endl; 
    std::cout << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << std::endl;
    std::cout << "|       |" << std::string(71, ' ') << "|       |" << std::endl;
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[19])) << "|" << std::string(71, ' ') 
        << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[31])) << "|" << std::endl;
    std::cout << "|OPT    |" << std::string(71, ' ') << "|EIT    |" << std::endl;
    std::cout << "|" << printEmptySquareWithPieces(buildings[19]) << "|" << std::string(71, ' ') 
        << "|" << printEmptySquareWithPieces(buildings[31]) << "|" << std::endl;
    std::cout << "|_______|" << std::string(71, ' ') << "|_______|" << std::endl;
    std::cout << "|       |" << std::string(71, ' ') << "|       |" << std::endl;
    std::cout << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[18])) << "|" << std::string(71, ' ') 
        << "|" << printImprovements(std::dynamic_pointer_cast<AcademicBuilding>(buildings[32])) << "|" << std::endl;
}

std::string Board::printImprovements(std::shared_ptr<AcademicBuilding> building) const {
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

std::string Board::printEmptySquareWithPieces(std::shared_ptr<Building> building) const {
    std::string result = "";
    for (auto& piece : building->getVisitingPieces()) {
        result += piece;
    }
    while (result.size() < 7) { // magic number maybe change later
        result += " ";
    }
    return result;
}

const std::vector<std::shared_ptr<Building>> &Board::getBuildings() const {
  return buildings;
}