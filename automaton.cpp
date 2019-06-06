#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>
#include "automaton.h"

using namespace std;

Automaton::Automaton()
{
    startState = 0;
    automatonID = 0;
}

Automaton::Automaton(const Automaton& toCopy)
{
    states = toCopy.states;
    startState = toCopy.startState;
    automatonID = toCopy.automatonID;
}

Automaton& Automaton::operator = (const Automaton& toCopy)
{
    states = toCopy.states;
    startState = toCopy.startState;
    automatonID = toCopy.automatonID;
}

int Automaton::getStartState() const
{
    return startState;
}

void Automaton::setStartState(int _startState)
{
    startState = _startState;
}

int Automaton::getAutomatonID() const
{
    return automatonID;
}

void Automaton::setAutomatonID(int _automatonID)
{
    automatonID = _automatonID;
}

void Automaton::setStateIsFinal(int stateIndex, bool _isFinal)
{
    assert(stateIndex >= 0 && stateIndex < states.size());
    states[stateIndex].setIsFinal(_isFinal);
}

void Automaton::addTransition(int startID, char symbol, int destinationID)
{
    for(int i = 0; i < states.size(); i++)
    {
        if(states[i].getStateID() == startID)
        {
            states[i].addTransition(symbol, destinationID);
            break;
        }
    }
}

void Automaton::addTransition(int startID, const Transition& toAdd)
{
    for(int i = 0; i < states.size(); i++)
    {
        if(states[i].getStateID() == startID)
        {
            states[i].addTransition(toAdd);
            break;
        }
    }
}

void Automaton::addState(const State& toAdd)
{
    states.push_back(toAdd);
}

State Automaton::getStateOfID(const int _stateID) const
{
    for(int i = 0; i < states.size(); i++)
    {
        if(states[i].getStateID() == _stateID)
            return states[i];
    }
}

int Automaton::getNumStates() const
{
    return states.size();
}

std::vector<State> Automaton::getStates() const
{
    return states;
}

void Automaton::setStates(const std::vector<State>& _states)
{
    states = _states;
}

void Automaton::sortStates(int startIndex, int length)
{
    if(length <= 1)
        return;

    int cnt = 0;
    for(int i = 1; i < length; i++)
    {
        if(states[startIndex + i] < states[startIndex + cnt])
        {
            std::swap(states[i], states[startIndex + cnt]);
            cnt ++;
        }
    }
    sortStates(startIndex, cnt);
    sortStates(startIndex + cnt + 1, length - cnt - 1);
}

int Automaton::getIndexOfState(int _stateId) const
{
    for(size_t i = 0; i < states.size(); i++)
    {
        if(states[i].getStateID() == _stateId)
            return i;
    }
    std::cout << "No such state found.\n";
    return -1;
}

int Automaton::getNumTransitions() const
{
    int numTransitions = 0;
    for(State st : states)
    {
        numTransitions += st.getNumTransitions();
    }
    return numTransitions;
}

bool Automaton::openFromFile(char fileName[])
{
    std::ifstream fileInput(fileName);

    if(fileInput.fail())
    {
        cout << "File doesn't exist or you have no permission for it\n";
        return 0;
    }

    int numStates;

    fileInput >> numStates;

    fileInput >> startState;

    automatonID = 0;

    int numTransitions;
    bool _isFinal;
    int startID, destinationID;
    char _symbol;

    states.clear();
    states.resize(numStates);

    for(int i = 0; i < numStates; i++)
    {
        fileInput >> _isFinal;
        states[i].setStateID(i);
        states[i].setIsFinal(_isFinal);
    }

    fileInput >> numTransitions;

    for(int i = 0; i < numTransitions; i++)
    {
        fileInput >> startID;
        fileInput >> _symbol;
        fileInput >> destinationID;

        if(_symbol == 'E')
        {
            states[ startID ].addTransition('E', destinationID );
        }
        else
        {
            states[ startID ].addTransition(_symbol, destinationID );
        }
    }

    fileInput.close();

    return 1;
}

void Automaton::writeInFile(char fileName[])
{
    this->sortStates(0, states.size());

    std::ofstream fileOutput(fileName);

    fileOutput << states.size() << " " << startState << "\n";

    for(State st : states)
    {
        fileOutput << st.getIsFinal() << " ";
    }
    fileOutput << "\n";

    fileOutput << getNumTransitions() << "\n";

    for(State st : states)
    {
        int stateNumTransitions = st.getNumTransitions();

        for(int i = 0; i < stateNumTransitions; i++)
        {
            if(st.getTransition(i).getSymbol() != 'E')
            {
                fileOutput << st.getStateID() << " " << st.getTransition(i).getSymbol() << " " << st.getTransition(i).getDestination() << "\n";
            }
            else
            {
                fileOutput << st.getStateID() << " " << "E" << " " << st.getTransition(i).getDestination() << "\n";
            }
        }
    }

    fileOutput.close();

}

bool Automaton::determined() const
{
    for(State st : states)
    {
        if(!st.isDetermined())
            return false;
    }
    return true;
}

void Automaton::printTransitions() const
{
    for(State st : states)
    {
        st.printTransitions();
    }
}

int Automaton::maxStateID() const
{
    int ans = -1;
    for(State st : states)
    {
        if(st.getStateID() > ans)
            ans = st.getStateID();
    }
    return ans;
}

///making the automaton such that states[i].stateID = i
void Automaton::normalize()
{
    this->sortStates(0, states.size());
    int* newIndex = new int[states[states.size() - 1].getStateID() + 1];

    for(int i = 0; i < states.size(); i++)
    {
        newIndex[states[i].getStateID()] = i;
        states[i].setStateID(i);
    }

    startState = newIndex[startState];

    for(int i = 0; i < states.size(); i++)
    {
        int numTrans = states[i].getNumTransitions();
        for(int j = 0; j < numTrans; j++)
        {
            states[i].getTransition(j).setDestination(newIndex[states[i].getTransition(j).getDestination()]);
        }


        ///remove duplicate transitions;
        for(int j = 0; j < states[i].getNumTransitions(); j ++)
        {
            for(int l = 0; l < j; l++)
            {
                if(states[i].getTransition(j) == states[i].getTransition(l))
                {
                    states[i].removeTransition(j);
                    j --;
                    break;
                }
            }
        }
    }

    delete[] newIndex;
}

///returning an automaton such that is the combined states and transitions of both automatons
Automaton Automaton::operator + (Automaton toMerge) const
{
    Automaton automatonMerge = *this;

    automatonMerge.normalize();

    toMerge.normalize();

    int toAdd = automatonMerge.states[states.size() - 1].getStateID() + 1;

    std::vector<State> toMergeStates = toMerge.getStates();

    for(int i = 0; i < toMergeStates.size(); i++)
    {
        toMergeStates[i].setStateID(toMergeStates[i].getStateID() + toAdd);

        int numTrans = toMergeStates[i].getNumTransitions();

        for(int j = 0; j < numTrans; j++)
        {
            toMergeStates[i].getTransition(j).setDestination(toMergeStates[i].getTransition(j).getDestination() + toAdd);
        }

        automatonMerge.addState(toMergeStates[i]);
    }

    return automatonMerge;
}

void Automaton::findEpsilons(State &startState, int curState, bool *used, bool &toBeFinal)
{
    if(used[curState])
        return;

    if(states[curState].getIsFinal())
    {
        toBeFinal = true;
    }
    used[curState] = true;
    int numTrans = states[curState].getNumTransitions();
    for(int i = 0; i < numTrans; i++)
    {

        if(!states[curState].getTransition(i).isEpsilon())
        {
            startState.addTransition(states[curState].getTransition(i));
        }
        else
        {
            int neighbour = states[curState].getTransition(i).getDestination();
            findEpsilons(startState, neighbour, used, toBeFinal);
        }

    }
}

void Automaton::removeEpsilonTransitions()
{
    ///replace epsilons

    for(int i = 0; i < states.size(); i++)
    {
        bool *used = new bool[states.size()];

        for(int j = 0; j < states.size(); j++)
            used[j] = false;

        bool toBeFinal = false;

        this->findEpsilons(states[i], i, used, toBeFinal);

        states[i].setIsFinal(toBeFinal);

        delete[] used;
    }

    ///remove epsilons
    for(int i = 0; i < states.size(); i++)
    {
        for(int j = 0; j < states[i].getNumTransitions(); j++)
        {
            if(states[i].getTransition(j).isEpsilon())
            {
                ///std::cout << "deleted duplicated " << j << "-th transitions of " << i << "-th state\n";
                states[i].removeTransition(j);
                j--;
            }
        }
    }
}

Automaton Automaton::Union(const Automaton& toMerge) const
{

    Automaton automatonUnion = *this + toMerge;

    bool _isFinal = this->getStateOfID(this->getStartState()).getIsFinal()
                    || toMerge.getStateOfID(toMerge.getStartState()).getIsFinal();

    automatonUnion.addState(State(_isFinal, this->getNumStates() + toMerge.getNumStates()));

    automatonUnion.setStartState(this->getNumStates() + toMerge.getNumStates());

    int start1 = this->getStartState();

    int start2 = this->getNumStates() + toMerge.getStartState();

    std::vector<State> unionStates = automatonUnion.getStates();

    for(int i = 0; i < unionStates.size(); i++)
    {
        if(i != start1 && i !=start2)
            continue;

        int numTrans = unionStates[i].getNumTransitions();

        for(int j = 0; j < numTrans; j++)
        {
            automatonUnion.addTransition(automatonUnion.getStartState(), unionStates[i].getTransition(j));
        }
    }

    automatonUnion.removeUnreachableStates();

    return automatonUnion;
}

void Automaton::dfsReachAll(int curState, bool *isReachable)
{
    isReachable[curState] = true;

    int numTrans = states[curState].getNumTransitions();

    for(int i = 0; i < numTrans; i++)
    {
        int neighbour = states[curState].getTransition(i).getDestination();
        if(!isReachable[neighbour])
        {
            dfsReachAll(neighbour, isReachable);
        }
    }

    return;

}

void Automaton::removeUnreachableStates()
{
    bool* isReachable = new bool[states.size()];
    for(int i = 0 ; i < states.size(); i++)
        isReachable[i] = false;

    dfsReachAll(startState, isReachable);

    for(int i = 0 ; i < states.size(); i++)
    {
        if(!isReachable[states[i].getStateID()])
        {
            states.erase(states.begin() + i);
            i --;
        }
    }

    delete[] isReachable;
    normalize();
}

bool Automaton::isEmpty()
{
    removeUnreachableStates();

    for(int i = 0; i < states.size(); i++)
    {
        if(states[i].getIsFinal())
            return false;
    }
    return true;

}

Automaton Automaton::Concat(const Automaton& toConcat) const
{
    Automaton automatonConcat = *this + toConcat;

    for(int i = 0 ; i < states.size(); i++)
    {
        if(states[i].getIsFinal())
        {
            automatonConcat.setStateIsFinal(i, 0);
            automatonConcat.addTransition(states[i].getStateID(), 'E', this->getNumStates() + toConcat.getStartState());
        }
    }

    automatonConcat.removeUnreachableStates();

    return automatonConcat;
}


bool Automaton::recognizeWord(int curState, const char* word, int wordIndex)
{
    if(strlen(word) == wordIndex)
    {
        return states[curState].getIsFinal();
    }

    int numTrans = states[curState].getNumTransitions();

    for(int i = 0; i < numTrans; i++)
    {
        if(word[wordIndex] == states[curState].getTransition(i).getSymbol())
        {
            if(recognizeWord(states[curState].getTransition(i).getDestination(), word, wordIndex + 1))
                return true;
        }
    }
    return false;
}

Automaton automatonForSymbol(char symbol)
{
    Automaton automatonSymbol;

    automatonSymbol.setStartState(0);
    if(symbol == 'E')
    {
        State startState(1,0);
        automatonSymbol.addState(startState);
        return automatonSymbol;
    }

    State startState(0,0);

    startState.addTransition(symbol, 1);
    State endState(1,1);

    automatonSymbol.addState(startState);
    automatonSymbol.addState(endState);

    return automatonSymbol;
}

Automaton Automaton::positiveClosure() const
{
    Automaton automatonUn = *this;
    for(int i = 0; i < states.size(); i++)
    {
        if(states[i].getIsFinal())
        {
            automatonUn.addTransition(i, 'E', startState);
        }
    }

    automatonUn.removeUnreachableStates();

    return automatonUn;
}

Automaton Automaton::Closure() const
{
    return positiveClosure().Union(automatonForSymbol('E'));
}

Automaton findAutomatonForRegex(int leftBorder, int rightBorder, const char* regexText)
{
    if(leftBorder == rightBorder)
    {
        return automatonForSymbol(regexText[leftBorder]);
    }

    int cntOpens = 0;
    int ended = -1;
    for(int i = leftBorder; i <= rightBorder; i++)
    {
        if(regexText[i] == '(')
        {
            cntOpens ++;
        }
        if(regexText[i] == ')')
        {
            cntOpens --;
        }
        if(!cntOpens)
        {
            ended = i;
            break;
        }
    }

    if(ended == rightBorder)
    {
        return findAutomatonForRegex(leftBorder + 1, rightBorder - 1, regexText);
    }

    int newLeft = ended + 1;
    for( ; newLeft < rightBorder; newLeft ++)
    {
        if(regexText[newLeft] != '*')
            break;
    }

    Automaton left;
    if(leftBorder == ended)
    {
        left = automatonForSymbol(regexText[leftBorder]);
    }
    else
    {
        left = findAutomatonForRegex(leftBorder + 1, ended - 1, regexText);
    }

    if(regexText[newLeft] == '*')
    {
        left = left.Closure();
    }

    if(newLeft != rightBorder)
    {
        Automaton right = findAutomatonForRegex(newLeft + 1, rightBorder, regexText);

        if(regexText[newLeft] == '+')
            return left.Union(right);
        if(regexText[newLeft] == '.')
            return left.Concat(right);
    }
    else
    {
        return left;
    }
}

Automaton Regex(const char* regexText)
{
    int sz = strlen(regexText);

    return findAutomatonForRegex(0, sz - 1, regexText);
}

void genPowerSet(int curIndex, int numStates, vector<vector<int> > &powerSetStates, vector<int>& curSet)
{
    if(curIndex == numStates)
    {
        if(powerSetStates.size() < (1<<numStates) - 1)
        {
            powerSetStates.push_back(curSet);
        }
        return;
    }

    curSet.push_back(curIndex);
    genPowerSet(curIndex + 1, numStates, powerSetStates, curSet);
    curSet.erase(curSet.begin() + curSet.size() - 1);
    genPowerSet(curIndex + 1, numStates, powerSetStates, curSet);

}

void Automaton::determine()
{
    if(determined() == true)
        return;

    removeEpsilonTransitions();
    removeUnreachableStates();

    vector<vector<int> > powerSetStates;
    vector<int> curSet;
    genPowerSet(0, getNumStates(), powerSetStates, curSet);

    assert(powerSetStates.size() == (1<<(getNumStates())) - 1);

    vector<State> determinedStates;
    for(int i = 0; i < powerSetStates.size(); i++)
    {
        bool _isFinal = false;
        for(int j = 0; j < powerSetStates[i].size(); j++)
        {
            if(states[powerSetStates[i][j]].getIsFinal() == true)
            {
                _isFinal = true;
                break;
            }
        }
        determinedStates.push_back(State(_isFinal, i));
    }

    for(int i = 0; i < powerSetStates.size(); i++)
    {
        for(int k = 0; k < 36; k++)
        {
            vector<int> neighbour;
            char symbol = 'a' + k;
            if(k >= 26)
            {
                symbol = '0' + (k - 26);
            }
            for(int j = 0; j < powerSetStates[i].size(); j++)
            {
                for(int l = 0; l < states[powerSetStates[i][j]].getNumTransitions(); l++)
                {
                    Transition curTrans = states[powerSetStates[i][j]].getTransition(l);
                    if(curTrans.getSymbol() == symbol)
                    {
                        neighbour.push_back(curTrans.getDestination());
                    }
                }
            }
            sort(neighbour.begin(), neighbour.end());
            neighbour.push_back(-1);
            vector<int> realNeighbour;
            for(int j = 0; j < neighbour.size() - 1; j++)
            {
                if(neighbour[j] != neighbour[j + 1])
                {
                    realNeighbour.push_back(neighbour[j]);
                }
            }
            for(int j = 0; j < powerSetStates.size(); j++)
            {
                if(realNeighbour.size() != powerSetStates[j].size())
                    continue;
                bool found = 1;
                for(int l = 0; l < realNeighbour.size(); l++)
                {
                    if(realNeighbour[l] != powerSetStates[j][l])
                    {
                        found = false;
                        break;
                    }
                }
                if(!found)
                    continue;
                determinedStates[i].addTransition(symbol, j);
                break;
            }
        }
    }

    int _startState;
    for(int i = 0; i < powerSetStates.size(); i++)
    {
        if(powerSetStates[i].size() == 1 && powerSetStates[i][0] == getStartState())
        {
            _startState = i;
            break;
        }
    }


    setStartState(_startState);
    setStates(determinedStates);

    removeUnreachableStates();

}


