#ifndef __RBTREE_H__
#define __RBTREE_H__

/*
 * Original code by Masayoshi Mizutani (github.com/m-mizutani)
 * taken from https://gist.github.com/m-mizutani/1135351 with
 * suggested fix by Donghan Miao (github.com/miaodonghan).
 */

#include <cassert>
#include <string>
#include <optional>

#ifdef DEBUG
#include <cstdio>
#endif

template<typename K, typename T> class RBTree
{
private:
    class RBTreeNode
    {
    public:
        enum Color
        {
            RED = 0,
            BLACK = 1,
        };
        enum Side
        {
            LEFT = 0,
            RIGHT = 1,
        };

    private:
        RBTreeNode() :
            _obj(std::nullopt), _key(std::nullopt), _color(BLACK), _parent(nullptr), _tree(nullptr)
        {

        }
    public:
        RBTreeNode(K k, const T& o, RBTree* t) :
            _obj(std::make_optional<T>(o)), _key(std::make_optional<K>(k)), _color(RED), _parent(nullptr), _tree(t)
        {
            _link[LEFT]  = RBTree<K,T>::nil;
            _link[RIGHT] = RBTree<K,T>::nil;
        }
        ~RBTreeNode()
        {
            if (_link[LEFT]->isNil() == false)
            {
                delete _link[LEFT];
            }
            if (_link[RIGHT]->isNil() == false)
            {
                delete _link[RIGHT];
            }
        }
        static RBTreeNode* makeNil()
        {
            return new RBTreeNode();
        }
        inline bool isNil()
        {
            return !_obj.has_value();
        }
        inline void swapColor(RBTreeNode& node)
        {
            std::swap(_color, node._color);
        }
        inline T& getObj()
        {
            return _obj;
        }
        inline void setBlack()
        {
            _color = BLACK;
        }
        inline void setRed()
        {
            _color = RED;
        }
        inline Color getColor()
        {
            return _color;
        }
        inline bool isBlack()
        {
            return(_color == BLACK);
        }
        inline bool isRed()
        {
            return(_color == RED);
        }

        inline Side whichSide(RBTreeNode& node)
        {
            if (_link[LEFT] == &node)
            {
                return LEFT;
            }
            else if (_link[RIGHT] == &node)
            {
                return RIGHT;
            }
            else
            {
                assert(0);
            }
        }

        inline Side otherSide(Side s)
        {
            assert(s == LEFT || s == RIGHT);
            return(s == LEFT ? RIGHT : LEFT);
        }

        inline RBTreeNode* getBrother()
        {
            if (_parent == nullptr)
            {
                return nullptr;
            }

            assert(_parent->_link[LEFT] == this ||
                   _parent->_link[RIGHT] == this);
            return(_parent->_link[LEFT] == this ?
                   _parent->_link[RIGHT] : _parent->_link[LEFT]);
        }

        inline void attach(RBTreeNode* node)
        {
            assert(_key != node->_key);
            Side s =(node->key < _key ? LEFT : RIGHT);
            _attach(s, node);
        }

        inline void attach(Side s, RBTreeNode* node)
        {
            assert(s == LEFT || s == RIGHT);
            assert(this != node);
            assert(_link[s]->isNil());
            _link[s] = node;
            if (!node->isNil())
            {
                node->_parent = this;
            }
        }

        inline RBTreeNode* detach(Side s)
        {
            assert(s == LEFT || s == RIGHT);

            if (isNil() || _link[s]->isNil())
            {
                return RBTree<K,T>::nil;
            }

            RBTreeNode* node = _link[s];
            _link[s]->_parent = nullptr;
            _link[s] = RBTree<K,T>::nil;
            return node;
        }
        inline RBTreeNode* detach(RBTreeNode* node)
        {
            if (_link[RIGHT] == node)
            {
                return detach(RIGHT);
            }
            else if (_link[LEFT] == node)
            {
                return detach(LEFT);
            }
            else
            {
                assert(0);
            }

            return nullptr;
        }
        inline RBTreeNode* searchMax()
        {
            if (! _link[RIGHT]->isNil())
            {
                return _link[RIGHT]->searchMax();
            }
            else
            {
                return this;
            }
        }
        inline RBTreeNode* searchMin()
        {
            if (!_link[LEFT]->isNil())
            {
                return _link[LEFT]->searchMin();
            }
            else
            {
                return this;
            }
        }
        void rotate(Side s)
        {
            RBTreeNode* nLeaf;    // New leaf
            RBTreeNode* nParent;  // New parent
            RBTreeNode* nGrand;   // New grand father
            Side r = otherSide(s);

            nGrand = _parent;
            nParent = detach(r);
            assert(nParent);

            nLeaf = nParent->detach(s);

            if (nGrand)
            {
                Side ps = nGrand->whichSide(*this);
                nGrand->detach(ps);
                nGrand->attach(ps, nParent);
            }
            else
            {
                _tree->_root = nParent;
            }

            nParent->attach(s, this);

            if (!nLeaf->isNil())
            {
                attach(r, nLeaf);
            }
        }

        void adjustInsert()
        {
            if (_parent == nullptr)
            {
                // this node is root
                setBlack();
                return ;
            }
            else
            {
                if (_parent->isRed())
                {
                    assert(_parent->_parent);
                    assert(_parent->_parent->isBlack());
                    RBTreeNode* cParent = _parent;
                    RBTreeNode* grand = _parent->_parent;
                    RBTreeNode* uncle = _parent->getBrother();
                    Side s;

                    if (uncle->isRed())
                    {
                        uncle->setBlack();
                        _parent->setBlack();
                        grand->setRed();
                        grand->adjustInsert();
                    }
                    else
                    {
                        if (_parent->whichSide(*this) !=
                                grand->whichSide(*_parent))
                        {
                            s = otherSide(cParent->whichSide(*this));
                            cParent->rotate(s);
                            cParent = this;
                        }

                        s = otherSide(grand->whichSide(*cParent));
                        grand->rotate(s);

                        assert(grand->isBlack() && cParent->isRed());
                        grand->swapColor(*cParent);
                    }
                }
            }
        }

        bool insert(RBTreeNode* node)
        {
            if (_key == node->_key)
            {
                // duplicated
                return false;
            }
            else
            {
                Side s = (node->_key < _key ? LEFT : RIGHT);
                if (! _link[s]->isNil())
                {
                    return _link[s]->insert(node);
                }
                else
                {
                    attach(s, node);
                }
            }

            node->adjustInsert();
            return true;
        }

        RBTreeNode* lookup(K k)
        {
            if (_key == k)
            {
                return this;
            }
            else
            {
                Side s =(k < _key ? LEFT : RIGHT);
                return(_link[s]->isNil() ? nullptr : _link[s]->lookup(k));
            }
        }

        void leave()
        {
            // only detach from tree, balancing color & tree in adjustLeave()
            RBTreeNode* cParent = _parent;

            if (_link[LEFT]->isNil() && _link[RIGHT]->isNil())
            {
                if (cParent)
                {
                    Side s = cParent->whichSide(*this);
                    cParent->detach(*this);

                    if (isBlack())
                    {
                        cParent->link[s]->adjustLeave(cParent);
                    }
                }
                else
                {
                    _tree->root = nullptr;
                }
            }
            else if ((_link[LEFT]->isNil()) ^
                     (_link[RIGHT]->isNil()))
            {
                Side s =(_link[LEFT]->isNil() ? RIGHT : LEFT);
                RBTreeNode* cTarget = _detach(s);

                if (cParent)
                {
                    cParent->detach(*this);
                    cParent->attach(*cTarget);
                }
                else
                {
                    _tree->root = cTarget;
                }

                if (isBlack())
                {
                    cTarget->adjustLeave(cParent);
                }
            }
            else
            {
                // swap target node & maximum node in left subtree
                assert(! _link[LEFT]->isNil() &&
                       ! _link[RIGHT]->isNil());

                RBTreeNode* cMax = _link[LEFT]->searchMax();
                RBTreeNode* mParent = cMax->parent;
                RBTreeNode* cLeft  = _detach(LEFT);
                RBTreeNode* cRight = _detach(RIGHT);
                RBTreeNode* mLeft  = cMax->detach(LEFT);

                _attach(*mLeft);
                if (cParent)
                {
                    cParent->detach(*this);
                }
                else
                {
                    _tree->root = nullptr;
                }

                if (cMax != cLeft)
                {
                    // cMax have more 1 hop from THIS
                    mParent->detach(*cMax);
                    mParent->attach(*this);
                    cMax->attach(LEFT,  *cLeft);
                    cMax->attach(RIGHT, *cRight);
                }
                else
                {
                    // cMax == cLeft(cMax is left node of THIS)
                    assert(cMax->link[RIGHT]->isNil());
                    cMax->attach(RIGHT, *cRight);
                    cMax->attach(LEFT,  *this);
                }

                if (cParent)
                {
                    cParent->attach(*cMax);
                }
                else
                {
                    _tree->root = cMax;
                }

                swapColor(*cMax);
                leave();
            }
        }

        void adjustLeave(RBTreeNode* cParent)
        {
            // nothing to do when node is root
            if (nullptr == cParent)
            {
                setBlack();
                return ;
            }
            if (isRed())
            {
                setBlack();
                return ;
            }

            RBTreeNode* cNeighbor =
                cParent->link[otherSide(cParent->whichSide(*this))];

            assert(cNeighbor) ;
            // cParent->tree->dumpTree("Adjusting by Leave");

            if (cNeighbor->isRed())
            {
                Side s = cParent->whichSide(*this);
                assert(cParent->isBlack());
                cParent->swapColor(*cNeighbor);
                cParent->rotate(s);
                cNeighbor = cParent->link[otherSide(s)];
            }
            else if (cParent->isBlack() &&
                     cNeighbor->link[LEFT]->isBlack() &&
                     cNeighbor->link[RIGHT]->isBlack())
            {
                assert(cNeighbor->isBlack());
                cNeighbor->setRed();
                return cParent->adjustLeave(cParent->parent);
            }

            if (cParent->isRed() &&
                    cNeighbor->link[LEFT]->isBlack() &&
                    cNeighbor->link[RIGHT]->isBlack())
            {
                assert(cNeighbor->isBlack());
                cParent->swapColor(*cNeighbor);
            }
            else
            {
                Side ns = cParent->whichSide(*cNeighbor); // Neighbor side
                Side os = otherSide(ns); // Other side

                if (cNeighbor->link[os]->isRed() &&
                        cNeighbor->link[ns]->isBlack())
                {
                    cNeighbor->swapColor(*cNeighbor->link[os]);
                    cNeighbor->rotate(ns);
                    cNeighbor = cParent->link[ns];
                }

                if (cNeighbor->link[ns]->isRed())
                {
                    cNeighbor->link[ns]->setBlack();
                    cParent->swapColor(*cNeighbor);
                    cParent->rotate(os);
                }
            }
        }

#ifdef DEBUG
        int checkBalance()
        {
            if (isNil())
            {
                return 1;
            }

            if (isRed() &&
                    (_link[LEFT]->isRed() || _link[RIGHT]->isRed()))
            {
                if (_key.has_value())
                {
                    printf("Detected double RED, around key=%f", _key.value());
                }
                assert(0);
            }

            int lCount = _link[LEFT]->checkBalance();
            int rCount = _link[RIGHT]->checkBalance();
            if (lCount != rCount)
            {
                if (_key.has_value())
                {
                    printf("Detected broken balance, around key=%f", _key.value());
                }
                assert(0);
            }

            return(isBlack() ? rCount + 1 : rCount);
        }

        void printNode(int depth)
        {
            char space[] = "     ";
            char header[0x1000] = "";
            if (_link[RIGHT])
            {
                _link[RIGHT]->printNode(depth + 1);
            }

            for (int i = 0; i < depth ; i++)
            {
                strncat(header, space, sizeof(header) - 1);
            }

            printf("%s[%s:%f %p]\n", header,
                  (_color == RED ? "R" : "B"), _key.value(), &_obj);

            if (_link[LEFT])
            {
                _link[LEFT]->printNode(depth + 1);
            }
        }
#endif

    private:
        std::optional<T> _obj;
        std::optional<K> _key;
        Color _color;
        RBTreeNode* _parent,* _link[2];
        RBTree* _tree;
    }* _root;

    static RBTreeNode* nil ;

#ifdef DEBUG
    void dumpTree(const std::string& title)
    {
        printf("======= %s =============================================\n", title.c_str());

        if (_root)
        {
            _root->printNode(0);
        }
        else
        {
            printf("(!!) No tree\n");
        }
    }
#endif

public:
    RBTree() : _root(nullptr) {}
    ~RBTree()
    {
        delete _root;
    }

    bool insert(K key, T p)
    {
        RBTreeNode* node = new RBTreeNode(key, p, this);

#ifdef DEBUG
        dumpTree("Before insertion");
#endif

        if (_root)
        {
            if (!_root->insert(node))
            {
                delete node;
                return false;
            }
        }
        else
        {
            _root = node;
            node->setBlack();
        }

#ifdef DEBUG
        dumpTree("After insertion");
        _root->checkBalance();
#endif
        return true;
    }

    T& lookup(K key)
    {
        if (nullptr == _root)
        {
            return nullptr;
        }

        RBTreeNode* node = _root->lookup(key);
        return(node ? node->getObj() : nullptr);
    }

    bool remove(K key)
    {
        if (_root == nullptr)
        {
            return false;
        }

        RBTreeNode* node = _root->lookup(key);
        if (node == nullptr)
        {
            return false;
        }

#ifdef DEBUG
        dumpTree("Before removing");
#endif
        node->leave();
        delete node;

#ifdef DEBUG
        dumpTree("After removing");
        _root->checkBalance();
#endif

        return true;
    }
};

template <typename K, typename T>
class RBTree<K,T>::RBTreeNode* RBTree<K,T>::nil = RBTreeNode::makeNil();


#endif /* __RBTREE_H__ */
