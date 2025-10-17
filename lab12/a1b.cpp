#include<iostream>
#include<vector>
#include<stack>
using namespace std;
//implementation using array

class Stack
{
    vector<int> v;

public:
    void PUSH(int x)
    {
        v.push_back(x);
    }

    void POP()
    {
        if (!v.empty())
            v.pop_back();
        else
            cout << "Stack Underflow\n";
    }

    int TOP()
    {
        if (!v.empty())
            return v.back();
        else
        {
            cout << "Stack is empty\n";
            return -1; 
        }
    }

    void PrintStack()
    {
        if (v.empty())
        {
            cout << "Stack is empty\n";
            return;
        }
        cout << "Stack : ";
        for (int x : v)
            cout << x << " ";
        cout << "\n";
    }

    int Post(const char arr[]){
    Stack st; //stack 2

    // left to right for post
    for (int i = 0; arr[i] != '\0'; i++) {
        char ch = arr[i];

        if (isdigit(ch)) {
            st.PUSH(ch - '0');
        } else {
            //its operator
            int A = st.TOP(); st.POP(); 
            int B = st.TOP(); st.POP();

            int result;
            switch (ch) {
                case '+': result = B + A; break;
                case '-': result = B - A; break;
                case '*': result = B * A; break;
                case '/': result = B / A; break;
                default:  result = 0;
            }
            st.PUSH(result);
        }
    }
    return st.TOP();
}

};


int main(){
    //Experiment 1b: Program to demonstrate stack operations and postfix evaluation
    Stack s;
    s.PUSH(1);
    s.PrintStack();
    s.PUSH(3);
    s.PrintStack();
    s.PUSH(4);
    s.PrintStack();
    cout<<"Popped element is: "<<s.TOP()<<endl;
    s.POP();
    s.PrintStack();
    cout<<"Top element is: "<<s.TOP()<<endl;
    s.PrintStack();
    //Postfix evaluation
    const char* expr = "45*2-";  
    cout << "Postfix Expression: " << expr << endl;
    cout << "valuation Result = " << s.Post(expr) << endl;
    return 0;
}