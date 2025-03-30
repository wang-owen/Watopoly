#include "Command.h"
#include "CommandContext.h"

Command::Command(std::shared_ptr<CommandContext> context) : context{context} {}
