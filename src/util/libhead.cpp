#include "util/libhead.h"

/* initial */
size_t init_id = 0;

const std::unordered_map<Value, string, EnumClassHash> Const_Str = {
    {L, "1'b0"},
    {H, "1'b1"},
    {X, "1'bx"}};

template <typename T>
Point<T>::Point(const Point<T> &obj)
{
    if (this != &obj)
    {
        x = obj.x;
        y = obj.y;
    }
}

template <typename T>
Point<T> &Point<T>::operator=(const Point<T> &obj)
{
    if (this == &obj)
    {
        x = obj.x;
        y = obj.y;
    }
    return *this;
};

template <typename T>
Point<T> Point<T>::operator+(const Point<T> &a)
{
    return Point<T>(x + a.x, y + a.y);
}

template <typename T>
Point<T> Point<T>::operator-(const Point<T> &a)
{
    return Point<T>(x - a.x, y - a.y);
}

template <typename T>
Point<T> &Point<T>::operator+=(const Point<T> &a)
{
    this->x += a.x;
    this->y += a.y;
    return *this;
}

template <typename T>
Point<T> &Point<T>::operator-=(const Point<T> &a)
{
    this->x -= a.x;
    this->y -= a.y;
    return *this;
}

template <typename T>
bool Point<T>::operator<(const Point<T> &p) const
{
    if (this->x == p.x)
    {
        return this->y < p.y;
    }
    else
    {
        return this->x < p.x;
    }
}

template <typename T>
T Point<T>::getX()
{
    return this->x;
}

template <typename T>
T Point<T>::getY()
{
    return this->y;
}

template <typename T>
void Point<T>::setX(T _x)
{
    this->x = _x;
}

template <typename T>
void Point<T>::setY(T _y)
{
    this->y = _y;
}

template <typename T>
void Point<T>::set(T _x, T _y)
{
    this->x = _x;
    this->y = _y;
}

/**
 * @return the distance from point (0,0).
 */
template <typename T>
T Point<T>::distance()
{
    return sqrt(x * x + y * y);
}

template <typename Q>
ostream &operator<<(ostream &output, const Point<Q> &p)
{
    output << "(" << p.x << "," << p.y << ")" << endl;
    return output;
}