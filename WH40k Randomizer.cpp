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
typedef std::pair<std::string, int> Selection; // Key & index for unit selecting
typedef std::vector<Selection> SelectionList;
typedef std::vector<Unit> UnitList;
typedef std::vector<Enhancement> EnhancementList;

// Unit data structure
struct Unit {
    std::string model_name = {};
    int models_owned = 0;
    int models_used = 0;
    std::vector<int> points_per_unit = { 0 };
    std::vector<int> unit_sizes = { 0 };
    bool required_warlord = false;
    bool is_character = false;
};
struct Enhancement {
    std::string enhancement_name = {};
    bool trait_taken = false;
    int points_cost = 0;
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
    EnhancementList ork_enhancements;

    Orks()
    {
        // Beastboss
        Unit beastboss;
        beastboss.model_name = "Beastboss";
        beastboss.models_owned = 1;
        beastboss.models_used = 0;
        beastboss.points_per_unit = { 80 };
        beastboss.unit_sizes = { 1 };
        beastboss.required_warlord = false;
        beastboss.is_character = true;
        ork_units.push_back(beastboss);

        // Big Mek in Mega Armor
        Unit bigmekinmegaarmor;
        bigmekinmegaarmor.model_name = "Big Mek in Mega Armor";
        bigmekinmegaarmor.models_owned = 1;
        bigmekinmegaarmor.models_used = 0;
        bigmekinmegaarmor.points_per_unit = { 100 };
        bigmekinmegaarmor.unit_sizes = { 1 };
        bigmekinmegaarmor.required_warlord = false;
        bigmekinmegaarmor.is_character = true;
        ork_units.push_back(bigmekinmegaarmor);

        // Deffkilla Wartrike
        Unit deffkillawartrike;
        deffkillawartrike.model_name = "Deffkilla Wartrike";
        deffkillawartrike.models_owned = 1;
        deffkillawartrike.models_used = 0;
        deffkillawartrike.points_per_unit = { 90 };
        deffkillawartrike.unit_sizes = { 1 };
        deffkillawartrike.required_warlord = false;
        deffkillawartrike.is_character = false;
        ork_units.push_back(deffkillawartrike);

        // Ghazghkull Thraka
        Unit ghazghkullthraka;
        ghazghkullthraka.model_name = "Ghazghkull Thraka";
        ghazghkullthraka.models_owned = 1;
        ghazghkullthraka.models_used = 0;
        ghazghkullthraka.points_per_unit = { 235 };
        ghazghkullthraka.unit_sizes = { 1 };
        ghazghkullthraka.required_warlord = false;
        ghazghkullthraka.is_character = false;
        ork_units.push_back(ghazghkullthraka);

        // Painboss
        Unit painboss;
        painboss.model_name = "Painboss";
        painboss.models_owned = 1;
        painboss.models_used = 0;
        painboss.points_per_unit = { 70 };
        painboss.unit_sizes = { 1 };
        painboss.required_warlord = false;
        painboss.is_character = false;
        ork_units.push_back(painboss);

        // Warboss in Mega Armor
        Unit warbossinmegaarmor;
        warbossinmegaarmor.model_name = "Warboss in Mega Armor";
        warbossinmegaarmor.models_owned = 2;
        warbossinmegaarmor.models_used = 0;
        warbossinmegaarmor.points_per_unit = { 95 };
        warbossinmegaarmor.unit_sizes = { 1 };
        warbossinmegaarmor.required_warlord = false;
        warbossinmegaarmor.is_character = false;
        ork_units.push_back(warbossinmegaarmor);

        // Weirdboy
        Unit weirdboy;
        weirdboy.model_name = "Weirdboy";
        weirdboy.models_owned = 1;
        weirdboy.models_used = 0;
        weirdboy.points_per_unit = { 55 };
        weirdboy.unit_sizes = { 1 };
        weirdboy.required_warlord = false;
        weirdboy.is_character = false;
        ork_units.push_back(weirdboy);

        // Zodgrod Wortsnagga
        Unit zodgrodwortsnagga;
        zodgrodwortsnagga.model_name = "Zodgrod Wortsnagga";
        zodgrodwortsnagga.models_owned = 1;
        zodgrodwortsnagga.models_used = 0;
        zodgrodwortsnagga.points_per_unit = { 80 };
        zodgrodwortsnagga.unit_sizes = { 1 };
        zodgrodwortsnagga.required_warlord = false;
        zodgrodwortsnagga.is_character = false;
        ork_units.push_back(zodgrodwortsnagga);

        // Beast Snagga Boyz
        Unit beastsnaggaboyz;
        beastsnaggaboyz.model_name = "Beast Snagga Boyz";
        beastsnaggaboyz.models_owned = 10;
        beastsnaggaboyz.models_used = 0;
        beastsnaggaboyz.points_per_unit = { 105, 210 };
        beastsnaggaboyz.unit_sizes = { 10, 20 };
        beastsnaggaboyz.required_warlord = false;
        beastsnaggaboyz.is_character = false;
        ork_units.push_back(beastsnaggaboyz);

        // Boyz
        Unit boyz;
        boyz.model_name = "Boyz";
        boyz.models_owned = 40;
        boyz.models_used = 0;
        boyz.points_per_unit = { 85, 170 };
        boyz.unit_sizes = { 10, 20 };
        boyz.required_warlord = false;
        boyz.is_character = false;
        ork_units.push_back(boyz);

        // Gretchin
        Unit gretchin;
        gretchin.model_name = "Gretchin";
        gretchin.models_owned = 20;
        gretchin.models_used = 0;
        gretchin.points_per_unit = { 45, 90 };
        gretchin.unit_sizes = { 10, 20 };
        gretchin.required_warlord = false;
        gretchin.is_character = false;
        ork_units.push_back(gretchin);

        // Kommandos
        Unit kommandos;
        kommandos.model_name = "Kommandos";
        kommandos.models_owned = 10;
        kommandos.models_used = 0;
        kommandos.points_per_unit = { 135 };
        kommandos.unit_sizes = { 10 };
        kommandos.required_warlord = false;
        kommandos.is_character = false;
        ork_units.push_back(kommandos);

        // Meganobz
        Unit meganobz;
        meganobz.model_name = "Meganobz";
        meganobz.models_owned = 2;
        meganobz.models_used = 0;
        meganobz.points_per_unit = { 65, 100, 165, 200 };
        meganobz.unit_sizes = { 2, 3, 5, 6 };
        meganobz.required_warlord = false;
        meganobz.is_character = false;
        ork_units.push_back(meganobz);

        // DeffKoptas
        Unit deffkoptas;
        deffkoptas.model_name = "Deffkoptas";
        deffkoptas.models_owned = 6;
        deffkoptas.models_used = 0;
        deffkoptas.points_per_unit = { 115, 230 };
        deffkoptas.unit_sizes = { 3, 6 };
        deffkoptas.required_warlord = false;
        deffkoptas.is_character = false;
        ork_units.push_back(deffkoptas);

        // Megatrakk Scrapjets
        Unit megatrakkscrapjets;
        megatrakkscrapjets.model_name = "Megatrakk Scrapjets";
        megatrakkscrapjets.models_owned = 1;
        megatrakkscrapjets.models_used = 0;
        megatrakkscrapjets.points_per_unit = { 90 };
        megatrakkscrapjets.unit_sizes = { 1 };
        megatrakkscrapjets.required_warlord = false;
        megatrakkscrapjets.is_character = false;
        ork_units.push_back(megatrakkscrapjets);

        // Nob on Smasha Squig
        Unit nobonsmashasquig;
        nobonsmashasquig.model_name = "Nob on Smasha Squig";
        nobonsmashasquig.models_owned = 1;
        nobonsmashasquig.models_used = 0;
        nobonsmashasquig.points_per_unit = { 75 };
        nobonsmashasquig.unit_sizes = { 1 };
        nobonsmashasquig.required_warlord = false;
        nobonsmashasquig.is_character = false;
        ork_units.push_back(nobonsmashasquig);

        // Rukkatrukk Squigbuggies
        Unit rukkatrukksquigbuggies;
        rukkatrukksquigbuggies.model_name = "Rukkatrukk Squigbuggies";
        rukkatrukksquigbuggies.models_owned = 1;
        rukkatrukksquigbuggies.models_used = 0;
        rukkatrukksquigbuggies.points_per_unit = { 110 };
        rukkatrukksquigbuggies.unit_sizes = { 1 };
        rukkatrukksquigbuggies.required_warlord = false;
        rukkatrukksquigbuggies.is_character = false;
        ork_units.push_back(rukkatrukksquigbuggies);

        // Squighog Boyz
        Unit squighogboyz;
        squighogboyz.model_name = "Squighog Boys";
        squighogboyz.models_owned = 3;
        squighogboyz.models_used = 0;
        squighogboyz.points_per_unit = { 110, 220 };
        squighogboyz.unit_sizes = { 3, 6};
        squighogboyz.required_warlord = false;
        squighogboyz.is_character = false;
        ork_units.push_back(squighogboyz);

        // Warbikers
        Unit warbikers;
        warbikers.model_name = "Warbikers";
        warbikers.models_owned = 3;
        warbikers.models_used = 0;
        warbikers.points_per_unit = { 75, 150 };
        warbikers.unit_sizes = { 3, 6};
        warbikers.required_warlord = false;
        warbikers.is_character = false;
        ork_units.push_back(warbikers);

        // Battlewagon
        Unit battlewagon;
        battlewagon.model_name = "Battlewagon";
        battlewagon.models_owned = 1;
        battlewagon.models_used = 0;
        battlewagon.points_per_unit = { 185 };
        battlewagon.unit_sizes = { 1 };
        battlewagon.required_warlord = false;
        battlewagon.is_character = false;
        ork_units.push_back(battlewagon);

        // Deff Dreads
        Unit deffdreads;
        deffdreads.model_name = "Deff Dreads";
        deffdreads.models_owned = 1;
        deffdreads.models_used = 0;
        deffdreads.points_per_unit = { 150 };
        deffdreads.unit_sizes = { 1 };
        deffdreads.required_warlord = false;
        deffdreads.is_character = false;
        ork_units.push_back(deffdreads);

        // Kill Rig
        Unit killrig;
        killrig.model_name = "Kill Rig";
        killrig.models_owned = 1;
        killrig.models_used = 0;
        killrig.points_per_unit = { 220 };
        killrig.unit_sizes = { 1 };
        killrig.required_warlord = false;
        killrig.is_character = false;
        ork_units.push_back(killrig);

        // Mek Gunz
        Unit mekgunz;
        mekgunz.model_name = "Mek Gunz";
        mekgunz.models_owned = 1;
        mekgunz.models_used = 0;
        mekgunz.points_per_unit = { 45, 90, 135 };
        mekgunz.unit_sizes = { 1, 2, 3 };
        mekgunz.required_warlord = false;
        mekgunz.is_character = false;
        ork_units.push_back(mekgunz);

        // Dakkajet
        Unit dakkajet;
        dakkajet.model_name = "Dakkajet";
        dakkajet.models_owned = 1;
        dakkajet.models_used = 0;
        dakkajet.points_per_unit = { 135 };
        dakkajet.unit_sizes = { 1 };
        dakkajet.required_warlord = false;
        dakkajet.is_character = false;
        ork_units.push_back(dakkajet);

        // Trukk
        //models_owned.insert(std::make_pair("Trukk", 1));
        //models_used.insert(std::make_pair("Trukk", 0));

        // Gorkanaut
        //models_owned.insert(std::make_pair("Gorkanaut", 1));
        //models_used.insert(std::make_pair("Gorkanaut", 0));

        // --------------------------
        //      ORK ENHANCEMENTS
        // --------------------------

        // Follow Me Ladz
        Enhancement followmeladz;
        followmeladz.enhancement_name = "Follow Me Ladz";
        followmeladz.trait_taken = false;
        followmeladz.points_cost = 25;
        ork_enhancements.push_back(followmeladz);

        // Headwoppa's Killchoppa
        Enhancement headwoppaskillchoppa;
        headwoppaskillchoppa.enhancement_name = "Headwoppa's Killchoppa";
        headwoppaskillchoppa.trait_taken = false;
        headwoppaskillchoppa.points_cost = 20;
        ork_enhancements.push_back(headwoppaskillchoppa);

        // Kunnin' But Brutal
        Enhancement kunninbutbrutal;
        kunninbutbrutal.enhancement_name = "Kunnin' But Brutal";
        kunninbutbrutal.trait_taken = false;
        kunninbutbrutal.points_cost = 15;
        ork_enhancements.push_back(kunninbutbrutal);

        // Supa-Cybork Body
        Enhancement supacyborkbody;
        supacyborkbody.enhancement_name = "Supa-Cybork Body";
        supacyborkbody.trait_taken = false;
        supacyborkbody.points_cost = 15;
        ork_enhancements.push_back(supacyborkbody);

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
    std::vector<int> lookupPointsPerUnit(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.points_per_unit; }
        return 0;
    }
    std::vector<int> lookupUnitSize(std::string key)
    {
        for (auto const& p : ork_units) { if (p.model_name == key) return p.unit_size; }
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

    // List functions
    SelectionList listModelsUnderCost(int cost)
    {
        SelectionList result = {};
        for (auto const& p : ork_units) {
            for (int i = 0; i < static_cast<int>(p.points_per_unit.size); i++) {
                if (cost >= p.points_per_unit(i)) result.push_back({ p.model_name, i });
            }
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
