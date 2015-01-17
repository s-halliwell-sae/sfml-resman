#include <ResourceManager/SFML/ManagedTexture.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <ResourceManager/Logger.hpp>
#include <SFML/Graphics.hpp>

void run()
{
	rm::ResourceManager::init(false);
	rm::ResourceManager::addResourceType<rm::ManagedTexture>();
	rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Queue);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Managed SFML Test");

	sf::Sprite sprite(*rm::ResourceManager::getResource<rm::ManagedTexture>("textureTest")->getTexture());

	while(window.isOpen())
	{
		// Check events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();

        rm::ResourceManager::update();
	}
}

int main()
{
	try
	{
		run();
	}
	catch(const char* e)
	{
		rm::Logger::logMessage(e);
	}
	rm::ResourceManager::cleanupUnused();

	return 0;
}