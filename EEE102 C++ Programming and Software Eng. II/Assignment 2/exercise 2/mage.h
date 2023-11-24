//=======================
//		mage.h
//=======================

// Derived from base class player
// For the job Mage

#ifndef mage_h
#define mage_h

#include "player.h"
#include <string>
using namespace std;

class mage : public player		// subclass swordsman publicly inherited from base player
{
public:
    mage(int lv_in = 1, string name_in = "Not Given");
    // constructor with default level of 1 and name of "Not given"
    void isLevelUp();
    bool attack(player &p);
    bool specialatt(player &p);
    /* These three are derived from the pure virtual functions of base class
     The definition of them will be given in this subclass. */
    void AI(player &p);				// Computer opponen
};

#endif /* mage_h */
