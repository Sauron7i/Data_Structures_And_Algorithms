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

class DoubleCircleLink
{
public:
	DoubleCircleLink()
	{
		head_ = new Node();
		head_->next_ = head_;
		head_->prev_ = head_;
	}
	~DoubleCircleLink()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			p->next_->prev_ = head_;
			delete p;
			p = head_->next_;
		}
		delete head_;
		head_ = nullptr;
	}

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
		Node* p = head_->prev_;

		// p-》尾节点
		Node* node = new Node(val);
		node->prev_ = p;
		p->next_ = node;
		node->next_ = head_;
		head_->prev_ = node;
	}

	// 移除一个节点
	void Remove(int val)
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			if (p->data_ == val)
			{
				p->prev_->next_ = p->next_;
				p->next_->prev_ = p->prev_;
				delete p;
				return;

			}
			p = p->next_;
		}
	}

	// 链表节点输出
	void show() const
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
private:
	Node* head_;
};

int main(void)
{
	DoubleCircleLink dlink;
	dlink.InsertHead(10);
	dlink.InsertTail(20);

	dlink.show();
	return 0;
}
