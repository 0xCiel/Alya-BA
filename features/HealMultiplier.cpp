#include "HealMultiplier.h"
#include "imgui/imgui.h"
#include "hooks.h"

namespace HealMultiplier
{
    static int64_t originalValue = 0;

    void Apply(void* battleEntity)
    {
        void* stat = BattleEntity::get_CurrentStat(battleEntity);
        if (!stat) return;

        int64_t base = 0;
        if (!BattleEntityStat::GetValue(stat, 69, &base)) return;

        if (!Options.bHealMultiplier && originalValue != 0)
        {
            BattleEntityStat::SetValue(stat, 69, originalValue);
            originalValue = 0;
            return;
        }

        if (Options.bHealMultiplier)
        {
            if (originalValue == 0) originalValue = base;
            int64_t newValue = originalValue * Options.HealMultiplier;
            BattleEntityStat::SetValue(stat, 69, newValue);
        }
    }

    void NewNormalAttackAction_Update_Hook(void* _this, void* battle)
    {
        if (IsInBattle())
        {
            void* executer = HeroAction::Executer(_this);
            if (executer && BattleEntity::TacticEntityType(executer) == 1)
            {
                Apply(executer);
            }
        }

        CALL_ORIGIN(NewNormalAttackAction_Update_Hook, _this, battle);
    }

    void Render()
    {
        ImGui::BeginGroupPanel("Heal Multiplier");
        if (ImGui::Checkbox("Heal Multiplier", &Options.bHealMultiplier))
        {
            if (Options.bHealMultiplier)
            {
                CreateHook(NewNormalAttackAction::Update, NewNormalAttackAction_Update_Hook);
            }
            else
            {
                DeleteHook(NewNormalAttackAction_Update_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("Multiplies your healing");
        if (Options.bHealMultiplier)
            ImGui::SliderInt("Multiplier", &Options.HealMultiplier, 1, 1000);
        ImGui::EndGroupPanel();
    }

    void Update() {}

    void Start()
    {
    }
}
