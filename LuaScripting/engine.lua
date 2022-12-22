local lpath = "LuaScripting/"

local this = { };

  this.vector = require(lpath .. "engine/vector/vector");


  this.tableLength = function (table)
    local count = 0;
    for _ in pairs(table) do count = count + 1 end;
    return count;
  end;


  this.worldDataInit = function (worldData)

    setmetatable(worldData, {

      __index = function (wData, key)
        if      key == "deltaTime"   then  return wData[1];
        elseif  key == "positions"   then  return wData[2];
        elseif  key == "velocities"  then  return wData[3];
        end;
      end;

      __tostring = function (wData)
        print("POSITIONS");
        for i, vec in pairs(wData.positions) do
          print(i..": ", vec.x, vec.y, vec.z);
        end;
        print("");
      
        print("VELOCITIES");
        for i, vec in pairs(wData.velocities) do
          print(i..": ", vec.x, vec.y, vec.z);
        end;
        print("");
      end;

    });

    this.vector.initVectorArray(worldData.positions,  this.tableLength(worldData.positions));
    this.vector.initVectorArray(worldData.velocities, this.tableLength(worldData.velocities));
    
  end;


return this;