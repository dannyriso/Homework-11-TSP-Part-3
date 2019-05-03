/*
 * The implementation of the TournamentDeme class.
 */

#include "tournament_deme.hh"
#include <algorithm>

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate) :
	Deme(cities_ptr, pop_size, mut_rate) {}

TournamentDeme::~TournamentDeme() {
}

ClimbChromosome* TournamentDeme::select_parent() {
	auto P = 8;
	std::vector<ClimbChromosome*> tourney;
	// Randomly selects P parents from the population
	std::uniform_int_distribution<int> distribution(0, pop_.size() - 1);
	for(auto i = 0; i < P; ++i) {
		auto index = distribution(generator_);
		auto chromo = pop_[index];
		tourney.push_back(chromo);
	}
	auto selected = tourney[0];
	// Takes a pair of parents and discards the one with the lower fitness.
	while(tourney.size() > 1) {
		for(auto i = 0; i < P; ++i) {
			auto parent1 = tourney[i];
			auto parent2 = tourney[++i];
			if(parent1->get_fitness() > parent2->get_fitness()) {
				selected = parent1;
				tourney.erase(std::remove(tourney.begin(), tourney.end(), parent2), tourney.end());
			} else {
				selected = parent2;
				tourney.erase(std::remove(tourney.begin(), tourney.end(), parent1), tourney.end());
			}
		}
	P /= 2;
	}
	return selected;
}
