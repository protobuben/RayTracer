## Definitions


$$
\begin{aligned}
&\hat{n}         &&\text{- unit vector of camera movement} \\
&\beta_r         &&\text{- camera speed as a fraction of } c \\
&\gamma          &&\text{- Lorentz factor, } 1/\sqrt{1-\beta_r^2} \\
&\hat{p}         &&\text{- photon propagation direction} \\
&\hat{d} = -\hat{p} &&\text{- traced ray direction, camera to source} \\
&a_p = \langle \hat{p}, \hat{n}\rangle, \quad a_d = \langle \hat{d}, \hat{n}\rangle &&\text{- cosines with the direction of motion} \\
&D               &&\text{- Doppler factor} \\
&\Omega               &&\text{- Solid angle} \\
&[\ \cdot\ ]     &&\text{- substitution used at this step}
\end{aligned}
$$


## Setting

Color shift was already derived in [Doppler document](doppler.md), however speed $\beta _ r$ also affects brightness. Actually, there are three ways how perceived brightness is affected, and each of them depends on Doppler factor. We consider all three and then multiply the factors to get the final multiplier. 

## What is brightness

Brightness of a pixel is how much energy per second hits that pixel.

Energy per second $=$ $($ how many photons per second $)\times($ energy of one photon $)$ 

And already from this equation we get 2 out of 3 factors that change brightness, and here's why:

## Each photon's energy

Planck's energy–frequency relation is:

$$
\begin{aligned}
E=h\nu
\end{aligned}
$$

where $E$ is energy, $\nu$ is photon frequency and $h$ is Planck constant.

From that, the change of energies between camera and lab frames is exactly Doppler factor, because energy is proportional to frequency:

$$
\begin{aligned}
\frac{E'}{E}=\frac{\nu'}{\nu}=D.
\end{aligned}
$$

## Photon arrival rate

In lab, emitter emits photons at some rate $N$ (times per second); every interval between emissions shrinks by $D$ for camera, therefore $N' = DN$.

Note that this factor and the previous one came from the same fact - every interval changes by $D$, but they are not the same quantity: one is about photon's energy, and other is about the amount of photons.

This concludes the formula above:
$$
\begin{aligned}
\frac{(\text{energy per second})'}{(\text{energy per second})} = \frac{N'}{N} \cdot \frac{E'}{E} = D^2
\end{aligned}
$$

What this does not cover is that the directions themselves change. Aberration contracts the sky toward the direction of motion, so light that arrived from a wide patch in the lab frame now arrives from a narrow one. The same flux is packed into a smaller solid angle, which raises the brightness per unit angle - and that is a third, independent factor.

## Solid angle

The contraction is axially symmetric - depends only on angle to the direction of motion. However it is not uniform: compression is strongest along the motion and turns into expansion behind - this factor will carry $a _ d$. This symmetry is what reduces solid angle calculation below to a one-dimensional one.

By definition, a solid angle measures how much of the unit sphere a cone of directions covers, in the same way a plane angle measures a fraction of the unit circle; full sphere is $4\pi$ steradians.

A cone with half-opening angle $\phi$ around the axis of motion cuts out a spherical cap with area

$$
\Omega = 2\pi(1-\cos{\phi})
$$

Checking the limits: $\phi = 0$ gives zero; $\phi = \pi$ gives $4\pi$ = the whole sphere.


Consider a small patch of sky at angle $\phi$ from the direction of motion. In the lab frame it covers some solid angle, while in camera frame it covers a different one. In camera frame the perceived light rays are packed accordingly tighter or looser. So the ratio of those two is how brighter/dimmer it becomes for camera.

Since the contraction is not uniform and varies with $\phi$, the patch has to be taken infinitesimally small so that the factor is constant across it. Widening some cone with cap area $\Omega$ by infinitesimally small $d\phi$ adds a strip along its rim, area of which is $d\Omega$. 

Differentiating $\Omega$ with respect to $\phi$:

$$
\begin{aligned}
\frac{d\Omega}{d\phi} &= 2\pi \sin{\phi} \\
d\Omega &= 2\pi \sin{\phi} \ d\phi \\
d\Omega &= -2\pi \ d(\cos{\phi}) \\
\end{aligned}
$$

and then setting

$$
d\Omega' = -2\pi \ d(\cos{\phi'}),
$$

we can derive:

$$
\begin{aligned}
\frac{d\Omega'}{d\Omega} &= \frac{-2\pi \ d(\cos{\phi'})}{-2\pi \ d(\cos{\phi})} = \\
&= \frac{d(\cos{\phi'})}{d(\cos{\phi})} = \\
&= \left[a _ d = \langle \hat{n}, \hat{d} \rangle = \cos{\phi}, \quad \cos{\phi'} = \frac{a _ d + \beta _ r}{1 + a _ d \beta _ r} \right] = \\
&= \frac{d}{da_d}\left(\frac{a_d + \beta_r}{1 + a_d\beta_r}\right) = \\
&= \frac{1 - \beta _ r ^2}{(1 + a _ d \beta _ r)^2} = \\
&= \frac{1}{\gamma ^2 (1 + a _ d \beta _ r)^2} = \\
&= \frac{1}{D^2}
\end{aligned}
$$

The light that arrives from $d\Omega$ in the lab frame will arrive from $\frac{d\Omega}{D^2}$ in the camera frame. The energy here is unchanged, so the flux per unit solid angle - which is what a pixel measures - increases by $D^2$.

## Conclusion

Considering everything we derived, we can say that for each pixel brightness is changed by a factor of $D^2 \cdot D^2=D^4$.

## Tests
- $\beta _ r = 0$:

$$
D^4 = 1
$$

No change in brightness.

- $a _ d = 0, \ \beta _ r > 0$:

$$
D^4 = \gamma^4 > 1
$$

Flying by a lamp that is still, you see it brighter.

- $a _ d = 1, \ \beta _ r > 0$:

$$
D^4 = \gamma^4 (1 + \beta _ r)^4
$$

Maximal increase in brightness.

## Implementation

In `renderer.h` after determining `brightness` via Lambertian shading, it is multiplied by `beaming_factor(D)`, which is basically a $D^4$.