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
struct Enhancement;

// Typedefs
typedef std::pair<std::string, int> Selection; // Types used for unit selecting
typedef std::vector<Selection> SelectionList;
typedef std::string EnhancementSelection;
typedef std::vector<EnhancementSelection> EnhancementSelectionList;

typedef std::vector<Unit> UnitList; // Types used for storing data
typedef std::vector<Enhancement> EnhancementList;
typedef std::pair<std::string, int> RosterSlot;
typedef std::vector<RosterSlot> Roster;

// Unit data structure
struct Unit {
    std::string model_name = {};
    int models_owned = 0;
    int models_used = 0;
    std::vector<int> points_per_unit = { 0 };
    std::vector<int> unit_sizes = { 0 };
    bool required_warlord = false;
    bool is_character = false;
    bool is_epic_hero = false;
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
    else { return (int)(rand() % count); }
    return 0;
}

class Faction {
public:

    // Common Variables
    std::string faction;
    std::vector<std::string> subfactions;
    int total_subfactions;

    EnhancementList faction_enhancements = {};
    UnitList faction_units = {};

    // Lookup functions
    int lookupModelsOwned(std::string key)
    {
        for (auto const& p : faction_units) { if (p.model_name == key) return p.models_owned; }
        return 0;
    }
    int lookupModelsUsed(std::string key)
    {
        for (auto const& p : faction_units) { if (p.model_name == key) return p.models_used; }
        return 0;
    }
    int lookupModelsAvailable(std::string key)
    {
        return (lookupModelsOwned(key) - lookupModelsUsed(key));
    }
    int lookupPointsPerUnit(std::string key, int index)
    {
        for (auto const& p : faction_units) { if (p.model_name == key) return p.points_per_unit[index]; }
        return 0;
    }
    int lookupUnitSize(std::string key, int index)
    {
        for (auto const& p : faction_units) { if (p.model_name == key) return p.unit_sizes[index]; }
        return 0;
    }
    bool lookupIsCharacter(std::string key) {
        for (auto const& p : faction_units) { if (p.model_name == key) return p.is_character; }
        return false;
    }
    bool lookupIsEpicHero(std::string key) {
        for (auto const& p : faction_units) { if (p.model_name == key) return p.is_epic_hero; }
        return false;
    }
    int lookupPointsPerEnhancement(std::string key)
    {
        for (auto const& p : faction_enhancements) { if (p.enhancement_name == key) return p.points_cost; }
        return 0;
    }

    // Setter functions
    void setModelsUsed(std::string key, int val)
    {
        for (auto p = faction_units.begin(); p != faction_units.end(); p++) {
            if ((*p).model_name == key) {
                (*p).models_used = val;
                return;
            }
        }
        return;
    }
    void setEnhancementUsed(std::string key) {
        for (auto p = faction_enhancements.begin(); p != faction_enhancements.end(); p++) {
            if ((*p).enhancement_name == key) {
                (*p).trait_taken = true;
                return;
            }
        }
        return;
    }

    // List functions
    SelectionList listAvailableUnitsUnderCost(int cost)
    {
        SelectionList result = {};
        for (auto const& p : faction_units) {
            for (int i = 0; i < static_cast<int>(p.points_per_unit.size()); i++) {
                if (cost >= p.points_per_unit[i] && lookupModelsAvailable(p.model_name) >= p.unit_sizes[i]) result.push_back({ p.model_name, i });
            }
        }
        return result;
    }
    SelectionList listAvailableCharactersUnderCost(int cost)
    {
        SelectionList result = {};
        for (auto const& p : faction_units) {
            if (p.is_character) {
                for (int i = 0; i < static_cast<int>(p.points_per_unit.size()); i++) {
                    if (cost >= p.points_per_unit[i] && lookupModelsAvailable(p.model_name) >= p.unit_sizes[i]) result.push_back({ p.model_name, i });
                }
            }
        }
        return result;
    }
    EnhancementSelectionList listAvailableEnhancementsUnderCost(int cost)
    {
        EnhancementSelectionList result = {};
        for (auto const& p : faction_enhancements) {
            if (!p.trait_taken) {
                if (cost >= p.points_cost) result.push_back(p.enhancement_name);
            }
        }
        return result;
    }

};

class Orks : public Faction
{
public:

    Orks()
    {
        // Declare variables
        faction = "Orks";
        subfactions = { "Waaaagh Tribe" };
        total_subfactions = subfactions.size();

        // Beastboss
        Unit beastboss;
        beastboss.model_name = "Beastboss";
        beastboss.models_owned = 1;
        beastboss.models_used = 0;
        beastboss.points_per_unit = { 80 };
        beastboss.unit_sizes = { 1 };
        beastboss.required_warlord = false;
        beastboss.is_character = true;
        beastboss.is_epic_hero = false;
        faction_units.push_back(beastboss);

        // Big Mek in Mega Armor
        Unit bigmekinmegaarmor;
        bigmekinmegaarmor.model_name = "Big Mek in Mega Armor";
        bigmekinmegaarmor.models_owned = 1;
        bigmekinmegaarmor.models_used = 0;
        bigmekinmegaarmor.points_per_unit = { 100 };
        bigmekinmegaarmor.unit_sizes = { 1 };
        bigmekinmegaarmor.required_warlord = false;
        bigmekinmegaarmor.is_character = true;
        bigmekinmegaarmor.is_epic_hero = false;
        faction_units.push_back(bigmekinmegaarmor);

        // Deffkilla Wartrike
        Unit deffkillawartrike;
        deffkillawartrike.model_name = "Deffkilla Wartrike";
        deffkillawartrike.models_owned = 1;
        deffkillawartrike.models_used = 0;
        deffkillawartrike.points_per_unit = { 90 };
        deffkillawartrike.unit_sizes = { 1 };
        deffkillawartrike.required_warlord = false;
        deffkillawartrike.is_character = false;
        deffkillawartrike.is_epic_hero = false;
        faction_units.push_back(deffkillawartrike);

        // Ghazghkull Thraka
        Unit ghazghkullthraka;
        ghazghkullthraka.model_name = "Ghazghkull Thraka and Makari";
        ghazghkullthraka.models_owned = 1;
        ghazghkullthraka.models_used = 0;
        ghazghkullthraka.points_per_unit = { 235 };
        ghazghkullthraka.unit_sizes = { 1 };
        ghazghkullthraka.required_warlord = false;
        ghazghkullthraka.is_character = false;
        ghazghkullthraka.is_epic_hero = true;
        faction_units.push_back(ghazghkullthraka);

        // Painboss
        Unit painboss;
        painboss.model_name = "Painboss";
        painboss.models_owned = 1;
        painboss.models_used = 0;
        painboss.points_per_unit = { 70 };
        painboss.unit_sizes = { 1 };
        painboss.required_warlord = false;
        painboss.is_character = true;
        painboss.is_epic_hero = false;
        faction_units.push_back(painboss);

        // Warboss in Mega Armor
        Unit warbossinmegaarmor;
        warbossinmegaarmor.model_name = "Warboss in Mega Armor";
        warbossinmegaarmor.models_owned = 2;
        warbossinmegaarmor.models_used = 0;
        warbossinmegaarmor.points_per_unit = { 95 };
        warbossinmegaarmor.unit_sizes = { 1 };
        warbossinmegaarmor.required_warlord = false;
        warbossinmegaarmor.is_character = true;
        warbossinmegaarmor.is_epic_hero = false;
        faction_units.push_back(warbossinmegaarmor);

        // Weirdboy
        Unit weirdboy;
        weirdboy.model_name = "Weirdboy";
        weirdboy.models_owned = 1;
        weirdboy.models_used = 0;
        weirdboy.points_per_unit = { 55 };
        weirdboy.unit_sizes = { 1 };
        weirdboy.required_warlord = false;
        weirdboy.is_character = true;
        weirdboy.is_epic_hero = false;
        faction_units.push_back(weirdboy);

        // Zodgrod Wortsnagga
        Unit zodgrodwortsnagga;
        zodgrodwortsnagga.model_name = "Zodgrod Wortsnagga";
        zodgrodwortsnagga.models_owned = 1;
        zodgrodwortsnagga.models_used = 0;
        zodgrodwortsnagga.points_per_unit = { 80 };
        zodgrodwortsnagga.unit_sizes = { 1 };
        zodgrodwortsnagga.required_warlord = false;
        zodgrodwortsnagga.is_character = true;
        zodgrodwortsnagga.is_epic_hero = true;
        faction_units.push_back(zodgrodwortsnagga);

        // Beast Snagga Boyz
        Unit beastsnaggaboyz;
        beastsnaggaboyz.model_name = "Beast Snagga Boyz";
        beastsnaggaboyz.models_owned = 10;
        beastsnaggaboyz.models_used = 0;
        beastsnaggaboyz.points_per_unit = { 105, 210 };
        beastsnaggaboyz.unit_sizes = { 10, 20 };
        beastsnaggaboyz.required_warlord = false;
        beastsnaggaboyz.is_character = false;
        beastsnaggaboyz.is_epic_hero = false;
        faction_units.push_back(beastsnaggaboyz);

        // Boyz
        Unit boyz;
        boyz.model_name = "Boyz";
        boyz.models_owned = 40;
        boyz.models_used = 0;
        boyz.points_per_unit = { 85, 170 };
        boyz.unit_sizes = { 10, 20 };
        boyz.required_warlord = false;
        boyz.is_character = false;
        boyz.is_epic_hero = false;
        faction_units.push_back(boyz);

        // Gretchin
        Unit gretchin;
        gretchin.model_name = "Gretchin";
        gretchin.models_owned = 20;
        gretchin.models_used = 0;
        gretchin.points_per_unit = { 45, 90 };
        gretchin.unit_sizes = { 10, 20 };
        gretchin.required_warlord = false;
        gretchin.is_character = false;
        gretchin.is_epic_hero = false;
        faction_units.push_back(gretchin);

        // Kommandos
        Unit kommandos;
        kommandos.model_name = "Kommandos";
        kommandos.models_owned = 10;
        kommandos.models_used = 0;
        kommandos.points_per_unit = { 135 };
        kommandos.unit_sizes = { 10 };
        kommandos.required_warlord = false;
        kommandos.is_character = false;
        kommandos.is_epic_hero = false;
        faction_units.push_back(kommandos);

        // Meganobz
        Unit meganobz;
        meganobz.model_name = "Meganobz";
        meganobz.models_owned = 2;
        meganobz.models_used = 0;
        meganobz.points_per_unit = { 65, 100, 165, 200 };
        meganobz.unit_sizes = { 2, 3, 5, 6 };
        meganobz.required_warlord = false;
        meganobz.is_character = false;
        meganobz.is_epic_hero = false;
        faction_units.push_back(meganobz);

        // DeffKoptas
        Unit deffkoptas;
        deffkoptas.model_name = "Deffkoptas";
        deffkoptas.models_owned = 6;
        deffkoptas.models_used = 0;
        deffkoptas.points_per_unit = { 115, 230 };
        deffkoptas.unit_sizes = { 3, 6 };
        deffkoptas.required_warlord = false;
        deffkoptas.is_character = false;
        deffkoptas.is_epic_hero = false;
        faction_units.push_back(deffkoptas);

        // Megatrakk Scrapjets
        Unit megatrakkscrapjets;
        megatrakkscrapjets.model_name = "Megatrakk Scrapjets";
        megatrakkscrapjets.models_owned = 1;
        megatrakkscrapjets.models_used = 0;
        megatrakkscrapjets.points_per_unit = { 90 };
        megatrakkscrapjets.unit_sizes = { 1 };
        megatrakkscrapjets.required_warlord = false;
        megatrakkscrapjets.is_character = false;
        megatrakkscrapjets.is_epic_hero = false;
        faction_units.push_back(megatrakkscrapjets);

        // Nob on Smasha Squig
        Unit nobonsmashasquig;
        nobonsmashasquig.model_name = "Nob on Smasha Squig";
        nobonsmashasquig.models_owned = 1;
        nobonsmashasquig.models_used = 0;
        nobonsmashasquig.points_per_unit = { 75 };
        nobonsmashasquig.unit_sizes = { 1 };
        nobonsmashasquig.required_warlord = false;
        nobonsmashasquig.is_character = true;
        nobonsmashasquig.is_epic_hero = false;
        faction_units.push_back(nobonsmashasquig);

        // Rukkatrukk Squigbuggies
        Unit rukkatrukksquigbuggies;
        rukkatrukksquigbuggies.model_name = "Rukkatrukk Squigbuggies";
        rukkatrukksquigbuggies.models_owned = 1;
        rukkatrukksquigbuggies.models_used = 0;
        rukkatrukksquigbuggies.points_per_unit = { 110 };
        rukkatrukksquigbuggies.unit_sizes = { 1 };
        rukkatrukksquigbuggies.required_warlord = false;
        rukkatrukksquigbuggies.is_character = false;
        rukkatrukksquigbuggies.is_epic_hero = false;
        faction_units.push_back(rukkatrukksquigbuggies);

        // Squighog Boyz
        Unit squighogboyz;
        squighogboyz.model_name = "Squighog Boys";
        squighogboyz.models_owned = 3;
        squighogboyz.models_used = 0;
        squighogboyz.points_per_unit = { 110, 220 };
        squighogboyz.unit_sizes = { 3, 6 };
        squighogboyz.required_warlord = false;
        squighogboyz.is_character = false;
        squighogboyz.is_epic_hero = false;
        faction_units.push_back(squighogboyz);

        // Warbikers
        Unit warbikers;
        warbikers.model_name = "Warbikers";
        warbikers.models_owned = 3;
        warbikers.models_used = 0;
        warbikers.points_per_unit = { 75, 150 };
        warbikers.unit_sizes = { 3, 6 };
        warbikers.required_warlord = false;
        warbikers.is_character = false;
        warbikers.is_epic_hero = false;
        faction_units.push_back(warbikers);

        // Battlewagon
        Unit battlewagon;
        battlewagon.model_name = "Battlewagon";
        battlewagon.models_owned = 1;
        battlewagon.models_used = 0;
        battlewagon.points_per_unit = { 185 };
        battlewagon.unit_sizes = { 1 };
        battlewagon.required_warlord = false;
        battlewagon.is_character = false;
        battlewagon.is_epic_hero = false;
        faction_units.push_back(battlewagon);

        // Deff Dreads
        Unit deffdreads;
        deffdreads.model_name = "Deff Dreads";
        deffdreads.models_owned = 1;
        deffdreads.models_used = 0;
        deffdreads.points_per_unit = { 150 };
        deffdreads.unit_sizes = { 1 };
        deffdreads.required_warlord = false;
        deffdreads.is_character = false;
        deffdreads.is_epic_hero = false;
        faction_units.push_back(deffdreads);

        // Kill Rig
        Unit killrig;
        killrig.model_name = "Kill Rig";
        killrig.models_owned = 1;
        killrig.models_used = 0;
        killrig.points_per_unit = { 220 };
        killrig.unit_sizes = { 1 };
        killrig.required_warlord = false;
        killrig.is_character = false;
        killrig.is_epic_hero = false;
        faction_units.push_back(killrig);

        // Mek Gunz
        Unit mekgunz;
        mekgunz.model_name = "Mek Gunz";
        mekgunz.models_owned = 1;
        mekgunz.models_used = 0;
        mekgunz.points_per_unit = { 45, 90, 135 };
        mekgunz.unit_sizes = { 1, 2, 3 };
        mekgunz.required_warlord = false;
        mekgunz.is_character = false;
        mekgunz.is_epic_hero = false;
        faction_units.push_back(mekgunz);

        // Dakkajet
        Unit dakkajet;
        dakkajet.model_name = "Dakkajet";
        dakkajet.models_owned = 1;
        dakkajet.models_used = 0;
        dakkajet.points_per_unit = { 135 };
        dakkajet.unit_sizes = { 1 };
        dakkajet.required_warlord = false;
        dakkajet.is_character = false;
        dakkajet.is_epic_hero = false;
        faction_units.push_back(dakkajet);

        // Trukk
        Unit trukk;
        trukk.model_name = "Trukk";
        trukk.models_owned = 1;
        trukk.models_used = 0;
        trukk.points_per_unit = { 50 };
        trukk.unit_sizes = { 1 };
        trukk.required_warlord = false;
        trukk.is_character = false;
        trukk.is_epic_hero = false;
        faction_units.push_back(trukk);

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
        faction_enhancements.push_back(followmeladz);

        // Headwoppa's Killchoppa
        Enhancement headwoppaskillchoppa;
        headwoppaskillchoppa.enhancement_name = "Headwoppa's Killchoppa";
        headwoppaskillchoppa.trait_taken = false;
        headwoppaskillchoppa.points_cost = 20;
        faction_enhancements.push_back(headwoppaskillchoppa);

        // Kunnin' But Brutal
        Enhancement kunninbutbrutal;
        kunninbutbrutal.enhancement_name = "Kunnin' But Brutal";
        kunninbutbrutal.trait_taken = false;
        kunninbutbrutal.points_cost = 15;
        faction_enhancements.push_back(kunninbutbrutal);

        // Supa-Cybork Body
        Enhancement supacyborkbody;
        supacyborkbody.enhancement_name = "Supa-Cybork Body";
        supacyborkbody.trait_taken = false;
        supacyborkbody.points_cost = 15;
        faction_enhancements.push_back(supacyborkbody);

    }

};

class SpaceMarines : public Faction
{
public:

    SpaceMarines()
    {
        // Declare variables
        faction = "Space Marines";
        subfactions = { "Gladius Task Force" };
        total_subfactions = subfactions.size();

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // Captain in Terminator Armor
        Unit captaininterminatorarmor;
        captaininterminatorarmor.model_name = "Captain in Terminator Armor";
        captaininterminatorarmor.models_owned = 1;
        captaininterminatorarmor.models_used = 0;
        captaininterminatorarmor.points_per_unit = { 95 };
        captaininterminatorarmor.unit_sizes = { 1 };
        captaininterminatorarmor.required_warlord = false;
        captaininterminatorarmor.is_character = true;
        captaininterminatorarmor.is_epic_hero = false;
        faction_units.push_back(captaininterminatorarmor);

        // Primaris Lieutenant
        Unit primarislieutenant;
        primarislieutenant.model_name = "Primaris Lieutenant";
        primarislieutenant.models_owned = 1;
        primarislieutenant.models_used = 0;
        primarislieutenant.points_per_unit = { 75 };
        primarislieutenant.unit_sizes = { 1 };
        primarislieutenant.required_warlord = false;
        primarislieutenant.is_character = true;
        primarislieutenant.is_epic_hero = false;
        faction_units.push_back(primarislieutenant);

        // Primaris Librarian
        Unit primarislibrarian;
        primarislibrarian.model_name = "Primaris Librarian";
        primarislibrarian.models_owned = 1;
        primarislibrarian.models_used = 0;
        primarislibrarian.points_per_unit = { 70 };
        primarislibrarian.unit_sizes = { 1 };
        primarislibrarian.required_warlord = false;
        primarislibrarian.is_character = true;
        primarislibrarian.is_epic_hero = false;
        faction_units.push_back(primarislibrarian);

        // Librarian in Terminator Armor
        Unit librarianinterminatorarmor;
        librarianinterminatorarmor.model_name = "Librarian in Terminator Armor";
        librarianinterminatorarmor.models_owned = 1;
        librarianinterminatorarmor.models_used = 0;
        librarianinterminatorarmor.points_per_unit = { 90 };
        librarianinterminatorarmor.unit_sizes = { 1 };
        librarianinterminatorarmor.required_warlord = false;
        librarianinterminatorarmor.is_character = true;
        librarianinterminatorarmor.is_epic_hero = false;
        faction_units.push_back(librarianinterminatorarmor);

        // Primaris Chaplain
        Unit primarischaplain;
        primarischaplain.model_name = "Primaris Chaplain";
        primarischaplain.models_owned = 1;
        primarischaplain.models_used = 0;
        primarischaplain.points_per_unit = { 65 };
        primarischaplain.unit_sizes = { 1 };
        primarischaplain.required_warlord = false;
        primarischaplain.is_character = true;
        primarischaplain.is_epic_hero = false;
        faction_units.push_back(primarischaplain);

        // Intercessor Squad
        Unit intercessorsquad;
        intercessorsquad.model_name = "Intercessor Squad";
        intercessorsquad.models_owned = 15;
        intercessorsquad.models_used = 0;
        intercessorsquad.points_per_unit = { 95, 190 };
        intercessorsquad.unit_sizes = { 5, 10 };
        intercessorsquad.required_warlord = false;
        intercessorsquad.is_character = false;
        intercessorsquad.is_epic_hero = false;
        faction_units.push_back(intercessorsquad);

        // Assault Intercessor Squad
        Unit assaultintercessorsquad;
        assaultintercessorsquad.model_name = "Assault Intercessor Squad";
        assaultintercessorsquad.models_owned = 5;
        assaultintercessorsquad.models_used = 0;
        assaultintercessorsquad.points_per_unit = { 90, 180 };
        assaultintercessorsquad.unit_sizes = { 5, 10 };
        assaultintercessorsquad.required_warlord = false;
        assaultintercessorsquad.is_character = false;
        assaultintercessorsquad.is_epic_hero = false;
        faction_units.push_back(assaultintercessorsquad);

        // Lieutenant with Combi-Weapon
        Unit lieutenantwithcombiweapon;
        lieutenantwithcombiweapon.model_name = "Lieutenant with Combi-Weapon";
        lieutenantwithcombiweapon.models_owned = 1;
        lieutenantwithcombiweapon.models_used = 0;
        lieutenantwithcombiweapon.points_per_unit = { 80 };
        lieutenantwithcombiweapon.unit_sizes = { 1 };
        lieutenantwithcombiweapon.required_warlord = false;
        lieutenantwithcombiweapon.is_character = true;
        lieutenantwithcombiweapon.is_epic_hero = false;
        faction_units.push_back(lieutenantwithcombiweapon);

        // Incursor Squad
        Unit incursorsquad;
        incursorsquad.model_name = "Incursor Squad";
        incursorsquad.models_owned = 5;
        incursorsquad.models_used = 0;
        incursorsquad.points_per_unit = { 90, 180 };
        incursorsquad.unit_sizes = { 5, 10 };
        incursorsquad.required_warlord = false;
        incursorsquad.is_character = false;
        incursorsquad.is_epic_hero = false;
        faction_units.push_back(incursorsquad);

        // Primaris Apothecary
        Unit primarisapothecary;
        primarisapothecary.model_name = "Primaris Apothecary";
        primarisapothecary.models_owned = 1;
        primarisapothecary.models_used = 0;
        primarisapothecary.points_per_unit = { 55 };
        primarisapothecary.unit_sizes = { 1 };
        primarisapothecary.required_warlord = false;
        primarisapothecary.is_character = true;
        primarisapothecary.is_epic_hero = false;
        faction_units.push_back(primarisapothecary);

        // Apothecary Biologis
        Unit apothecarybiologis;
        apothecarybiologis.model_name = "Apothecary Biologis";
        apothecarybiologis.models_owned = 1;
        apothecarybiologis.models_used = 0;
        apothecarybiologis.points_per_unit = { 55 };
        apothecarybiologis.unit_sizes = { 1 };
        apothecarybiologis.required_warlord = false;
        apothecarybiologis.is_character = true;
        apothecarybiologis.is_epic_hero = false;
        faction_units.push_back(apothecarybiologis);

        // Sternguard Veteran Squad
        Unit sternguardveteransquad;
        sternguardveteransquad.model_name = "Sternguard Veteran Squad";
        sternguardveteransquad.models_owned = 5;
        sternguardveteransquad.models_used = 0;
        sternguardveteransquad.points_per_unit = { 105, 210 };
        sternguardveteransquad.unit_sizes = { 5, 10 };
        sternguardveteransquad.required_warlord = false;
        sternguardveteransquad.is_character = false;
        sternguardveteransquad.is_epic_hero = false;
        faction_units.push_back(sternguardveteransquad);

        // Aggressor Squad
        Unit aggressorsquad;
        aggressorsquad.model_name = "Aggressor Squad";
        aggressorsquad.models_owned = 6;
        aggressorsquad.models_used = 0;
        aggressorsquad.points_per_unit = { 110, 220 };
        aggressorsquad.unit_sizes = { 3, 6 };
        aggressorsquad.required_warlord = false;
        aggressorsquad.is_character = false;
        aggressorsquad.is_epic_hero = false;
        faction_units.push_back(aggressorsquad);

        // Terminator Squad
        Unit terminatorsquad;
        terminatorsquad.model_name = "Terminator Squad";
        terminatorsquad.models_owned = 5;
        terminatorsquad.models_used = 0;
        terminatorsquad.points_per_unit = { 205, 410 };
        terminatorsquad.unit_sizes = { 5, 10 };
        terminatorsquad.required_warlord = false;
        terminatorsquad.is_character = false;
        terminatorsquad.is_epic_hero = false;
        faction_units.push_back(terminatorsquad);

        // Redemptor Dreadnought
        Unit redemptordreadnought;
        redemptordreadnought.model_name = "Redemptor Dreadnought";
        redemptordreadnought.models_owned = 1;
        redemptordreadnought.models_used = 0;
        redemptordreadnought.points_per_unit = { 225 };
        redemptordreadnought.unit_sizes = { 1 };
        redemptordreadnought.required_warlord = false;
        redemptordreadnought.is_character = false;
        redemptordreadnought.is_epic_hero = false;
        faction_units.push_back(redemptordreadnought);

        // Ballistus Dreadnought
        Unit ballistusdreadnought;
        ballistusdreadnought.model_name = "Ballistus Dreadnought";
        ballistusdreadnought.models_owned = 1;
        ballistusdreadnought.models_used = 0;
        ballistusdreadnought.points_per_unit = { 170 };
        ballistusdreadnought.unit_sizes = { 1 };
        ballistusdreadnought.required_warlord = false;
        ballistusdreadnought.is_character = false;
        ballistusdreadnought.is_epic_hero = false;
        faction_units.push_back(ballistusdreadnought);

        // Outrider Squad
        Unit outridersquad;
        outridersquad.model_name = "Outrider Squad";
        outridersquad.models_owned = 3;
        outridersquad.models_used = 0;
        outridersquad.points_per_unit = { 115, 230 };
        outridersquad.unit_sizes = { 3, 6 };
        outridersquad.required_warlord = false;
        outridersquad.is_character = false;
        outridersquad.is_epic_hero = false;
        faction_units.push_back(outridersquad);

        // Inceptor Squad
        Unit inceptorsquad;
        inceptorsquad.model_name = "Inceptor Squad";
        inceptorsquad.models_owned = 3;
        inceptorsquad.models_used = 0;
        inceptorsquad.points_per_unit = { 115, 230 };
        inceptorsquad.unit_sizes = { 3, 6 };
        inceptorsquad.required_warlord = false;
        inceptorsquad.is_character = false;
        inceptorsquad.is_epic_hero = false;
        faction_units.push_back(inceptorsquad);

        // Eliminator Squad
        Unit eliminatorsquad;
        eliminatorsquad.model_name = "Eliminator Squad";
        eliminatorsquad.models_owned = 3;
        eliminatorsquad.models_used = 0;
        eliminatorsquad.points_per_unit = { 95 };
        eliminatorsquad.unit_sizes = { 3 };
        eliminatorsquad.required_warlord = false;
        eliminatorsquad.is_character = false;
        eliminatorsquad.is_epic_hero = false;
        faction_units.push_back(eliminatorsquad);

        // Repulsor
        Unit repulsor;
        repulsor.model_name = "Repulsor";
        repulsor.models_owned = 1;
        repulsor.models_used = 0;
        repulsor.points_per_unit = { 195 };
        repulsor.unit_sizes = { 1 };
        repulsor.required_warlord = false;
        repulsor.is_character = false;
        repulsor.is_epic_hero = false;
        faction_units.push_back(repulsor);

        // Impulsor
        Unit impulsor;
        impulsor.model_name = "Impulsor";
        impulsor.models_owned = 1;
        impulsor.models_used = 0;
        impulsor.points_per_unit = { 95 };
        impulsor.unit_sizes = { 1 };
        impulsor.required_warlord = false;
        impulsor.is_character = false;
        impulsor.is_epic_hero = false;
        faction_units.push_back(impulsor);

        // --------------------------
        //      Space Marines ENHANCEMENTS
        // --------------------------

        // Artificer Armor
        Enhancement artificerarmor;
        artificerarmor.enhancement_name = "Artificer Armor";
        artificerarmor.trait_taken = false;
        artificerarmor.points_cost = 10;
        faction_enhancements.push_back(artificerarmor);

        // The Honour Vehement
        Enhancement thehonourvehement;
        thehonourvehement.enhancement_name = "The Honour Vehement";
        thehonourvehement.trait_taken = false;
        thehonourvehement.points_cost = 15;
        faction_enhancements.push_back(thehonourvehement);

        // Adept of the Codex
        Enhancement adeptofthecodex;
        adeptofthecodex.enhancement_name = "Adept of the Codex";
        adeptofthecodex.trait_taken = false;
        adeptofthecodex.points_cost = 20;
        faction_enhancements.push_back(adeptofthecodex);

        // Bolter Discipline
        Enhancement bolterdiscipline;
        bolterdiscipline.enhancement_name = "Bolter Discipline";
        bolterdiscipline.trait_taken = false;
        bolterdiscipline.points_cost = 25;
        faction_enhancements.push_back(bolterdiscipline);

    }

};

class AdeptaSororitas : public Faction
{
public:

    AdeptaSororitas()
    {
        // Declare variables
        faction = "Adepta Sororitas";
        subfactions = { "Hallowed Martyrs" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Adepta Sororitas UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Adepta Sororitas ENHANCEMENTS
        // -----------------------------------------

        // Saintly Example
        Enhancement saintlyexample;
        saintlyexample.enhancement_name = "Saintly Example";
        saintlyexample.trait_taken = false;
        saintlyexample.points_cost = 15;
        faction_enhancements.push_back(saintlyexample);

        // Blade of Saint Ellynor
        Enhancement bladeofsaintellynor;
        bladeofsaintellynor.enhancement_name = "Blade of Saint Ellynor";
        bladeofsaintellynor.trait_taken = false;
        bladeofsaintellynor.points_cost = 25;
        faction_enhancements.push_back(bladeofsaintellynor);

        // Litanies of Faith
        Enhancement litaniesoffaith;
        litaniesoffaith.enhancement_name = "Litanies of Faith";
        litaniesoffaith.trait_taken = false;
        litaniesoffaith.points_cost = 20;
        faction_enhancements.push_back(litaniesoffaith);

        // Mantle of Ophelia
        Enhancement mantleofophelia;
        mantleofophelia.enhancement_name = "Mantle of Ophelia";
        mantleofophelia.trait_taken = false;
        mantleofophelia.points_cost = 10;
        faction_enhancements.push_back(mantleofophelia);

    }

};

class AdeptusMechanicus : public Faction
{
public:

    AdeptusMechanicus()
    {
        // Declare variables
        faction = "Adeptus Mechanicus";
        subfactions = { "Rad-cohort" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Adeptus Mechanicus UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Adeptus Mechanicus ENHANCEMENTS
        // -----------------------------------------

        // Archived Purge Protocols
        Enhancement archivedpurgeprotocols;
        archivedpurgeprotocols.enhancement_name = "Archived Purge Protocols";
        archivedpurgeprotocols.trait_taken = false;
        archivedpurgeprotocols.points_cost = 10;
        faction_enhancements.push_back(archivedpurgeprotocols);

        // Excoriating Emanation
        Enhancement excoriatingemanation;
        excoriatingemanation.enhancement_name = "Excoriating Emanation";
        excoriatingemanation.trait_taken = false;
        excoriatingemanation.points_cost = 25;
        faction_enhancements.push_back(excoriatingemanation);

        // Master Annihilator
        Enhancement masterannihilator;
        masterannihilator.enhancement_name = "Master Annihilator";
        masterannihilator.trait_taken = false;
        masterannihilator.points_cost = 35;
        faction_enhancements.push_back(masterannihilator);

        // Omni-steriliser
        Enhancement omnisteriliser;
        omnisteriliser.enhancement_name = "Omni-steriliser";
        omnisteriliser.trait_taken = false;
        omnisteriliser.points_cost = 20;
        faction_enhancements.push_back(omnisteriliser);

    }

};

class ChaosDemons : public Faction
{
public:

    ChaosDemons()
    {
        // Declare variables
        faction = "Chaos Demons";
        subfactions = { "Daemonic Invasion" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Chaos Demons UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Chaos Demons ENHANCEMENTS
        // -----------------------------------------

        // A'rgath, The King of Blades
        Enhancement argaththekingofblades;
        argaththekingofblades.enhancement_name = "A'rgath, The King of Blades";
        argaththekingofblades.trait_taken = false;
        argaththekingofblades.points_cost = 20;
        faction_enhancements.push_back(argaththekingofblades);

        // The Everstave
        Enhancement theeverstave;
        theeverstave.enhancement_name = "The Everstave";
        theeverstave.trait_taken = false;
        theeverstave.points_cost = 15;
        faction_enhancements.push_back(theeverstave);

        // The Endless Gift
        Enhancement theendlessgift;
        theendlessgift.enhancement_name = "The Endless Gift";
        theendlessgift.trait_taken = false;
        theendlessgift.points_cost = 30;
        faction_enhancements.push_back(theendlessgift);

        // Soulstealer
        Enhancement soulstealer;
        soulstealer.enhancement_name = "Soulstealer";
        soulstealer.trait_taken = false;
        soulstealer.points_cost = 25;
        faction_enhancements.push_back(soulstealer);

    }

};

class ChaosSpaceMarines : public Faction
{
public:

    ChaosSpaceMarines()
    {
        // Declare variables
        faction = "Chaos Space Marines";
        subfactions = { "Slaves to Darkness" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Chaos Space Marines UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Chaos Space Marines ENHANCEMENTS
        // -----------------------------------------

        // Talisman of Burning Blood
        Enhancement talismanofburningblood;
        talismanofburningblood.enhancement_name = "Talisman of Burning Blood";
        talismanofburningblood.trait_taken = false;
        talismanofburningblood.points_cost = 20;
        faction_enhancements.push_back(talismanofburningblood);

        // Eye of Tzeentch
        Enhancement eyeoftzeentch;
        eyeoftzeentch.enhancement_name = "Eye of Tzeentch";
        eyeoftzeentch.trait_taken = false;
        eyeoftzeentch.points_cost = 30;
        faction_enhancements.push_back(eyeoftzeentch);

        // Orbs of Unlife
        Enhancement orbsofunlife;
        orbsofunlife.enhancement_name = "Orbs of Unlife";
        orbsofunlife.trait_taken = false;
        orbsofunlife.points_cost = 25;
        faction_enhancements.push_back(orbsofunlife);

        // Intoxicating Elixir
        Enhancement intoxicatingelixir;
        intoxicatingelixir.enhancement_name = "Intoxicating Elixir";
        intoxicatingelixir.trait_taken = false;
        intoxicatingelixir.points_cost = 15;
        faction_enhancements.push_back(intoxicatingelixir);

        // Liber Hereticus
        Enhancement liberhereticus;
        liberhereticus.enhancement_name = "Liber Hereticus";
        liberhereticus.trait_taken = false;
        liberhereticus.points_cost = 40;
        faction_enhancements.push_back(liberhereticus);

    }

};

class DeathGuard : public Faction
{
public:

    DeathGuard()
    {
        // Declare variables
        faction = "Death Guard";
        subfactions = { "Plague Company" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Death Guard UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Death Guard ENHANCEMENTS
        // -----------------------------------------

        // Living Plague
        Enhancement livingplague;
        livingplague.enhancement_name = "Living Plague";
        livingplague.trait_taken = false;
        livingplague.points_cost = 20;
        faction_enhancements.push_back(livingplague);

        // The Droning
        Enhancement thedroning;
        thedroning.enhancement_name = "The Droning";
        thedroning.trait_taken = false;
        thedroning.points_cost = 10;
        faction_enhancements.push_back(thedroning);

        // Deadly Pathowogen
        Enhancement deadlypathowogen;
        deadlypathowogen.enhancement_name = "Deadly Pathowogen";
        deadlypathowogen.trait_taken = false;
        deadlypathowogen.points_cost = 15;
        faction_enhancements.push_back(deadlypathowogen);

        // Shamblerot
        Enhancement shamblerot;
        shamblerot.enhancement_name = "Shamblerot";
        shamblerot.trait_taken = false;
        shamblerot.points_cost = 25;
        faction_enhancements.push_back(shamblerot);

    }

};

class Drukhari : public Faction
{
public:

    Drukhari()
    {
        // Declare variables
        faction = "Drukhari";
        subfactions = { "Realspace Raiders" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Drukhari UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Drukhari ENHANCEMENTS
        // -----------------------------------------

        // Crucible of Malediction
        Enhancement crucibleofmalediction;
        crucibleofmalediction.enhancement_name = "Crucible of Malediction";
        crucibleofmalediction.trait_taken = false;
        crucibleofmalediction.points_cost = 10;
        faction_enhancements.push_back(crucibleofmalediction);

        // Labyrinthine Cunning
        Enhancement labyrinthinecunning;
        labyrinthinecunning.enhancement_name = "Labyrinthine Cunning";
        labyrinthinecunning.trait_taken = false;
        labyrinthinecunning.points_cost = 30;
        faction_enhancements.push_back(labyrinthinecunning);

        // Blood Dancer
        Enhancement blooddancer;
        blooddancer.enhancement_name = "Blood Dancer";
        blooddancer.trait_taken = false;
        blooddancer.points_cost = 20;
        faction_enhancements.push_back(blooddancer);

        // The Art of Pain
        Enhancement theartofpain;
        theartofpain.enhancement_name = "The Art of Pain";
        theartofpain.trait_taken = false;
        theartofpain.points_cost = 25;
        faction_enhancements.push_back(theartofpain);

    }

};

class GreyKnights : public Faction
{
public:

    GreyKnights()
    {
        // Declare variables
        faction = "Grey Knights";
        subfactions = { "Teleport Strike Force" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Grey Knights UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Grey Knights ENHANCEMENTS
        // -----------------------------------------

        // First to the Fray
        Enhancement firsttothefray;
        firsttothefray.enhancement_name = "First to the Fray";
        firsttothefray.trait_taken = false;
        firsttothefray.points_cost = 35;
        faction_enhancements.push_back(firsttothefray);

        // Domina Liber Daemonica
        Enhancement dominaliberdaemonica;
        dominaliberdaemonica.enhancement_name = "Domina Liber Daemonica";
        dominaliberdaemonica.trait_taken = false;
        dominaliberdaemonica.points_cost = 20;
        faction_enhancements.push_back(dominaliberdaemonica);

        // Sigil of Exigence
        Enhancement sigilofexigence;
        sigilofexigence.enhancement_name = "Sigil of Exigence";
        sigilofexigence.trait_taken = false;
        sigilofexigence.points_cost = 30;
        faction_enhancements.push_back(sigilofexigence);

        // Inescapable Wrath
        Enhancement inescapablewrath;
        inescapablewrath.enhancement_name = "Inescapable Wrath";
        inescapablewrath.trait_taken = false;
        inescapablewrath.points_cost = 15;
        faction_enhancements.push_back(inescapablewrath);

    }

};

class ImperialKnights : public Faction
{
public:

    ImperialKnights()
    {
        // Declare variables
        faction = "Imperial Knights";
        subfactions = { "Noble Lance" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Imperial Knights UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Imperial Knights ENHANCEMENTS
        // -----------------------------------------

        // Revered Knight
        Enhancement reveredknight;
        reveredknight.enhancement_name = "Revered Knight";
        reveredknight.trait_taken = false;
        reveredknight.points_cost = 20;
        faction_enhancements.push_back(reveredknight);

        // Mysterious Guardian
        Enhancement mysteriousguardian;
        mysteriousguardian.enhancement_name = "Mysterious Guardian";
        mysteriousguardian.trait_taken = false;
        mysteriousguardian.points_cost = 35;
        faction_enhancements.push_back(mysteriousguardian);

        // Mythic Hero
        Enhancement mythichero;
        mythichero.enhancement_name = "Mythic Hero";
        mythichero.trait_taken = false;
        mythichero.points_cost = 25;
        faction_enhancements.push_back(mythichero);

        // Banner of Macharius Triumphant
        Enhancement bannerofmachariustriumphant;
        bannerofmachariustriumphant.enhancement_name = "Banner of Macharius Triumphant";
        bannerofmachariustriumphant.trait_taken = false;
        bannerofmachariustriumphant.points_cost = 30;
        faction_enhancements.push_back(bannerofmachariustriumphant);

        // Unyielding Paragon
        Enhancement unyieldingparagon;
        unyieldingparagon.enhancement_name = "Unyielding Paragon";
        unyieldingparagon.trait_taken = false;
        unyieldingparagon.points_cost = 40;
        faction_enhancements.push_back(unyieldingparagon);

    }

};

class LeaguesOfVotann : public Faction
{
public:

    LeaguesOfVotann()
    {
        // Declare variables
        faction = "Leagues Of Votann";
        subfactions = { "Oathband" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Leagues Of Votann UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Leagues Of Votann ENHANCEMENTS
        // -----------------------------------------

        // Appraising Glare
        Enhancement appraisingglare;
        appraisingglare.enhancement_name = "Appraising Glare";
        appraisingglare.trait_taken = false;
        appraisingglare.points_cost = 20;
        faction_enhancements.push_back(appraisingglare);

        // A Long List
        Enhancement alonglist;
        alonglist.enhancement_name = "A Long List";
        alonglist.trait_taken = false;
        alonglist.points_cost = 15;
        faction_enhancements.push_back(alonglist);

        // Grim Demeanour
        Enhancement grimdemeanour;
        grimdemeanour.enhancement_name = "Grim Demeanour";
        grimdemeanour.trait_taken = false;
        grimdemeanour.points_cost = 20;
        faction_enhancements.push_back(grimdemeanour);

        // Wayfarer's Grace
        Enhancement wayfarersgrace;
        wayfarersgrace.enhancement_name = "Wayfarer's Grace";
        wayfarersgrace.trait_taken = false;
        wayfarersgrace.points_cost = 25;
        faction_enhancements.push_back(wayfarersgrace);

    }

};

class Necrons : public Faction
{
public:

    Necrons()
    {
        // Declare variables
        faction = "Necrons";
        subfactions = { "Awakened Dynasty" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Necrons UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Necrons ENHANCEMENTS
        // -----------------------------------------

        // Veil of Darkness
        Enhancement veilofdarkness;
        veilofdarkness.enhancement_name = "Veil of Darkness";
        veilofdarkness.trait_taken = false;
        veilofdarkness.points_cost = 20;
        faction_enhancements.push_back(veilofdarkness);

        // Hypermaterial Ablator
        Enhancement hypermaterialablator;
        hypermaterialablator.enhancement_name = "Hypermaterial Ablator";
        hypermaterialablator.trait_taken = false;
        hypermaterialablator.points_cost = 25;
        faction_enhancements.push_back(hypermaterialablator);

        // The Sovereign Coronal
        Enhancement thesovereigncoronal;
        thesovereigncoronal.enhancement_name = "The Sovereign Coronal";
        thesovereigncoronal.trait_taken = false;
        thesovereigncoronal.points_cost = 30;
        faction_enhancements.push_back(thesovereigncoronal);

        // Semiternal Weave
        Enhancement semiternalweave;
        semiternalweave.enhancement_name = "Semiternal Weave";
        semiternalweave.trait_taken = false;
        semiternalweave.points_cost = 10;
        faction_enhancements.push_back(semiternalweave);

    }

};

class ThousandSons : public Faction
{
public:

    ThousandSons()
    {
        // Declare variables
        faction = "Thousand Sons";
        subfactions = { "Cult of Magic" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Thousand Sons UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Thousand Sons ENHANCEMENTS
        // -----------------------------------------

        // Lord of Forbidden Lore
        Enhancement lordofforbiddenlore;
        lordofforbiddenlore.enhancement_name = "Lord of Forbidden Lore";
        lordofforbiddenlore.trait_taken = false;
        lordofforbiddenlore.points_cost = 25;
        faction_enhancements.push_back(lordofforbiddenlore);

        // Athenaean Scrolls
        Enhancement athenaeanscrolls;
        athenaeanscrolls.enhancement_name = "Athenaean Scrolls";
        athenaeanscrolls.trait_taken = false;
        athenaeanscrolls.points_cost = 20;
        faction_enhancements.push_back(athenaeanscrolls);

        // Umbralefic Crystal
        Enhancement umbraleficcrystal;
        umbraleficcrystal.enhancement_name = "Umbralefic Crystal";
        umbraleficcrystal.trait_taken = false;
        umbraleficcrystal.points_cost = 20;
        faction_enhancements.push_back(umbraleficcrystal);

        // Arcane Vortex
        Enhancement arcanevortex;
        arcanevortex.enhancement_name = "Arcane Vortex";
        arcanevortex.trait_taken = false;
        arcanevortex.points_cost = 15;
        faction_enhancements.push_back(arcanevortex);

    }

};

class Tyranids : public Faction
{
public:

    Tyranids()
    {
        // Declare variables
        faction = "Tyranids";
        subfactions = { "Invasion Fleet" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      Tyranids UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      Tyranids ENHANCEMENTS
        // -----------------------------------------

        // Alien Cunning
        Enhancement aliencunning;
        aliencunning.enhancement_name = "Alien Cunning";
        aliencunning.trait_taken = false;
        aliencunning.points_cost = 30;
        faction_enhancements.push_back(aliencunning);

        // Perfectly Adapted
        Enhancement perfectlyadapted;
        perfectlyadapted.enhancement_name = "Perfectly Adapted";
        perfectlyadapted.trait_taken = false;
        perfectlyadapted.points_cost = 15;
        faction_enhancements.push_back(perfectlyadapted);

        // Synaptic Linchpin
        Enhancement synapticlinchpin;
        synapticlinchpin.enhancement_name = "Synaptic Linchpin";
        synapticlinchpin.trait_taken = false;
        synapticlinchpin.points_cost = 10;
        faction_enhancements.push_back(synapticlinchpin);

        // Adaptive Biology
        Enhancement adaptivebiology;
        adaptivebiology.enhancement_name = "Adaptive Biology";
        adaptivebiology.trait_taken = false;
        adaptivebiology.points_cost = 25;
        faction_enhancements.push_back(adaptivebiology);

    }

};

class TauEmpire : public Faction
{
public:

    TauEmpire()
    {
        // Declare variables
        faction = "T'au Empire";
        subfactions = { "Kauyon" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      T'au Empire UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      T'au Empire ENHANCEMENTS
        // -----------------------------------------

        // Exemplar of the Kauyon
        Enhancement exemplarofthekauyon;
        exemplarofthekauyon.enhancement_name = "Exemplar of the Kauyon";
        exemplarofthekauyon.trait_taken = false;
        exemplarofthekauyon.points_cost = 15;
        faction_enhancements.push_back(exemplarofthekauyon);

        // Precision of the Patient Hunter
        Enhancement precisionofthepatienthunter;
        precisionofthepatienthunter.enhancement_name = "Precision of the Patient Hunter";
        precisionofthepatienthunter.trait_taken = false;
        precisionofthepatienthunter.points_cost = 20;
        faction_enhancements.push_back(precisionofthepatienthunter);

        // Puretide Engram Neurochip
        Enhancement puretideengramneurochip;
        puretideengramneurochip.enhancement_name = "Puretide Engram Neurochip";
        puretideengramneurochip.trait_taken = false;
        puretideengramneurochip.points_cost = 25;
        faction_enhancements.push_back(puretideengramneurochip);

        // Through Unity, Devestation
        Enhancement throughunitydevestation;
        throughunitydevestation.enhancement_name = "Through Unity, Devestation";
        throughunitydevestation.trait_taken = false;
        throughunitydevestation.points_cost = 20;
        faction_enhancements.push_back(throughunitydevestation);

    }

};

class WorldEaters : public Faction
{
public:

    WorldEaters()
    {
        // Declare variables
        faction = "World Eaters";
        subfactions = { "Berzerker Warband" };
        total_subfactions = subfactions.size();

        // -----------------------------------------
        //      World Eaters UNITS
        // -----------------------------------------

        // Primaris Captain
        Unit primariscaptain;
        primariscaptain.model_name = "Primaris Captain";
        primariscaptain.models_owned = 1;
        primariscaptain.models_used = 0;
        primariscaptain.points_per_unit = { 80 };
        primariscaptain.unit_sizes = { 1 };
        primariscaptain.required_warlord = false;
        primariscaptain.is_character = true;
        primariscaptain.is_epic_hero = false;
        faction_units.push_back(primariscaptain);

        // -----------------------------------------
        //      World Eaters ENHANCEMENTS
        // -----------------------------------------

        // Favoured of Khorne
        Enhancement favouredofkhorne;
        favouredofkhorne.enhancement_name = "Favoured of Khorne";
        favouredofkhorne.trait_taken = false;
        favouredofkhorne.points_cost = 30;
        faction_enhancements.push_back(favouredofkhorne);

        // Berzerker Glaive
        Enhancement berzerkerglaive;
        berzerkerglaive.enhancement_name = "Berzerker Glaive";
        berzerkerglaive.trait_taken = false;
        berzerkerglaive.points_cost = 25;
        faction_enhancements.push_back(berzerkerglaive);

        // Battle-lust
        Enhancement battlelust;
        battlelust.enhancement_name = "Battle-lust";
        battlelust.trait_taken = false;
        battlelust.points_cost = 15;
        faction_enhancements.push_back(battlelust);

        // Helm of Brazen Ire
        Enhancement helmofbrazenire;
        helmofbrazenire.enhancement_name = "Helm of Brazen Ire";
        helmofbrazenire.trait_taken = false;
        helmofbrazenire.points_cost = 25;
        faction_enhancements.push_back(helmofbrazenire);

    }

};

class Detachment
{
public:
    int points = 0;
    int points_max = 0;

    int character_count = 0;
    int epic_hero_count = 0;
    int enhancement_count = 0;

    std::string faction = "";
    std::string subfaction = "";

    Roster units = {}; // Stores the units taken

    Detachment()
    {
        points = 0;
        points_max = 0;

        faction = "";
        subfaction = "";

        units = {};
    }

    Detachment(std::string fact, std::string subfact, int points_limit, RosterSlot selected_character)
    {
        faction = fact;
        subfaction = subfact;

        points = 0;
        points_max = points_limit;

        character_count = 1;
        enhancement_count = 0;

        // Add first required unit
        units = {};
        units.push_back(selected_character);
        points += selected_character.second;

    }

    void addUnit(RosterSlot unit, bool is_character, bool is_epic_hero, bool is_enhancement)
    {
        units.push_back(unit);
        points += unit.second;
        if (is_character) character_count++;
        if (is_epic_hero) epic_hero_count++;
        if (is_enhancement) enhancement_count++;
        return;
    }

    // Lookup functions
    int lookupPointsAvailable()
    {
        return static_cast<int>(points_max - points);
    }
    int lookupEnhancementsAvailable()
    {
        // character count should always be at least 1
        return std::min(character_count-epic_hero_count, 3) - enhancement_count;
    }

    // Roster printer
    void printDetachment()
    {
        std::cout << "++ 10th Edition Detachment (" << faction << " - " << subfaction << ") [ " << points << "pts] ++" << std::endl;
        std::cout << std::endl;
        for (auto const& p : units) { std::cout << p.first << " [" << p.second << "pts] " << std::endl; }
        std::cout << std::endl;
        return;
    }
};

int main()
{

    int points_per_roster = 0;
    int roster_count = 0;

    SelectionList possible_units = {};
    EnhancementSelectionList possible_enhancements = {};
    int unit_choice = 0;
    Selection unit_selection = {};
    EnhancementSelection enhancement_selection = "";
    RosterSlot unit_to_add = {};

    Detachment roster1, roster2;
    RosterSlot character1 = {};
    RosterSlot character2 = {};

    int faction_selection;
    Faction* faction_data;

    Orks orks_data;
    SpaceMarines spacemarines_data;
    AdeptaSororitas adeptasororitas_data;
    AdeptusMechanicus adeptusmechanicus_data;
    ChaosDemons chaosdemons_data;
    ChaosSpaceMarines chaosspacemarines_data;
    DeathGuard deathguard_data;
    Drukhari drukhari_data;
    GreyKnights greyknights_data;
    ImperialKnights imperialknights_data;
    LeaguesOfVotann leaguesofvotann_data;
    Necrons necrons_data;
    ThousandSons thousandsons_data;
    Tyranids tyranids_data;
    TauEmpire tauempire_data;
    WorldEaters worldeaters_data;

    std::string faction1_name = "";
    std::string faction2_name = "";
    std::string subfaction1_name = "";
    std::string subfaction2_name = "";

    bool roster1_novalidunits = false;
    bool roster2_novalidunits = false;

    // Welcome message
    std::cout << " -------------------- Warhammer 40k Random Army Generator --------------------" << std::endl;

    // Initialize Random Number Generator
    std::srand(std::time(NULL));

    // Prompt User for points limit and number of rosters

    std::cout << "How many points per roster? ";
    std::cin >> points_per_roster;
    std::cout << std::endl;
    std::cout << "How many rosters from same collection (1 or 2)? ";
    std::cin >> roster_count;
    if (roster_count != 1) roster_count = 2;
    std::cout << std::endl;

    // Select factions and subfactions

    std::cout << "0. Follow the Will of the Emperor" << std::endl;
    std::cout << "1. Orks" << std::endl;
    std::cout << "2. Space Marines" << std::endl;
    std::cout << "3. Adepta Sororitas" << std::endl;
    std::cout << "4. Adeptus Mechanicus" << std::endl;
    std::cout << "5. Chaos Demons" << std::endl;
    std::cout << "6. Chaos Space Marines" << std::endl;
    std::cout << "7. Death Guard" << std::endl;
    std::cout << "8. Drukhari" << std::endl;
    std::cout << "9. Grey Knights" << std::endl;
    std::cout << "10. Imperial Knights" << std::endl;
    std::cout << "11. Leagues of Votann" << std::endl;
    std::cout << "12. Necrons" << std::endl;
    std::cout << "13. Thousand Sons" << std::endl;
    std::cout << "14. Tyranids" << std::endl;
    std::cout << "15. T'au Empire" << std::endl;
    std::cout << "16. World Eaters" << std::endl;
    std::cout << std::endl;
    std::cout << "Which army for rosters? ";
    std::cin >> faction_selection;
    if (faction_selection == 0) { faction_selection = randint(16) + 1; }
    switch (faction_selection) {
    case 1:
        faction_data = &orks_data;
        break;
    case 2:
        faction_data = &spacemarines_data;
        break;
    case 3:
        faction_data = &adeptasororitas_data;
        break;
    case 4:
        faction_data = &adeptusmechanicus_data;
        break;
    case 5:
        faction_data = &chaosdemons_data;
        break;
    case 6:
        faction_data = &chaosspacemarines_data;
        break;
    case 7:
        faction_data = &deathguard_data;
        break;
    case 8:
        faction_data = &drukhari_data;
        break;
    case 9:
        faction_data = &greyknights_data;
        break;
    case 10:
        faction_data = &imperialknights_data;
        break;
    case 11:
        faction_data = &leaguesofvotann_data;
        break;
    case 12:
        faction_data = &necrons_data;
        break;
    case 13:
        faction_data = &thousandsons_data;
        break;
    case 14:
        faction_data = &tyranids_data;
        break;
    case 15:
        faction_data = &tauempire_data;
        break;
    case 16:
        faction_data = &worldeaters_data;
        break;
    default:
        faction_data = &orks_data;
        break;
    }
    faction1_name = faction_data->faction;
    subfaction1_name = faction_data->subfactions[randint(faction_data->total_subfactions)];
    if (roster_count != 1) {
        faction2_name = faction_data->faction;
        subfaction2_name = faction_data->subfactions[randint(faction_data->total_subfactions)];
    }

    // Generate Required character for Roster 1 and initialize detachment
    possible_units = faction_data->listAvailableCharactersUnderCost(points_per_roster);
    unit_choice = randint(static_cast<int>(possible_units.size()));
    unit_selection = possible_units[unit_choice];
    character1 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)), faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
    roster1 = Detachment(faction1_name, subfaction1_name, points_per_roster, character1);
    if (faction_data->lookupIsEpicHero(unit_selection.first)) { roster1.epic_hero_count++; }
    faction_data->setModelsUsed(unit_selection.first, faction_data->lookupModelsUsed(unit_selection.first) + faction_data->lookupUnitSize(unit_selection.first, unit_selection.second));

    // Generate Required character for Roster 2 and initialize detachment
    if (roster_count != 1) {
        possible_units = faction_data->listAvailableCharactersUnderCost(points_per_roster);
        unit_choice = randint(static_cast<int>(possible_units.size()));
        unit_selection = possible_units[unit_choice];
        character2 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)), faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
        roster2 = Detachment(faction2_name, subfaction2_name, points_per_roster, character2);
        if (faction_data->lookupIsEpicHero(unit_selection.first)) { roster2.epic_hero_count++; }
        faction_data->setModelsUsed(unit_selection.first, faction_data->lookupModelsUsed(unit_selection.first) + faction_data->lookupUnitSize(unit_selection.first, unit_selection.second));
    }

    // Add units until point limit is reached
    roster1_novalidunits = false;
    roster2_novalidunits = false;
    while ((roster1.points < roster1.points_max) || (roster2.points < roster2.points_max))
    {
        if (!roster1_novalidunits) {
            // Generate a unit for roster 1
            possible_units = {};
            possible_units = faction_data->listAvailableUnitsUnderCost(roster1.lookupPointsAvailable());
            if (roster1.lookupEnhancementsAvailable() >= 1) {
                possible_enhancements = faction_data->listAvailableEnhancementsUnderCost(roster1.lookupPointsAvailable());
            }
            else {
                possible_enhancements = {};
            }

            if (possible_units.size() + possible_enhancements.size() == 0) {
                roster1_novalidunits = true;
            }
            else {
                unit_choice = randint(static_cast<int>(possible_units.size() + possible_enhancements.size()));
                if (unit_choice < possible_units.size()) {
                    unit_selection = possible_units[unit_choice];
                    character1 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)), faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
                    roster1.addUnit(character1, faction_data->lookupIsCharacter(unit_selection.first), faction_data->lookupIsEpicHero(unit_selection.first), false);
                    faction_data->setModelsUsed(unit_selection.first, faction_data->lookupModelsUsed(unit_selection.first) + faction_data->lookupUnitSize(unit_selection.first, unit_selection.second));
                }
                else {
                    enhancement_selection = possible_enhancements[unit_choice - possible_units.size()];
                    character1 = std::make_pair(enhancement_selection + " [Enhancement]", faction_data->lookupPointsPerEnhancement(enhancement_selection));
                    roster1.addUnit(character1, false, false, true);
                    faction_data->setEnhancementUsed(enhancement_selection);
                }
            }
        }
        if (roster_count != 1) {
            if (!roster2_novalidunits) {
                // Generate a unit for roster 2
                possible_units = {};
                possible_units = faction_data->listAvailableUnitsUnderCost(roster2.lookupPointsAvailable());
                if (roster2.lookupEnhancementsAvailable() >= 1) {
                    possible_enhancements = faction_data->listAvailableEnhancementsUnderCost(roster2.lookupPointsAvailable());
                }
                else {
                    possible_enhancements = {};
                }

                if (possible_units.size() + possible_enhancements.size() == 0) {
                    roster2_novalidunits = true;
                }
                else {
                    unit_choice = randint(static_cast<int>(possible_units.size() + possible_enhancements.size()));
                    if (unit_choice < possible_units.size()) {
                        unit_selection = possible_units[unit_choice];
                        character2 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)), faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
                        roster2.addUnit(character1, faction_data->lookupIsCharacter(unit_selection.first), faction_data->lookupIsEpicHero(unit_selection.first), false);
                        faction_data->setModelsUsed(unit_selection.first, faction_data->lookupModelsUsed(unit_selection.first) + faction_data->lookupUnitSize(unit_selection.first, unit_selection.second));
                    }
                    else {
                        enhancement_selection = possible_enhancements[unit_choice - possible_units.size()];
                        character2 = std::make_pair(enhancement_selection + " [Enhancement]", faction_data->lookupPointsPerEnhancement(enhancement_selection));
                        roster2.addUnit(character2, false, false, true);
                        faction_data->setEnhancementUsed(enhancement_selection);
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