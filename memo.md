## 型の復習 ##
cpp で扱う型についてどのような範囲をとるのか
→　厳密にはコンパイラや実行環境によって異なる。
一般的な範囲としては下記
|型|一般的なサイズ | おおよその範囲|
|-----|---------------|----------------------------|
| int | 4 byte | -2147483648 ~ 2147483647|
| float | 4 byte | 約 -3.4028235 × 10^38 ～ 3.4028235 × 10^38|
| double | 8 byte | 約 -1.7976931348623157 × 10^308 ～ 1.7976931348623157 × 10^308 |

```cpp
#include <iostream>
#include <limits>

int main()
{
    std::cout << "int:" << std::endl;
    std::cout << "  lowest: "
              << std::numeric_limits<int>::lowest() << std::endl;
    std::cout << "  max:    "
              << std::numeric_limits<int>::max() << std::endl;

    std::cout << "\nfloat:" << std::endl;
    std::cout << "  lowest: "
              << std::numeric_limits<float>::lowest() << std::endl;
    std::cout << "  min:    "
              << std::numeric_limits<float>::min() << std::endl;
    std::cout << "  max:    "
              << std::numeric_limits<float>::max() << std::endl;
    std::cout << "  digits10: "
              << std::numeric_limits<float>::digits10 << std::endl;

    std::cout << "\ndouble:" << std::endl;
    std::cout << "  lowest: "
              << std::numeric_limits<double>::lowest() << std::endl;
    std::cout << "  min:    "
              << std::numeric_limits<double>::min() << std::endl;
    std::cout << "  max:    "
              << std::numeric_limits<double>::max() << std::endl;
    std::cout << "  digits10: "
              << std::numeric_limits<double>::digits10 << std::endl;
}
```
上記コードにてそれぞれの使用可能な min max を確認することが可能

## 疑似リテラル ##
通常の数値の形ではないものの浮動小数点数の特殊な値を表す文字列のこと。
対象となるのは下記 6 つ
```cpp
nan
nanf
+inf
-inf
+inff
-inff
```

|疑似リテラル|意味|扱う型|
|-----------|----|-----|
| nan | 数値ではない値 | double |
| nanf | 数値ではない値 | float |
| +inf | 正の無限大 | double |
| -inf | 負の無限大 | double |
| +inff | 正の無限大 | float |
| -inff | 負の無限大 | float |

### nan の特性 ###
自分自身とも等しくないという特性を持つ。
例としては次のような演算で発生することがある。
```cpp
0.0 / 0.0
// 下記が成り立つ
double value = /* NaN */;

value == value; // false
value != value; // true
```

