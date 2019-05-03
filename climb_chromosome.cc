/*
 * The ClimbChromosome class, which uses local hill climbing to mutate chromosomes.
 */

#include "climb_chromosome.hh"
#include <algorithm>

ClimbChromosome::ClimbChromosome(const Cities* cities_ptr) :
	Chromosome(cities_ptr) {}


ClimbChromosome* ClimbChromosome::clone() const {
	return new ClimbChromosome(*this);
}

void ClimbChromosome::mutate() {
	auto chromo_b = clone();
	auto chromo_c = clone();
	// Finds the current chromosome's fitness
	auto fit_a = get_fitness();
	// Picks a random point p in the chromosome
	std::uniform_int_distribution<int> distribution(0, order_.size() - 1);
	auto p = distribution(generator_);
	// Swaps the cities with indexes p and p - 1; if p = 0, swaps cities with indexes p and N - 1
	if(p) {
		std::swap(chromo_b->order_[p], chromo_b->order_[p - 1]);
	} else {
		std::swap(chromo_b->order_[p], chromo_b->order_[order_.size() - 1]);
	}
	auto fit_b = get_fitness();
	// Swaps the cities with indexes p and p + 1; if p = N - 1, swaps cities with indexes p and 0
	std::swap(chromo_c->order_[p], chromo_c->order_[(p + 1) % chromo_c->order_.size()]);
	auto fit_c = get_fitness();
	if(fit_a > fit_b && fit_a > fit_c) {
		delete chromo_b;
		delete chromo_c;
	} else if(fit_b > fit_c) {
		if(p) { std::swap(order_[p], order_[p - 1]); }
		else { std::swap(order_[p], order_[order_.size() - 1]); }
		delete chromo_c;
	} else {
		std::swap(order_[p], order_[(p + 1) % order_.size()]);
		delete chromo_b;
	}
}

std::pair<ClimbChromosome*, ClimbChromosome*> ClimbChromosome::recombine(const ClimbChromosome* other) {
	assert(is_valid());
	assert(other->is_valid());
	
	// Need to include size() because create_crossover_child takes [b, e):
	std::uniform_int_distribution<int> dist(0, order_.size());
	
	// Pick two random indices such that b <= e:
	auto r1 = dist(generator_);
	auto r2 = dist(generator_);
	auto [b, e] = std::minmax(r1, r2);
	
	// Make children:
	auto child1 = create_crossover_child(this, other, b, e);
	auto child2 = create_crossover_child(other, this, b, e);
	
	return std::make_pair(child1, child2);
}

ClimbChromosome* ClimbChromosome::create_crossover_child(const ClimbChromosome* p1, const ClimbChromosome* p2,
								unsigned b, unsigned e) const {
	const unsigned len = p1->order_.size();
	assert(len == p2->order_.size());
	ClimbChromosome* child = p1->clone();

	// We iterate over both parents separately, copying from parent1 if the
	// value is within [b,e) and from parent2 otherwise
	unsigned i = 0, j = 0;
	
	for ( ; i < len && j < len; ++i) {
		if (i >= b and i < e) {
			child->order_[i] = p1->order_[i];
		} else { // Increment j as long as its value is in the [b,e) range of p1
			while (p1->is_in_range(p2->order_[j], b, e)) {
				++j;
			}
			assert(j < len);
			child->order_[i] = p2->order_[j];
			j++;
		}
	}
	
	assert(child->is_valid());
	return child;
}


