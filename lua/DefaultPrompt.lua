Prompt = {}

Prompt.Default = function()
  local user = os.getenv("USER")
  local host = Prompt.get_hostname()

  return user .. "@" .. host
end

function Prompt.get_hostname()
  local handle = io.popen("hostname")
  local hostname = handle:read("*a")
  handle:close()
  return hostname:match("^%s*(.-)%s*$")  -- Trim whitespace
end
