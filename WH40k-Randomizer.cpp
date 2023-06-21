// WH40k Randomizer.cpp : Defines the entry point for the application.
//

#include "WH40k-Randomizer.h"
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
        for (auto const& p : faction_units) {if (p.model_name == key) return p.models_owned;}
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
    SelectionList listAvailableCharactersUnderCost (int cost) 
    {
        SelectionList result = {};
        for (auto const& p : faction_units) {
			if (p.is_character) {
				for (int i = 0; i < static_cast<int>(p.points_per_unit.size()); i++) {
					if (cost >= p.points_per_unit[i]  && lookupModelsAvailable(p.model_name) >= p.unit_sizes[i]) result.push_back({ p.model_name, i });
				}
			}
        }
        return result;
    }
	EnhancementSelectionList listAvailableEnhancementsUnderCost (int cost) 
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
        faction_units.push_back(rukkatrukksquigbuggies);

        // Squighog Boyz
        Unit squighogboyz;
        squighogboyz.model_name = "Squighog Boys";
        squighogboyz.models_owned = 3;
        squighogboyz.models_used = 0;
        squighogboyz.points_per_unit = { 110, 220 };
        squighogboyz.unit_sizes = { 3, 6};
        squighogboyz.required_warlord = false;
        squighogboyz.is_character = false;
        faction_units.push_back(squighogboyz);

        // Warbikers
        Unit warbikers;
        warbikers.model_name = "Warbikers";
        warbikers.models_owned = 3;
        warbikers.models_used = 0;
        warbikers.points_per_unit = { 75, 150 };
        warbikers.unit_sizes = { 3, 6};
        warbikers.required_warlord = false;
        warbikers.is_character = false;
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

class Detachment
{
public:
    int points = 0;
    int points_max = 0;
	
	int character_count = 0;
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
		points+=selected_character.second;
        
    }

    void addUnit(RosterSlot unit, bool is_character, bool is_enhancement)
    {
        units.push_back(unit);
		points+=unit.second;
		if (is_character) character_count++;
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
		return std::min(character_count,3) - enhancement_count;
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
	
	std::cout << "1. Orks" << std::endl;
	std::cout << "2. Space Marines" << std::endl;
	std::cout << std::endl;
	std::cout << "Which army for rosters? ";
	std::cin >> faction_selection;
	switch(faction_selection) {
		case 1:
			faction_data = &orks_data;
			break;
		case 2:
			faction_data = &spacemarines_data;
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
	character1 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)) , faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
	roster1 = Detachment(faction1_name, subfaction1_name, points_per_roster, character1);
	faction_data->setModelsUsed(unit_selection.first, faction_data->lookupModelsUsed(unit_selection.first) + faction_data->lookupUnitSize(unit_selection.first, unit_selection.second));
	
	// Generate Required character for Roster 2 and initialize detachment
	if (roster_count != 1) {
		possible_units = faction_data->listAvailableCharactersUnderCost(points_per_roster);
		unit_choice = randint(static_cast<int>(possible_units.size()));
		unit_selection = possible_units[unit_choice];
		character2 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)), faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
		roster2 = Detachment(faction2_name, subfaction2_name, points_per_roster, character2);
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
			} else {
				possible_enhancements = {};
			}
			
			if (possible_units.size() + possible_enhancements.size() == 0) {
				roster1_novalidunits = true;
			} else {
				unit_choice = randint(static_cast<int>(possible_units.size() + possible_enhancements.size()));
				if (unit_choice < possible_units.size()) {
					unit_selection = possible_units[unit_choice];
					character1 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)), faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
					roster1.addUnit(character1, faction_data->lookupIsCharacter(unit_selection.first), false);
					faction_data->setModelsUsed(unit_selection.first, faction_data->lookupModelsUsed(unit_selection.first) + faction_data->lookupUnitSize(unit_selection.first, unit_selection.second));
				} else {
					enhancement_selection = possible_enhancements[unit_choice - possible_units.size()];
					character1 = std::make_pair(enhancement_selection + " [Enhancement]", faction_data->lookupPointsPerEnhancement(enhancement_selection));
					roster1.addUnit(character1, false, true);
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
				} else {
					possible_enhancements = {};
				}
			
				if (possible_units.size() + possible_enhancements.size() == 0) {
					roster2_novalidunits = true;
				} else {
					unit_choice = randint(static_cast<int>(possible_units.size() + possible_enhancements.size()));
					if (unit_choice < possible_units.size()) {
						unit_selection = possible_units[unit_choice];
						character2 = std::make_pair(unit_selection.first + " x" + std::to_string(faction_data->lookupUnitSize(unit_selection.first, unit_selection.second)), faction_data->lookupPointsPerUnit(unit_selection.first, unit_selection.second));
						roster2.addUnit(character2, faction_data->lookupIsCharacter(unit_selection.first), false);
						faction_data->setModelsUsed(unit_selection.first, faction_data->lookupModelsUsed(unit_selection.first) + faction_data->lookupUnitSize(unit_selection.first, unit_selection.second));
					} else {
						enhancement_selection = possible_enhancements[unit_choice - possible_units.size()];
						character2 = std::make_pair(enhancement_selection + " [Enhancement]", faction_data->lookupPointsPerEnhancement(enhancement_selection));
						roster2.addUnit(character2, false, true);
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
