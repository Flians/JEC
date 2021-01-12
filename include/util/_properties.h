#include "circuit/node.h"

class Node;

enum PROPERTY
{
    CYCLE = 0,     // vector<pair<Node *, Node *>> source -> target
    CLEAN_SPL = 1, // bool
    CLEAN_DFF = 2, // bool
    LAYERS = 3,    // vector<vector<Node*>>
};

class FieldInterface
{
protected:
    size_t type;

public:
    virtual ~FieldInterface() = default;
};

template <typename T>
class Field : virtual public FieldInterface
{
private:
    T val;

public:
    Field() {}
    Field(T val_) : val(val_){};
    T &get_value()
    {
        return val;
    }
};

template <typename T = Node *>
class Field_V : virtual public FieldInterface
{
private:
    vector<T> _val;

public:
    Field_V() {}
    Field_V(vector<T> val_) : _val(val_){};
    vector<T> &get_value()
    {
        return _val;
    }
};

template <typename T = Node *>
class Field_2V : virtual public FieldInterface
{
private:
    vector<vector<T>> __val;

public:
    Field_2V() {}
    Field_2V(vector<vector<T>> val_) : __val(val_) {}
    vector<vector<T>> &get_value()
    {
        return __val;
    }
};