[TOC]

## 概要
c++に関して、知らない概念や、よく理解していない概念、便利だと思ったスキルをメモする文書。
できるだけ具体例を交えて理解するように心がける。もし、コードを実行した際には、そのリンクを貼ること。
調べ物をした際には、そのwebリンクを貼ること。

## 本編
### namespaceってなに？
namespace, 名前空間とは、名前(変数名、クラス名とか？)の衝突を避けるために必要なもの。
この中で書かれた名前にアクセスするには、名前空間の修飾をつけなければいけない。スコープ解決演算子`::`を用いる。
```cpp
namespace A
{
    void f(){std::cout << "A" << std::endl;};
    void hoge(){
        f();
    }
}
namespace B
{
    void f(){std::cout << "B" << std::endl;};
    void hoge(){
        A::f();
    }
}

int main(){
    A::f();
    B::f();
    A::hoge();
    B::hoge();
}
```
このようにして、`f()`などの汎用性の高い名前を区別することができる。
- 参照
  - [namespaceの賢い使い方](https://qiita.com/_EnumHack/items/430da105a541f9ecd774)


### ヘッダファイルの使い方と用途
**ヘッダファイルは開けておくべきスペースを他のオブジェクトファイルに教えることが役割**
クラスの変数やメンバ関数の定義をヘッダーファイルに書き、関数の処理内容をソースファイルに書くことで、定義と処理を分けて視認しやすくできる。
あるソースファイルがあるヘッダファイルをincludeした後に、別のソースファイルが同じヘッダをincludeすると、同じ宣言を２回行うことになってしまう。一つのヘッダは一回しかincludeできない。
```cpp
#ifdef C_HPP
#define C_HPP

class c
{
    private:
    int m_value;

    public:
    int get();
    void set( int value );
};

#endif // C_HPP
```
- `#ifndef`, `#endif`: 同じ記号定数を複数回定義しないようにする擬似命令。
    ```cpp
    #ifndef simbol
    #define simbol

    ...

    #endif
    ```
    とすることで、同じヘッダが重複して定義されることを回避できる。
```cpp
#include "c.hpp"

int c::get()
{
    return m_value;
}

void c::set( int const value )
{
    m_value = value;
}
```

しかし、このやり方だと処理速度が遅い。
-> 関数の定義を再度ヘッダに戻す

```cpp
#ifdef C_HPP
#define C_HPP

class c
{
    private:
    int m_value;

    public:
    int get();
    void set( int value );
};

inline int c::get()
{
    return m_value;
}

inline void c::set( int const value )
{
    m_value = value;
}

#endif // C_HPP
```
前半でクラスの定義を行い、後半で`inline`指定子をつけてメンバ関数の定義を行う。
- `inline`指定子: メンバ関数が呼び出された際、処理内容を呼び出し元に展開して処理する。＝同じファイルに記述されたときと同等の速度で処理される。
基本的に、長い関数はソースファイルに書くべきである。

- 参照
  - [ヘッダファイルの書き方](https://qiita.com/MoriokaReimen/items/7c83ebd0fbae44d8532d)
  - [c++でヘッダとソースでファイルを分ける　基本編](https://qiita.com/agate-pris/items/1b29726935f0b6e75768)


### 戻り値の型と後置修飾
```cpp
const std::vector<double>& getXc() const;
```
- 先頭の`const`は読み取り専用を示す
- 型のケツについている`&`は参照型戻り値を示す。参照を戻すため、新たにメモリを確保しない。
  - 参照型とポインタ型の違いは何？
- 最後の`const`は、この関数がメンバ変数を変更しないことを保証している。


### 参照型とポインタ型の違い
- ポインタ型: 
  - 変数のアドレスを値として持つ型
  - `int* ip;`: `ip`はアドレスの値を持った変数
    ```cpp
    int i;
    int* ip = &i; //ipにiのアドレスを渡す
    int i2 = *ip //i2にipの中身を代入
    ```
- 参照型: 
  - 参照型もポインタ型と同じくアドレスを値に持つ型である。
  - しかし、参照型は初期化時以外は参照先を変更することができない。
  - = constポインタ型のようなイメージ
    ```cpp
    int i;
    int& ref = i; //refにiのアドレスを渡す。この時、&iとする必要はない。
    int i2 = ref; //i2をrefのアドレス参照する変数とする
    ```

- 参照
  - [c++初心者が躓く「値型、ポインタ型、参照型」](https://qiita.com/0htaka/items/abc0671455ec4ea8b0fc)