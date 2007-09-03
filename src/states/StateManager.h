/*=============================================================================
XMOTO

This file is part of XMOTO.

XMOTO is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

XMOTO is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XMOTO; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
=============================================================================*/

#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include "VCommon.h"

  class GameState {
  public:
    GameState(bool drawStateBehind,
	      bool sendInputToStatesBehind,
	      bool updateStatesBehind);
    virtual ~GameState();

    virtual void enter()=0;
    virtual void leave()=0;
    /* called when a new state is pushed or poped on top of the
       current one*/
    virtual void enterAfterPop()=0;
    virtual void leaveAfterPush()=0;

    virtual void update()=0;
    virtual void render()=0;
    virtual void input()=0;

    bool isHide(){
      return m_isHide;
    }
    void setHide(bool isHide){
      m_isHide = isHide;
    }
    bool drawStatesBehind(){
      return m_drawStateBehind;
    }
    bool sendInputToStatesBehind(){
      return m_sendInputToStatesBehind;
    }
    bool updateStatesBehind(){
      return m_updateStatesBehind;
    }

  private:
    bool m_isHide;
    bool m_drawStateBehind;
    bool m_sendInputToStatesBehind;
    bool m_updateStatesBehind;
  };

  class StateManager {
  public:
    StateManager();
    ~StateManager();

    void pushState(GameState* pNewState);
    GameState* popState();
    GameState* enterState(GameState* pNewState);

    void update();
    void render();
    void input();

  private:
    void calculateWhichStateIsRendered();

    std::vector<GameState*> m_statesStack;
  };

#endif