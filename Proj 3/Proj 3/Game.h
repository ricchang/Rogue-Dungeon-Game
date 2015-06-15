//
//  Game.h
//  Proj 3
//
//  Created by Eric Chang on 5/26/15.
//  Copyright (c) 2015 Eric Chang. All rights reserved.
//

#ifndef __Proj_3__Game__
#define __Proj_3__Game__

#include "utilities.h"
#include "Levels.h"
#include "Actors.h"

class Game
{
public:
    // Constructor/destructor
    Game();
    ~Game();
    
    // Mutators
    void play();
    
private:
    Levels* m_levels[5];
    int m_currentLvl;
    
    int decodeDirection(char dir) const;
};

#endif /* defined(__Proj_3__Game__) */
