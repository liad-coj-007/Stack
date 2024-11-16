#include <new> 
template<class T>
class Stack{
public:
    /**
     * @brief defualt constractor
     */
    Stack(){
        idx = -1;
        lastptr = nullptr;
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

private:
    struct Node{
        Node* next;
        // for check
        static const int MAXLENGTH  = 2;
        T arr[MAXLENGTH];
      
        /**
         * @brief node constractor
         */
        Node(){
            next = nullptr;
        }

    };

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
