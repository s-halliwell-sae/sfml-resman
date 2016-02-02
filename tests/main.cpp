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

void writetofile(const std::string& toWrite, const std::string& filename)
{
	std::ofstream file(filename);
	file << toWrite;
	file.close();
}

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
	std::string textResFileContents1 = 
		"return {"
		"{ type = \"TestResource\", alias = \"myTestResource1\", path = \"nofile.txt\"}"
		","
		"{ type = \"TestResource\", alias = \"myTestResource2\", path = \"nofile.txt\"}"
		"}";

	const std::string packFileName1 = "resourcepack1.lua";

	writetofile(textResFileContents1, packFileName1);
	
	//load that basic resource file
	rm::ResourceManager::loadPack(packFileName1, rm::LoadMode::Block);

	//load pack that we know doesn't exist

	//test asset
	auto mytestassetFromPack = rm::ResourceManager::getResource<TestResource>("myTestResource1");

	//load an asset that we know doesn't exist

	//unload resource pack
	rm::ResourceManager::unloadPack(packFileName1, rm::LoadMode::Block);

	//test asset
	if (mytestassetFromPack->isLoaded())
		std::cout << "Shouldn't be loaded\n";

	//reload resource file
	rm::ResourceManager::reloadPack(packFileName1, rm::LoadMode::Block);

	//test aset
	if (!mytestassetFromPack->isLoaded())
		std::cout << "Should be loaded\n";

	//create switch asset file
	std::string textResFileContents2 =
		"return {"
		"{ type = \"TestResource\", alias = \"myTestResource2\", path = \"nofile.txt\"}"
		","
		"{ type = \"TestResource\", alias = \"myTestResource3\", path = \"nofile.txt\"}"
		"}";

	const std::string packFileName2 = "resourcepack2.lua";

	writetofile(textResFileContents2, packFileName2);


	//load second pack
	rm::ResourceManager::loadPack(packFileName2, rm::LoadMode::Block);

	//get res that is only in pack 2
	auto pack2res = rm::ResourceManager::getResource<TestResource>("myTestResource3");

	//auto numAssets = rm::ResourceManager::getNumResources();

	//unload unused
	rm::ResourceManager::cleanupUnused();


	//auto numAssetsAftercleanup = rm::ResourceManager::getNumResources();


	//TODO switch to resrouce
	//rm::ResourceManager::switchPack(packFileName2, rm::LoadMode::Block);

	//test asset does exist

	//test asset doesn't exist
}