#include "transition.h"
#include <iostream>
#include "state.h"

Transition::Transition()
{
    symbol = 'E';
    destinationID = -1;
}

Transition::Transition(char _symbol, int _destinationID)
{
    symbol = _symbol;
    destinationID = _destinationID;
}

Transition::Transition(const Transition& toCopy)
{
    symbol = toCopy.symbol;
    destinationID = toCopy.destinationID;
}

Transition& Transition::operator = (const Transition& toCopy)
{
    symbol = toCopy.symbol;
    destinationID = toCopy.destinationID;
}

bool Transition::operator == (const Transition& cmp) const
{
    return (symbol == cmp.symbol && destinationID == cmp.destinationID);
}

int Transition::getDestination() const
{
    return destinationID;
}

void Transition::setDestination(int _destinationID)
{
    destinationID = _destinationID;
}

char Transition::getSymbol() const
{
    return symbol;
}

void Transition::print() const
{
    if(destinationID == -1)
        return;
    std::cout << symbol << " " << destinationID;
}

bool Transition::isEpsilon() const
{
    return symbol == 'E';
}
