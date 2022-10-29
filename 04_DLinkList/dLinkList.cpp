#include <iostream>
using namespace std;

// 定义双向链表的节点类型
struct Node
{
	Node(int data = 0)
		: data_(data)
		, next_(nullptr)
		, prev_(nullptr)
	{}
	int data_;
	Node* next_;
	Node* prev_;
};

// 双向链表
class DoubleLink
{
public:
	DoubleLink()
	{
		head_ = new Node();
	}
	~DoubleLink()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}

public:
	// 头插
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		
		// 先改自己再改别人
		node->prev_ = head_;
		node->next_ = head_->next_;
		if (head_->next_ != nullptr)
			head_->next_->prev_ = node;
		head_->next_ = node;
	}

	// 尾插
	void InsertTail(int val)
	{
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		// p-》尾节点
		Node* node = new Node(val);
		node->prev_ = p;
		p->next_ = node;
	}

	// 移除一个节点
	void Remove(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				p->prev_->next_ = p->next_;
				if (p->next_ != nullptr)
				{
					p->next_->prev_ = p->prev_;
				}
				delete p;
				return;
					
			}
			p = p->next_;
		}
	}

	// 移除所有指定节点
	void RemoveAll(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				p->prev_->next_ = p->next_;
				if (p->next_ != nullptr)
				{
					p->next_->prev_ = p->prev_;
				}
				Node* next = p->next_;
				delete p;
				p = next;
			}
			p = p->next_;
		}
	}

	// 链表节点输出
	void show() const
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}

private:
	Node* head_;	// 指向头节点
};

int main(void)
{
	DoubleLink dlink;

	dlink.InsertHead(10);
	dlink.InsertHead(11);
	
	dlink.InsertTail(20);
	dlink.InsertTail(21);
	dlink.InsertTail(22);
	dlink.InsertTail(23);
	dlink.InsertTail(24);
	dlink.InsertTail(25);
	dlink.show();

	return 0;
}
