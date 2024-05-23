# CLog

~~Logging tool written in C~~
My ***first-ever*** real programming project! This
is a development log tool written in C using `sqlite3` and `less`, written during
my time in Summerside, PEI mostly during my welding class in high school.
I was *really* into free software, C "purity", and snark at this point in my
life.
That being said, this was the first program I ever made, and by god I actually
use it to organize my thoughts in projects today!

That being said, there are still many things in this codebase that I would change
and plan to update -- as it stands, this code is as it was written 7 years ago
when I was 15 years old.
Believe me, I've improved a lot in the time since then.

## Building

To build the program into `./bin/`

```sh
$ make
```

To build and install the program into `/usr/bin/`

```sh
$ make
$ sudo make install
```

To clean build directory

```sh
$ make clean
```

To uninstall from `/usr/bin/`

```sh
$ sudo make uninstall
```

## License

This program is licensed under the GNU General Public License 3. The full terms
can be found in [LICENSE](LICENSE).
