#include "CellGrid.h"
#include <iostream>

namespace cellState
{
	int dead = 0;
	int alive = 1;
}

namespace cellColor
{
	sf::Color dead(255, 255, 255);
	sf::Color alive(0, 0, 0);
}

CellGrid::CellGrid()
{
}

CellGrid::CellGrid(int numberCellsX, int numberCellsY, int cellWidth, int cellHeight, int FPS)
{
	this->FPS = FPS;
	this->cellHeight = cellHeight;
	this->cellWidth = cellWidth;
	this->numberCellsX = numberCellsX;
	this->numberCellsY = numberCellsY;

	oldGrid = std::vector<int>(numberCellsX * numberCellsY);
	newGrid = std::vector<int>(numberCellsX * numberCellsY);

	vertexGrid = std::vector<sf::Vertex>(numberCellsX * numberCellsY * 4);

	for (int i = 1; i < numberCellsY - 1; i++) {
		for (int j = 1; j < numberCellsX - 1; j++) {
			newGrid[getIndex(i, j)] = rand() % 2;
			setCellPosition(i, j);
			setCellColor(i, j);
		}
	}
	setOldGrid();
}

CellGrid::~CellGrid()
{
}

void CellGrid::draw(sf::RenderWindow & window)
{
	window.draw(vertexGrid.data(), vertexGrid.size(), sf::Quads);
}

int CellGrid::getIndexVertex(int i, int j)
{
	return (j + i * numberCellsX) * 4;
}

int CellGrid::getIndex(int i, int j)
{
	return (j + i *numberCellsX);
}

sf::Color CellGrid::randomGray()
{
	int rand = std::rand() % 256;
	return sf::Color(rand,rand,rand);
}

void CellGrid::setCellColor(int i, int j)
{
	sf::Color color;
	if (newGrid[getIndex(i, j)] == cellState::dead) {
		color = cellColor::dead;
	}
	else {
		color = cellColor::alive;
	}

	int indexVertex = getIndexVertex(i, j);
	vertexGrid[indexVertex].color		= color;
	vertexGrid[indexVertex + 1].color	= color;
	vertexGrid[indexVertex + 2].color	= color;
	vertexGrid[indexVertex + 3].color	= color;
}

void CellGrid::setCellPosition(int i, int j)
{
	int index = getIndexVertex(i, j);
	vertexGrid[index].position		= sf::Vector2f(j * (cellWidth + 1) + j, i * (cellHeight + 1) + i);
	vertexGrid[index + 1].position	= sf::Vector2f(j * (cellWidth + 1) + cellWidth + j, i * (cellHeight + 1) + i);
	vertexGrid[index + 2].position	= sf::Vector2f(j * (cellWidth + 1) + cellWidth + j, i * (cellHeight + 1) + cellHeight + i);
	vertexGrid[index + 3].position	= sf::Vector2f(j * (cellWidth + 1) + j, i * (cellHeight + 1) + cellHeight + i);
}

void CellGrid::setOldGrid()
{
	for (int i = 0; i < newGrid.size(); i++) {
		oldGrid[i] = newGrid[i];
	}
}

void CellGrid::update(float dT)
{
	static float totalTime = 0;
	static float switchTime = 1 / (float)FPS;

	if (totalTime > switchTime) {
		totalTime -= switchTime;

		for (int i = 1; i < numberCellsY - 1; i++) {
			for (int j = 1; j < numberCellsX - 1; j++) {
				int state = updateCell(i, j);
				setCellColor(i, j);
			}
		}
		setOldGrid();
	}
	else {
		totalTime += dT;
	}
}

int CellGrid::updateCell(int i, int j)
{
	int cellsAlive = 0;
	if (oldGrid[getIndex(i - 1, j - 1)] == cellState::alive)
		cellsAlive++;
	if (oldGrid[getIndex(i - 1, j)] == cellState::alive)
		cellsAlive++;
	if (oldGrid[getIndex(i - 1, j + 1)] == cellState::alive)
		cellsAlive++;
	if (oldGrid[getIndex(i, j - 1)] == cellState::alive)
		cellsAlive++;
	if (oldGrid[getIndex(i, j + 1)] == cellState::alive)
		cellsAlive++;
	if (oldGrid[getIndex(i + 1, j - 1)] == cellState::alive)
		cellsAlive++;
	if (oldGrid[getIndex(i + 1, j)] == cellState::alive)
		cellsAlive++;
	if (oldGrid[getIndex(i + 1, j + 1)] == cellState::alive)
		cellsAlive++;
	
	if (cellsAlive < 2 || cellsAlive > 3)
		newGrid[getIndex(i, j)] = cellState::dead;
	if (cellsAlive == 3)
		newGrid[getIndex(i, j)] = cellState::alive;
	return cellsAlive;
}

