#include <string>
#include <iostream>
#include <stack>
#include <cassert>
#include <cctype>

using namespace std;

bool isInfix(string infix);
bool isLessOrEqualPrec(char curr, char top);
string toPostfix(string infix);
bool toResult(string postfix);

int evaluate(string infix, string& postfix, bool& result)
{
    if (!isInfix(infix))
        return 1;
    postfix = toPostfix(infix);
    result = toResult(postfix);
    return 0;
}

bool toResult(string postfix)
{
    stack<bool> operands;
    for (size_t i = 0; i < postfix.size(); i++)
    {
        if (postfix[i] == 'T')
            operands.push(true);
        else if (postfix[i] == 'F')
            operands.push(false);
        else if (postfix[i] == '!')
        {
            bool operated = operands.top();
            operands.pop();
            operands.push(!operated);
        }
        else
        {
            bool operand2 = operands.top();
            operands.pop();
            bool operand1 = operands.top();
            operands.pop();
            bool operated;
            if (postfix[i] == '&')
                operated = operand1 & operand2;
            else
                operated = operand1 | operand2;
            operands.push(operated);
        }
    }
    return operands.top();
}

string toPostfix(string infix)
{
    string postfix = "";
    stack<char> operators;
    for (size_t i = 0; i < infix.size(); i++)
    {
        switch (infix[i])
        {
            case 'T':
            case 'F':
                postfix += infix[i];
                while (!operators.empty() && operators.top() == '!')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                break;
            case '!':
                operators.push('!');
                break;
            case '(':
                operators.push('(');
                break;
            case ')':
                while (operators.top() != '(')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.pop();
                while (!operators.empty() && operators.top() == '!')
                {
                    postfix += operators.top();
                    operators.pop();
                }
                break;
            case '&':
            case '|':
                while (!operators.empty() && operators.top() != '(' && isLessOrEqualPrec(infix[i], operators.top()))
                {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(infix[i]);
                break;
        }
    }
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    return postfix;
}
    
bool isLessOrEqualPrec(char curr, char top)
{
    if (curr == '!' && (top == '&' || top == '|'))
        return false;
    if (curr == '&' && top == '|')
        return false;
    return true;
}

bool isInfix(string infix)
{
    if (infix == "")
        return false;
    string noSpaces = "";
    int numOfOperands = 0;
    int numOfLeftPar = 0;
    int numOfRightPar = 0;
    for (size_t i = 0; i < infix.size(); i++)
    {
        if (infix[i] == '(')
            numOfLeftPar++;
        else if (infix[i] == ')')
            numOfRightPar++;
        switch (infix[i])
        {
            case 'T':
            case 'F':
                numOfOperands++;
            case '(':
            case ')':
            case '|':
            case '&':
            case '!':
                noSpaces += infix[i];
                break;
            case ' ':
                break;
            default:
                return false;
        }
    }
    if (numOfOperands == 0 || numOfLeftPar != numOfRightPar)
        return false;
    if (noSpaces[0] == '&' || noSpaces[0] == '|' || noSpaces[0] == ')')
        return false;
	size_t lastIndex = noSpaces.size() - 1;
    if (noSpaces[lastIndex] == '|' || noSpaces[lastIndex] == '&' || noSpaces[lastIndex] == '!')
        return false;
    for (size_t i = 1; i < noSpaces.size(); i++)
    {
        switch (noSpaces[i])
        {
            case 'T':
            case 'F':
            case '!':
                switch (noSpaces[i-1])
                {
                    case 'T':
                    case 'F':
                    case ')':
                        return false;
                }
                break;
            case '&':
            case '|':
            case ')':
                switch (noSpaces[i-1])
                {
                    case '(':
                    case '&':
                    case '!':
                    case '|':
                        return false;
                }
                break;
            case '(':
                switch (noSpaces[i-1])
                {
                    case 'T':
                    case 'F':
                    case ')':
                        return false;
                }
                break;
        }
    }
    return true;
}

/*
int main()
{
    string pf;
    bool answer;
    assert(evaluate("t|f", pf, answer) == 1);
    assert(evaluate("T%F", pf, answer) == 1);
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F&  ", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("T!  ", pf, answer) == 1);
    assert(evaluate("T!T", pf, answer) == 1);
    assert(evaluate("F|T& ! ", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("T&(F)", pf, answer) == 0 && pf == "TF&" && !answer);
    assert(evaluate("T & !F", pf, answer) == 0 && pf == "TF!&" && answer);
    assert(evaluate("!(F|T)", pf, answer) == 0 && pf == "FT|!" && !answer);
    assert(evaluate("!F|T", pf, answer) == 0 && pf == "F!T|" && answer);
    assert(evaluate("T|F&F", pf, answer) == 0 && pf == "TFF&|" && answer);
    assert(evaluate("T&!(F|T&T|F)|!!(F&T&F)", pf, answer) == 0 && pf == "TFTT&|F|!&FT&F&!!|" && !answer);
    assert(evaluate("  |T", pf, answer) == 1);
    assert(evaluate("&F", pf, answer) == 1);
    assert(evaluate("   )|T&( ", pf, answer) == 1);
    assert(evaluate(")|T", pf, answer) == 1);
    assert(evaluate(" ) &F", pf, answer) == 1);
    cout << "Passed all tests" << endl;
}
*/