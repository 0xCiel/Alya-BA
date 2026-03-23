#include "CameraFOV.h"
#include "imgui/imgui.h"
#include "utils.h"

namespace CameraFOV
{
    void Render()
    {
        ImGui::BeginGroupPanel("Camera FOV");
        ImGui::Checkbox("Camera FOV", &Options.bEnableFOV);
        ImGui::SameLine();
        ImGui::HelpMarker("Changes your Camera Field of View");
        ImGui::Separator();
        if (Options.bEnableFOV) {
            ImGui::SliderFloat("Field of View", &Options.fFOV, 0.0f, 360.0f, "%.1f");
        }
        
        ImGui::EndGroupPanel();
    }

    void Update()
    {
        static bool wasEnabled = false;
        static float originalFOV = 60.0f;
        
        void* cam = UnityEngine::Camera::get_main();
        if (cam == nullptr) return;

        if (Options.bEnableFOV) {
            if (!wasEnabled) {
                originalFOV = UnityEngine::Camera::get_fieldOfView(cam);
                wasEnabled = true;
            }
            UnityEngine::Camera::set_fieldOfView(cam, Options.fFOV);
        } else {
            if (wasEnabled) {
                UnityEngine::Camera::set_fieldOfView(cam, originalFOV);
                wasEnabled = false;
            }
        }
    }

    void Start()
    {
    }
}
