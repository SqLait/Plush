local function Get_hostname()
  local handle = io.popen("hostname")
  local hostname = handle:read("*a")
  handle:close()
  return hostname:match("^%s*(.-)%s*$")  -- Trim whitespace
end

DefaultPrompt = function()
  local user = os.getenv("USER")
  local host = Get_hostname()

  return user .. "@" .. host .. " ~$ "
end
