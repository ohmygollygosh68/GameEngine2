-- a = 7 + 11 + math.sin(23.7)
-- a = a + 100
--PlayerTitle = "Squire"
--PlayerName = "Ciaran"
--PlayerFamily = "Wirral"
--PlayerLevel = 20


-- player = {}
-- player["Title"]	= "Squire"
-- player["Name"]	= "Ciaran"
-- player["Family"] = "Wirral"
-- player["Level"] = 20

players = {}
players[0] = { Title = "Squire", Name = "Ciaran", Family = "Wirral", Level = 20}
players[1] = { Title = "Lord", Name = "Diego", Family = "Brazil", Level = 50}


function AddStuff(a, b)
	print("[LUA] AddStuff("..a..", "..b..") called \n")
	return a + b
end

function GetPlayer(n)
	return players[n]
end
