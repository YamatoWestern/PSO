#ifndef PARTICLE_H
#define PARTICLE_H

/**
 * @brief Represents a particle in the Particle Swarm Optimization (PSO) algorithm.
 *
 * Each particle has a position, a velocity, and a memory of its best-known position. The particles
 * move through the search space, and their movements are influenced by their own best-known position
 * and the best-known positions of other particles.
 */
class Particle {
public:
    int Dimension;       /**< The dimension of the particle. */
    int localBest;       /**< The index of the local best position. */
    double* Position;    /**< The current position of the particle. */
    double* Velocity;    /**< The current velocity of the particle. */
    double* Neighbor;    /**< The best position of the particle's neighbors. */
    double* BestP;       /**< The previous best position of the particle. */
    double Objective;    /**< The current objective function value of the particle. */
    double ObjectiveP;   /**< The previous best objective function value of the particle. */
    double* PosMax;      /**< The maximum position of the particle. */
    double* PosMin;      /**< The minimum position of the particle. */

    /**
     * @brief Constructor that initializes a particle with a given dimension.
     * @param nDim The dimension of the particle.
     */
    Particle(int nDim) {
        // construct a particle with nDim dimension
        Dimension = nDim;
        Position = new double[Dimension];
        Velocity = new double[Dimension];
        BestP = new double[Dimension];
        Neighbor = new double[Dimension];
        PosMax = new double[Dimension];
        PosMin = new double[Dimension];
    }

    /**
     * @brief Destructor.
     */
    ~Particle() {
        delete[] Position;
        delete[] Velocity;
        delete[] BestP;
        delete[] Neighbor;
        delete[] PosMax;
        delete[] PosMin;
    }
};

#endif
