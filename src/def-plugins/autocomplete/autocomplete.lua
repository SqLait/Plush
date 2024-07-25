local home = os.getenv("HOME")
local history_path = home .. "/.local/share/.plushhs"

local ReadHistory = function(file_path)
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

local SearchHistory = function(partialStr, history)
  local best_match = nil
  local best_score = 0

  for _, word in ipairs(history) do
    if word:sub(1, #partialStr) == partialStr then
      local score = #partialStr
      if score > best_score then
        best_score = score
        best_match = word
      end
    end
  end

  return best_match
end

local history = ReadHistory(history_path)

local partialStr = "no"
local suggestion = SearchHistory(partialStr, history)

if suggestion then
  print("Suggestion:", suggestion)
else
  print("No suggestion found.")
end

