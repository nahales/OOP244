#include <iostream>
#include "SuperHero.h"
#include "Hero.h"
#include <cstring>
using namespace std;
SuperHero::SuperHero() : Hero()
{
	m_superPowerAttack = 0;
	m_superPowerDefend = 0;
}
        
        
SuperHero::SuperHero( const char* name, unsigned maximumHealth, unsigned attack,
                unsigned superPowerAttack, unsigned superPowerDefend
        )  : Hero(name, maximumHealth, attack)
{ 
	strcpy(m_name, name);
	m_maximumHealth = maximumHealth;
	m_attack = attack;
	m_health = maximumHealth;
	m_superPowerAttack = superPowerAttack;
	m_superPowerDefend = superPowerDefend;
}



  
        
unsigned SuperHero::getAttack() const 
{ 
	return m_superPowerAttack;
}
