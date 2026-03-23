#include "DamageMultiplier.h"
#include "imgui/imgui.h"
#include "hooks.h"

namespace DamageMultiplier
{
    static int64_t originalValue = 0;

    void Apply(void* battleEntity)
    {
        void* stat = BattleEntity::get_CurrentStat(battleEntity);
        if (!stat) return;

        int64_t base = 0;
        if (!BattleEntityStat::GetValue(stat, 2, &base)) return;

        if (!Options.bDamageMultiplier && originalValue != 0)
        {
            BattleEntityStat::SetValue(stat, 2, originalValue);
            originalValue = 0;
            return;
        }

        if (Options.bDamageMultiplier)
        {
            if (originalValue == 0) originalValue = base;
            int64_t newValue = originalValue * Options.DamageMultiplier;
            BattleEntityStat::SetValue(stat, 2, newValue);
        }
    }

    void NewNormalAttackAction_Update_Hook(void* _this, void* battle)
    {
        if (Options.bDamageMultiplier && IsInBattle())
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
        ImGui::BeginGroupPanel("Damage Multiplier");
        if (ImGui::Checkbox("Damage Multiplier", &Options.bDamageMultiplier))
        {
            if (Options.bDamageMultiplier)
            {
                CreateHook(NewNormalAttackAction::Update, NewNormalAttackAction_Update_Hook);
            }
            else
            {
                DeleteHook(NewNormalAttackAction_Update_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("Multiplies your damage");
        if (Options.bDamageMultiplier)
            ImGui::SliderInt("Multiplier", &Options.DamageMultiplier, 1, 1000);
        ImGui::EndGroupPanel();
    }

    void Update() {}

    void Start()
    {
    }
}
