#ifndef ARRAYOPERATE_H
#define ARRAYOPERATE_H
#include<string>
#include<vector>
#include <string>
#include <vector>
template <class T>
int lengthofarray(T &array)/*lengthofarray函数，求数组长度*/
{
return sizeof(array) / sizeof(array[0]);
}

template <class U,class V>
int findindex(U &array,V element)/*findindex函数，查找指定元素在容器中的索引值，返回-1即为无法找到索引*/
{
    int index = -1; 
    for(int ii = 0; ii != lengthofarray(array); ii++)
    {
        if (array[ii] == element)
        {
            index = ii; 
            break;
        }
        
    }
    return index; 
}
#endif
