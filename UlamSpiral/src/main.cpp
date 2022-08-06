#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <cstring>
#pragma warning(disable:4996)
#include <SFML/Graphics.hpp>

bool IsPrime(uint32_t number)
{
	if (number <= 1)
		return false;
	for (uint32_t i = 2; i <= sqrt(number); i++)
	{
		if (number % i == 0)
			return false;
	}
	return true;
}

int main(int argc, char const *argv[])
{
	uint32_t width = 500;
	uint32_t height = 500;

	int32_t framesPerSec = 30;
	if (argc >= 3)
	{
		for (int i = 0; i < strlen(argv[1]); i++)
		{
			if (!isdigit(argv[1][i]))
			{
				std::cerr << "Argument 1 is not a number\n";
				exit(1);
			}
		}
		for (int i = 0; i < strlen(argv[2]); i++)
		{
			if (!isdigit(argv[2][i]))
			{
				std::cerr << "Argument 2 is not a number\n";
				exit(1);
			}
		}

		width = atoi(argv[1]);
		height = atoi(argv[2]);

		if (argc >= 4)
		{
			for (int i = 0; i < strlen(argv[3]); i++)
			{
				if (!isdigit(argv[3][i]) && argv[3][i] != '-')
				{
					std::cerr << "Argument 3 is not a number\n";
					exit(1);
				}
			}
			framesPerSec = std::max(-1, atoi(argv[3]));
			if (framesPerSec == 0)
				framesPerSec = -1;
		}
	}
	else
	{
		std::cout << "You can use differnet options such as: \n"
					 "\t ./<Sim> [width height] [maxFPS]\n";
	}

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	char title[1024];
	sprintf(title, "%s  %u x %u  max fps: %u", "Ulam Spiral", width, height, (uint32_t)framesPerSec);

	sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar, settings);

	if (framesPerSec != -1)
		window.setFramerateLimit(uint32_t(framesPerSec));
	uint32_t step = 1;
	uint32_t numSteps = 1;
	uint32_t stepSize = 15;
	uint32_t totalSteps = (width / stepSize) * (height / stepSize);
	uint32_t turnCount = 0;
	uint32_t state = 0;
	float radius = 5.0f;
	std::vector<sf::CircleShape> points;
	sf::CircleShape refPoint(radius);
	refPoint.setOrigin(radius / 2.0f, radius / 2.0f);
	uint32_t x = (uint32_t)(width / 2.0f);
	uint32_t y = (uint32_t)(height / 2.0f);
	refPoint.setPosition(sf::Vector2f((float)x, (float)y));
	sf::VertexArray line;
	line.setPrimitiveType(sf::Lines);
	line.append(sf::Vertex(sf::Vector2f{x + radius / 2.0f, y + radius / 2.0f}));
	line.append(sf::Vertex(sf::Vector2f{x + radius / 2.0f, y + radius / 2.0f}));
	uint32_t lastIndex = 1;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
			}
			break;
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
				{
					window.close();
				}
				break;
				default:
					break;
				}
			}
			break;
			case sf::Event::Resized:
			{
				window.setSize(sf::Vector2u{width, height});
			}
			break;
			default:
				break;
			}
		}

		if (step > totalSteps)
			continue;
		switch (state)
		{
		case 0:
			x += stepSize;
			break;
		case 1:
			y -= stepSize;
			break;
		case 2:
			x -= stepSize;
			break;
		case 3:
			y += stepSize;
			break;
		default:
			break;
		}
		uint32_t index = turnCount % 2;
		if (step % numSteps == 0)
		{
			state = (state + 1) % 4;
			turnCount++;
			if (turnCount % 2 == 0)
				numSteps++;
		}
		line.append(line[lastIndex]);
		line.append(line[lastIndex]);
		lastIndex+=2;
		line[lastIndex].position = {x + radius / 2.0f, y + radius / 2.0f};
		step++;
		if (IsPrime(step))
		{
			points.emplace_back(refPoint);
			points.back().setPosition((float)x, (float)y);
		}

		window.clear();
		for(auto& p : points)
		{
			window.draw(p);
		}
		window.draw(line);
		window.display();
	}
	return 0;
}
