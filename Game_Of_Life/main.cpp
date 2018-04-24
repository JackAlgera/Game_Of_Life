#include <SFML\Graphics.hpp>
#include <iostream>
#include "CellGrid.h"

int WINDOW_HEIGHT = 800;
int WINDOW_WIDTH = 1000;
float nbrCellsX, nbrCellsY;
int cellWidth, cellHeight, FPS;

int multiplier = 5;
int viewSpeed = 300;

bool qPressed, dPressed, zPressed, sPressed, upPressed, downPressed, pPressed;
bool isPaused = true;

void moveView(float dT, sf::View& view);

int main() {
	std::cout << "Choose window width (number of entities on X axis)\n";
	std::cin >> nbrCellsX;
	std::cout << "Choose window heigth (number of entities on Y axis)\n";
	std::cin >> nbrCellsY;
	std::cout << "Choose the speed of the game (FPS)\n";
	std::cin >> FPS;
	std::cout << "\nPress P to unpause and pause the game.\nZoom in and out with the up and down arrows and move the camera around with the qdsz keys.\n";
	cellWidth = ((float)(multiplier * WINDOW_WIDTH - 1) / (float)nbrCellsX) - 1;
	cellHeight = ((float)(multiplier * WINDOW_HEIGHT - 1) / (float)nbrCellsY) - 1;
	sf::View view(sf::Vector2f(WINDOW_WIDTH*multiplier / 2, WINDOW_HEIGHT*multiplier / 2), sf::Vector2f(WINDOW_WIDTH*multiplier / 4, WINDOW_HEIGHT*multiplier / 4));
	
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game Of Life");
	CellGrid grid(nbrCellsX, nbrCellsY, cellWidth, cellHeight, FPS);
	sf::Clock clock;
	float dT = clock.restart().asSeconds();


	window.setFramerateLimit(60);
	window.setView(view);

	while (window.isOpen()){
		float dT = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::Q:
						qPressed = true;
						break;
					case sf::Keyboard::D:
						dPressed = true;
						break;
					case sf::Keyboard::S:
						sPressed = true;
						break;
					case sf::Keyboard::Z:
						zPressed = true;
						break;
					case sf::Keyboard::Down:
						downPressed = true;
						break;
					case sf::Keyboard::Up:
						upPressed = true;
						break;
					case sf::Keyboard::P:
						if (!pPressed) {
							pPressed = true;
							isPaused = !isPaused;
						}
						break;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
					case sf::Keyboard::Q:
						qPressed = false;
						break;
					case sf::Keyboard::D:
						dPressed = false;
						break;
					case sf::Keyboard::S:
						sPressed = false;
						break;
					case sf::Keyboard::Z:
						zPressed = false;
						break;
					case sf::Keyboard::Down:
						downPressed = false;
						break;
					case sf::Keyboard::Up:
						upPressed = false;
						break;
					case sf::Keyboard::P:
						pPressed = false;
						break;
				}
			}
		}

		window.clear();
		moveView(dT, view);
		window.setView(view);
		if(!isPaused)
			grid.update(dT);
		grid.draw(window);
		window.display();
	}

	return 0;
}

void moveView(float dT, sf::View& view) {
	if (qPressed)
		view.move(- viewSpeed*dT, 0);
	if (dPressed)
		view.move(viewSpeed*dT, 0);
	if (zPressed)
		view.move(0, - viewSpeed*dT);
	if (sPressed)
		view.move(0, viewSpeed*dT);
	if (upPressed)
		view.zoom(1 - 0.5 * dT);
	if (downPressed)
		view.zoom(1 + 0.5 * dT);
}