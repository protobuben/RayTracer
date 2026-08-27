## Definitions
$$
\begin{aligned}
&\hat{n} &&\text{ - unit camera movement direction} \\
&\beta _ r &&\text{ - relative speed between frames as fraction of } c \\
&x,\ y,\ t &&\text{ - units in lab frame} \\
&x',\ y',\ t' &&\text{ - units in camera frame} \\
&\hat{p}  &&\text{ - photon direction in lab frame} \\
&\hat{p}'  &&\text{ - photon direction in camera frame} \\
&\hat{d}  &&\text{ - ray direction in lab frame} \\
&\hat{d}'  &&\text{ - ray direction in camera frame} \\
\end{aligned}
$$

## Setting
World is still, camera is moving along $\hat{n}$ with speed $\beta _ r$. Pixel registers photon, that propagated along $\hat{p}'$ in the camera frame; the ray traced for that pixel points the opposite way, $\hat{d}'=-\hat{p}'$. The same photon has a different direction in the lab frame, so to find where it came from we need $\hat{d}$. Aberration is this difference between the same event described in two frames - the photon's path is straight in both; its direction differs.

## Scalar derivation
Simpler problem:

derive angle $\phi'$ to $x'$ axis of photon's direction in camera's frame, if in lab's frame it's $\phi$ to $x$

Since the photon's speed equals $\beta _ c=1$, distances traveled along $x$ and $y$ become

$$
\begin{aligned}
\Delta x &= \Delta t\cos{\phi} \\ 
\Delta y &= \Delta t\sin{\phi} = \Delta y'
\end{aligned}
$$

Because boost is along $x$ axis, speed along $y$ doesn't change.

Therefore, via Lorentz transformation formula we can derive:

$$
\begin{aligned}
\Delta x' &= \Delta t(\cos{\phi}\cosh{\theta _ r}-\sinh{\theta _ r}) \\ 
\Delta t' &= \Delta t(\cosh{\theta _ r}-\cos{\phi}\sinh{\theta _ r})
\end{aligned}
$$

where $\beta _ r=\tanh{\theta _ r}$ - relative speed of camera frame.

Since observable object is light, its interval is null

$$
\Delta \tau=0.
$$

Therefore

$$
\begin{aligned}
(\Delta x')^2 + (\Delta y')^2 &= (\Delta t')^2 \\
1 + \left(\frac{\Delta y'}{\Delta x'}\right)^2 &= \left(\frac{\Delta t'}{\Delta x'}\right)^2 \\
1 + \tan^2\phi' &= \left(\frac{\Delta t'}{\Delta x'}\right)^2 \\
\cos^2{\phi'} &= \left(\frac{\Delta x'}{\Delta t'}\right)^2 \\
\cos{\phi'} &= \frac{\Delta x'}{\Delta t'}, \quad \Delta t' > 0 \\
\end{aligned}
$$

And then deriving $\frac{\Delta x'}{\Delta t'}$

$$
\begin{aligned}
\frac{\Delta x'}{\Delta t'} &= \frac{\Delta t(\cos{\phi}\cosh{\theta _ r}-\sinh{\theta _ r})}{\Delta t(\cosh{\theta _ r}-\cos{\phi}\sinh{\theta _ r})} = \\
&= \frac{\cos{\phi}\cosh{\theta _ r}-\sinh{\theta _ r}}{\cosh{\theta _ r}-\cos{\phi}\sinh{\theta _ r}} = \\
&= \left| \beta _ r=\tanh{\theta _ r}=\frac{\sinh{\theta _ r}}{\cosh{\theta _ r}} \implies \sinh{\theta _ r}=\beta _ r \cosh{\theta _ r} \right| = \\
&= \frac{\cos{\phi}\cosh{\theta _ r}-\beta _ r \cosh{\theta _ r}}{\cosh{\theta _ r}-\beta _ r \cos{\phi}\cosh{\theta _ r}} = \\
&= \frac{\cos{\phi}-\beta _ r}{1-\beta _ r \cos{\phi}}
\end{aligned}
$$

we get

$$
\cos{\phi'} = \frac{\cos{\phi}-\beta _ r}{1-\beta _ r \cos{\phi}}.
$$

## Vector form
The scalar result gives the angle to $\hat{n}$ (if we take $\hat{n}$ as $x$ axis), but the renderer requires a vector. Let's decompose photon direction vector $\hat{p}$ into components along and across the motion:

$$
\begin{aligned}
&a _ p := \langle \hat{p}, \hat{n} \rangle \\
&\bar{p} _ \parallel = a _ p\hat{n} \\
&\bar{p} _ \perp = \hat{p}-a _ p\hat{n} \\
\end{aligned}
$$

The boost mixes only $\bar{p} _ \parallel$ with time; $\bar{p} _ \perp$ is untouched, exactly as $y$ in scalar case. Taking $\Delta t = 1$ so that $\Delta x = a _ p$ and the deviating displacement is $\Delta y = \bar{p} _ \perp = \Delta y'$, via same Lorentz transformation we get:

$$
\begin{aligned}
\Delta x' &= a _ p\cosh{\theta _ r}-\sinh{\theta _ r} \\
\Delta t' &= \cosh{\theta _ r}-a _ p\sinh{\theta _ r}.
\end{aligned}
$$

A direction is a displacement per unit time, so dividing spatial part by $\Delta t'$ gives the desired unit vector:

$$
\begin{aligned}
\hat{p}' &= \frac{\Delta x' \hat{n} + \bar{p} _ \perp}{\Delta t'} = \\
&= \frac{(a _ p\cosh{\theta _ r} - \sinh{\theta _ r})\hat{n} + \hat{p} - a _ p\hat{n}}{\cosh{\theta _ r} - a _ p\sinh{\theta _ r}}= \\
&= \left| \sinh{\theta _ r} = \beta _ r\cosh{\theta _ r},\quad \cosh{\theta _ r} = \frac{1}{\sqrt{1-\beta _ r^2}} \right| = \\
&= \frac{(a _ p - \beta _ r)\hat{n} + \sqrt{1-\beta _ r^2}\,(\hat{p} - a _ p\hat{n})}{1 - a _ p\beta _ r}.
\end{aligned}
$$

Note that this has no special case at $\hat{p} \parallel \hat{n}$ - denominator vanishes only at $a _ p=1/\beta _ r$, which is unreachable since a frame's worldline is timelike -- $\beta _ r<1 \implies 1/\beta _ r > 1 \geq a _ p$.

## What renderer needs

The derivation above transforms the photon's **propagation** direction. A traced ray points the opposite way - from the camera towards the source.

Renderer knows $\hat{d}'$ (it's set by the pixel) and needs $\hat{d}$ (lab frame, where the scene is static). Going camera $\to$ lab means the lab moves at $-\beta _ r$ relative to the camera, so the inverse transform is obtained by substituting $\beta _ r \to -\beta _ r$ into the formula above:

$$
\hat{p} = \frac{(a _ {p'} + \beta _ r)\hat{n} + \sqrt{1-\beta _ r^2}\,(\hat{p}' - a _ {p'}\hat{n})}{1 + a _ {p'}\beta _ r}, \quad a _ {p'} = \langle \hat{p}', \hat{n} \rangle
$$

Substituting $\hat{p}' = -\hat{d}'$, hence $a _ {p'} = -a$ with $a = \langle \hat{d}', \hat{n} \rangle$, and negating the result:

$$
\hat{d} = -\hat{p}
= \frac{(a - \beta _ r)\hat{n} + \sqrt{1-\beta _ r^2}\,(\hat{d}' - a\hat{n})}{1 - a\beta _ r}
$$

The two sign flips cancel, so the implemented formula is identical to the forward one. This is worth stating explicitly - substituting $-\beta _ r$ alone without reversing the ray gives aberration in opposite direction.

## Checks

- $\beta _ r = 0$: reduces to 

$$
\hat{d} = a\hat{n} + \hat{d}' - a\hat{n} = \hat{d}'
$$

no aberration;

- $\hat{d}' = \hat{n}$ -- ray along movement direction ($a=1$): gives 

$$
\frac{(1-\beta _ r)\hat{n}}{1-\beta _ r} = \hat{n}
$$

the axis of motion is fixed;

- $a=0$ -- ray perpendicular to camera frame movement direction: gives 

$$
\hat{d} = -\beta  _  r\hat{n} + \sqrt{1-\beta _ r^2}\,\hat{d}'
$$

the lab direction is tilted against the motion, so what the camera sees ahead of it actually lies to the side. Equivalently in scalar case $\cos{\phi} = 0 \implies \cos{\phi'} = -\beta _ r$ -- the whole sky squeezes towards the direction of travel;

- Norm: let $\bar{d}'_\perp = \hat{d}' - a\hat{n}$ be the transverse part of the
incoming ray. It is orthogonal to $\hat{n}$ by construction, so by the
Pythagorean theorem and $|\hat{d}'| = 1$:

$$|\bar{d}'_\perp|^2 = 1 - a^2$$

Then

$$
|\hat{d}|^2 = \frac{(a-\beta _ r)^2 + (1-\beta _ r^2)(1-a^2)}{(1-a\beta _ r)^2}
= \frac{1 - 2a\beta _ r + a^2\beta _ r^2}{(1-a\beta _ r)^2} = 1
$$

Unit vectors stay unit, so no renormalisation is needed after the transform.

## Implementation
[relativity.h](../relativity.h) - `aberrate(d, n, beta)`, called from `camera::project` before the ray is constructed. The scene geometry is unchanged because it lives entirely in the lab frame, where nothing moves.