// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_MCTS_CONFIG_HPP
#define ROSETTASTONE_TORCH_AGENTS_MCTS_CONFIG_HPP

namespace RosettaTorch::Agents
{
struct MCTSConfig
{
    MCTSConfig()
        : threads(1),
          treeSamples(10),
          iterationsPerAction(10000),
          callbackInterval(1000),
          actionFollowTemperature(0.0)
    {
        // Do nothing
    }

    int threads;
    int treeSamples;

    int iterationsPerAction;
    int callbackInterval;

    double actionFollowTemperature;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_CONFIG_HPP