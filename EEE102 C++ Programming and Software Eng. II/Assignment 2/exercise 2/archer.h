//=======================
//		archer.h
//=======================

// Derived from base class player
// For the job Archer

#ifndef archer_h
#define archer_h
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

class archer : public player		// subclass swordsman publicly inherited from base player
{
public:
    archer(int lv_in = 1, string name_in = "Not Given");
    // constructor with default level of 1 and name of "Not given"
    void isLevelUp();
    bool attack(player &p);
    bool specialatt(player &p);
    /* These three are derived from the pure virtual functions of base class
     The definition of them will be given in this subclass. */
    void AI(player &p);				// Computer opponent
};

#endif /* archer_h */
