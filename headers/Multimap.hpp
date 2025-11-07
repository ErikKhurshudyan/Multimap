#ifndef __MAP_T_HPP__
#define __MAP_T_HPP__

#include <iostream>
#include <utility>

template <typename Key1, typename Data1> std::ostream& operator<<(std::ostream& out, const std::pair<Key1, Data1> rhv);

template <typename Key, typename Data>
class MultiMap 
{
    template <typename Key1, typename Data1> friend std::ostream& operator<<(std::ostream& out, const MultiMap<Key1, Data1>& rhv);
private:
    struct Node {
        Node(const Key& key,
             const Data& data,
                   Node* parent = NULL,
                   Node* left = NULL,
                   Node* right = NULL)
            : value_(key, data)
            , parent_(parent), left_(left), right_(right)
        {}
        std::pair<const Key, Data> value_;
        Node* parent_;
        Node* left_;
        Node* right_;
    };
public:
    typedef std::pair<const Key, Data> value_type;
    typedef Key key_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;
private:
    typedef Data data_type;

private:
    static Node* getRightMost(Node* rhv);
    static Node* getLeftMost(Node* rhv);

public:
    MultiMap();
    MultiMap(const MultiMap& rhv); 
    template <typename InputIterator>
    MultiMap(InputIterator first, InputIterator last); 
    ~MultiMap();
    const MultiMap& operator=(const MultiMap& rhv);
    void swap(MultiMap& rhv);
    size_type size() const;
    size_type max_size() const;
    void clear();
     
    data_type& operator[](const key_type& x);
    bool empty() const; 
    bool operator==(const MultiMap& rhv) const;
    bool operator!=(const MultiMap& rhv) const;
    bool operator< (const MultiMap& rhv) const;
    bool operator<=(const MultiMap& rhv) const;
    bool operator> (const MultiMap& rhv) const;
    bool operator>=(const MultiMap& rhv) const;

    class const_iterator {
        friend class MultiMap<Key, Data>; 
    public:
        const_iterator();
        const_iterator(const const_iterator& rhv);
        ~const_iterator();
        const const_iterator& operator=(const const_iterator& rhv); 
        const value_type& operator*() const;
        const value_type* operator->() const;
        const_iterator operator++();
        const_iterator operator++(int);
        const_iterator operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator& rhv) const;
        bool operator!=(const const_iterator& rhv) const;
        bool operator!() const;
    protected:
        Node* getPtr() const;
        void setPtr(Node* temp);
        void destroy();
        const_iterator parent() const;
        const_iterator left() const;
        const_iterator right() const;
        const const_iterator& goParent();
        const const_iterator& goLeft();
        const const_iterator& goRight();
        void setParent(const_iterator it);
        void setLeft(const_iterator it);
        void setRight(const_iterator it);
        void createLeft(const value_type& x);
        void createRight(const value_type& x);
        const_iterator firstLeftParent() const;
        const_iterator firstRightParent() const;
        bool isLeftParent() const;
        bool isRightParent() const;
        int balance() const;
        int depth() const;
        operator bool() const;
    private:
        explicit const_iterator(Node* ptr);
    private:
        Node* ptr_;
    };

    class iterator : public const_iterator {
        friend class MultiMap<Key, Data>; 
    public:
        iterator();
        iterator(const iterator& rhv);
        ~iterator();
        const iterator& operator=(const iterator& rhv); 
        value_type& operator*();
        value_type* operator->();
        iterator operator++();
        iterator operator++(int);
        iterator operator--();
        iterator operator--(int);
    private:
        explicit iterator(Node* ptr);
        iterator parent();
        iterator left();
        iterator right();
        iterator& goParent();
        iterator& goLeft();
        iterator& goRight();
    };

    class const_reverse_iterator {
        friend class MultiMap<Key, Data>; 
    public:
        const_reverse_iterator();
        const_reverse_iterator(const const_reverse_iterator& rhv);
        ~const_reverse_iterator();
        const const_reverse_iterator& operator=(const const_reverse_iterator& rhv); 
        const value_type& operator*() const;
        const value_type* operator->() const;
        const_reverse_iterator operator++();
        const_reverse_iterator operator++(int);
        const_reverse_iterator operator--();
        const_reverse_iterator operator--(int);
        bool operator==(const const_reverse_iterator& rhv) const;
        bool operator!=(const const_reverse_iterator& rhv) const;
        bool operator!() const;
    protected:
        Node* getPtr() const;
        void setPtr(Node* temp);
        void destroy();
        const const_reverse_iterator& goParent();
        bool isLeftParent() const;
        bool isRightParent() const;
    private:
        explicit const_reverse_iterator(Node* ptr);
    private:
        Node* ptr_;
    };
    
    class reverse_iterator : public const_reverse_iterator {
        friend class MultiMap<Key, Data>;
    public:
        reverse_iterator();
        reverse_iterator(const reverse_iterator& rhv);
        ~reverse_iterator();
        const reverse_iterator& operator=(const reverse_iterator& rhv); 
        value_type& operator*();
        value_type* operator->();
        reverse_iterator operator++();
        reverse_iterator operator++(int);
        reverse_iterator operator--();
        reverse_iterator operator--(int);
    private:
        explicit reverse_iterator(Node* ptr);
        reverse_iterator& goParent();
    };

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    std::pair<iterator, bool> insert(const value_type& x);
    iterator insert(iterator pos, const value_type& x);
    template <typename InputIt>
    void insert(InputIt first, InputIt last);

    void erase(iterator pos);
    size_type erase(const key_type& k);
    void erase(iterator first, iterator last);

    const_iterator find(const key_type& k) const;
    iterator find(const key_type& k);
    size_type count(const key_type& k) const;

    iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;
    std::pair<iterator, iterator> equal_range(const key_type& k);
    std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
    
    void print(std::ostream& out = std::cout) const;
    void preOrderRec(std::ostream& out = std::cout) const;
    void inOrderRec(std::ostream& out = std::cout) const;
    void postOrderRec(std::ostream& out = std::cout) const;
    void preOrderIter(std::ostream& out = std::cout) const;
    void inOrderIter(std::ostream& out = std::cout) const;
    void postOrderIter(std::ostream& out = std::cout) const;
    void levelOrderIter(std::ostream& out = std::cout) const;
private:
    void goUp(iterator& it, const value_type& x);
    std::pair<iterator, bool> goDownAndInsert(iterator it, const value_type& x);
    void rotateRight(iterator& it);
    void rotateLeft(iterator& it);
    void balance(iterator it);
    bool isRoot(const const_iterator& temp) const;
    void preOrderHelper(Node* root, std::ostream& out = std::cout) const;
    void inOrderHelper(Node* root, std::ostream& out = std::cout) const;
    void postOrderHelper(Node* root, std::ostream& out = std::cout) const;
    void outputTree(Node* ptr, std::ostream& out, const int totalSpaces = 0) const;
    iterator findHelper(iterator root, const key_type& key) const;
    iterator boundHelper(iterator root, const key_type& key) const;
    void clearHelper(Node*& root); 
    std::pair<iterator,bool> insertHelper(iterator pos, const value_type& x);
    size_type eraseRangeHelper(iterator first, iterator last);
private:
    Node* root_;

};

#include "templates/MultiMap.cpp"
#endif /// __MAP_T_HPP__

