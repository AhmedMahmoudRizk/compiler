//
// Created by yousef on 27/03/18.
//

#include <fstream>
#include "TestProgram.h"
#include "GroupedNFA.h"

void TestProgram::split(string &txt, vector<string> &strs1, char ch) {
    string token;
    stringstream ss(txt);
    while (getline(ss, token, ch)) {
        strs1.push_back(token);
    }
}

string TestProgram::removeWhiteSpaces(string str) {
    vector<string> vector2;
    TestProgram::split(str, vector2, ' ');
    for (int j = 0; j < vector2.size(); j++) {
        char t = vector2[j][0];
        if (!(t <= 32)) {
            return vector2[j];
        }
    }
    return "";
}

string TestProgram::definitionRange(string &str, string &result) {
    vector<string> vector1;
    TestProgram::split(str, vector1, '-');
    vector<string> vector2;
    if (vector1.size() == 1) {
        result = TestProgram::removeWhiteSpaces(vector1[0]);
        return result;
    }
    string startRange, endRange, temp;
    bool check_first_part = true;
    for (int i = 0; i < vector1.size(); i++) {
        temp = TestProgram::removeWhiteSpaces(vector1[i]);
        if (temp == "") {
            continue;
        } else if (check_first_part) {
            check_first_part = false;
            startRange = temp;
        } else
            endRange = temp;
    }
    for (int k = startRange[0]; k <= endRange[0]; k++) {
        char element = k;
        result.push_back(element);
    }
    return result;
}


bool TestProgram::charValid(char &j, string transitionToken) {
    string result;
    if (transitionToken.size() == 1)
        result = transitionToken;
    else
        result = TestProgram::definitionRange(transitionToken, result);
    return result.find(j) != string::npos;
}

bool TestProgram::checkEmptyState() {
    vector<int> Row = TestProgram::dfaTable[currentState];
    for (int i = 0; i < Row.size(); i++) {
        if (Row[i] != currentState)
            return true;
    }
    return false;
}

bool TestProgram::matchPunc(char &i) {
    string test;
    test.push_back(i);
    for (auto j:TestProgram::punctuations) {
        if (test == j)
            return true;
    }
    return false;
}

bool TestProgram::checkTokenKeyword(string token) {
    for (auto it : TestProgram::keyWords) {
        if (it == token) {
            TestProgram::tokens.push_back(it);
            return true;
        }
    }
    return false;
}

void TestProgram::refereToEmptyState(int index, string line) {
    TestProgram::tokens.push_back("Not Matched");
    index++;
    while (line.size() > index && (line[index] == ' ' || line[index] == '\t' || line[index] == '\n'))
        index++;
    curCharIndex = index;
}

int TestProgram::checkChar(char &currChar, int index, int lineSize, string line, string value) {

    vector<int> Row = dfaTable[currentState];
    bool matched = false;
    bool inputFound = true;
    for (int i = 0; i < Row.size(); i++) {
        if (charValid(currChar, GroupedNFA::getInstance()->allInputs[i])) {
            inputFound = false;
            currentState = dfaTable[currentState][i];
            readedStates.push(currentState);

            fromLastAcceptance++;
            bool dfaStateAttr = TestProgram::check_status(currentState);
            if (dfaStateAttr) {
                fromLastAcceptance = 0;
                acceptedStates.push(currentState);
            }
            readedCharsIndex.push(index);
            if (TestProgram::checkEmptyState())
                matched = true;
            else {
                if (value.size() == 0) {
                    TestProgram::refereToEmptyState(index, line);
                    return 2;
                }
            }
            if (index == lineSize - 1 && !dfaStateAttr)
                matched = false;

            break;
        }

    }
    if (inputFound) {
        cout << "Lexical Error in char " << endl;
        cout << currChar << endl;
        exit(1);
    }
    if (!matched) {
        // if char is not matching pop all states readed untill we reach an acceptance state
        while (fromLastAcceptance != 0) {
            readedStates.pop();
            curCharIndex = readedCharsIndex.top(); //store index of last char after acceptance state
            readedCharsIndex.pop();
            fromLastAcceptance--;
        }
        if (acceptedStates.empty()) //if no acceptance came before , this is an Error
        {
            cout << "Error in char " << endl;
            cout << currChar << endl;
            exit(0);
        } else {
            int tos = readedStates.top();
            string lastAcceptedGraphName = dfaStates.find(tos)->second;
            if (lastAcceptedGraphName != "")
                TestProgram::tokens.push_back(lastAcceptedGraphName);
            currentState = 0;
            return 1;
        }
    }
    return 0;

}


void TestProgram::parseLine(string line) {
    cout << line << endl;
    string value;
    vector<string> values;
    int i = 0;
    curCharIndex = 0;
    while (i < line.size()) {
        if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r' || matchPunc(line[i])) {
            bool punMatch = matchPunc(line[i]);
            if (value.size() > 0) {
                if (checkTokenKeyword(value)) {
                    value.clear();
                    if (punMatch) {
                        string temp;
                        temp.push_back(line[i]);
                        TestProgram::tokens.push_back(temp);
                    }
                    currentState = 0;
                    curCharIndex++;
                    i++;
                    continue;
                } else {
                    if (TestProgram::check_status(currentState)) {
                        string lastAcceptedGraphName = dfaStates.find(currentState)->second;
                        if (lastAcceptedGraphName != "")
                            TestProgram::tokens.push_back(lastAcceptedGraphName);
                        if (punMatch) {
                            string temp;
                            temp.push_back(line[i]);
                            TestProgram::tokens.push_back(temp);
                        }
                        curCharIndex++;
                        i++;
                        currentState = 0;
                        value.clear();
                        continue;
                    } else {
                        int checkValidate = checkChar(line[i], i, line.size(), line, value);
                        if (checkValidate == 1) {
                            value.clear();
                            i = curCharIndex;
                            currentState = 0;
                        } else {
                            value.push_back(line[i]);
                            curCharIndex++;
                            i++;
                        }

                    }
                }
            } else {
                if (punMatch) {
                    string temp;
                    temp.push_back(line[i]);
                    TestProgram::tokens.push_back(temp);
                }
                i++;
                curCharIndex++;
            }
        } else {
            int checkValidate = checkChar(line[i], i, line.size(), line, value);
            if (checkValidate == 1) {
                value.clear();
                i = curCharIndex;
                currentState = 0;
            } else {
                value.push_back(line[i]);
                curCharIndex++;
                i++;
                if (i >= line.size() && TestProgram::check_status(currentState)) {
                    string lastAcceptedGraphName = dfaStates.find(currentState)->second;
                    if (lastAcceptedGraphName != "")
                        TestProgram::tokens.push_back(lastAcceptedGraphName);
                }
            }
        }

    }
}

int TestProgram::check_status(int statusIndex) {
    if (dfaStates.find(statusIndex)->second != "")
        return 1;
    return 0;
}


void TestProgram::setData(vector<string> keywords, vector<string> punctuation, vector<vector<int> > dfatable,
                          map<int, string> acceptedState) {
    TestProgram::dfaTable = dfatable;
    TestProgram::keyWords = keywords;
    TestProgram::punctuations = punctuation;
    TestProgram::dfaStates = acceptedState;
}

void TestProgram::printTokens() {
    for (auto token: TestProgram::tokens) {
        cout << "token: " << token << endl;
    }
}


void TestProgram::executeTokensFile() {
    ofstream outfile;
    outfile.open("/home/yousef/tests/tokens.txt");
    for (auto token : tokens)
        outfile << token << endl;
    outfile.close();
}