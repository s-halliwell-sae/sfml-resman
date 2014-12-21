#include <ResourceManager/Logger.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <ResourceManager/BaseResource.hpp>

class Test : public rm::BaseResource {
public:
	Test(){
		rm::Logger::logMessage("-- Test::Test()");
	}
	~Test(){
		rm::Logger::logMessage("-- Test::~Test() ", alias, " ", filePath);
	}

	bool load() override {
		rm::Logger::logMessage("---- Test::load() ", alias, " ", filePath);
		return filePath != "obviously.wrong";
	}
	bool unload() override {
		rm::Logger::logMessage("---- Test::unload() ", alias, " ", filePath);
		return true;
	}
	bool reload() override {
		rm::Logger::logMessage("---- Test::reload() ", alias, " ", filePath);
		return true;
	}

	static std::string getResourceClassType(){
		return "test";
	}
};

void unittest(){
	std::string iAmAString = "is ";
	char c = 'a';

	rm::Logger::setFileLocation("log.txt");

	rm::ResourceManager::init(false);
	rm::ResourceManager::addResourceType<Test>();
	rm::ResourceManager::createErrorResource<Test>("log.txt");

	rm::ResourceManager::setLoadCompleteCallback([]{
		rm::Logger::logMessage("λ\tload complete\tλ");
	});

	auto r = rm::ResourceManager::loadResource<Test>("obviously.wrong", rm::LoadMode::Block);
	rm::Logger::logMessage("loadResource obviously.wrong\tptr: ", !r?"nullptr":"valid", " \tfilePath: ", r?r->getFilePath():"");
	rm::Logger::logMessage("loadResource obviously.wrong\ttype: ", r?r->getResourceType():"null");

	rm::ResourceManager::loadPack("tests/testresourcepack.lua", rm::LoadMode::Queue);

	while(rm::ResourceManager::isLoading()){
		rm::Logger::logMessage(rm::ResourceManager::getNumToLoad(), " resources to load");
		rm::ResourceManager::update();
	}

	rm::Logger::logMessage("Loading complete\n\n");

	rm::ResourceManager::loadPack("tests/testresourcepack.lua", rm::LoadMode::Block);
}

int main(){
	try{
		unittest();
	}catch(const char* e){
		rm::Logger::logMessage("Exception: ", e);
	}

	return 0;
}