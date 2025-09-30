#include <iostream>
#include <stack>
using namespace std;

class QueueWithTwoStacks{
private:
stack<int> stack_in;
stack<int> stack_out;
int maxsize;
public:
    QueueWithTwoStacks(int capcity):maxsize(capcity){}

    void inQueue(int x){
        if (isFull()) cout<<"队列已满"<<endl;
        else stack_in.push(x);
    }

    int deQueue(){
        if(isEmpty()) {
            cout<<"队列已空"<<endl;
            return 0;
        }
        if(stack_out.empty()){
            while(!stack_in.empty()){
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }
        int result=stack_out.top();
        stack_out.pop();
        return result;
    }

    bool isFull(){
        return (stack_in.size()+stack_out.size()==maxsize);
    }

    bool isEmpty(){
        return stack_in.empty()&&stack_out.empty();
    }

};