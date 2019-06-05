<<<<<<< HEAD
#ifndef __TRANSITION_H
#define __TRANSITION_H

class State;

class Transition
{
private:

    char symbol;
    int destinationID;

public:

    Transition();

    Transition(char _symbol, int _destinationID);

    Transition(const Transition& toCopy);

    Transition& operator = (const Transition& toCopy);

    bool operator == (const Transition& cmp) const;

    int getDestination() const;

    void setDestination(int);

    char getSymbol() const;

    void print() const;

    bool isEpsilon() const;

};


#endif // TRANSITION_H_INCLUDED
=======
#ifndef __TRANSITION_H
#define __TRANSITION_H

class State;

class Transition
{
private:

    char symbol;
    int destinationID;

public:

    Transition();

    Transition(char _symbol, int _destinationID);

    Transition(const Transition& toCopy);

    Transition& operator = (const Transition& toCopy);

    bool operator == (const Transition& cmp) const;

    int getDestination() const;

    void setDestination(int);

    char getSymbol() const;

    void print() const;

    bool isEpsilon() const;

};


#endif // TRANSITION_H_INCLUDED
>>>>>>> yeah
