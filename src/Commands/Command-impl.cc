module Command;
import CommandContext;

Command::Command(std::shared_ptr<CommandContext> context) : context{context} {}
