using DelimitedFiles, Random

# simulation
N = 10000
t_0 = 0.0
t_end = 60.0
dt = 1e-2
Nsteps = convert(Int, (t_end - t_0) / dt)

# neuron
mu = 1.1
D = 0.001

# signal
ϵ = 0.05
α = 1.0
f1 = 0.215

# adaptation
Delta = 3
τ = 0.01

rate = zeros(Float64,Nsteps)
time = zeros(Float64,Nsteps)

# loop over all neurons
for i in 1:N
    v = 0.0
    t = t_0
    a = 0.0

    # euler maruyama scheme
    for j in 1:Nsteps 
        t += dt
        v += (mu - v)*dt -a*dt + ϵ*α*cos(2.0 * π * f1 * t)*dt + sqrt(2.0 * D)*randn()*sqrt(dt)*dt
        a += - 1.0/τ * a * dt

        if v > 1
            v = 0
            a += Delta
            rate[j] += 1.0/(N * dt)
        end

        time[j] = t
    end
end

# write to file
writedlm("test.txt", [time rate]);
