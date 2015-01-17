return {
	{
		-- missing path
		alias = "missing.path",
		type = "test"
	},
	{
		-- missing type
		alias = "missing.type",
		path = "/I/am/a/path"
	},
	{
		-- empty node
	},
	{
		-- recursion
		type = "resourcepack",
		path = "tests/resourcepacks/erroneouspack.lua"
	},
	{
		-- invalid type
		type = "type that doesn't exist",
		path = "tests/resourcepacks/erroneouspack.lua"
	},
	{
		-- resourcepack of invalid format
		type = "resourcepack",
		path = "log.txt"
	},
}