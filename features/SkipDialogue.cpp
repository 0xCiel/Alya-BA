#include "SkipDialogue.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"


namespace SkipDialog
{
    void* UIScenarioNew_get_Task_Hook(void* _this)
    {
        void* task = CALL_ORIGIN(UIScenarioNew_get_Task_Hook, _this);
        
        if (Options.bSkipDialogue && task != nullptr) {
            static void* lastTaskPtr = nullptr;
            static int64_t lastTaskId = -1;

            int64_t currentId = ScenarioTask::CurrentId(task);
            
            if (task != lastTaskPtr || currentId != lastTaskId) {
                ScenarioTask::FinishScenario(task);
                lastTaskPtr = task;
                lastTaskId = currentId;
            }
        }

        return task;
    }

    void Update() {}

    void Render() {
        ImGui::BeginGroupPanel("Skip Dialogue");
        if (ImGui::Checkbox("Skip Dialogue", &Options.bSkipDialogue))
        {
            if (Options.bSkipDialogue)
            {
                CreateHook(UIScenarioNew::get_Task, UIScenarioNew_get_Task_Hook);
            }
            else
            {
                DeleteHook(UIScenarioNew_get_Task_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("Skips Dialogues");
        ImGui::EndGroupPanel();
    }

    void Start() {
    }
}