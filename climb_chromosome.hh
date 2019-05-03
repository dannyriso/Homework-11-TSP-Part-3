/*
 * The declaration of the ClimbChromosome class, which inherits from Chromosome and overrides mutate() and clone().
 */

#include "chromosome.hh"
#include <cassert>
#include <random>

class ClimbChromosome : public Chromosome {
	public:
		ClimbChromosome(const Cities* cities_ptr);
		virtual ~ClimbChromosome() = default;
		
		ClimbChromosome* clone() const override;
		void mutate() override;
		std::pair<ClimbChromosome*, ClimbChromosome*> recombine(const ClimbChromosome* other);
		ClimbChromosome* create_crossover_child(const ClimbChromosome* parent1,
							const ClimbChromosome* parent2,
							unsigned begin,
							unsigned end) const;
};
