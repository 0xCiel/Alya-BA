#include "GodMode.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"
namespace GodMode
{
    int64_t BattleEntity_AddHitPoint_Hook(void* _this, int64_t value)
    {
        if (Options.bGodMode && IsInBattle())
        {
            if (BattleEntity::TacticEntityType(_this) == 1)
            {
                BattleEntity::Damaged(_this) = nullptr;
                return 0; 
            }
        }

        return CALL_ORIGIN(BattleEntity_AddHitPoint_Hook, _this, value);
    }
    void Render() {
		ImGui::BeginGroupPanel("God Mode");
        if (ImGui::Checkbox("God Mode", &Options.bGodMode))
        {
            if (Options.bGodMode)
            {
                CreateHook(BattleEntity::AddHitPoint, BattleEntity_AddHitPoint_Hook);
            }
            else
            {
                DeleteHook(BattleEntity_AddHitPoint_Hook);
            }
        }
		ImGui::SameLine();
        ImGui::HelpMarker("You won't take Damage");
		ImGui::EndGroupPanel();
    }

    void Update() {
    }

    void Start() {
    }


}
