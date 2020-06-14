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
	rolls.fill(0);
	for (unsigned i = 0; i < a_NumRolls; i++)
	{
		rolls[i] = a_Dice[i].Roll();
	}
	std::sort(rolls.begin(), rolls.end(), std::greater<unsigned>());
	return rolls;
}

SimulationResult Simulate(std::array<Die, 2>& a_DefenderDice, std::array<Die, 3>& a_AttackerDice)
{
	unsigned defendingUnits = 15;
	unsigned attackingUnits = 15;
	while (defendingUnits > 0 && attackingUnits > 1)
	{
		unsigned numAttackDice = std::min(3u, attackingUnits - 1);
		std::array<unsigned, 3> attackResults = RollDice(a_AttackerDice, numAttackDice);
		unsigned numLargeRolls = std::count_if(attackResults.begin(), attackResults.end(), [](unsigned roll) { return roll > 3; });

		unsigned numDefenderDice =  std::min(defendingUnits, numLargeRolls > 1 && defendingUnits > 2u ? 1u : 2u);
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

	unsigned attackWins = 0;
	unsigned defenseWins = 0;
	while (true)
	{
		SimulationResult simResult = Simulate(defenderDice, attackerDice);
		if (simResult.attackersLeft > simResult.defendersLeft)
		{
			attackWins++;
			std::cout << "Attackers won";
		}
		else
		{
			defenseWins++;
			std::cout << "Defenders won";
		}
		std::cout << "\nAttackers left: " << simResult.attackersLeft << "\nDefenders left: " << simResult.defendersLeft << "\n";
		std::cout << "Attackers have won " << attackWins << " out of " << (attackWins + defenseWins);
		char c;
		std::cin >> c;
	}
}