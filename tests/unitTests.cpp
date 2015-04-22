#include "Shiny.h"
#include <fstream>
#include <ResourceManager/SFML/ManagedTexture.hpp>
#include <ResourceManager/SFML/ManagedSound.hpp>
#include <ResourceManager/SFML/ManagedFont.hpp>
#include <ResourceManager/Logger.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <ResourceManager/BaseResource.hpp>

void run()
{
	//sf::RenderWindow window(sf::VideoMode(800, 600), "Unit Tests");

	// Init the resource manager and set it to try to use error resources
	// This test doesn't have any yet so should the test resources go
	//  missing, it will crash when their use is attempted
	rm::ResourceManager::init(false);

	rm::Logger::setFileLocation("tests.txt");

	// Sets the Available Resource Types for the Resource Manager
	rm::ResourceManager::addResourceType<rm::ManagedTexture>();
	rm::ResourceManager::addResourceType<rm::ManagedSound>();
	rm::ResourceManager::addResourceType<rm::ManagedFont>();

	//UNIT TESTS BEGIN
	std::string currentTest = "Load Resources";

	try
	{
		//UNIT TEST 1: Load Pack (Block)
		currentTest = "Load Pack";

		rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
		//Unit Test 1.1: Reload Pack
		rm::ResourceManager::reloadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);

		//Unit Test 1.2: Unload Pack
		rm::ResourceManager::unloadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);

		//UNIT TEST 1.3: Load non-existing pack
		//		rm::ResourceManager::loadPack("itsgonenow.lua", rm::LoadMode::Block);

		//PRE-UNIT TEST 2: Load Pack
		rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);

		//UNIT TEST 2: Load Resources
		currentTest = "Load Resources";
		auto managedTexture = rm::ResourceManager::getResource<rm::ManagedTexture>("textureTest");
		auto managedSound = rm::ResourceManager::getResource<rm::ManagedSound>("soundTest");
		auto managedFont = rm::ResourceManager::getResource<rm::ManagedFont>("fontTest");

		//UNIT TEST 2.1: Load non-existing resource
		//auto missingResource = rm::ResourceManager::getResource<rm::ManagedFont>("itsgonenow");

		//UNIT TEST 3: Reload Resources
		currentTest = "Reload Resources";
		managedTexture->reload();
		managedSound->reload();
		managedFont->reload();

		//Unit Test 4: Unload Resources
		currentTest = "Unload Resources";
		managedTexture->unload();
		managedSound->unload();
		managedFont->unload();

		//Unit Test 5: Cleanup Resources
		currentTest = "Cleanup Resources";
		rm::ResourceManager::cleanupUnused();

		//Unit Test 6: Async Pack Load
		currentTest = "Async Load Pack";
		// Queue a resource pack for loading
		rm::ResourceManager::loadPack("resourcepacks/sfmltestpack2.lua", rm::LoadMode::Queue);

		rm::ResourceManager::setLoadCompleteCallback([&]()
		{
			//Pre-Unit Test 7: Create and Load new resources
			currentTest = "Hard Release (Creation)";
			auto managedTexture2 = rm::ResourceManager::getResource<rm::ManagedTexture>("resources/textureTest2.png");
			auto managedSound2 = rm::ResourceManager::getResource<rm::ManagedSound>("resources/soundTest2.wav");
			auto managedFont2 = rm::ResourceManager::getResource<rm::ManagedFont>("resources/fontTest2.ttf");

			//Unit Test 7: Hard Release Resources
			currentTest = "Hard Release";
			rm::ResourceManager::unloadResource("textureTest2", rm::LoadMode::Block);
			rm::ResourceManager::unloadResource("soundTest2", rm::LoadMode::Block);
			rm::ResourceManager::unloadResource("fontTest2", rm::LoadMode::Block);

			rm::Logger::logMessage("----------------------------------------");
			rm::Logger::logMessage("--------------BUILD SUCCESS-------------");
			rm::Logger::logMessage("----------------------------------------");
		});
	}

	catch (std::string e)
	{
		rm::Logger::logMessage("----------------------------------------");
		rm::Logger::logMessage("--------------BUILD FAILURE-------------");
		rm::Logger::logMessage("----------------------------------------");

		rm::Logger::logMessage("Unit Testing failed on task " + currentTest);
		rm::Logger::logMessage(e);

		rm::Logger::logMessage("----------------------------------------");
	}
}

int main()
{
	run();
	std::ofstream file("profile.txt");

	PROFILER_UPDATE(); // update all profiles
	PROFILER_OUTPUT(); // print to cout

	return 0;
}