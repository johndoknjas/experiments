/* Notes:

- random_device is used to generate a pseudo-random seed, which is used to initialize an instance of
  mt19937.
- If the same seed were used for mt19937 on each run, then the same random numbers / shuffles would be
  outputted using mt19937.
    - So, this is why the seed should be different each time. random_device is good enough for this.
- random_device could also be used on its own to generate random numbers, replacing the need for mt19937
  entirely. However, using random_device many times can lead to a degradation in performance. So generally,
  it's just used to generate a seed for a better random number generator (like mt19937).
    - random_device is also implementation defined. It should use data from an external source on the computer,
      with the goal of generating non-deterministic random numbers. However, if such a source can't be found,
      then it falls back on a deterministic PRNG approach (this doesn't seem to be relevant on your computer
      though - as well as for most computers for that matter).
    - An exception was that in MinGW, it used to be that random_device would be deterministic (so multiple
      instances of random_device would genreate the same sequences, and multiple runs of a program would
      lead to a random_device instance generating the same sequences). However, this bug was fixed in
      GCC 9.2. https://en.cppreference.com/w/cpp/numeric/random/random_device
      So, it's not a problem for how you're currently using it in the Connect Four engine / Versus Sim.
    - So on standard computers like yours, random_device is completely fine. The main downside of it is that
      it can get expensive if it's called many times (since it gets data from the actual computer in order
      to generate "true" randomness). But if it's just used in functions/loops that aren't called much, all good
      (and this is what you're currently doing for the Connect Four engine and Versus Sim).
- mt19937 is a string of 2^19937-1 numbers, so as long as the seed is different on a call to it, all good.
  mt19937 only repeats itself after 2^19937-1 uses.
- Each instance of mt19937 is separate from each other (not like srand() and rand(), which do global stuff).
  If each mt19937 is seeded with the same seed, then they will output identical values, but if they're
  seeded with different seeds, then they will output different values (and of course don't affect each other).
- The rationale behind using random_device to seed an mt19937 instance is nicely explained in
  Sam's answer: https://stackoverflow.com/questions/45425115/generating-random-numbers-in-c-using-stdrandom-device

- For the Connect Four, it's more ideal to declare a random_device and seed it into an mt19937 instance once,
  and then use that same mt19937 instance every time a random number / random shuffle is needed in the project.
    - However, declaring a random_device and mt19937 in every function that requires randomness should also
      be fine. The main thing is that this function isn't called a very large number of times, since as
      mentioned random_device can degrade in performance after many implementations of it.
        - See Michael's comment: https://stackoverflow.com/questions/39288595/why-not-just-use-random-device
    - In the Connect Four project and Versus Sim, instances of random_device and mt19937 are not declared
      in any big loops (or in functions which are called a very large number of times), so should be all good.
    - As the output from second_mt() shows, using a new random_device and mt19937 each time a 
      random number / shuffle is needed is fine. Different outputs are produced, both within the same run and on
      different runs of the program.

- Note that for generating random numbers, the same uniform_int_distribution can be used to generate
  multiple random numbers - or, a new uniform_int_distribution can be created whenever you need to generate
  a random number. E.g., see user13723942's answer: https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
  Shows it's fine using the same uid in a loop of 10 iterations.
  Vittorio's answer shows it's fine using different uids for each single random number generation:
  https://stackoverflow.com/questions/19036141/vary-range-of-uniform-int-distribution
*/


#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

void first_mt() {
    random_device rd;
    mt19937 g(rd());
    for (int i = 0; i < 5; i++) {
        uniform_int_distribution<int> uid(1, 10);
        int var = uid(g);
        cout << var << "\n";
    }
    cout << "\n";
    vector<int> vec = {1,2,3,4,5};
    shuffle(vec.begin(), vec.end(), g);
    for (int current: vec) {
        cout << current << ", ";
    }
    cout << "\n";
    shuffle(vec.begin(), vec.end(), g);
    for (int current: vec) {
        cout << current << ", ";
    }
    cout << "\n-----------\n\n";
}

void second_mt() {
    vector<int> old_vec = {1,2,3,4,5};
    vector<int> vec = old_vec;
    for (int i = 0; i < 3; i++) {
        vec = old_vec;
        random_device rd;
        mt19937 g(rd());
        shuffle(vec.begin(), vec.end(), g);
        for (int current: vec) {
            cout << current << ", ";
        }
        cout << "\n";
        uniform_int_distribution<int> uid(1, 10);
        int var = uid(g);
        cout << var << "\n";
    }
}

void random_device_test() {
    random_device rd1;
    random_device rd2;
    cout << rd1() << ", " << rd1() << "\n";
    cout << rd2() << ", " << rd2() << "\n";
}

int main()
{
    first_mt();
    second_mt();
    random_device_test();

    return 0;
}
