#ifndef MODEL_H
#define MODEL_H

#include <set>
#include <map>
#include <vector>

/**
 * @brief Represents a data structure with three integer members.
 */
struct dat {
    int _h; /**< The h member. */
    int _w; /**< The w member. */
    int _l; /**< The l member. */

    /**
     * @brief Constructor that initializes the members.
     * @param x The value for the h member.
     * @param y The value for the w member.
     * @param z The value for the l member.
     */
    dat(int x, int y, int z) : _h(x), _w(y), _l(z) {}

    /**
     * @brief Less-than operator for comparing two `dat` objects.
     * @param b The other `dat` object to compare with.
     * @return `true` if this object is less than the other object, `false` otherwise.
     */
    bool operator<(const dat& b) const {
        if (_h != b._h) return _h < b._h;
        else if (_w != b._w) return _w < b._w;
        else return _l < b._l;
    }
};

/**
 * @brief Represents a base model for the Particle Swarm Optimization (PSO) algorithm.
 *
 * This is an abstract base class that defines the common interface for different optimization models.
 * It provides methods for loading data, cloning the model, and solving the fitness function.
 */
class Model {
private:
    int allocate_size; /**< The allocated size for the model. */

    /**
     * @brief Loads data from a file.
     * @param file The path to the input file.
     */
    virtual void load_data(const char* file);

public:
    /**
     * @brief Default constructor.
     */
    Model();

    /**
     * @brief Constructor that loads data from a file.
     * @param input The path to the input file.
     */
    Model(const char*& input);

    /**
     * @brief Destructor.
     */
    ~Model();

    /**
     * @brief Clones the model.
     * @return A new instance of the `Model` class.
     */
    virtual Model* clone();

    /**
     * @brief Solves the fitness function for the model.
     * @param x_size The size of the input vector.
     * @param x The input vector.
     * @param display A flag indicating whether to display the results.
     * @return The fitness value.
     */
    virtual double fx_function_solve(int x_size, char* x, bool display);

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
    virtual void display();
};

#endif /* MODEL_H */
