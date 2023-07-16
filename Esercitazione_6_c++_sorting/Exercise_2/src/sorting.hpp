#ifndef __SORTING_H
#define __SORTING_H

#include "iostream"
#include "list"
#include "Eigen/Eigen"
#include "map"

using namespace std;
using namespace Eigen;

namespace SortLibrary {


  struct DecreasingInt
  {
    int value;
    DecreasingInt() = default;
    DecreasingInt(const int& value): value(value){}
  };

  inline ostream &operator<<(ostream &os, const DecreasingInt &obj)
  {
    os << obj.value;
    return os;
  }

  inline bool operator==(const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return obj1.value == obj2.value;
  }

  inline bool operator!=(const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return !(obj1 == obj2);
  }

  inline bool operator < (const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return obj1.value > obj2.value;
  }

  inline bool operator > (const DecreasingInt &obj1, const DecreasingInt &obj2)
  {
    return obj1.value < obj2.value;
  }

  template<typename T>
  vector<T> HeapSort(const vector<T>& v){

    vector<T> temp(v.size());
    T var;
    int s, f;

    temp[0] = v[0];
    for(unsigned int i = 1; i < v.size(); i++)
    {
        temp[i] = v[i];
        s = i;
        f = (i - 1)/2;

        while(temp[s] > temp[f] && f >= 0){
            var = temp[f];
            temp[f] = temp[s];
            temp[s] = var;
            s = f;
            f = (f - 1)/2;
        }
    }

    unsigned int j, l, r;
    bool flag;

    for(unsigned int i = v.size() - 1; i >= 1; i--)
    {
        var = temp[0];
        temp[0] = temp[i];
        temp[i] = var;

        j = 0;
        l = 1;
        r = 2;
        flag = true;
        while(r <= i - 1 && flag)
        {
            if(temp[l] > temp[r] && temp[l] > temp[j]){
                var = temp[j];
                temp[j] = temp[l];
                temp[l] = var;
                j = l;
            }

            else if(temp[l] == temp[r] && temp[l] > temp[j]){
                var = temp[j];
                temp[j] = temp[l];
                temp[l] = var;
                j = l;
            }

            else if(temp[l] < temp[r] && temp[r] > temp[j]){
                var = temp[j];
                temp[j] = temp[r];
                temp[r] = var;
                j = r;
            }

            else
                flag = false;

            l = 2*j + 1;
            r = 2*j + 2;
        }

        if(l == i - 1 && temp[l] > temp[j]){
            var = temp[j];
            temp[j] = temp[l];
            temp[l] = var;
        }
    }

    return temp;
  }

   /// ... and other

}




#endif // __SORTING_H
