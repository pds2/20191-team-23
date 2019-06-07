#ifndef INPUT_MAP_H
#define INPUT_MAP_H

#include <unordered_map>
#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "InputNames.h"

enum KeyStatus {
	KEY_STATUS_NONE,
	KEY_STATUS_PRESSED,
	KEY_STATUS_ACTIVE,
	KEY_STATUS_RELEASED
};

// class Window;

class InputMap {
public:
	InputMap();
	virtual ~InputMap();

	void Update();
	
	float GetValue(std::string map);
	bool Pressed(std::string map);
	bool Active(std::string map);
	bool Released(std::string map);

	void NewMap(std::string map);
	void BindKey(std::string map, int key, float value);

	bool GetQuitEvent();
private:

	struct InputValue {
		InputValue() : status(-1){}

		int key;
		int status; // (KeyStatus enum) 
		float value;

		std::vector<std::string> maps;
	};

	struct MapStatus {
		MapStatus(): value(0.0), status(-1) {}

		float value;
		int status; // (KeyStatus enum) 
	};

	float m_value;
	bool m_eventQuit;

	std::vector<InputValue> m_keys;
	std::unordered_map<std::string, MapStatus> m_map;
};

#endif