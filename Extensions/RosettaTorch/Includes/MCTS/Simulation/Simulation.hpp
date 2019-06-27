// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP
#define ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP

#include <MCTS/Policies/ISimulationPolicy.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief Simulation class.
//!
class Simulation
{
    Simulation() : m_policy(new UCBPolicy())
    {
        // Do nothing
    }

    bool CutoffCheck(const Game& game, StateValue& stateValue) const
    {
        if (m_policy->IsEnableCutoff())
        {
            return m_policy->GetCutoffResult(game, stateValue);
        }

        return false;
    }

    void StartAction(const Game& game,
                     engine::ValidActionAnalyzer const& action_analyzer)
    {
        select_.StartAction(board, action_analyzer);
    }

    int ChooseAction(const Game& game,
                     engine::ValidActionAnalyzer const& action_analyzer,
                     ActionType actionType, const std::vector<int>& choices)
    {
        assert(!choices.empty());

        if (choices.size() == 1)
        {
            return 0;
        }

        int choice =
            m_policy->GetChoice(board, action_analyzer, action_type,
                              policy::simulation::ChoiceGetter(choices));
        // Always return a valid choice
        assert(choice >= 0);

        return choice;
    }

 private:
    ISimulationPolicy* m_policy = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP