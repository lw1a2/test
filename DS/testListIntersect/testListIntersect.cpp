#include <iostream>
#include <set>

using namespace std;

/*
判断两个链表是否相交 
*/

template <class T>
struct Node
{
    T value;
    Node* next;
    Node():next(NULL)
    {
    }
};


/*
方法一：将一个链表放到set里，遍历另一个链表，如果发现另一个链表的next在set里，则说明相交 
复杂度M*logN 
*/
template <class T>
bool testListIntersect(Node<T>* list1, Node<T>* list2)
{
    Node<T>* p1 = list1;
    Node<T>* p2 = list2;
    set<Node<T>*> s;
    while (p1)
    {
        s.insert(p1);
        p1 = p1->next;
    }

    while (p2)
    {
        if (s.find(p2) != s.end())
        {
            return true;
        }
        p2 = p2->next;
    }

    return false;
}

/*
方法二：检测两个列表的最后一个节点是否相同（即检测倒数第二个节点的next是否相同）， 
相同则说明相交 
复杂度M+N 
*/
template <class T>
bool testListIntersect2(Node<T>* list1, Node<T>* list2)
{
    Node<T>* p1 = list1;
    Node<T>* p2 = list2;
    while (p1->next)
    {
        p1 = p1->next;
    }

    while (p2->next)
    {
        p2 = p2->next;
    }

    if (p1 == p2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Node<int> common_node3;
    Node<int> common_node4;
    common_node3.next = &common_node4;

    Node<int> list1;
    Node<int> list1_node1;
    list1.next = &list1_node1;
    Node<int> list1_node2;
    list1_node1.next = &list1_node2;
    list1_node2.next = &common_node3;

    Node<int> list2;
    Node<int> list2_node1;
    list2.next = &list2_node1;
    Node<int> list2_node2;
    list2_node1.next = &list2_node2;
    list2_node2.next = &common_node3;

    Node<int> list3;
    Node<int> list3_node1;
    list3.next = &list3_node1;
    Node<int> list3_node2;
    list3_node1.next = &list3_node2;

    cout << testListIntersect(&list1, &list2) << endl;
    cout << testListIntersect(&list1, &list3) << endl;

    cout << testListIntersect2(&list1, &list2) << endl;
    cout << testListIntersect2(&list1, &list3) << endl;

    return 0;
}
