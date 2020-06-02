# Elevators

Simple elevator system with graphical interface (SDL).

Demo on YouTube:
https://youtu.be/oZrhFfv18yI

Demo Level:
 - A building with Lobby, Basement, Observation Deck and 23 normal floors.
 - 1 standard elevator for the lower floors (B, L, 2-12)
 - 2 standard elevators for the higher floors (B, L, 13-24)
 - 1 high-speed elevator for tourists (Lobby, Observation Deck)
 
 UI:
 - Little bit hard to understand, but it works.
 - Speed setting: sets the simulation speed between 0% and 200%. Can be used to pause the game.
 - Elevator Controls: each elevator has an individual set of buttons. There are four panels for the four elevators, each panel consists of 3 columns. The first two columns (triangles) are summoning buttons: pushing them indicates that someone on the respective floor wishes to use the elevator to go down/up. The third column (square) holds the cabin button: pushing this button indicates that someone inside the elevator wishes to go to the respective floor.
 
 Elevator Controller:
 - Standard elevator controller for high efficiency.
 - Has three route modes: up, down, idle.
 - Attempts to finish the current route before reversing.
 - Reverses if current route is cleared.
 - Accepts further input while moving. However, will ignore inputs if braking is impossible (elevator too fast / too close to destination)
  
 Planned Future Features:
 - Add AI. Configure the floors to have traffic. Should also depend on the floor type (office, living, shops, observation deck) and the time of the day (rush hours).
 - Clean up the code by refining the class system (static scene objects, actor components, ...)
