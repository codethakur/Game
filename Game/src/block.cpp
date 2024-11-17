#include"block.h"

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
	rowOffset = 0;
	columnOffset = 0;

}
void Block::Draw(int offsetX, int offsetY)
{
	std::vector<Position>titles = getCellPositions();

	for (Position item : titles) {
		DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize+offsetY,
			cellSize-1, cellSize-1, colors[id]);
	}
}

void Block::Move(int row, int column)
{
	rowOffset += row;
	columnOffset += column;

}

std::vector<Position>Block::getCellPositions()
{
	std::vector<Position>titles = cells[rotationState];
	std::vector<Position>moveTitles;
	for (Position item : titles)
	{
		Position newPos = Position(item.row + rowOffset, item.column+columnOffset);
		moveTitles.push_back(newPos);
	}
	return moveTitles;
}
void Block::Rotate() 
{
	rotationState++;
	if (rotationState == (int)cells.size()) {
		rotationState = 0;
	}
}

void Block::UndoRotation() // Corrected typo here
{
	rotationState--;
	if (rotationState == -1) {
		rotationState = cells.size() - 1;
	}
}