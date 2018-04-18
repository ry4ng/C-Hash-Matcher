## What does this program do?

C-Hash-Matcher aims to find the matching hex value for a given hash, therefore finding out the
unencrypted value of the hash.

## Usage guide - Mac & Linux

Clone the repository:
```bash
git clone https://github.com/ry4n98/C-Hash-Matcher
```

Navigate to the folder by running:
```bash
cd C-Hash-Matcher
```

Run the shell file to link and compile the source code.
```bash
sh scripts/build.sh
``` 

If all goes well this will create a file ```a.out```. Then simply run:

```bash
./a.out <target hash> <target int>
```

### Example

```bash
./a.out e401f2bd399f3456e5348217a7908ca545ea6d179f60f297a1b0133e87d2ff85 5001
```

Expected output:
```bash
Starting at:  0
Finishing at: 5,001
------------------------------------------------------------------------------
Target hash:  e401f2bd399f3456e5348217a7908ca545ea6d179f60f297a1b0133e87d2ff85

Hashing...
----------------------------------------------------------------------------
A match for your target hash hash been found!

Raw value:  1388
Int value:  5,000
Hash value: e401f2bd399f3456e5348217a7908ca545ea6d179f60f297a1b0133e87d2ff85
----------------------------------------------------------------------------

5,001 hashes checked in 0.029089 seconds.
```

In this case, a match was found, we now know that the un-hashed value for `e401f2bd399f3456e5348217a7908ca545ea6d179f60f297a1b0133e87d2ff85` is the hex value of `1388`. 

[GitHub Repo](https://github.com/ryansmith98/C-Hash-Matcher)

[Report an Issue](https://github.com/ryansmith98/C-Hash-Matcher/issues)

[![License](https://img.shields.io/badge/License-MIT-yellowgreen.svg?style=flat-square)](https://github.com/ryansmith98/C-Hash-Matcher/blob/master/LICENSE.md)
