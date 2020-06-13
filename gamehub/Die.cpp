#include "Die.h"

Die::Die() : 
	m_Distribution(1,6),
	m_RandomGenerator(std::random_device()())
{
}

unsigned Die::Roll()
{
	return m_Distribution(m_RandomGenerator);
}
