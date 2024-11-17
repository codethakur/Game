#pragma once
#include"blocks.cpp"
#include "grid.h"
class Game 
{
public:
	Game();
	~Game();
	void Draw();
	void HandelInput();
	void MovesBlockDown();
	bool gameOver;
	int score;
	Music music;
private:
	void MovesBlockLeft();
	void MovesBlockRight();
	Block GetRandomBlock();
	std::vector<Block>GetAllBlocks();
	bool IsBlockOutSide();
	void RotateBlock();
	void LockBlock();
	bool BlockFits();
	void Reset();
	Grid grid;
	void updateScore(int LineClreared, int moveDownPoints);
	std::vector<Block>blocks;
	Block currentBlock;
	Block nextBlock;
	Sound rotateSound;
	Sound ClearSound;
};
