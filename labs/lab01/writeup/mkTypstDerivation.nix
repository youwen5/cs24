{
  stdenvNoCC,
  typst,
  fetchFromGitHub,
}:
{
  unixTime ? 0,
  fontPaths ? [ ],
  packages ? [ ],
  stdenv ? stdenvNoCC,
  nativeBuildInputs,
  buildInputs,
  ...
}@attrs:
let
  typst-packages-src = fetchFromGitHub {
    owner = "typst";
    repo = "packages";
    rev = "7b657a93ca4aa28758b75d71bcb3135275771724";
    hash = "sha256-S746ZI5FIFu482AlaF0lDoxIOAgqF64gD/sYdAZUNjk=";
    sparseCheckout = [
      "packages/preview/cetz-plot"
      "packages/preview/cetz"
      "packages/preview/showybox"
      "packages/preview/ctheorems"
      "packages/preview/codly"
      "packages/preview/codly-languages"
      "packages/preview/oxifmt"
    ];
  };
  typst-packages-cache = stdenvNoCC.mkDerivation {
    name = "typst-packages-cache";
    src = "${typst-packages-src}/packages";
    dontBuild = true;
    installPhase = ''
      mkdir -p "$out/typst/packages/youwen/zen/0.5.0"
      cp -LR --reflink=auto --no-preserve=mode -t "$out/typst/packages" "$src"/*
      cp -LR --reflink=auto --no-preserve=mode -t "$out/typst/packages/youwen/zen/0.5.0" "${zen-typ}/typst"/*
    '';
  };
in
stdenvNoCC.mkDerivation {
  name = "lab01-writeup";

  src = ./.;

  XDG_CACHE_HOME = typst-packages-cache;
  SOURCE_DATE_EPOCH = builtins.toString flakeSelf.lastModified;

  nativeBuildInputs = [
    typst
  ];

  buildPhase = ''
    # create home dir in nix build environment
    export HOME="$(mktemp -d)"
    mkdir -p $HOME/.local/share/fonts
    # lualatex needs to know where to get fonts
    export TYPST_FONT_PATHS=$HOME/.local/share/fonts

    # "install" fonts so Typst can find them
    cp -r ${liberation_ttf}/share/fonts/truetype $HOME/.local/share/fonts

    typst compile main.typ
  '';

  installPhase = ''
    install -Dm744 main.pdf $out/main.pdf
  '';
}
