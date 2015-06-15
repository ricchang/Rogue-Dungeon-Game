//
//  Actors.cpp
//  Proj 3
//
//  Created by Eric Chang on 5/25/15.
//  Copyright (c) 2015 Eric Chang. All rights reserved.
//

#include "Actors.h"

//Constructor
Actor:: Actor (Levels* l, int r, int c, int hp, int armor, int strength, int dex, Items* wield, string name, char rep) {
    m_level = l;
    m_row = r;
    m_col = c;
    m_hp = hp;
    m_armor = armor;
    m_strength = strength;
    m_dex = dex;
    m_wield = wield;
    m_name = name;
    m_rep = rep;
    
    
}

//Destructor
Actor::~Actor() {
    delete m_wield;
}

bool Actor:: issleep() const {
 if (m_sleep > 0)
     return true;
else
    return false;
    
}

bool Actor:: isdead() const {
    if (m_hp <= 0)
        return true;
    else
        return false;
}

void Actor :: move(int r, int c) {
    
    m_row = r;
    m_col = c;
    
    
}

void Actor:: hitorheal(int x) {
    
    m_hp = x + m_hp;
    if (m_hp > max_hp)
        m_hp = max_hp;
    
}

void Actor :: addmaxhp(int x) {
    
    max_hp = max_hp + x;
}

void Actor :: addarmor(int x) {
    
    m_armor = m_armor + x;
}
void Actor :: addstrength(int x) {
    
    m_strength = m_strength + x;
}
void Actor :: adddex(int x) {
    
    m_dex = m_dex + x;
}
void Actor :: addsleep(int x) {
    
    m_sleep = m_sleep + x;
}

void Actor::switchmaxsleep(int x) {
    
    if (x > maxsleep)
        m_maxsleep = x;
}
void Actor :: adddmg(int x) {
    
    m_dmg = m_dmg + x;
}

void Actor:: changedeath(bool x) {
    
    m_dead = x;
}

void Actor:: setweapon(Items* x) {
    
    m_wield = x;
}

void Actor:: attack(int r, int c, string & action) {
    
    bool strike;
    
    if (level()->player()->row() == r && level ()->player()->col() == c) {
        //pointer to the player
        Actor* pla = level()->player();
        
        //calculating dexterity bonus
        int attackerpoints = dex();
        int defenderpoints = pla->dex() + pla->armor();
        
        //chances to strike
        if (randInt(attackerpoints) >= randInt(defenderpoints)){
            
            strike = true;
            //subtract from HP
            pla-> hitorheal(randInt(strength() + dmg())* -1);
            
            if(wielding()->name() == "magic fangs of sleep")
            {
                //generate a random number from 1-5 to see if sleeps
                if (randInt(5) == 0) {
                    
                    if (!pla -> issleep()) {
                        
                        int x = randInt(5) +2;
                        pla -> switchmaxsleep(x);
                        pla -> addsleep(x);
                    }
                    else
                        pla -> addsleep(randInt(5) +2);
                        
                }
                
            }
            
        }
        
        //add to action string whether or not there was a hit
        if (strike)
        {
            if (pla-> isdead())
                action += (name() + " " + wielding()->action() + " " + wielding()->name()
                        + " at " + pla->name() + ", dealing the final blow." + '\n');
            else if (pla->issleep())
                action += (name() + " " + wielding()->action() + " " + wielding()->name()
                        + " at " + pla->name() + " and hits, putting " + pla->name() + " to sleep." + '\n');
            else
                action += (name() + " " + wielding()->action() + " " + wielding()->name()
                        + " at " + pla->name() + " and hits." + '\n');
        }
        else
            action += (name() + " " + wielding()->action() + " " + wielding()->name()
                    + " at " + pla->name() + " and misses." + '\n');
        
            
    }
    
    
}

bool Actor::move(char dir, string &str)
{
    //if the move is a monster's
    if (dir == 'p')
    {
        //check distance from monster to player
        dir = moveto(level()->player()->row(), level()->player()->col());
    }
    switch (dir)
    {
        case ARROW_UP:
            //check if it's a valid move, then move
            if (row() > 0 && level()->correctmove(row()-1, col()))
            {
                move(row()-1, col());
                return false;
            }
            
            //if you cant move there, attack!
            attack(row()-1, col(), str);
            return true;
            break;
        case ARROW_DOWN:
            //check if it's a valid move, then move
            if (row() < MAXROWS-1  && level()->correctmove(row()+1, col()))
            {
                move(row()+1, col());
                return false;
            }
            
            //if you cant move there, attack!
            attack(row()+1, col(), str);
            return true;
            break;
        case ARROW_LEFT:
            //check if it's a valid move, then move
            if (col() > 0 && level()->correctmove(row(), col()-1))
            {
                move(row(), col()-1);
                return false;
            }
            
            //if you cant move there, attack!
            attack(row(), col()-1, str);
            return true;
            break;
        case ARROW_RIGHT: 
            //check if it's a valid move, then move
            if (col() < MAXCOLS-1  && level()->correctmove(row(), col()+1))
            {
                move(row(), col()+1);
                return false;
            }
            //if you cant move there, attack!
            attack(row(), col()+1, str);
            return true;
            break;
    }
    return false;
}

void Actor:: drop(int r, int c) {}

bool Actor:: checkdistance() {
    
    return true;
}

bool Actor:: checkplayer(int r, int c) const{
    
    if (m_level ->player() ->row() && c== m_level ->player() ->col())
        return true;
    return false;
}

void Actor:: newlevel(Levels *l, int r, int c) {
    
    m_level = l;
    m_row = r;
    m_col = c;
    
}

//return true if actor is holding a weapon, false if not
bool Actor:: checkweapon() {
    
    if (m_wield == nullptr)
    {
        m_itemdex = 0;
        m_itemdmg = 0;
    }
    else
    {
        m_itemdmg = m_wield->dmg();
        m_itemdmg = m_wield -> dex();
        return true;
    }
    return false;
    
}

void Actor:: heal() {
    
    //only heals if actor isn't at full hp
    if (hp() < maxhp())
    {
        if (randInt(10)==0)
            hitorheal(1);
    }
}

int Actor:: rowabsval()
{
    int x = m_level->player()->row() - m_row;
    if (x<0)
        return x*-1;
    return x;
    
    
}

int Actor:: colabsval()
{
    int y = m_level->player()->col() - m_col;
    if (y<0)
        return y*-1;
    return y;
    
}

Player::Player(Levels* ap, int r, int c)
:Actor(ap, r, c, 20, 2, 2, 2, NULL, "Player", '@')
{
    holdItems(new ShortSword());
    setweapon(m_invent[0]);
}

void Player::cheat()
{
   // oops
    hitorheal(50);
    addstrength(9-strength());
}

bool Player::showInvent(char type, string &str)
{
    clearScreen();
    
    //display the invent
    cout << "Inventory: " << endl;
    int a;
    for (a = 0; a < m_invent.size(); a++)
    {
        char b = a + 'a';
        cout << " " << b << ". " << m_invent[a]->name() << endl;
    }
    
    //get a character
    char e = getCharacter();
    
    //equip an item if they had clicked w
    if (type == 'w')
        //make sure the character is within the item boundaries
        if (e < (a + 'a'))
            //if the character is a letter
            if (e >= 'a' && e <= 'z')
                //if the item symbol is weapon
                if (m_invent[e-'a']->sym() == ')')
                {
                    //equip and produce a message
                    setweapon(m_invent[e-'a']);
                    str = "You equipped " + m_invent[e-'a']->name();
                }
    
    //use a scroll if they had clicked r
    if (type == 'r')
        //make sure the character is within the item boundaries
        if (e < (a + 'a'))
            //if the character is a letter
            if (e >= 'a' && e <= 'z')
                //if the item symbol is scroll
                if (m_invent[e-'a']->sym() == '?')
                {
                    //add the message
                    str = "You used a " + m_invent[e-'a']->name() + ".";
                    switch (m_invent[e-'a']->type())
                    {
                        case 't':
                            str += " You have been teleported.";
                            break;
                        case 'a':
                            str += " Your armor has been enhanced.";
                            break;
                        case 's':
                            str += " Your strength increases.";
                            break;
                        case 'h':
                            str += " Your maximum health has increased.";
                            break;
                        case 'd':
                            str += " Your dexterity increases.";
                            break;
                        default:
                            break;
                    }
                    
                    //use the scroll and delete it
                    useScroll(m_invent[e-'a']);
                    vector<Items*>::iterator p = (m_invent.begin()+e-'a');
                    p = m_invent.erase(p);
                }
    return true;
}

void Player::attack(int r, int c, string &act)
{
    bool hit; // bool to check if someone was hit
    char a = level()->checkgrid(r,c);
    switch (a) {
        case 'S':
        case 'G':
        case 'D':
        case 'B':
        {
            //create a pointer to the monster
            Actor* ah = level()->monsters(r,c);
            
            //get dex and defense
            int aP = dex();
            int dP = ah->dex() + ah->armor();
            
            //chance to hit
            if (randInt(aP) >= randInt(dP))
            {
                hit = true;
                
                //do dmg to the monster
                ah->hitorheal(-1*(randInt(strength()+dmg())));
                
                //if fangs are equipped, sleep
                if (wielding()->name() == "magic fangs of sleep")
                {
                    if (randInt(5) == 0)
                    {
                        if (!ah->issleep())
                            ah->switchmaxsleep(2+randInt(5));
                        ah->switchmaxsleep(randInt(2+randInt(5)));
                        
                    }
                }
                
            }
            
            //if there was a hit, add to the string
            if (hit)
            {
                if (ah->isdead())
                    act += (name() + " " + wielding()->action() + " " + wielding()->name()
                            + " at " + ah->name() + " and hits, dealing the final blow." + '\n');
                else if (ah->issleep())
                    act += (name() + " " + wielding()->action() + " " + wielding()->name()
                            + " at " + ah->name() + " and hits, putting " + ah->name() + " to sleep." + '\n');
                else
                    act += (name() + " " + wielding()->action() + " " + wielding()->name()
                            + " at " + ah->name() + " and hits." + '\n');
            }
            else
                act += (name() + " " + wielding()->action() + " " + wielding()->name()
                        + " at " + ah->name() + " and misses." + '\n');
        }
            break;
        default:
            break;
    }
    
}

void Player::useScroll(Items* a)
{
    //check the type of scroll
    switch (a->type())
    {
        case 't':
        {
            //find a new spot and move
            int x=0, y=0;
            level()->checkgrid(x, y);
            move(x,y);
            break;
        }
        case 'a':
            addarmor(a->add());
            break;
        case 's':
            addstrength(a->add());
            break;
        case 'h':
            addmaxhp(a->add());
            break;
        case 'd':
            adddex(a->add());
            break;
        default:
            break;
    }
}




//MONSTERS AHHHHH
Bogeyman::Bogeyman(Levels* ap, int r, int c)
:Actor(ap, r, c, (5+randInt(6)), (2+randInt(2)), (2+randInt(2)), 2,
       new ShortSword(r,c), "the Bogeyman", 'B')
{
}
Bogeyman::~Bogeyman()
{
}
void Bogeyman::drop(int r, int c)
{
    //1 in 10 chance to drop
    if (randInt(10) == 0)
        if(level()->checkforitem(r, c))
            level()->additem(r, c, 9);
}
bool Bogeyman::checkDistance()
{
    //check to see if the distance is <= 5
    if (rowabsval() + colabsval() <= 5)
        return true;
    return false;
}
char Bogeyman::moveDir(int r, int c)
{
    int sc = col(), sr = row();
    
    //if it's not within distance, don't do anything
    if (!checkDistance())
        return ' ';
    
    //if it is, then check all the other directions
    else if (sr - r < 0 && !level()->iswall(sr+1, sc) &&
             (level()->correctmove(sr+1, sc) || checkplayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->iswall(sr-1, sc) &&
             (level()->correctmove(sr-1, sc) || checkplayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->iswall(sr, sc+1) &&
             (level()->correctmove(sr, sc+1) || checkplayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->iswall(sr, sc-1) &&
             (level()->correctmove(sr, sc-1) || checkplayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}



Snakewomen::Snakewomen(Levels* ap, int r, int c)
:Actor(ap, r, c, (3+randInt(4)), 2, 3, 3,
       new Fangs(r,c), "the Snakewomen", 'S')
{
}
Snakewomen::~Snakewomen()
{
}

void Snakewomen::drop(int r, int c)
{
    if (randInt(3) == 0)
        if(level()->checkforitem(r, c))
            level()->additem(r, c, 8);
}
bool Snakewomen::checkDistance()
{
    //distance of 3
    if (rowabsval() + colabsval() <= 3)
        return true;
    return false;
}
char Snakewomen::moveDir(int r, int c)
{
    int sc = col(), sr = row();
    
    //if it's not within distance, don't do anything
    if (!checkDistance())
        return ' ';
    
    //if it is, then check all the other directions
    else if (sr - r < 0 && !level()->iswall(sr+1, sc) &&
             (level()->correctmove(sr+1, sc) || checkplayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->iswall(sr-1, sc) &&
             (level()->correctmove(sr-1, sc) ||checkplayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->iswall(sr, sc+1) &&
             (level()->correctmove(sr, sc+1) ||checkplayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->iswall(sr, sc-1) &&
             (level()->correctmove(sr, sc-1) ||checkplayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}


Dragon::Dragon(Levels* ap, int r, int c)
:Actor(ap, r, c, (20+randInt(6)), 4, 4, 4,
       new LongSword(r,c), "the Dragon", 'D')
{
}
Dragon::~Dragon()
{
}
void Dragon::drop(int r, int c)
{
    if(level()->checkforitem(r, c))
        level()->additem(r, c, 3+randInt(5));
}
bool Dragon::checkDistance()
{
    //distance of 1
    if (rowabsval() + colabsval() <= 1)
        return true;
    return false;
}
char Dragon::moveDir(int r, int c)
{
    int sc = col(), sr = row();
    
    //if it's not within distance, don't do anything
    if (!checkDistance())
        return ' ';
    
    //if it is, then check all the other directions
    else if (sr - r < 0 && !level()->iswall(sr+1, sc) &&
             (level()->correctmove(sr+1, sc) || checkplayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->iswall(sr-1, sc) &&
             (level()->correctmove(sr-1, sc) ||checkplayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->iswall(sr, sc+1) &&
             (level()->correctmove(sr, sc+1) ||checkplayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->iswall(sr, sc-1) &&
             (level()->correctmove(sr, sc-1) ||checkplayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}

Goblin::Goblin(Levels* ap, int r, int c)
:Actor(ap, r, c, (15+randInt(6)), 3, 1, 1, 
       new ShortSword(r,c), "the Goblin", 'G')
{
}
Goblin::~Goblin()
{
}
void Goblin::drop(int r, int c)
{
    //1 in 3 chance to drop
    if (randInt(3) == 0)
        if(level()->checkforitem(r, c))
            level()->additem(r, c, 8+randInt(2));
}
bool Goblin::checkDistance()
{
    //distance of 15
    if (rowabsval() + colabsval() <= 15)
        return true;
    return false;
    
}
char Goblin::moveDir(int r, int c)
{
    int sc = col(), sr = row();
    
    //if it's not within distance, don't do anything
    if (!checkDistance())
        return ' ';
    
    //if it is, then check all the other directions
    else if (sr - r < 0 && !level()->iswall(sr+1, sc) &&
             (level()->correctmove(sr+1, sc) || checkplayer(sr+1, sc)))
        return ARROW_DOWN;
    else if (sr - r > 0 && !level()->iswall(sr-1, sc) &&
             (level()->correctmove(sr-1, sc) ||checkplayer(sr-1, sc)))
        return ARROW_UP;
    else if (sc - c < 0 && !level()->iswall(sr, sc+1) &&
             (level()->correctmove(sr, sc+1) ||checkplayer(sr, sc+1)))
        return ARROW_RIGHT;
    else if (sc - c > 0 && !level()->iswall(sr, sc-1) &&
             (level()->correctmove(sr, sc-1) ||checkplayer(sr, sc-1)))
        return ARROW_LEFT;
    else
        return ' ';
}

