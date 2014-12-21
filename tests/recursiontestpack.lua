return {
	-- nested recursion
	{
		type = "resourcepack",
		path = "tests/recursiontestpack2.lua"
	},

	-- self referencing recursion
	{
		type = "resourcepack",
		path = "tests/recursiontestpack.lua"
	}
}