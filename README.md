# Quantum-Mechanics
量子力学について，プログラミングを交えて学ぶリポジトリ

## シュレーディンガー方程式の離散化
1. 復習
    1. 粒子の位置や運動量は確定値を持たない->波動関数 $\psi (x)$ によって確率分布として記述される．
    2. 物理量は演算子として作用->ある物理量Aを観測するとは，その演算子 $\hat A$ の固有値問題を解くことと同義．
  - $\hat A \psi = a \psi$ が成り立つときのみ，確定した値aが観測できる．

2. シュレーディンガー方程式は時間に依存しない
- 1次元のポテンシャル $V(x)$ 中の粒子を考えると，エネルギー固有状態を求める方程式は以下の通り．

```math
-\frac{\hbar ^2}{2m}\frac{d^2\psi (x)}{dx^2}+V(x)\psi (x) = E\psi (x)
```
- どうやって計算機的に解こう？
- 実は上の方程式は $H\psi = E\psi$ のような固有値問題
  - 左辺の微分演算子とポテンシャル項を合わせてハミルトニアン $\hat H$

3. 空間の離散化(差分法)
- 空間xを刻み幅 $\Delta x$ で離散化-> $\psi (x)$ は配列になる．
- 二階微分を差分近似すると？

```math
\frac{d^2 \psi}{dx^2} \approx \frac{\psi_{i+1}-2\psi_{i}+\psi_{i-1}}{(\Delta x)^2}
```
- これを方程式に代入して，定数項 $\frac{\hbar^2}{2m}$ を省略して整理すると漸化式になる．

```math
-\frac{\psi_{i-1}}{(\Delta x)^2}+(\frac{2}{(\Delta x)^2}+V_{i})\psi_{i}-frac{\psi{i-1}}{(\Delta x)^2}=E\psi_{i}
```
- 行列形式に直せば
```math
\begin{pmatrix} \ddots & \ddots & 0 \\ -1 & 2+v_{i}(\Delta x)^2 & -1 \\ 0 & \ddots & \ddots \end{pmatrix} \begin{pmatrix} \vdots \\ \psi_{i} \\ \vdots \end{pmatrix} = E(\Delta x)^2 \begin{pmatrix} \vdots \\ \psi_{i} \\ \vdots \end{pmatrix}
```

- ベクトル $\psi$ に対して行列 $H$ がかかっている．
- 上の**三重対角行列**をプログラムに実装したい->Create-Hamiltonian
- 条件
  - $\psi (x)->0\le x\le N$
  - $V(x)->xの範囲内で0, それ以外で\infity$
  - ディリクレ境界条件-> $\psi (0)=0$ , $\psi (N)=0$

- ディリクレ境界条件はなぜ必要？
- 方程式:
```math
-\psi_{i-1} + (2 + V)\psi_{i} - \psi_{i+1} = E\psi_{i}
```
- i=1,Nのときにこの境界条件が発動する．
- 本来 $1\le i\le N$ だから，方程式にi=1, Nを代入したときに現れる $\psi_{0}, \psi_{N+1}$ は未知数．
- ディリクレ境界条件はこの未知数を前もって定めておくためのもの．
  - これによって，計算は範囲内のものだけで良い，ということになる．
### 行列の固有値を求めるアルゴリズム

#### べき乗法(Power Iteration)
- n次正方行列の最大固有値と最大固有値に対応する固有ベクトルを計算する．


#### 逆べき乗法(Inverse Power Iteration)

