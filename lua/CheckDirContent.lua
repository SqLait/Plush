local function ends_with(str, ending)
    return ending == "" or str:sub(-#ending) == ending
end

local function get_lua_files(directory)
    local lua_files = {}
    -- Open a pipe to the `ls` command
    local p = io.popen('ls "' .. directory .. '"')
    if p then
        for file in p:lines() do
            if ends_with(file, ".lua") then
                table.insert(lua_files, directory .. '/' .. file)
            end
        end
        p:close()
    end
    return lua_files
end

local home = os.getenv("HOME")
local dir = home .. "/.config/plush"
LuaFiles = get_lua_files(dir)

return LuaFiles
