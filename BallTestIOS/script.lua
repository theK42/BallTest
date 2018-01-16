local renderer = require "renderer"
local ballTest = require "ballTest"
local timer = require "timer"
--[[local input = require "input"]]--

local worldWidth, worldHeight = renderer.getDimensions();

local center = {x = worldWidth / 2, y = worldHeight / 2};
local westofCenter = {x = worldWidth / 3, y = (worldHeight / 2)};
local northofCenter = {x = worldWidth / 2, y = worldHeight / 3};

local west = {vx = -20.0, vy = 0.0};
local east = {vx = 20.0, vy = 0.0};
local north = {vx = 0.0, vy = 20.0};

local stationary = {vx = 0.0, vy = 0.0};
--local stationaryBall = ballTest.newBall(center, stationary, 50, 500);

--local box1 = ballTest.newBox(center, west, 0, 50, 50, 500);
--local box2 = ballTest.newBox(westofCenter, east, 0, 50, 50, 500);

local doBalls = true;

local randomObjects = {};

function randomBall()
	local radius = math.random(5, 25);
	local mass = 3.14 * radius * radius;
	local position = {x = math.random(radius, worldWidth - radius), y = math.random(radius, worldHeight - radius)};
	local velocity = {vx = math.random(0, 20), vy = math.random(0, 20)};
	randomObjects[#randomObjects + 1] = ballTest.newBall(position, velocity, 0, radius, mass);
end

function randomBox()
	local side = math.random(10, 50);
	local mass = side * side;
	local position = {x = math.random(side, worldWidth - side), y = math.random(side, worldHeight - side)};
	local velocity = {vx = math.random(0, 20), vy = math.random(0, 20)};
	randomObjects[#randomObjects + 1] = ballTest.newBox(position, velocity, 0, side, side, mass);
end

while doBalls do 
	--randomBox();
	--timer.waits(1);
	randomBall();
	timer.waits(1);
end


--[[
local interval = timer.setInterval(2, function()	
	local radius = math.random(5, 25);
	local mass = math.random(1, 2) * math.pi * radius ^ 2;
	local position = {x = math.random(radius, worldWidth - radius), y = math.random(radius, worldHeight - radius)};
	local velocity = {vx = math.random(0, 20), vy = math.random(0, 20)};
	
	randomBalls[#randomBalls + 1] = ball.new(position, velocity, radius, mass);
end);
]]--

--[[
while true do
	input.waitForInput();
	local radius = math.random(.5, 4.5);
	local mass = math.random(1, 2) * math.pi * radius ^ 2;
	local position = {x = math.random(radius, worldWidth - radius), y = math.random(radius, worldHeight - radius)};
	local velocity = {vx = math.random(0, 20), vy = math.random(0, 20)};
	
	randomBalls[#randomBalls + 1] = ball.new(position, velocity, radius, mass);
end]]--

while true do coroutine.yield() end
