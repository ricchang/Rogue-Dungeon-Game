//
//  Items.cpp
//  Proj 3
//
//  Created by Eric Chang on 5/25/15.
//  Copyright (c) 2015 Eric Chang. All rights reserved.
//

#include "Items.h"

#include "Items.h"

Items::Items()
{
}

Items::Items(int r, int c)
:i_row(r), i_col(c)
{
    
}

//for scrolls
Items::Items(int a, int r, int c, char sym, string name, char type)
:i_add(a), i_row(r), i_col(c), i_name(name), i_symbol(sym), i_type(type)
{
}

//for weapons
Items::Items(int a, int b, int r, int c, char sym, string name, string act)
:i_dmg(a), i_dex(b), i_row(r), i_col(c), i_add(0), i_name(name), i_symbol(sym),
i_action(act)
{
}
Mace::Mace()
{}

Mace::Mace(int r, int c)
:Items(2, 0, r, c, ')', "mace", "swings")
{}

ShortSword::ShortSword()
:Items(2, 0, 0, 0, ')', "short sword", "slashes")
{
}

ShortSword::ShortSword(int r, int c)
:Items(2, 0, r, c, ')', "short sword", "slashes")
{
}

LongSword::LongSword()
{
}

LongSword::LongSword(int r, int c)
:Items(4, 2, r, c, ')', "long sword", "slashes")
{
}

Axe::Axe()
{
}

Axe::Axe(int r, int c)
:Items(5, 5, r, c, ')', "magic axe", "swings")
{
}

Fangs::Fangs()
{
}

Fangs::Fangs(int r, int c)
:Items(2, 3, r, c, ')', "magic fangs of sleep", "strikes")
{
}



//scrolls
Tele::Tele()
{
}


//scrolls
Tele::Tele(int r, int c)
:Items(0, r, c, '?', "scroll of teleportation", 't')
{
}


Armor::Armor()
{
}

Armor::Armor(int r, int c)
:Items(1+randInt(3), r, c, '?', "scroll of enhanced armor", 'a')
{
}

Str::Str()
{
}

Str::Str(int r, int c)
:Items(1+randInt(3), r, c, '?', "scroll of strength", 's')
{
}

Health::Health()
{
}

Health::Health(int r, int c)
:Items(3+randInt(6), r, c, '?', "scroll of health", 'h')
{
}

Dex::Dex()
{
}

Dex::Dex(int r, int c)
:Items(1, r, c, '?', "scroll of dexterity", 'd')
{
}