sfml-resman
===========

Goal
----

The purpose of this project is to provide a reliable and flexible resource manager for sfml. This is a student project. 
Feedback is encouraged.

Dependencies
----

####Required

LUA: http://www.lua.org/

####Optional

SFML: http://www.sfml-dev.org/

Integration & Building (Visual Studio)
----
1. Clone the resman repo.
2. Ensure that you have Lua installed.
3. If you are using the default SFML resource types, install the SFML library. A guide for setting up SFML can be found HERE: http://www.sfml-dev.org/tutorials/2.2/start-vc.php
4. Add the source (/src) and header (/include) files from the cloned repository to your project.
5. If not already, link the SFML and LUA .dll and .lib files in your project settings.
6. Make sure all dependency .dll files have been copied into the output directory.

How to use it
----
1. Initialize resource manager
<pre>rm::ResourceManager::init(false);</pre>
2. Setup logger output file path.
<pre>rm::Logger::setFileLocation("tests.txt");</pre>
3. You can either (a)use the included managed types that use SFML, or (b)implementing your own resource that extend BaseResource, add the desired resource types to the resource manager. <br>
(a) Included managed texture example.
<pre>rm::ResourceManager::addResourceType<rm::ManagedTexture>();
rm::ResourceManager::addResourceType<rm::ManagedSound>();
rm::ResourceManager::addResourceType<rm::ManagedFont>();</pre>
(b) Implement your own resource that extends BaseResource.<br>
    Extending these three virtual functions:
<pre>virtual bool load();
virtual bool unload();
virtual bool reload();</pre>
4. Create error resources for desired managed resources. 
<pre>rm::ResourceManager::createErrorResource<rm::ManagedFont>("wrongFont.ttf");</pre>
5. Load resource pack containing LUA script consisting of resource information. In either Block or Queue format. 
<pre>rm::ResourceManager::loadPack("resourcepacks/sfmltestpack.lua", rm::LoadMode::Block);</pre>
6. Get resource with following code using resource alias.
<pre>rm::ResourceManager::getResource<rm::ManagedSound>("Jump");</pre>

What it can do
----
Resman can manage any type of resource that can implement a load and unload function.<br>
Resources can be queued and block loaded. <br>
Resources are loaded through packs in LAU script format. <br>
Packs can be switched, unloading resources that are no longer needed and loading resources that are now required.
