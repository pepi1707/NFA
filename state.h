#ifndef __STATE_H
#define __STATE_H

#include <vector>
#include <fstream>
#include <iostream>
#include "transition.h"

class State
{

private:

    bool isFinal;

    std::vector<Transition> transitions;
    int stateID;
    static int numStates;

public:

    State();

    State(bool _isFinal);

    State(bool _isFinal, int _stateID);

    State(const State& toCopy);

    State& operator = (const State& toCopy);

    bool operator == (const State& cmp) const;

    bool operator < (const State& cmp) const;


    bool transitionExists(const Transition&) const;

    void addTransition(char edgeChar, int toConnectID);

    void addTransition(const Transition& toAdd);

    void removeTransition(char edgeChar, int toConnectID);

    void removeTransition(int index);

    void stateSerialize() const;

    int getStateID() const;

    bool getIsFinal() const;

    void setStateID(int);

    void setIsFinal(bool);

    int getNumTransitions() const;

    void printTransitions() const;

    Transition& getTransition(int idx);

    bool isDetermined();



};


#endif // STATE_H_INCLUDED
