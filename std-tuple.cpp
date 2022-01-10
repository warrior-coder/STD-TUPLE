#include <iostream>

using std::cout;
using std::endl;



/*
tuple – реализует кортеж (упорядоченный набор фиксированной длины), экземпляры которого содержат объекты различных типов
благодаря variadic templates кортеж допускает неограниченное количество элементов

реализация запутана из-за синтаксиса шаблонов, но обычно присутствуют следующие элементы:
  цепочка классов с головными и хвостовыми элементами
  пустой экземпляр хвоста, определяющий конец цепочки наследования
  рекурсивный код для обращения к определенному индексу

скорость доступа к элементам в run-time составляет O(1), т.к. вывод шаблонов происходит на этапе компиляции
*/



/*
посредник для конечного класса, который имеет дополнительный параметр шаблона i
описание шаблона
*/
template<int i, typename... Args>
class tuple;


/*
базовый класс: специализация пустого tuple
нужен для завершения цепочки наследования
*/
template<int i>
class tuple<i> {};


/*
рекурсивная специализация
This позволяет выделить элемент val среди пакета
*/
template<int i, typename This, typename... Rest>
class tuple<i, This, Rest...> : public tuple<i + 1, Rest...>
{
    This val;

public:
    tuple() = default;
    tuple(This val, Rest... rest) : tuple<i + 1, Rest...>(rest...), val(val) {}

    template<int i, typename This, typename... Rest>
    friend This& get(tuple<i, This, Rest...>&);
};


/*
возвращает ссылку на i элемент в кортеже
параметр шаблона i позволяет get() находить val за время O(1), (т.к. вывод шаблонов происходит на этапе компиляции)
*/
template<int i, typename This, typename... Rest>
This& get(tuple<i, This, Rest...>& tpl)
{
    return tpl.val;
}


/*
используем псевдоним шаблона, чтобы каждый раз не указывать i = 0
*/
template<typename... Args>
using tuple_t = tuple<0, Args...>;



int main()
{
    /* tuple_t */
    tuple_t<int, double, const char*> tpl(1, 0.2, "333");
    
    get<1>(tpl) = 0.02;

    cout << get<0>(tpl) << endl; // 1
    cout << get<1>(tpl) << endl; // 0.02
    cout << get<2>(tpl) << endl; // 333
    

    return 0;
}