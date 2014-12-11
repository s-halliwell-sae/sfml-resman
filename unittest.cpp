#include <ResourceManager/Logger.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <ResourceManager/BaseResource.hpp>

class Test : public rm::BaseResource {
public:
	static std::string getResourceClassType(){
		return "test";
	}
};

int main(){
	std::string iAmAString = "is ";
	char c = 'a';

	rm::Logger::setFileLocation("log.txt");
	rm::Logger::logMessage("Hello");
	rm::Logger::logMessage("Hello ", "this ", iAmAString, c, "Thing ", 1234);

	return 0;
}