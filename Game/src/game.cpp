#include"game.h"
#include <random>
#include <ctime>

Game::Game()
{
	srand(time(0)); 

	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("Sounds/Sounds_music.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Sounds/Sounds_rotate.mp3");
	ClearSound=LoadSound("Sounds/Sounds_clear.mp3");
}
Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(ClearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}
Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}

	int  randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);

	return block;

}
std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(),JBlock(), LBlock(),OBlock(),SBlock(),TBlock(),ZBlock() };
}

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw(11, 11);
	nextBlock.Draw(270, 270);
	/*switch (nextBlock.id)
	{
	case 1:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255, 280);
		break;
	default:
		nextBlock.Draw(270, 270);
		break; 
	}*/
}
void Game::HandelInput() 
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
	}

	switch (keyPressed)
	{
	case KEY_LEFT:
			MovesBlockLeft();
			break;
	case KEY_RIGHT:
			MovesBlockRight();
			break;
	case KEY_DOWN:
			MovesBlockDown();
			break;
	case KEY_UP:
		RotateBlock();
		break;	
	}
}

void Game::MovesBlockLeft()
{
	if (!gameOver) 
	{
		currentBlock.Move(0, -1);
		if (IsBlockOutSide() || BlockFits() == false)
		{
			currentBlock.Move(0, 1);
		}
	}
	

}
void Game::MovesBlockRight()
{
	if (!gameOver)
	{
		currentBlock.Move(0, 1);
		if (IsBlockOutSide() || BlockFits() == false)
		{
			currentBlock.Move(0, -1);
		}
	}
}
void Game::MovesBlockDown()
{
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (IsBlockOutSide() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}

		updateScore(0, 1);
	}
}
bool Game::IsBlockOutSide()
{
	std::vector<Position>titles = currentBlock.getCellPositions();
	for (Position item : titles)
	{
		if (grid.isCellOutSide(item.row, item.column)) {
			return true;
		}
		
	}
	return false;
}
void Game::RotateBlock()
{
	currentBlock.Rotate();
	if (IsBlockOutSide() || BlockFits() == false)
	{
		currentBlock.UndoRotation();
	}
	else {
		PlaySound(rotateSound);
	}

}

void Game::LockBlock()
{
	std::vector<Position>titles = currentBlock.getCellPositions();
	for (Position item : titles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;

	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = GetRandomBlock();

	int rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0)
	{
		PlaySound(ClearSound);
		updateScore(rowsCleared, 0);

	}
}

bool Game::BlockFits()
{
	std::vector<Position>titles = currentBlock.getCellPositions();
	for (Position item : titles)
	{
		if (grid.isCellEmpty(item.row, item.column) == false) 
		{
			return false;
		}
	}
	return true;
}

void Game::Reset()
{
	grid.initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
}

void Game::updateScore(int LineClreared, int moveDownPoints)
{
	switch (LineClreared)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}
	score += moveDownPoints;
}
