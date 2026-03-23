#include "NoCost.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"

namespace NoCost
{
    void PlayerSkillCardManager_UpdateRegenCost_Hook(void* _this)
    {
        if (Options.bNoCost && IsInBattle())
        {
            PlayerSkillCardManager::CurCost(_this) = 999999.0f;
            PlayerSkillCardManager::RegenStartDelayFrame(_this) = 0;
            return;
        }

        CALL_ORIGIN(PlayerSkillCardManager_UpdateRegenCost_Hook, _this);
    }

    void PlayerSkillCardManager_ProcessSkillCard_Hook(void* _this)
    {
        if (Options.bNoCost && IsInBattle())
        {
            PlayerSkillCardManager::CurCost(_this) = 999999.0f;
            PlayerSkillCardManager::RegenStartDelayFrame(_this) = 0;
        }

        CALL_ORIGIN(PlayerSkillCardManager_ProcessSkillCard_Hook, _this);
    }

    void PlayerSkillCardManager_AddCost_Hook(void* _this, float costToAdd)
    {
        if (Options.bNoCost && IsInBattle() && costToAdd < 0)
            return;

        CALL_ORIGIN(PlayerSkillCardManager_AddCost_Hook, _this, costToAdd);
    }

    void Render()
    {
        ImGui::BeginGroupPanel("No Cost");
        if (ImGui::Checkbox("No Cost", &Options.bNoCost))
        {
            if (Options.bNoCost)
            {
                CreateHook(PlayerSkillCardManager::ProcessSkillCard, PlayerSkillCardManager_ProcessSkillCard_Hook);
                CreateHook(PlayerSkillCardManager::UpdateRegenCost, PlayerSkillCardManager_UpdateRegenCost_Hook);
                CreateHook(PlayerSkillCardManager::AddCost, PlayerSkillCardManager_AddCost_Hook);
            }
            else
            {
                DeleteHook(PlayerSkillCardManager_ProcessSkillCard_Hook);
                DeleteHook(PlayerSkillCardManager_UpdateRegenCost_Hook);
                DeleteHook(PlayerSkillCardManager_AddCost_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("Inf Cost");
        ImGui::EndGroupPanel();
    }

    void Update()
    {
    }

    void Start()
    {
    }
}
