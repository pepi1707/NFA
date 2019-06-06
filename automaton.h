#ifndef __AUTOMATON_H
#define __AUTOMATON_H

#include <vector>
#include "state.h"

class Automaton
{

private:

    std::vector<State> states;
    int startState;
    int automatonID;

public:

    Automaton();

    Automaton(const Automaton& toCopy);

    Automaton& operator = (const Automaton& toCopy);

    int getStartState() const;

    void setStartState(int);

    int getAutomatonID() const;

    void setAutomatonID(int);

    void setStateIsFinal(int stateIndex, bool _isFinal);

    void addTransition(int startID, char symbol, int destinationID);

    void addTransition(int startId, const Transition& toAdd);

    void addState(const State& toAdd);

    State getStateOfID(const int) const;

    int getNumStates() const;

    std::vector<State> getStates() const;

    int getIndexOfState(int) const;

    int getNumTransitions() const;

    void setStates(const std::vector<State>&);

    void sortStates(int, int);

    void openFromFile(char fileName[]);

    void writeInFile(char fileName[]);

    void printTransitions() const;

    bool determined() const;

    int maxStateID() const;

    void normalize();

    Automaton operator + (Automaton toMerge) const;

    void findEpsilons(State &startState, int curState, bool *used, bool &toBeFinal);

    void removeEpsilonTransitions();

    Automaton Union(const Automaton&) const;

    void dfsReachAll(int, bool*);

    void removeUnreachableStates();

    bool isEmpty();

    Automaton Concat(const Automaton&) const;

    bool recognizeWord(int curState, const char* word, int wordIndex);

    Automaton positiveClosure() const;

    Automaton Closure() const;

    void determine();

};

Automaton automatonForSymbol(char);

Automaton Regex(const char* regexText);

Automaton findAutomatonForRegex(int, int, const char*);


#endif // __AUTOMATON_H

