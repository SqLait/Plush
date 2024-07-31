TabCompl = function(input)
  local HistoryContent = {}
  local occurringVars = {}
  local highestRelHolder = ""
  local highestScore = -1

  local home = os.getenv("HOME")
  local hs = home .. "/.local/share/.plushhs"

  for line in io.lines(hs) do --Get lines form history file
    table.insert(HistoryContent, line)
  end

  -- Traverse history from the most recent to the oldest
  for i = #HistoryContent, 1, -1 do
    local entry = HistoryContent[i]

    -- Check if the entry contains the input string
    if string.find(entry, input) then
      if occurringVars[entry] then
        occurringVars[entry] = occurringVars[entry] + 1
      else
        occurringVars[entry] = 1
      end

      -- Calculate the score: recentness + frequency
      local score = occurringVars[entry] + i / #HistoryContent

      -- Update the highest score and relevant holder
      if score > highestScore then
        highestScore = score
        highestRelHolder = entry
      end
    end
  end
  return highestRelHolder
end
