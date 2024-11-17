#pragma once
#include<vector>
#include<raylib.h>

class Grid
{
public:
	Grid();
	void initialize();
	void Print();
	void Draw();
	int grid[20][10];
	bool isCellOutSide(int row, int column);
	bool isCellEmpty(int row, int column);
	int ClearFullRows();


private:
	bool isRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color>colors;
};