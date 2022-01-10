# STD TUPLE

tuple – реализует кортеж (упорядоченный набор фиксированной длины), экземпляры которого содержат объекты различных типов


```CPP
tuple_t<int, double, const char*> tpl(1, 0.2, "333");

get<1>(tpl) = 0.02;

cout << get<0>(tpl) << endl; // 1
cout << get<1>(tpl) << endl; // 0.02
cout << get<2>(tpl) << endl; // 333 
```