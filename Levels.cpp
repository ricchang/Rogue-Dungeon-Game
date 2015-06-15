//
//  Levels.cpp
//  Proj 3
//
//  Created by Eric Chang on 5/25/15.
//  Copyright (c) 2015 Eric Chang. All rights reserved.
//

#include "Levels.h"

Levels:: Levels()
{
    m_player = nullptr;
    m_rows = MAXROWS;
    m_cols = MAXCOLS;
    m_er = 0;
    m_ec = 0;
    m_level = 0;
    
    m_rooms = randInt(3) +4;
    m_track = 0;
    
    for (int r = 0; r < MAXROWS; r++)
        for (int c = 0; c<MAXCOLS; c++)
            room[r][c] = '#';
    
    design();
    
    opencoord(m_pr, m_pc);
}

Levels:: ~Levels()
{
    delete m_player;
    
    for (int i = 0; i < m_items.size(); i++)
    {
        delete m_items[i];
    }
    for (int j = 0; j < m_monsters.size(); j++)
    {
        delete m_monsters[j];
    }
    
    
}

Levels:: Levels (int l, Player* p) {
    
    m_player = p;
    m_rows = MAXROWS;
    m_cols = MAXROWS;
    m_er = 0;
    m_ec = 0 ;
    m_level = l;
    
    m_rooms = l*(randInt(3) +1) + 4;
    m_track = 0;
    for (int r = 0; r < MAXROWS; r++)
        for (int c = 0; c<MAXCOLS; c++)
            room[r][c] = '#';
    
    design();
    
    opencoord(m_pr, m_pc);
    display();
    
}

Actor* Levels::monsters(int r, int c) const
{
    //serach through monster vector and return the monster
    for (int a = 0; a < m_monsters.size(); a++)
        if (r == m_monsters[a]->row() && c == m_monsters[a]->col())
            return m_monsters[a];
    return NULL;
}

void Levels::display() {
    
    for (int i = 0; i < MAXROWS; i++)
        for (int j = 0; j<MAXCOLS; j++)
            if (room [i][j] != '#' && room[i][j] != ')' && room[i][j]!= '?')
                room[i][j] = ' ';
    
    for (int i = 0; i <m_items.size(); i++)
        room[m_items[i] ->rows()][m_items[i] ->cols()] = m_items[i]->sym();
    
    //display exit or idol
    if (m_level != 4)
        room[m_er][m_ec] = '>';
    else
        room[m_idol.rows()][m_idol.cols()] = '&';
    
    //display the monsters
    for (int i = 0; i < m_monsters.size(); i++)
        room[m_monsters[i]->row()][m_monsters[i]->col()] = m_monsters[i]->rep();
    
    // Indicate player's position
    if (m_player != NULL)
    {
        char& roomChar = room[m_player->row()][m_player->col()];
        if (room[m_player->row()][m_player->col()] != '#')
            roomChar = m_player->rep();
    }
    
    //output the grid
    for (int i = 0; i < MAXROWS; i++)
    {
        for (int j = 0; j < MAXCOLS; j++)
            cout << room[i][j];
        cout << endl;
    }
    
    //output player status
    cout << "Dungeon Level: " << m_level << " Hit points: " <<
    m_player->hp() << " Armor: " << m_player->armor() << " Strength: " <<
    m_player->strength() << " Dexterity: " << m_player->dex() << endl << endl;
}
    
bool Levels:: addplayer() {
    if (m_player != nullptr)
    {
        
        m_player -> newlevel(this, m_pr, m_pc);
        return false;
    }
    
    m_player = new Player(this, m_pr, m_pc);
    return true;
}


bool Levels:: rooms( int &r, int &c) {
    
    bool check = true;
    
    //generate random point and heights and widths
    int rr = 4+randInt(15);
    int cc = 3+randInt(75);
    int w = (randInt(6)) + 5;
    int h = (randInt(6)) + 4;
    r = rr;
    c = cc;
    
    for (int i = (r-h/2)-1; i < (r+h/2); i++)
        for (int j = (c-w/2)-1; j<(c+w/2); j++)
            if (((i >0 && j>0)&& ((i < MAXROWS && j < MAXCOLS)) && room[i][j] != '#') || i<0 || j<0|| i>MAXROWS -1 || j > MAXCOLS -1) {
                
                check = false;
                break;
            }
    if (!check)
        return false;
    else
        for (int i = (r-h/2); i < (r+h/2); i++)
            for (int j = (c-w/2); j<(c+w/2); j++)
                if (i < MAXROWS && j < MAXCOLS)
                    room[i][j] = ' ';
    m_track++;
    return true;
                
}

//CHANGE CHANGE CHANGE CHANGE CHANGE CHANGE CHANGE

void Levels::design()
{
    //making rooms
    //while it doesn't fail 1000 times, and there isn't m_rooms number of rooms
    int a = 0, newr = 0, newc = 0, prevr = 0, prevc = 0;
    bool check = false; // to check if there have been previous rooms
    while (a <= 1000 && m_track != m_rooms)
    {
        if (check)
        {
            prevr = newr;
            prevc = newc;
        }
        
        check = rooms(newr,newc);
        
        //adding corridors
        if (m_track > 1 && check)
        {
            //if prev was below of new
            if (prevr >= newr)
            {
                //if prev was to the right of new
                if (prevc > newc)
                {
                    //go up then left
                    for (int r = prevr; r >= newr; r--)
                        room[r][prevc] = ' ';
                    for (int b = prevc; b > newc; b--)
                        room[newr][b] = ' ';
                }
                //else if prev was to the left of new
                else
                {
                    //go up then right
                    for (int r = prevr; r >= newr; r--)
                        room[r][prevc] = ' ';
                    for (int b = prevc; b < newc; b++)
                        room[newr][b] = ' ';
                }
            }
            //if prev was above new
            else if (prevr < newr)
            {
                //if prev was to the right of new
                if (prevc > newc)
                {
                    //go left then down
                    for (int b = prevc; b >= newc; b--)
                        room[prevr][b] = ' ';
                    for (int r = prevr; r < newr; r++)
                        room[r][newc] = ' ';
                }
                //if prev was to the left of new
                else
                {
                    //go right then down
                    for (int b = prevc; b <= newc; b++)
                        room[prevr][b] = ' ';
                    for (int r = prevr; r < newr; r++)
                        room[r][newc] = ' ';
                }
            }
        }
        if (!check)
            a++;
    }
    
    //if there are enugh rooms
    if (m_track >= m_rooms/2)
    {
        //include 2-3 random items
        int startItems = 2+randInt(2);
        for (int a = 0; a < startItems; a++)
        {
            int q = 0, w = 0;
            opencoord(q, w);
            additem(q, w, randInt(7));
        }
        
        //add monsters
        //int m = 50 + randInt(5*(m_level+1));
        int m = 2 + randInt(5*(m_level+1));
        for (int a = 0; a < m; a++)
        {
            int mon = 0;
            switch (m_level) {
                case 2:
                    mon = 3;
                    break;
                case 3:
                    mon = 4;
                    break;
                default:
                    mon = 2;
                    break;
            }
            addmonster(randInt(mon));
        }
        
        //include the ending spot
        if (m_level != 4)
            //set a coordinate for end spot
            opencoord(m_er, m_ec);
        else 
        {	
            //if it's lvl 4, put the idol down
            int q = 0, w = 0;
            opencoord(q, w);
            Items a(q, w);
            m_idol = a;
        }
    }
}

void Levels::opencoord(int&x, int&y) {
    
    while (room[x][y] != ' ')
    {
        x = randInt(MAXROWS -2) +1;
        y = randInt(MAXCOLS -2) +1;
    }
    
    
}

bool Levels:: correctmove(int r, int c)
{
    //make sure the person is set
    room[m_player->row()][m_player ->col()] = '@';
    
    
    //make sure the monsters aren't there
    for (int i = 0; i < m_monsters.size(); i++)
        if (r == m_monsters[i]->row() && c == m_monsters[i] ->col())
            return false;
    
    //make sure it's not a wall
    if(room[r][c] != ' ' && room[r][c] != ')' &&
       room[r][c] != '?' && room[r][c] != '&' &&
       room[r][c] != '>')
        return false;
    
    return true;
    
}

bool Levels:: iswall(int r, int c) {
    
    if (room[r][c] == '#')
        return true;
    return false;
    
    
}
bool Levels :: moveroom() {
    
    //if it's a > delete the monsters and items
    if (m_player->row() == m_er && m_player ->col() == m_ec)
    {
        for (int i = 0; i < m_items.size() ; i++)
            delete m_items[i];
        for (int i = 0; i < m_monsters.size(); i++)
            delete m_monsters[i];
        return true;
        
        
    }
    return false;
    
}
bool Levels::itemget(string& yes) {
    
    {
        //win the game if u pick up golden idol
        if (m_player->row() == m_idol.rows() && m_player->col() == m_idol.cols())
        {
            cout << "You pick up the golden idol" << endl;
            cout << "Congratulations, you won!" << endl;
            cout << "Press q to exit game." << endl;
            char x;
            
            while (x != 'q') {
                x = getCharacter();
                if (x == 'q')
                    exit(1);
            }
            return true;
        }
        //pick up only if not at max items
        
        if (m_items.size() < MAXITEMS+1)
        {
            for (int i = 0; i < m_items.size(); i++)
            {
                //if your coordinates match with the item's
                if ( m_player->row() == m_items[i]->rows()
                    &&  m_player->col() == m_items[i]->cols())
                {
                    //output
                    yes = "You picked up " + m_items[i]->name();
                    
                    //add to the items and pop from items on map
                    m_player->holdItems(m_items[i]);
                    m_items[i] = m_items[m_items.size()-1];
                    m_items.pop_back();
                }
            }
            return true;
        }
        return false;
    }
    
    
    
}
bool Levels::additem(int r, int c, int x) {
    
    //push items onto the map
    switch (x) {
        case 0:
            m_items.push_back(new Mace(r,c));
            break;
        case 1:
            m_items.push_back(new ShortSword(r,c));
            break;
        case 2:
            m_items.push_back(new LongSword(r,c));
            break;
        case 3:
            m_items.push_back(new Armor(r,c)); // armor scroll
            break;
        case 4:
            m_items.push_back(new Str(r,c)); // str scroll
            break;
        case 5:
            m_items.push_back(new Health(r,c)); // health scroll
            break;
        case 6:
            m_items.push_back(new Dex(r,c)); // dex scroll
            break;
        case 7:
            m_items.push_back(new Tele(r,c)); // teleport scroll
            break;
        case 8:
            m_items.push_back(new Fangs(r,c)); // fangs
            break;
        case 9:
            m_items.push_back(new Axe(r,c)); // fangs
            break;
            
        default:
            break;
    }
    return true;
}

    

bool Levels::addmonster(int x) {
    //put on map at a randomized loc
    int r = 0,  c= 0;
    opencoord(r, c);
    switch (x) {
        case 0:
            m_monsters.push_back(new Snakewomen(this, r,c)); // snakewomen
            break;
        case 1:
            m_monsters.push_back(new Goblin(this, r,c)); // goblin
            break;
        case 2:
            m_monsters.push_back(new Bogeyman(this, r,c)); // bogeyman
            break;
        case 3:
            m_monsters.push_back(new Dragon(this, r,c)); // dragon
            break;
        default:
            break;
    }
    return true;
    
}

//CHANGECHANGECHANGECHANGECHANGE from this point on
bool Levels::checkmonsterdeath() {
    for (vector<Actor*>::iterator p = m_monsters.begin(); p != m_monsters.end(); p++)
    {
        Actor* ptr = *p;
        if (ptr->isdead())
        {
            //erase the monster if he's dead
            ptr->drop(ptr->row(), ptr->col());
            p = m_monsters.erase(p);
            return true;
        }
    }
    return false;
    
}
bool Levels::checkforitem(int r, int c) {
    
    //check to make sure there's no items already there
    for (int a = 0; a < m_items.size(); a++)
    {
        if (m_items[a]->rows() == r
            && m_items[a]->cols() == c)
        {
            //return false if there's an item
            return false;
        }
    }
    // return true if there is no item
    return true;
    
}
bool Levels:: monstersmove(string& yes) {
    
    //bool to see if we need to output a message
    bool hit[m_monsters.size()];
    
    for (int a = 0; a < m_monsters.size(); a++)
    {
        //if he's not sleeping, move, otherwise, reduce counter
        if (!m_monsters[a]->issleep())
            hit[a] = m_monsters[a]->move('p', yes);
        m_monsters[a]->addsleep(-1);
    }
    for (int a = 0; a < m_monsters.size(); a++)
    {
        //if there's at least 1 monster that attacked, output
        if (hit[a] == true)
            return true;
    } 
    return false;
    
    
}
