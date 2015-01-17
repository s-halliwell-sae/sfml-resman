return {
	-- nested recursion
	{
		type = "resourcepack",
		path = "resourcepacks/recursiontestpack2.lua"
	},

	-- self referencing recursion
	{
		type = "resourcepack",
		path = "resourcepacks/recursiontestpack.lua"
	}
}