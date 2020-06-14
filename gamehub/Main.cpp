#include <iostream>
#include <array>
#include <algorithm>

#include "Die.h"

struct SimulationResult
{
	unsigned attackersLeft;
	unsigned defendersLeft;
};

SimulationResult Simulate(std::array<Die, 2>& a_DefenderDice, std::array<Die, 3>& a_AttackerDice)
{
	unsigned defendingUnits = 50000;
	unsigned attackingUnits = 50000;
	while (defendingUnits > 0 && attackingUnits > 0)
	{
		unsigned numAttackDice = std::min(3u, attackingUnits);
		std::array<unsigned, 3> rolledDigits;
		for (unsigned i = 0; i < numAttackDice; i++)
		{
			rolledDigits[i] = a_AttackerDice[i].Roll();
		}
		std::sort(rolledDigits.begin(), rolledDigits.end(), std::greater<unsigned>());

		unsigned numLargeNumbers = std::count_if(rolledDigits.begin(), rolledDigits.end(), [](unsigned roll) { return roll > 2; });

		unsigned numDefenderDice = numLargeNumbers > 1 ? 1 : std::min(defendingUnits, 2u);
		std::array<unsigned, 2> defenderRolledDigits;
		for (unsigned i = 0; i < numDefenderDice; i++)
		{
			defenderRolledDigits[i] = a_DefenderDice[i].Roll();
		}
		std::sort(defenderRolledDigits.begin(), defenderRolledDigits.end(), std::greater<unsigned>());

		for (unsigned i = 0; i < std::min(numDefenderDice, numAttackDice); i++)
		{
			if (defenderRolledDigits[i] < rolledDigits[i])
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