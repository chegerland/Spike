struct Signal {
    double eps;
    double alpha;
    double beta;
    double phi;
    double f1;
    double f2;
};

struct Simulation {
    double t_0;
    double t_end;
    double dt;
    int N;
};

double signal(double t, void *signal)
{
    struct Signal * sig = (struct Signal *)signal;

    return sig->eps*(sig->alpha*cos(2.0*M_PI*sig->f1*t) + sig->beta*cos(2.0*M_PI*sig->f2*t + sig->phi) );
};


int main (int argc, char *argv[]) 
{
    struct Simulation sim;
    sim.t_0 = 0.0;
    sim.t_end = 40;
    sim.dt = 5e-3;
    sim.N = 10000;

    struct Signal sig;
    sig.eps = 0.05;
    sig.alpha = 1.0;
    sig.beta = 0.0;
    sig.phi = 0.0;
    sig.f1 = 0.215;
    sig.f2 = 0.0;

};

