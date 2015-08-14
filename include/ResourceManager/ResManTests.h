//#include "Shiny.h"
#include <fstream>
#include <ResourceManager/Logger.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <ResourceManager/BaseResource.hpp>
#include <algorithm>

void ResManTests()
{
	rm::ResourceManager::init(false);

	rm::Logger::setFileLocation("resmantests.txt");

	//rm::ResourceManager::addResourceType<rm::ManagedTexture>();

	//rm::ResourceManager::createErrorResource<rm::ManagedFont>("wrongErrorFontResource.ttf");

	//UNIT TEST A: Load Pack (Block)
	//		currentTest = "Load Pack";
	//		rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
	//		//Unit Test B: Reload Pack
	//		currentTest = "Reload Pack";
	//		rm::ResourceManager::reloadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
	//		//Unit Test C: Unload Pack
	//		currentTest = "Unload Pack";
	//		rm::ResourceManager::unloadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
	//		//UNIT TEST D: Switch pack
	//		//currentTest = "Switch Pack with good data";
	//		//rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
	//		//rm::ResourceManager::switchPack("resourcepacks/sfmltestpack.lua", "resourcepacks/sfmltestpack2.lua");
	//
	//		//if (rm::ResourceManager::getResource<rm::ManagedFont>("fontTest3")->getFont() == rm::ResourceManager::getErrorResource<rm::ManagedFont>()->getFont())
	//		//	throw(std::string("Switch pack did not keep existing font."));
	//
	//		//auto res = rm::ResourceManager::getResource<rm::ManagedFont>("fontTest")->getFont();
	//		//if (res != rm::ResourceManager::getErrorResource<rm::ManagedFont>()->getFont())
	//		//	throw(std::string("Switch pack did not unload resource."));
	//
	//		//if (rm::ResourceManager::getResource<rm::ManagedFont>("fontTest2")->getFont() == rm::ResourceManager::getErrorResource<rm::ManagedFont>()->getFont())
	//		//	throw(std::string("Switch pack did not load new resource."));
	//
	//		//UNIT TEST E: Switch pack with false data
	//		//currentTest = "Switch Pack with false data";
	//		//rm::ResourceManager::switchPack("resourcepacks/sfmltestpack2.lua", "obviouslyWrong.lua");
	//
	//
	//
	//		//UNIT TEST F: Load non-existing pack
	//		currentTest = "Load Missing Pack";
	//		rm::ResourceManager::loadPack("itsgonenow.lua", rm::LoadMode::Block);


	//UNIT TEST A: Load Resources
	//		//Texture
	//		currentTest = "Load Texture Resource";
	//		auto managedTexture = rm::ResourceManager::getResource<rm::ManagedTexture>("textureTest");
	//		if (managedTexture->getAlias() != "textureTest" || managedTexture->getTexture() == nullptr)
	//		{
	//			throw(std::string("Texture resource did not load!"));
	//		}


	//UNIT TEST C: Reload Resources
	//		currentTest = "Reload Resources";
	//		managedTexture->reload();
	//		managedSound->reload();
	//		managedFont->reload();
	//
	//		//Unit Test D: Unload Resources
	//		currentTest = "Unload Resources";
	//		managedTexture->unload();
	//		managedSound->unload();
	//		managedFont->unload();
	//
	//		//Unit Test E: Cleanup Resources
	//		currentTest = "Cleanup Resources";
	//		rm::ResourceManager::cleanupUnused();
	//
	//		//PROFILE_FUNC();
	//		//Unit Test F: List of Loaded Resources
	//		rm::ResourceList resList = rm::ResourceManager::listAll();
}

//
//void OnTestEnd()
//{
//	//PROFILER_UPDATE(); // update all profiles
//	//PROFILER_OUTPUT(); // print to cout
//
//	system("pause");
//
//}
//
//void OnTestFailure(std::string currentTest, std::string& e)
//{
//	rm::Logger::logMessage("----------------------------------------");
//	rm::Logger::logMessage("-             BUILD FAILURE            -");
//	rm::Logger::logMessage("----------------------------------------");
//
//	rm::Logger::logMessage("Unit Testing failed on task: " + currentTest);
//	rm::Logger::logMessage(e);
//
//	rm::Logger::logMessage("----------------------------------------");
//	OnTestEnd();
//}
//
//void OnTestFailure(std::string currentTest, const char* e)
//{
//	OnTestFailure(currentTest, std::string(e));
//}
//
//void _CreateErrorResources(std::string& currentTest)
//{
//	////	UNIT TEST A: Create missing error resources
//	////Font
//	//currentTest = "Load Missing Font Error Resource";
//	//try
//	//{
//	//	rm::ResourceManager::createErrorResource<rm::ManagedFont>("wrongErrorFontResource.ttf");
//	//	OnTestFailure(currentTest, "Did not generate an exception.");
//	//}
//	//catch (...)	{}
//
//	////Texture
//	//currentTest = "Load Missing Texture Error Resource";
//	//try
//	//{
//	//	rm::ResourceManager::createErrorResource<rm::ManagedTexture>("wrongErrorTextureResource.png");
//	//	OnTestFailure(currentTest, "Did not generate an exception.");
//	//}
//	//catch (...)	{}
//
//	////ManagedSound
//	//currentTest = "Load Missing Sound Error Resource";
//	//try
//	//{
//	//	rm::ResourceManager::createErrorResource<rm::ManagedSound>("wrongErrorSoundResource.wav");
//	//	OnTestFailure(currentTest, "Did not generate an exception.");
//	//}
//	//catch (...)	{}
//
//	////	UNIT TEST B: Create error resources
//	//try
//	//{
//	//	//ManagedFont
//	//	currentTest = "Load Font Error Resource";
//	//	rm::ResourceManager::createErrorResource<rm::ManagedFont>("error_resources/free3of9.ttf");
//
//	//	//ManagedTexture
//	//	currentTest = "Load Texture Error Resource";
//	//	rm::ResourceManager::createErrorResource<rm::ManagedTexture>("error_resources/ResMan_DefaultError_Texture_1.png");
//
//	//	//ManagedSound
//	//	currentTest = "Load Sound Error Resource";
//	//	rm::ResourceManager::createErrorResource<rm::ManagedSound>("error_resources/ResMan_DefaultError_Audio_1.wav");
//	//}
//	//catch (std::string e)
//	//{
//	//	OnTestFailure(currentTest, e);
//	//}
//}
//
//void _Pack(std::string& currentTest)
//{
//	try
//	{
//		//UNIT TEST A: Load Pack (Block)
//		currentTest = "Load Pack";
//		rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
//		//Unit Test B: Reload Pack
//		currentTest = "Reload Pack";
//		rm::ResourceManager::reloadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
//		//Unit Test C: Unload Pack
//		currentTest = "Unload Pack";
//		rm::ResourceManager::unloadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
//		//UNIT TEST D: Switch pack
//		//currentTest = "Switch Pack with good data";
//		//rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
//		//rm::ResourceManager::switchPack("resourcepacks/sfmltestpack.lua", "resourcepacks/sfmltestpack2.lua");
//
//		//if (rm::ResourceManager::getResource<rm::ManagedFont>("fontTest3")->getFont() == rm::ResourceManager::getErrorResource<rm::ManagedFont>()->getFont())
//		//	throw(std::string("Switch pack did not keep existing font."));
//
//		//auto res = rm::ResourceManager::getResource<rm::ManagedFont>("fontTest")->getFont();
//		//if (res != rm::ResourceManager::getErrorResource<rm::ManagedFont>()->getFont())
//		//	throw(std::string("Switch pack did not unload resource."));
//
//		//if (rm::ResourceManager::getResource<rm::ManagedFont>("fontTest2")->getFont() == rm::ResourceManager::getErrorResource<rm::ManagedFont>()->getFont())
//		//	throw(std::string("Switch pack did not load new resource."));
//
//		//UNIT TEST E: Switch pack with false data
//		//currentTest = "Switch Pack with false data";
//		//rm::ResourceManager::switchPack("resourcepacks/sfmltestpack2.lua", "obviouslyWrong.lua");
//
//
//
//		//UNIT TEST F: Load non-existing pack
//		currentTest = "Load Missing Pack";
//		rm::ResourceManager::loadPack("itsgonenow.lua", rm::LoadMode::Block);
//	}
//	catch (std::string e)
//	{
//		OnTestFailure(currentTest, e);
//	}
//}
//
//void _Resources(std::string& currentTest)
//{
//	try
//	{
//		//PRE-UNIT TEST: Load Pack
//		currentTest = "Load Pack (Resources)";
//		rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);
//
//		//UNIT TEST A: Load Resources
//		//Texture
//		currentTest = "Load Texture Resource";
//		auto managedTexture = rm::ResourceManager::getResource<rm::ManagedTexture>("textureTest");
//		if (managedTexture->getAlias() != "textureTest" || managedTexture->getTexture() == nullptr)
//		{
//			throw(std::string("Texture resource did not load!"));
//		}
//
//		//Sound
//		currentTest = "Load Sound Resource";
//		auto managedSound = rm::ResourceManager::getResource<rm::ManagedSound>("soundTest");
//		if (managedSound->getAlias() != "soundTest" || managedSound->getSoundBuffer() == nullptr)
//		{
//			throw(std::string("Sound Resource did not load!"));
//		}
//
//		//Font
//		currentTest = "Load Font Resource";
//		auto managedFont = rm::ResourceManager::getResource<rm::ManagedFont>("fontTest");
//		if (managedFont->getAlias() != "fontTest" || managedFont->getFont() == nullptr)
//		{
//			throw(std::string("Font Resource did not load!"));
//		}
//
//		//UNIT TEST B: Load non-existing resource
//		//Font
//		currentTest = "Load Missing Font Resource";
//		auto missingFont = rm::ResourceManager::getResource<rm::ManagedFont>("somethingsmissing.ttf");
//		if (missingFont->getFont() != rm::ResourceManager::getErrorResource<rm::ManagedFont>()->getFont())
//		{
//			throw(std::string("Non-existing font does not match error resource"));
//		}
//
//		//Texture
//		currentTest = "Load Missing Texture Resource";
//		auto missingTexture = rm::ResourceManager::getResource<rm::ManagedTexture>("somethingsmissing.png");
//		if (missingTexture->getTexture() != rm::ResourceManager::getErrorResource<rm::ManagedTexture>()->getTexture())
//		{
//			throw(std::string("Non-existing texture does not match error resource"));
//		}
//
//		//Sound
//		currentTest = "Load Missing Sound Resource";
//		auto missingSound = rm::ResourceManager::getResource<rm::ManagedSound>("somethingsmissing.wav");
//		if (missingSound->getSoundBuffer() != rm::ResourceManager::getErrorResource<rm::ManagedSound>()->getSoundBuffer())
//		{
//			throw(std::string("Non-existing sound does not match error resource"));
//		}
//
//		//UNIT TEST C: Reload Resources
//		currentTest = "Reload Resources";
//		managedTexture->reload();
//		managedSound->reload();
//		managedFont->reload();
//
//		//Unit Test D: Unload Resources
//		currentTest = "Unload Resources";
//		managedTexture->unload();
//		managedSound->unload();
//		managedFont->unload();
//
//		//Unit Test E: Cleanup Resources
//		currentTest = "Cleanup Resources";
//		rm::ResourceManager::cleanupUnused();
//
//		//PROFILE_FUNC();
//		//Unit Test F: List of Loaded Resources
//		rm::ResourceList resList = rm::ResourceManager::listAll();
//
//		//PROFILE_BEGIN(loadedResources);
//		if (resList.size() == 0)
//		{
//			throw(std::string("No resources loaded, list is empty"));
//		}
//		//PROFILE_END(loadedResources);
//	}
//
//	catch (std::string e)
//	{
//		OnTestFailure(currentTest, e);
//	}
//
//}
//
//void _PackLoadRelease(std::string& currentTest)
//{
//	try
//	{
//		//Unit Test A: Async Pack Load
//		currentTest = "Async Load Pack";
//		// Queue a resource pack for loading
//		//TODO Broken
//
//		//rm::ResourceManager::loadPack("resourcepacks/sfmltestpack2.lua", rm::LoadMode::Queue);
//		//rm::ResourceManager::setLoadCompleteCallback([&]()
//		//{
//		//	//Pre-Unit Test B: Create and Load new resources
//		//	currentTest = "Hard Release (Creation)";
//		//	auto managedTexture2 = rm::ResourceManager::getResource<rm::ManagedTexture>("resources/textureTest2.png");
//		//	auto managedSound2 = rm::ResourceManager::getResource<rm::ManagedSound>("resources/soundTest2.wav");
//		//	auto managedFont2 = rm::ResourceManager::getResource<rm::ManagedFont>("resources/fontTest2.ttf");
//
//		//	//Unit Test B: Hard Release Resources
//		//	currentTest = "Hard Release";
//		//	rm::ResourceManager::unloadResource("textureTest2", rm::LoadMode::Block);
//		//	rm::ResourceManager::unloadResource("soundTest2", rm::LoadMode::Block);
//		//	rm::ResourceManager::unloadResource("fontTest2", rm::LoadMode::Block);
//
//		//	rm::Logger::logMessage("----------------------------------------");
//		//	rm::Logger::logMessage("-             BUILD SUCCESS            -");
//		//	rm::Logger::logMessage("----------------------------------------");
//		//});
//
//		rm::ResourceManager::loadPack("resourcepacks/sfmltestpack2.lua", rm::LoadMode::Block);
//		//Pre-Unit Test B: Create and Load new resources
//		currentTest = "Hard Release (Creation)";
//		auto managedTexture2 = rm::ResourceManager::getResource<rm::ManagedTexture>("resources/textureTest2.png");
//		auto managedSound2 = rm::ResourceManager::getResource<rm::ManagedSound>("resources/soundTest2.wav");
//		auto managedFont2 = rm::ResourceManager::getResource<rm::ManagedFont>("resources/fontTest2.ttf");
//
//		//Unit Test B: Hard Release Resources
//		currentTest = "Hard Release";
//		rm::ResourceManager::unloadResource("textureTest2", rm::LoadMode::Block);
//		rm::ResourceManager::unloadResource("soundTest2", rm::LoadMode::Block);
//		rm::ResourceManager::unloadResource("fontTest2", rm::LoadMode::Block);
//
//		rm::Logger::logMessage("----------------------------------------");
//		rm::Logger::logMessage("-             BUILD SUCCESS            -");
//		rm::Logger::logMessage("----------------------------------------");
//
//		OnTestEnd();
//	}
//	catch (std::string e)
//	{
//		OnTestFailure(currentTest, e);
//	}
//}
//
//void run()
//{
//	//sf::RenderWindow window(sf::VideoMode(800, 600), "Unit Tests");
//
//	// Init the resource manager and set it to try to use error resources
//	// This test doesn't have any yet so should the test resources go
//	//  missing, it will crash when their use is attempted
//	rm::ResourceManager::init(false);
//
//	rm::Logger::setFileLocation("tests.txt");
//
//	// Sets the Available Resource Types for the Resource Manager
//	rm::ResourceManager::addResourceType<rm::ManagedTexture>();
//	rm::ResourceManager::addResourceType<rm::ManagedSound>();
//	rm::ResourceManager::addResourceType<rm::ManagedFont>();
//
//	//UNIT TESTS BEGIN
//	std::string currentTest = "Init";
//
//	//UNIT TEST 1: Error Resources
//	_CreateErrorResources(currentTest);
//
//	//UNIT TEST 3: Packs
//	_Pack(currentTest);
//
//	//UNIT TEST 4: Resources
//	_Resources(currentTest);
//
//	//UNIT TEST 2: Async Pack Load and Release
//	_PackLoadRelease(currentTest);
//}