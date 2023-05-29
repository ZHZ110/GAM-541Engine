#include "pch.h"
#include "PlayerController.h"
#include "InputSystem.h"

extern InputSystem* INPUTSYS;

PlayerController::PlayerController() {

}

void PlayerController::HandleKeyPressed(const unsigned char keycode, Command* command) {
	keypress_command_map.push_back(std::pair<const unsigned char, Command*>(keycode, command));
}

void PlayerController::HandleKeyTriggered(const unsigned char keycode, Command* command) {
	keytrigger_command_map.push_back(std::pair<const unsigned char, Command*>(keycode, command));
}

void PlayerController::ResetPlayerController() {
	while (!keypress_command_map.empty()) {
		delete keypress_command_map.back().second;
		keypress_command_map.pop_back();
	}

	while (!keytrigger_command_map.empty()) {
		delete keytrigger_command_map.back().second;
		keytrigger_command_map.pop_back();
	}
}

void PlayerController::Update(float dt) {
	for (int i = 0; i < keypress_command_map.size(); ++i) {
		if (INPUTSYS->KeyIsPressed(keypress_command_map[i].first)) {
			keypress_command_map[i].second->execute(actor);
		}
	}

	for (int i = 0; i < keytrigger_command_map.size(); ++i) {
		if (INPUTSYS->KeyIsTriggered(keytrigger_command_map[i].first)) {
			keytrigger_command_map[i].second->execute(actor);
		}
	}
}