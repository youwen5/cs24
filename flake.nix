{
  description = "cs24 at ucsb";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    zen-typ.url = "github:youwen5/zen.typ";
    mkTypstDerivation.url = "github:youwen5/mkTypstDerivation.nix";
  };

  outputs =
    {
      self,
      nixpkgs,
      zen-typ,
      mkTypstDerivation,
    }:
    let
      forAllSystems = nixpkgs.lib.genAttrs [
        "aarch64-darwin"
        "aarch64-linux"
        "x86_64-darwin"
        "x86_64-linux"
      ];
    in
    {
      legacyPackages = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
          flakeSelf = self;
          typstLib = import mkTypstDerivation { inherit pkgs; };
          extraPackages =
            let
              zenTyp = pkgs.stdenvNoCC.mkDerivation (finalAttrs: {
                pname = "zen-typ-package";
                version = "0.5.0";
                src = zen-typ;
                dontBuild = true;
                installPhase = ''
                  mkdir -p "$out/packages/youwen/zen/0.5.0"
                  cp -r typst/* "$out/packages/youwen/zen/0.5.0"
                '';
              });
            in
            pkgs.symlinkJoin {
              name = "typst-packages-src";
              paths = [
                "${zenTyp}/packages"
                # more custom packages can be added here
              ];
            };
          fontPaths = [
            "${pkgs.liberation_ttf}/share/fonts/truetype/*"
            # more fonts can be added
          ];
        in
        {
          labs = {
            lab01 = {
              code = pkgs.callPackage ./labs/lab01/code { };
              writeup = typstLib.mkTypstDerivation rec {
                inherit fontPaths;
                name = "lab01";
                src = ./labs/lab01/writeup;
                documentRoot = "main.typ";
                typstPackages = typstLib.fetchTypstPackages {
                  inherit documentRoot src extraPackages;
                  hash = "sha256-ukgjzbF9Tdvn/eTKUuX5AGHS4QeK00mzjFZ+aDj5axc=";
                };
                unixTime = builtins.toString flakeSelf.lastModified;
              };
            };
            lab02 = {
              code = pkgs.callPackage ./labs/lab02/code { };
            };
            lab03 = {
              code = pkgs.callPackage ./labs/lab03 { };
            };
          };
        }
      );
      devShells = forAllSystems (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              clang-tools
              mesonlsp
              ninja
              meson
              valgrind
              gdb
              just
            ];
          };
        }
      );
    };
}
