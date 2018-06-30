#include "Atirador_em_Plataforma.h"

static const float VIEW_WIDTH = 1024.0f;    /*largura da tela*/
static const float VIEW_HEIGHT = 600.0f;    /*altura da tela*/

enum WindowState { Game, Options, Exit, Menu, setMenu, setGame };

Atirador_em_Plataforma::Atirador_em_Plataforma():
	window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Jogo de Tiro em 2D", sf::Style::Close | sf::Style::Resize),
	view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT))
{
	stateValue = WindowState::setMenu;
	playerTexture.loadFromFile("textures/Player_tex.png");
	enemyTexture.loadFromFile("textures/Inimigo.png");
	groundTexture.loadFromFile("textures/ground.png");
	floorTexture.loadFromFile("textures/floor.png");
	bulletTexture.loadFromFile("textures/Bullet.png");
	healthTexture.loadFromFile("textures/health.bmp");
}


Atirador_em_Plataforma::~Atirador_em_Plataforma()
{

}


void Atirador_em_Plataforma::ResizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT * aspectRatio);
}

void Atirador_em_Plataforma::Loop_Janela()
{
	while (window.isOpen())
	{
		window.clear();
		window.setView(window.getDefaultView());

		if (stateValue == WindowState::setMenu)
		{
			while (GameStack.size() > 0)
				GameStack.pop();

			MenuStack.emplace(VIEW_WIDTH, VIEW_HEIGHT, stateValue);
			stateValue = WindowState::Menu;
		}

		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			deltaTime = clock.restart().asSeconds();
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				deltaTime = clock.restart().asSeconds();    //CONGELA A JANELA ENQUANTO O TAMANHO DESTA EH ALTERADO
				ResizeView(window, view);
				break;
				//************

			case sf::Event::KeyReleased:
				switch (stateValue)
				{
				case WindowState::Menu:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						MenuStack.top().MoveUp();
						break;

					case sf::Keyboard::Down:
						MenuStack.top().MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (MenuStack.top().GetPressedItem())
						{
						case 0:
							std::cout << "Play button has been pressed" << std::endl;
							stateValue = WindowState::setGame;
							break;
						case 1:
							std::cout << "Option button has been pressed" << std::endl;
							break;
						case 2:
							window.close();
							break;
						default:
							break;
						}
						break;

					default:
						break;
					}
					break;

				case WindowState::Game:
					GameStack.top().input(stateValue);
					break;

				default:
					break;
				}

				break;
				//************
			default:
				break;
			}
		}

		if (stateValue == WindowState::Menu) {
			MenuStack.top().draw(window);
		}

		if (stateValue == WindowState::setGame)
		{
			while (MenuStack.size() > 0)
				MenuStack.pop();

			GameStack.emplace(&playerTexture, &enemyTexture, &groundTexture, &floorTexture, &bulletTexture, &healthTexture, stateValue);
		}
		if (stateValue == WindowState::Game)
		{
			GameStack.top().Loop(window, view, deltaTime, stateValue);

			if (stateValue == WindowState::setMenu)
			{
				GameStack.pop();
			}
		}

		window.display();
	}
}
