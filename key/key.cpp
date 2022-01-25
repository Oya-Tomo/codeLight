#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>

#include "key.h"

const std::vector<std::string> ctrlKeyList = {
	"<[ctrl-a]>",
	"<[ctrl-b]>",
	"<[ctrl-c]>",
	"<[ctrl-d]>",
	"<[ctrl-e]>",
	"<[ctrl-f]>",
	"<[ctrl-g]>",
	"<[ctrl-h]>",
	"<[ctrl-i]>",
	"<[ctrl-j]>",
	"<[ctrl-k]>",
	"<[ctrl-l]>",
	"<[ctrl-m]>",
	"<[ctrl-n]>",
	"<[ctrl-o]>",
	"<[ctrl-p]>",
	"<[ctrl-q]>",
	"<[ctrl-r]>",
	"<[ctrl-s]>",
	"<[ctrl-t]>",
	"<[ctrl-u]>",
	"<[ctrl-v]>",
	"<[ctrl-w]>",
	"<[ctrl-x]>",
	"<[ctrl-y]>",
	"<[ctrl-z]>",
};

std::string keyBind() {
	int c;
	c = _getch();
	bool ctrlState = (bool)(GetKeyState(VK_CONTROL) & 0x8000);

	std::vector<int> stdi;
	stdi.push_back(c);

	while (_kbhit() != 0) {
		c = _getch();
		stdi.push_back(c);
	}

	std::string stds(stdi.begin(), stdi.end());

	if (ctrlState && c <= 26) {
		return ctrlKeyList[(int)c - 1];
	}
	else if (stds == "\b") {
		return "<[back]>";
	}
	else if (stds == "\r") {
		return "<[enter]>";
	}
	else if (stds == "\t") {
		return "<[tab]>";
	}
	else if (stdi == std::vector<int>({ 224, 72 })) {
		return "<[up]>";
	}
	else if (stdi == std::vector<int>({ 224, 75 })) {
		return "<[left]>";
	}
	else if (stdi == std::vector<int>({ 224, 77 })) {
		return "<[right]>";
	}
	else if (stdi == std::vector<int>({ 224, 80 })) {
		return "<[down]>";
	}
	else if (stdi == std::vector<int>({ 0, 59 })) {
		return "<[f1]>";
	}
	else if (stdi == std::vector<int>({ 0, 60 })) {
		return "<[f2]>";
	}
	else if (stdi == std::vector<int>({ 0, 61 })) {
		return "<[f3]>";
	}
	else if (stdi == std::vector<int>({ 0, 62 })) {
		return "<[f4]>";
	}
	else if (stdi == std::vector<int>({ 0, 63 })) {
		return "<[f5]>";
	}
	else if (stdi == std::vector<int>({ 0, 64 })) {
		return "<[f6]>";
	}
	else if (stdi == std::vector<int>({ 0, 65 })) {
		return "<[f7]>";
	}
	else if (stdi == std::vector<int>({ 0, 66 })) {
		return "<[f8]>";
	}
	else if (stdi == std::vector<int>({ 0, 67 })) {
		return "<[f9]>";
	}
	else if (stdi == std::vector<int>({ 0, 68 })) {
		return "<[f10]>";
	}
	else if (stdi == std::vector<int>({ 224, 133 })) {
		return "<[f11]>";
	}
	else if (stdi == std::vector<int>({ 224, 134 })) {
		return "<[f12]>";
	}
	else if (stdi == std::vector<int>({ 224, 82 })) {
		return "<[insert]>";
	}
	else if (stdi == std::vector<int>({ 224, 83 })) {
		return "<[delete]>";
	}

	return stds;
}
