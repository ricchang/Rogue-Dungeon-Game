//
//  Actors.h
//  Proj 3
//
//  Created by Eric Chang on 5/25/15.
//  Copyright (c) 2015 Eric Chang. All rights reserved.
//

#ifndef __Proj_3__Actors__
#define __Proj_3__Actors__

#include <stdio.h>
#include <string>
#include "constants.h"
#include "Utilities.h"
#include "Levels.h"
#include "Items.h"

using namespace std;

class Levels;
class Items;

class Actor
{
public:
    //constructor that points to the level, gives the attributes, item wielded, and the symbol
    Actor(Levels* l, int r, int c, int hp, int armor, int strength, int dex, Items* wield, string name, char rep);
    //virtual destructor
    virtual ~Actor();
    
    
    //Accessor Functions
    //just returns attributes
    int row() const {return m_row;}
    int col() const {return m_col;}
    int hp() const {return m_hp;}
    int maxhp() const {return max_hp;}
    int armor() const {return m_armor;}
    int strength() const {return m_strength;}
    int dex() const {return m_dex + m_itemdex;}
    int dmg() const {return m_dmg+ m_itemdmg;}
    char rep() const {return m_rep;}
    string name() const {return m_name;}
    Items* wielding() const {return m_wield;}
    
    
    //returns statuses of sleep or death
    bool issleep() const;
    bool isdead() const;
    
    //returns the level
    Levels* level() const {return m_level;}
    
    //Mutators
    
    //moves the actor
    void move(int r, int c);
    
    //changes the attributes
    void hitorheal(int x);
    void addmaxhp(int x);
    void addarmor ( int x);
    void addstrength(int x);
    void adddex (int x);
    void addsleep(int x);
    void switchmaxsleep(int x);
    void adddmg(int x);
    void changedeath (bool x);
    void setweapon (Items* x);
    
    
    //Virtual functions
    virtual void attack(int r, int c, string & action);
    virtual void drop(int r, int c);
    virtual char moveto (int r, int c){return ' ';}
    //monsters check distance to player differently
    virtual bool checkdistance();
    
    bool checkplayer (int r, int c) const;
    void newlevel(Levels * l, int r, int c);
    bool checkweapon();
    bool move (char dir, string&str);
    void heal();
    int rowabsval();
    int colabsval();
    
private:
    //coordinates of the actor
    int m_row;
    int m_col;
    
    //attributes of the actor
    string m_name;
    int m_hp;
    int max_hp;
    int m_armor;
    int m_strength;
    int m_dex;
    int m_sleep;
    int m_maxsleep;
    int m_dmg;
    
    bool m_dead;
    
    //the symbol that represents the actor
    char m_rep;
    
    //the level that the actor is in
    Levels* m_level;
    
    //the item the actor wields
    Items* m_wield;
    int m_itemdex;
    int m_itemdmg;
    
    
};


class Player: public Actor
{
public:
    // Constructor
    Player(Levels *ap, int r, int c);
    virtual ~Player() {}
    
    int  items() const {return m_items;}
    bool showInvent(char type, string& str);
    
    // Mutators
    void	moreItems() { m_items++; } // add to items
    void	holdItems(Items* a) {m_invent.push_back(a);} // add to vector
    void	cheat();
    void	useScroll(Items* a);
    virtual void attack(int r, int c, string &act);
    
private:
    vector<Items*> m_invent;
    Actor*  m_monsters;
    int		m_items; // number of items in inventory
};

//MONSTERSSSSSSSSS
class Bogeyman: public Actor
{
public:
    Bogeyman();
    Bogeyman(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    
    virtual ~Bogeyman();
private:
    
};

class Snakewomen: public Actor
{
public:
    Snakewomen();
    Snakewomen(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    virtual ~Snakewomen();
private:
    
};

class Dragon: public Actor
{
public:
    Dragon();
    Dragon(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    virtual ~Dragon();
private:
    
};

class Goblin: public Actor
{
public:
    Goblin();
    Goblin(Levels* ap, int r, int c);
    virtual void drop(int r, int c);
    virtual bool checkDistance();
    virtual char moveDir(int r, int c);
    virtual ~Goblin();
private:
    
};



#endif /* defined(__Proj_3__Actors__) */
