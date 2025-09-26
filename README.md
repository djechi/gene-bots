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

### Robot Specifications
Sensors: 4 directional sensors (North, South, East, West) detecting adjacent squares

Sensor States: Empty, Wall, Battery, or Ignore

Genes: 16 genes per robot, each containing 5 codes (4 sensor states + 1 action)

Actions: Move North, South, East, West, or Random direction

### Environment
Grid: 10x10 navigation area with boundary walls

Batteries: 40% of squares randomly populated with energy sources

Energy System: Start with 5 units, -1 per move, +5 per battery collected

Map Generation: Unique random map for each robot evaluation

### Genetic Algorithm
Population: 200 robots per generation

Fitness: Total batteries collected during lifespan

Selection: Top 50% survive and reproduce

Crossover: Two parents produce two children with combined genes

Mutation: 5% chance per gene to introduce random changes

Evolution: Continuous improvement over generations

### Simulation Process
Initialization: Create 200 robots with random genes

Evaluation: Each robot navigates its own random map until energy depletion

Selection: Rank robots by batteries collected, keep the top 100

Reproduction: Breed survivors to repopulate to 200 robots

Iteration: Repeat the process for a specified number of generations

Analysis: Track and display average fitness scores per generation
