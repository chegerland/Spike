#!/usr/bin/env python3

from mpmath import *
mp.dps = 15
mp.pretty = True

class LIF:
    def __init__(
    self,
    mu, # mean input current
    D   # diffusion coefficient
    ):
        self.mu = mu
        self.D = D

    def stationary_rate(self):
        integrand = lambda x: exp(x**2)*erfc(x)
        r0 = 1/(sqrt(pi) * quad(integrand, [(self.mu-1)/sqrt(2*self.D), self.mu/sqrt(2*self.D)]) )
        return r0


    def susceptibility_1(self, omega):
        alpha = self.stationary_rate()/sqrt(self.D) * j * omega / (j * omega - 1)
        a = pcfd(j*omega - 1, (self.mu - 1) /sqrt(self.D))
        b = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega - 1, self.mu/sqrt(self.D))
        c = pcfd(j*omega, (self.mu - 1) /sqrt(self.D))
        d = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega, self.mu/sqrt(self.D))

        result = alpha*(a - b)/(c - d)
        return result


    def susceptibility_2(self, omega_1, omega_2):
        alpha = self.stationary_rate()*(1 - j*omega_1 - j*omega_2)*(j*omega_1 + j*omega_2)/(2*self.D*(j*omega_1 - 1)*(j*omega_2 - 1))
        a = pcfd(j*omega_1 + j*omega_2 - 2, (self.mu - 1)/sqrt(self.D))
        b = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega_1 + j*omega_2 - 2, self.mu/sqrt(self.D))
        c = pcfd(j*omega_1 + j*omega_2, (self.mu - 1)/sqrt(self.D))
        d = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega_1 + j*omega_2, self.mu/sqrt(self.D))

        beta = (j*omega_1 + j*omega_2)/(2*sqrt(self.D))
        a_2 = (self.susceptibility_1(omega_1)/(j*omega_2 - 1) + self.susceptibility_1(omega_2)/(j*omega_1 - 1))*pcfd(j*omega_1 + j*omega_2 - 1, (self.mu-1)/sqrt(self.D))
        a_3 = (self.susceptibility_1(omega_1)/(j*omega_2 - 1) + self.susceptibility_1(omega_2)/(j*omega_1 - 1))*exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega_1 + j*omega_2 - 1, self.mu/sqrt(self.D))

        result = alpha*(a - b)/(c - d) + beta*(a_2)/(c - d) - beta*(a_3)/(c - d)
        return result

    def firing_rate_signal(self, t, eps, f):
        omega = 2 * pi * f
        stat = self.stationary_rate() + 0.5*eps**2*self.susceptibility_2(omega, -omega)
        lr = eps*fabs(self.susceptibility_1(omega))*cos(omega*t - arg(self.susceptibility_1(omega)))
        hh = 0.5*eps**2*fabs(self.susceptibility_2(omega, omega))*cos(2*omega*t - arg(self.susceptibility_2(omega,omega)))
        result = stat + lr + hh
        assert im(result) == 0
        return re(result)


class LIFadapt:

    def __init__(self,
    mu,
    D,
    Delta,
    tau_a
    ):
        self.D = D
        self.Delta = Delta
        self.tau_a = tau_a
        self.mu = mu - Delta*tau_a/(1 + Delta*tau_a)*(mu - 0.5)

    def stationary_rate(self):
        r0 = 1./(1 + Delta*tau_a)*(mu - 0.5)
        return r0


    def susceptibility_1(self, omega):
        alpha = self.stationary_rate()/sqrt(self.D) * j * omega / (j * omega - 1)
        a = pcfd(j*omega - 1, (self.mu - 1) /sqrt(self.D))
        b = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega - 1, self.mu/sqrt(self.D))
        c = pcfd(j*omega, (self.mu - 1) /sqrt(self.D))
        d = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega, self.mu/sqrt(self.D))

        result = alpha*(a - b)/(c - d)
        result = result / ( 1 + result * self.Delta*self.tau_a/(1 - j* self.tau_a*omega))
        return result


    def susceptibility_2(self, omega_1, omega_2):
        alpha = self.stationary_rate()*(1 - j*omega_1 - j*omega_2)*(j*omega_1 + j*omega_2)/(2*self.D*(j*omega_1 - 1)*(j*omega_2 - 1))
        a = pcfd(j*omega_1 + j*omega_2 - 2, (self.mu - 1)/sqrt(self.D))
        b = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega_1 + j*omega_2 - 2, self.mu/sqrt(self.D))
        c = pcfd(j*omega_1 + j*omega_2, (self.mu - 1)/sqrt(self.D))
        d = exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega_1 + j*omega_2, self.mu/sqrt(self.D))

        beta = (j*omega_1 + j*omega_2)/(2*sqrt(self.D))
        a_2 = (self.susceptibility_1(omega_1)/(j*omega_2 - 1) + self.susceptibility_1(omega_2)/(j*omega_1 - 1))*pcfd(j*omega_1 + j*omega_2 - 1, (self.mu-1)/sqrt(self.D))
        a_3 = (self.susceptibility_1(omega_1)/(j*omega_2 - 1) + self.susceptibility_1(omega_2)/(j*omega_1 - 1))*exp((2 * self.mu - 1)/(4*self.D))*pcfd(j*omega_1 + j*omega_2 - 1, self.mu/sqrt(self.D))

        result = alpha*(a - b)/(c - d) + beta*(a_2)/(c - d) - beta*(a_3)/(c - d)
        suscept1 = self.susceptibility_1(omega_1 + omega_2)
        result = result / (1 + suscept1 * self.Delta*self.tau_a/(1 - j* self.tau_a*(omega_1+omega_2)))
        return result

    def firing_rate_signal_linear(self, t, eps, f):
        omega = 2 * pi * f
        stat = self.stationary_rate()
        lr = eps*fabs(self.susceptibility_1(omega))*cos(omega*t - arg(self.susceptibility_1(omega)))
        result = stat + lr
        assert im(result) == 0
        return re(result)

    def firing_rate_signal_nonlinear(self, t, eps, f):
        omega = 2 * pi * f
        stat = self.stationary_rate() + 0.5*eps**2*self.susceptibility_2(omega, -omega)
        lr = eps*fabs(self.susceptibility_1(omega))*cos(omega*t - arg(self.susceptibility_1(omega)))
        hh = 0.5*eps**2*fabs(self.susceptibility_2(omega, omega))*cos(2*omega*t - arg(self.susceptibility_2(omega,omega)))
        result = stat + lr + hh
        assert im(result) == 0
        return re(result)
