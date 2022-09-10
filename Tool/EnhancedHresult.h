#pragma once
#include <string>
#include <winerror.h>

using namespace std;

class EnhancedHresult {

private: 
    HRESULT _result;
    string _message;

public : 
    EnhancedHresult(){};
    ~EnhancedHresult(){};

    void SetResult(HRESULT result) { _result = result; };
    void SetMessage(string message) { _message = message;};
    HRESULT getResult() { return _result; }
    string getMessage() { return _message; }

};