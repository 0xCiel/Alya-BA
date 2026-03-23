#include "InstantKill.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"

namespace InstantKill
{

    int64_t BattleEntity_AddHitPoint_Hook(void* _this, int64_t value)
    {
        if (Options.bInstantKill && IsInBattle())
        {
            if (BattleEntity::TacticEntityType(_this) != 1)
            {
                BattleEntity::HitPoint(_this) = 1;
                BattleEntity::HitPointBefore(_this) = 1;
            }
        }

        return CALL_ORIGIN(BattleEntity_AddHitPoint_Hook, _this, value);
    }
    void Render() {
		ImGui::BeginGroupPanel("Instant Kill");
        if (ImGui::Checkbox("Instant Kill", &Options.bInstantKill))
        {
            if (Options.bInstantKill)
            {
                CreateHook(BattleEntity::AddHitPoint, BattleEntity_AddHitPoint_Hook);
            }
            else
            {
                DeleteHook(BattleEntity_AddHitPoint_Hook);
            }
        }
		ImGui::SameLine();
		ImGui::HelpMarker("Instantly kills enemies");
		ImGui::EndGroupPanel();
    }

    void Update() {
    }

    void Start() {
    }
}
