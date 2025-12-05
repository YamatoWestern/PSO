#ifndef ALL_MODEL_H
#define ALL_MODEL_H

#include <vector>
#include "model.h"

class TimeGraph;

/**
 * @brief Represents a comprehensive model for the Particle Swarm Optimization (PSO) algorithm.
 *
 * This class extends the base `Model` class and provides a more detailed implementation for a specific
 * optimization problem. It manages the state of the system, including containers, areas, and various
 * parameters related to the optimization process.
 */
class All_Model : public Model {
private:
    int W, H, L; /**< Dimensions of the environment (Width, Height, Length). */

    int allocate_size = 0;    /**< Total allocated size for the model. */
    int ss_allocate_size = 0; /**< Allocated size for the short-span model. */
    int ls_allocate_size = 0; /**< Allocated size for the long-span model. */

    int imp_ss, imp_ls; /**< Number of import short-span and long-span containers. */
    int res_ss_steps;   /**< Number of steps for reserved short-span containers. */
    int res_ls_steps;   /**< Number of steps for reserved long-span containers. */
    int imp_ss_steps;   /**< Number of steps for import short-span containers. */
    int exp_ss_steps;   /**< Number of steps for export short-span containers. */
    int max_ss_steps;   /**< Maximum number of steps for short-span containers. */
    int total_ss_steps; /**< Total number of steps for short-span containers. */
    int imp_ls_steps;   /**< Number of steps for import long-span containers. */
    int exp_ls_steps;   /**< Number of steps for export long-span containers. */
    int max_ls_steps;   /**< Maximum number of steps for long-span containers. */
    int total_ls_steps; /**< Total number of steps for long-span containers. */
    int res_ss_bits;    /**< Number of bits for reserved short-span containers. */
    int res_ls_bits;    /**< Number of bits for reserved long-span containers. */
    int ss_bits;        /**< Number of bits for short-span containers. */
    int ls_bits;        /**< Number of bits for long-span containers. */
    int area_size;      /**< Size of the area. */

    std::set<int> res_ss; /**< Set of reserved short-span containers. */
    std::set<int> res_ls; /**< Set of reserved long-span containers. */
    std::set<int> exp_ss; /**< Set of export short-span containers. */
    std::set<int> exp_ls; /**< Set of export long-span containers. */

    int last_cc_container;                                  /**< Index of the last container. */
    std::map<int, dat*> cc_containers;                      /**< Map of containers. */
    std::map<int, dat*> areas;                              /**< Map of areas. */
    std::vector<std::vector<std::vector<int>>> table;       /**< 3D table representing the environment. */
    std::vector<std::vector<bool>> mark;                    /**< 2D table for marking positions. */

    std::vector<int> area_pool;   /**< Pool of available areas. */
    std::vector<int> imp_ls_pool; /**< Pool of import long-span containers. */
    std::vector<int> imp_ss_pool; /**< Pool of import short-span containers. */
    std::vector<int> exp_ls_pool; /**< Pool of export long-span containers. */
    std::vector<int> exp_ss_pool; /**< Pool of export short-span containers. */
    std::vector<int> res_ss_pool; /**< Pool of reserved short-span containers. */
    std::vector<int> res_ls_pool; /**< Pool of reserved long-span containers. */

    std::vector<TimeGraph*> ss_graph; /**< Time graph for the short-span model. */
    std::vector<TimeGraph*> ls_graph; /**< Time graph for the long-span model. */

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

    /**
     * @brief Checks the short-span model.
     * @param src The source time graph.
     * @param time_counter The time counter.
     * @param start_time The start time.
     * @return An integer value.
     */
    int check_ss(TimeGraph* src, int& time_counter, int start_time);

public:
    /**
     * @brief Default constructor.
     */
    All_Model();

    /**
     * @brief Constructor that loads data from a file.
     * @param input The path to the input file.
     */
    All_Model(const char*& input);

    /**
     * @brief Destructor.
     */
    ~All_Model();

    /**
     * @brief Clones the model.
     * @return A new instance of the `All_Model` class.
     */
    All_Model* clone();

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
     * @brief Pops an element from the reserved short-span pool.
     * @param a The index of the element to pop.
     * @return The popped element.
     */
    int pop_res_ss_pool(int a);

    /**
     * @brief Pops an element from the reserved long-span pool.
     * @param a The index of the element to pop.
     * @return The popped element.
     */
    int pop_res_ls_pool(int a);

    /**
     * @brief Checks the short-span slope.
     * @param tc The time counter.
     * @param tt The travel time.
     * @param d The distance.
     * @param a The starting position.
     * @param b The ending position.
     * @return An integer value.
     */
    int check_ss_slope(int& tc, int tt, int d, int a, int b);

    /**
     * @brief Checks the short-span stability.
     * @param tc The time counter.
     * @param tt The travel time.
     * @param d The distance.
     * @param _x The x-coordinate.
     * @return An integer value.
     */
    int check_ss_stable(int& tc, int tt, int d, int _x);

    /**
     * @brief Analyzes the long-span model.
     */
    void ls_analyze();

    /**
     * @brief Solves the fitness function for the short-span model.
     * @param x_size The size of the input vector.
     * @param x The input vector.
     * @param edited A flag indicating whether the model has been edited.
     * @return The fitness value.
     */
    double fx_function_solve(int x_size, char* x, bool edited = false);

    /**
     * @brief Solves the fitness function for the long-span model.
     * @param x_size The size of the input vector.
     * @param x The input vector.
     * @param edited A flag indicating whether the model has been edited.
     * @return The fitness value.
     */
    double fx_function_solve_2(int x_size, char* x, bool edited = false);

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

#endif /* ALL_MODEL_H */
