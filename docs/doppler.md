## Definitions

$$
\begin{aligned}
&\hat{n}         &&\text{- unit vector of camera movement} \\
&\beta_r         &&\text{- camera speed as a fraction of } c \\
&\bar{\beta}_r = \beta_r\hat{n} &&\text{- camera velocity} \\
&\gamma          &&\text{- Lorentz factor, } 1/\sqrt{1-\beta_r^2} \\
&\hat{p}         &&\text{- photon propagation direction} \\
&\hat{d} = -\hat{p} &&\text{- traced ray direction, camera to source} \\
&a_p = \langle \hat{p}, \hat{n}\rangle, \quad a_d = \langle \hat{d}, \hat{n}\rangle &&\text{- cosines with the direction of motion} \\
&T,\ T'          &&\text{- emitted and observed period} \\
&D = T/T'        &&\text{- Doppler factor} \\
&x,\ t           &&\text{- lab frame coordinates} \\
&x',\ t'         &&\text{- camera frame coordinates} \\
&[\ \cdot\ ]     &&\text{- substitution used at this step}
\end{aligned}
$$

## Setting
Considering light to be a wave, it must be affected by a doppler shift. If you move away from wave, its period lengthens; other direction - shortens. However to properly demonstrate that, we need to derive correct relation ourselves.

Consider a plane with $x$ axis for space and $t$ axis for time. Light emitter stays still (lab frame), while camera frame moves away from it with speed $\beta _ r$. To use SR formulas easily, we can state that emitter emits two short light flashes with period $T$ between them. 

Difference in time between those two is $\Delta t _ {out}$. Camera frame was moving away from it, and got two signals with time difference of $\Delta t' _ {in}$. Therefore the whole initial system is:

$$
\begin{aligned}
&\Delta t _ {out} = T \\
&\Delta x _ {out} = 0 \\
&\Delta x' _ {in} = 0 \quad &&\text{- both signals arrive at the same point of the camera frame} \\
&l \quad &&\text{- distance between camera and emitter at } t=0 \\
&x_{cam}(t) = l + t\beta _ r
\end{aligned}
$$

The plan is to find $\Delta x _ {in}$ and $\Delta t _ {in}$, and then find $\Delta t' _ {in}$ via interval invariance. $\Delta t' _ {in}$ is exactly $T'$ - the period perceived in camera frame, while $\frac{T}{T'}$ is a Doppler factor.

After that, by introducing angle and vectors we will find a Doppler factor relation suitable for ray tracer.

## 2D scenario - $x$ and $t$ axis
Using spacetime interval invariance $\Delta \tau _ {in} ^ 2 = (\Delta t' _ {in})^2 - (\Delta x' _ {in})^2 = \Delta t _ {in} ^2 - \Delta x _ {in} ^ 2$:

$$
\begin{aligned}
(\Delta t' _ {in})^2 &= \Delta t _ {in} ^2 - \Delta x _ {in} ^ 2 = \\
&= [\Delta x _ {in} = \beta _ r \Delta t _ {in}] = \\
&= \Delta t _ {in} ^ 2 - \beta _ r ^ 2 \Delta t _ {in} ^ 2 = \\
&= \Delta t _ {in} ^ 2 (1 - \beta _ r ^ 2) \\ 
\Delta t' _ {in} &= \frac{\Delta t _ {in}}{\gamma}, \quad \gamma = \frac{1}{\sqrt{1-\beta _ r ^ 2}}
\end{aligned}
$$

$\Delta t _ {in}$ can be found using intersections of the photon and camera worldlines:

$$
\begin{aligned}
& &&\text{signal 1} &&&\text{signal 2} \\
&\text{photon} &&x=t &&&x=t-T \\
&\text{camera} &&x=l+t\beta _ r &&&x=l+t\beta _ r
\end{aligned}
$$

Solving for reception time:

$$
\begin{aligned}
&\text{signal 1} &&\text{signal 2} \\
&t=l + t\beta _ r &&t - T = l + t\beta _ r \\
&t - t\beta _ r = l &&t - t\beta _ r = l + T \\
&t(1-\beta _ r)=l &&t(1-\beta _ r)=l + T \\
&t = \frac{l}{1-\beta _ r} &&t = \frac{l + T}{1-\beta _ r} \\
\end{aligned}
$$

Therefore difference between them is

$$
\begin{aligned}
&\Delta t _ {in} = \frac{l + T}{1-\beta _ r} - \frac{l}{1-\beta _ r} = \frac{T}{1-\beta _ r}.
\end{aligned}
$$

And finally solving for a $\Delta t' _ {in}$:

$$
\begin{aligned}
\Delta t' _ {in} &= \frac{T}{\gamma (1-\beta _ r)} = \\
&= \frac{T}{1-\beta _ r}\sqrt{1-\beta _ r ^ 2} = \\
&= T\frac{\sqrt{1-\beta _ r}\sqrt{1+\beta _ r}}{1-\beta _ r} = \\
&= T\sqrt{\frac{1+\beta _ r} {1-\beta _ r}} = T' \\
\implies \sqrt{\frac{1+\beta _ r}{1-\beta _ r}} &= \frac{T'}{T} = \frac{(1/\nu')}{(1/\nu)} = \frac{\nu}{\nu'} = \frac{1}{D}
\end{aligned} 
$$

where $D$ is a Doppler factor $\sqrt{\frac{1-\beta _ r}{1 + \beta _ r}}$.

Indeed, for $\beta _ r > 0$ period is longer for camera $\implies$ perceived light appears redder; and for $\beta _ r < 0$ period is shorter for camera $\implies$ perceived light appears more blue.

## Vector form
Let $\hat{n}$ be the unit vector of camera movement - the same $\hat{n}$ as in
[aberration.md](./aberration.md) - so that the camera velocity is
$\bar{\beta} _ r = \beta _ r \hat{n}$, and let $\hat{p}$ be the photon propagation
direction. In the one-dimensional case above, $\hat{n}$ played the role of the
$x$ axis.

Their dot product is the cosine of the angle between them, since both are unit:

$$
\begin{aligned}
a_p := \langle \hat{p}, \hat{n} \rangle = \cos{\phi}
\end{aligned}
$$

Decompose the velocity relative to $\hat{p}$:

$$
\begin{aligned}
\bar{\beta} _ \parallel &= \langle \bar{\beta} _ r, \hat{p} \rangle \hat{p}
= \beta_r a _ p \hat{p} \\
\bar{\beta} _ \perp &= \bar{\beta} _ r - \bar{\beta} _ \parallel
\end{aligned}
$$

Distance the second signal has to travel depends on how far camera moved *along* the line of sight:

$$
\begin{aligned}
L(t) &= \sqrt{(l + \beta _ r a _ p t) ^ 2 + (|\bar{\beta} _ \perp|t)^2} =  \\
&= l + \beta _ r a _ p t  + \frac{|\bar{\beta} _ \perp|^2 t^2}{2l} + O\left(\left(\frac{t}{l}\right)^3\right)
\end{aligned}
$$

The transverse component appears only at second order and is divided by $l$. Over one period $t \sim T$, so the term becomes $\frac{|\bar{\beta} _ \perp|^2 t^2}{2l}$, which is negligible against the longitudinal $\beta _ r T a _ p$ whenever $\beta _ r T \ll l$ - that is unless camera sits within a wavelength of the source. In general case we will use one-dimensional result with $\bar{\beta} _ r$, replaced by its projection $\beta _ r a _ p$.

Note that $\gamma$ component in previously derived $\Delta t' _ {in}$ expression does **not** change and retains whole $\beta _ r$ speed. It came from the interval invariance step, where $\Delta x _ {in}$ is the camera's total displacement along its own worldline - the transverse part contributes here just as much as the parallel one.

Using $L(t)$ as one-dimensional $x _ {cam} (t)$ from previous section, the intersection calculation carries over as is, giving

$$
\begin{aligned}
\Delta t _ {in} = \frac{T}{1 - \beta _ r a _ p},
\end{aligned}
$$

therefore:

$$
\begin{aligned}
\Delta t' _ {in} &= \frac{T}{\gamma (1 - \beta _ r a _ p)} = T' \\
\implies \frac{T'}{T} &= \frac{1}{\gamma (1 - \beta _ r a _ p)} = \frac{1}{D}.
\end{aligned}
$$

## What renderer needs
The derivation above transforms the photon's **propagation** direction. A traced ray points the opposite way - from the camera towards the source. A renderer knows $\hat{d}'$, alongside with $\hat{d}$ after aberration. Expanding $a _ p$:

$$
\begin{aligned}
\frac{T'}{T} &= \frac{1}{\gamma (1 - \beta _ r a _ p)} = \\
&= \frac{1}{\gamma (1 - \beta _ r \langle \hat{p}, \hat{n} \rangle)},
\end{aligned}
$$

and then substituting $\hat{p} = -\hat{d}$ we get:

$$
\begin{aligned}
\frac{T'}{T} &= \frac{1}{\gamma (1 + \beta _ r \langle \hat{d}, \hat{n} \rangle)} = \\
&= \frac{1}{\gamma (1 + \beta _ r a _ d)}, \quad a _ d = \langle \hat{d}, \hat{n} \rangle.
\end{aligned} 
$$

Only one sign flip compared to aberration - no $\beta _ r \to -\beta _ r$ substitution is needed. $\frac{T'}{T}$ already **is** the camera-to-source ratio, whereas the aberration derivation had to flip the speed as well. Hence $1 + a_d\beta_r$ here versus $1 - a\beta_r$ there.

## Tests

- $\beta _ r = 0$:

$$
\begin{aligned}
\gamma &= 1 \\
\frac{T'}{T} &= 1
\end{aligned}
$$

No shift.

- $a _ d = 1,\ \beta _ r > 0$ -- camera flies straight at the emitter:

$$
\begin{aligned}
\frac{T'}{T} = \frac{1}{\gamma(1 + \beta _ r)} < 1
\end{aligned}
$$

Period tightens - color is more blue

- $a _ d = -1,\ \beta _ r > 0$ -- camera flies away from the emitter:

$$
\begin{aligned}
\frac{T'}{T} = \frac{1}{\gamma(1 - \beta _ r)} > 1
\end{aligned}
$$

Period stretches - color is more red

- $a_d = 0$ - the ray is perpendicular to the camera's motion, so the source is
seen directly to the side:

$$
\begin{aligned}
\frac{T'}{T} = \frac{1}{\gamma} > 1
\end{aligned}
$$

The period is still stretched even though the source is neither approaching nor receding. This is the transverse Doppler shift, and it has no classical counterpart - it comes purely from time dilation, which is why $\gamma$ was kept at the full speed $\beta_r$ rather than its projection.

## Implementation

[relativity.h](../relativity.h) - `doppler_factor(d, n, beta)`, called from
`ray_color` after the hit is resolved. The wavelength stored on the object is
the emitted one; the observed wavelength is

$$
\begin{aligned}
\lambda_{obs} = \lambda_{emit} \cdot \frac{T'}{T}
\end{aligned}
$$

and only $\lambda_{obs}$ is passed to `wavelength_to_xyz`.

Two things worth restating, since both are easy to get backwards:

- The factor applied in code is $\frac{T'}{T} = \frac{1}{D}$. Wavelength scales with the period, frequency with its inverse.
- $a _ d$ is taken in the **lab** frame - which is exactly what `r.direction` already holds, since `camera::project` applies aberration before the ray is constructed. 

Wavelengths shifted outside the visible range fall to zero naturally: the CIE
fits vanish there, so the object simply goes black. This is correct for a
monochromatic source but not for a real one - see the note on the model's
limits in the README.