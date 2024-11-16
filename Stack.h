#include "Exception/EmptyStack.h"
template<class T>
class Stack{
private:
 struct Node{
        Node* next;
        // for check
        static const int MAXLENGTH  = 1000;
        T arr[MAXLENGTH];
      
        /**
         * @brief node constractor
         */
        Node(){
            next = nullptr;
        }

    };
public:
    /**
     * @brief defualt constractor
     */
    Stack(){
        idx = -1;
        lastptr = nullptr;
    }


    Stack(const Stack &other){
        idx = -1;
        lastptr = nullptr;
        CopyData(other);
    }

    Stack& operator=(const Stack &other){
        if(this == &other){
            return *this;
        }
        
        idx = -1;
        DeleteNode(lastptr);
        lastptr = nullptr;
        CopyData(other);
        return *this;
    }


    Stack(Stack &&other){
        idx = other.idx;
        lastptr = other.lastptr;
        other.lastptr = nullptr;
    }

    Stack operator=(Stack &&other){
        DeleteNode(lastptr);
        idx = other.idx;
        lastptr = other.lastptr;
        other.lastptr = nullptr;
        return *this;
    }


    class Iterator {
    private:
        const Stack* stack;
        int idx;
        Node* ptr;

        Iterator(const Stack* stack,Node *ptr,
        const int idx){
            this->stack = stack;
            this->ptr = ptr;
            this->idx = idx;
        }
    public:
        /**
         * @brief return the last value on node
         * @return T&
         */
        const T& operator*()const {
            return ptr->arr[idx];
        }

        /**
         * @brief get the next it
         * 
         */
        Iterator operator++(){
            if(idx == -1){
                return *this;
            }

            idx--;
            if(idx != -1){
                return *this;
            }

            ptr = ptr->next;
        
            if(ptr != nullptr){
                idx = Node::MAXLENGTH - 1;
            }

            return *this;

        }

        /**
         * do operator!= 
         * @param other - other iterator we equal
         */
        bool operator!=(const Iterator &other)const{
            return stack != other.stack || 
            idx != other.idx || ptr != other.ptr;
        }

        friend class Stack;
    };


    /**
     * @brief return the begin it
     */
    Iterator begin()const{
        return Iterator(this,lastptr,idx);
    }

    /**
     * @brief return end it
     */
    Iterator end()const {
        return Iterator(this,nullptr,-1);
    }


    /**
     * @brief add a value to the stack
     * @brief value - the value we add
     */
    void push(const T& value){
        idx = (idx + 1)%Node::MAXLENGTH;
        if(!idx){
            AppendNode(value);
            return;
        }
        lastptr->arr[idx] = value;
    }

    /**
     * @brief check if the stack is empty
     */
    bool is_empty()const{
        return idx == -1;
    }

    /**
     * @brief destructor stack
     */
    ~Stack(){
        DeleteNode(lastptr);
    }

    /**
     * @brief return the last val we push
     * @return const T&
     */
    const T& top()const {
        if(is_empty()){
            throw EmptyStack();
        }
        return lastptr->arr[idx];
    }

    /**
     * @brief pop the lastelement
     */
    void pop(){
        if(is_empty()){
            return;
        }

        idx--;
        if(idx != -1){
            return;
        }

        //delete node
        Node* temp = lastptr;
        lastptr = lastptr->next;
        temp->next = nullptr;
        DeleteNode(temp);


        if(lastptr != nullptr){
            idx = Node::MAXLENGTH - 1;
        }
    }


   

private:

    /**
     * @brief copy data from stack
     * @param stack - the stack we copy
     */
    void CopyData(const Stack &stack){
        try{
            CopyData(stack.begin(),stack.end());
        }catch(const bad_alloc &e){
            DeleteNode(lastptr);
            throw;
        }
    }

    void CopyData(const Iterator &begin ,const Iterator &end){
        if(!(begin != end)){
            return;
        }

        auto it = begin;
        ++it;
        CopyData(it,end);
        push(*begin);
    }

    Node* lastptr;
    int idx;

    /**
     * @brief Delete node
     * @param ptr - the pointer the node we 
     * delete
     */
    void DeleteNode(Node *ptr){
        
        while(ptr != nullptr){
            Node *temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }

    /**
     * @brief append node to the begin
     * with the first value of it value
     * @param value - the value we add 
     * to the new node
     */
    void AppendNode(const T& value){
        Node* newnode = new Node();
        newnode->arr[idx] = value;
        Node* temp = lastptr;
        newnode->next = temp;
        lastptr = newnode;
    }
};
