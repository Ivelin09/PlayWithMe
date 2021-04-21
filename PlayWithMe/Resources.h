#pragma once

#include<unordered_map>
#include<vector>

#include "Game.h"

struct Resources {
	std::unordered_map<std::string, std::vector<unsigned int>> table;
	bool change = false;

	std::vector<unsigned int>& getSector(std::string secName) {
		return this->table[secName];
	}

	void levelUp(std::string secName, GAME_TYPE gameName) {
		table[secName][gameName]++;
		change = true;

		return;
	}

	bool isChanged() const {
		return this->change;
	}

	void levelUp(std::string secName, GAME_TYPE gameName, const int stars) {
		table[secName][gameName] += stars;
		change = true;

		return;
	}


	std::unordered_map<std::string, std::vector<unsigned int>>& getInfo() {
		change = false;
		return this->table;
	}

	Resources operator++() {

	}

};