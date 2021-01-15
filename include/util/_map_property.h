#ifndef _MAP_PROPERTY_H_
#define _MAP_PROPERTY_H_

#include <string>
#include <ctime>
#include <memory>
#include <typeinfo>
#include <unordered_map>

using namespace std;

class PropertyInterface
{
protected:
    /** name of this property. */
    const string name;

public:
    PropertyInterface(const string &_name) : name(_name){};

    virtual ~PropertyInterface() = default;

    virtual const string &get_name()
    {
        return this->name;
    }
    virtual bool operator<(const PropertyInterface &p) const
    {
        return this->name < p.name;
    }
    virtual bool operator==(const PropertyInterface &p) const
    {
        return this->name == p.name;
    }
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
    Property(const string &_name) : PropertyInterface(_name) {}

    /**
     * Creates a property with given name and default value.
     * 
     * @param _name the name
     * @param _default_val the default value
     */
    Property(const string &_name, const T &_default_val) : PropertyInterface(_name), default_val(_default_val) {}

    /**
     * @return the default value of this property.
     */
    const T &get_default()
    {
        return this->default_val;
    }

    /**
     * @return the name of this property.
     */
    const string &get_name()
    {
        return this->name;
    }
};

class FieldInterface
{
protected:
    size_t type;

public:
    FieldInterface() = default;
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

namespace std
{
    template <> //function-template-specialization
    class hash<PropertyInterface>
    {
    public:
        size_t operator()(const PropertyInterface &key) const
        {
            string _name = const_cast<PropertyInterface &>(key).get_name();
            return hash<string>()(_name) ^ hash<long int>()(time(0));
        }
    };
}; // namespace std

class MapProperty
{

protected:
    /** map of property identifiers to their values. */
    unordered_map<PropertyInterface, std::shared_ptr<FieldInterface>> properties;

public:
    MapProperty() = default;
    virtual ~MapProperty() = default;
    /**
     * set the value of the property.
     * if the value is null, remove the property.
     */
    template <typename T = bool>
    void setProperty(const Property<T> &property, const Field<T> &value)
    {
        this->properties[dynamic_cast<PropertyInterface &>(const_cast<Property<T> &>(property))] = dynamic_pointer_cast<FieldInterface>(make_shared<Field<T>>(value));
    }

    template <typename T>
    void removeProperty(const Property<T> &property)
    {
        if (this->hasProperty<T>(property))
        {
            this->properties.erase(dynamic_cast<PropertyInterface &>(const_cast<Property<T> &>(property)));
        }
    }

    template <typename T>
    std::shared_ptr<FieldInterface> getProperty(const Property<T> &property)
    {
        auto _property = dynamic_cast<PropertyInterface &>(const_cast<Property<T> &>(property));
        if (!this->hasProperty<T>(property))
        {
            this->setProperty<T>(property, Field<T>(const_cast<Property<T> &>(property).get_default()));
        }
        return properties[_property];
    }

    template <typename T>
    bool hasProperty(const Property<T> &property)
    {
        return this->properties.find(dynamic_cast<PropertyInterface &>(const_cast<Property<T> &>(property))) != this->properties.end();
    }

    /**
     * @return the property map, creating a new map if there hasn't been one so far.
     */
    unordered_map<PropertyInterface, std::shared_ptr<FieldInterface>> &getProperties()
    {
        return this->properties;
    }
};

#endif