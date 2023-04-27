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
    std::pair<std::string,int>(*wargear)(std::string, int, int, std::vector<bool>) = nullptr;
};

class Orks
{
public:

    UnitList ork_units;

    std::string faction = "Orks";
    std::vector<std::string> subfactions = {};
    std::vector<std::string> warlord_traits = {};
    std::vector<std::string> relics = {};
    std::vector<std::string> kustom_jobs = {};
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
        beastboss.wargear = &(beastboss_wargear);
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
        bigmekinmegaarmor.wargear = &(default_wargear);
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
        daredgobboonbounca.wargear = &(default_wargear);
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
        deffkillawartrike.wargear = &(default_wargear);
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
        ghazghkullthraka.wargear = &(default_wargear);
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
        goffrokker.wargear = &(default_wargear);
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
        makari.wargear = &(default_wargear);
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
        painboss.wargear = &(default_wargear);
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
        warbossinmegaarmor.wargear = &(default_wargear);
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
        weirdboy.wargear = &(default_wargear);
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
        zodgrodwortsnagga.wargear = &(default_wargear);
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
        beastsnaggaboyz.wargear = &(default_wargear);
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
        boyz.wargear = &(default_wargear);
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
        gretchin.wargear = &(default_wargear);
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
        kommandos.wargear = &(default_wargear);
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
        meganobz.wargear = &(default_wargear);
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
        deffkoptas.wargear = &(default_wargear);
        ork_units.push_back(deffkoptas);

        // Megatrakk Scrapjet
        Unit megatrakkscrapjet;
        megatrakkscrapjet.model_name = "Megatrakk Scrapjet";
        megatrakkscrapjet.models_owned = 1;
        megatrakkscrapjet.models_used = 0;
        megatrakkscrapjet.model_type = "Fast Attack";
        megatrakkscrapjet.points_per_model = 100;
        megatrakkscrapjet.min_unit_size = 1;
        megatrakkscrapjet.max_unit_size = 3;
        megatrakkscrapjet.wargear = &(default_wargear);
        ork_units.push_back(megatrakkscrapjet);

        // Nob on Smasha Squig
        Unit nobonsmashasquig;
        nobonsmashasquig.model_name = "Nob on Smasha Squig";
        nobonsmashasquig.models_owned = 1;
        nobonsmashasquig.models_used = 0;
        nobonsmashasquig.model_type = "Fast Attack";
        nobonsmashasquig.points_per_model = 65;
        nobonsmashasquig.min_unit_size = 1;
        nobonsmashasquig.max_unit_size = 3;
        nobonsmashasquig.wargear = &(default_wargear);
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
        rukkatrukksquigbuggies.wargear = &(default_wargear);
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
        squighogboyz.wargear = &(default_wargear);
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
        warbikers.wargear = &(default_wargear);
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
        battlewagon.wargear = &(default_wargear);
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
        deffdreads.wargear = &(default_wargear);
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
        killrig.wargear = &(default_wargear);
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
        mekgunz.wargear = &(default_wargear);
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
        dakkajet.wargear = &(default_wargear);
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
        subfactions.push_back("No Clan");

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
                cost = p.points_per_model * std::min(p.max_unit_size, lookupModelsAvailable(p.model_name));
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
                    cost = p.points_per_model * std::min(p.max_unit_size, lookupModelsAvailable(p.model_name));
                    if (cost <= max_cost) result.push_back(p.model_name);
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
    static std::pair<std::string, int> beastboss_wargear(std::string model, int base_points, int max_points, std::vector<bool> flags)
    {
        // We expect 3 flags in: warlord trait, relic, kustom job
        int random;
        int modified_points = base_points;
        std::string result = model;

        if (flags[0]) {
            random = static_cast<int>(rand() % 5);
        }

        return { result, modified_points };
    }
    static std::pair<std::string, int> default_wargear(std::string model, int base_points, int max_points, std::vector<bool> flags)
    {
        std::string result;
        int modified_points = base_points;
        result = model;

        return { result, modified_points };
    }
    std::pair<std::string, int> generateWargear(std::string key, int base_points, int max_points, std::vector<bool> flags)
    {
        for (auto const& p : ork_units) {
            if (p.model_name == key) return p.wargear(key, base_points, max_points, flags);
        }
        return { "Unknown", 0 };
    }

};

class PatrolDetachment
{
public:
    int points = 0;
    int points_max = 0;
    int CP = 0;

    std::string faction;
    std::string subfaction;

    DetachmentRoster units_HQ = {}; // Stores the name of the unit, the point cost, and the CP modifiers
    const int HQ_limit = 2;
    DetachmentRoster units_troops = {}; // Stores the name of the unit, and the point cost
    const int troops_limit = 3;
    DetachmentRoster units_elites = {};
    const int elites_limit = 2;
    DetachmentRoster units_fastattack = {};
    const int fastattack_limit = 2;
    DetachmentRoster units_heavysupport = {};
    const int heavysupport_limit = 2;
    DetachmentRoster units_flyer = {};
    int flyer_limit;
    DetachmentRoster units_dedicatedtransport = {};
    const int dedicatedtransport_limit = 3;

    int warlord_trait_limit = 0;
    int relic_limit = 0;

    PatrolDetachment(int points_limit, DetachmentSlot hq0, DetachmentSlot troop0)
    {
        points_max = points_limit;
        flyer_limit = static_cast<int>(points_limit / 1000);
        CP = static_cast<int>(3 * (points_limit / 500));
        warlord_trait_limit = static_cast<int>(points_limit / 1000);
        relic_limit = 1 + static_cast<int>(points_limit / 1000);
        units_HQ.push_back(hq0);
        units_troops.push_back(troop0);
    }

    void addHQ(DetachmentSlot unit)
    {
        if (units_HQ.size() < HQ_limit) units_HQ.push_back(unit);
    }
    void addTroop(DetachmentSlot unit)
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
    void addDedicatedtransport(DetachmentSlot unit)
    {
        if (units_flyer.size() < flyer_limit) units_flyer.push_back(unit);
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
    int relic_limit = 0;

    ArksOfOmenDetachment() 
    {
        faction = "";
        subfaction = "";
        compulsory_type = "";
        flyer_limit = 0;
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
    void addTroop(DetachmentSlot unit)
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
    void addDedicatedtransport(DetachmentSlot unit)
    {
        if (units_flyer.size() < flyer_limit) units_flyer.push_back(unit);
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

    std::vector<std::string> possible_units;
    int unit_choice;
    std::string unit_choice_name;
    int unit_choice_count;
    int unit_count_range;

    ArksOfOmenDetachment roster1, roster2;
    std::string faction1, faction2;
    std::string subfaction1, subfaction2;
    std::vector<std::string> compulsory_types;
    int troop_count, elites_count, fastattack_count, heavysupport_count;
    std::string compulsory_type1, compulsory_type2;
    int compulsory_type_selection;
    DetachmentSlot warlord1, warlord2;
    DetachmentSlot units1, units2;
    DetachmentRoster compulsory_roster1, compulsory_roster2;
    int compulsory_points1, compulsory_points2;
    std::pair<std::string, int> wargear_result;

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
    subfaction1 = ork.subfactions[(int)(rand() % ork.total_subfactions)];
    if (roster_count != 1) {
        faction2 = ork.faction;
        subfaction2 = ork.subfactions[(int)(rand() % ork.total_subfactions)];
    }

    compulsory_points1 = 0;
    compulsory_points2 = 0;

    // Generate Warlord for Roster 1
    warlord1 = {};
    possible_units = ork.listAvailableModelsUnderCostByType("HQ", points_per_roster);
    unit_choice = static_cast<int>(rand() % ((int)possible_units.size()));
    unit_choice_name = possible_units[unit_choice];
    unit_choice_count = 1;
    warlord1 = ork.generateWargear(unit_choice_name, unit_choice_count * ork.lookupPointsPerModel(unit_choice_name), points_per_roster, { false, false, false });
    ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
    compulsory_points1 += warlord1.second;
    warlord1.first = warlord1.first + " (Warlord) ";

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

        compulsory_type_selection = static_cast<int>(rand() % static_cast<int>(compulsory_types.size()));
        compulsory_type2 = compulsory_types[compulsory_type_selection];

        for (int i = 0; i < 3; i++)
        {
            units2 = {};
            possible_units = ork.listAvailableModelsUnderCostByType(compulsory_type2, points_per_roster - compulsory_points2);
            unit_choice = static_cast<int>(rand() % ((int)possible_units.size()));
            unit_choice_name = possible_units[unit_choice];
            do
            {
                unit_count_range = std::min(ork.lookupModelsAvailable(unit_choice_name), ork.lookupMaxUnitSize(unit_choice_name)) - ork.lookupMinUnitSize(unit_choice_name);
                if (unit_count_range == 0) {
                    unit_choice_count = ork.lookupMinUnitSize(unit_choice_name);
                }
                else {
                    unit_choice_count = (rand() % (unit_count_range + 1)) + ork.lookupMinUnitSize(unit_choice_name);
                }
            } while (unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) % 5 != 0);
            units2 = ork.generateWargear(unit_choice_name, unit_choice_count * ork.lookupPointsPerModel(unit_choice_name), points_per_roster - compulsory_points2, { false, false, false });
            ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
            units2.first = std::to_string(unit_choice_count) + " " + units2.first;
            compulsory_points2 += units2.second;
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

    compulsory_type_selection = static_cast<int>(rand() % static_cast<int>(compulsory_types.size()));
    compulsory_type1 = compulsory_types[compulsory_type_selection];

    for (int i = 0; i < 3; i++)
    {
        units1 = {};
        possible_units = ork.listAvailableModelsUnderCostByType(compulsory_type1, points_per_roster - compulsory_points1);
        unit_choice = static_cast<int>(rand() % ((int)possible_units.size()));
        unit_choice_name = possible_units[unit_choice];
        do
        {
            unit_count_range = std::min(ork.lookupModelsAvailable(unit_choice_name), ork.lookupMaxUnitSize(unit_choice_name)) - ork.lookupMinUnitSize(unit_choice_name);
            if (unit_count_range == 0) {
                unit_choice_count = ork.lookupMinUnitSize(unit_choice_name);
            }
            else {
                unit_choice_count = (rand() % (unit_count_range + 1)) + ork.lookupMinUnitSize(unit_choice_name);
            }
        } while (unit_choice_count * ork.lookupPointsPerModel(unit_choice_name) % 5 != 0);
        units1 = ork.generateWargear(unit_choice_name, unit_choice_count * ork.lookupPointsPerModel(unit_choice_name), points_per_roster - compulsory_points1, { false, false, false });
        ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
        units1.first = std::to_string(unit_choice_count) + " " + units1.first;
        compulsory_points1 += units1.second;
        compulsory_roster1.push_back(units1);
    }

    // Generate a warlord for roster 2
    if (roster_count != 1) {
        warlord2 = {};
        possible_units = ork.listAvailableModelsUnderCostByType("HQ", points_per_roster - compulsory_points2);
        unit_choice = static_cast<int>(rand() % ((int)possible_units.size()));
        unit_choice_name = possible_units[unit_choice];
        unit_choice_count = 1;
        warlord2 = ork.generateWargear(unit_choice_name, unit_choice_count * ork.lookupPointsPerModel(unit_choice_name), points_per_roster - compulsory_points2, { false, false, false });
        ork.setModelsUsed(unit_choice_name, ork.lookupModelsUsed(unit_choice_name) + unit_choice_count);
        warlord2.first = warlord2.first + " (Warlord) ";
        compulsory_points2 += warlord2.second;
    }

    // Initialize detachments

    roster1 = ArksOfOmenDetachment(faction1, subfaction1, points_per_roster, compulsory_type1, warlord1, compulsory_roster1);
    roster1.points += compulsory_points1;

    if (roster_count != 1) {
        roster2 = ArksOfOmenDetachment(faction2, subfaction2, points_per_roster, compulsory_type2, warlord2, compulsory_roster2);
        roster2.points += compulsory_points2;
    }

    // Add units until point limit is reached

    



    




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
