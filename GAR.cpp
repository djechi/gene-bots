// GAR.cpp
// DJ Echipare, CISP 400
// 12/13/23
// This program makes use of genetic algorithms to evolve a population of robots in order to navigate a 10x10 grid to collect batteries efficiently, increasing survival time through natural selection

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

//Cardinal directions: 1 means North, 2 means South, 3 means East, 4 means West
void ProgramGreeting();

struct Robots
{
  static const int GRID_SIZE = 12;
  static const int GENE_LENGTH = 16;
  static const int GENE_COLUMNS = 5;  
  static const int MAX_ENERGY = 5;
  static const int MAX_BATTERIES = 40;
  static const int RANDOM_ACTION = 4; // Magic number for "random move"
  static const int DIRECTION_COUNT = 4; // North, South, East, West
  static const int MUTATION_RATE = 5; // 5% mutation chance
  static const int MAP_SIZE = 10;  
  int xLocation;
  int yLocation;
  int gridDesign[GRID_SIZE][GRID_SIZE];
  int geneCode[GENE_LENGTH][GENE_COLUMNS];
  int turnsSurvived = 0;
  float batteryCount = 0.0;

  void randomMapping();
  void genes();
  void sensor(int i);
};

void Robots::genes()
{
  for (int a = 0; a < GENE_LENGTH; a++)
    {
      for (int b = 0; b < DIRECTION_COUNT; b++)
        {
            geneCode[a][b] = rand() % DIRECTION_COUNT;  // Generates genes
        }
            geneCode[a][4] = rand() % (DIRECTION_COUNT + 1);  // Generates actions (4 directions + random action)
    }
}

void Robots::sensor(int i)
{

  if(i == 0)  // Allows genes(); to run once for the first generation
  {
    genes();
  }
  
  randomMapping();

  int energy = MAX_ENERGY;
  xLocation = rand() % MAP_SIZE + 1;
  yLocation = rand() % MAP_SIZE + 1;

  turnsSurvived = 0;
  batteryCount = 0.0;

  do
  {
    int changeX[] = {0, 0, 1, -1};  // Change in X for North, South, East, West
    int changeY[] = {-1, 1, 0, 0};  // Change in Y for North, South, East, West

    for (int a = 0; a < GENE_LENGTH; a++)
    {
      int sensorActions[DIRECTION_COUNT] = {geneCode[a][0], geneCode[a][1], geneCode[a][2], geneCode[a][3]};

      if (((gridDesign[xLocation + changeX[0]][yLocation + changeY[0]] == sensorActions[0]) || (sensorActions[0] == 3)) &&    // Checks North
      ((gridDesign[xLocation + changeX[1]][yLocation + changeY[1]] == sensorActions[1]) || (sensorActions[1] == 3)) &&        // Checks South
      ((gridDesign[xLocation + changeX[2]][yLocation + changeY[2]] == sensorActions[2]) || (sensorActions[2] == 3)) &&        // Chekcs East
      ((gridDesign[xLocation + changeX[3]][yLocation + changeY[3]] == sensorActions[3]) || (sensorActions[3] == 3)))          // Chekcs West
      {
        turnsSurvived++;
        int action = geneCode[a][4];
      
        if (action == RANDOM_ACTION)  // Random Move
        {
          action = rand() % DIRECTION_COUNT;
        }

        xLocation += changeX[action];
        yLocation += changeY[action];

        if (gridDesign[xLocation][yLocation] == 1)
        {
          xLocation -= changeX[action]; // Revert move if hitting a wall
          yLocation -= changeY[action];
          energy--; // Hitting a wall will decrease energy
        }
      
        energy--;
        break;  // Break out of the loop when a gene matches
      }
      else if (a == GENE_LENGTH - 1)
      {
        int action = geneCode[a][4];
        if (action == RANDOM_ACTION)
        {
          action = rand() % DIRECTION_COUNT;
        }

        xLocation += changeX[action];
        yLocation += changeY[action];

        if (gridDesign[xLocation][yLocation] == 1)
        {
          xLocation -= changeX[action]; // Revert move if hitting a wall
          yLocation -= changeY[action];
          energy--;
        }

        energy--;
    }
  }

  if (gridDesign[xLocation][yLocation] == 2)  // Update the map whenever the robot gets a battery
  {
    energy += MAX_ENERGY;
    batteryCount++;
    gridDesign[xLocation][yLocation] = 0;
  }

  } while (energy > 0);
}

void Robots::randomMapping()
{
  int randomX = 0;
  int randomY = 0;
  int batteriesPlaced = 0;

  for (int i = 0; i < GRID_SIZE; i++) //Resets the map
  {
    for (int a = 0; a < GRID_SIZE; a++)
    {
      gridDesign[i][a] = 0;
    }
  }

  for (int a = 0; a < GRID_SIZE; a++) // Generates walls on the edge of the map
  {
    gridDesign[a][0] = 1;
    gridDesign[a][GRID_SIZE - 1] = 1;
    gridDesign[0][a] = 1;
    gridDesign[GRID_SIZE - 1][a] = 1;
  }

  while (batteriesPlaced < MAX_BATTERIES) // Place batteries on the map
  {
    randomX = rand() % MAP_SIZE + 1;
    randomY = rand() % MAP_SIZE + 1;

    if (gridDesign[randomX][randomY] == 0)  // Makes sure that the place to place the batteries is an empty space
    {
      gridDesign[randomX][randomY] = 2;
      batteriesPlaced++;
    }
  }

}

int main() 
{
  srand(time(NULL));
  const int POPULATION_SIZE = 200;
  const int MAX_BATTERIES = 40;
  const int GENE_LENGTH = 16;
  const int GENE_COLUMNS = 5;
  const int CROSSOVER_POINT = 8;  // Half of GENE_LENGTH
  const int MUTATION_RATE = 5;
  const int DIRECTION_COUNT = 4;  // North, South, East, West
  int generationCount = 0;
  int mutationChance = 0;
  int number;
  bool check;
  float fitnessScore = 0.0;
  string option;
  Robots robotGeneration[POPULATION_SIZE];
  Robots pTmp[POPULATION_SIZE];

  ProgramGreeting();
  cout << "Press <Enter> to continue to the program.";
  getline(cin,option);
  
  do
  { 
    cout <<"\n\nHow many generations of robots would you like to generate?\n\nEnter in a number: ";
    cin >> number;
  } while(number < 0);

  vector<float> fitnessArray(number);
  
  for (int a = 0; a < number; a++)
    {
      for (int b = 0; b < POPULATION_SIZE; b++)
        {
          robotGeneration[b].sensor(generationCount);
        }
      
      for (int c = 0; c < POPULATION_SIZE; c++)
        {
          fitnessScore = fitnessScore + robotGeneration[c].batteryCount;
        }
      
      fitnessArray[a] = fitnessScore = fitnessScore/POPULATION_SIZE;

       do
        {
          check = false;
          for(int d = 0; d < POPULATION_SIZE - 1; d++)
            {
              if (robotGeneration[d].batteryCount < robotGeneration[d + 1].batteryCount)
              {
                swap(robotGeneration[d], robotGeneration[d + 1]);
                check = true;
              }
            }
        } while(check);

      for (int e = 0; e < POPULATION_SIZE/2; e++)
        {
          for (int f = 0; f < GENE_LENGTH; f++)
            {
              for (int g = 0; g < GENE_COLUMNS; g++)
                {
                  pTmp[e].geneCode[f][g] = robotGeneration[e].geneCode[f][g];
                }
            }
        }

      for (int h = POPULATION_SIZE/2; h < POPULATION_SIZE; h += 2)
        {
          for (int i = 0; i < CROSSOVER_POINT; i++)
            {
              for (int j = 0; j < GENE_COLUMNS; j++)
                {
                  if ((mutationChance = rand() % 100 + 1) < MUTATION_RATE)
                  {
                    pTmp[h].geneCode[i][j] = rand() % DIRECTION_COUNT;  // Random move when there is a mutation
                  }
                  else
                  {
                    pTmp[h].geneCode[i][j] = pTmp[h-(POPULATION_SIZE/2)].geneCode[i + CROSSOVER_POINT][j];  // Second half of 1st parents genes to first child
                  }
                  
                  if ((mutationChance = rand() % 100 + 1) < MUTATION_RATE)
                  {
                    pTmp[h + 1].geneCode[i][j] = rand() % DIRECTION_COUNT;
                  }
                  else
                  {
                    pTmp[h + 1].geneCode[i][j] = pTmp[h - (POPULATION_SIZE/2)].geneCode[i][j];  // First half of 1st parent's genes to second child
                  }

                  if((mutationChance = rand() % 100 + 1) < MUTATION_RATE)
                  {
                    pTmp[h].geneCode[i + CROSSOVER_POINT][j] = rand() % DIRECTION_COUNT;
                  }
                  else
                  {
                    pTmp[h].geneCode[i + CROSSOVER_POINT][j] = pTmp[h - ((POPULATION_SIZE/2) - 1)].geneCode[i][j];  // First half of second parent's genes to first child
                  }

                  if((mutationChance = rand() % 100 + 1) < MUTATION_RATE)
                  {
                    pTmp[h + 1].geneCode[i + CROSSOVER_POINT][j] = rand() % DIRECTION_COUNT;
                  }
                  else
                  {
                    pTmp[h + 1].geneCode[i + CROSSOVER_POINT][j] = pTmp[h - ((POPULATION_SIZE/2) - 1)].geneCode[i + CROSSOVER_POINT][j];  // Second half of second parent's genes to second child
                  }
                }
            }
        }
      for (int i = 0; i < POPULATION_SIZE; i++)
        {
          robotGeneration[i] = pTmp[i];
        }
      generationCount++;
    }

  for (int i = 0; i < number; i++)
    {
      cout << "\nGeneration " << i + 1 << "    Fitness Score: " << fitnessArray[i] << endl;
    }

  return 0;
}

void ProgramGreeting()
{
  cout << "Welcome to Genetic Algorithm Robots.\n\n";
  cout << "By: DJ Echipare\n\n";
  cout << "Description: This program will simulate a population of 200 robots that will navigate on a 10x10 grid map. This objective of the robots are to collect batteries in order for to survive. After every robot is done, the fitness scores will be calculated to find the average. The top 100 robots will survive while the rest are eliminated. The top 100 robots will then repopulate the population until 200 robots are up again. The genes from two parent robots will be transferred to their children. This process will continue until the program is stopped. The fitness scores over time will increase.\n\n";
}