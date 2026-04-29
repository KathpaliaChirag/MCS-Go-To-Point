

## **Data Visibility and State Table**

This table clarifies exactly who knows what and in what mathematical form. It’s the "Security Map" of the protocol.

| Component | Mathematical Symbol | Visibility | Format |
| :--- | :--- | :--- | :--- |
| **Circuit Logic** | $L, R, O$ | **Public** | Plaintext Matrices |
| **Public Inputs** | $y$ (e.g., $14$) | **Public** | Plaintext Scalars |
| **Secret Witness** | $x, v_1$ (e.g., $3, 9$) | **Prover Only** | Plaintext Scalars |
| **Target Polynomial**| $Z(x)$ | **Public** | Plaintext Polynomial |
| **Toxic Waste** | $\tau, \alpha, \beta, \gamma, \delta$ | **Destroyed** | Plaintext Scalars (Post-MPC) |
| **Proving Key** | CRS ($G^{A(\tau)}, etc.$) | **Public** | **Encrypted** (EC Points) |
| **The Proof** | $\pi = (A, B, C)$ | **Public** | **Encrypted** (EC Points) |

---

## **The Efficiency Engine: Why FFT Matters**



### **The $O(n^2)$ Bottleneck (Naive Evaluation)**
Imagine you have a polynomial with $n$ coefficients:  
$$f(x) = a_0 + a_1x + a_2x^2 \dots + a_{n-1}x^{n-1}$$

You want to find its value at $n$ different points ($x_0, x_1, \dots, x_{n-1}$).
* **For ONE point ($x_0$):** You have to plug $x_0$ into every term. That’s roughly $n$ multiplications.
* **For ALL $n$ points:** You repeat that process $n$ times.
* **Total Complexity:** $n \text{ points} \times n \text{ operations per point} = \mathbf{n^2}$.

### **The $n \log n$ Shortcut (The FFT Symmetry)**
To break this bottleneck, we use **Roots of Unity**. Let's use 4 points ($n=4$): $1, i, -1, -i$.  
Notice their squares:
* $(1)^2 = \mathbf{1}$
* $(-1)^2 = \mathbf{1}$
* $(i)^2 = \mathbf{-1}$
* $(-i)^2 = \mathbf{-1}$

**The Symmetry:** Four distinct points $(1, -1, i, -i)$ collapsed into only **two** distinct squared values $(1, -1)$.



### **The Divide and Conquer**
We split $f(x)$ into even and odd powers:
$$f(x) = \text{Even}(x^2) + x \cdot \text{Odd}(x^2)$$

By using the symmetry above, evaluating $f(1)$ and $f(-1)$ only requires us to calculate $\text{Even}(1)$ and $\text{Odd}(1)$ **once**. 
* $f(1) = \text{Even}(1) + \text{Odd}(1)$
* $f(-1) = \text{Even}(1) - \text{Odd}(1)$

Mathematically, this recurrence relation ($T(n) = 2T(n/2) + n$) solves to **$O(n \log n)$**.

---

## **Deep Dive: The Bilinear Pairing "Cheat Sheet"**

If a student asks how the Verifier "multiplies" encrypted points, refer to this:

* **Property:** $e(P^a, Q^b) = e(P, Q)^{ab}$
* **The "Bridge":** It moves exponents from the Elliptic Curve (where you can only add) into a Target Group (where they are multiplied).
* **The Constraint:** You can only use a pairing **once** per proof check. You cannot "re-pair" the output. This is why Groth16 is restricted to Quadratic Arithmetic Programs (degree-2 math).

---
