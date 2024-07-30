TabCompl = function(input)
  local HistoryContent = {}
  local occurringVars = {}
  local highestRelHolder = ""
  local highestCount = 0

  local home = os.getenv("HOME")
  local hs = home .. "/.local/share/.plushhs"

  for line in io.lines(hs) do
    table.insert(HistoryContent, line)
  end

  for _, entry in ipairs(HistoryContent) do
    if occurringVars[entry] then
      occurringVars[entry] = occurringVars[entry] + 1
    else
      occurringVars[entry] = 1
    end

    if occurringVars[entry] > highestCount then
      highestCount = occurringVars[entry]
      highestRelHolder = entry
    end
  end

  print(highestRelHolder)
end

TabCompl("")
