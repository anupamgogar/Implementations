class LRUCache{
private:
	struct Node{
		int value;
		int key;
		Node* next;
		Node* prev;
		Node(){
			value = -1;
			key = -1;
			next = NULL;
			prev = NULL;
		}
	};
	unordered_map<int, Node*> m_HashMap;
	Node * m_back;
	Node * m_front;
	int m_capacity;
	int m_Elements;

	void remove_last_node(){
		Node* temp = m_back;
		m_back->next->prev = NULL;
		m_back = m_back->next;
		m_HashMap.erase(temp->key);
		delete temp;
		temp = 0;
		m_Elements--;
	}

	void move_to_front(Node* n){
		//todo: modify m_root
		//Case 1: First Element
		if(!m_front){
			m_front = n;
			m_back = n;
			return;
		}
		//Case 2: Node is already at front.
		if (m_front == n){
			//do nothing
			return;
		}
		//Case 3: Node is in the middle.
		if (n->prev && n != m_back){
			n->prev->next = n->next;
			n->next->prev = n->prev;
		}
		//Case 4: Node is at last.
		if (n == m_back){
			n->next->prev = NULL;
			m_back = n->next;
		}
		//Attach node in the front
		n->next = NULL;
		m_front->next = n;
		n->prev = m_front;
		m_front = n;
		if (m_Elements > m_capacity){
			remove_last_node();
		}
	}
public:
	LRUCache(int capacity) {
		m_back = NULL;
		m_front = NULL;
		m_capacity = capacity;
		m_Elements = 0;
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
			m_Elements++;
		}
		m_HashMap[key]->value = value;
		m_HashMap[key]->key = key;
		move_to_front(m_HashMap[key]);
	}
};