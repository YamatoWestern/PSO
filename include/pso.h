#ifndef PSO_H
#define PSO_H

#include <math.h>
#include <stdio.h>
#include "swarm.h"

/**
 * @brief Represents the Particle Swarm Optimization (PSO) algorithm.
 *
 * This class encapsulates the logic of the PSO algorithm. It manages a swarm of particles and
 * iteratively updates their positions and velocities to find the optimal solution to a given problem.
 */
class PSO {
public:
    double wmax; /**< The maximum value of the inertia weight. */
    double wmin; /**< The minimum value of the inertia weight. */
    double cp;   /**< The cognitive parameter. */
    double cg;   /**< The social parameter. */
    double cl;   /**< The local parameter. */
    double cn;   /**< The neighborhood parameter. */
    int Iter;    /**< The number of iterations. */
    int nPar;    /**< The number of particles. */
    int nDim;    /**< The number of dimensions. */
    int NB;      /**< The number of neighbors. */

    Swarm* sSwarm; /**< A pointer to the swarm of particles. */

    /**
     * @brief Constructor that initializes the PSO algorithm with the given parameters.
     * @param nIter The number of iterations.
     * @param nNB The number of neighbors.
     * @param dwmax The maximum value of the inertia weight.
     * @param dwmin The minimum value of the inertia weight.
     * @param dcp The cognitive parameter.
     * @param dcg The social parameter.
     * @param dcl The local parameter.
     * @param dcn The neighborhood parameter.
     */
    PSO(int nIter, int nNB, double dwmax, double dwmin, double dcp, double dcg, double dcl, double dcn) {
        Iter = nIter;
        NB = nNB;
        wmax = dwmax;
        wmin = dwmin;
        cp = dcp;
        cg = dcg;
        cl = dcl;
        cn = dcn;
    }

    /**
     * @brief Destructor.
     */
    ~PSO() {
        if (sSwarm) {
            delete sSwarm;
            sSwarm = NULL;
        }
    }

    /**
     * @brief Sets the dimensions of the swarm.
     * @param par The number of particles.
     * @param dim The number of dimensions.
     */
    void SetDimension(int par, int dim) {
        //set swarm members and particle dimensions
        nPar = par;
        nDim = dim;
    }

    /**
     * @brief Initializes the swarm.
     */
    virtual void InitSwarm() {
        //swarm initialization
    }

    /**
     * @brief Runs the PSO algorithm.
     * @param debug A flag indicating whether to print debug information.
     */
    void Run(bool debug) {
        //PSO algorithm
        double w = wmax;
        double decr = (wmax - wmin) / Iter;

        sSwarm = new Swarm(nPar, nDim);
        InitSwarm();
        Evaluate();
        sSwarm->UpdateBest(NB);

        double** u1 = new double*[sSwarm->Member];
        double** u2 = new double*[sSwarm->Member];
        double** u3 = new double*[sSwarm->Member];
        double** u4 = new double*[sSwarm->Member];
        for (int i = 0; i < sSwarm->Member; i++) {
            u1[i] = new double[sSwarm->pParticle[0]->Dimension];
            u2[i] = new double[sSwarm->pParticle[0]->Dimension];
            u3[i] = new double[sSwarm->pParticle[0]->Dimension];
            u4[i] = new double[sSwarm->pParticle[0]->Dimension];
        }

        for (int i = 1; i < Iter; i++) {
            //generate random number for the iteration process
            for (int j = 0; j < sSwarm->Member; j++) {
                for (int k = 0; k < sSwarm->pParticle[0]->Dimension; k++) {
                    u1[j][k] = ((double)rand() / (RAND_MAX));
                    u2[j][k] = ((double)rand() / (RAND_MAX));
                    u3[j][k] = ((double)rand() / (RAND_MAX));
                    u4[j][k] = ((double)rand() / (RAND_MAX));
                }
            }

            sSwarm->Move(w, cp, cg, cl, cn, u1, u2, u3, u4);
            Evaluate();
            sSwarm->UpdateBest(NB);
            if (debug) {
                sSwarm->EvalDispersion();
                sSwarm->EvalStatObj();
                printf("%d \t %d \t %lf  \t %lf  \t %lf  \t %lf  \t %lf\n", i, sSwarm->posBest, sSwarm->pParticle[sSwarm->posBest]->ObjectiveP, sSwarm->Dispersion, sSwarm->AvgObj, sSwarm->MinObj, sSwarm->MaxObj);
            }
            w -= decr;
        }

        for (int i = 0; i < sSwarm->Member; i++) {
            delete[] u1[i];
            delete[] u2[i];
            delete[] u3[i];
            delete[] u4[i];
        }
        delete[] u1;
        delete[] u2;
        delete[] u3;
        delete[] u4;
        u1 = u2 = u3 = u4 = NULL;
    }

    /**
     * @brief Evaluates the objective function for each particle in the swarm.
     */
    void Evaluate() {
        //evaluate objective function value of each swarm member
        for (int j = 0; j < sSwarm->Member; j++)
            sSwarm->pParticle[j]->Objective = Objective(sSwarm->pParticle[j]);
    }

    /**
     * @brief Calculates the objective function for a given particle.
     * @param p A pointer to the particle.
     * @return The objective function value.
     */
    virtual double Objective(Particle*& p) {
        //empty function to be override in the problem specific definition
        //to calculate objective function of a particle
        return 0;
    }

    /**
     * @brief Displays the results of the optimization.
     */
    virtual void DisplayResult() {
        //empty function to be override in the problem specific definition
        //to display the result
    }
};

#endif
