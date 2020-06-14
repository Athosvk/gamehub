#include <iostream>
#include <array>
#include <algorithm>

#include "Die.h"

struct SimulationResult
{
	unsigned attackersLeft;
	unsigned defendersLeft;
};

template<unsigned TSize>
std::array<unsigned, TSize> RollDice(std::array<Die, TSize>& a_Dice, unsigned a_NumRolls)
{
	std::array<unsigned, TSize> rolls;
	for (unsigned i = 0; i < a_NumRolls; i++)
	{
		rolls[i] = a_Dice[i].Roll();
	}
	std::sort(rolls.begin(), rolls.end(), std::greater<unsigned>());
	return rolls;
}

SimulationResult Simulate(std::array<Die, 2>& a_DefenderDice, std::array<Die, 3>& a_AttackerDice)
{
	unsigned defendingUnits = 50000;
	unsigned attackingUnits = 50000;
	while (defendingUnits > 0 && attackingUnits > 0)
	{
		unsigned numAttackDice = std::min(3u, attackingUnits);
		std::array<unsigned, 3> attackResults = RollDice(a_AttackerDice, numAttackDice);
		unsigned numLargeRolls = std::count_if(attackResults.begin(), attackResults.end(), [](unsigned roll) { return roll > 3; });

		unsigned numDefenderDice = numLargeRolls > 1 ? 1 : std::min(defendingUnits, 2u);
		std::array<unsigned, 2> defenderResults = RollDice(a_DefenderDice, numDefenderDice);

		for (unsigned i = 0; i < std::min(numDefenderDice, numAttackDice); i++)
		{
			if (defenderResults[i] < attackResults[i])
			{
				defendingUnits--;
			}
			else
			{
				attackingUnits--;
			}
		}
	}
	return { attackingUnits, defendingUnits };
}

int main()
{
	std::array<Die, 2> defenderDice;
	std::array<Die, 3> attackerDice;

	while (true)
	{
		SimulationResult simResult = Simulate(defenderDice, attackerDice);
		std::cout << "Attackers left: " << simResult.attackersLeft << "\nDefenders left: " << simResult.defendersLeft << "\n";
		char c;
		std::cin >> c;
	}
}