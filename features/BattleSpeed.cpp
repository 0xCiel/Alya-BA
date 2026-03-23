#include "BattleSpeed.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"
#include <algorithm>

namespace BattleSpeed {

    void BattleGameTime_Tick_Hook(void* _this) {
        if (Options.bBattleSpeed && IsInBattle() && Options.fBattleSpeed > 0.1f) {
            float scale = std::clamp(Options.fBattleSpeed, 0.1f, 10.0f);

            float oldLogicSec = BattleGameTime::LogicSecondPerFrameField(_this);
            int32_t oldFrame = BattleGameTime::CurrentFrame(_this);

            BattleGameTime::LogicSecondPerFrameField(_this) = oldLogicSec / scale;

            CALL_ORIGIN(BattleGameTime_Tick_Hook, _this);

            BattleGameTime::LogicSecondPerFrameField(_this) = oldLogicSec;

            if (BattleGameTime::CurrentFrame(_this) < oldFrame) {
                BattleGameTime::CurrentFrame(_this) = oldFrame;
            }
            return;
        }

        CALL_ORIGIN(BattleGameTime_Tick_Hook, _this);
    }

    void Render() {
        ImGui::BeginGroupPanel("Battle Speed");

        if (ImGui::Checkbox("Battle Speed", &Options.bBattleSpeed))
        {
            if (Options.bBattleSpeed)
            {
                CreateHook(BattleGameTime::Tick, BattleGameTime_Tick_Hook);
            }
            else
            {
                DeleteHook(BattleGameTime_Tick_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("Change Battle Speed");

        if (Options.bBattleSpeed) {
            ImGui::SliderFloat("Multiplier", &Options.fBattleSpeed, 1.0f, 10.0f, "%.1f");
        }

        ImGui::EndGroupPanel();
    }

    void Update() {}

    void Start() {
    }
}