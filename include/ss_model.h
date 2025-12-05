#ifndef SS_MODEL_H
#define SS_MODEL_H

#include "model.h"

/**
 * @brief Represents a short-span model for the Particle Swarm Optimization (PSO) algorithm.
 *
 * This class extends the base `Model` class and provides a specific implementation for a short-span
 * optimization problem. It manages the state of the system, including containers, areas, and various
 * parameters related to the optimization process.
 */
class SS_Model : public Model {
private:
    int W, H, L;            /**< Dimensions of the environment (Width, Height, Length). */
    int allocate_size;      /**< Total allocated size for the model. */
    int imp_ss, imp_ls;     /**< Number of import short-span and long-span containers. */
    int res_steps;          /**< Number of steps for reserved containers. */
    int imp_ss_steps;       /**< Number of steps for import short-span containers. */
    int exp_ss_steps;       /**< Number of steps for export short-span containers. */
    int max_ss_steps;       /**< Maximum number of steps for short-span containers. */
    int total_ss_steps;     /**< Total number of steps for short-span containers. */
    int res_bits;           /**< Number of bits for reserved containers. */
    int ss_bits;            /**< Number of bits for short-span containers. */
    int area_size;          /**< Size of the area. */

    std::set<int> res;    /**< Set of reserved containers. */
    std::set<int> exp_ss; /**< Set of export short-span containers. */
    std::set<int> exp_ls; /**< Set of export long-span containers. */

    std::map<int, dat*> cc_containers;                /**< Map of containers. */
    std::map<int, dat*> areas;                        /**< Map of areas. */
    std::vector<std::vector<std::vector<int>>> table; /**< 3D table representing the environment. */

    std::vector<int> area_pool; /**< Pool of available areas. */
    std::vector<int> imp_pool;  /**< Pool of import containers. */
    std::vector<int> exp_pool;  /**< Pool of export containers. */
    std::vector<int> res_pool;  /**< Pool of reserved containers. */

    const static int TRAVEL_TIME = 3;  /**< Time required for travel. */
    const static int CONTROL_TIME = 28; /**< Time required for control operations. */

    /**
     * @brief Loads data from a file.
     * @param file The path to the input file.
     */
    void load_data(const char* file);

    /**
     * @brief Analyzes the loaded data.
     */
    void analyze();

    /**
     * @brief Calculates the required memory allocation size.
     * @return The calculated allocation size.
     */
    int calculate_malloc_size();

    /**
     * @brief Finds the reserved containers.
     */
    void find_res();

public:
    /**
     * @brief Default constructor.
     */
    SS_Model();

    /**
     * @brief Constructor that loads data from a file.
     * @param input The path to the input file.
     */
    SS_Model(const char*& input);

    /**
     * @brief Destructor.
     */
    ~SS_Model();

    /**
     * @brief Clones the model.
     * @return A new instance of the `SS_Model` class.
     */
    SS_Model* clone();

    /**
     * @brief Pops an element from a pool.
     * @param pool The pool to pop from.
     * @param idx The index of the element to pop.
     * @return The popped element.
     */
    int pop_pool(std::vector<int>& pool, int idx);

    /**
     * @brief Pops an element from the area pool.
     * @param a The index of the element to pop.
     * @return The popped element.
     */
    int pop_area_pool(int a);

    /**
     * @brief Pops an element from the reserved pool.
     * @param a The index of the element to pop.
     * @return The popped element.
     */
    int pop_res_pool(int a);

    /**
     * @brief Solves the fitness function for the model.
     * @param x_size The size of the input vector.
     * @param x The input vector.
     * @param display A flag indicating whether to display the results.
     * @return The fitness value.
     */
    double fx_function_solve(int x_size, char* x, bool display);

    /**
     * @brief Gets the bit size of the model.
     * @return The bit size.
     */
    inline int get_bit_size() const {
        return allocate_size;
    }

    /**
     * @brief Displays the model's state.
     */
    void display();
};

#endif /* SS_MODEL_H */
