local function endsWith(str, ending)
    return ending == "" or str:sub(-#ending) == ending
end

local function getLuaFiles(directory)
    local luaFiles = {}
    -- Open a pipe to the `ls` command
    local p = io.popen('ls "' .. directory .. '"')
    if p then
        for file in p:lines() do
            if endsWith(file, ".lua") then
                table.insert(luaFiles, directory .. '/' .. file)
            end
        end
        p:close()
    end
    return luaFiles
end

local home = os.getenv("HOME")
local dir = home .. "/.config/plush"
LuaFiles = getLuaFiles(dir)

return LuaFiles
