// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/ModifyManaTask.hpp>

namespace Hearthstonepp::BasicTasks
{
ModifyManaTask::ModifyManaTask(ManaOperator numMode, ManaType manaMode,
                               BYTE num)
    : m_numMode(numMode), m_manaMode(manaMode), m_num(num)
{
    // Do Nothing
}

TaskID ModifyManaTask::GetTaskID() const
{
    return TaskID::MODIFY_MANA;
}

MetaData ModifyManaTask::Impl(Player& player)
{
    const auto getMana = [](Player& p, ManaType mode) -> BYTE {
        if (mode == ManaType::AVAILABLE)
        {
            return p.GetAvailableMana();
        }

        if (mode == ManaType::MAXIMUM)
        {
            return p.GetMaximumMana();
        }

        throw std::runtime_error("ModifyMana: Invalid mana mode");
    };

    BYTE mana = getMana(player, m_manaMode);
    switch (m_numMode)
    {
        case ManaOperator::ADD:
            mana += m_num;
            break;
        case ManaOperator::SUB:
            mana = (mana <= m_num) ? 0 : (mana - m_num);
            break;
        case ManaOperator::SET:
            mana = m_num;
            break;
    }

    // Clamps a mana cost to a given range (min:0 ~ max:10)
    mana = std::clamp(mana, static_cast<BYTE>(0), static_cast<BYTE>(10));

    if (m_manaMode == ManaType::AVAILABLE)
    {
        player.SetAvailableMana(mana);
    }

    if (m_manaMode == ManaType::MAXIMUM)
    {
        player.SetMaximumMana(mana);
    }

    return MetaData::MODIFY_MANA_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks