#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <regex>
#include <numeric>
#include <Windows.h>
#include "main.h"
#include "tab/tab.h"
#include "key/key.h"

int main() {

	Tab tab = Tab();
	tab.setViewRange(0, 50);

	std::string text;
	std::vector<std::string> viewText;
	std::string view = "";
	std::vector<int> pos;

	while (true) {
		text = keyBind();
		tab.editText(text);
		viewText = tab.getViewText();
		view = "";
		
		for (int i = 0; i < viewText.size(); i++) {
			if (i == viewText.size() - 1) {
				viewText[i] = std::regex_replace(viewText[i], std::regex("(</?!?)([a-z]*[A-Z]*[0-9]*)([^>]*)(>)"), "$1\033[34m$2\033[33m$3\033[m$4");
			}
			else {
				viewText[i] = std::regex_replace(viewText[i], std::regex("(</?!?)([a-z]*[A-Z]*[0-9]*)([^>]*)(>)"), "$1\033[34m$2\033[33m$3\033[m$4") + "\n";
			}
		}

		view = std::accumulate(viewText.begin(), viewText.end(), view);

		std::cout << "\033[?25l";
		pos = tab.getCursorPos();
		system("cls");
		std::cout << view;
		std::cout << "\033[?25h";
		std::cout << "\033[" << pos[0] + 1 << ";" << pos[1] + 1 << "H";
	}

	return 0;
}

//int main() {
//	std::string test = "a‚ ";
//	std::cout << (bool)IsDBCSLeadByte(test[0]) << std::endl;
//	std::cout << (bool)IsDBCSLeadByte(test[1]) << std::endl;
//	std::cout << (bool)IsDBCSLeadByte(test[2]) << std::endl;
//
//	return 0;
//}