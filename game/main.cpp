#include "includ/GameInit.hpp"

/**
 * @brief Main function to start the game.
 * 
 * @return int Exit status code.
 */
int main(int argc, const char **argv)
{
	GameInit *init = new GameInit(argc, argv);
    return init->Start();
}
