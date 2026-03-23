#include "Stats.h"
#include "imgui/imgui.h"
#include "hooks.h"
#include "engine.h"
#include "utils.h"

namespace PlayerStats
{
    struct StatValue {
        int id;
        const char* name;
        int value;
    };

    static std::vector<StatValue> g_Stats = {
     { 1, "Max HP", 0 },
     { 2, "Attack Power", 0 },
     { 3, "Defense Power", 0 },
     { 4, "Heal Power", 0 },
     { 5, "Accuracy Point", 0 },
     { 6, "Accuracy Rate", 0 },
     { 7, "Dodge Point", 0 },
     { 8, "Dodge Rate", 0 },
     { 9, "Critical Point", 0 },
     { 10, "Critical Chance Rate", 0 },
     { 11, "Critical Resist Chance Rate", 0 },
     { 12, "Critical Damage Rate", 0 },
     { 13, "Move Speed", 0 },
     { 14, "Sight Range", 0 },
     { 15, "Active Gauge", 0 },
     { 16, "Stability Point", 0 },
     { 17, "Stability Rate", 0 },
     { 18, "Reload Time", 0 },
     { 19, "Max Bullet Count", 0 },
     { 20, "Ignore Delay Count", 0 },
     { 21, "Weapon Range", 0 },
     { 22, "Block Rate", 0 },
     { 23, "Body Radius", 0 },
     { 24, "Action Count", 0 },
     { 25, "Strategy Mobility", 0 },
     { 26, "Strategy Sight Range", 0 },
     { 27, "Street Battle Adaptation", 0 },
     { 28, "Outdoor Battle Adaptation", 0 },
     { 29, "Indoor Battle Adaptation", 0 },
     { 30, "Heal Effectiveness Rate", 0 },
     { 31, "Critical Chance Resist Point", 0 },
     { 32, "Critical Damage Resist Rate", 0 },
     { 33, "Life Recover On Hit", 0 },
     { 34, "Normal Attack Speed", 0 },
     { 35, "Ammo Cost", 0 },
     { 36, "Groggy Gauge", 0 },
     { 37, "Groggy Time", 0 },
     { 38, "Damage Ratio", 0 },
     { 39, "Damaged Ratio", 0 },
     { 40, "Oppression Power", 0 },
     { 41, "Oppression Resist", 0 },
     { 42, "Regen Cost", 0 },
     { 43, "Initial Weapon Range Rate", 0 },
     { 44, "Defense Penetration", 0 },
     { 45, "Defense Penetration Resist", 0 },
     { 46, "Extend Buff Duration", 0 },
     { 47, "Extend Debuff Duration", 0 },
     { 48, "Extend Crowd Control Duration", 0 },
     { 49, "Enhance Explosion Rate", 0 },
     { 50, "Enhance Pierce Rate", 0 },
     { 51, "Enhance Mystic Rate", 0 },
     { 52, "Enhance Light Armor Rate", 0 },
     { 53, "Enhance Heavy Armor Rate", 0 },
     { 54, "Enhance Unarmed Rate", 0 },
     { 55, "Enhance Siege Rate", 0 },
     { 56, "Enhance Normal Rate", 0 },
     { 57, "Enhance Structure Rate", 0 },
     { 58, "Enhance Normal Armor Rate", 0 },
     { 59, "Damage Ratio 2 Increase", 0 },
     { 60, "Damage Ratio 2 Decrease", 0 },
     { 61, "Damaged Ratio 2 Increase", 0 },
     { 62, "Damaged Ratio 2 Decrease", 0 },
     { 63, "Enhance Sonic Rate", 0 },
     { 64, "Enhance Elastic Armor Rate", 0 },
     { 65, "Ex Damaged Ratio Increase", 0 },
     { 66, "Ex Damaged Ratio Decrease", 0 },
     { 67, "Enhance Ex Damage Rate", 0 },
     { 68, "Reduce Ex Damaged Rate", 0 },
     { 69, "Heal Rate", 0 },
     { 70, "Heal Light Armor Rate", 0 },
     { 71, "Heal Heavy Armor Rate", 0 },
     { 72, "Heal Unarmed Rate", 0 },
     { 73, "Heal Elastic Armor Rate", 0 },
     { 74, "Heal Normal Armor Rate", 0 },
     { 75, "Healed Explosion Rate", 0 },
     { 76, "Healed Pierce Rate", 0 },
     { 77, "Healed Mystic Rate", 0 },
     { 78, "Healed Sonic Rate", 0 },
     { 79, "Healed Normal Rate", 0 },
     { 80, "Growth Score", 0 },
     { 81, "Bullet Type Enhance Rate", 0 },
     { 82, "Max Cost Increase", 0 }
    };

    void ApplyStats(void* battleEntity)
    {
        void* statProc = BattleEntity::statProcessor(battleEntity);
        if (!statProc) return;

        void* currentStat = BattleEntity::get_CurrentStat(battleEntity);
        if (!currentStat) return;

        for (auto& stat : g_Stats)
        {
            if (stat.value == 0) continue;
            BattleEntityStatProcessor::Apply(statProc, stat.id);
            BattleEntityStat::SetValue(currentStat, stat.id, (int64_t)stat.value);
            BattleEntityStatProcessor::InitialStat(statProc) = currentStat;
            BattleEntityStatProcessor::DefaultStat(statProc) = currentStat;
            if (stat.id == 1) 
            {
                BattleEntity::SetHitPoint(battleEntity, (int64_t)stat.value);
            }
        }
    }

    void NewNormalAttackAction_Update_Hook(void* _this, void* battle)
    {
        if (Options.bPlayerStats && IsInBattle())
        {
            void* executer = HeroAction::Executer(_this);
            if (executer)
            {
                if (BattleEntity::TacticEntityType(executer) == 1)
                {
                    ApplyStats(executer);
                }
            }
        }

        CALL_ORIGIN(NewNormalAttackAction_Update_Hook, _this, battle);
    }

    void Render() {
        ImGui::BeginGroupPanel("Player Stats");
        if (ImGui::Checkbox("Stat Mods", &Options.bPlayerStats))
        {
            if (Options.bPlayerStats)
            {
                CreateHook(NewNormalAttackAction::Update, NewNormalAttackAction_Update_Hook);
            }
            else
            {
                DeleteHook(NewNormalAttackAction_Update_Hook);
            }
        }
        ImGui::SameLine();
        ImGui::HelpMarker("Let you change your stats");

        if (Options.bPlayerStats)
        {
            for (auto& stat : g_Stats)
            {
                ImGui::InputInt(stat.name, &stat.value);
            }
        }
        ImGui::EndGroupPanel();
    }

    void Update() {
    }

    void Start() {
    }
}
