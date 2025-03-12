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


### C++のキャストについて
static_cast, dynamic_cast, constt_cast, reinterpret_castの4種類存在する。
- static_cast
  - 型変換を明示的に行う。必要があれば値を変化させる。
    ```cpp
    double dx = 3.14;
    int x = static_cast<int>(dx);  // 3
    ```
  - 列挙型と数値型の変換など、暗黙的に変換されない変換も行える。
- dynamic_cast
  - ダウンキャストというものについて書かれていたが、よく理解できなかった。
- const_cast
  - const修飾子を外すために用いる
    ```cpp
    const std::string str("hoge");
    std::string& x = const_cast<std::string&>(str);
    ```
  - そもそもconstをつけているので、用いるべきではない
- reinterpret_cast
  - 値はそのままで、型情報の変換を行うキャスト
  - 安全じゃないらしい。
  - バイナリーデータの読み書きで用いられる

- 参照
  - [c++のキャストについて](https://rinatz.github.io/cpp-book/ch08-01-cpp-casts/)
  - [ダウンキャスト](https://rinatz.github.io/cpp-book/appendix-downcasts/)


### Makefileについて
- Makeに必要な情報
  - コンパイラ: `CC = g++`
  - コンパイルオプション: `CFLAGS = `
  - 実行ファイル名: `TARGET = exe`
  - コンパイル対象のソースコード: `SRCS = main.cpp ...`
  - オブジェクトファイル名: `OBJS = $(SRCS:.cpp=.o)`
  - includeファイルのあるディレクトリパス: `INCDIR = -I../inc`
- ターゲットの生成
  - ターゲットファイルの生成:
    ```make
    $(TARGET): $(OBJS)
        $(CC) -o $@ $^ $(LIBDIR) $(LIBS)
    ```
  - オブジェクトファイルの生成:
    ```make
    $(OBJS): $(SRCS)
        $(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)
    ```
- Make実行オプション
  - make all として、clean -> makeを同時に行えるコマンドを作れる
  - `make clean`: 


- 最低限の文法
    ```make
    <target>: <pre-requisite>
        <command>
    ```
    は次のような動作をする。
    - targetが呼ばれたとき、まず前提条件pre-requisiteのターゲットを実行する
    - その後、targetファイルがない、または前提条件のファイルよりタイムスタンプが古い場合にcommandを実行する
    - targetファイルがあり、かつ前提条件のファイルよりタイムスタンプが新しい場合は何もしない
    - 

- 参照
  - [Makefileの書き方(初心者向け)](https://qiita.com/yagiyuki/items/ff343d381d9477e89f3b)
  - [ついにッ！最強のMakefileが完成したぞッッッ！！！](https://qiita.com/harinez2/items/0d25eabdc6dae66e7bee)


### const修飾子について
const修飾子は、"値が不変である"ことを示す修飾子であるが、ポインタ変数に対して指定する場合に混乱しやすい。
- 変数に対してconst指定する場合
  ```cpp
  const int a = 10;
  int const a = 10;
  ```
  - どちらも同じ意味で、書き換えができなくなる。
- ポインタ変数に対してconst指定する場合
  ```cpp
  const int *p = &a; //pを介して、aの書き換えができない。pの参照先を別にすることは可能
  int const *p = &a; // 同上
  int* const p = &a; // pの参照先を変更できない。pを介してaを変更することはできる
  ```
  ```cpp
        int       *       p = &a;    // 通常のポインタ変数
  // ------------------------------------------------------------ //
  const int       *       p = &a;    // p を介した a の書き換えを禁止.
        int const *       p = &a;    // 同上
  // ------------------------------------------------------------ //
        int       * const p = &a;    // p の参照先の変更を禁止.
  // ------------------------------------------------------------ //
  const int       * const p = &a;    // p を介した a の書き換えと p の参照先の変更をどちらも禁止.
        int const * const p = &a;    // 同上
  ```
  - `const int`と`int const`はどちらも、"不変なint型”という意味を表す
  - `const * p`は、pの中身をロックしている
  - `* const p`は、pの参照をロックしている

- 参照
  - [C++のconst修飾子の位置で混乱しないために](https://annpin.com/posts/18/03/27/c-cpp-const/)


### constメンバ関数まとめ
- constメンバ関数とは
  - 引数の後にconstが明記されたメンバ関数
  ```cpp
  class Hito {
  private:
    int age = 10;
  public:
    void output_age() const { // <- constメンバ関数
      std::cout << age << std::endl; 
    }
    void grow_a_year_older() {
      age++;
    } 
  }
  ```
  - 関数内でメンバ変数を更新しないことを明示的に指定できる。
  - 書き換えをしようとすると、エラーが起きる(おそらく)
- 関数内でメンバ変数を使わない場合はstatic関数にした方が良い

- 参照
  - [c++ constメンバ関数まとめ](https://qiita.com/hhgghhh/items/e44c384561ca159d6411)


### クラスのメンバ変数の初期化
**メンバ変数はメンバ初期化リストを使って初期化するべきである**

```cpp
class Person {
 public:
  explicit Person(const std::string &name, const int &age);
  explicit Person();

 private:
  std::string name_;
  int         age_;
};
```
上のPersonクラスを使う際に、下のように代入によって初期化できる。
```cpp
Person::Person(const std::string &name, const int &age) {
  name_ = name;                 // 代入であって初期化でない
  age_ = age;                   // 代入であって初期化でない
}
```
だが、代入前に初期化は行われないかもしれない。
以下のようにして、**メンバ初期化リスト**を使って初期化できる。
```cpp
Person::Person(const std::string &name, const int &age)
 : name_(name), 
   age_(age)
   {}
```
この方法だと、const変数にも引数の値で初期化できる。


- 参考
  - [Effective C++ 第3版 - 4項　オブジェクトは、使う前に初期化しよう](https://qiita.com/eierapfel/items/5bdfe625a439bc6c0670)