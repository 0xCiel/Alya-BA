#include "InstantWin.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"

namespace InstantWin
{
    void Battle_Update_Hook(void* _this)
    {
        if (Options.bInstantWin && IsInBattle())
        {
            void* summary = Battle::BattleSummary_(_this);
            if (summary)
            {
                BattleSummary::Winner(summary) = 1;
                BattleSummary::EndType(summary) = 4;
                BattleSummary::EndFrame(summary) = 0;
                BattleSummary::ElapsedRealtime(summary) = 0.0f;

                Battle::set_GameState(_this, 3);
            }
        }

        CALL_ORIGIN(Battle_Update_Hook, _this);
    }

    void Render()
    {
        ImGui::BeginGroupPanel("Instant Win");
        if (ImGui::Checkbox("Instant Win", &Options.bInstantWin))
        {
            if (Options.bInstantWin)
            {
                CreateHook(Battle::Update, Battle_Update_Hook);
            }
            else
            {
                DeleteHook(Battle_Update_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("Instantly wins the battle");
        ImGui::SameLine();
        ImGui::AlertMarker("PLEASE DISABLE THIS WHEN GOING TO TACTICAL CHALLENGE TO AVOID GETTING KICKED, can still be used inside Tactical Challenge though, just disable when going to tactical challenge");
        ImGui::EndGroupPanel();
    }

    void Update()
    {
    }

    void Start()
    {
    }
}