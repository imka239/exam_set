//
// Created by ASUS on 22.06.2019.
//

#ifndef List_List_H
#define List_List_H

#include <iostream>
#include <assert.h>

template <class T>
struct Set {
    struct node {
        node* left, * right,* par;
        node(node* left, node* right, node * par) : left(left), right(right), par(par) {}
        node() : left(nullptr), right(nullptr), par(nullptr) {}
        ~node() = default;
    };
    struct extended_node : node {
        T value;
        extended_node() = default;
        ~extended_node() = default;
        extended_node(T const& v, node* l, node* r, node * par) : node(l, r, par), value(v) {}
    };

    template <class U>
    struct Iterator {
        using difference_type = std::ptrdiff_t;
        typedef const U value_type;
        typedef const U* pointer;
        typedef const U& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        friend class Set;

        Iterator() = default;
        Iterator(const Iterator<T> & p) : ptr(p.ptr) {}
        ~Iterator() = default;
        Iterator& operator++() {
            if (ptr == nullptr) return *this;
            if (ptr->right != nullptr) {
                ptr = ptr->right;
                while (ptr->left != nullptr) {
                    ptr = ptr->left;
                }
                return *this;
            }
            while (ptr->par != nullptr && ptr->par->right == ptr) {
                ptr = ptr->par;
            }
            if (ptr->par != nullptr) {
                ptr = ptr->par;
            }
            return *this;
        }
        const Iterator operator++(int) {
            Iterator res(ptr);
            ++(*this);
            return res;
        }
        Iterator& operator--() {
            if (ptr == nullptr) return *this;
            if (ptr->left != nullptr) {
                ptr = ptr->left;
                while (ptr->right != nullptr) {
                    ptr = ptr->right;
                }
                return *this;
            }
            while (ptr->par != nullptr && ptr->par->left == ptr) {
                ptr = ptr->par;
            }
            if (ptr->par != nullptr) {
                ptr = ptr->par;
            }
            return *this;
        }
        const Iterator operator--(int) {
            Iterator res(ptr);
            --(*this);
            return res;
        }
        const U& operator *() const {
            return (static_cast<extended_node*>(ptr)->value);
        }
        const U* operator ->() const {
            return &(static_cast<extended_node*>(ptr)->value);
        }

        friend bool operator ==(Iterator const& a, Iterator const& b) {
            return a.ptr == b.ptr;
        }

        friend bool operator !=(Iterator const& a, Iterator const& b) {
            return a.ptr != b.ptr;
        }

    private:
        explicit Iterator(Set<T>::node* p) : ptr(p) {}
        node* ptr;
    };

    Set() noexcept {}
    ~Set() noexcept {
        clear();
    }

    Set(Set const& that) : Set() {
        for (auto x = that.cbegin(); x != that.cend(); ++x) {
            insert(*x);
        }
    }

    Set& operator=(Set const& that) {
        Set x(that);
        swap(x, *this);
        return *this;
    }

    typedef Iterator<T> iterator;
    using const_iterator = Iterator <T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() {
        node * now = &fake;
        while (now->left != nullptr) {
            now = now->left;
        }
        return iterator(now);
    }

    iterator end() {
        return iterator(&fake);
    }

    const_iterator begin() const {
        node * now = const_cast<node *>(&fake);
        while (now->left != nullptr) {
            now = now->left;
        }
        return const_iterator(now);
    }

    const_iterator end() const {
        return const_iterator(const_cast<node*>(&fake));
    }
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(cend());
    }
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(cbegin());
    }

    const_iterator cend() const noexcept{
        return end();
    }

    const_iterator cbegin() const noexcept {
        return begin();
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }

    iterator erase(const_iterator that) {
        assert(that != end());
        iterator ans(that);
        ans++;
        node * now = that.ptr;
        if (now->left == nullptr && now->right == nullptr) {
            now->par->left == now ? now->par->left = nullptr : now->par->right = nullptr;
        } else if (now->right == nullptr) {
            now->par->left == now ? now->par->left = now->left : now->par->right =  now->left;
            now->left->par = now->par;
        } else if (now->left == nullptr) {
            now->par->left == now ? now->par->left = now->right : now->par->right =  now->right;
            now->right->par = now->par;
        } else {
            node* next = ans.ptr;
            if (next->par->right == next) {
                now->par->left == now ? now->par->left = next : now->par->right = next;
                next->par = now->par;
                next->left = now->left;
                now->left->par = next;
                now->left = nullptr;
                now->right = nullptr;
                now->par = nullptr;
            } else {
                next->par->left = next->right;
                if (next->right != nullptr) {
                    next->right->par = next->par;
                }
                next->right = nullptr;
                next->par = nullptr;
                now->par->left == now ? now->par->left = next : now->par->right = next;
                next->par = now->par;
                next->right = now->right;
                next->left = now->left;
                now->left->par = next;
                now->right->par = next;
                now->left = nullptr;
                now->right = nullptr;
                now->par = nullptr;
            }
        }
        delete (static_cast<extended_node*>(now));
        return ans;
    }

    std::pair<iterator, bool> insert(T const& val) {
        return insert(val, nullptr);
    }

    iterator find(T const& val) {
        if (empty()) {
            return end();
        }
        iterator ans = lower_bound(val);
        if (ans != end() && static_cast<extended_node*>(ans.ptr)->value == val) {
            return ans;
        } else {
            return end();
        }
    }

    iterator lower_bound(T const & val) const {
        for (auto x = begin(); x != end(); ++x) {
            if (static_cast<extended_node*>(x.ptr)->value >= val) {
                return x;
            }
        }
        return end();
    }

    iterator upper_bound(T const & val) const {
        iterator ans = lower_bound(val);
        if (ans != end() && static_cast<extended_node*>(ans.ptr)->value == val) {
            return ++ans;
        } else {
            return ans;
        }
    }

    friend void swap(Set<T> & a, Set<T> & b) noexcept {
        std::swap(a.fake.left, b.fake.left);
        std::swap(a.fake.right, b.fake.right);
        std::swap(a.fake.par, b.fake.par);
        if (a.fake.left != nullptr) {
         a.fake.left->par = &a.fake;
        }
        if (b.fake.left != nullptr) {
            b.fake.left->par = &b.fake;
        }
    }

    void clear() {
        dealloc(fake.left);
        fake.left = nullptr;
    }

    const bool empty() const {
        return fake.left == nullptr;
    }

private:
    node fake;
    void dealloc(node * cur) {
        if (cur == nullptr) {
            return;
        }
        dealloc(cur->left);
        dealloc(cur->right);
        delete (static_cast<extended_node*>(cur));
    }

    std::pair<iterator, bool> insert(T const& x, node * parent) {
        if (fake.left == nullptr) {
            fake.left = new extended_node(x, nullptr, nullptr, &fake);
            return {iterator(fake.left), true};
        }
        if (parent == nullptr) {
            return insert(x, fake.left);
        }
        const T& value = static_cast<extended_node*>(parent)->value;
        if (x < value) {
            if (parent->left == nullptr) {
                parent->left = new extended_node(x, nullptr, nullptr, parent);
                return {iterator(parent->left), true};
            } else {
                return insert(x, parent->left);
            }
        }
        if (x > value) {
            if (parent->right == nullptr) {
                parent->right = new extended_node(x, nullptr, nullptr, parent);
                return {iterator(parent->right), true};
            } else {
                return insert(x, parent->right);
            }
        }
        return {iterator(parent), false};
    }
};

#endif //List_List_H
