using DelimitedFiles, Random

# simulation
N = 10000
t0 = 0.0
tend = 40.0
dt = 1e-2
Nsteps = convert(Int64, (tend - t0) / dt)

# neuron
mu = 1.1
D = 0.001

# signal
eps = 0.05
alpha = 1.0
f1 = 0.215

# adaptation
Delta = 3.0
tau = 0.1

# define arrays for firing rate and time
rate = zeros(Float64,Nsteps)
time = zeros(Float64,Nsteps)

# loop over all neurons
for i in 1:N

    # initial condition
    v = 0.0
    t = t0
    a = 0.0

    # euler maruyama scheme
    for j in 1:Nsteps 
        t += dt
        v += (mu - v)*dt -a*dt + eps*alpha*cos(2.0 * π * f1 * t)*dt + sqrt(2.0 * D)*randn()*sqrt(dt)
        a += - 1.0/tau * a * dt

        if (v > 1.0)
            v = 0.0
            a += Delta
            rate[j] += 1.0/(N * dt)
        end
    end
end

# fill time array
for j in 1:Nsteps
    time[j] = t0 + j*dt
end

# write to file
writedlm("test.txt", [time rate]);
