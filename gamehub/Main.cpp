#include <iostream>
#include <array>
#include <algorithm>

#include "Die.h"

int main()
{
	std::array<Die, 2> defenderDice;
	std::array<Die, 3> attackerDice;

	unsigned defendingUnitsLost = 0;
	unsigned attackingUnitsLost = 0;
	for (int i = 0; i < 5000; i++)
	{
		unsigned numAttackDice = 3;
		std::array<unsigned, 3> rolledDigits;
		for (unsigned i = 0; i < numAttackDice; i++)
		{
			rolledDigits[i] = attackerDice[i].Roll();
		}
		std::sort(rolledDigits.begin(), rolledDigits.end(), std::greater<unsigned>());

		unsigned numLargeNumbers = std::count_if(rolledDigits.begin(), rolledDigits.end(), [](unsigned roll) { return roll > 3; });

		unsigned numDefenderDice = numLargeNumbers > 1 ? 1 : 2;
		std::array<unsigned, 2> defenderRolledDigits;
		for (unsigned i = 0; i < numDefenderDice; i++)
		{
			defenderRolledDigits[i] = defenderDice[i].Roll();
		}
		std::sort(defenderRolledDigits.begin(), defenderRolledDigits.end(), std::greater<unsigned>());

		for (unsigned i = 0; i < std::min(numDefenderDice, numAttackDice); i++)
		{
			if (defenderRolledDigits[i] < rolledDigits[i])
			{
				defendingUnitsLost++;
			}
			else
			{
				attackingUnitsLost++;
			}
		}
	}
	std::cout << "Attackers lost: " << attackingUnitsLost << "\nDefenders lost: " << defendingUnitsLost << "\n";
	char c;
	std::cin >> c;
}