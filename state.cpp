<<<<<<< HEAD
#include <iostream>
#include <cassert>
#include "state.h"

int State::numStates = 0;

State::State()
{
    numStates ++;
    isFinal = false;
    stateID = numStates;
}

State::State(bool _isFinal)
{
    numStates ++;
    isFinal = _isFinal;
    stateID = numStates;
}

State::State(bool _isFinal, int _stateID)
{
    isFinal = _isFinal;
    stateID = _stateID;
}

State::State(const State& toCopy)
{
    transitions = toCopy.transitions;
    isFinal = toCopy.isFinal;
    stateID = toCopy.stateID;
}

State& State::operator = (const State& toCopy)
{
    if(this == &toCopy)
        return *this;

    transitions = toCopy.transitions;
    isFinal = toCopy.isFinal;
    stateID = toCopy.stateID;

    return *this;

}

bool State::transitionExists(const Transition& check) const
{
    for(int i = 0; i < getNumTransitions(); i++)
    {
        if(transitions[i] == check)
            return true;
    }
    return false;
}

void State::addTransition(char edgeChar, int toConnectID)
{
    if((edgeChar < 'a' || edgeChar > 'z') && (edgeChar < '0' || edgeChar > '9') && edgeChar != 'E')
    {
        std::cout << "NOT CORRECT SYMBOL: " << edgeChar << std::endl;
        return;
    }
    Transition toAdd(edgeChar, toConnectID);
    if(!transitionExists(toAdd))
        transitions.push_back(toAdd);
}

void State::addTransition(const Transition& toAdd)
{
    if(!transitionExists(toAdd))
        transitions.push_back(toAdd);
}

void State::removeTransition(char charEdge, int toConnectID)
{
    for(int i = 0; i < getNumTransitions(); i++)
    {
        if(transitions[i].getSymbol() == charEdge && transitions[i].getDestination() == toConnectID)
        {
            transitions.erase(transitions.begin() + i);
            i --;
        }
    }
}

void State::removeTransition(int index)
{
    assert(index >= 0 && index < getNumTransitions());
    transitions.erase(transitions.begin() + index);
}

bool State::operator == (const State& cmp) const
{
    return stateID == cmp.stateID;
}

bool State::operator < (const State& cmp) const
{
    return stateID < cmp.stateID;
}

int State::getStateID() const
{
    return stateID;
}

bool State::getIsFinal() const
{
    return isFinal;
}

void State::setStateID(int _stateID)
{
    stateID = _stateID;
}

void State::setIsFinal(bool _isFinal)
{
    isFinal = _isFinal;
}

int State::getNumTransitions() const
{
    return transitions.size();
}

Transition& State::getTransition(int idx)
{
    assert(idx < transitions.size());
    return transitions[idx];
}

void State::printTransitions() const
{
    for(Transition curr : transitions)
    {
        std::cout << stateID << " ";
        curr.print();
        std::cout << "\n";
    }
}

bool State::isDetermined()
{
    bool hasOccured[200];

    for(int i = 0; i < 200; i++)
        hasOccured[i] = 0;

    for(Transition tr : transitions)
    {
        if(tr.isEpsilon() == true)
            return false;

        char sym = tr.getSymbol();

        if(hasOccured[sym])
            return false;

        hasOccured[sym] = true;
    }

    return true;
}





=======
#include <iostream>
#include <cassert>
#include "state.h"

State::State()
{
    isFinal = false;
    stateID = 0;
}

State::State(bool _isFinal)
{
    isFinal = _isFinal;
    stateID = 0;
}

State::State(bool _isFinal, int _stateID)
{
    isFinal = _isFinal;
    stateID = _stateID;
}

State::State(const State& toCopy)
{
    transitions = toCopy.transitions;
    isFinal = toCopy.isFinal;
    stateID = toCopy.stateID;
}

State& State::operator = (const State& toCopy)
{
    if(this == &toCopy)
        return *this;

    transitions = toCopy.transitions;
    isFinal = toCopy.isFinal;
    stateID = toCopy.stateID;

    return *this;

}

bool State::transitionExists(const Transition& check) const
{
    for(int i = 0; i < getNumTransitions(); i++)
    {
        if(transitions[i] == check)
            return true;
    }
    return false;
}

void State::addTransition(char edgeChar, int toConnectID)
{
    if((edgeChar < 'a' || edgeChar > 'z') && (edgeChar < '0' || edgeChar > '9') && edgeChar != 'E')
    {
        std::cout << "NOT CORRECT SYMBOL: " << edgeChar << std::endl;
        return;
    }
    Transition toAdd(edgeChar, toConnectID);
    if(!transitionExists(toAdd))
        transitions.push_back(toAdd);
}

void State::addTransition(const Transition& toAdd)
{
    if(!transitionExists(toAdd))
        transitions.push_back(toAdd);
}

void State::removeTransition(char charEdge, int toConnectID)
{
    for(int i = 0; i < getNumTransitions(); i++)
    {
        if(transitions[i].getSymbol() == charEdge && transitions[i].getDestination() == toConnectID)
        {
            transitions.erase(transitions.begin() + i);
            i --;
        }
    }
}

void State::removeTransition(int index)
{
    assert(index >= 0 && index < getNumTransitions());
    transitions.erase(transitions.begin() + index);
}

bool State::operator == (const State& cmp) const
{
    return stateID == cmp.stateID;
}

bool State::operator < (const State& cmp) const
{
    return stateID < cmp.stateID;
}

int State::getStateID() const
{
    return stateID;
}

bool State::getIsFinal() const
{
    return isFinal;
}

void State::setStateID(int _stateID)
{
    stateID = _stateID;
}

void State::setIsFinal(bool _isFinal)
{
    isFinal = _isFinal;
}

int State::getNumTransitions() const
{
    return transitions.size();
}

Transition& State::getTransition(int idx)
{
    assert(idx < transitions.size());
    return transitions[idx];
}

void State::printTransitions() const
{
    for(Transition curr : transitions)
    {
        std::cout << stateID << " ";
        curr.print();
        std::cout << "\n";
    }
}

bool State::isDetermined()
{
    bool hasOccured[200];

    for(int i = 0; i < 200; i++)
        hasOccured[i] = 0;

    for(Transition tr : transitions)
    {
        if(tr.isEpsilon() == true)
            return false;

        char sym = tr.getSymbol();

        if(hasOccured[sym])
            return false;

        hasOccured[sym] = true;
    }

    return true;
}





>>>>>>> yeah
