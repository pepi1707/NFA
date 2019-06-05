<<<<<<< HEAD
#include <iostream>
#include "automaton.h"

using namespace std;

int main()
{
    Automaton a;
    a.openFromFile("automatas/automata1.txt");
    a.printTransitions();

    cout << a.determined() << endl;
    cout << a.isEmpty() << endl;

    a.writeInFile("automatas/automata2.txt");

    a.removeUnreachableStates();

    a.writeInFile("automatas/automata2_reachable.txt");

    Automaton b = a.Union(a);
    b.writeInFile("automatas/automata3.txt");

    Automaton con = a.Concat(a);
    con.writeInFile("automatas/automata_concat.txt");

    cout << "is aba recognized?: " << a.recognizeWord(a.getStartState(), "aba", 0) << "\n";

    cout << "is bab recognized?: " << a.recognizeWord(a.getStartState(), "bab", 0) << "\n";

    Automaton un = a.positiveClosure();
    un.writeInFile("automatas/automata_posClos.txt");

    Automaton automatonForA = automatonForSymbol('a');
    automatonForA.writeInFile("automatas/automatonForA.txt");

    Automaton automatonClosure = a.Closure();
    automatonClosure.writeInFile("automatas/automatonClosure.txt");

    automatonClosure.removeUnreachableStates();
    automatonClosure.normalize();
    automatonClosure.writeInFile("automatas/automatonClosureReachable.txt");

    automatonClosure.removeEpsilonTransitions();
    automatonClosure.writeInFile("automatas/automatonClosureNoEps.txt");

    Automaton automatonRegex = Regex("(a+b).c");
    automatonRegex.writeInFile("automatas/automatonRegex.txt");

    automatonRegex.removeEpsilonTransitions();
    automatonRegex.writeInFile("automatas/automatonRegexNoEps.txt");

    automatonRegex.removeUnreachableStates();
    automatonRegex.normalize();
    automatonRegex.writeInFile("automatas/automatonRegexNorm.txt");



	return 0;
}
=======
#include <iostream>
#include "automaton.h"
#include <cstring>

using namespace std;


int main()
{
    bool isClosed = false;
    vector<Automaton> automata;
    while(!isClosed)
    {

        string command;
        cin >> command;

        if(command == "exit")
        {
            isClosed = true;
            continue;
        }

        if(command == "open")
        {
            char filepath[256];
            cin >> filepath;
            automata.push_back(Automaton());

            automata[automata.size() - 1].openFromFile(filepath);
            automata[automata.size() - 1].setAutomatonID(automata.size() - 1);

            continue;

        }

        if(command == "list")
        {
            for(int i = 0; i < automata.size(); i++)
            {
                cout << automata[i].getAutomatonID() << " ";
            }
            cout << endl;
            continue;
        }

        if(command == "print")
        {
            int automatonID;
            cin >> automatonID;

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata[automatonID].printTransitions();

            continue;
        }

        if(command == "save")
        {
            int automatonID;
            char filepath[256];

            cin >> automatonID >> filepath;

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata[automatonID].writeInFile(filepath);

            continue;
        }

        if(command == "empty")
        {
            int automatonID;
            cin >> automatonID;

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            if(automata[automatonID].isEmpty())
            {
                cout << "the automaton is empty\n";
            }
            else
            {
                cout << "the automaton is not empty\n";
            }

            continue;
        }

        if(command == "deterministic")
        {
            int automatonID;
            cin >> automatonID;

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            if(automata[automatonID].determined())
            {
                cout << "the automaton is deterministic\n";
            }
            else
            {
                cout << "the automaton is not deterministic\n";
            }

            continue;
        }

        if(command == "recognize")
        {
            int automatonID;
            char word[256];

            cin >> automatonID >> word;

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata[automatonID].removeEpsilonTransitions();

            automata[automatonID].normalize();

            if(automata[automatonID].recognizeWord(automata[automatonID].getStartState(), word, 0))
            {
                cout << "the word is recognized\n";
            }
            else
            {
                cout << "the word is not recognized\n";
            }

            continue;
        }

        if(command == "union")
        {
            int automatonID1, automatonID2;
            cin >> automatonID1 >> automatonID2;

            if(automatonID1 < 0 || automatonID1 >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            if(automatonID2 < 0 || automatonID2 >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata.push_back(automata[automatonID1].Union(automata[automatonID2]));

            automata[automata.size() - 1].setAutomatonID(automata.size() - 1);

            cout << automata[automata.size() - 1].getAutomatonID() << endl;

            continue;
        }

        if(command == "concat")
        {
            int automatonID1, automatonID2;
            cin >> automatonID1 >> automatonID2;

            if(automatonID1 < 0 || automatonID1 >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            if(automatonID2 < 0 || automatonID2 >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata.push_back(automata[automatonID1].Concat(automata[automatonID2]));

            automata[automata.size() - 1].setAutomatonID(automata.size() - 1);

            cout << automata[automata.size() - 1].getAutomatonID() << endl;

            continue;
        }

        if(command == "union")
        {
            int automatonID;
            cin >> automatonID;

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata.push_back(automata[automatonID].positiveClosure());

            automata[automata.size() - 1].setAutomatonID(automata.size() - 1);

            cout << automata[automata.size() - 1].getAutomatonID() << endl;

            continue;
        }

        if(command == "regex")
        {
            char _regex[256];
            cin >> _regex;

            automata.push_back(Regex(_regex));

            automata[automata.size() - 1].setAutomatonID(automata.size() - 1);

            cout << automata[automata.size() - 1].getAutomatonID() << endl;

            continue;
        }

        if(command == "determine")
        {
            int automatonID;
            cin >> automatonID;

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata[automatonID].determine();

            continue;
        }

        cout << "Invalid command\n";

    }


























    /*
    Automaton a;
    a.openFromFile("automatas/automata1.txt");
    a.printTransitions();

    cout << a.determined() << endl;
    cout << a.isEmpty() << endl;

    a.writeInFile("automatas/automata2.txt");

    a.removeUnreachableStates();

    a.writeInFile("automatas/automata2_reachable.txt");

    Automaton b = a.Union(a);
    b.writeInFile("automatas/automata3.txt");

    Automaton con = a.Concat(a);
    con.writeInFile("automatas/automata_concat.txt");

    cout << "is aba recognized?: " << a.recognizeWord(a.getStartState(), "aba", 0) << "\n";

    cout << "is bab recognized?: " << a.recognizeWord(a.getStartState(), "bab", 0) << "\n";

    Automaton un = a.positiveClosure();
    un.writeInFile("automatas/automata_posClos.txt");

    Automaton automatonForA = automatonForSymbol('a');
    automatonForA.writeInFile("automatas/automatonForA.txt");

    Automaton automatonClosure = a.Closure();
    automatonClosure.writeInFile("automatas/automatonClosure.txt");

    automatonClosure.removeUnreachableStates();
    automatonClosure.normalize();
    automatonClosure.writeInFile("automatas/automatonClosureReachable.txt");

    automatonClosure.removeEpsilonTransitions();
    automatonClosure.writeInFile("automatas/automatonClosureNoEps.txt");

    Automaton automatonRegex = Regex("(a+b).c");
    automatonRegex.writeInFile("automatas/automatonRegex.txt");

    automatonRegex.removeEpsilonTransitions();
    automatonRegex.writeInFile("automatas/automatonRegexNoEps.txt");

    automatonRegex.removeUnreachableStates();
    automatonRegex.normalize();
    automatonRegex.writeInFile("automatas/automatonRegexNorm.txt");*/



	return 0;
}
>>>>>>> yeah
