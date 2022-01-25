#pragma once
#ifndef TAB_H
#define TAB_H

#include <iostream>
#include <string>
#include <vector>

class Tab
{
public:
	Tab();
	void setViewRange(int start, int range);
	void editText(std::string keyBindString);
	std::vector<std::string> getViewText();
	std::vector<int> getCursorPos();

private:
	std::string fileName;
	std::vector<std::string> editingText;
	int viewRangeStart;
	int viewRange;
	int x;
	int y;
	int row;
	void moveCursor(std::string keyBindText);
	void pressEnter();
	void pressBack();
	void pressDelete();
};

#endif // !TAB_H
