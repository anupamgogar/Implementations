class LRUCache{
private:
    unordered_map<int, Node*> m_HashMap;
    struct Node{
        int value;
        Node* next;
        Node* prev;
        Node(){
            value = -1;
            next = NULL;
            prev = NULL;
        }
    };
    Node* m_root;
    int m_capacity;
    Node * front;
    move_to_front(Node* n){
    //todo: modify m_root
    
        if (n->prev){
            n->prev->next = n->next;
        }
        if(!m_front){
            m_front = n;
            m_root = n; 
            return;
        }
        else{
            front->next = n;
            n->prev = front;
            front = n;
        }
        n->next = NULL;
        //todo:check capacity and delete
    }
public:
    LRUCache(int capacity) {
        m_root = NULL;
        front = NULL;
        m_capacity = capacity;
    }
    
    int get(int key) {
        //exists in the map
        if(m_HashMap.find(key)!=m_HashMap.end()){
            move_to_front(m_HashMap[key]);
            return m_HashMap[key]->value;
        }
        else
            return -1;
    }
    void set(int key, int value) {
        //doesn't exist in the map
        if (m_HashMap.find(key)==m_HashMap.end()){
            m_HashMap[key] = new Node();
            m_HashMap[key]->value = value;
        }
        move_to_front(m_HashMap[key]);
    }
};