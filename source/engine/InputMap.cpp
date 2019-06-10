#include "InputMap.h"

#include <iostream>


InputMap::InputMap() {
	m_eventQuit = false;
}

InputMap::~InputMap() {

}



void InputMap::Update() {
	for (auto& obj : m_map) {
		obj.second.value = 0.0f;
		obj.second.status = KEY_STATUS_NONE;
	}

	for (auto& obj : m_keys) {
		if (obj.status == KEY_STATUS_RELEASED)
			obj.status = KEY_STATUS_NONE; // released last frame
		else if (obj.status == KEY_STATUS_PRESSED)
			obj.status = KEY_STATUS_ACTIVE; // pressed lat frame
	}

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		for (auto& obj : m_keys) {
			if (obj.key == event.key.keysym.sym) {
				if (event.type == SDL_KEYDOWN)
					obj.status = KEY_STATUS_PRESSED;
				else if (event.type == SDL_KEYUP) 
					obj.status = KEY_STATUS_RELEASED;
			}

		}
		if (event.type == SDL_QUIT) {
			m_eventQuit = true;
		}
	}

	for (auto& obj : m_keys) {
		// Updates all the map values
		for (auto& map : obj.maps) {
			if (obj.status == KEY_STATUS_ACTIVE || obj.status == KEY_STATUS_PRESSED)
				m_map[map].value += obj.value;

			if (m_map[map].status == KEY_STATUS_NONE || m_map[map].status == KEY_STATUS_ACTIVE) {
				m_map[map].status = obj.status;
			}
		}
	}
}


float InputMap::GetValue(std::string map) {
	return m_map[map].value;
}
bool InputMap::Pressed(std::string map) {
	return m_map[map].status == KEY_STATUS_PRESSED;
}
bool InputMap::Active(std::string map) {
	return m_map[map].status == KEY_STATUS_ACTIVE || m_map[map].status == KEY_STATUS_PRESSED;
}
bool InputMap::Released(std::string map) {
	return m_map[map].status == KEY_STATUS_RELEASED;
}

void InputMap::NewMap(std::string map) {
	m_map[map] = MapStatus();
}
void InputMap::BindKey(std::string map, int key, float value) {
	for (auto& obj : m_keys) {
		if (obj.key == key) {
			obj.maps.emplace_back(map);
			return;
		}
	}

	m_keys.emplace_back(InputValue());

	m_keys.back().key = key;
	m_keys.back().value = value;
	m_keys.back().maps.emplace_back(map);
}

bool InputMap::GetQuitEvent() {
	return m_eventQuit;
}