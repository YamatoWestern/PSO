#ifndef SWARM_H
#define SWARM_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "particle.h"

/**
 * @brief Represents a swarm of particles in the Particle Swarm Optimization (PSO) algorithm.
 *
 * The swarm is a collection of particles that work together to find the optimal solution to a given
 * problem. The swarm manages the particles and their interactions, and it keeps track of the best-known
 * position found by any particle in the swarm.
 */
class Swarm {
public:
    int Member;        /**< The number of members (particles) in the swarm. */
    int posBest;       /**< The index of the best particle in the swarm. */
    double Dispersion; /**< The dispersion index of the swarm. */
    double VelIndex;   /**< The velocity index of the swarm. */
    double MaxObj;     /**< The maximum objective function value of the swarm. */
    double MinObj;     /**< The minimum objective function value of the swarm. */
    double AvgObj;     /**< The average objective function value of the swarm. */

    Particle** pParticle; /**< An array of pointers to the particles in the swarm. */

    /**
     * @brief Constructor that initializes a swarm with a given number of particles and dimensions.
     * @param nPar The number of particles.
     * @param nDim The number of dimensions.
     */
    Swarm(int nPar, int nDim) {
        // construct a swarm with nPar particles,
        // each particle with nDim dimension
        Member = nPar;
        pParticle = new Particle*[Member];

        for (int i = 0; i < Member; i++) {
            //Initialize particles
            pParticle[i] = new Particle(nDim);
        }
    }

    /**
     * @brief Destructor.
     */
    ~Swarm() {
        for (int i = 0; i < Member; i++) {
            delete pParticle[i];
        }
        delete[] pParticle;
    }

    /**
     * @brief Moves the swarm.
     * @param w The inertia weight.
     * @param cp The cognitive parameter.
     * @param cg The social parameter.
     * @param cl The local parameter.
     * @param cn The neighborhood parameter.
     * @param r1 A 2D array of random numbers.
     * @param r2 A 2D array of random numbers.
     * @param r3 A 2D array of random numbers.
     * @param r4 A 2D array of random numbers.
     */
    void Move(double w, double cp, double cg, double cl, double cn, double** r1, double** r2, double** r3, double** r4) {
        //moving swarm ...
        for (int i = 0; i < Member; i++) {
            for (int j = 0; j < pParticle[i]->Dimension; j++) {
                pParticle[i]->Velocity[j] *= w;
                pParticle[i]->Velocity[j] += cp * r1[i][j] * (pParticle[i]->BestP[j] - pParticle[i]->Position[j]);
                pParticle[i]->Velocity[j] += cg * r2[i][j] * (pParticle[posBest]->BestP[j] - pParticle[i]->Position[j]);
                pParticle[i]->Velocity[j] += cl * r3[i][j] * (pParticle[pParticle[i]->localBest]->BestP[j] - pParticle[i]->Position[j]);
                pParticle[i]->Velocity[j] += cn * r4[i][j] * (pParticle[i]->Neighbor[j] - pParticle[i]->Position[j]);

                pParticle[i]->Position[j] += pParticle[i]->Velocity[j];

                if (pParticle[i]->Position[j] > pParticle[i]->PosMax[j]) {
                    pParticle[i]->Position[j] = pParticle[i]->PosMax[j];
                    pParticle[i]->Velocity[j] = 0;
                }
                if (pParticle[i]->Position[j] < pParticle[i]->PosMin[j]) {
                    pParticle[i]->Position[j] = pParticle[i]->PosMin[j];
                    pParticle[i]->Velocity[j] = 0;
                }
            }
        }
    }

    /**
     * @brief Updates the cognitive and social information of the swarm.
     * @param nbSize The size of the neighborhood.
     */
    void UpdateBest(int nbSize) {
        //updating cognitive and social information

        int l_temp, n_temp;
        double FDR;
        double FDRBest;

        //update personal best
        for (int i = 0; i < Member; i++) {
            if (pParticle[i]->Objective < pParticle[i]->ObjectiveP) {
                pParticle[i]->ObjectiveP = pParticle[i]->Objective;
                for (int j = 0; j < pParticle[i]->Dimension; j++)
                    pParticle[i]->BestP[j] = pParticle[i]->Position[j];
            }
        }

        //update global best
        for (int i = 0; i < Member; i++)
            if (pParticle[i]->ObjectiveP < pParticle[posBest]->ObjectiveP)
                posBest = i;

        //update local best
        for (int i = 0; i < Member; i++) {
            pParticle[i]->localBest = i;

            for (int j = i - nbSize / 2; j <= i + nbSize / 2; j++) {
                l_temp = j;
                if (i == j)
                    continue;
                if (l_temp < 0)
                    l_temp += Member;
                if (l_temp >= Member)
                    l_temp -= Member;
                if (pParticle[l_temp]->ObjectiveP < pParticle[pParticle[i]->localBest]->ObjectiveP)
                    pParticle[i]->localBest = l_temp;
            }
        }

        //update near neighbor best
        for (
        int i = 0; i < Member; i++) {
            for (int j = 0; j < pParticle[i]->Dimension; j++) {
                if (i == 0)
                    n_temp = 1;
                else
                    n_temp = 0;

                FDRBest = (pParticle[i]->Objective - pParticle[n_temp]->ObjectiveP) / fabs(pParticle[i]->Position[j] - pParticle[n_temp]->BestP[j]);

                for (int k = 0; k < Member; k++) {
                    if (i == k) continue;
                    FDR = (pParticle[i]->Objective - pParticle[k]->ObjectiveP) / fabs(pParticle[i]->Position[j] - pParticle[k]->BestP[j]);
                    if (FDR > FDRBest) {
                        n_temp = k;
                        FDRBest = FDR;
                    }
                }
                pParticle[i]->Neighbor[j] = pParticle[n_temp]->BestP[j];
            }
        }
    }

    /**
     * @brief Displays the best particle in the swarm.
     */
    void DisplayBest() {
        //display the best particle

        printf("\n");
        printf("Best Particle in the Swarm\n");
        printf("--------------------------\n");
        printf("position:\n");
        printf("---------\n");
        for (int j = 0; j < pParticle[posBest]->Dimension; j++) {
            printf("dimension %d: %lf\n", j, pParticle[posBest]->Position[j]);
        }
        printf("---------\n");
        printf("objective: %lf\n", pParticle[posBest]->ObjectiveP);

    }

    /**
     * @brief Evaluates the dispersion index of the swarm.
     */
    void EvalDispersion() {
        //evaluate dispersion index

        double result = 0;
        for (int i = 0; i < this->Member; i++) {
            for (int j = 0; j < this->pParticle[i]->Dimension; j++) {
                result += fabs(this->pParticle[i]->Position[j] - this->pParticle[this->posBest]->BestP[j]);
            }
        }
        this->Dispersion = result / this->Member / this->pParticle[0]->Dimension;
    }

    /**
     * @brief Evaluates the velocity index of the swarm.
     */
    void EvalVelIndex() {
        //evaluate velocity index

        double result = 0;
        for (int i = 0; i < this->Member; i++)
            for (int j = 0; j < this->pParticle[i]->Dimension; j++)
                result += fabs(this->pParticle[i]->Velocity[j]);

        this->VelIndex = result / this->Member / this->pParticle[0]->Dimension;
    }

    /**
     * @brief Evaluates the swarm's objective function statistic.
     */
    void EvalStatObj() {
        //evaluate swarm's objective function statistic
        MaxObj = -1.7E308;
        MinObj = 1.7E308;
        AvgObj = 0;

        for (int i = 0; i < this->Member; i++) {
            if (MaxObj < this->pParticle[i]->Objective)
                MaxObj = this->pParticle[i]->Objective;
            if (MinObj > this->pParticle[i]->Objective)
                MinObj = this->pParticle[i]->Objective;
            AvgObj += this->pParticle[i]->Objective;
        }
        AvgObj /= this->Member;
    }
};

#endif
