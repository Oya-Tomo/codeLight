#include <Windows.h>
#include <numeric>
#include <regex>
#include "tab.h"

Tab::Tab() {
	this->fileName = "";
	this->editingText = std::vector<std::string>({""});
	this->viewRangeStart = 0;
	this->viewRange = 20;
	this->x = 0;
	this->y = 0;
	this->row = 0;
}

void Tab::setViewRange(int start, int range) {
	this->viewRangeStart = start;
	this->viewRange = range;
}

void Tab::editText(std::string keyBindString) {
	std::string origin_txt = keyBindString;

	std::smatch m;

	if (std::regex_match(keyBindString, m, std::regex(R"(<\[.*\]>)"))) {
	
		if (keyBindString == "<[up]>") {
			this->moveCursor(keyBindString);
		}
		else if (keyBindString == "<[down]>") {
			this->moveCursor(keyBindString);
		}
		else if (keyBindString == "<[left]>") {
			this->moveCursor(keyBindString);
		}
		else if (keyBindString == "<[right]>") {
			this->moveCursor(keyBindString);
		}
		else if (keyBindString == "<[enter]>") {
			this->pressEnter();
		}
		else if (keyBindString == "<[back]>") {
			this->pressBack();
		}
		else if (keyBindString == "<[delete]>") {

		}
		else if (keyBindString == "<[tab]>") {
			this->editingText[this->y].insert(this->x, "    ");
			this->x += 4;
			this->row += 4;
		}
	}
	else {
	while (!origin_txt.empty()) {
		if (IsDBCSLeadByte(origin_txt[0]) == 0) { // ”¼Šp
			this->editingText[this->y].insert(this->x, origin_txt.substr(0, 1));
			origin_txt.erase(0, 1);
			this->x += 1;
			this->row += 1;
		}
		else { // ‘SŠp
			this->editingText[this->y].insert(this->x, origin_txt.substr(0, 2));
			origin_txt.erase(0, 2);
			this->x += 2;
			this->row += 2;
		}
	}
	}
}

std::vector<std::string> Tab::getViewText() {
	if (this->viewRangeStart + this->viewRange <= this->editingText.size()) {
		std::vector<std::string> viewText{ this->editingText.begin() + this->viewRangeStart, this->editingText.begin() + this->viewRangeStart + this->viewRange };
		return viewText;
	}
	else {
		std::vector<std::string> viewText{ this->editingText.begin() + this->viewRangeStart, this->editingText.end() };
		return viewText;
	}
}

std::vector<int> Tab::getCursorPos() {
	std::vector<int> pos{ this->y, this->x };
	return pos;
}

void Tab::moveCursor(std::string keyBindText) {
	if (keyBindText == "<[up]>") {
		if (this->y == 0) {
			this->x = 0;
		}
		else {
			this->y--;
			if (this->row <= this->editingText[this->y].length()) {
				this->x = this->row;
			}
			else {
				this->x = this->editingText[this->y].length();
			}
		}
	}
	else if (keyBindText == "<[down]>") {
		if (this->y == this->editingText.size() - 1) {
			this->x = this->editingText[this->y].length();
		}
		else {
			this->y++;
			if (this->row <= this->editingText[this->y].length()) {
				this->x = this->row;
			}
			else {
				this->x = this->editingText[this->y].length();
			}
		}
	}
	else if (keyBindText == "<[left]>") {
		if (this->x == 0) {
			if (this->y != 0) {
				this->y--;
				this->x = this->editingText[this->y].length();
			}
		}
		else {
			if (this->x == 1) {
				this->x = 0;
			}
			else if ((bool)IsDBCSLeadByte(this->editingText[this->y][this->x - 2]) == 1) {
				this->x -= 2;
			}
			else {
				this->x--;
			}
		}
		this->row = this->x;
	}
	else if (keyBindText == "<[right]>") {
		if (this->x == this->editingText[this->y].length()) {
			if (this->y != this->editingText.size() - 1) {
				this->y++;
				this->x = 0;
			}
		}
		else {
			if ((bool)IsDBCSLeadByte(this->editingText[this->y][this->x]) == 1) {
				this->x += 2;
			}
			else {
				this->x++;
			}
		}
		this->row = this->x;

	}
}

void Tab::pressEnter() {
	if (this->x == 0) {
		this->editingText.insert(this->editingText.begin() + this->y, "");
		this->y += 1;
		this->x = 0;
		this->row = 0;
	}
	else if (this->x == this->editingText[this->y].size()) {
		this->y += 1;
		this->editingText.insert(this->editingText.begin() + this->y, "");
		this->x = 0;
		this->row = 0;
	}
	else {
		std::string substr = this->editingText[this->y].substr(this->x);
		this->editingText[this->y].erase(this->x);
		this->y += 1;
		this->editingText.insert(this->editingText.begin() + this->y, substr);
		this->x = 0;
		this->row = 0;
	}
}

void Tab::pressBack() {
	if (this->x == 0) {
		if (this->y != 0) {
			this->x = this->editingText[this->y - 1].length();
			this->editingText[this->y - 1] += this->editingText[this->y];
			this->editingText.erase(this->editingText.begin() + this->y, this->editingText.begin() + this->y + 1);
			this->y--;
		}
	}
	else {
		if (x == 1) {
			this->editingText[this->y].erase(this->editingText[this->y].begin(), this->editingText[this->y].begin() + 1);
			this->x--;
		}
		else {
			if ((bool)IsDBCSLeadByte(this->editingText[this->y][this->x - 2]) == 1) {
				this->editingText[this->y].erase(this->x - 2, 2);
				this->x -= 2;
			}
			else {
				this->editingText[this->y].erase(this->x - 1, 1);
				this->x--;
			}
		}
	}
	this->row = this->x;
}

void Tab::pressDelete()
{
}
