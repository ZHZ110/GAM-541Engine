#pragma once

#include "IController.h"
#include "Command.h"
#include <vector>

class PlayerController : public IController {
public:
	PlayerController();
	void HandleKeyPressed(const unsigned char keycode, Command* command);
	void HandleKeyTriggered(const unsigned char keycode, Command* command);
	void ResetPlayerController();
	void Update(float dt) override;

private:
	std::vector<std::pair<const unsigned char, Command*>> keypress_command_map;
	std::vector<std::pair<const unsigned char, Command*>> keytrigger_command_map;
};