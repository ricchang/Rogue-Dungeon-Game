#include "Game.h"

Game::Game()
:m_currentLvl(0)
{
    // Create level
    m_levels[0] = new Levels();
    // Add player
    m_levels[0]->addplayer();
}

Game::~Game()
{
    for (int a = 0; a < 5 && m_levels[a]!=NULL; a++)
        delete m_levels[a];
}

void Game::play()
{
    Player* p = m_levels[0]->player();
    if (p == NULL)
    {
        m_levels[0]->display();
        return;
    }
    string msg; // string that outputs message
    bool message, compmessage; //booleans to check if there needs to be mesage
    do
    {
        //heal
        p->heal();
        //clear dead monsters
        m_levels[m_currentLvl]->checkmonsterdeath();
        
        //display
        clearScreen();
        m_levels[m_currentLvl]->display();
        
        //if there needs to be a message, output it then erase it
        if (message)
        {
            cout << msg << endl;
            message = false;
        } else if (compmessage)
        {
            cout << msg << endl;
            compmessage = false;
        }
        msg = "";
        
        char move = getCharacter();
        if (!p->issleep())
        {
            switch (move) {
                    
                case 'c': //cheat
                    p->cheat();
                    break;
                case 'g': //pick up an item
                    message = m_levels[m_currentLvl]->itemget(msg);
                    break;
                case 'w': //view/use held weapons
                    message = p->showInvent('w', msg);
                    break;
                case 'r': //view/use held scrolls
                    message = p->showInvent('r', msg);
                    break;
                case 'i': //view inventory
                    message = p->showInvent('i', msg);
                    break;
                case ARROW_LEFT:
                case ARROW_RIGHT:
                case ARROW_UP:
                case ARROW_DOWN:
                    message = p->move(move, msg);
                    break;
                case '>':
                    if(m_levels[m_currentLvl]->moveroom())
                    {
                        m_currentLvl++;
                        m_levels[m_currentLvl] = new Levels(m_currentLvl, p);
                        m_levels[m_currentLvl]->addplayer();
                    }
                    break;
                case 'q':
                    exit(1);
                default:
                    break;
            }
        }
        p->addsleep(-1);
        
        //make the computer's move
        compmessage = m_levels[m_currentLvl]->monstersmove(msg);
    } 
    while (!m_levels[m_currentLvl]->player()->isdead());
    
    //if you're dead, output it
    clearScreen();
    m_levels[m_currentLvl]->display();
    cout << msg;
    cout << "Press q to exit game. " << endl;
    char a;
    
    while (a != 'q') {
        a = getCharacter();
        if (a == 'q')
            exit(1);
    } 
}