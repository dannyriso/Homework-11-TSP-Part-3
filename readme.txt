This repository holds the files needed to implement the ClimbChromosome and TournamentDeme subclasses, meant to
further increase the efficiency of finding a solution to the Traveling Salesman Problem.

---
The ClimbChromosome subclass is implemented using the climb_chromosome header and implementation files. It overrides
the clone() and mutate() methods and overloads recombine() and create_crossover_child(). The mutate() method does so by
creating three potential chromosomes, evaluating each of their fitnesses, and then actually mutating the chromosome
to match the one with the highest fitness. The other three methods are nearly identical to their counterparts in
Chromosome, personalized only as necessary to account for ClimbChromosome.

Using ClimbChromosome in place of Chromosome produces a slight increase in efficiency, finding a shorter route between
all the cities in fewer iterations. However, it still has a tendency to prematurely converge, and the final route is
much longer than it could be.

---
The TournamentDeme subclass only overrides the select_parent() method. It uses tournament selection to do so, with
brackets of 8 to ensure a power of 2 less than the population size, which was 10 at minimum in testing. Other than
that, no other aspects of Deme were overloaded or overridden besides the constructor and destructor.

Using TournamentDeme rather than Deme in testing produced a vast improvement in results. Where before, no routes had
been reached less than 18,000, TournamentDeme produced routes approaching as low as 10,000.
