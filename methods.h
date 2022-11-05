#ifndef METHODS_H
#define METHODS_H

#include <QVector>



class methods
{
public:
    methods();

    template<typename T>
    static bool searchElement(QVector<T> vector, T element)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            if (element == vector[i])
                return true;
        }
        return false;
    }

};

#endif // METHODS_H
