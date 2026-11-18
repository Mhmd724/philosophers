# philosophers

My solution to the **Philosophers** project from the 42 curriculum: the classic
dining philosophers problem, written in C with POSIX threads and mutexes.

A number of philosophers sit around a table with one fork between each pair.
To eat, a philosopher needs both the fork on their left and the one on their
right. After eating they sleep, then think, then try to eat again. If one goes
too long without eating, they die and the simulation stops. The challenge is
to keep everyone alive without deadlocks or data races.

## How it works

- **One thread per philosopher**, each running an eat → sleep → think loop.
- **One mutex per fork**, plus a `philo_taken_by` field so a philosopher only
  picks up a fork that is free.
- **Even-numbered philosophers start 1.5 ms late**, so neighbours don't all
  reach for the same forks at once.
- **A monitor loop in the main thread** checks each philosopher's last meal
  time and stops the simulation when someone dies or when everyone has eaten
  the required number of meals.
- **Separate mutexes** protect printing, last-meal times, meal counts and the
  stop flags, so output lines never interleave and shared state is never read
  mid-write.
- **A single philosopher** is handled on its own: they take the only fork and
  die after `time_to_die`.

## Build

```sh
make        # builds ./philo
make clean  # removes object files
make fclean # removes object files and the binary
make re     # rebuilds from scratch
```

Requires `gcc` and pthreads (Linux or macOS).

## Usage

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```

All times are in milliseconds. Every argument must be a positive integer, and
the number of philosophers is capped at 200.

```sh
./philo 5 800 200 200      # nobody should die
./philo 5 800 200 200 7    # stops once everyone has eaten 7 times
./philo 4 310 200 100      # a philosopher dies
./philo 1 800 200 200      # takes the only fork, then dies
```

Each line of output is `timestamp_in_ms philosopher_id action`.

## Project structure

| File | Purpose |
| --- | --- |
| `src/main.c` | Argument parsing, starting and ending the simulation |
| `src/validations.c` | Input checks |
| `src/initializations.c` | Setting up and destroying forks, mutexes and philosophers |
| `src/philosopher_routine.c` | Thread routines for one or several philosophers |
| `src/philosophers_actions.c` | Eating, logging and the death monitor |
| `src/checkers.c` | Thread-safe checks on forks and simulation state |
| `src/utils.c` | `ft_atoi`, timestamps and a sleep that stops early when the simulation ends |
| `include/my_philosophers.h` | Structs and prototypes |

## Testing

I tested it with [LazyPhilosophersTester](https://github.com/MichelleJiam/LazyPhilosophersTester).

## Author

Mohamad Harajly — [@Mhmd724](https://github.com/Mhmd724)

## License

[MIT](LICENSE)
