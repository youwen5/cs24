#import "@youwen/zen:0.5.0": *
#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *
#import "@preview/cetz:0.3.4"
#import "@preview/cetz-plot:0.1.1"

#show: codly-init.with()

#show: zen.with(
  title: "Lab 2 Writeup",
  author: "Youwen Wu",
  subtitle: "CS24, Spring 2025",
  outline-separate-page: false,
)

#outline()

#codly(languages: codly-languages)

#show link: underline

= Prelude

Code available on
#link("https://github.com/youwen5/cs24/tree/main/labs/lab01/code")[GitHub]. A
reproducible build environment is included, if you have
#link("https://nixos.org/")[Nix] with flakes installed, you can run
```sh
nix build github:youwen5/cs24#labs.lab01.code
result/bin/3sum_analysis
```

Additionally, in the same Git tree, you will find the source code of this document alongside the plotting code (written using CeTZ). You may reproducibly compile this document as well using Nix.
```sh
nix build github:youwen5/cs24#labs.lab01.writeup
# pdf available at result/main.pdf
```

