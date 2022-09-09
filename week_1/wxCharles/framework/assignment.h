#pragma once

#include "world.h"

#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <optional>

constexpr int DEFAULT_TIMEOUT = 5000;
constexpr int DEFAULT_MAX_ACTIONS = 1000000;

/**
 * @brief Defines an agent function, implemented by the user, which can be simulated with the provided constraints.
 *
 */
struct Agent {
    std::string name;
    std::string description;
    std::string category;
    std::function<void()> agent;
    int maxActions;
    int timeout;
    bool hadSimulationError;

    Agent(std::string name, std::string description, std::string category, std::function<void()> agent, int maxActions, int timeout) {
        this->name = std::move(name);
        this->description = std::move(description);
        this->category = std::move(category);
        this->agent = std::move(agent);
        this->maxActions = maxActions;
        this->timeout = timeout;
        this->hadSimulationError = false;
    }
};

/**
 * @brief Base class for all exercises.
 *
 */
class Exercise {
public:
    /**
     * @brief Construct a new Exercise object.
     *
     * @param name The name of the exercise, with optional keyboard accelerator. The keyboard accelerator is not shown in the window title.
     * @param description The description of the exercise, which is shown when the user hovers over the selection item in the menu bar.
     * @param category The category of the exercise, which is used to group exercises with identical categories in the menu bar.
     * @param minVariant The minimum variant number, which must be at least 1.
     * @param maxVariant The maximum variant number, which must be at least \p minVariant. Setting this equal to \p minVariant effectively means no variants exist, as there is only one variant.
     */
    Exercise(std::string name, std::string description, std::string category, int minVariant, int maxVariant);

    virtual ~Exercise() {}

    /**
     * @brief Returns the exercise name with the keyboard accelerator part.
     *
     * @return The name.
     */
    const std::string& GetName() const { return m_name; }

    /**
     * @brief Returns the exercise description.
     *
     * @return The description.
     */
    const std::string& GetDescription() const { return m_description; }

    /**
     * @brief Returns the exercise category. Exercises are grouped in the menu bar according to their category.
     * An empty string indicates no category, which will prevent grouping as it is placed direcly under the exercise menu item.
     *
     * @return The category.
     */
    const std::string& GetCategory() const { return m_category; }

    /**
     * @brief Returns the exercise name without the keyboard accelerator part.
     *
     * @return The clean name.
     */
    std::string GetCleanName() const { return m_name.substr(0, m_name.find('\t')); }

    /**
     * @brief Returns the minimum variant number.
     *
     * @return The minimum variant.
     */
    int GetMinVariant() const { return m_minVariant; }

    /**
     * @brief Returns the maximum variant number.
     *
     * @return The maximum variant.
     */
    int GetMaxVariant() const { return m_maxVariant; }

    /**
     * @brief Returns whether at least two variants of this exercise exist.
     *
     * @return Whether multiple variants of this exercise exist.
     */
    bool HasVariants() const { return m_minVariant != m_maxVariant; }

    /**
     * @brief Attaches an agent to this exercise, which is automatically ran once the exercise has been selected as the active exercise, or a different variant is selected.
     * Users can disable this automatic running in the UI. If a simulation error occurs while running the attached agent, automatic running is disabled for this exercise.
     * This is to prevent spamming users with errors.
     *
     * @param agent The agent to run.
     */
    void AttachAgent(std::shared_ptr<Agent> agent) { m_agent = agent; }

    /**
     * @brief Gets the attached agent. Calling this member function when no agent is attached will throw an exception.
     *
     * @return The attached agent.
     */
    std::shared_ptr<Agent> GetAttachedAgent() const { return m_agent.value(); }

    /**
     * @brief Checks whether an agent is attached to this exercise.
     *
     * @return true if an agent is attached, false otherwise.
     */
    bool HasAttachedAgent() const { return m_agent.has_value(); }

    /**
     * @brief Creates the world for this exercise. The given variant must be valid respective to the minimum and maximum variant allowed.
     *
     * @param variant The variant of the exercise to create.
     * @return The created world.
     */
    World Create(int variant);

protected:
    /**
     * @brief Implements the actual creation of the world for this exercise.
     *
     * @param variant The variant of the exercise to create, which is guaranteed to be valid.
     * @return The created world.
     */
    virtual World DoCreate(int variant) = 0;

private:
    std::string m_name;
    std::string m_description;
    std::string m_category;
    int m_minVariant;
    int m_maxVariant;
    std::optional<std::shared_ptr<Agent>> m_agent;
};

/**
 * @brief Base class for exercises without multiple variants.
 *
 */
class StaticExercise : public Exercise {
public:
    /**
     * @brief Construct a new StaticExercise object.
     *
     * @param name The name of the exercise, with optional keyboard accelerator. The keyboard accelerator is not shown in the window title.
     * @param description The description of the exercise, which is shown when the user hovers over the selection item in the menu bar.
     * @param category The category of the exercise, which is used to group exercises with identical categories in the menu bar.
     */
    StaticExercise(std::string name, std::string description, std::string category = "")
        : Exercise(name, description, category, 1, 1) {}

protected:
    World DoCreate(int variant) override final;

    /**
     * @brief Creates the world for this exercise.
     *
     * @return The created world.
     */
    virtual World Create() = 0;
};

/**
 * @brief Base class for exercises with multiple variants that are randomly generated.
 *
 */
class RandomExercise : public Exercise {
public:
    /**
     * @brief Construct a new RandomExercise object.
     *
     * @param name The name of the exercise, with optional keyboard accelerator. The keyboard accelerator is not shown in the window title.
     * @param description The description of the exercise, which is shown when the user hovers over the selection item in the menu bar.
     * @param seed The seed used for the variant PRNG, which is used to generate seeds for the exercise PRNG.
     * @param category The category of the exercise, which is used to group exercises with identical categories in the menu bar.
     * @param variants The number of variants that can be generated.
     */
    RandomExercise(std::string name, std::string description, uint_fast32_t seed, std::string category = "", int variants = 99);

protected:
    World DoCreate(int variant) override final;

    /**
     * @brief Creates the world for this exercise. The exercise PRNG is seeded with the seed of the respective variant prior to this function being called, which allows for deterministic generation of pseudo-random variants.
     *
     * @return The created world.
     */
    virtual World Create() = 0;

    /**
     * @brief Returns the next random integer between 0 and \p max, based on the current exercise PRNG.
     *
     * @param max The inclusive upper bound.
     * @return The randomly generated integer.
     */
    int NextRandomInt(int max) { return NextRandomInt(0, max); }

    /**
     * @brief Returns the next random integer between \p min and \p max, based on the current exercise PRNG.
     *
     * @param min The inclusive lower bound.
     * @param max The inclusive upper bound.
     * @return The randomly generated integer.
     */
    int NextRandomInt(int min, int max);

private:
    uint_fast32_t m_seed;
    std::mt19937 m_variantRNG;
    std::mt19937 m_exerciseRNG;
};

/**
 * @brief Defines an assignment, which consists of several agents and exercises.
 *
 */
class Assignment {
public:
    /**
     * @brief Returns all the agents belonging to this assignment.
     *
     * @return The agents.
     */
    const std::vector<std::shared_ptr<Agent>>& GetAgents() const { return m_agents; }

    /**
     * @brief Returns all the exercises belonging to this assignment.
     *
     * @return The exercises.
     */
    const std::vector<std::shared_ptr<Exercise>>& GetExercises() const { return m_exercises; }

protected:
    /**
     * @brief Adds an agent to this assignment.
     *
     * @param name The name of the agent as shown in the menu bar, along with optional keyboard accelerator.
     * @param description The description of the agent, as shown in the status bar upon hovering on the menu item.
     * @param category The category to place the menu item under. An empty string causes the menu item to be placed directly in the Run menu item.
     * @param agent The agent function to call when simulating.
     * @param maxActions The maximum number of actions the agent may perform while simulating.
     * @param timeout The maximum number of time the simulation may take before being aborted.
     *
     * @return The created agent instance.
     */
    std::shared_ptr<Agent> AddAgent(std::string name, std::string description, std::string category, std::function<void()> agent, int maxActions = DEFAULT_MAX_ACTIONS, int timeout = DEFAULT_TIMEOUT);

    /**
     * @brief Adds an exercise to this assignment. The pointer is stored using a shared pointer, which will automatically free the instance once no more references are hold.
     *
     * @param exercise The exercise to add, which must be a pointer to a valid exercise instance.
     *
     * @return The given exercise instance.
     */
    std::shared_ptr<Exercise> AddExercise(Exercise* exercise);

private:
    std::vector<std::shared_ptr<Agent>> m_agents;
    std::vector<std::shared_ptr<Exercise>> m_exercises;
};

/**
 * @brief Creates the assignment instance which is used to populate the UI.
 *
 * @return The assignment instance.
 */
extern std::unique_ptr<Assignment> CreateAssignment();