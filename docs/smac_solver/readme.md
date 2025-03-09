# SMAC法による二次元ナビエストークス方程式の時間発展

## 無次元化された非圧縮二次元ナビエストークス方程式

![2d_ns_eq_u](https://latex.codecogs.com/svg.image?\frac{\partial&space;u}{\partial&space;t}&plus;\frac{\partial(uu)}{\partial&space;x}&plus;\frac{\partial(vu)}{\partial&space;y}=-\frac{\partial&space;p}{\partial&space;x}&plus;\frac{1}{\mathrm{Re}}\left(\frac{\partial^2&space;u}{\partial&space;x^2}&plus;\frac{\partial^2&space;u}{\partial&space;y^2}\right))

![2d_ns_eq_v](https://latex.codecogs.com/svg.image?\frac{\partial&space;v}{\partial&space;t}&plus;\frac{\partial(uv)}{\partial&space;x}&plus;\frac{\partial(vv)}{\partial&space;y}=-\frac{\partial&space;p}{\partial&space;y}&plus;\frac{1}{\mathrm{Re}}\left(\frac{\partial^2&space;v}{\partial&space;x^2}&plus;\frac{\partial^2&space;v}{\partial&space;y^2}\right))


## SMAC法の概要
SMAC法とは、圧力を陰的に扱って時間発展させる方法である。

式を簡便にするためにベクトル形式で書き、次のように時間の離散化を行う。

![ns_vector](https://latex.codecogs.com/svg.image?\frac{\Delta\mathbf{u}}{\Delta&space;t}=-(\mathbf{u}\cdot\nabla)\mathbf{u}-\nabla&space;p&plus;\frac{1}{\mathrm{Re}}\nabla^2\mathbf{u}=\mathbf{f}(\mathbf{u},p))

ここで、$n+1$ステップ目の速度場$\mathbf{u}^{(n+1)}$を求める際に、$n$ステップ目の速度場$\mathbf{u}^{(n)}$と$n+1$ステップ目の圧力場$p^{(n+1)}$を用いたい。すなわち、

![ns_semi_implicit_n+1](https://latex.codecogs.com/svg.image?\mathbf{u}^{(n&plus;1)}=\mathbf{u}^{(n)}&plus;\Delta&space;t\mathbf{f}(\mathbf{u}^{(n)},p^{(n&plus;1)}))

となる。$p^{(n+1)}$を求めるために、$p^{(n)}$を用いて速度場の中間予測値$\mathbf{u^{*}}$を求めると、

![ns_semi_implicit_star](https://latex.codecogs.com/svg.image?\mathbf{u}^{*}=\mathbf{u}^{(n)}&plus;\Delta&space;t\mathbf{f}(\mathbf{u}^{(n)},p^{(n)}))

となる。こららの差を取ると、

![smac_modify_term](https://latex.codecogs.com/svg.image?\mathbf{u}^{(n&plus;1)}-\mathbf{u}^{*}=-\Delta&space;t\nabla(p^{(n&plus;1)}-p^{(n)}))

となり、圧力の変化量が現れる。$\mathbf{u}^{(n+1)}$は連続の式を満たすため、この式の発散を取ると、

![smac_deltap_poisson](https://latex.codecogs.com/svg.image?\frac{\nabla\cdot\mathbf{u}^{*}}{\Delta&space;t}=\nabla^2\delta&space;p&space;)

が得られる。


## 時間について離散化
これを時間について離散化する。その際、第nステップ目の$u^{(n)}, v^{(n)}, p^{(n)}$を用いて、$u^*, v^*$を予測する。


![time_discretize_u_2](https://latex.codecogs.com/svg.image?&space;u^*=u^{(n)}&plus;\Delta&space;t\left(\mathrm{AdvectionTerm_u}&plus;\mathrm{PressureTerm_u}&plus;\mathrm{ViscosityTerm_u}\right))

![time_discretize_v_2](https://latex.codecogs.com/svg.image?&space;v^*=v^{(n)}&plus;\Delta&space;t\left(\mathrm{AdvectionTerm_v}&plus;\mathrm{PressureTerm_v}&plus;\mathrm{ViscosityTerm_v}\right))



## 参考
- [粘性流体の非定常流れの数値解析アルゴリズム](https://www.kurims.kyoto-u.ac.jp/~kyodo/kokyuroku/contents/pdf/0548-07.pdf)