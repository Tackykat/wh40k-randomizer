// WH40k Randomizer.cpp : Defines the entry point for the application.
//

#include "WH40k Randomizer.h"
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <cstdlib>
#include <utility>
#include <vector>
#include <tuple>
#include <set>

// Forward declarations
class Orks;
struct Unit;

// Typedefs
typedef std::pair<std::string, int> DetachmentSlot;
typedef std::vector<DetachmentSlot> DetachmentRoster;
typedef std::vector<Unit> UnitList;

// Unit data structure
struct Unit {
    std::string model_name = {};
    int models_owned = 0;
    int models_used = 0;
    std::string model_type = {};
    int points_per_model = 0;
    int min_unit_size = 0;
    int max_unit_size = 0;
    bool requiredWarlord = false;
    std::vector<std::string> available_warlordtraits = {};
    std::vector<std::string> available_relics = {};
    std::vector<std::string> available_kustomjobs = {};
    std::vector<int> kustomjobs_costs = {};
};
struct WargearInput
{
    std::string key = "None";
    int unit_size = 1;
    int max_points = 0;
    bool take_trait = false;
    bool take_relic = false;
    bool take_kustomjob = false;
    std::vector<std::string> taken_traits = {};
    std::vector<std::string> taken_relics = {};
    std::vector<std::string> taken_kustomjobs = {};
};
struct WargearOutput
{
    std::string output = "None";
    int points = 0;
    bool took_trait = false;
    std::string took_trait_name = {};
    bool took_relic = false;
    std::string took_relic_name = {};
    bool took_kustomjob = false;
    std::string took_kustomjob_name = {};
};

bool isKeyInVector(std::string key, const std::vector<std::string>& values)
{
    if (values.empty()) {
        return false;
    }
    else {
        for (auto const& p : values) {
            if (key == p) return true;
        }
    }
    return false;
}
int randint(int count) {
    if (count == 0 || count == 1) { return 0; }
    else {return (int)(rand() % count);}
    return 0;
}

class Orks
{
public:

    UnitList ork_units;

    std::string faction = "Orks";
    std::vector<std::string> subfactions = {};
    int total_subfactions;

    // Orks get one free relic
    // Strategem: Extra Gubbinz can be used 1 time in a 1k game, and 2 times in a 2k game
    // Strategem: Big Boss can be used 1 time in a 1k game, and 2 times in a 2k game

    Orks()
    {
        // Beastboss
        Unit beastboss;
        beastboss.model_name = "Beastboss";
        beastboss.models_owned = 1;
        beastboss.models_used = 0;
        beastboss.model_type = "HQ";
        beastboss.points_per_model = 95;
        beastboss.min_unit_size = 1;
        beastboss.max_unit_size = 1;
        beastboss.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Clan-specific Trait", "Inspiring Leader", "Big Killa Boss", "BeastGob", "Half-chewed" };
        beastboss.available_relics = { "Beasthide Mantle", "Headwoppa's Killchoppa", "Super Cybork Body", "Clan-specific Relic" };
        beastboss.requiredWarlord = true;
        ork_units.push_back(beastboss);

        // Big Mek in Mega Armor
        Unit bigmekinmegaarmor;
        bigmekinmegaarmor.model_name = "Big Mek in Mega Armor";
        bigmekinmegaarmor.models_owned = 1;
        bigmekinmegaarmor.models_used = 0;
        bigmekinmegaarmor.model_type = "HQ";
        bigmekinmegaarmor.points_per_model = 85;
        bigmekinmegaarmor.min_unit_size = 1;
        bigmekinmegaarmor.max_unit_size = 1;
        bigmekinmegaarmor.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Inspiring Leader", "Clan-specific Trait" };
        bigmekinmegaarmor.available_relics = { "Da Killa Klaw", "Da Krushin' Armor", "Super Cybork Body", "Clan-specific Relic"};
        bigmekinmegaarmor.available_kustomjobs = { "Bionik Oiler" };
        bigmekinmegaarmor.kustomjobs_costs = { 10 };
        ork_units.push_back(bigmekinmegaarmor);

        // Da Red Gobbo on Bounca
        Unit daredgobboonbounca;
        daredgobboonbounca.model_name = "Da Red Gobbo on Bounca";
        daredgobboonbounca.models_owned = 1;
        daredgobboonbounca.models_used = 0;
        daredgobboonbounca.model_type = "HQ";
        daredgobboonbounca.points_per_model = 50;
        daredgobboonbounca.min_unit_size = 1;
        daredgobboonbounca.max_unit_size = 1;
        daredgobboonbounca.available_warlordtraits = { "Inspiring Leader" };
        ork_units.push_back(daredgobboonbounca);

        // Deffkilla Wartrike
        Unit deffkillawartrike;
        deffkillawartrike.model_name = "Deffkilla Wartrike";
        deffkillawartrike.models_owned = 1;
        deffkillawartrike.models_used = 0;
        deffkillawartrike.model_type = "HQ";
        deffkillawartrike.points_per_model = 120;
        deffkillawartrike.min_unit_size = 1;
        deffkillawartrike.max_unit_size = 1;
        deffkillawartrike.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Inspiring Leader", "Clan-specific Trait", "Roadkilla", "Get Up in Their Faces", "Junkboss"};
        deffkillawartrike.available_kustomjobs = { "More Dakka", "Shokka Hull", "Squig-hide Tyres" };
        deffkillawartrike.kustomjobs_costs = { 15, 15, 15 };
        ork_units.push_back(deffkillawartrike);

        // Ghazghkull Thraka
        Unit ghazghkullthraka;
        ghazghkullthraka.model_name = "Ghazghkull Thraka";
        ghazghkullthraka.models_owned = 1;
        ghazghkullthraka.models_used = 0;
        ghazghkullthraka.model_type = "HQ";
        ghazghkullthraka.points_per_model = 300;
        ghazghkullthraka.min_unit_size = 1;
        ghazghkullthraka.max_unit_size = 1;
        ghazghkullthraka.available_warlordtraits = { "Clan-specific Trait" };
        ghazghkullthraka.requiredWarlord = true;
        ork_units.push_back(ghazghkullthraka);

        // Goff Rokker
        Unit goffrokker;
        goffrokker.model_name = "Goff Rokker";
        goffrokker.models_owned = 1;
        goffrokker.models_used = 0;
        goffrokker.model_type = "HQ";
        goffrokker.points_per_model = 40;
        goffrokker.min_unit_size = 1;
        goffrokker.max_unit_size = 1;
        goffrokker.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Inspiring Leader", "Clan-specific Trait" };
        ork_units.push_back(goffrokker);

        // Makari
        Unit makari;
        makari.model_name = "Makari";
        makari.models_owned = 1;
        makari.models_used = 0;
        makari.model_type = "HQ";
        makari.points_per_model = 50;
        makari.min_unit_size = 1;
        makari.max_unit_size = 1;
        makari.available_warlordtraits = { "Follow Me, Ladz!" };
        ork_units.push_back(makari);

        // Painboss
        Unit painboss;
        painboss.model_name = "Painboss";
        painboss.models_owned = 1;
        painboss.models_used = 0;
        painboss.model_type = "HQ";
        painboss.points_per_model = 80;
        painboss.min_unit_size = 1;
        painboss.max_unit_size = 1;
        painboss.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Inspiring Leader", "Clan-specific Trait", "Big Killa Boss", "BeastGob", "Half-Chewed"};
        painboss.available_relics = { "Beasthide Mantle", "Clan-specific Relic", "Super Cybork Body" };
        ork_units.push_back(painboss);

        // Warboss in Mega Armor
        Unit warbossinmegaarmor;
        warbossinmegaarmor.model_name = "Warboss in Mega Armor";
        warbossinmegaarmor.models_owned = 2;
        warbossinmegaarmor.models_used = 0;
        warbossinmegaarmor.model_type = "HQ";
        warbossinmegaarmor.points_per_model = 115;
        warbossinmegaarmor.min_unit_size = 1;
        warbossinmegaarmor.max_unit_size = 1;
        warbossinmegaarmor.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Inspiring Leader", "Clan-specific Trait" };
        warbossinmegaarmor.available_relics = { "Da Krushin' Armor", "Headwoppa's Killchoppa", "Super Cybork Body", "Clan-specific Relic" };
        warbossinmegaarmor.requiredWarlord = true;
        ork_units.push_back(warbossinmegaarmor);

        // Weirdboy
        Unit weirdboy;
        weirdboy.model_name = "Weirdboy";
        weirdboy.models_owned = 1;
        weirdboy.models_used = 0;
        weirdboy.model_type = "HQ";
        weirdboy.points_per_model = 70;
        weirdboy.min_unit_size = 1;
        weirdboy.max_unit_size = 1;
        weirdboy.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Inspiring Leader", "Clan-specific Trait" };
        weirdboy.available_relics = { "Clan-specific Relic", "Scorched Gitbonez", "Super Cybork Body" };
        ork_units.push_back(weirdboy);

        // Zodgrod Wortsnagga
        Unit zodgrodwortsnagga;
        zodgrodwortsnagga.model_name = "Zodgrod Wortsnagga";
        zodgrodwortsnagga.models_owned = 1;
        zodgrodwortsnagga.models_used = 0;
        zodgrodwortsnagga.model_type = "HQ";
        zodgrodwortsnagga.points_per_model = 65;
        zodgrodwortsnagga.min_unit_size = 1;
        zodgrodwortsnagga.max_unit_size = 1;
        zodgrodwortsnagga.available_warlordtraits = { "BeastGob" };
        ork_units.push_back(zodgrodwortsnagga);

        // Beast Snagga Boyz
        Unit beastsnaggaboyz;
        beastsnaggaboyz.model_name = "Beast Snagga Boyz";
        beastsnaggaboyz.models_owned = 10;
        beastsnaggaboyz.models_used = 0;
        beastsnaggaboyz.model_type = "Troops";
        beastsnaggaboyz.points_per_model = 10;
        beastsnaggaboyz.min_unit_size = 10;
        beastsnaggaboyz.max_unit_size = 20;
        ork_units.push_back(beastsnaggaboyz);

        // Boyz
        Unit boyz;
        boyz.model_name = "Boyz";
        boyz.models_owned = 40;
        boyz.models_used = 0;
        boyz.model_type = "Troops";
        boyz.points_per_model = 8;
        boyz.min_unit_size = 10;
        boyz.max_unit_size = 30;
        ork_units.push_back(boyz);

        // Gretchin
        Unit gretchin;
        gretchin.model_name = "Gretchin";
        gretchin.models_owned = 20;
        gretchin.models_used = 0;
        gretchin.model_type = "Troops";
        gretchin.points_per_model = 4;
        gretchin.min_unit_size = 10;
        gretchin.max_unit_size = 30;
        ork_units.push_back(gretchin);

        // Kommandos
        Unit kommandos;
        kommandos.model_name = "Kommandos";
        kommandos.models_owned = 10;
        kommandos.models_used = 0;
        kommandos.model_type = "Elites";
        kommandos.points_per_model = 11;
        kommandos.min_unit_size = 5;
        kommandos.max_unit_size = 15;
        ork_units.push_back(kommandos);

        // Meganobz
        Unit meganobz;
        meganobz.model_name = "Meganobz";
        meganobz.models_owned = 3;
        meganobz.models_used = 0;
        meganobz.model_type = "Elites";
        meganobz.points_per_model = 30;
        meganobz.min_unit_size = 3;
        meganobz.max_unit_size = 10;
        ork_units.push_back(meganobz);

        // DeffKoptas
        Unit deffkoptas;
        deffkoptas.model_name = "Deffkoptas";
        deffkoptas.models_owned = 6;
        deffkoptas.models_used = 0;
        deffkoptas.model_type = "Fast Attack";
        deffkoptas.points_per_model = 50;
        deffkoptas.min_unit_size = 3;
        deffkoptas.max_unit_size = 6;
        ork_units.push_back(deffkoptas);

        // Megatrakk Scrapjets
        Unit megatrakkscrapjets;
        megatrakkscrapjets.model_name = "Megatrakk Scrapjets";
        megatrakkscrapjets.models_owned = 1;
        megatrakkscrapjets.models_used = 0;
        megatrakkscrapjets.model_type = "Fast Attack";
        megatrakkscrapjets.points_per_model = 100;
        megatrakkscrapjets.min_unit_size = 1;
        megatrakkscrapjets.max_unit_size = 3;
        megatrakkscrapjets.available_kustomjobs = { "More Dakka", "Shokka Hull", "Squig-hide Tyres" };
        megatrakkscrapjets.kustomjobs_costs = { 15, 15, 15 };
        ork_units.push_back(megatrakkscrapjets);

        // Nob on Smasha Squig
        Unit nobonsmashasquig;
        nobonsmashasquig.model_name = "Nob on Smasha Squig";
        nobonsmashasquig.models_owned = 1;
        nobonsmashasquig.models_used = 0;
        nobonsmashasquig.model_type = "Fast Attack";
        nobonsmashasquig.points_per_model = 65;
        nobonsmashasquig.min_unit_size = 1;
        nobonsmashasquig.max_unit_size = 3;
        nobonsmashasquig.available_warlordtraits = { "Follow Me, Ladz!", "Big Gob", "'Ard as Nails", "Brutal but Kunnin", "Kunnin but Brutal", "Might is Right", "Inspiring Leader", "Clan-specific Trait", "Big Killa Boss", "BeastGob", "Half-Chewed" };
        nobonsmashasquig.available_relics = { "Beasthide Mantle", "Headwoppa's Killchoppa", "Clan-specific Relic" };
        ork_units.push_back(nobonsmashasquig);

        // Rukkatrukk Squigbuggies
        Unit rukkatrukksquigbuggies;
        rukkatrukksquigbuggies.model_name = "Rukkatrukk Squigbuggies";
        rukkatrukksquigbuggies.models_owned = 1;
        rukkatrukksquigbuggies.models_used = 0;
        rukkatrukksquigbuggies.model_type = "Fast Attack";
        rukkatrukksquigbuggies.points_per_model = 95;
        rukkatrukksquigbuggies.min_unit_size = 1;
        rukkatrukksquigbuggies.max_unit_size = 3;
        rukkatrukksquigbuggies.available_kustomjobs = { "More Dakka", "Nitro Squigs", "Shokka Hull", "Squig-hide Tyres" };
        rukkatrukksquigbuggies.kustomjobs_costs = { 15, 25, 15, 15 };
        ork_units.push_back(rukkatrukksquigbuggies);

        // Squighog Boyz
        Unit squighogboyz;
        squighogboyz.model_name = "Squighog Boys";
        squighogboyz.models_owned = 3;
        squighogboyz.models_used = 0;
        squighogboyz.model_type = "Fast Attack";
        squighogboyz.points_per_model = 25;
        squighogboyz.min_unit_size = 3;
        squighogboyz.max_unit_size = 6;
        ork_units.push_back(squighogboyz);

        // Warbikers
        Unit warbikers;
        warbikers.model_name = "Warbikers";
        warbikers.models_owned = 3;
        warbikers.models_used = 0;
        warbikers.model_type = "Fast Attack";
        warbikers.points_per_model = 25;
        warbikers.min_unit_size = 3;
        warbikers.max_unit_size = 9;
        ork_units.push_back(warbikers);

        // Battlewagon
        Unit battlewagon;
        battlewagon.model_name = "Battlewagon";
        battlewagon.models_owned = 1;
        battlewagon.models_used = 0;
        battlewagon.model_type = "Heavy Support";
        battlewagon.points_per_model = 105;
        battlewagon.min_unit_size = 1;
        battlewagon.max_unit_size = 1;
        battlewagon.available_kustomjobs = { "Da Booma", "Fortress on Wheels", "More Dakka", "Shokka Hull", "Squig-hide Tyres" };
        battlewagon.kustomjobs_costs = { 15, 20, 30, 15, 15 };
        ork_units.push_back(battlewagon);

        // Deff Dreads
        Unit deffdreads;
        deffdreads.model_name = "Deff Dreads";
        deffdreads.models_owned = 1;
        deffdreads.models_used = 0;
        deffdreads.model_type = "Heavy Support";
        deffdreads.points_per_model = 85;
        deffdreads.min_unit_size = 1;
        deffdreads.max_unit_size = 3;
        deffdreads.available_kustomjobs = { "More Dakka", "Shokka Hull", "Stompamatic Pistons" };
        deffdreads.kustomjobs_costs = { 15, 15, 15 };
        ork_units.push_back(deffdreads);

        // Kill Rig
        Unit killrig;
        killrig.model_name = "Kill Rig";
        killrig.models_owned = 1;
        killrig.models_used = 0;
        killrig.model_type = "Heavy Support";
        killrig.points_per_model = 190;
        killrig.min_unit_size = 1;
        killrig.max_unit_size = 1;
        killrig.available_warlordtraits = { "BeastGob" };
        killrig.available_relics = { "Scorched Gitbonez" };
        killrig.available_kustomjobs = { "More Dakka", "Shokka Hull", "Squighide Tyres" };
        killrig.kustomjobs_costs = { 30, 30, 15 };
        ork_units.push_back(killrig);

        // Mek Gunz
        Unit mekgunz;
        mekgunz.model_name = "Mek Gunz";
        mekgunz.models_owned = 1;
        mekgunz.models_used = 0;
        mekgunz.model_type = "Heavy Support";
        mekgunz.points_per_model = 40;
        mekgunz.min_unit_size = 1;
        mekgunz.max_unit_size = 3;
        ork_units.push_back(mekgunz);

        // Dakkajet
        Unit dakkajet;
        dakkajet.model_name = "Dakkajet";
        dakkajet.models_owned = 1;
        dakkajet.models_used = 0;
        dakkajet.model_type = "Flyer";
        dakkajet.points_per_model = 100;
        dakkajet.min_unit_size = 1;
        dakkajet.max_unit_size = 1;
        dakkajet.available_kustomjobs = { "More Dakka", "Shokka Hull" };
        dakkajet.kustomjobs_costs = { 15, 15 };
        ork_units.push_back(dakkajet);

        // Trukk
        //models_owned.insert(std::make_pair("Trukk", 1));
        //models_used.insert(std::make_pair("Trukk", 0));

        // Gorkanaut
        //models_owned.insert(std::make_pair("Gorkanaut", 1));
        //models_used.insert(std::make_pair("Gorkanaut", 0));

        // Subfactions
        subfactions.push_back("Bad Moons");
        subfactions.push_back("Blood Axes");
        subfactions.push_back("Deathskulls");
        subfactions.push_back("Evil Sunz");
        subfactions.push_back("Freebooterz");
        subfactions.push_back("Goffs");
        subfactions.push_back("Snakebites");

        total_subfactions = static_cast<int>(subfactions.size());
    }

    //###################################################################
    // 
    //     SECTION FOR OTHER FUNCTIONS
    //
    //###################################################################

    // Lookup functions
    int lookupModelsOwned(std::string key) 
    {
        for (auto const& p : ork_units) {if (p.model_name == key) return p.models_owned;}
        return 0;
    }
    int lookupModelsUsed(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.models_used; }
        return 0;
    }
    int lookupModelsAvailable(std::string key)
    {
        return (lookupModelsOwned(key) - lookupModelsUsed(key));
    }
    std::string lookupModelType(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.model_type; }
        return "Unknown";
    }
    int lookupPointsPerModel(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.points_per_model; }
        return 0;
    }
    int lookupMinUnitSize(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.min_unit_size; }
        return 0;
    }
    int lookupMaxUnitSize(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.max_unit_size; }
        return 0;
    }
    std::vector<std::string> lookupAvailableWarlordTraits(std::string key) 
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.available_warlordtraits; }
        return {};
    }
    std::vector<std::string> lookupAvailableRelics(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.available_relics; }
        return {};
    }
    std::vector<std::string> lookupAvailableKustomJobs(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.available_kustomjobs; }
        return {};
    }
    std::vector<int> lookupKustomJobsCosts(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.kustomjobs_costs; }
        return {};
    }

    // Setter functions
    void setModelsUsed(std::string key, int val)
    {
        for (auto p = ork_units.begin(); p != ork_units.end(); p++) {
            if ((*p).model_name == key) {
               (*p).models_used = val;
                return; 
            } 
        }
        return;
    }

    // Counter functions
    int countModelTypes(std::string key)
    {
        int count = 0;
        for (auto const& p : ork_units) { if (p.model_type == key) count++; }
        return count;
    }
    int countModelAvailableUnitsByType(std::string key) 
    {
        int count = 0;
        for (auto const& p : ork_units) {if (p.model_type == key) count += (int)((p.models_owned - p.models_used) / p.min_unit_size);}
        return count;
    }
    int countModelAvailableNonWarlordUnitsByType(std::string key)
    {
        int count = 0;
        for (auto const& p : ork_units) { if ((p.model_type == key) && !p.requiredWarlord) count += (int)((p.models_owned - p.models_used) / p.min_unit_size); }
        return count;
    }
    int countModelAvailableUnitsUnderCostByType(std::string key, int max_cost)
    {
        int count = 0;
        int cost;
        for (auto const& p : ork_units) {
            if (p.model_type == key)
            {
                if (lookupModelsAvailable(p.model_name) >= p.min_unit_size) {
                    cost = p.points_per_model * p.min_unit_size;
                    if (cost <= max_cost) count++;
                }
            }
        }
        return count;
    }
    int countModelAvailableNonWarlordUnitsUnderCostByType(std::string key, int max_cost)
    {
        int count = 0;
        int cost;
        for (auto const& p : ork_units) {
            if (p.model_type == key)
            {
                if (p.requiredWarlord == false) {
                    if (lookupModelsAvailable(p.model_name) >= p.min_unit_size) {
                        cost = p.points_per_model * p.min_unit_size;
                        if (cost <= max_cost) count++;
                    }
                }
            }
        }
        return count;
    }


    // List functions
    std::vector<std::string> listModelsByType (std::string key) 
    {
        std::vector<std::string> result = {};
        for (auto const& p : ork_units) { if (p.model_type == key) result.push_back(p.model_name); }
        return result;
    }
    std::vector<std::string> listModelsUnderCost(int cost)
    {
        std::vector<std::string> result = {};
        int max_cost;
        for (auto const& p : ork_units) {
            max_cost = p.points_per_model * std::min(p.max_unit_size, lookupModelsAvailable(p.model_name));
            if (cost <= max_cost) result.push_back(p.model_name); 
        }
        return result;
    }
    std::vector<std::string> listModelsUnderCostByType  (std::string key, int max_cost) 
    {
        std::vector<std::string> result = {};
        int cost;
        for (auto const& p : ork_units) {
            if (p.model_type == key)
            {
                cost = p.points_per_model * p.min_unit_size;
                if (cost <= max_cost) result.push_back(p.model_name);
            }
        }
        return result;
    }
    std::vector<std::string> listAvailableModelsUnderCostByType(std::string key, int max_cost)
    {
        std::vector<std::string> result = {};
        int cost;
        for (auto const& p : ork_units) {
            if (p.model_type == key)
            {
                if (lookupModelsAvailable(p.model_name) >= p.min_unit_size) {
                    cost = p.points_per_model * p.min_unit_size;
                    if (cost <= max_cost) result.push_back(p.model_name);
                }
            }
        }
        return result;
    }
    std::vector<std::string> listAvailableNonWarlordModelsUnderCostByType(std::string key, int max_cost)
    {
        std::vector<std::string> result = {};
        int cost;
        for (auto const& p : ork_units) {
            if (p.model_type == key)
            {
                if (p.requiredWarlord == false) {
                    if (lookupModelsAvailable(p.model_name) >= p.min_unit_size) {
                        cost = p.points_per_model * p.min_unit_size;
                        if (cost <= max_cost) result.push_back(p.model_name);
                    }
                }
            }
        }
        return result;
    }

    //###################################################################
   // 
   //     SECTION FOR WARGEAR
   //
   //###################################################################
    bool takeWargear(double wargear_chance)
    {
        double rand0 = ((double)rand() / (RAND_MAX));
        return (rand0 <= wargear_chance );
    }

    WargearOutput generateWargear(WargearInput war_in)
    {
        // Convert to old arguments
        std::string key = war_in.key;
        int unit_size = war_in.unit_size;
        int max_points = war_in.max_points;
        bool take_trait = war_in.take_trait;
        bool take_relic = war_in.take_relic;
        bool take_kustomjob = war_in.take_kustomjob;
        std::vector<std::string> taken_traits = {};
        std::vector<std::string> taken_relics = {};
        std::vector<std::string> taken_kustomjobs = {};

        // Input flags are if there is room in the detachment for a warlord trait or relic
        WargearOutput result;
        std::string modified_name;
        int modified_points;
        bool took_trait = false;
        bool took_relic = false;
        bool took_kustomjob = false;
        
        int possible_traits = 0;
        int possible_relics = 0;
        int possible_kustomjobs = 0;
        std::string key1;
        int rand1, rand2, rand3;
        bool bool1;
        int count1;
        std::vector<std::string> choices1 = {};
        std::vector<std::string> choices2 = {};
        std::vector<std::string> choices3 = {};
        std::vector<std::string> choices4 = {};

        // Load in necessary model data
        int base_points = unit_size * lookupPointsPerModel(key);
        modified_points = base_points;

        // Build starting result string
        if (lookupModelType(key) == "HQ") {
            result.output = key;
        }
        else {
            result.output = std::to_string(unit_size) + " " + key;
        }

        // Check for warlord traits, relics and kustom jobs
        if (take_trait) possible_traits = static_cast<int>(lookupAvailableWarlordTraits(key).size());
        if (take_relic) possible_relics = static_cast<int>(lookupAvailableRelics(key).size());
        if (take_kustomjob) possible_kustomjobs = static_cast<int>(lookupAvailableKustomJobs(key).size());

        // Warlord Trait
        if (possible_traits > 0) {
            rand1 = randint(possible_traits);
            key1 = lookupAvailableWarlordTraits(key)[rand1];
            if (!isKeyInVector(key1, taken_traits))
            {
                result.output = result.output + " - Warlord Trait: " + key1;
                taken_traits.push_back(key1);
                result.took_trait_name = key1;
                result.took_trait = true;
            }
        }

        // Relics
        if (possible_relics > 0) {
            rand1 = randint(possible_relics);
            key1 = lookupAvailableRelics(key)[rand1];
            if (!isKeyInVector(key1, taken_relics))
            {
                result.output = result.output + " - Relic: " + key1;
                taken_relics.push_back(key1);
                result.took_relic_name = key1;
                result.took_relic = true;
            }
        }

        // Big Mek in Mega Armor
        if (key == "Big Mek in Mega Armor") 
        {
            if (modified_points + 5 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Grot Oiler";
                    modified_points += 5;
                } 
            }
            choices1 = { "Kombi-rokkit", "Kombi-skorcha", "Kustom Mega-Blasta", "Kustom Shoota" };
            if (modified_points + 5 <= max_points) {choices1.push_back("Killsaw");}
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - KMB Arm: " + choices1[rand1];
            if (choices1[rand1] == "Killsaw") modified_points += 5;

            bool1 = false;
            if (modified_points + 30 <= max_points) {
                if (takeWargear(0.50)) {
                    result.output = result.output + " - Kustom Force Field";
                    bool1 = true;
                }
            }
            if (modified_points + 10 <= max_points) {
                if (takeWargear(0.50) && !bool1) {
                    result.output = result.output + " - Tellyport Blasta";
                }
            }

            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
        }

        // Deffkilla Wartrike
        if (key == "Deffkilla Wartrike") {
            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
        }

        // Painboss
        if (key == "Painboss") {
            if (modified_points + 5 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Grot Orderly";
                    modified_points += 5;
                }
            }
            if (modified_points + 5 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Beast Snagga Klaw";
                    modified_points += 5;
                }
            }
        }

        // Weirdboy
        if (key == "Weirdboy") 
        {
            choices1 = {"1. 'Eadbanger", "2. Warpath", "3. Da Jump", "4. Fists of Gork", "5. Da Krunch", "6. Jabbin' Fingerz"};
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - " + choices1[rand1];
            choices2 = {};
            for (auto const& p : choices1) { if (p != choices1[rand1]) choices2.push_back(p); }
            rand2 = randint(static_cast<int>(choices2.size()));
            result.output = result.output + " - " + choices2[rand2];
        }

        

        // Beast Snagga Boyz
        if (key == "Beast Snagga Boyz") {
            if (modified_points + 5 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Beast Snagga Boy w/ Thump Gun";
                    modified_points += 5;
                }
            }
        }

        // Boyz
        if (key == "Boyz") {
            choices1 = {"Choppa", "Slugga"};
            if (modified_points + 5 <= max_points) {
                choices1.push_back("Big Choppa");
                choices1.push_back("Kombi-rokkit");
                choices1.push_back("Kombi-skorcha");
                choices1.push_back("Power Stabba");
                if (modified_points + 10 <= max_points) {
                    choices1.push_back("Killsaw");
                    choices1.push_back("Power Klaw");
                }
            }
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - Boss Nob w/ " + choices1[rand1] + " & ";
            if (choices1[rand1] == "Big Choppa" || choices1[rand1] == "Kombi-rokkit" || choices1[rand1] == "Kombi-skorcha" || choices1[rand1] == "Power Stabba") modified_points += 5;
            if (choices1[rand1] == "Killsaw" || choices1[rand1] == "Power Klaw") modified_points += 10;

            choices2 = { "Choppa", "Slugga" };
            if (modified_points + 5 <= max_points) {
                choices2.push_back("Big Choppa");
                choices2.push_back("Power Stabba");
                if (modified_points + 10 <= max_points) {
                    choices2.push_back("Killsaw");
                    choices2.push_back("Power Klaw");
                }
            }
            rand2 = randint(static_cast<int>(choices2.size()));
            result.output = result.output + choices2[rand2];
            if (choices2[rand2] == "Big Choppa" || choices2[rand2] == "Power Stabba") modified_points += 5;
            if (choices2[rand2] == "Killsaw" || choices2[rand2] == "Power Klaw") modified_points += 10;
        
            choices3 = {};
            if (modified_points + 5 <= max_points) {
                choices3 = { "Big Shoota", "Rokkit Launcha" };
                rand3 = randint(static_cast<int>(choices3.size()));
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Ork Boy w/ 'Eavy Weapon (" + choices3[rand3] + ")";
                    modified_points += 5;
                }
            }
        }

        // Kommandos
        if (key == "Kommandos") 
        {
            choices1 = { "Choppa" };
            if (modified_points + 5 <= max_points) {
                choices1.push_back("Big Choppa");
                choices1.push_back("Power Klaw");
            }
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - Boss Nob w/ " + choices1[rand1] + " & Slugga ";
            if (choices1[rand1] == "Big Choppa" || choices1[rand1] == "Power Klaw") modified_points += 5;
        
            if (unit_size >= 10) {
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.75)) {
                        result.output = result.output + " - Bomb Squig";
                        modified_points += 5;
                    }
                }
                if (modified_points + 10 <= max_points) {
                    if (takeWargear(0.75)) {
                        result.output = result.output + " - Distraction Grot";
                        modified_points += 5;
                    }
                }
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.50)) {
                        result.output = result.output + " - Kommando w/ Big Shoota";
                        modified_points += 5;
                    }
                }
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.50)) {
                        result.output = result.output + " - Kommando w/ Breacha Ram";
                        modified_points += 5;
                    }
                }
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.50)) {
                        result.output = result.output + " - Kommando w/ Burna";
                        modified_points += 5;
                    }
                }
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.50)) {
                        result.output = result.output + " - Kommando w/ Choppa & Shokka Pistol";
                        modified_points += 5;
                    }
                }
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.50)) {
                        result.output = result.output + " - Kommando w/ Kustom Shoota";
                        modified_points += 5;
                    }
                }
                if (modified_points + 10 <= max_points) {
                    if (takeWargear(0.50)) {
                        result.output = result.output + " - Kommando w/ Rokkit Launcha";
                        modified_points += 5;
                    }
                }
            }
        }

        // Meganobz
        if (key == "Meganobz") 
        {
            choices1 = { "Kustom Shoota" };
            if (modified_points + 5 <= max_points) {
                choices1.push_back("Killsaw");
                choices1.push_back("Kombi-rokkit");
                if (modified_points + 10 <= max_points) {
                    choices1.push_back("Kombi-skorcha");
                }
            }
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - Boss Meganob w/ " + choices1[rand1] + " & ";
            if (choices1[rand1] == "Killsaw" || choices1[rand1] == "Kombi-rokkit") modified_points += 5;
            if (choices1[rand1] == "Kombi-skorcha") modified_points += 10;

            choices2 = { "Power Klaw" };
            if (modified_points + 5 <= max_points) {
                choices2.push_back("Killsaw");
            }
            rand2 = randint(static_cast<int>(choices2.size()));
            result.output = result.output + choices2[rand2];
            if (choices2[rand2] == "Killsaw") modified_points += 5;
        
            for (int i = 1; i < unit_size; i++) {
                choices1 = { "Kustom Shoota" };
                if (modified_points + 5 <= max_points) {
                    choices1.push_back("Killsaw");
                    choices1.push_back("Kombi-rokkit");
                    if (modified_points + 10 <= max_points) {
                        choices1.push_back("Kombi-skorcha");
                    }
                }
                rand1 = randint(static_cast<int>(choices1.size()));
                result.output = result.output + " - Meganob w/ " + choices1[rand1] + " & ";
                if (choices1[rand1] == "Killsaw" || choices1[rand1] == "Kombi-rokkit") modified_points += 5;
                if (choices1[rand1] == "Kombi-skorcha") modified_points += 10;

                choices2 = { "Power Klaw" };
                if (modified_points + 5 <= max_points) {
                    choices2.push_back("Killsaw");
                }
                rand2 = randint(static_cast<int>(choices2.size()));
                result.output = result.output + choices2[rand2];
                if (choices2[rand2] == "Killsaw") modified_points += 5;
            }
        }

        // Deffkoptas
        if (key == "Deffkoptas") 
        {
            for (int i = 0; i < (int)(unit_size / 3); i++) {
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.50)) {
                        result.output = result.output + " - Deffkopta w/ KMB & Big Bomb";
                        modified_points += 5;
                    }
                }
            }
        }

        // Megatrakk Scrapjet
        if (key == "Megatrakk Scrapjet") {
            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
        }

        // Rukkatrukk Squigbuggies
        if (key == "Rukkatrukk Sguigbuggies") {
            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
        }

        // Squighog Boyz
        if (key == "Squighog Boyz") {
            if (unit_size >= 3) {
                if (modified_points + 5 <= max_points) {
                    if (takeWargear(0.75)) {
                        result.output = result.output + " - Bomb Squig";
                        modified_points += 5;
                    }
                }
            }
        }

        // Warbikers
        if (key == "Warbikers") {
            choices1 = { "Choppa", "Slugga"};
            if (modified_points + 5 <= max_points) {
                choices1.push_back("Big Choppa");
                if (modified_points + 10 <= max_points) {
                    choices1.push_back("Power Klaw");
                }
            }
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - Boss Nob w/ " + choices1[rand1];
            if (choices1[rand1] == "Big Choppa" ) modified_points += 5;
            if (choices1[rand1] == "Power Klaw") modified_points += 10;
        }

        

        // Battlewagon
        if (key == "Battlewagon") {
            if (modified_points + 15 <= max_points) {
                if (takeWargear(0.50)) {
                    result.output = result.output + " - 'Ard Case";
                    modified_points += 15;
                }
            }
            choices1 = { "None" };
            if (modified_points + 5 <= max_points) {
                choices1.push_back("Kannon");
                choices1.push_back("Zzap Gun");
                if (modified_points + 15 <= max_points) {
                    choices1.push_back("Killkannon");
                }
            }
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - Big Gun: " + choices1[rand1];
            if (choices1[rand1] == "Kannon" || choices1[rand1] == "Zzap Gun") modified_points += 5;
            if (choices1[rand1] == "Killkannon") modified_points += 15;
            count1 = 0;
            for (int i = 0; i<4; i++){
                if (modified_points + 5 * (i + 1) <= max_points) {count1 = i;}
            }
            if (count1 > 0) {
                rand2 = randint(count1);
                result.output = result.output + " - Big Shootas: " + std::to_string(rand2);
                modified_points += (rand2 * 5);
            }
            if (modified_points + 15 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Deffrolla";
                    modified_points += 15;
                }
            }
            if (modified_points + 5 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Grabbin' Klaw";
                    modified_points += 5;
                }
            }
            if (modified_points + 5 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Lobba";
                    modified_points += 5;
                }
            }
            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
            if (modified_points + 5 <= max_points) {
                if (takeWargear(0.75)) {
                    result.output = result.output + " - Wreckin' Ball";
                    modified_points += 5;
                }
            }
        
        }

        // Deff Dread
        if (key == "Deff Dreads") {
            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
            for (int i = 0; i < unit_size; i++) {
                choices1 = { "Big Shoota", "Dread Klaw" };
                if (modified_points + 5 <= max_points) {
                    choices1.push_back("Skorcha");
                    if (modified_points + 10 <= max_points) {
                        choices1.push_back("Kustom Mega-Blasta");
                        choices1.push_back("Rokkit Launcha");
                    }
                }
                rand1 = randint(static_cast<int>(choices1.size()));
                result.output = result.output + " - Deff Dread #" + std::to_string(i+1) + " Arms: ( " + choices1[rand1] + ", ";
                if (choices1[rand1] == "Skorcha") modified_points += 5;
                if (choices1[rand1] == "Kustom Mega-Blasta" || choices1[rand1] == "Rokkit Launcha") modified_points += 10;
                choices1 = { "Big Shoota", "Dread Klaw" };
                if (modified_points + 5 <= max_points) {
                    choices1.push_back("Skorcha");
                    if (modified_points + 10 <= max_points) {
                        choices1.push_back("Kustom Mega-Blasta");
                        choices1.push_back("Rokkit Launcha");
                    }
                }
                rand1 = randint(static_cast<int>(choices1.size()));
                result.output = result.output + choices1[rand1] + ", ";
                if (choices1[rand1] == "Skorcha") modified_points += 5;
                if (choices1[rand1] == "Kustom Mega-Blasta" || choices1[rand1] == "Rokkit Launcha") modified_points += 10;
                choices1 = { "Big Shoota", "Dread Klaw" };
                if (modified_points + 5 <= max_points) {
                    choices1.push_back("Skorcha");
                    if (modified_points + 10 <= max_points) {
                        choices1.push_back("Kustom Mega-Blasta");
                        choices1.push_back("Rokkit Launcha");
                    }
                }
                rand1 = randint(static_cast<int>(choices1.size()));
                result.output = result.output + choices1[rand1] + ", ";
                if (choices1[rand1] == "Skorcha") modified_points += 5;
                if (choices1[rand1] == "Kustom Mega-Blasta" || choices1[rand1] == "Rokkit Launcha") modified_points += 10;
                choices1 = { "Big Shoota", "Dread Klaw" };
                if (modified_points + 5 <= max_points) {
                    choices1.push_back("Skorcha");
                    if (modified_points + 10 <= max_points) {
                        choices1.push_back("Kustom Mega-Blasta");
                        choices1.push_back("Rokkit Launcha");
                    }
                }
                rand1 = randint(static_cast<int>(choices1.size()));
                result.output = result.output + choices1[rand1] + ") ";
                if (choices1[rand1] == "Skorcha") modified_points += 5;
                if (choices1[rand1] == "Kustom Mega-Blasta" || choices1[rand1] == "Rokkit Launcha") modified_points += 10;
            }
        }

        // Kill Rig
        if (key == "Kill Rig") {
            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
            choices1 = { "1. Roar of Mork", "2. Frazzle", "3. Bitin' Jaws", "4. Spirit of Gork", "5. Beastscent", "6. Squiggly Curse" };
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - " + choices1[rand1];
            choices2 = {};
            for (auto const& p : choices1) { if (p != choices1[rand1]) choices2.push_back(p); }
            rand2 = randint(static_cast<int>(choices2.size()));
            result.output = result.output + " - " + choices2[rand2];
        }

        // Mek Gunz
        if (key == "Mek Gunz") {
            choices1 = { "Bubblechukka", "Smasha Gun", "Traktor Kannon" };
            if (modified_points + 5 <= max_points) {
                choices1.push_back("Kustom Mega Kannon");
            }
            rand1 = randint(static_cast<int>(choices1.size()));
            result.output = result.output + " - " + choices1[rand1];
            if (choices1[rand1] == "Kustom Mega Kannon") modified_points += 5;

            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
        }

        // Dakkajet
        if (key == "Dakkajet") {

            choices1 = { "Dakkajet" };
            if (modified_points + 35 <= max_points) choices1.push_back("Burna-bommer");
            if (modified_points + 50 <= max_points) choices1.push_back("Blitza-bommer");
            if (modified_points + 70 <= max_points) choices1.push_back("Wazbom Blastajet");
            rand1 = randint(static_cast<int>(choices1.size()));
            std::string temp_key = choices1[rand1];
            result.output = std::to_string(unit_size) + " " + choices1[rand1];
            if (choices1[rand1] == "Burna-bommer") modified_points += 35;
            if (choices1[rand1] == "Blitza-bommer") modified_points += 50;
            if (choices1[rand1] == "Wazbom Blastajet") modified_points += 70;

            if (temp_key == "Dakkajet") {
                count1 = 0;
                for (int i = 0; i < 2; i++) {
                    if (modified_points + 10 * (i + 1) <= max_points) { count1 = i; }
                }
                if (count1 > 0) {
                    rand2 = randint(count1);
                    result.output = result.output + " - Additional Supa Shootas: " + std::to_string(rand2);
                    modified_points += (rand2 * 10);
                }
            }
            if (temp_key == "Burna-bommer") {
                if (modified_points + 15 <= max_points) {
                    if (takeWargear(0.75)) {
                        result.output = result.output + " - Skorcha Missiles";
                        modified_points += 15;
                    }
                }
            }
            if (temp_key == "Wazbom Blastajet") {
                choices2 = { "Wazbom Mega-Kannons" };
                if (modified_points + 20 <= max_points) choices2.push_back("Tellyport Mega-blastas");
                rand2 = randint(static_cast<int>(choices2.size()));
                result.output = result.output + " - Main Guns: " + choices2[rand2];
                if (choices2[rand2] == "Tellyport Mega-blastas") modified_points += 20;

                choices2 = { "Stikkbomb Flinga" };
                if (modified_points + 20 <= max_points) choices2.push_back("Blastajet Force Field");
                rand2 = randint(static_cast<int>(choices2.size()));
                result.output = result.output + " - " + choices2[rand2];
                if (choices2[rand2] == "Blastajet Force Field") modified_points += 20;

                count1 = 0;
                for (int i = 0; i < 2; i++) {
                    if (modified_points + 10 * (i + 1) <= max_points) { count1 = i; }
                }
                if (count1 > 0) {
                    rand2 = randint(count1);
                    result.output = result.output + " - Additional Supa Shootas: " + std::to_string(rand2);
                    modified_points += (rand2 * 10);
                }
            }

            if (possible_kustomjobs > 0) {
                rand1 = randint(possible_kustomjobs);
                key1 = lookupAvailableKustomJobs(key)[rand1];
                if (modified_points + lookupKustomJobsCosts(key)[rand1] <= max_points) {
                    if (!isKeyInVector(key1, taken_kustomjobs))
                    {
                        result.output = result.output + " - Kustom Job: " + key1;
                        taken_kustomjobs.push_back(key1);
                        result.took_kustomjob_name = key1;
                        result.took_kustomjob = true;
                        modified_points += lookupKustomJobsCosts(key)[rand1];
                    }
                }
            }
        }
        
        // Convert outputs to struct
        
        result.points = modified_points;

        return result;
    }
   
};

class ArksOfOmenDetachment
{
public:
    int points = 0;
    int points_max = 0;
    int CP = 0;

    std::string faction;
    std::string subfaction;
    std::string compulsory_type;

    DetachmentRoster units_HQ = {}; // Stores the name of the unit, the point cost, and the CP modifiers
    int HQ_limit = 4;
    DetachmentRoster units_troops = {}; // Stores the name of the unit, and the point cost
    int troops_limit = 3;
    DetachmentRoster units_elites = {};
    int elites_limit = 3;
    DetachmentRoster units_fastattack = {};
    int fastattack_limit = 3;
    DetachmentRoster units_heavysupport = {};
    int heavysupport_limit = 3;
    DetachmentRoster units_flyer = {};
    int flyer_limit;
    DetachmentRoster units_dedicatedtransport = {};
    int dedicatedtransport_limit = 3;

    int warlord_trait_limit = 0;
    int warlord_trait_count = 0;
    int relic_limit = 0;
    int relic_count = 0;

    bool free_relic; // Have you taken the free relic

    std::vector<std::string> warlord_traits;
    std::vector<std::string> relics;
    std::vector<std::string> kustom_jobs;

    ArksOfOmenDetachment() 
    {
        faction = "";
        subfaction = "";
        compulsory_type = "";
        flyer_limit = 0;

        warlord_traits = {};
        relics = {};
        kustom_jobs = {};

        free_relic = false;
    }

    ArksOfOmenDetachment(std::string fact, std::string subfact, int points_limit, std::string comp_type, DetachmentSlot hq0, DetachmentRoster comp_unit)
    {
        faction = fact;
        subfaction = subfact;
        compulsory_type = comp_type;

        points_max = points_limit;
        CP = static_cast<int>(3 * (points_limit / 500));
        flyer_limit = static_cast<int>(points_limit / 1000);
        warlord_trait_limit = static_cast<int>(points_limit / 1000);
        relic_limit = 1 + static_cast<int>(points_limit / 1000);

        warlord_traits = {};
        relics = {};
        kustom_jobs = {};

        // Add units
        units_HQ.push_back(hq0);
        if (comp_type == "Troops") { 
            troops_limit += 3;
            for (auto const& p : comp_unit) { units_troops.push_back(p); } 
        }
        if (comp_type == "Elites") { 
            elites_limit += 3;
            for (auto const& p : comp_unit) { units_elites.push_back(p); } 
        }
        if (comp_type == "Fast Attack") {
            fastattack_limit += 3;
            for (auto const& p : comp_unit) { units_fastattack.push_back(p); } 
        }
        if (comp_type == "Heavy Support") {
            heavysupport_limit += 3;
            for (auto const& p : comp_unit) { units_heavysupport.push_back(p); }
        }
    }

    void addHQ(DetachmentSlot unit)
    {
        if (units_HQ.size() < HQ_limit) units_HQ.push_back(unit);
    }
    void addTroops(DetachmentSlot unit)
    {
        if (units_troops.size() < troops_limit) units_troops.push_back(unit);
    }
    void addElites(DetachmentSlot unit)
    {
        if (units_elites.size() < elites_limit) units_elites.push_back(unit);
    }
    void addFastAttack(DetachmentSlot unit)
    {
        if (units_fastattack.size() < fastattack_limit) units_fastattack.push_back(unit);
    }
    void addHeavySupport(DetachmentSlot unit)
    {
        if (units_heavysupport.size() < heavysupport_limit) units_heavysupport.push_back(unit);
    }
    void addFlyer(DetachmentSlot unit)
    {
        if (units_flyer.size() < flyer_limit) units_flyer.push_back(unit);
    }
    void addDedicatedTransport(DetachmentSlot unit)
    {
        if (units_flyer.size() < flyer_limit) units_flyer.push_back(unit);
    }
    void addUnit(std::string key, DetachmentSlot unit)
    {
        if (key == "HQ") addHQ(unit);
        if (key == "Troops") addTroops(unit);
        if (key == "Elites") addElites(unit);
        if (key == "Fast Attack") addFastAttack(unit);
        if (key == "Heavy Support") addHeavySupport(unit);
        if (key == "Flyer") addFlyer(unit);
        if (key == "Dedicated Transport") addDedicatedTransport(unit);
        return;
    }

    // Lookup functions
    int lookupPointsAvailable() 
    {
        return static_cast<int>(points_max - points);
    }
    int lookupRemainingSlotsByRole(std::string key) 
    {
        if (key == "HQ") return HQ_limit - (int)units_HQ.size();
        if (key == "Troops") return troops_limit - (int)units_troops.size();
        if (key == "Elites") return elites_limit - (int)units_elites.size();
        if (key == "Fast Attack") return fastattack_limit - (int)units_fastattack.size();
        if (key == "Heavy Support") return heavysupport_limit - (int)units_heavysupport.size();
        if (key == "Flyer") return flyer_limit - (int)units_flyer.size();
        if (key == "Dedicated Transport") return dedicatedtransport_limit - (int)units_dedicatedtransport.size();
        return 0;
    }

    // Roster printer
    void printDetachment()
    {
        std::cout << "++ Arks of Omen Detachment (" << faction << " - " << subfaction << ") [ " << CP << "CP, " << points << "pts] ++" << std::endl;
        std::cout << std::endl;
        std::cout << "Arks of Omen Compulsory Type: " << compulsory_type << std::endl;
        std::cout << std::endl;
        if (units_HQ.size() > 0) {
            std::cout << "+ HQ +" << std::endl;
            for (auto const& p : units_HQ) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
            std::cout << std::endl;
        }
        if (units_troops.size() > 0) {
            std::cout << "+ Troops +" << std::endl;
            for (auto const& p : units_troops) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
            std::cout << std::endl;
        }
        if (units_elites.size() > 0) {
            std::cout << "+ Elites +" << std::endl;
            for (auto const& p : units_elites) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
            std::cout << std::endl;
        }
        if (units_fastattack.size() > 0) {
            std::cout << "+ Fast Attack +" << std::endl;
            for (auto const& p : units_fastattack) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
            std::cout << std::endl;
        }
        if (units_heavysupport.size() > 0) {
            std::cout << "+ Heavy Support +" << std::endl;
            for (auto const& p : units_heavysupport) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
            std::cout << std::endl;
        }
        if (units_flyer.size() > 0) {
            std::cout << "+ Flyer +" << std::endl;
            for (auto const& p : units_flyer) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
            std::cout << std::endl;
        }
        if (units_dedicatedtransport.size() > 0) {
            std::cout << "+ Dedicated Transport +" << std::endl;
            for (auto const& p : units_dedicatedtransport) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
            std::cout << std::endl;
        }
        return;
    }
};

int main()
{

    int points_per_roster;
    int roster_count;

    std::vector<std::string> possible_units, possible_types;
    int unit_choice;
    std::string unit_choice_name;
    int unit_choice_count;
    int unit_count_range;

    ArksOfOmenDetachment roster1, roster2;
    std::string faction1, faction2;
    std::string subfaction1, subfaction2;
    std::vector<std::string> compulsory_types;
    int HQ_count, troop_count, elites_count, fastattack_count, heavysupport_count, flyer_count, dedicatedtransport_count;
    std::string compulsory_type1, compulsory_type2;
    std::string unit_type;
    int compulsory_type_selection;
    DetachmentSlot warlord1, warlord2;
    DetachmentSlot units1, units2;
    DetachmentRoster compulsory_roster1, compulsory_roster2;
    int compulsory_points1, compulsory_points2;
    int compulsory_CP1, compulsory_CP2;
    int compulsory_trait_count1, compulsory_trait_count2;
    std::vector<std::string> compulsory_trait_list1, compulsory_trait_list2;
    int compulsory_relic_count1, compulsory_relic_count2;
    std::vector<std::string> compulsory_relic_list1, compulsory_relic_list2;
    std::vector<std::string> compulsory_kustomjob_list1, compulsory_kustomjob_list2;
    int trait_limit;
    int relic_limit;

    WargearInput wargear_data;
    WargearOutput wargear_result;

    bool roster1_novalidunits, roster2_novalidunits;

    // Welcome message
    std::cout << " -------------------- Warhammer 40k Random Army Generator --------------------" << std::endl;

    // Initialize classes
    Orks ork;

    // Initialize Random Number Generator
    std::srand(std::time(NULL));

    // Prompt User for points limit and number of rosters

    std::cout << "How many points per roster? ";
    std::cin >> points_per_roster;
    std::cout << std::endl;
    std::cout << "How many rosters (1 or 2)? ";
    std::cin >> roster_count;
    if (roster_count != 1) roster_count = 2;
    std::cout << std::endl;

    // Select factions and subfactions
    faction1 = ork.faction;
    subfaction1 = ork.subfactions[randint(ork.total_subfactions)];
    if (roster_count != 1) {
        faction2 = ork.faction;
        subfaction2 = ork.subfactions[randint(ork.total_subfactions)];
    }

    compulsory_points1 = 0;
    compulsory_points2 = 0;
    compulsory_CP1 = 0;
    compulsory_CP2 = 0;
    compulsory_trait_count1 = 0;
    compulsory_trait_count2 = 0;
    compulsory_relic_count1 = 0;
    compulsory_relic_count2 = 0;
    compulsory_trait_list1 = {};
    compulsory_trait_list2 = {};
    compulsory_relic_list1 = {};
    compulsory_relic_list2 = {};
    compulsory_kustomjob_list1 = {};
    compulsory_kustomjob_list2 = {};
    trait_limit = static_cast<int>(points_per_roster / 1000);
    relic_limit = 1 + static_cast<int>(points_per_roster / 1000);

    // Generate Warlord for Roster 1
    warlord1 = {};
    possible_units = ork.listAvailableModelsUnderCostByType("HQ", points_per_roster);
    unit_choice = randint(static_cast<int>(possible_units.size()));
    unit_choice_name = possible_units[unit_choice];
    unit_choice_count = 1;
    wargear_data = {};
    wargear_data.key = unit_choice_name;
    wargear_data.unit_size = unit_choice_count;
    wargear_data.max_points = points_per_roster;
    if (compulsory_trait_count1 < trait_limit) { wargear_data.take_trait = true; }
    else { wargear_data.take_trait = false; }
    if (compulsory_relic_count1 < relic_limit) { wargear_data.take_relic = true; }
    else { wargear_data.take_relic = false; }
    wargear_data.take_kustomjob = true;
    wargear_data.taken_traits = compulsory_trait_list1;
    wargear_data.taken_relics = compulsory_relic_list1;
    wargear_data.taken_kustomjobs = compulsory_kustomjob_list1;
    wargear_result = ork.generateWargear(wargear_data);
    ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
    warlord1 = {wargear_result.output, wargear_result.points};
    warlord1.first = warlord1.first + " (Warlord)";
    compulsory_points1 += warlord1.second;
    if (wargear_result.took_trait) { 
        compulsory_CP1--; 
        compulsory_trait_count1++;
        compulsory_trait_list1.push_back(wargear_result.took_trait_name);
    }
    if (wargear_result.took_relic) {
        compulsory_CP1--;
        compulsory_relic_count1++;
        compulsory_relic_list1.push_back(wargear_result.took_relic_name);
    }
    if (wargear_result.took_kustomjob) 
    {
        compulsory_kustomjob_list1.push_back(wargear_result.took_kustomjob_name);
    }

    // Generate compulsory slots for Roster 2
    if (roster_count != 1) {
        units2 = {};
        compulsory_roster2 = {};

        compulsory_types = {};
        troop_count = ork.countModelAvailableUnitsByType("Troops");
        elites_count = ork.countModelAvailableUnitsByType("Elites");
        fastattack_count = ork.countModelAvailableUnitsByType("Fast Attack");
        heavysupport_count = ork.countModelAvailableUnitsByType("Heavy Support");

        if (troop_count >= 3) compulsory_types.push_back("Troops");
        if (elites_count >= 3) compulsory_types.push_back("Elites");
        if (fastattack_count >= 3) compulsory_types.push_back("Fast Attack");
        if (heavysupport_count >= 3) compulsory_types.push_back("Heavy Support");

        compulsory_type_selection = randint(static_cast<int>(compulsory_types.size()));
        compulsory_type2 = compulsory_types[compulsory_type_selection];

        for (int i = 0; i < 3; i++)
        {
            units2 = {};
            possible_units = ork.listAvailableModelsUnderCostByType(compulsory_type2, points_per_roster - compulsory_points2);
            unit_choice = randint(static_cast<int>(possible_units.size()));
            unit_choice_name = possible_units[unit_choice];
            do
            {
                unit_count_range = std::min(ork.lookupModelsAvailable(unit_choice_name), ork.lookupMaxUnitSize(unit_choice_name)) - ork.lookupMinUnitSize(unit_choice_name);
                if (unit_count_range == 0) {
                    unit_choice_count = ork.lookupMinUnitSize(unit_choice_name);
                }
                else {
                    unit_choice_count = randint(unit_count_range + 1) + ork.lookupMinUnitSize(unit_choice_name);
                }
            } while (unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) % 5 != 0);
            wargear_data = {};
            wargear_data.key = unit_choice_name;
            wargear_data.unit_size = unit_choice_count;
            wargear_data.max_points = points_per_roster;
            if (compulsory_trait_count2 < trait_limit) { wargear_data.take_trait = true; }
            else { wargear_data.take_trait = false; }
            if (compulsory_relic_count2 < relic_limit) { wargear_data.take_relic = true; }
            else { wargear_data.take_relic = false; }
            wargear_data.take_kustomjob = true;
            wargear_data.taken_traits = compulsory_trait_list2;
            wargear_data.taken_relics = compulsory_relic_list2;
            wargear_data.taken_kustomjobs = compulsory_kustomjob_list2;
            wargear_result = ork.generateWargear(wargear_data);
            ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
            units2 = { wargear_result.output, wargear_result.points };
            compulsory_points2 += units2.second;
            if (wargear_result.took_trait) {
                compulsory_CP2--;
                compulsory_trait_count2++;
                compulsory_trait_list2.push_back(wargear_result.took_trait_name);
            }
            if (wargear_result.took_relic) {
                compulsory_CP2--;
                compulsory_relic_count2++;
                compulsory_relic_list2.push_back(wargear_result.took_relic_name);
            }
            if (wargear_result.took_kustomjob)
            {
                compulsory_kustomjob_list2.push_back(wargear_result.took_kustomjob_name);
            }
            compulsory_roster2.push_back(units2);
        }
    }

    // Generate compulsory slots for roster 1
    units1 = {};
    compulsory_roster1 = {};

    compulsory_types = {};
    troop_count = ork.countModelAvailableUnitsByType("Troops");
    elites_count = ork.countModelAvailableUnitsByType("Elites");
    fastattack_count = ork.countModelAvailableUnitsByType("Fast Attack");
    heavysupport_count = ork.countModelAvailableUnitsByType("Heavy Support");

    if (troop_count >= 3) compulsory_types.push_back("Troops");
    if (elites_count >= 3) compulsory_types.push_back("Elites");
    if (fastattack_count >= 3) compulsory_types.push_back("Fast Attack");
    if (heavysupport_count >= 3) compulsory_types.push_back("Heavy Support");

    compulsory_type_selection = randint(static_cast<int>(compulsory_types.size()));
    compulsory_type1 = compulsory_types[compulsory_type_selection];

    for (int i = 0; i < 3; i++)
    {
        units1 = {};
        possible_units = ork.listAvailableModelsUnderCostByType(compulsory_type1, points_per_roster - compulsory_points1);
        unit_choice = randint(static_cast<int>(possible_units.size()));
        unit_choice_name = possible_units[unit_choice];
        do
        {
            unit_count_range = std::min(ork.lookupModelsAvailable(unit_choice_name), ork.lookupMaxUnitSize(unit_choice_name)) - ork.lookupMinUnitSize(unit_choice_name);
            if (unit_count_range == 0) {
                unit_choice_count = ork.lookupMinUnitSize(unit_choice_name);
            }
            else {
                unit_choice_count = randint(unit_count_range + 1) + ork.lookupMinUnitSize(unit_choice_name);
            }
        } while (unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) % 5 != 0);
        wargear_data = {};
        wargear_data.key = unit_choice_name;
        wargear_data.unit_size = unit_choice_count;
        wargear_data.max_points = points_per_roster;
        if (compulsory_trait_count1 < trait_limit) { wargear_data.take_trait = true; }
        else { wargear_data.take_trait = false; }
        if (compulsory_relic_count1 < relic_limit) { wargear_data.take_relic = true; }
        else { wargear_data.take_relic = false; }
        wargear_data.take_kustomjob = true;
        wargear_data.taken_traits = compulsory_trait_list1;
        wargear_data.taken_relics = compulsory_relic_list1;
        wargear_data.taken_kustomjobs = compulsory_kustomjob_list1;
        wargear_result = ork.generateWargear(wargear_data);
        ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
        units1 = { wargear_result.output, wargear_result.points };
        compulsory_points1 += units1.second;
        if (wargear_result.took_trait) {
            compulsory_CP1--;
            compulsory_trait_count1++;
            compulsory_trait_list1.push_back(wargear_result.took_trait_name);
        }
        if (wargear_result.took_relic) {
            compulsory_CP1--;
            compulsory_relic_count1++;
            compulsory_relic_list1.push_back(wargear_result.took_relic_name);
        }
        if (wargear_result.took_kustomjob)
        {
            compulsory_kustomjob_list1.push_back(wargear_result.took_kustomjob_name);
        }
        compulsory_roster1.push_back(units1);
    }

    // Generate a warlord for roster 2
    if (roster_count != 1) {
        warlord2 = {};
        possible_units = ork.listAvailableModelsUnderCostByType("HQ", points_per_roster);
        unit_choice = randint(static_cast<int>(possible_units.size()));
        unit_choice_name = possible_units[unit_choice];
        unit_choice_count = 1;
        wargear_data = {};
        wargear_data.key = unit_choice_name;
        wargear_data.unit_size = unit_choice_count;
        wargear_data.max_points = points_per_roster;
        if (compulsory_trait_count2 < trait_limit) { wargear_data.take_trait = true; }
        else { wargear_data.take_trait = false; }
        if (compulsory_relic_count2 < relic_limit) { wargear_data.take_relic = true; }
        else { wargear_data.take_relic = false; }
        wargear_data.take_kustomjob = true;
        wargear_data.taken_traits = compulsory_trait_list2;
        wargear_data.taken_relics = compulsory_relic_list2;
        wargear_data.taken_kustomjobs = compulsory_kustomjob_list2;
        wargear_result = ork.generateWargear(wargear_data);
        ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
        warlord2 = { wargear_result.output, wargear_result.points };
        warlord2.first = warlord2.first + " (Warlord)";
        compulsory_points2 += warlord2.second;
        if (wargear_result.took_trait) {
            compulsory_CP2--;
            compulsory_trait_count2++;
            compulsory_trait_list2.push_back(wargear_result.took_trait_name);
        }
        if (wargear_result.took_relic) {
            compulsory_CP2--;
            compulsory_relic_count2++;
            compulsory_relic_list2.push_back(wargear_result.took_relic_name);
        }
        if (wargear_result.took_kustomjob)
        {
            compulsory_kustomjob_list2.push_back(wargear_result.took_kustomjob_name);
        }
    }

    // Initialize detachments

    roster1 = ArksOfOmenDetachment(faction1, subfaction1, points_per_roster, compulsory_type1, warlord1, compulsory_roster1);
    roster1.points += compulsory_points1;
    roster1.CP += compulsory_CP1;
    roster1.warlord_traits = compulsory_trait_list1;
    roster1.warlord_trait_count = compulsory_trait_count1;
    roster1.relics = compulsory_relic_list1;
    roster1.relic_count = compulsory_relic_count1;
    if (compulsory_relic_count1 > 0) {
        roster1.free_relic = true;
        roster1.CP++;
    }
    roster1.kustom_jobs = compulsory_kustomjob_list1;

    if (roster_count != 1) {
        roster2 = ArksOfOmenDetachment(faction2, subfaction2, points_per_roster, compulsory_type2, warlord2, compulsory_roster2);
        roster2.points += compulsory_points2;
        roster2.CP += compulsory_CP2;
        roster2.warlord_traits = compulsory_trait_list2;
        roster2.warlord_trait_count = compulsory_trait_count2;
        roster2.relics = compulsory_relic_list2;
        roster2.relic_count = compulsory_relic_count2;
        if (compulsory_relic_count2 > 0) {
            roster2.free_relic = true;
            roster2.CP++;
        }
        roster2.kustom_jobs = compulsory_kustomjob_list2;
    }

    // Add units until point limit is reached
    roster1_novalidunits = false;
    roster2_novalidunits = false;
    while ((roster1.points < roster1.points_max) || (roster2.points < roster2.points_max)) 
    {
        if (!roster1_novalidunits) {
            // Generate a unit for roster 1
            possible_types = {};
            HQ_count = ork.countModelAvailableNonWarlordUnitsUnderCostByType("HQ", roster1.lookupPointsAvailable());
            troop_count = ork.countModelAvailableUnitsUnderCostByType("Troops", roster1.lookupPointsAvailable());
            elites_count = ork.countModelAvailableUnitsUnderCostByType("Elites", roster1.lookupPointsAvailable());
            fastattack_count = ork.countModelAvailableUnitsUnderCostByType("Fast Attack", roster1.lookupPointsAvailable());
            heavysupport_count = ork.countModelAvailableUnitsUnderCostByType("Heavy Support", roster1.lookupPointsAvailable());
            flyer_count = ork.countModelAvailableUnitsUnderCostByType("Flyer", roster1.lookupPointsAvailable());
            dedicatedtransport_count = ork.countModelAvailableUnitsUnderCostByType("Dedicated Transport", roster1.lookupPointsAvailable());

            if ((HQ_count > 0) && (roster1.units_HQ.size() < roster1.HQ_limit))  possible_types.push_back("HQ");
            if ((troop_count > 0) && (roster1.units_troops.size() < roster1.troops_limit)) possible_types.push_back("Troops");
            if ((elites_count > 0) && (roster1.units_elites.size() < roster1.elites_limit)) possible_types.push_back("Elites");
            if ((fastattack_count > 0) && (roster1.units_fastattack.size() < roster1.fastattack_limit)) possible_types.push_back("Fast Attack");
            if ((heavysupport_count > 0) && (roster1.units_heavysupport.size() < roster1.heavysupport_limit)) possible_types.push_back("Heavy Support");
            if ((flyer_count > 0) && (roster1.units_flyer.size() < roster1.flyer_limit)) possible_types.push_back("Flyer");
            if ((dedicatedtransport_count > 0) && (roster1.units_dedicatedtransport.size() < roster1.dedicatedtransport_limit)) possible_types.push_back("Dedicated Transport");

            if (possible_types.size() == 0) {
                roster1_novalidunits = true;
            }
            else {
                unit_type = possible_types[randint(static_cast<int>(possible_types.size()))];
                possible_units = {};
                possible_units = ork.listAvailableNonWarlordModelsUnderCostByType(unit_type, roster1.points_max - roster1.points);
                if (possible_units.size() > 0) {

                    unit_choice = randint(static_cast<int>(possible_units.size()));
                    unit_choice_name = possible_units[unit_choice];

                    do
                    {
                        unit_count_range = std::min(ork.lookupModelsAvailable(unit_choice_name), ork.lookupMaxUnitSize(unit_choice_name)) - ork.lookupMinUnitSize(unit_choice_name);
                        if (unit_count_range == 0) {
                            unit_choice_count = ork.lookupMinUnitSize(unit_choice_name);
                        }
                        else {
                            unit_choice_count = randint(unit_count_range + 1) + ork.lookupMinUnitSize(unit_choice_name);
                        }
                    } while ((unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) % 5 != 0) || (unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) > roster1.lookupPointsAvailable()));

                    units1 = {};
                    wargear_data = {};
                    wargear_data.key = unit_choice_name;
                    wargear_data.unit_size = unit_choice_count;
                    wargear_data.max_points = roster1.lookupPointsAvailable();
                    if (roster1.warlord_trait_count < roster1.warlord_trait_limit) { wargear_data.take_trait = true; }
                    else { wargear_data.take_trait = false; }
                    if (roster1.relic_count < roster1.relic_limit) { wargear_data.take_relic = true; }
                    else { wargear_data.take_relic = false; }
                    wargear_data.take_kustomjob = true;
                    wargear_data.taken_traits = roster1.warlord_traits;
                    wargear_data.taken_relics = roster1.relics;
                    wargear_data.taken_kustomjobs = roster1.kustom_jobs;
                    wargear_result = ork.generateWargear(wargear_data);
                    ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
                    units1 = { wargear_result.output, wargear_result.points };
                    roster1.points += units1.second;
                    if (wargear_result.took_trait) {
                        roster1.CP--;
                        roster1.warlord_trait_count++;
                        roster1.warlord_traits.push_back(wargear_result.took_trait_name);
                    }
                    if (wargear_result.took_relic) {
                        if (roster1.free_relic) { 
                            roster1.CP--; 
                        } else { 
                            roster1.free_relic = true; 
                        }
                        roster1.relic_count++;
                        roster1.relics.push_back(wargear_result.took_relic_name);
                    }
                    if (wargear_result.took_kustomjob)
                    {
                        roster1.kustom_jobs.push_back(wargear_result.took_kustomjob_name);
                    }
                    roster1.addUnit(unit_type, units1);

                    // Miscellaneous stuff because reasons
                    if (unit_choice_name == "Big Mek in Mega Armor") ork.setModelsUsed("Meganobz", ork.lookupModelsUsed("Meganobz") + 1);
                    if (unit_choice_name == "Meganobz") ork.setModelsUsed("Big Mek in Mega Armor", ork.lookupModelsUsed("Big Mek in Mega Armor") + 1);

                }
            }
        }

        if (roster_count != 1) {
            if (!roster2_novalidunits) {
                // Generate a unit for roster 1
                possible_types = {};
                HQ_count = ork.countModelAvailableNonWarlordUnitsUnderCostByType("HQ", roster2.lookupPointsAvailable());
                troop_count = ork.countModelAvailableUnitsUnderCostByType("Troops", roster2.lookupPointsAvailable());
                elites_count = ork.countModelAvailableUnitsUnderCostByType("Elites", roster2.lookupPointsAvailable());
                fastattack_count = ork.countModelAvailableUnitsUnderCostByType("Fast Attack", roster2.lookupPointsAvailable());
                heavysupport_count = ork.countModelAvailableUnitsUnderCostByType("Heavy Support", roster2.lookupPointsAvailable());
                flyer_count = ork.countModelAvailableUnitsUnderCostByType("Flyer", roster2.lookupPointsAvailable());
                dedicatedtransport_count = ork.countModelAvailableUnitsUnderCostByType("Dedicated Transport", roster2.lookupPointsAvailable());

                if ((HQ_count > 0) && (roster2.units_HQ.size() < roster2.HQ_limit))  possible_types.push_back("HQ");
                if ((troop_count > 0) && (roster2.units_troops.size() < roster2.troops_limit)) possible_types.push_back("Troops");
                if ((elites_count > 0) && (roster2.units_elites.size() < roster2.elites_limit)) possible_types.push_back("Elites");
                if ((fastattack_count > 0) && (roster2.units_fastattack.size() < roster2.fastattack_limit)) possible_types.push_back("Fast Attack");
                if ((heavysupport_count > 0) && (roster2.units_heavysupport.size() < roster2.heavysupport_limit)) possible_types.push_back("Heavy Support");
                if ((flyer_count > 0) && (roster2.units_flyer.size() < roster2.flyer_limit)) possible_types.push_back("Flyer");
                if ((dedicatedtransport_count > 0) && (roster2.units_dedicatedtransport.size() < roster2.dedicatedtransport_limit)) possible_types.push_back("Dedicated Transport");

                if (possible_types.size() == 0) {
                    roster2_novalidunits = true;
                }
                else {
                    unit_type = possible_types[randint(static_cast<int>(possible_types.size()))];
                    possible_units = {};
                    possible_units = ork.listAvailableNonWarlordModelsUnderCostByType(unit_type, roster2.points_max - roster2.points);
                    if (possible_units.size() > 0) {

                        unit_choice = randint(static_cast<int>(possible_units.size()));
                        unit_choice_name = possible_units[unit_choice];

                        do
                        {
                            unit_count_range = std::min(ork.lookupModelsAvailable(unit_choice_name), ork.lookupMaxUnitSize(unit_choice_name)) - ork.lookupMinUnitSize(unit_choice_name);
                            if (unit_count_range == 0) {
                                unit_choice_count = ork.lookupMinUnitSize(unit_choice_name);
                            }
                            else {
                                unit_choice_count = randint(unit_count_range + 1) + ork.lookupMinUnitSize(unit_choice_name);
                            }
                        } while ((unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) % 5 != 0) || (unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) > roster2.lookupPointsAvailable()));

                        units2 = {};
                        wargear_data = {};
                        wargear_data.key = unit_choice_name;
                        wargear_data.unit_size = unit_choice_count;
                        wargear_data.max_points = roster2.lookupPointsAvailable();
                        if (roster2.warlord_trait_count < roster2.warlord_trait_limit) { wargear_data.take_trait = true; }
                        else { wargear_data.take_trait = false; }
                        if (roster2.relic_count < roster2.relic_limit) { wargear_data.take_relic = true; }
                        else { wargear_data.take_relic = false; }
                        wargear_data.take_kustomjob = true;
                        wargear_data.taken_traits = roster2.warlord_traits;
                        wargear_data.taken_relics = roster2.relics;
                        wargear_data.taken_kustomjobs = roster2.kustom_jobs;
                        wargear_result = ork.generateWargear(wargear_data);
                        ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
                        units2 = { wargear_result.output, wargear_result.points };
                        roster2.points += units2.second;
                        if (wargear_result.took_trait) {
                            roster2.CP--;
                            roster2.warlord_trait_count++;
                            roster2.warlord_traits.push_back(wargear_result.took_trait_name);
                        }
                        if (wargear_result.took_relic) {
                            if (roster2.free_relic) {
                                roster2.CP--;
                            }
                            else {
                                roster2.free_relic = true;
                            }
                            roster2.relic_count++;
                            roster2.relics.push_back(wargear_result.took_relic_name);
                        }
                        if (wargear_result.took_kustomjob)
                        {
                            roster2.kustom_jobs.push_back(wargear_result.took_kustomjob_name);
                        }
                        roster2.addUnit(unit_type, units2);

                        // Miscellaneous stuff because reasons
                        if (unit_choice_name == "Big Mek in Mega Armor") ork.setModelsUsed("Meganobz", ork.lookupModelsUsed("Meganobz") + 1);
                        if (unit_choice_name == "Meganobz") ork.setModelsUsed("Big Mek in Mega Armor", ork.lookupModelsUsed("Big Mek in Mega Armor") + 1);

                    }
                }
            }
        }

        if ((roster_count == 1 && roster1_novalidunits) || (roster_count != 1 && roster1_novalidunits && roster2_novalidunits)) break;
    }

    // Print out detachments

    std::cout << " --------------------  Roster 1  ----------------------------" << std::endl;
    roster1.printDetachment();
    std::cout << std::endl;

    if (roster_count != 1) {
        std::cout << " --------------------  Roster 2  ----------------------------" << std::endl;
        roster2.printDetachment();
        std::cout << std::endl;
    }

    return 0;
}
