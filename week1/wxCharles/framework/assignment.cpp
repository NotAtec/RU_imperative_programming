#include "assignment.h"

#include <cassert>

Exercise::Exercise(std::string name, std::string description, std::string category, int minVariant, int maxVariant)
        : m_name{name}, m_description{description}, m_category{category}, m_minVariant{minVariant}, m_maxVariant{maxVariant}, m_agent{std::nullopt} {
    assert(minVariant >= 1);
    assert(maxVariant >= minVariant);
}

World Exercise::Create(int variant) {
    assert(variant >= m_minVariant);
    assert(variant <= m_maxVariant);

    return DoCreate(variant);
}

World StaticExercise::DoCreate(int variant) {
    assert(variant == 1);

    return Create();
}

RandomExercise::RandomExercise(std::string name, std::string description, uint_fast32_t seed, std::string category, int variants)
    : Exercise(name, description, category, 1, 1 + variants), m_seed{seed} {}

World RandomExercise::DoCreate(int variant) {
    // Seed RNG used to generate exercise variant seeds with the assignment seed.
    m_variantRNG.seed(m_seed);

    // Compute the N-th exercise variant seed by taking N-th RNG output.
    for(int i = 1; i < variant; ++i) {
        m_variantRNG();
    }

    // Seed RNG used to generate the exercise variant.
    m_exerciseRNG.seed(m_variantRNG());

    return Create();
}

int RandomExercise::NextRandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);

    return dist(m_exerciseRNG);
}

std::shared_ptr<Agent> Assignment::AddAgent(std::string name, std::string description, std::string category, std::function<void()> agent, int maxActions, int timeout) {
    assert(maxActions > 0);
    assert(timeout > 0);

    return m_agents.emplace_back(std::make_shared<Agent>(name, description, category, agent, maxActions, timeout));
}

std::shared_ptr<Exercise> Assignment::AddExercise(Exercise* exercise) {
    assert(exercise != nullptr);

    return m_exercises.emplace_back(exercise);
}