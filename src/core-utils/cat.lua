Show_all = function(file)
  for line in io.lines(file) do
    line = line:gsub("[^\32-\126\10\13\9]", function(c)
      return string.format("^%c", c:byte() + 64)
    end)
    line = line:gsub("\t", "^I")
    print(line .. "$")
  end
end

Number = function(file)
  local count = 1
  for line in io.lines(file) do
    print(string.format("%6d  %s", count, line))
    count = count + 1
  end
end

Number_no_blank = function(file)
  local count = 1
  for line in io.lines(file) do
    if line ~= "" then
      print(string.format("%6d  %s", count, line))
      count = count + 1
    else
      print("")
    end
  end
end

Show_ends = function(file)
  for line in io.lines(file) do
    print(line .. "$")
  end
end

Show_tabs = function(file)
  for line in io.lines(file) do
    line = line:gsub("\t", "^I")
    print(line)
  end
end

Main = function(file, flag)
  local flags = {
    ["-A"] = Show_all,
    ["-n"] = Number,
    ["-E"] = Show_ends,
    ["-b"] = Number_no_blank,
    ["-T"] = Show_tabs
  }
  if flags[flag] then
    flags[flag](file)
  else
    print("Invalid flag")
  end
end

local file = arg[1]
local flag = arg[2]

if file and flag then
  Main(file, flag)
else
  print("Usage: lua script.lua <file> <flag>")
  print("Flags:")
  print("  -A = Show_all")
  print("  -n = Number")
  print("  -E = Show_ends")
end

