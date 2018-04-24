#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <random>

class CellGrid
{
public:
	CellGrid();
	CellGrid(int numberCellsX, int numberCellsY, int cellWidth, int cellHeight, int FPS);
	~CellGrid();

	void draw(sf::RenderWindow& window);
	int getIndexVertex(int i, int j);
	int getIndex(int i, int j);
	sf::Color randomGray();
	void setCellColor(int i, int j);
	void setCellPosition(int i, int j);
	void setOldGrid();
	void update(float dT);
	int updateCell(int i, int j);

private:
	int FPS;
	int numberCellsX;
	int numberCellsY;
	int cellWidth;
	int cellHeight;
	std::vector<int>			oldGrid;
	std::vector<int>			newGrid;
	std::vector<sf::Vertex>		vertexGrid;
};

