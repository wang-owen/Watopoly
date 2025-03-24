#include "Command.h"
#include "CommandContext.h"

Command::Command(std::weak_ptr<CommandContext> context) : context{context} {}
