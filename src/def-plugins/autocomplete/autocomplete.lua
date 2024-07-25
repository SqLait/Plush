local home = os.getenv("HOME")
local history_path = home .. "/.local/share/.plushhs"

local function read_history(file_path)
  local history_table = {}
  local file, err = io.open(file_path, "r")

  if not file then
    print("Error opening file:", err)
    return nil
  end

  for line in file:lines() do
    table.insert(history_table, line)
  end

  file:close()
  return history_table
end

-- Use the function to read the history file
local history = read_history(history_path)

-- Print the contents of the table (optional)
if history then
  for i in pairs(history) do
    print(history[i])
  end
end

