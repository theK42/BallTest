local renderer = require "renderer"
local ball = require "ball"
local timer = require "timer"
--[[local input = require "input"]]--

local worldWidth, worldHeight = renderer.getDimensions();

local center = {x = worldWidth / 2, y = worldHeight / 2};
local westofCenter = {x = worldWidth / 3, y = worldHeight / 2};
local northofCenter = {x = worldWidth / 2, y = worldHeight / 3};

local west = {vx = -10.0, vy = 0.0};
local east = {vx = 5.0, vy = 0.0};
local north = {vx = 0.0, vy = 20.0};



local ball1 = ball.new(center, west, 0.5, 1.0);
timer.waits(1);
local ball2 = ball.new(westofCenter, east, 1.0, 2.0);
timer.waits(1);
local ball3 = ball.new(northofCenter, north, 4.5, 10.0);

local randomBalls = {};
local interval = timer.setInterval(2, function()	
	local radius = math.random(.5, 4.5);
	local mass = math.random(1, 2) * math.pi * radius ^ 2;
	local position = {x = math.random(radius, worldWidth - radius), y = math.random(radius, worldHeight - radius)};
	local velocity = {vx = math.random(0, 20), vy = math.random(0, 20)};
	
	randomBalls[#randomBalls + 1] = ball.new(position, velocity, radius, mass);
end);


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