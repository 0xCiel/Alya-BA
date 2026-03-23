#include "DumbEnemy.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"

namespace DumbEnemies
{
    bool BattleEntity_get_HasMainTarget_Hook(void* _this)
    {
        if (Options.bDumbEnemies && IsInBattle())
        {
            int type = BattleEntity::TacticEntityType(_this);
            if (type == 2 || type == 4 || type == 8 || type == 16)
            {
                BattleEntity::ClearTargetAndSkillCommandInfo(_this);
            }
        }

        return CALL_ORIGIN(BattleEntity_get_HasMainTarget_Hook, _this);
    }

    void Render() {
        ImGui::BeginGroupPanel("Dumb Enemies");
        if (ImGui::Checkbox("Dumb Enemies", &Options.bDumbEnemies))
        {
            if (Options.bDumbEnemies)
            {
                CreateHook(BattleEntity::get_HasMainTarget, BattleEntity_get_HasMainTarget_Hook);
            }
            else
            {
                DeleteHook(BattleEntity_get_HasMainTarget_Hook);
            }
        }
		ImGui::SameLine();
		ImGui::HelpMarker("Makes enemies unable to target you");
        ImGui::EndGroupPanel();
    }

    void Update() {
    }

    void Start() {
    }
}
