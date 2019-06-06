#include <iostream>
#include "automaton.h"
#include <cstring>

using namespace std;


bool checkBrackets(char *text)
{
    int numBrackets = 0;
    int len = strlen(text);
    for(int i = 0; i < len; i++)
    {
        if(text[i] == '(')
        {
            numBrackets ++;
        }
        if(text[i] == ')')
        {
            numBrackets --;
        }
        if(numBrackets < 0)
            return false;
    }
    return numBrackets == 0;
}

void findWord(char text[], char word[], int& index)
{
    int len = strlen(text);

    int cnt = 0;

    for(; index < len; index++)
    {
        if(text[index] == ' ')
        {
            index ++;
            word[cnt] = '\0';
            return;
        }
        word[cnt] = text[index];
        cnt ++;
    }
    word[cnt] = '\0';
    return;
}

int castToInt(char text[])
{
    int num = -1;
    int len = strlen(text);
    for(int i = 0; i < len; i++)
    {
        if(i == 0)
            num = 0;
        if(text[i] < '0' || text[i] > '9')
        {
            return -1;
        }
        num *= 10;
        num += text[i] - '0';
    }
    return num;
}

int main()
{
    bool isClosed = false;
    vector<Automaton> automata;
    while(!isClosed)
    {

        char commandLine[256];
        cin.getline(commandLine, 256);

        int index = 0;
        char command[256];
        findWord(commandLine, command, index);

        if(!strcmp(command, "exit"))
        {
            isClosed = true;
            continue;
        }

        if(!strcmp(command, "open"))
        {
            char filepath[256];

            findWord(commandLine, filepath, index);

            automata.push_back(Automaton());

            automata[automata.size() - 1].openFromFile(filepath);
            automata[automata.size() - 1].setAutomatonID(automata.size() - 1);

            continue;

        }

        if(!strcmp(command, "list"))
        {
            for(int i = 0; i < automata.size(); i++)
            {
                cout << automata[i].getAutomatonID() << " ";
            }
            cout << endl;
            continue;
        }

        if(!strcmp(command, "print"))
        {
            int automatonID;

            char idChar[256];

            findWord(commandLine, idChar, index);

            automatonID = castToInt(idChar);

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata[automatonID].printTransitions();

            continue;
        }

        if(!strcmp(command, "save"))
        {
            int automatonID;
            char filepath[256];
            char idChar[256];

            findWord(commandLine, idChar, index);

            findWord(commandLine, filepath, index);

            automatonID = castToInt(idChar);

            if(automatonID < 0 || automatonID >= automata.size())
            {
                cout << "no such automaton\n";
                continue;
            }

            automata[automatonID].writeInFile(filepath);

            continue;
        }

        if(!strcmp(command, "empty"))
        {
            int automatonID;
            char idChar[256];

            findWord(commandLine, idChar, index);
            automatonID = castToInt(idChar);

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

        if(!strcmp(command, "deterministic"))
        {
            int automatonID;
            char idChar[256];

            findWord(commandLine, idChar, index);
            automatonID = castToInt(idChar);

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

        if(!strcmp(command, "recognize"))
        {
            int automatonID;
            char word[256];
            char idChar[256];

            findWord(commandLine, idChar, index);
            findWord(commandLine, word, index);

            automatonID = castToInt(idChar);

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

        if(!strcmp(command, "union"))
        {
            int automatonID1, automatonID2;

            char idChar1[256], idChar2[256];

            findWord(commandLine, idChar1, index);
            findWord(commandLine, idChar2, index);

            automatonID1 = castToInt(idChar1);
            automatonID2 = castToInt(idChar2);

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

        if(!strcmp(command, "concat"))
        {
            int automatonID1, automatonID2;
            char idChar1[256], idChar2[256];

            findWord(commandLine, idChar1, index);
            findWord(commandLine, idChar2, index);

            automatonID1 = castToInt(idChar1);
            automatonID2 = castToInt(idChar2);

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

        if(!strcmp(command, "un"))
        {
            int automatonID;
            char idChar[256];
            findWord(commandLine, idChar, index);
            automatonID = castToInt(idChar);

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

        if(!strcmp(command, "regex"))
        {
            char _regex[256];
            findWord(commandLine, _regex, index);

            if(!checkBrackets(_regex))
            {
                cout << "Invalid regex\n";
                continue;
            }

            automata.push_back(Regex(_regex));

            automata[automata.size() - 1].setAutomatonID(automata.size() - 1);

            cout << automata[automata.size() - 1].getAutomatonID() << endl;

            continue;
        }

        if(!strcmp(command, "determine"))
        {
            int automatonID;
            char idChar[256];
            findWord(commandLine, idChar, index);
            automatonID = castToInt(idChar);

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
