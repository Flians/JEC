#include "circuit/node.h"
#include <memory>
#include <typeinfo>

class Node;

class PropertyInterface
{
protected:
    /** name of this property. */
    const string name;

public:
    virtual const string &get_name() const
    {
        return this->name;
    }
    virtual ~PropertyInterface() = default;
};

template <typename T>
class Property : virtual public PropertyInterface
{
private:
    /** the default value of this property. */
    const T default_val;

public:
    /**
     * Creates a property with given name and {@code null} as default value.
     * 
     * @param _name the name
     */
    Property(const string &_name) : name(_name) {}

    /**
     * Creates a property with given name and default value.
     * 
     * @param _name the name
     * @param _default_val the default value
     */
    Property(const string &_name, const T &_default_val) : Property(_name), default_val(_default_val) {}

    /**
     * @return the default value of this property.
     */
    const T &get_default() const
    {
        return this->default_val;
    }

    /**
     * @return the name of this property.
     */
    const string &get_name() const
    {
        return this->name;
    }
};

class PROPERTIES
{
private:
    PROPERTIES();
    PROPERTIES(const PROPERTIES &);
    PROPERTIES &operator=(const PROPERTIES &);
    ~PROPERTIES();

public:
    const static Property<vector<pair<Node *, Node *>>> CYCLE; // reversed edges: vector<pair<Node *, Node *>> source -> target
    const static Property<bool> CLEAN_SPL;                     // bool
    const static Property<bool> CLEAN_DFF;                     // bool
    const static Property<vector<vector<Node *>>> LAYERS;      // vector<vector<Node*>>
    const static Property<bool> PATH_BALANCED;                 // bool
    const static Property<bool> EQ;                            // bool
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

class MapProperty
{

private:
    /** map of property identifiers to their values. */
    std::unordered_map<PropertyInterface, std::shared_ptr<FieldInterface>> properties;

public:
    void setProperty(const PropertyInterface &property, const std::shared_ptr<FieldInterface> &value)
    {
        if (value == nullptr)
        {
            this->properties.erase(property);
        }
        else
        {
            this->properties[property] = value;
        }
    }

    std::shared_ptr<FieldInterface> &getProperty(const PropertyInterface &property)
    {
        if (!hasProperty(property))
        {
            string &name = const_cast<string &>(property.get_name());
            if ()
                setProperty(property, make_shared<FieldInterface>(dynamic_cast<Property<>>(property).get_default()));
        }
        return properties[property];
    }

    bool hasProperty(const PropertyInterface &property)
    {
        return properties.find(property) != properties.end();
    }

    /**
     * @return the property map, creating a new map if there hasn't been one so far.
     */
    std::unordered_map<PropertyInterface, std::shared_ptr<FieldInterface>> &getProperties()
    {
        return properties;
    }
};
