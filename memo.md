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

## overflow (桁あふれ) ##
値がその方で表現できる範囲を超えること。日本語では桁あふれや範囲超過と呼ぶ。
一般的な 32 ビット int の最大値は以下。
```text
2147483647
```
これを超える計算をするとオーバーフローが発生する。 c++ では符号付整数のオーバーフローは未定義動作。

## strtol の挙動 ##
```c++
#include <cstdlib>
long std::strtol(
    const char* str,
    char** endptr,
    int base
);
```
str: 変換したい文字列
endptr: 変換が終了した位置を受け取る
base: 何進数として解釈するか。
## c_str の挙動 ##
```c++
std::string str = "12345"
const char* ptr = str.c_str();
```
std::string の内容を C 言語形式の文字列(ヌル終端文字列) として参照するための関数

## std::fixed << std::setprecision(1) ##
小数点以下を必ず 1 桁表示するということを表す。
std::fixed は浮動小数点数を固定小数点表記で表す。
std::setprecision は入出力ストリームで浮動小数点型の桁数を指定出来るマニピュレータです。


> fixed で小数点以下だよと教えてあげる。 setprecision で小数点以下の長さを指定してあげる。

<https://qiita.com/ryupim/items/1cbeb860d4a2f056358a>

## std::floor の挙動 ##
浮動小数点数をその値以下で最大の整数値へ切下げる関数。
<cmath> が必要
