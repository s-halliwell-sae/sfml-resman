#include <ResourceManager/Logger.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <ResourceManager/BaseResource.hpp>

class Test : public rm::BaseResource {
public:
	bool load() override {
		return filePath != "obviously.wrong";
	}
	bool unload() override {
		return true;
	}
	bool reload() override {
		return true;
	}

	size_t getMemUsage() const override {
		return sizeof(Test);
	}

	static std::string getResourceClassType(){
		return "text";
	}
};

void unittest(){
	std::string iAmAString = "is ";
	char c = 'a';

	rm::Logger::setFileLocation("log.txt");
	rm::Logger::logMessage("Hello");
	rm::Logger::logMessage("Hello ", "this ", iAmAString, c, " Thing ", 1234);

	rm::ResourceManager::init(false);
	rm::ResourceManager::addResourceType<Test>();
	rm::ResourceManager::createErrorResource<Test>("log.txt");

	auto r = rm::ResourceManager::loadResource<Test>("obviously.wrong", rm::LoadMode::Block);
	rm::Logger::logMessage("loadResource obviously.wrong\tptr: ", !r?"nullptr":"valid", " \tfilePath: ", r?r->getFilePath():"");
}

int main(){
	try{
		unittest();
	}catch(const char* e){
		rm::Logger::logMessage("Exception: ", e);
	}

	return 0;
}