/*
 * The declaration of the TournamentDeme class, which inherites from Deme and overrides select_parent(), as well
 * as any other methods and variables needed for select_parent() to function.
 */

#include "deme.hh"

class TournamentDeme : public Deme {
	public:
		TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);
		virtual ~TournamentDeme();
	protected:
		ClimbChromosome* select_parent() override;
};
