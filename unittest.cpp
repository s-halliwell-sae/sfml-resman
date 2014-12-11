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
	rm::Logger::setFileLocation("log.txt");
	rm::Logger::logMessage("Hello");

	return 0;
}