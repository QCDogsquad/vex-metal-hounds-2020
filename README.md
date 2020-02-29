# 8235A Robot Code

  This repository holds the code for team 8235A's Vex robot for the 2019-2020 game, *Tower Takeover*.
We use the [PROS](https://pros.cs.purdue.edu/) library along with [Okapi](https://okapilib.github.io/OkapiLib/index.html) library. 
We create a PID chassis controller for our chassis using Okapi, we have plans to use Pathfinder with Okapi 
to control our robot's autonomous routine. However, we urrently have a relatively simple autonomous, that simply pushes a single cube
into a goal.

## PID
 PID is a control system used in advanced robotics systems that combine several simple control systems into one. it combines
propotional, integral, and derivative control. Proportional control influences the system to try and correct the error at different speeds
depeneding on the size of the error. Integral control sums the error over time in order to correct steady state error. Finally
derivative control calculates the change in error over time in order to attempt to predict it, to minimize overshoot.
