#include "InfiniteSummonDuration.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"

namespace InfSummonDuration {
    void SummonedCharacter_Update_Hook(void* _this, void* battle) {
        if (Options.bInfSummonDuration && IsInBattle()) {
            int64_t maxDuration = SummonedCharacter::SummonDurationMax(_this);
            SummonedCharacter::SummonDurationRemained(_this) = maxDuration;
        }
        CALL_ORIGIN(SummonedCharacter_Update_Hook, _this, battle);
    }
    void SummonedCharacter_ExpireSummonedCharacter_Hook(void* _this) {
        if (Options.bInfSummonDuration && IsInBattle()) {
            return; 
        }
        CALL_ORIGIN(SummonedCharacter_ExpireSummonedCharacter_Hook, _this);
    }

    void Render() {
        ImGui::BeginGroupPanel("Infinite Summon Duration");
        if (ImGui::Checkbox("Infinite Summon Duration", &Options.bInfSummonDuration))
        {
            if (Options.bInfSummonDuration)
            {
                CreateHook(SummonedCharacter::Update, SummonedCharacter_Update_Hook);
                CreateHook(SummonedCharacter::ExpireSummonedCharacter, SummonedCharacter_ExpireSummonedCharacter_Hook);
            }
            else
            {
                DeleteHook(SummonedCharacter_Update_Hook);
                DeleteHook(SummonedCharacter_ExpireSummonedCharacter_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("your summon last forever");
        ImGui::EndGroupPanel();
    }
    void Update() {}
    void Start() {
    }
}