#pragma once

#include <iostream>

template <typename _T>
class linklist
{
public:
    using value_type = _T;
    using pointer = _T*;
    using reference = _T&;

protected:
    struct node {
        value_type val;
        node *next = nullptr, *prior = nullptr;

        node() {}
        node(value_type u): val(u), next(nullptr), prior(nullptr) {}

        template <typename ...types>
        node(types ...args) : val(args...) {}
    };

    using nodeptr = node*;
    node head, tail;
    size_t len = 0;

    void init()
    {
        len = 0;
        head.next = &tail;
        tail.prior = &head;
    }

    void insert_after (nodeptr pre, nodeptr n)
    {
        n->next = pre->next;
        n->prior = pre;
        pre->next->prior = n;
        pre->next = n;
        ++len;
    }

    void iswap(linklist &&l)
    {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(len, l.len);
    }

public:

    linklist() noexcept
    {
        init();
    }

    linklist (linklist &l) noexcept : linklist()
    {
        nodeptr cur = l.head.next;
        while (cur != &l.tail) {
            push_back(cur->val);
            cur = cur->next;
        }
        return this;
    }

    linklist (linklist &&l) noexcept : linklist()
    {
        iswap(std::move(l));
    }

    virtual ~linklist noexcept ()
    {
        clear();
    }

    void push_back(const value_type &v)
    {
        insert_after(tail.prior, new node{v});
    }

    template <typename ...types>
    void emplace_back(types ...args)
    {
        insert_after(tail.prior, new node(args...));
    }

    void remove (const nodeptr p)
    {
        p->prior->next=p->next;
        p->next->prior=p->prior;
        delete p;
    }

    void clear()
    {
        nodeptr p = head.next, q;
        while (p != &tail) {
            q = p;
            p = p->next;
            delete q;
        }
        init();
    }

    bool empty()
    {
        return len == 0;
    }

    void push_back(const value_type &u)
    {
        insert_after(tail.prior, new node{u});
    }

    friend class iterator;
    using range = nodeptr;

    class iterator
    {
    private:
        range x;
    public:
        using value_type = typename linklist::value_type;
        using pointer = typename linklist::pointer;
        using reference = typename linklist::reference;

        iterator(range y = nullptr): x(y) {}

        bool operator !=(const iterator &i)
        {
            return x != i.x;
        }

        bool operator ==(const iterator i)
        {
            return x == i.x;
        }

        iterator &operator ++ ()
        {
            x = x->next;
            return *this;
        }

        iterator &operator -- ()
        {
            x = x->prior;
            return *this;
        }

        iterator &operator += (int n)
        {
            for (int i = 0; i < n; ++i)
                try {
                    if (x == &tail)
                        throw std::out_of_range("argement is too large");
                    x = x->next;
                }
                catch (std::out_of_range &k) {
                    std::cout << k.what() << std::endl;
                    exit(-1);
                }
            return *this;
        }

        iterator &operator -= (int n)
        {
            for (int i = 0; i < n; ++i)
                try {
                    if (x == &head)
                        throw std::out_of_range("argement is too large");
                    x = x->prior;
                }
                catch (std::out_of_range &k) {
                    std::cout << k.what() << std::endl;
                    exit(-1);
                }
            return *this;
        }

        iterator operator +(int n)
        {
            iterator temp = (this->x);
            for (int i = 0; i < n; ++i)
                temp = temp->next;
            return temp;
        }

        iterator operator -(int n)
        {
            iterator temp = (this->x);
            for (int i = 0; i < n; ++i)
                temp = temp->prior;
            return temp;
        }

        reference operator *()
        {
            return x->val;
        }

        pointer operator ->() const
        {
            return x;
        }
    };

    iterator begin()
    {
        return iterator(head.next);
    }

    iterator end()
    {
        return iterator(&tail);
    }

    iterator rbegin()
    {
        return iterator(tail.prior);
    }

    iterator rend()
    {
        return iterator(&head);
    }

};
