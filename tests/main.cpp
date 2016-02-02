#include <iostream>
#include <fstream>
#include "ResourceManager\BaseResource.hpp"
#include "ResourceManager\ResourceFactory.hpp"
#include "ResourceManager\ResourceManager.hpp"

class TestResource : public rm::BaseResource
{
public:
	TestResource() {}
	virtual ~TestResource() {}

	virtual bool load() { std::cout << "Loaded a TestResource\n"; return true; }
	virtual bool unload() { std::cout << "Unloaded a TestResource\n";  return true; }

	
	int payload = 0;

	static std::string getResourceClassType() { return "TestResource"; }

};


void main()
{
	//make a resrouce creator
	rm::ResourceFactory::addType<TestResource>();

	//make a resource
	auto testres = rm::ResourceFactory::createResource<TestResource>("");

	//now we have a resoure that is unloaded
	testres->Load();
	testres->Load();
	testres->Unload();
	testres->Unload();
	testres->Load();
	testres->Reload();

	//make a create a basic resource file
	std::string textResFileContents = "return {{ type = \"TestResource\", alias = \"myTestResource1\", path = \"nofile.txt\"}}";

	const std::string packFileName = "resourcepack1.lua";

	std::ofstream file(packFileName);
	file << textResFileContents;
	file.close();
	
	//load that basic resource file
	rm::ResourceManager::loadPack(packFileName, rm::LoadMode::Block);

	//load pack that we know doesn't exist

	//test asset
	const std::string testResourceAlias = "myTestResource1";
	auto mytestassetFromPack = rm::ResourceManager::getResource<TestResource>(testResourceAlias);

	//load an asset that we know doesn't exist

	//unload resource pack
	rm::ResourceManager::unloadPack(packFileName, rm::LoadMode::Block);

	//test asset
	if (mytestassetFromPack->isLoaded())
		std::cout << "Shouldn't be loaded\n";

	//reload resource file
	rm::ResourceManager::reloadPack(packFileName, rm::LoadMode::Block);

	//test aset
	if (!mytestassetFromPack->isLoaded())
		std::cout << "Should be loaded\n";

	//create switch asset file

	//switch to resrouce

	//test asset does exist

	//test asset doesn't exist
}