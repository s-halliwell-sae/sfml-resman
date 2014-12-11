#include <BaseResource.hpp>


class BaseResource
{
public:
    void BaseResource()
    {
    }

    void ~BaseResource()
    {
    }

    ///////////////////////////////////////////////////////////
    /// \brief Returns the alias of type string
    ///
    ///////////////////////////////////////////////////////////
    std::string BaseResource::getAlias()const
    {
        return alias;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Returns the resource type string
    ///
    ///////////////////////////////////////////////////////////
    std::string BaseResource::getResourceType()const
    {
        return type;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Returns the file path string
    ///
    ///////////////////////////////////////////////////////////
    std::string BaseResource::getFilePath()const
    {
        return filePath;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Returns true if resource is loaded
    ///
    ///////////////////////////////////////////////////////////
    bool BaseResource::isLoaded()const
    {
        return isResourceLoaded;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Sets the alias member
    ///
    /// \param newalias The new Alias
    ///
    ///////////////////////////////////////////////////////////
    void BaseResource::setAlias(const std::string& newAlias)
    {
        alias = newAlias;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Sets the file path member
    ///
    ///////////////////////////////////////////////////////////
    void BaseResource::setFilePath(const std::string& newFilePath)
    {
        filePath = new filePath;
    }

    ///////////////////////////////////////////////////////////
    /// \brief Sets the isLoaded member
    ///
    ///////////////////////////////////////////////////////////
    void BaseResource::setIsLoaded(bool isLoaded)
    {
        isResourceLoaded = isLoaded;
    }

private:
    std::string alias, type, filePath;
    bool isResourceLoaded;
};
