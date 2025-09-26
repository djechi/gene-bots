# Genetic Algorithm Robots
C++ simulation that uses genetic algorithms to evolve robot navigation behavior within a grid. Through multiple generations, robots will learn to efficiently collect batteries through natural selection.

## Overview
This program will simulate a population of 200 robots that will navigate on a 10x10 grid map. 
The objective of the robots is to collect batteries to survive. After every robot is done, the 
fitness scores will be calculated to find the average. The top 100 robots will survive, while the rest will be eliminated. 
The top 100 robots will then repopulate the population until 200 robots are up again. The genes from the two parent robots will 
be transferred to their children. This process will continue until the program is stopped. The fitness scores will increase over time, showcasing
the evolution and increased survival of the robots through generations.

## Key Features
- Robot Sensors: 4 sensors detect adjacent squares/New maps will generate a different code for the sensor/Sensor states include no object, wall object, battery object, and ignore what is there
- Robot Genes: 16 genes for each robot/Each gene is an array with 5 codes/4 Robot actions/Every turn, the robot compares the current sensor state with its genetic code to find a match
- Map: Robot placed in random spot/populate 40% of squares with batteries/Make a new map for each robot/Each square consumes 1 unit/Invalid moves consume energy but keep robot stationary
- Population: 200 randomly generated robots at start/Count the number of turns they survive
- Robot Reproduction: Record total energy harvested by entire generation and breed robots/Sort population by energy harvested
- Genetic Algorithms: Fitness is the total amount of power harvested when each robot's time ends/Calculate the average fitness score for the whole population/Save average fitness for each generation/Print out average fitness scores
