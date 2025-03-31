module ImproveCommand;
import <iostream>;
import <sstream>;
import AcademicBuilding;
import CommandContext;

const std::string ImproveCommand::NAME = "improve";

ImproveCommand::ImproveCommand(std::shared_ptr<CommandContext> context)
    : Command{context} {}

void ImproveCommand::execute(const std::vector<std::string> &params) {
  if (params.size() != 2 || (params[1] != "buy" && params[1] != "sell")) {
    std::cout << "Usage: improve <property> buy/sell\n";
    return;
  }

  auto &player = context->cur_player;
  auto &player_properties = player->getProperties();
  if (!player_properties.count(params[0])) {
    std::cout << "You do not own " << params[0] << "!\n";
    return;
  }

  if (auto building = std::dynamic_pointer_cast<AcademicBuilding>(
          player->getProperties().at(params[0]))) {
    auto name = building->getName();

    // Verify that owner owns entire monopoly
    for (auto &b_name : building->getBlockBuildings(building->getBlock())) {
      if (!player_properties.count(b_name)) {
        std::cout
            << "You cannot improve a building without owning its monopoly!\n";
        return;
      }
    }

    if (params[1] == "buy") {
      // Buy
      if (building->getNumImprovements() >=
          AcademicBuilding::MAX_IMPROVEMENTS) {
        std::cout << name
                  << " already has the maximum number of improvements!\n";
        return;
      }

      auto cost = building->getImprovementCost();
      std::cout << "Improvement cost: $" << cost << ". Purchase? (y/n)";
      while (true) {
        std::string input, extra;
        char answer;
        std::getline(std::cin, input);
        std::istringstream iss{input};

        if (!(iss >> answer) || (iss >> extra)) {
          std::cout << "Invalid input. Try again.\n";
          continue;
        }

        switch (std::tolower(answer)) {
        case 'y': {
          if (player->getBalance() < cost) {
            std::cout << "Insufficient funds.\n";
            return;
          }
          player->reduceFunds(cost);
          building->improve();

          context->board->displayBoard();
          std::cout << name << " has been improved!\n";
          std::cout << "New tuition cost: $" << building->getFee() << "\n";
          return;
        }
        case 'n': {
          return;
        }
        default:
          continue;
        }
      }
    } else {
      // Sell
      if (building->getNumImprovements() == 0) {
        std::cout << name << " already has no improvements!\n";
        return;
      }

      auto cost = building->getImprovementCost() / 2;
      std::cout << "Improvement cost: $" << cost << ". Sell? (y/n)";
      while (true) {
        std::string input, extra;
        char answer;
        std::getline(std::cin, input);
        std::istringstream iss{input};

        if (!(iss >> answer) || (iss >> extra)) {
          std::cout << "Invalid input. Try again.\n";
          continue;
        }

        switch (std::tolower(answer)) {
        case 'y': {
          player->increaseFunds(cost);
          building->impair();

          context->board->displayBoard();
          std::cout << name << " has lost an improvement.\n";
          std::cout << "New tuition cost: $" << building->getFee() << "\n";
          return;
        }
        case 'n': {
          return;
        }
        default:
          continue;
        }
      }
    }
  } else {
    std::cout << "You can only improve academic buildings.\n";
  }
}
