#ifndef _MAP_PROPERTY_H_
#define _MAP_PROPERTY_H_

#include <string>
#include <ctime>
#include <memory>
#include <typeinfo>
#include <unordered_map>
#include <malloc.h>

using namespace std;

class PropertyInterface
{
protected:
    const time_t id;
    /** name of this property. */
    const string name;

public:
    PropertyInterface(const string &_name) : id(time(nullptr)), name(_name){};

    virtual ~PropertyInterface() = default;

    /**
     * @return the id of this property.
     */
    virtual const time_t &get_id() const final
    {
        return this->id;
    }
    /**
     * @return the name of this property.
     */
    virtual const string &get_name() const final
    {
        return this->name;
    }
    virtual bool operator<(const PropertyInterface &p) const
    {
        return this->name == p.name ? this->id < p.id : this->name < p.name;
    }
    virtual bool operator==(const PropertyInterface &p) const
    {
        return this->name == p.name && this->id == p.id;
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
    const T &get_default() const
    {
        return this->default_val;
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
    Field() = default;
    Field(const T &val_) : val(val_){};
    ~Field() = default;
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
            PropertyInterface &_key = const_cast<PropertyInterface &>(key);
            return hash<string>()(_key.get_name()) ^ hash<time_t>()(_key.get_id());
        }
    };
}; // namespace std

class MapProperty
{
private:
    /** map of property identifiers to their values. */
    std::unordered_map<PropertyInterface, std::shared_ptr<FieldInterface>> properties;

public:
    MapProperty() = default;
    virtual ~MapProperty()
    {
        this->removeAllProperties();
    }
    /**
     * set the value of the property.
     * if the value is null, remove the property form this->properties.
     */
    template <typename T = bool>
    void setProperty(const Property<T> &property, const T &value)
    {
        if (typeid(value) == typeid(nullptr))
        {
            this->removeProperty(property);
        }
        else
        {
            this->properties[dynamic_cast<const PropertyInterface &>(property)] = dynamic_pointer_cast<FieldInterface>(make_shared<Field<T>>(value));
        }
    }
    /**
     * remove the property form this->properties if it exists.
     */
    template <typename T>
    void removeProperty(const Property<T> &property)
    {
        if (this->hasProperty<T>(property))
        {
            this->properties.erase(dynamic_cast<const PropertyInterface &>(property));
        }
    }
    /**
     * @return the value of the property.
     * if the property does not exist, return it's default value.
     */
    template <typename T>
    T &getProperty(const Property<T> &property)
    {

        if (!this->hasProperty<T>(property))
        {
            this->setProperty<T>(property, property.get_default());
        }
        return dynamic_pointer_cast<Field<T>>(this->properties.at(dynamic_cast<const PropertyInterface &>(property)))->get_value();
    }
    /**
     * @return determine if the property exists in this->properties.
     */
    template <typename T>
    bool hasProperty(const Property<T> &property) const
    {
        return this->properties.find(dynamic_cast<const PropertyInterface &>(property)) != this->properties.end();
    }

    /**
     * @return this->properties.
     */
    unordered_map<PropertyInterface, std::shared_ptr<FieldInterface>> &getProperties()
    {
        return this->properties;
    }

    /**
     * @return this->properties.
     */
    void removeAllProperties()
    {
        this->properties.clear();
        malloc_trim(0);
    }
};

#endif