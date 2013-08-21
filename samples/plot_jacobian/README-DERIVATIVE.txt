README-DERIVATIVE.txt

A function f(Q,n) is described in W.pgm and
W.txt, which is a W-shaped function.

The derivative df/dQ is computed. In general,
df/dQ is a Jacobian matrix when f is a m tuple
f = [f0 f1 ... fm-1] and Q a n tuple 
Q = [Q0 ... Qn-1]. 

The gradient grad(f) = Del(f) is also df/dQ for 
f a 1 tuple and Q a n tuple. 

If f a 1 tuple and Q a 1 tuple, its the regular derivative,
df/dQ.

This program plots f and its derivative df/dQ
using an example W-shaped function.

Other functions can be used. Try defining
f(Q,n) as cos(Q[0]) and compute derivative. It
should be df/dQ = -sin(Q[0]).
