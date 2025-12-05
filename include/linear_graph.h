#ifndef LINEAR_GRAPH_H
#define LINEAR_GRAPH_H

#include <string>

const int const_travel_time = 3; /**< Constant travel time. */

/**
 * @brief Represents a time graph.
 *
 * This is an abstract base class for different types of time graphs. It provides a common interface
 * for working with time-dependent data.
 */
class TimeGraph {
protected:
    int min_x, max_x; /**< The minimum and maximum x-values. */
    int min_y, max_y; /**< The minimum and maximum y-values. */
    int mode, counter; /**< The mode and counter for the graph. */
    bool is_wait;     /**< A flag indicating whether the graph is in a waiting state. */

public:
    /**
     * @brief Default constructor.
     */
    TimeGraph() {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~TimeGraph() {}

    /**
     * @brief Sets the mode of the graph.
     * @param _mode The mode to set.
     * @param _counter The counter to set.
     * @param is_wait A flag indicating whether the graph is in a waiting state.
     */
    virtual void set_mode(int _mode, int _counter, bool is_wait = false);

    /**
     * @brief Gets the mode of the graph.
     */
    virtual void get_mode();

    /**
     * @brief Gets the type of the graph.
     * @return The type of the graph.
     */
    virtual int get_type();

    /**
     * @brief Gets the value of the graph at a given x-coordinate.
     * @param x The x-coordinate.
     * @return The value of the graph at the given x-coordinate.
     */
    virtual int get_value(int x) = 0;

    /**
     * @brief Clones the graph.
     * @return A new instance of the `TimeGraph` class.
     */
    virtual TimeGraph* clone() = 0;

    /**
     * @brief Checks if a given x-coordinate is within the graph's range.
     * @param x The x-coordinate to check.
     * @return `true` if the x-coordinate is within the graph's range, `false` otherwise.
     */
    bool inner(int x);

    /**
     * @brief Checks if a given x-coordinate is outside the graph's range.
     * @param x The x-coordinate to check.
     * @return `true` if the x-coordinate is outside the graph's range, `false` otherwise.
     */
    bool outer(int x);

    /**
     * @brief Compares two time graphs.
     * @param a The first time graph.
     * @param b The second time graph.
     * @param i The first index.
     * @param j The second index.
     * @return `true` if the graphs are equal, `false` otherwise.
     */
    static bool compare(TimeGraph* a, TimeGraph* b, int i, int j);

    /**
     * @brief Converts the graph to a string.
     * @return A string representation of the graph.
     */
    std::string toString();

    /**
     * @brief Displays the graph.
     */
    virtual void display();
};

/**
 * @brief Represents a time graph with a slope.
 *
 * This class extends the `TimeGraph` class and represents a linear function with a slope.
 */
class SlopeTimeGraph : public TimeGraph {
private:
    int y_diff; /**< The difference in y-values. */
    int x_diff; /**< The difference in x-values. */

public:
    /**
     * @brief Default constructor.
     */
    SlopeTimeGraph() {}

    /**
     * @brief Constructor that sets the dimensions of the graph.
     * @param _min_x The minimum x-value.
     * @param _max_x The maximum x-value.
     * @param _min_y The minimum y-value.
     * @param _max_y The maximum y-value.
     */
    SlopeTimeGraph(int _min_x, int _max_x, int _min_y, int _max_y);

    /**
     * @brief Gets the type of the graph.
     * @return The type of the graph.
     */
    int get_type();

    /**
     * @brief Gets the value of the graph at a given x-coordinate.
     * @param x The x-coordinate.
     * @return The value of the graph at the given x-coordinate.
     */
    int get_value(int x);

    /**
     * @brief Clones the graph.
     * @return A new instance of the `SlopeTimeGraph` class.
     */
    TimeGraph* clone();
};

/**
 * @brief Represents a time graph with a stable value.
 *
 * This class extends the `TimeGraph` class and represents a horizontal line with a constant y-value.
 */
class StableTimeGraph : public TimeGraph {
public:
    /**
     * @brief Default constructor.
     */
    StableTimeGraph() {}

    /**
     * @brief Constructor that sets the dimensions of the graph.
     * @param _min_x The minimum x-value.
     * @param _max_x The maximum x-value.
     * @param _y The y-value of the graph.
     */
    StableTimeGraph(int _min_x, int _max_x, int _y);

    /**
     * @brief Gets the type of the graph.
     * @return The type of the graph.
     */
    int get_type();

    /**
     * @brief Gets the value of the graph at a given x-coordinate.
     * @param x The x-coordinate.
     * @return The value of the graph at the given x-coordinate.
     */
    int get_value(int x);

    /**
     * @brief Clones the graph.
     * @return A new instance of the `StableTimeGraph` class.
     */
    TimeGraph* clone();
};

#endif /* LINEAR_GRAPH_H */
