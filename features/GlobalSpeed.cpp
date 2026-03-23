#include "GlobalSpeed.h"
#include "hooks.h"
#include "engine.h"
#include "globals.h"
#include "utils.h"

namespace GlobalSpeed {

    static bool lastEnabled = false;

    void Render() {
        ImGui::BeginGroupPanel("Global Speed");
        ImGui::Checkbox("Global Speed", &Options.bGlobalSpeed);
        ImGui::SameLine();
        ImGui::HelpMarker("Modifies Game Speed");
        if (Options.bGlobalSpeed) {
            ImGui::SliderFloat("Speed Multiplier", &Options.fGlobalSpeed, 1.f, 10.0f, "%.1f");
        }
        ImGui::EndGroupPanel();
    }

    void Update() {
        if (Options.bGlobalSpeed) {
            UnityEngine::Time::set_timeScale(Options.fGlobalSpeed);
        }
        else if (lastEnabled) {
            UnityEngine::Time::set_timeScale(1.0f); 
        }

        lastEnabled = Options.bGlobalSpeed;
    }

    void Start() {}
}
