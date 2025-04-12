{
  description = "cs24 at ucsb";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    zen-typ.url = "github:youwen5/zen.typ";
  };

  outputs =
    {
      self,
      nixpkgs,
      zen-typ,
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
          resolvePackagesPath = builtins.map (x: "packages/preview/" + x);
          mkTypstDerivation = pkgs.callPackage ./nix/mkTypstDerivation.nix { };
          flakeSelf = self;
        in
        {
          labs = {
            lab01 = {
              code = pkgs.callPackage ./labs/lab01/code { };
              writeup = pkgs.callPackage ./labs/lab01/writeup {
                inherit
                  zen-typ
                  resolvePackagesPath
                  mkTypstDerivation
                  flakeSelf
                  ;
              };
            };
            lab02 = {
              code = pkgs.callPackage ./labs/lab02/code { };
              writeup = pkgs.callPackage ./labs/lab02/writeup {
                inherit
                  zen-typ
                  resolvePackagesPath
                  mkTypstDerivation
                  flakeSelf
                  ;
              };
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
            ];
          };
        }
      );
    };
}
