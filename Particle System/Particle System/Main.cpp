#include "ParticleSystem.h"
#include "Manager.h"


int main()
{
	int width = 1366;
	int height = 768;
	// create the window
	sf::RenderWindow window(sf::VideoMode(width, height), "Particles");
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	Clock gameClock;

	Font font;
	font.loadFromFile("Jupiter.ttf");
	Texture t;
	t.loadFromFile("tex.png");


	SoundBuffer buffer;
	buffer.loadFromFile("BGM.flac");
	Sound bgm;
	bgm.setBuffer(buffer);

	Text testText;
	testText.setFont(font);
	testText.setCharacterSize(50);
	testText.setPosition(20, 20);

	Text testText1;
	testText1.setFont(font);
	testText1.setCharacterSize(50);
	testText1.setPosition(300, 600);
	Text testText2;
	testText2.setFont(font);
	testText2.setCharacterSize(50);
	testText2.setPosition(600, 600);
	Text testText3;
	testText3.setFont(font);
	testText3.setCharacterSize(50);
	testText3.setPosition(1050, 600);

	Text testText4;
	testText4.setFont(font);
	testText4.setCharacterSize(50);
	testText4.setPosition(500, 50);
	testText4.setString("Some Boring Particles");

	int stage = 0;

	Manager manager(t);
	manager.changeStage(stage, window);

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Add|| event.key.code == sf::Keyboard::Equal))
			{
				std::vector<Particle> new_particles(50);
				for(ParticleSystem *ps : manager.PSList)
					ps->particles.insert(ps->particles.end(), new_particles.begin(), new_particles.end());
			}
			else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Dash))
			{
				for (ParticleSystem *ps : manager.PSList)
				{
					if ((ps->particles.size() - 50) > 0)
					{
						ps->particles.erase(ps->particles.end() - 50, ps->particles.end());
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				bgm.play();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				stage = (stage + 1) % 10;
				manager.changeStage(stage,window);

				switch (stage)
				{
				case 0:
					testText1.setString("");
					testText2.setString("");
					testText3.setString("");
					testText4.setString("Some Boring Particles");
					break;
				case 1:
					testText1.setString("");
					testText2.setString("");
					testText3.setString("");
					testText4.setString("Set Emitter Angle");
					break;
				case 2:
					testText1.setString("");
					testText2.setString("");
					testText3.setString("");
					testText4.setString("Add Random Velocity");
					break;
				case 3:
					testText1.setString("");
					testText2.setString("");
					testText3.setString("");
					testText4.setString("Add Random Rotation");
					break;
				case 4:
					testText1.setString("");
					testText2.setString("");
					testText3.setString("");
					testText4.setString("Add Random Size");
					break;
				case 5:
					testText1.setString("");
					testText2.setString("");
					testText3.setString("");
					testText4.setString("Add Random Rotate Speed");
					break;
				case 6:
					testText1.setString("Linear");
					testText2.setString("Exponential");
					testText3.setString("Sin");
					testText4.setString("Velocity Easing");
					break;
				case 7:
					testText1.setString("Linear");
					testText2.setString("Exponential");
					testText3.setString("Sin");
					testText4.setString("Angle Easing");
					break;
				case 8:
					testText1.setString("Linear");
					testText2.setString("Exponential");
					testText3.setString("Sin");
					testText4.setString("Size Easing");
					break;
				case 9:
					testText1.setString("Linear");
					testText2.setString("Exponential");
					testText3.setString("Sin");
					testText4.setString("Rotation Easing");
					break;
				}
			}
		}

		
		// draw it
		window.clear();
		// update it
		sf::Time elapsed = gameClock.restart();

		testText.setString(to_string(1 / elapsed.asSeconds()));

		for (ParticleSystem *ps : manager.PSList)
		{
			ps->update(elapsed);

			for (Particle p : ps->particles)
			{
				window.draw(p.rect);
			}
		}

		window.draw(testText1);
		window.draw(testText2);
		window.draw(testText3);
		window.draw(testText4);
		window.display();
	}

	return 0;
}


