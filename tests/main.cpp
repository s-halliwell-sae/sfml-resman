#include "iostream"
#include "ResourceManager\BaseResource.hpp"
#include "ResourceManager\ResourceFactory.hpp"

class TestResource : public rm::BaseResource
{
public:
	TestResource() {}
	virtual ~TestResource() {}

	virtual bool load() { return true; }
	virtual bool unload() { return true; }

	
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
	
	//make a create a basic resource file

	//load that basic resource file

	//test asset

	//unload resource file

	//test asset

	//reload resource file

	//create switch asset file

	//switch to resrouce

	//test asset does exist

	//test asset doesn't exist
}