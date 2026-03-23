#include "SkipBattleSummary.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"

namespace SkipBattleSummary {

   /*
    void BattleSceneHandler_Update_Hook(void* _this) {
        if (Options.bSkipBattleSummary) {
            if (BattleSceneHandler::currentState(_this) == BSS_Ending) {

                BattleSceneHandler::set_BattleResultSkipType(_this, BRST_SkipTimeline);
                BattleSceneHandler::set_BattleState(_this, BSS_ShowResult);
            }
        }

        CALL_ORIGIN(BattleSceneHandler_Update_Hook, _this);
    }
   */

    void Update() {}

    void Render() {
       /*
        ImGui::BeginGroupPanel("Skip Battle Summary");

        ImGui::Checkbox("Instant Result", &Options.bSkipBattleSummary);
        ImGui::SameLine();
        ImGui::HelpMarker("Skips the battle summary");

        ImGui::EndGroupPanel();
       */
    }

    void Start() {
      /*
        CreateHook(BattleSceneHandler::Update, BattleSceneHandler_Update_Hook);
      */
    }
}