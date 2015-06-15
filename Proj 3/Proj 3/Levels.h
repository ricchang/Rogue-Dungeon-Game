//
//  Levels.h
//  Proj 3
//
//  Created by Eric Chang on 5/25/15.
//  Copyright (c) 2015 Eric Chang. All rights reserved.
//

#ifndef __Proj_3__Levels__
#define __Proj_3__Levels__

#include <stdio.h>
#include "utilities.h"
#include <vector>
#include <iostream>
#include "Actors.h"
#include "Items.h"
#include "Player.h"
#include "constants.h"
using namespace std;

class Player;
class Items;
class Actor;

class Levels
{
public:

    //constructors; one for first level, one for the next levels
    Levels();
    Levels(int l, Player* p);
    
    //destructor
    ~Levels();
    
    //Accessor Functions
    char checkgrid(int r, int c) {return room[r][c];}
    int pr() const {return m_pr;}
    int pc() const {return m_pc;}
    Player* player() const {return m_player;}
    Actor* monsters (int r, int c) const;
    
    void display();
    
    //mutators
    bool addplayer();
    bool rooms(int& row, int & col);
    void design();
    void opencoord(int&x, int&y);
    bool correctmove(int r, int c);
    bool iswall(int r, int c);
    bool moveroom();
    bool itemget(string& yes);
    bool additem(int r, int c, int x);
    bool addmonster(int x);
    bool checkmonsterdeath();
    bool checkforitem(int r, int c);
    bool monstersmove(string& yes);
    
private:
    //GRID
    char room[MAXROWS][MAXCOLS];
    
    //number of rows and cols
    int m_rows;
    int m_cols;
    
    //number of rooms
    int m_rooms;
    int m_track;
    int m_level;
    
    //coordinates of the player
    int m_pr;
    int m_pc;
    
    //coordinates of the stairs/golden idol
    int m_er;
    int m_ec;
    
    Items m_idol;
    vector<Items*> m_items;
    vector <Actor*> m_monsters;
    
    Player* m_player;
    
    
    
};

#endif /* defined(__Proj_3__Levels__) */
