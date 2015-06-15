//
//  Items.h
//  Proj 3
//
//  Created by Eric Chang on 5/25/15.
//  Copyright (c) 2015 Eric Chang. All rights reserved.
//

#ifndef __Proj_3__Items__
#define __Proj_3__Items__

#include "utilities.h"
#include <string>

using namespace std;

class Items
{
public:
    // Constructor/destructor
    Items();
    //weapon constructor
    Items(int a, int b, int r, int c, char sym, string name, string action);
    //idol constructor
    Items(int r, int c);
    //scroll constructor
    Items(int a, int r, int c, char sym, string name, char type);
    
    
    // Accessors
    int rows() { return i_row; }
    int cols() { return i_col; }
    int dmg() { return i_dmg; }
    int dex() { return i_dex; }
    int add() { return i_add; }
    char sym() { return i_symbol; }
    char type() { return i_type; }
    string name() { return i_name; }
    string action() { return i_action; }
    
    // Mutators
    
private:
    int i_row, i_col; // position of items
    int i_dmg, i_dex, i_add; // what the items do
    char i_symbol;
    char i_type;
    string i_name;
    string i_action;
};

class Mace: public Items
{
public:
    Mace();
    Mace(int r, int c);
};

class ShortSword: public Items
{
public:
    ShortSword();
    ShortSword(int r, int c);
};

class LongSword: public Items
{
public:
    LongSword();
    LongSword(int r, int c);
};

class Axe: public Items
{
public:
    Axe();
    Axe(int r, int c);
};

class Fangs: public Items
{
public:
    Fangs();
    Fangs(int r, int c);
};

class Tele: public Items
{
public:
    Tele();
    Tele(int r, int c);
};

class Armor: public Items
{
public:
    Armor();
    Armor(int r, int c);
};

class Str: public Items
{
public:
    Str();
    Str(int r, int c);
};

class Health: public Items
{
public:
    Health();
    Health(int r, int c);
};

class Dex: public Items
{
public:
    Dex();
    Dex(int r, int c);
};

#endif /* defined(__Proj_3__Items__) */
