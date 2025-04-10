{
  stdenvNoCC,
  typst,
  fetchFromGitHub,
}:
{
  name ? null,
  pname ? null,
  version ? null,
  src,
  unixTime ? 0,
  fontPaths ? [ ],
  typstPackages ? [ ],
  postPackagePhase ? "",
  stdenv ? stdenvNoCC,
  nativeBuildInputs ? [ ],
  buildInputs ? [ ],
  packagesHash ? "",
  typstPackagesRev ? "7b657a93ca4aa28758b75d71bcb3135275771724",
  documentRoot ? "main.typ",
  typst-packages-src,
  ...
}@attrs:
let
  typst-packages-cache = stdenv.mkDerivation {
    name = "typst-packages-cache";
    src = "${typst-packages-src}/packages";
    dontBuild = true;
    installPhase =
      ''
        mkdir -p "$out/typst/packages"
        cp -LR --reflink=auto --no-preserve=mode -t "$out/typst/packages" "$src"/*
      ''
      + postPackagePhase;
  };
  font-paths = fontPaths;
  generateFontCommands = builtins.map (x: "cp -r " + x + " $out");
  font-packages = stdenv.mkDerivation {
    name = "fonts";
    phases = [ "installPhase" ];
    installPhase =
      ''
        mkdir -p $out
      ''
      + builtins.concatStringsSep "\n" (generateFontCommands font-paths);
  };
in
stdenv.mkDerivation {
  inherit
    name
    pname
    version
    src
    buildInputs
    ;

  XDG_CACHE_HOME = typst-packages-cache;
  SOURCE_DATE_EPOCH = unixTime;

  nativeBuildInputs = [ typst ] ++ nativeBuildInputs;

  buildPhase = ''
    export TYPST_FONT_PATHS=${font-packages}
    typst compile "${documentRoot}" "main.pdf"
  '';

  installPhase = ''
    install -Dm744 main.pdf $out/main.pdf
  '';
}
