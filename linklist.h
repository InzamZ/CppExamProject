#pragma once
#include <iostream>
#include "employee.h"

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
        ~node() {}

        template <typename ...types>
        node(types ...args) : val(args...) {}

        friend class iterator;
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
    }

    linklist (linklist &&l) noexcept : linklist()
    {
        iswap(std::move(l));
    }

    virtual ~linklist() noexcept
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
        p->prior->next = p->next;
        p->next->prior = p->prior;
        delete p;
    }

    void clear()
    {
        nodeptr p = head.next, q;
        while (p != &tail) {
            q = p;
            p = p->next;
            delete (q->val);
            delete q;
        }
        init();
    }

    bool empty()
    {
        return len == 0;
    }

    using callback_t = std::function<void (value_type &)>;
    using callback_e = std::function<void (employee &)>;

    void traverse (callback_t f)
    {
        for (auto it = begin(); it != end(); ++it)
            f(*it) ;
    }
    void _traverse (callback_e f)
    {
        for (auto it = begin(); it != end(); ++it)
            f((*(*it))) ;
    }
    friend class iterator;
    using range = nodeptr;
    friend void sort<linklist<employee *>, std::function<bool(employee *, employee *)> >(linklist<employee *> &a, std::function<bool(employee *, employee *)> b);

    class iterator
    {
    private:
        range x;
    public:
        using value_type = typename linklist::value_type;
        using pointer = typename linklist::pointer;
        using reference = typename linklist::reference;

        iterator(range y = nullptr): x(y) {}

        bool operator !=(const iterator i)
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
            auto temp = (this->x);
            for (int i = 0; i < n; ++i)
                temp = temp->next;
            return iterator(temp);
        }

        iterator operator =(iterator a)
        {
            x = a.x;
            return *this;
        }

        iterator operator -(int n)
        {
            auto temp = (this->x);
            for (int i = 0; i < n; ++i)
                temp = temp->prior;
            return iterator(temp);
        }

        reference operator *()
        {
            return x->val;
        }

        constexpr pointer operator ->() const
        {
            return x;
        }

        void remove ()
        {
            x->prior->next = x->next;
            x->next->prior = x->prior;
            delete x->val;
            delete x;
        }

        void _swap(iterator &m)
        {
            x->prior->next = m.x;
            m.x->next->prior = x;
            x->next = m.x->next;
            m.x->prior = x->prior;
            x->prior = m.x;
            m.x->next = x;
            x = m.x;
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
